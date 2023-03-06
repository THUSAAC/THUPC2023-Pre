import os
import datetime
import matplotlib.pyplot as plt

a = [863] * 399 + [1000] * 600
s = " ".join(map(str, a))

res = []

print(datetime.datetime.now())
for i in range(1, 1001):
	with open("test.in", "w") as f:
		f.write("1000 100000000\n")
		f.write(s)
		f.write(f" {i}\n")
	os.system("std < test.in > test.out")
	with open("test.out", "r") as f:
		out_pow8 = float(f.read())

	with open("test.in", "w") as f:
		f.write("1000 1000000000\n")
		f.write(s)
		f.write(f" {i}\n")
	os.system("std < test.in > test.out")
	with open("test.out", "r") as f:
		out_pow9 = float(f.read())
	
	res.append(abs(out_pow8 - out_pow9))
	if abs(out_pow8 - out_pow9) > 1e-5:
		print(i, out_pow8, out_pow9)

print(datetime.datetime.now())

plt.plot(range(1, 1001), res)
plt.show()