import math
import random
import os
import datetime
import numpy as np

TASK_NUM = 1

N_LIMIT = 6
M_LIMIT = 10000
S_LBD = 1
S_RBD = 10000
C_LBD = 0
C_RBD = 100
P_LBD = 0
P_RBD = 10000

def log(string):
	print(string, flush = True)
	with open("gen.log", "a") as f:
		f.write("[{}] {}\n".format(datetime.datetime.now(), string))

def genPUniform(n, p0_lbd = P_LBD, p0_rbd = P_RBD, pi_lbd = P_LBD, pi_rbd = P_RBD, **extra_param):
	rng = np.random.default_rng()
	u = np.concatenate((rng.integers(p0_lbd, p0_rbd + 1, (n, 1)), rng.integers(pi_lbd, pi_rbd + 1, (n, 2))), axis = 1)
	v = np.concatenate((rng.integers(p0_lbd, p0_rbd + 1, (n, 1)), rng.integers(pi_lbd, pi_rbd + 1, (n, 2))), axis = 1)
	return u, v

def genPDeterministic(n, **extra_param):
	return np.array((0, 1, 0) * n).reshape(n, 3), np.array((0, 0, 1) * n).reshape(n, 3)

def genUniform(n, m, s_lbd = S_LBD, s_rbd = S_RBD, **extra_param):
	rng = np.random.default_rng()

	if "c" in extra_param:
		c = extra_param["c"]
	elif "gen_c" in extra_param:
		c = extra_param["gen_c"](extra_param)
	else:
		c = rng.integers(C_LBD, C_RBD + 1)

	s = rng.integers(s_lbd, s_rbd + 1, (n, 2))
	for i in range(n):
		if s[i][0] > s[i][1]:
			s[i] = s[i][1], s[i][0]
	u, v = extra_param.get("gen_p", genPUniform)(n, **extra_param)
	return c, s, u, v

def genCommonDivisor(n, m, s_lbd = S_LBD, s_rbd = S_RBD, **extra_param):
	rng = np.random.default_rng()
	d = 2 * rng.integers(20, 300)
	
	if "c" in extra_param:
		c = extra_param["c"]
	elif "gen_c" in extra_param:
		c = extra_param["gen_c"](extra_param)
	else:
		c = rng.integers(C_LBD, C_RBD + 1)

	s = d * rng.integers(math.ceil(s_lbd / d), math.floor(s_rbd / d) + 1, (n - 1, 2))
	s = np.concatenate((s, rng.integers(s_lbd, s_rbd + 1, (1, 2))))
	for i in range(n):
		if s[i][0] > s[i][1]:
			s[i] = s[i][1], s[i][0]
	
	u, v = extra_param.get("gen_p", genPUniform)(n, **extra_param)

	return c, s, u, v

def genLargeHead(n, m, s_lbd = S_LBD, s_rbd = S_RBD // 10, **extra_param):
	rng = np.random.default_rng()
	
	if "c" in extra_param:
		c = extra_param["c"]
	elif "gen_c" in extra_param:
		c = extra_param["gen_c"](extra_param)
	else:
		c = rng.integers(C_LBD, C_RBD + 1)

	if extra_param.get("overflow", False):
		s1 = rng.integers(m + 1, S_RBD + 1, (1, 2))
	else:
		s1 = rng.integers(math.ceil(m / 4), math.ceil(m / 2), (1, 2))
	s2 = rng.integers(s_lbd, s_rbd + 1, (n - 1, 2))
	s = np.concatenate((s1, s2))
	for i in range(n):
		if s[i][0] > s[i][1]:
			s[i] = s[i][1], s[i][0]
	
	u, v = extra_param.get("gen_p", genPUniform)(n, **extra_param)

	return c, s, u, v

def gcd(a, b):
	c = a % b
	while c != 0:
		a = b
		b = c
		c = a % b
	return b

def genLargeTail(n, m, s_lbd = S_LBD, s_rbd = S_RBD // 1000, **extra_param):
	rng = np.random.default_rng()
	
	if "c" in extra_param:
		c = extra_param["c"]
	elif "gen_c" in extra_param:
		c = extra_param["gen_c"](extra_param)
	else:
		c = rng.integers(C_LBD, C_RBD + 1)

	while True:
		s0 = rng.integers(27, 52, (1, 2))
		if gcd(s0[0, 0], s0[0, 1]) == 1:
			break
	s1 = rng.integers(s_lbd, s_rbd + 1, (n - 2, 2))
	if extra_param.get("overflow", False):
		s2 = rng.integers(m, S_RBD + 1, (1, 2))
	else:
		s2 = rng.integers(math.ceil(m / 4), math.ceil(m / 2), (1, 2))
	s = np.concatenate((s0, s1, s2))
	for i in range(n):
		if s[i][0] > s[i][1]:
			s[i] = s[i][1], s[i][0]
	
	u, v = extra_param.get("gen_p", genPUniform)(n, **extra_param)

	return c, s, u, v

def genUnbalanced(n, m, s1_lbd = S_LBD, s1_rbd = S_RBD, s2_lbd = S_LBD, s2_rbd = S_RBD, **extra_param):
	rng = np.random.default_rng()
	
	if "c" in extra_param:
		c = extra_param["c"]
	elif "gen_c" in extra_param:
		c = extra_param["gen_c"](extra_param)
	else:
		c = rng.integers(C_LBD, C_RBD + 1)

	s1 = rng.integers(s1_lbd, s1_rbd + 1, (n, 1))
	s2 = rng.integers(s2_lbd, s2_rbd + 1, (n, 1))
	s = np.concatenate((s1, s2), axis = 1)
	for i in range(n):
		if s[i][0] > s[i][1]:
			s[i] = s[i][1], s[i][0]
	
	u, v = extra_param.get("gen_p", genPUniform)(n, **extra_param)

	return c, s, u, v

def genTestcase(filename, n, m, gen, **extra_param):
	log(f"Generating input for case {filename}, params: gen = {gen.__name__}, {n = }, {m = }, {extra_param = }")
	# assert ..., "Parameters invalid!"
	c, s, u, v = gen(n, m, **extra_param)
	
	# Assertions if needed
	for i in range(n):
		assert u[i][1] + u[i][2] >= 1 and v[i][1] + v[i][2] >= 1

	with open("{}.in".format(filename), "w") as f:
		print(n, m, c, file = f)
		for i in range(n):
			print(*s[i], *u[i], *v[i], file = f)
	log("Generating output for case {}".format(filename))
	os.system('(time ../ScarletStorm/std < {}.in > {}.ans) 2>> gen.log'.format(filename, filename))

class Cases:
	def __init__(self, prefix = ""):
		self.cnt = 0
		self.prefix = prefix
	
	def gen(self, n, m, gen, **extra_param):
		self.cnt += 1
		genTestcase("{}{}".format(self.prefix, self.cnt), n, m, gen, **extra_param)
	
	def skip(self, cnt = 1):
		self.cnt += cnt

os.system("rm gen.log")
testcase = Cases()
# precase = Cases("../pre/")
# sample = Cases("../down/")

for i in range(1, TASK_NUM + 1):
	log("Generating subtask {}".format(i))
	pre = testcase.cnt
	# pre_pre = precase.cnt
	# add testcases below
	for n in range(1, 7):
		testcase.gen(n, 10000, genUniform)
	for j in range(2):
		testcase.gen(6, 2013, genUniform, s_lbd = 1, s_rbd = 10, c = random.randint(5, 9))
	for s_lbd, s_rbd in ((1, 20), (101, 500), (1001, 10000)):
		for n in (1, random.randint(2, 5), 6):
			testcase.gen(n, random.randint(9900, 10000), genUniform, s_lbd = s_lbd, s_rbd = s_rbd)
	for j in range(2):
		testcase.gen(6, random.randint(500, 1000), genUniform)

	# Deterministic Result
	for j in (1, 6, random.randint(2, 5)):
		testcase.gen(j, random.randint(9900, 10000), genUniform, gen_p = genPDeterministic)
	for j in (6, random.randint(2, 5)):
		testcase.gen(j, random.randint(9900, 10000), genUniform, c = 100, gen_p = genPDeterministic)
	
	for c in (0, 50, 100):
		for j in range(2):
			testcase.gen(6, random.randint(9990, 10000), genCommonDivisor, c = c, s_lbd = 50, s_rbd = 1000)
		for j in range(2):
			testcase.gen(6, random.randint(9990, 10000), genCommonDivisor, c = c, s_lbd = 50, s_rbd = 1000, gen_p = genPDeterministic)
	
	for j in range(2):
		testcase.gen(6, random.randint(9990, 10000), genUnbalanced, c = random.randint(50, 100), s1_lbd = 20, s1_rbd = 100, s2_lbd = 1000)
	
	for j in range(2):
		testcase.gen(6, random.randint(9990, 10000), genLargeHead, c = random.randint(50, 100))
	for j in range(2):
		testcase.gen(6, random.randint(9990, 9999), genLargeHead, c = random.randint(50, 100), overflow = True)
	
	for j in range(2):
		testcase.gen(6, random.randint(9990, 10000), genLargeTail, c = 2, s_lbd = 3, s_rbd = 7, p0_lbd = 9000, pi_rbd = 2000)
	for j in range(2):
		testcase.gen(6, random.randint(9990, 10000), genLargeTail, c = 1, s_lbd = 3, s_rbd = 12, p0_lbd = 9000, pi_rbd = 2000, overflow = True)
	
	# add testcases above		
	log("Subtask {} done. ({} - {})".format(i, pre + 1, testcase.cnt))
	# log("Subtask {} done. (test: {} - {}; pre: {} - {})".format(i, pre + 1, testcase.cnt, pre_pre + 1, precase.cnt))

# for duck
# os.system("mkdir download")
# os.system("cp ../down/* ./download/")
