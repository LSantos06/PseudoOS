class MemoryManager:

	def allocate(self, mem, size):
		if mem == None:
			mem = {}
			mem['offset'] = 0
			mem['size'] = size
			mem['allocated'] = size
			mem['next'] = None
			mem['prev'] = None
		else:
			mem['allocated'] = size
		return mem

	def check(self, mem, size):
		while mem != None:
			if size <= mem['size'] - mem['allocated']:
				return mem
			else:
				mem = mem['next']
		return None

	def free(self, mem):
		if mem == None:
			return None
		elif mem['prev'] != None or mem['next'] != None:
			mem['allocated'] = 0
			mem = self.merge(mem)
		else:
			mem = None
		return mem

	def merge(self, m):
		ml = m['prev']
		mr = m['next']
		if ml != None and ml['allocated'] == 0:
			temp = m
			m = ml
			m['size'] += temp['size']
			m['next'] = temp['next']
			a = None
			if m['next'] != None:
				m['next']['prev'] = m
		if mr != None and mr['allocated'] == 0:
			temp = mr
			m['size'] += temp['size']
			m['next'] = temp['next']
			if m['next'] != None:
				m['next']['prev'] = m
		return m

	def split(self, m, size):
		mr = {}
		mr['offset'] = m['offset'] + size
		mr['size'] = m['size'] - size
		mr['allocated'] = 0
		mr['next'] = m['next']
		if mr['next'] != None:
			mr['next']['prev'] = mr
		mr['prev'] = m
		m['next'] = mr
		m['size'] = size
		m['allocated'] = size
		return m
