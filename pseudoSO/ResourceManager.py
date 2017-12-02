class ResourceManager:
	resources = {}
	rt_resources = {}

	def __init__(self, res):
		self.resources = res
		self.rt_resources = {
						'max_impressoras': 0,
						'max_scanners': 0,
						'max_modens': 0,
						'max_sata': 0
					}

	def alloc(self, res):
		for r in res:
			try:
				self.resources[r] -= res[r]
			except Exception as e:
				pass

	def free(self, res):
		for r in res:
			try:
				self.resources[r] += res[r]
			except Exception as e:
				pass

	def check(self, res):
		try:
				if 	self.resources['scanners'] >= res['scanners'] and\
					self.resources['impressoras'] >= res['impressoras'] and\
					self.resources['modens'] >= res['modens'] and\
					self.resources['sata'] >= res['sata']:
						return False
				else:
					return True
		except Exception as e:
			return False

	def checkRtResources(self, res):
		try:
			return	self.rt_resources['scanners'] < res['scanners'] or\
			self.rt_resources['impressoras'] < res['impressoras'] or\
			self.rt_resources['modens'] < res['modens'] or\
			self.rt_resources['sata'] < res['sata']
		except Exception as e:
			return True

	def checkResources(self, res):
		try:
			return	self.resources['scanners'] < res['scanners'] or\
			self.resources['impressoras'] < res['impressoras'] or\
			self.resources['modens'] < res['modens'] or\
			self.resources['sata'] < res['sata']
		except Exception as e:
			return True
