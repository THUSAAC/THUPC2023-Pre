import sys
sys.set_int_max_str_digits(50000)
inp = input().split(' ')
n = int(inp[0])
k = int(inp[1])
if n <= k:
    print(1)
    exit()
if k == 2:
    print(2 ** (n - 2))
    exit()
x = 1
y = 0
flag = 1
while flag == 1:
    # print(x,y,n)
    u = x + y
    a = k // u
    b = k % u
    n -= a
    x -= b
    y += b
    if x <= 0:
        n -= 1
        x = -x
        y -= x + x
        (x,y) = (y,x)
        if (n > 0) & (x + y > 1000000):
            flag = 0
    if n <= 0:
        print(x + y)
        exit()
    else:
        x = x + 1
# print(x,y,n)
while n > 0: 
    t = x + (k - 3)
    z,ys = divmod(t,k - 1)
    # z = t // (k - 1)
    # ys = t % (k - 1)
    x += z + y
    y = k - 2 - ys
    if n > 1: 
        x -= y
    n -= 1 
print(x - 1)
