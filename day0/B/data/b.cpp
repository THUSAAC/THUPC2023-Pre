#include<bits/stdc++.h>
using namespace std;
#define li long long
#define gc getchar()
#define pc putchar
const li MAX_PER_UNIT = 100000000;
inline li ll_in(){
	li x = 0,y = 0,c = gc;
	while(!isdigit(c)) y = c,c = gc;
	while(c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ '0'),c = gc;
	return y == '-' ? -x : x;
}
inline void ll_out(li q){
	if(q < 0){
		pc('-');
		q = -q;
	} 
	if(q >= 10) ll_out(q / 10);
	pc(q % 10 + '0');
} 
struct gjd{
	vector<li> a;//存储高精度数据 
	int len;//该数据的位数 
	bool fh;//符号,0为非负1为负 
	gjd(){//初始化(清零)  
		len = fh = 0;a.clear();
	}
	inline gjd operator = (li x){
		a.clear();len = fh = 0;
		if(x < 0){
			fh = 1;x = -x;
		}
		while(x){
			a.push_back(x % MAX_PER_UNIT);
			x /= MAX_PER_UNIT;
		}
		len = a.size();
		return *this;
	}
	inline gjd operator = (int x){
		a.clear();len = fh = 0;
		if(x < 0){
			fh = 1;x = -x;
		}
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
			putchar('0');
			return;
		} 
		if(fh) putchar('-');
		ll_out(a[i - 1]);
		for(i -= 2;i >= 0;--i){
			if(a[i] < 10000000) pc('0');
			if(a[i] < 1000000) pc('0');
			if(a[i] < 100000) pc('0');
			if(a[i] < 10000) pc('0');
			if(a[i] < 1000) pc('0');
			if(a[i] < 100) pc('0');
			if(a[i] < 10) pc('0');
			ll_out(a[i]);
		} 
	}
};
inline ostream& operator << (ostream &os,gjd x){
	x.print();return os;
}

inline void clear(gjd &x){//初始化(清零) 
	x.a.clear();
	x.len = 0;
}
inline gjd turn(li x){//将低精转化为高精
	gjd y;
	if(x < 0){
		y.fh = 1;x = -x;
	}
	while(x){
		y.a.push_back(x % MAX_PER_UNIT); 
		x /= MAX_PER_UNIT;
	}
	y.len = y.a.size();
	return y;
} 
inline li turn(gjd z){//将高精转化为低精（有爆ll风险，慎用） 
	li x = 0;
	for(int i = z.len - 1;i >= 0;--i) x = x * MAX_PER_UNIT + z.a[i];
	return z.fh ? -x : x;
} 
inline void swap(gjd &x,gjd &y){//交换两个高精度数据 
	gjd t = x;
	x = y;
	y = t;
}
inline gjd abs(gjd x){//高精度数据取绝对值
	x.fh = 0;
	return x;
}
inline gjd operator - (gjd x){//相反数 
	if(x.len) x.fh ^= 1;
	return x;
}

inline int cmp(gjd x,gjd y){//高精与高精比较大小 
	if(x.fh && !y.fh) return -1;
	if(!x.fh && y.fh) return 1;
	int tmp = 1;
	if(x.fh && y.fh) tmp = -1;
	int q = x.len,w = y.len; 
	if(q > w) return tmp;
	if(w > q) return -tmp;
	for(--q;q >= 0;--q){
		if(x.a[q] > y.a[q]) return tmp;
		if(x.a[q] < y.a[q]) return -tmp;
	}
	return 0;
}
inline bool operator == (gjd b,gjd c){
	return cmp(b,c) == 0;
} 
inline bool operator < (gjd b,gjd c){
	return cmp(b,c) == -1;
}
inline bool operator > (gjd b,gjd c){
	return cmp(b,c) == 1;
}
inline bool operator <= (gjd b,gjd c){
	return cmp(b,c) != 1;
}
inline bool operator >= (gjd b,gjd c){
	return cmp(b,c) != -1;
}
inline bool operator != (gjd b,gjd c){
	return cmp(b,c) != 0;
}

inline int cmp(gjd x,li b){//高精与低精比较大小 
	return cmp(x,turn(b));
}
inline bool operator == (gjd b,li c){
	return cmp(b,c) == 0;
} 
inline bool operator < (gjd b,li c){
	return cmp(b,c) == -1;
}
inline bool operator > (gjd b,li c){
	return cmp(b,c) == 1;
}
inline bool operator <= (gjd b,li c){
	return cmp(b,c) != 1;
}
inline bool operator >= (gjd b,li c){
	return cmp(b,c) != -1;
}
inline bool operator != (gjd b,li c){
	return cmp(b,c) != 0;
}

inline int cmp(li b,gjd c){//低精与高精比较大小
	return cmp(turn(b),c);
}  
inline bool operator == (li b,gjd c){
	return cmp(b,c) == 0;
} 
inline bool operator < (li b,gjd c){
	return cmp(b,c) == -1;
}
inline bool operator > (li b,gjd c){
	return cmp(b,c) == 1;
}
inline bool operator <= (li b,gjd c){
	return cmp(b,c) != 1;
}
inline bool operator >= (li b,gjd c){
	return cmp(b,c) != -1;
}
inline bool operator != (li b,gjd c){
	return cmp(b,c) != 0;
}

inline gjd max(gjd x,gjd y){//高精与高精取最大值 
	return x > y ? x : y;
}
inline gjd max(gjd x,li y){//高精与低精取最大值 
	return x >= y ? x : turn(y);
}
inline gjd max(li x,gjd y){//低精与高精取最大值 
	return x > y ? turn(x) : y;
}
inline gjd min(gjd x,gjd y){//高精与高精取最小值 
	return x < y ? x : y;
}
inline gjd min(gjd x,li y){//高精与低精取最小值 
	return x <= y ? x : turn(y);
}
inline gjd min(li x,gjd y){//低精与高精取最小值 
	return x < y ? turn(x) : y;
}


inline gjd jia(gjd b,gjd c) {//高精加高精的绝对值相加,要求b,c>=0 
	if(c.len == 0) return b;
	if(b.len == 0) return c;
	int z = 0;
	gjd d;
	int l1 = b.len,l2 = c.len,t1,t2;
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
inline gjd jia(gjd b,li c){//高精加低精的绝对值相加,要求b,c>=0 
	if(c == 0) return b;
	if(b.len == 0) return turn(c);
	if(abs(c) > 9000000000000000000ll) return jia(b,turn(c));//不然会爆ll 
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

inline gjd jian(gjd z,li x){//高精减低精的绝对值相减，要求z>=x>=0 
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
inline gjd jian(gjd b,gjd c){//高精减高精的绝对值相减，要求b>=c>=0 
	if(c.len == 0) return b;
	int z = 0,w = -1;
	int l1 = b.len,l2 = c.len;
	gjd d;
	d.a.resize(b.len);
	int tp;
	while(z < l1){
		if(l2 > z) tp = c.a[z];
		else tp = 0;
		d.a[z] += b.a[z] - tp;
		if(d.a[z] < 0){
			d.a[z] += MAX_PER_UNIT;
			d.a[z + 1] = -1;
		}
		if(d.a[z]) w = z;
		++z;
	}
	d.len = w + 1;
	return d;
}

inline gjd operator + (gjd z,li x){//高精加低精 
	if(!z.fh && x >= 0) return jia(z,x);
	gjd a;
	if(z.fh && x < 0){
		z.fh = 0;x = -x;
		a = jia(z,x);
		a.fh = 1;
		return a;
	}
	if(!z.fh && x < 0){
		x = -x;
		if(z >= x){
			a = jian(z,x);
			a.fh = 0;
		}
		else{
			a = jian(turn(x),z);
			a.fh = 1;
		}
		return a;
	}
	if(z.fh && x >= 0){
		z.fh = 0;
		if(z > x){
			a = jian(z,x);
			a.fh = 1;
		}
		else{
			a = jian(turn(x),z);
			a.fh = 0;
		}
		return a;
	}
	return a;
}
inline gjd operator + (gjd z,gjd x){//高精加高精 
	if(!z.fh && !x.fh) return jia(z,x);
	if(z > x) swap(z,x);
	gjd a;
	if(z.fh && x.fh){
		z.fh = x.fh = 0;
		a = jia(z,x);
		a.fh = 1;
		return a;
	}
	if(z.fh && !x.fh){
		z.fh = 0;
		if(z > x){
			a = jian(z,x);
			a.fh = 1;
		}
		else{
			a = jian(x,z);
			a.fh = 0;
		}
		return a;
	}
	return a;
}
inline gjd operator + (li z,gjd x){//低精加高精 
	return x + z;
}
inline gjd operator += (gjd &z,li x){
	z = z + x;
	return z;
}
inline gjd operator += (gjd &z,gjd x){
	z = z + x;
	return z;
}
inline li operator += (li &z,gjd x){//请注意爆long long风险 
	z = z + turn(x);
	return z;
} 
inline gjd operator ++ (gjd &z){//由于特殊原因，使用时只能写作++z，不能写作z++ 
	z = z + 1;
	return z;
}

inline gjd operator - (gjd z,li x){//高精减低精 
	return z + (-x);
}
inline gjd operator - (gjd z,gjd x){//高精减高精 
	if(x.len) x.fh ^= 1;
	return z + x;
}
inline gjd operator - (li b,gjd c){//低精减高精
	return turn(b) - c; 
} 
inline gjd operator -= (gjd &z,li x){
	z = z - x;
	return z;
}
inline gjd operator -= (gjd &z,gjd x){
	z = z - x;
	return z;
}  
inline li operator -= (li &z,gjd x){//请注意爆long long风险 
	z = z - turn(x);
	return z;
} 
inline gjd operator -- (gjd &z){//由于特殊原因，使用时只能写作--z，不能写作z-- 
	z = z - 1;
	return z;
}

inline gjd operator * (gjd b,gjd c){//高精乘高精 
	if(b.len == 0 || c.len == 0) return turn(0);
	if(min(b.len,c.len) <= 200){
		gjd d;
		d.fh = b.fh ^ c.fh;
		b.fh = c.fh = 0;
		int i,j;
		int l1 = b.len,l2 = c.len;
		d.a.resize(l1 + l2 - 1);
		for(i = 0;i < l1;++i){
			for(j = 0;j < l2;++j){
				d.a[i + j] += b.a[i] * c.a[j];
			}
		}
		for(i = 0;i < l1 + l2 - 2;++i){
			d.a[i + 1] += d.a[i] / MAX_PER_UNIT;
			d.a[i] %= MAX_PER_UNIT;
		}
		while(d.a[i] >= MAX_PER_UNIT){
			if(d.a.size() == i + 1) d.a.push_back(d.a[i] / MAX_PER_UNIT);
			else d.a[i + 1] = d.a[i] / MAX_PER_UNIT;
			d.a[i] %= MAX_PER_UNIT;
			++i; 
		}
		d.len = i + 1;
		return d;
	}
	int l = max(b.len,c.len) / 2;
	gjd ans,b1,b2,c1,c2,s1,s2,s3,s4,s5;
	int tmp = b.fh ^ c.fh;
	b.fh = c.fh = 0;
	int i;
	b1.len = min(l,b.len);
	b1.a.resize(b1.len);
	for(i = 0;i < l && i < b.len;++i) b1.a[i] = b.a[i];
	c1.len = min(l,c.len);
	c1.a.resize(c1.len);
	for(i = 0;i < l && i < c.len;++i) c1.a[i] = c.a[i];
	if(b.len > l){
		b2.a.resize(b.len - 1);
		for(i = l;i < b.len;++i) b2.a[i - l] = b.a[i];
		b2.len = b.len - l;
	}
	if(c.len > l){
		c2.a.resize(c.len - 1);
		for(i = l;i < c.len;++i) c2.a[i - l] = c.a[i];
		c2.len = c.len - l;
	}
	while(b1.len && !b1.a[b1.len - 1]) --b1.len;
	while(c1.len && !c1.a[c1.len - 1]) --c1.len;
	while(b2.len && !b2.a[b2.len - 1]) --b2.len;
	while(c2.len && !c2.a[c2.len - 1]) --c2.len;
	s1 = b1 * c1;
	s2 = b2 * c2;
	s3 = (b1 + b2) * (c1 + c2) - s1 - s2;
	if(s2.len){
		s4.a.resize((l << 1) + s2.len);
		for(i = 0;i < s2.len;++i) s4.a[i + (l << 1)] = s2.a[i];
		s4.len = (l << 1) + s2.len; 
	}
	if(s3.len){
		s5.a.resize(l + s3.len);
		for(i = 0;i < s3.len;++i) s5.a[i + l] = s3.a[i];
		s5.len = l + s3.len;
	}
	ans = s1 + s4 + s5;ans.fh = tmp;
	return ans;
}
inline gjd operator * (gjd b,li c){//高精乘低精 
	if(b.len == 0 || c == 0) return turn(0);
	if(abs(c) > 10000000000ll) return b * turn(c);//不然会爆long long
	int l = b.len,i,j;
	j = b.fh ^ (c < 0);
	b.fh = 0;c = abs(c);
	for(i = 0;i < l;++i) b.a[i] *= c;
	for(i = 0;i < l - 1;++i){
		b.a[i + 1] += b.a[i] / MAX_PER_UNIT;
		b.a[i] %= MAX_PER_UNIT;
	}
	while(b.a[i] >= MAX_PER_UNIT){
		if(b.a.size() == i + 1) b.a.push_back(b.a[i] / MAX_PER_UNIT);
		else b.a[i + 1] = b.a[i] / MAX_PER_UNIT;
		b.a[i] %= MAX_PER_UNIT;
		++i;
	}
	b.len = i + 1;
	b.fh = j;
	return b;
}
inline gjd operator * (li z,gjd x){//低精乘高精 
	return x * z;
} 
inline gjd operator *= (gjd &z,li x){
	z = z * x;
	return z;
}
inline gjd operator *= (gjd &z,gjd x){
	z = z * x;
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
	q.fh = b.fh ^ (c < 0);
	b.fh = 0;c = abs(c);
	int l = b.len - 1;
	int x = 0,y;
	while(l){
		y = b.a[l] / c;
		if(!x && y){
			x = l;
			q.a.resize(x);
			q.a.push_back(y);
		} 
		if(x) q.a[l] = y;
		b.a[l - 1] += b.a[l] % c * MAX_PER_UNIT;
		--l;
	}
	if(!x){
		y = b.a[0] / c;
		ys = b.a[0] % c;
		if(!y) return q;
		q.a.push_back(y);
		q.len = x + 1;
		return q;
	}
	q.a[0] = b.a[0] / c;
	ys = b.a[0] % c;
	if(!q.a[0] && !x) q.len = 0;
	else q.len = x + 1;
	return q;
}

inline gjd spw(gjd q,li w){//高精度数据的单精度次幂运算，结果为高精度，要求指数是非负整数 
	if(w < 0){
		puts("error:in function 'spw(gjd q,long long int w)',w is negative!");
		exit(1);
	}
	if(!w) return turn(1);
	if(q == 0) return turn(0);
	if(q == 1) return turn(1);
	if(w == 1) return q;
	gjd z;
	z = spw(q,w >> 1);
	z = z * z;
	if(w & 1) z = z * q;
	return z;
}
inline gjd spw(li q,li w){//两个单精度数据的幂运算，结果为高精度，要求指数是非负整数  
	return spw(turn(q),w);
} 
inline gjd operator ^ (gjd q,li w){
	return spw(q,w);
}
inline gjd operator ^= (gjd &q,li w){
	q = q ^ w;
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
		x = 2; 
		(x ^ (n - 2)).print();
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
