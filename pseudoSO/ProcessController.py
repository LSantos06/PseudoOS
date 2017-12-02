import os
import signal
import sys
import colors
import time

class Mock:
	pass

class ProcessController:
	list_manager = None
	proc = None

	def __init__(self):
		self.proc =  Mock()

	# cria uma estrutura de processe
	def createProcessBlock(self):
		proc = {}
		proc['status'] = 'UNINITIALISED'
		proc['arrivaltime'] = 0
		proc['priority'] = 0
		proc['remainingcputime'] = 0
		proc['mem_usage'] = 0
		proc['impressoras'] = 0
		proc['scanners'] = 0
		proc['modens'] = 0
		proc['sata'] = 0
		proc['mab'] = None
		proc['next'] = None
		return proc

	#Inicializa essa estrutura
	def initProcessBlock(self, proc, d):
		proc['status'] = 'INITIALISED'
		tok = d.split(", ")
		tok = map(int, tok)
		proc['arrivaltime'] = tok[0]
		proc['priority'] = tok[1]
		proc['remainingcputime'] = tok[2]
		proc['mem_usage'] = tok[3]
		proc['impressoras'] = tok[4]
		proc['scanners'] = tok[5]
		proc['modens'] = tok[6]
		proc['sata'] = tok[7]
		return proc

	#Insere mais um processo a fila
	def pushProcessBlock(self, head, proc):
		if head:
			curr = head
			while curr['next']:
				curr = curr['next']
			curr['next'] = proc
			curr['next']['next'] = None
		else:
			head = proc
		return head

	#Retira a cabeca da lista de processos
	def popProcessBlock(self, head):
		if head:
			proc = head
			head = head['next']
			proc['next'] = None
			return (proc, head)
		return None

	# Muda o estado do processo para RUNNING
	# Se o estado anterior = SUSPENDED
	def restartProcessBlock(self, proc):
		os.kill(proc['pid'], signal.SIGCONT)
		proc['status'] = 'RUNNING'
		self.updateTable(proc)
		return proc

	# Muda o estado do processo para RUNNING
	def startProcessBlock(self, proc):
		proc['pid'] = os.fork()
		if proc['pid'] == 0:
			proc['pid'] = os.getpid()
			proc['status'] = 'RUNNING'
			os.execv("./proc", ["./proc"])
		else:
			os.kill(proc['pid'], signal.SIGCONT)
			proc['status'] = 'RUNNING'
		self.updateTable(proc)
		return proc

	# Muda o estado do processo para SUSPENDED
	def suspendProcessBlock(self, proc):
		stat = os.kill(proc['pid'], signal.SIGTSTP)
		if stat == 0:
			print "Suspend of %d failed" % int(proc['pid'])
		os.waitpid(proc['pid'], os.WUNTRACED)
		proc['status'] = 'SUSPENDED'
		self.updateTable(proc)
		return proc

	# Muda o estado para finalizado
	def termProcessBlock(self, proc):
		stat = os.kill(proc['pid'], signal.SIGINT)
		if stat != 0:
			os.waitpid(proc['pid'], os.WUNTRACED)
		proc['status'] = 'TERMINATED'
		self.updateTable(proc)
		return proc

	# Exibe cada processo e seus atributos
	def updateTable(self, p):
		info = colors.BACK_ON_BLACK + colors.FRONT_GREEN
		info += "%-8s" % str(p['pid'])
		info += "%-9s" % str(p['mem_alloc_block']['offset'])
		info += "%-9s" % str(p['mem_usage'])
		info += "%-9s" % str(p['priority'])
		info += "%-7s" % str(p['remainingcputime'])
		info += "%-9s" % str(p['impressoras'])
		info += "%-7s" % str(p['scanners'])
		info += "%-8s" % str(p['modens'])
		info += "%-8s" % str(p['sata'])
		info += "%-8s" % str(p['status'])
		info += colors.DEFAULT
		self.list_manager.processtable[p['pid']] = info

	#header da tabela de processo
	def printTable(self):
		tab = colors.CLEAR
		tab += colors.BACK_ON_GREEN + colors.FRONT_BLACK
		tab += "%-7s" % 'PID'
		tab += "%-8s" % 'OFFSET'
		tab += "%-8s" % 'BLOCKS'
		tab += "%-10s" % 'PRIORITY'
		tab += "%-6s" % 'TIME'
		tab += "%-10s" % 'PRINTERS'
		tab += "%-7s" % 'SCANS'
		tab += "%-8s" % 'MODEMS'
		tab += "%-10s" % 'DRIVES'
		tab += "%-14s" % 'STATUS'
		tab += "\n"
		tab += colors.DEFAULT
		for pid in self.list_manager.processtable:
			tab += self.list_manager.processtable[pid] + "\n"
			tab += colors.DEFAULT
			sys.stdout.write(tab)
			sys.stdout.flush()
