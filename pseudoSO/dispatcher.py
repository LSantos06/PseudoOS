import sys
import FileReader
import time
import signal
from ListManager import ListManager
from MemoryManager import MemoryManager
from ProcessController import ProcessController
from ResourceManager import ResourceManager

#constantes dos valores dos recursos
IMPRESSORAS = 2
SCANNERS = 1
MODENS = 1
SATA = 2
MAX_BUFF = 64
MIN_PRIOR = 0
MAX_PRIOR = 3
RT_MEMORY = 64
MEMORY = 1024
QUANTUM = 1

#recursos do sistema
resources = {
				'impressoras': IMPRESSORAS,
				'sata': SATA,
				'modens': MODENS,
				'scanners': SCANNERS,
				'memory': MEMORY,
				'rt_memory': RT_MEMORY,
				'min_prior': MIN_PRIOR,
				'max_prior': MAX_PRIOR,
				'max_buff': MAX_BUFF
			}

# instancia de modulos
process_controller = ProcessController()
memory_manager = MemoryManager()
resource_manager = ResourceManager(resources)
list_manager = ListManager(memory_manager, process_controller, resource_manager)

#passa list manager para process controller
process_controller.list_manager = list_manager

#inicializador de memoria
def start_memory():
	if memory_manager.check(list_manager.mem_alloc_block, resource_manager.resources['memory']) == None:
			mab = memory_manager.allocate(list_manager.mem_alloc_block, resource_manager.resources['memory'])
			mab = memory_manager.split(mab, resource_manager.resources['rt_memory'])
			list_manager.rt_mem_alloc_block = mab
			list_manager.mem_alloc_block = mab['next']
			list_manager.rt_mem_alloc_block['next'] = None
			list_manager.mem_alloc_block['prev'] = None

def main():
	dispatch_list = FileReader.process_list_file(sys.argv[1])

	start_memory()

	list_manager.start(dispatch_list)
	curr = None
	while list_manager.checkLists() or curr:
		list_manager.main_queue_routine()
		list_manager.user_queue_routine()
		#se existe um processo corrente subtrai o quantum e verifica se o tempo restante nao acabou
		if curr :
			curr['remainingcputime'] -= QUANTUM
			if curr['remainingcputime'] <= 0:
				curr = process_controller.termProcessBlock(curr)
				# Desaloca o processo
				if curr['priority'] == resource_manager.resources['min_prior']:
					curr['mem_alloc_block']['allocated'] = 0
				else: # Retira da lista
					curr['mem_alloc_block'] = memory_manager.free(curr['mem_alloc_block'])
					resource_manager.free(curr)
				curr = None
			# Caso ainda exista tempo restante de CPU e a sua prioridade nao eh 0
			# Suspende o processo e se sua prioridade < 3, adiciona uma penalidade +1
			# E insere na lista de processos em espera
			elif curr['priority'] > resource_manager.resources['min_prior'] and\
				 (list_manager.rt_queue or list_manager.prior1_queue or\
				 list_manager.prior2_queue or list_manager.prior3_queue ):
				curr = process_controller.suspendProcessBlock(curr) #Processo eh suspenso
				if curr['priority'] < resource_manager.resources['max_prior']:
					curr['priority'] += 1
				if curr['priority'] == 2:
					list_manager.prior2_queue = \
						process_controller.pushProcessBlock(list_manager.prior2_queue, curr)
				elif curr['priority'] == 3:
					list_manager.prior3_queue = \
						process_controller.pushProcessBlock(list_manager.prior3_queue, curr)
				curr = None
		# Se nao existe um processo executando na CPU, verifica se existe algum
    # processo RT a ser executado, senao existir verifica por ordem de
    # prioridade (1 -> 3). Verifica estado do processo, se for SUSPENDED reinicia
    # a execucao e se nao for usa a funcao start
		if not curr and	(list_manager.rt_queue or list_manager.prior1_queue or\
										list_manager.prior2_queue or list_manager.prior3_queue ):
			if list_manager.rt_queue != None:
				(p, list_manager.rt_queue) = \
					process_controller.popProcessBlock(list_manager.rt_queue)
			elif list_manager.prior1_queue != None:
				(p, list_manager.prior1_queue) =\
					process_controller.popProcessBlock(list_manager.prior1_queue)
			elif list_manager.prior2_queue != None:
				(p, list_manager.prior2_queue) =\
					process_controller.popProcessBlock(list_manager.prior2_queue)
			else:
				(p, list_manager.prior3_queue) =\
					process_controller.popProcessBlock(list_manager.prior3_queue)
			if p['status'] == 'SUSPENDED':
				p = process_controller.restartProcessBlock(p)
			else:
				p = process_controller.startProcessBlock(p)
			curr = p
		time.sleep(QUANTUM)
		list_manager.timer += QUANTUM
		process_controller.printTable()
	list_manager.mem_alloc_block = memory_manager.free(list_manager.mem_alloc_block)
	list_manager.rt_mem_alloc_block = memory_manager.free(list_manager.rt_mem_alloc_block)
	process_controller.printTable()

if __name__ == "__main__":
	if len(sys.argv) != 2:
		print "Comando invalido"
		print "python main.py processes.txt"
	else:
		main()
