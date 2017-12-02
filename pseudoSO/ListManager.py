import sys

MemoryManager = None
ProcessController = None
ResourceManager = None

class ListManager:
	timer = None
	mem_alloc_block = None
	rt_mem_alloc_block = None
	main_queue = None
	rt_queue = None
	user_queue = None
	prior1_queue = None
	prior2_queue = None
	prior3_queue = None
	processtable = {}

	#construtor da classe list manager
	def __init__(self, mm, pc, rm):
		global MemoryManager, ProcessController, ResourceManager
		MemoryManager = mm
		ProcessController = pc
		ResourceManager = rm

	# retorna true se alguma das listas nao esta vazia
	def checkLists(self):
		return self.main_queue or self.rt_queue or self.user_queue or\
				self.prior1_queue or self.prior2_queue or self.prior3_queue

	#inicia gerencia das listas
	def start(self, dispatch_list):
		self.timer = 0
		for d in dispatch_list:
			p = ProcessController.createProcessBlock()
			p = ProcessController.initProcessBlock(p, d)
			self.main_queue = ProcessController.pushProcessBlock(self.main_queue, p)

	#enquanto houver processo na fila principal arrivaltime dentro do limite
	#'popa' processo da lista e analisa prioridade
	#prioridade 0 -> processo realtime; checa recursos e memoria para alocar
	#prioridade 1-3 -> processo de usuario; checa recursos e memoria para alocar
	# e coloca processo na lista de processos de usuario
	def main_queue_routine(self):
		while self.main_queue and self.main_queue['arrivaltime'] <= self.timer:
			proc, self.main_queue = ProcessController.popProcessBlock(self.main_queue)
			if proc['priority'] == ResourceManager.resources['min_prior']:
				if ResourceManager.checkRtResources(proc) or proc['mem_usage'] > ResourceManager.resources['rt_memory']:
					print "Process deleted - excess memory request"
					proc = None
				else:
					proc['mem_alloc_block'] = MemoryManager.allocate(self.rt_mem_alloc_block, ResourceManager.resources['rt_memory'])
					self.rt_queue = ProcessController.pushProcessBlock(self.rt_queue, proc)
			elif proc['priority'] <= ResourceManager.resources['max_prior']:
				if ResourceManager.checkResources(proc) or proc['mem_usage'] >\
					ResourceManager.resources['memory'] - ResourceManager.resources['rt_memory']:
					print "Process deleted - excess memory request"
					proc = None
				else:
					self.user_queue = ProcessController.pushProcessBlock(self.user_queue, proc)
			else:
				print "Error reading priority order."
				sys.exit(-1)

	#enquanto houver processo na fila de processos de usuario
	#checa se ha memoria disponivel
	#'popa', seta status de READY, aloca bloco de memoria ou 'splita'
	#gerente de recursos aloca processo
	#de acordo com prioridade, coloca processo na respectiva fila
	def user_queue_routine(self):
		while self.user_queue and not ResourceManager.check(self.user_queue):
			m = MemoryManager.check(self.mem_alloc_block, self.user_queue['mem_usage'])
			if m == None:
				break
			proc, self.user_queue = ProcessController.popProcessBlock(self.user_queue)
			proc['status'] = 'READY'
			if proc['mem_usage'] == m['size'] - m['allocated']:
				proc['mem_alloc_block'] = MemoryManager.allocate(m, proc['mem_usage'])
			else:
				proc['mem_alloc_block'] = MemoryManager.split(m, proc['mem_usage'])
			ResourceManager.alloc(proc)
			if proc['priority'] == 1:
				self.prior1_queue = ProcessController.pushProcessBlock(self.prior1_queue, proc)
			elif proc['priority'] == 2:
				self.prior2_queue = ProcessController.pushProcessBlock(self.prior2_queue, proc)
			elif  proc['priority'] == 3:
				self.prior3_queue = ProcessController.pushProcessBlock(self.prior3_queue, proc)
			else:
				print "Error reading priority order."
				sys.exit(-1)
