import random
import os
import datetime
import numpy as np

TASK_NUM = 1

A_LBD = 1
A_RBD = 2000
N_LIMIT = 2000
L_LIMIT = 1000000000

def log(string):
	print(string, flush = True)
	with open("gen.log", "a") as f:
		f.write("[{}] {}\n".format(datetime.datetime.now(), string))

def genAUniform(n, lbd = A_LBD, rbd = A_RBD, **extra_param):
	rng = np.random.default_rng()
	return rng.integers(lbd, rbd + 1, size = n)

def genAShuffle(n, lbd = A_LBD, rbd = A_RBD, **extra_param):
	rng = np.random.default_rng()
	return rng.permutation(np.arange(lbd, rbd + 1))[:n]

def genACliff(n, lbd = A_LBD, rbd = A_RBD // 10, top_prob = 0.8, **extra_param):
	rng = np.random.default_rng()
	candidates = list(range(lbd, rbd + 1)) + [random.randint(A_RBD - 20, A_RBD)]
	prob = [(1 - top_prob) / (rbd - lbd + 1)] * (rbd - lbd + 1) + [top_prob]
	return rng.choice(candidates, size = n, p = prob)

def gcd(a, b):
	c = a % b
	while c != 0:
		a = b
		b = c
		c = a % b
	return b

def genAMultiples(n, lbd = 100, rbd = 500, prob_double = 0.75, top_lbd = 1990, top_prob_lbd = 0.7, top_prob_rbd = 0.9, **extra_param):
	rng = np.random.default_rng()
	while True:
		x = random.randint(lbd, rbd)
		y = random.randint(top_lbd, A_RBD)
		if gcd(x, y) == 1:
			break
	candidates = [x, 2 * x if random.random() < prob_double else 3 * x, y]
	py = random.uniform(top_prob_lbd, top_prob_rbd)
	prob = [(1 - py) / 2, (1 - py) / 2, py]
	return rng.choice(candidates, size = n, p = prob)

def genAArithmetic(n, dlbd = 50, drbd = 400, prob_double = 0.75, top_lbd = 1990, top_prob_lbd = 0.7, top_prob_rbd = 0.9, **extra_param):
	rng = np.random.default_rng()
	while True:
		d = random.randint(dlbd, drbd)
		y = random.randint(top_lbd, A_RBD)
		if gcd(d, y) == 1:
			break
	candidates = [(y - 2 * d) if random.random() < prob_double else (y - 3 * d), y - d, y]
	py = random.uniform(top_prob_lbd, top_prob_rbd)
	prob = [(1 - py) / 2, (1 - py) / 2, py]
	return rng.choice(candidates, size = n, p = prob)

def genLSmaller(n, a, **extra_param):
	return random.randint(max(1, min(max(a) // 2, max(a) - 10)), max(a) - 1)

def genLExact(n, a, **extra_param):
	return max(a)

def genLWithinTwice(n, a, **extra_param):
	return random.randint(max(a) + 1, max(2 * max(a) - 5, max(a) + 1))

def genLNearLimit(n, a, lbd = int(L_LIMIT * 0.9), **extra_param):
	return random.randint(lbd, L_LIMIT)

def genLModerate(n, a, lbd = int(L_LIMIT * 0.08), rbd = int(L_LIMIT * 0.25), **extra_param):
	return random.randint(lbd, rbd)

def genLUniform(n, a, lbd = A_RBD * 5, rbd = int(L_LIMIT * 0.01), **extra_param):
	return random.randint(lbd, rbd)

def genTestcase(filename, n, l, a, gen_l, gen_a, **extra_param):
	log(f"Generating input for case {filename}, params: {n = } {l = } ({gen_l.__name__ if gen_l is not None else '-'}) {a = } ({gen_a.__name__ if gen_a is not None else '-'}) {extra_param = }")
	# assert ..., "Parameters invalid!"
	if a is None:
		a = gen_a(n, **extra_param)
	if l is None:
		l = gen_l(n, a, **extra_param)
	
	assert n == len(a) and 1 <= n <= N_LIMIT
	assert 1 <= l <= L_LIMIT
	for x in a:
		assert A_LBD <= x <= A_RBD

	with open("{}.in".format(filename), "w") as f:
		print(n, l, file = f)
		print(*a, file = f)
	log("Generating output for case {}".format(filename))
	os.system('(time ../ScarletStorm/std < {}.in > {}.ans) 2>> gen.log'.format(filename, filename))

class Cases:
	def __init__(self, prefix = ""):
		self.cnt = 0
		self.prefix = prefix
	
	def gen(self, n, l = None, a = None, gen_l = None, gen_a = None, **extra_param):
		self.cnt += 1
		genTestcase("{}{}".format(self.prefix, self.cnt), n, l, a, gen_l, gen_a, **extra_param)
	
	def skip(self, cnt = 1):
		self.cnt += cnt

os.system("rm gen.log")
testcase = Cases()
# precase = Cases("../pre/")
sample = Cases("../down/")

for i in range(1, TASK_NUM + 1):
	log("Generating subtask {}".format(i))
	pre = testcase.cnt
	# pre_pre = precase.cnt
	# add testcases below
	
	# Basic Case & Corner Cases
	testcase.gen(14, 1000000000, gen_a = genAUniform)
	testcase.gen(14, gen_l = genLExact, gen_a = genAUniform)
	testcase.gen(14, gen_l = genLSmaller, gen_a = genAUniform)
	testcase.gen(14, gen_l = genLWithinTwice, gen_a = genAUniform)
	testcase.gen(14, gen_l = genLModerate, gen_a = genAUniform)
	testcase.gen(2000, 999999999, gen_a = genAUniform)
	testcase.gen(2000, 999999999, gen_a = genAUniform)
	testcase.gen(2000, 999999999, gen_a = genAShuffle)
	testcase.gen(100, 10000000, gen_a = genAShuffle)
	testcase.gen(50, gen_l = genLUniform, gen_a = genAUniform)

	for genL in (genLExact, genLSmaller, genLWithinTwice, genLUniform, genLModerate, genLModerate, genLNearLimit, genLNearLimit):
		testcase.gen(random.randint(1990, 2000), gen_l = genL, gen_a = genACliff)
	
	for genA in (genAMultiples, genAArithmetic):
		for genL in (genLExact, genLSmaller, genLWithinTwice, genLUniform):
			testcase.gen(random.randint(1990, 2000), gen_l = genL, gen_a = genA)
		for genL in (genLModerate, genLNearLimit):
			for prob in (0, 1, 0.75, 0.75):
				testcase.gen(random.randint(1990, 2000), gen_l = genL, gen_a = genA, prob_double = prob)
	
	# add testcases above		
	log("Subtask {} done. ({} - {})".format(i, pre + 1, testcase.cnt))
	# log("Subtask {} done. (test: {} - {}; pre: {} - {})".format(i, pre + 1, testcase.cnt, pre_pre + 1, precase.cnt))

sample.gen(2, 4, [1, 2])
sample.gen(4, 1999, [8, 8, 12, 22])
sample.gen(13, 31416, [3, 14, 15, 92, 65, 35, 89, 79, 32, 38, 46, 26, 433])

# for duck
# os.system("mkdir download")
# os.system("cp ../down/* ./download/")
