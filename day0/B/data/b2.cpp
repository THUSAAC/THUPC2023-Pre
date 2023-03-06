#include<bits/stdc++.h>
using namespace std;
#define li unsigned long long
#define gc getchar()
#define pc putchar
const li MAX_PER_UNIT = 100000000000000ll;
inline li ll_in(){
	li x = 0,c = gc;
	while(!isdigit(c)) c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return x;
}
inline void ll_out(li q){
	if(q >= 10) ll_out(q / 10);
	pc(q % 10 + '0');
} 
struct gjd{
	vector<li> a;//存储高精度数据 
	int len;//该数据的位数 
	gjd(){//初始化(清零)  
		len = 0;a.clear();
	}
	inline gjd operator = (li x){
		a.clear();len = 0;
		while(x){
			a.push_back(x % MAX_PER_UNIT);
			x /= MAX_PER_UNIT;
		}
		len = a.size();
		return *this;
	}
	inline gjd operator = (int x){
		a.clear();len = 0;
		while(x){
			a.push_back(x % MAX_PER_UNIT);
			x /= MAX_PER_UNIT;
		}
		len = a.size();
		return *this;
	}
	inline void print(){//输出 
		int i = len;
		if(i == 0){
			pc('0');
			return;
		} 
		ll_out(a[i - 1]);
		for(i -= 2;i >= 0;--i){
			li x = MAX_PER_UNIT;
			while(x > 10){
				x /= 10;
				if(a[i] < x) pc('0');
			}
			ll_out(a[i]);
		} 
	}
	
};

inline void clear(gjd &x){//初始化(清零) 
	x.a.clear();
	x.len = 0;
}
inline gjd turn(li x){//将低精转化为高精
	gjd y;
	while(x){
		y.a.push_back(x % MAX_PER_UNIT); 
		x /= MAX_PER_UNIT;
	}
	y.len = y.a.size();
	return y;
} 

inline gjd operator + (gjd b,gjd c){//高精加高精的绝对值相加,要求b,c>=0 
	if(c.len == 0) return b;
	if(b.len == 0) return c;
	int z = 0;
	gjd d;
	int l1 = b.len,l2 = c.len;
	li t1,t2;
	d.a.resize(max(l1,l2) + 1);
	while(z < l1 || z < l2){
		if(l1 > z) t1 = b.a[z];
		else t1 = 0;
		if(l2 > z) t2 = c.a[z];
		else t2 = 0;
		d.a[z] += t1 + t2;
		if(d.a[z] >= MAX_PER_UNIT) d.a[z + 1] = 1,d.a[z] -= MAX_PER_UNIT;
		++z;
	}
	d.len = d.a.size();
	while(d.len && !d.a[d.len - 1]) --d.len;
	return d;
}
inline gjd operator + (gjd b,li c){//高精加低精的绝对值相加,要求b,c>=0 
	if(c == 0) return b;
	if(b.len == 0) return turn(c);
	int z = 0;
	b.a[0] += c;
	while(b.a[z] >= MAX_PER_UNIT){
		if(b.a.size() == z + 1) b.a.push_back(b.a[z] / MAX_PER_UNIT);
		else b.a[z + 1] += b.a[z] / MAX_PER_UNIT;
		b.a[z] %= MAX_PER_UNIT;
		++z;
	}
	b.len = max(b.len,z + 1);
	return b;
}

inline gjd operator - (gjd z,li x){//高精减低精的绝对值相减，要求z>=x>=0 
	if(x == 0) return z;
	int q = 0,w = -1;
	z.a[0] -= x;
	while(z.a[q] < 0){
		z.a[q + 1] += z.a[q] / MAX_PER_UNIT;
		z.a[q] %= MAX_PER_UNIT;
		if(z.a[q] < 0){
			z.a[q] += MAX_PER_UNIT;
			--z.a[q + 1];	
		}
		if(z.a[q]) w = q;
		++q;
	}
	if(z.len == q + 1 && z.a[q] == 0) z.len = w + 1;
	return z;
}

li ys = 0;
inline gjd operator / (gjd b,li c){//高精除以低精 
	if(!c){
		puts("error:divided by zero!");
		exit(1);
	}
	if(b.len == 0) return turn(0);
	gjd q;
	int l = b.len - 1,x = 0;
	li y;
	while(l >= 0){
		y = b.a[l] / c;
		if(!x && y){
			x = l + 1;
			q.a.resize(x);
		} 
		if(x) q.a[l] = y;
		if(l){
			b.a[l - 1] += b.a[l] % c * MAX_PER_UNIT;
			--l;
		}
		else break;
	}
	ys = b.a[0] % c;
	q.len = x;
	return q;
}

int n,k;
int main(){	
	int i,j,l;
	n = ll_in();k = ll_in();
	if(n <= k){
		puts("1");return 0;
	}
	if(k == 1){
		puts("Poor E.S.!");return 0;
	}
	if(k == 2){
		gjd x;
		x = 1; 
		int d = clock();
		for(i = 1;i <= n - 2;++i){
			x = x + x;
			//x.print();pc('\n');
		} 
		cerr<<clock() - d<<endl; 
		x.print();
		pc('\n');
		return 0;
	}
	gjd x,z,w;
	int m = n,xx = 1,yy = 0,y;
	while(1){
		//cerr<<xx + yy<<":"<<xx<<" "<<yy<<" "<<m<<endl;
		int u = xx + yy;
		int a = k / u,b = k % u;
		m -= a;xx -= b;yy += b;
		if(xx <= 0){
			--m;
			xx = -xx;yy -= xx + xx;
			swap(xx,yy);
			if(m > 0 && xx + yy > 1000000){
				++xx;
				break;
			}
		}
		if(m <= 0){
			ll_out(xx + yy);
			pc('\n');
			return 0;
		}
		else ++xx;
	}
	x = xx;y = yy;
	int d = clock();
	while(m){ 
		//make sure x > 1
		//if(x == 1) z = 1; 
		z = (x + (k - 3)) / (k - 1);
		x = x + z + y;
		y = k - 2 - ys;
		if(m > 1) x = x - y;
		--m; 
	}
	cerr<<clock() - d<<endl; 
	(x - 1).print();pc('\n');
	return 0;
}
