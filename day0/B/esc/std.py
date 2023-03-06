n,k = map(int,input().split())
if n==k:
	print("1")
	quit()
if k==1:
	print("Poor E.S.!")
	quit()
if k==2:
	print(2**(n-2))
	quit()
now=k
x=1
y=0
while x+y+1<=k:
	q,r = divmod(k,x+y+1)
	if r<=x:
		now+=q
		x=x+1-r
		y+=r
	else:
		now+=q+1
		x,y=2*x+y+2-r,r-x-1
	if now>=n:
		print(x+y)
		quit()
while now<n:
	q,r = divmod(x,k-1)
	now+=1
	if r==0:
		x,y=y+q*k,0
	else:
		x,y=y+(q-1)*k+2*r+2,k-r-1
print(x+y)
