#include<bits/stdc++.h>
//#pragma gcc optimize(3)
#define gc getchar()
//char buf[100000],*buff = buf + 100000;
//#define gc ((buff == buf + 100000 ? (fread(buf,1,100000,stdin),buff = buf) : 0),*(buff++))
#define pc putchar
//char bfu[10000000],*bfuu = bfu;
//#define pc(x) (*(bfuu++) = x)
#define li long long
#define uli unsigned li
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define md int mid = l + r >> 1
#define ls q << 1
#define rs q << 1 | 1
#define ln ls,l,mid
#define rn rs,mid + 1,r
#define ldb long double
#define INF 1e18l
using namespace std;
//const int mo = 998244353;
//const int mo = 1000000007;
inline li read(){
	li x = 0;
	int y = 0,c = gc;
	while(c < '0' || c > '9') y = c,c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return y == '-' ? -x : x;
}
inline ldb read_ldb(){
	double x;scanf("%lf",&x);return (ldb)x;
}
inline void prt(li x){
	if(x >= 10) prt(x / 10);
	pc(x % 10 + '0');
}
inline void print(li x){
	if(x < 0) pc('-'),x = -x;
	prt(x);
}
inline void file(char *s){
	char c[50];
	sprintf(c,"%s.in",s);
	freopen(c,"r",stdin);
	sprintf(c,"%s.out",s);
	freopen(c,"w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m,t;

/**************************GEOMETRY BEGIN********************************/
namespace geometry{
#define EPS 1e-12l
	inline ldb my_acosl(ldb x){return acosl(max(-1.0l,min(1.0l,x)));}
	inline bool chkeq(ldb x,ldb y){return fabsl(x - y) < EPS;}
	struct vec2{
		ldb x,y;
		ldb dis()const {return sqrtl(x * x + y * y);} //长度
		ldb dis2()const {return x * x + y * y;} //长度的平方
		ldb dot(const vec2 &p)const {return x * p.x + y * p.y;}
		ldb cross(const vec2 &p)const {return x * p.y - y * p.x;}
		ldb dis_to_rectangle(ldb lx,ldb hy)const {return min(fabsl(x - lx),fabsl(x + lx)) + min(fabsl(y - hy),fabsl(y + hy));}
	};
	struct vec3{
		ldb x,y,z;
		vec3 to_int(){x = round(x);y = round(y);z = round(z);return *this;}
		ldb dis()const {return sqrtl(x * x + y * y + z * z);} 
		ldb dis2()const {return x * x + y * y + z * z;} 
		vec3 get_norm()const {ldb d = dis();return {x / d,y / d,z / d};}//获取向量单位化后的结果，但向量本身不单位化
		vec3 norm(){ldb d = dis();x /= d;y /= d;z /= d;return *this;}//获取向量单位化后的结果并将向量本身单位化
		ldb dot(const vec3 &p)const {return x * p.x + y * p.y + z * p.z;}
		vec3 cross(const vec3 &p)const {return {y * p.z - z * p.y,z * p.x - x * p.z,x * p.y - y * p.x};}
		ldb get_angle(const vec3 &p)const {return my_acosl(dot(p) / dis() / p.dis());}
		void input(){x = read_ldb();y = read_ldb();z = read_ldb();}	
	};
	vec3 operator + (const vec3 &a,const vec3 &b){return {a.x + b.x,a.y + b.y,a.z + b.z};}
	vec3 operator - (const vec3 &a,const vec3 &b){return {a.x - b.x,a.y - b.y,a.z - b.z};}
	vec3 operator * (ldb k,const vec3 &a){return {k * a.x,k * a.y,k * a.z};}
	bool operator == (const vec3 &a,const vec3 &b){return chkeq(a.x,b.x) && chkeq(a.y,b.y) && chkeq(a.z,b.z);}
	struct line{
		vec3 p,v;
		vec3 projection(const vec3 &x)const {return p + v.dot(x - p) * v;}
		ldb get_min_dis(const vec3 &x)const {return (x - projection(x)).dis();}
	};
	struct segment{
		vec3 p,q;
		ldb len()const {return (p - q).dis();} //长度
		ldb len2()const {return (p - q).dis2();} //长度的平方
		ldb get_min_dis(const vec3 &x)const {//求点到线段的最近距离
			if(p == q) return (x - p).dis();
			ldb tmp = (x - p).dot(q - p);
			if(tmp <= 0) return (x - p).dis();
			if(tmp >= len2()) return (x - q).dis();
			line y = {p,(q - p).norm()};
			return y.get_min_dis(x);
		}
	};
	struct plain{
		vec3 p,n;
		vec3 projection(const vec3 &x)const {return x - n.dot(x - p) * n;}
	};
};
using namespace geometry;
/**************************GEOMETRY END**********************************/

/**************************DEFINITION BEGIN******************************/
struct out_entry{
	int p1,p2,p3;
	vector<pair<int,vector<int> > >q1,q2,q3;
	void init(){
		q1.clear();q2.clear();q3.clear();
		p1 = p2 = p3 = 0;
	}
	void out_sort(){
		for(int i = 0;i < p1;++i) sort(q1[i].second.begin(),q1[i].second.end());
		sort(q1.begin(),q1.end());
		for(int i = 0;i < p2;++i) sort(q2[i].second.begin(),q2[i].second.end());
		sort(q2.begin(),q2.end());
		for(int i = 0;i < p3;++i){
			sort(q3[i].second.begin(),q3[i].second.end());
			q3[i].first = q3[i].second[0];
		}
		sort(q3.begin(),q3.end());
	}
	void output(){
		out_sort();
		print(p1);pc(' ');print(p2);pc(' ');print(p3);pc('\n');
		for(int i = 0;i < p1;++i){
			print(q1[i].first);pc(' ');print(q1[i].second.size());
			for(int j = 0;j < q1[i].second.size();++j) pc(' '),print(q1[i].second[j]);
			pc('\n');
		}
		for(int i = 0;i < p2;++i){
			print(q2[i].first);pc(' ');print(q2[i].second.size());
			for(int j = 0;j < q2[i].second.size();++j) pc(' '),print(q2[i].second[j]);
			pc('\n');
		}
		for(int i = 0;i < p3;++i){
			print(q3[i].second.size());
			for(int j = 0;j < q3[i].second.size();++j) pc(' '),print(q3[i].second[j]);
			pc('\n');
		}
		init();
	}
}out_en;
#define DEAD 0
#define ALIVE 1
#define INACTIVE 2
#define ACTIVE 3
#define HANDLING 4
struct plane{
	int id;
	int status;
	bool team;
	vec3 p,d,u,l;
	vec3 nxtp,nxtd,nxtu,nxtl;
	ldb tu,td,r,vm,lx,hy;
	int target;
	bool tar_in_radar;
	vector<int> exploded;
	void getl(){l = u.cross(d);}
	void input(int _id,bool _team){
		id = _id;
		team = _team;
		p.input();d.input();u.input();getl();
		tu = read_ldb();td = read_ldb();r = read_ldb();
		vm = read_ldb();lx = read_ldb();hy = read_ldb();
		status = ALIVE;
		target = 0;
		exploded.clear();
	}
	bool in_horizon(const plane &x)const {return d.dot(x.p - p) > EPS;}
	bool in_nxt_horizon(const plane &x)const {return nxtd.dot(x.p - nxtp) > EPS;}
	vec2 get_radar_r(const plane &x)const {//求x在自己的雷达平面上的投影
		plain pl = {p,d};
		vec3 nd = pl.projection(x.p);
		return {l.dot(nd - p),u.dot(nd - p)};
	}
	vec2 get_nxt_radar_r(const plane &x)const {//求移动后x在自己的雷达平面上的投影
		plain pl = {nxtp,nxtd};
		vec3 nd = pl.projection(x.p);
		return {nxtl.dot(nd - p),nxtu.dot(nd - p)};
	}
	bool in_radar_r(const vec2 &r)const {return fabsl(r.x) <= lx + EPS && fabsl(r.y) <= hy + EPS;}
	bool can_reach(const vec3 &x){//飞机能否飞行x距离（飞到p+x位置），能的话更新nxtp,nxtu,nxtd
		nxtp = p + x;
		nxtd = x.get_norm();
		if(d == nxtd) nxtl = l;//不需要滚转
		else if(d == -1 * nxtd) return 0;
		else{//需要滚转
			nxtl = d.cross(nxtd).norm();//要通过滚转把l转到与d和nxtd所在的平面垂直的方向
			if(l.dot(nxtl) < 0) nxtl = -1 * nxtl;//滚转只能在90度以内
		}
		nxtu = nxtd.cross(nxtl);
		return l.get_angle(nxtl) / r //滚转
			+ d.get_angle(nxtd) / (u.dot(nxtd) >= 0 ? tu : td) //俯仰
			+ x.dis() / vm <= 1 + EPS; //直线飞行
	}
}a[210]; 
struct missile{
	int id;
	int status;
	bool team;
	vec3 p,d;
	vec3 nxtp,nxtd;
	ldb tr,vm,ds,dp,bs;
	int tz,timer,target;
	void input(int _id,bool _team){
		id = _id;
		team = _team;
		tr = read_ldb();vm = read_ldb();ds = read_ldb();
		dp = read_ldb();bs = read_ldb();tz = read();
		status = DEAD;
		timer = target = 0;
	}
	void init(const vec3 &_p,const vec3 &_d,int _target){
		p = _p;d = _d;
		timer = 0;
		target = _target;
		status = INACTIVE;
	}
	bool nxt_can_lock(const plane &x,ldb &angle){//导弹即将飞到的位置能否锁定目标即将飞到的位置，能的话锁定角是多少（传给angle）
		if(x.nxtp == nxtp){//两者目标位置相同
			angle = 0;
			return 1;
		}
		ldb dott = nxtd.dot(x.nxtp - nxtp); 
		angle = nxtd.get_angle(x.nxtp - nxtp);//锁定角
		return dott > 0 && angle <= bs + EPS;//在前方且锁定角不超过最大锁定角
	}
	bool can_reach(const vec3 &x){//导弹能否飞行x距离（飞到p+x位置），能的话更新nxtp,nxtd
		nxtp = p + x;
		nxtd = x.get_norm();
		return d.get_angle(nxtd) / tr //偏航
			+ x.dis() / vm <= 1 + EPS; //直线飞行
	}
}b[210];
/**************************DEFINITION END*********************************/

/**************************STAGE 1 BEGIN**********************************/
void find_target(plane &x){//无人机选定目标
	if(x.status != ALIVE) return;
	int last_target = x.target;x.target = 0;x.tar_in_radar = 0;
	ldb min_dis = INF,min_dis_r = INF;
	for(int i = 1;i <= m;++i){
		plane &y = a[i];
		if(y.status != ALIVE || y.team == x.team || !x.in_horizon(y)) continue;
		vec2 r = x.get_radar_r(y);
		if(last_target == i){//先前的锁定目标，现在还能锁定 
			x.target = i;
			x.tar_in_radar = x.in_radar_r(r);
			return;
		}
		if(x.in_radar_r(r)){//在雷达范围内，优先选 
			ldb nw_dis = (x.p - y.p).dis2();
			if(nw_dis < min_dis - EPS){//取距离自己最近的 
				x.target = i;
				min_dis = nw_dis;
				x.tar_in_radar = 1;
			}
		}
		else{//不在雷达范围内 
			if(min_dis < INF) continue;
			ldb nw_dis = r.dis_to_rectangle(x.lx,x.hy);
			if(nw_dis < min_dis_r - EPS){//取距离雷达范围最近的 
				x.target = i;
				min_dis_r = nw_dis;
			}
		}
	}
}
void get_plane_fly_info(plane &x){//求出无人机的飞行策略
	if(x.status != ALIVE) return;
	if(x.target){//如果无人机有选定目标
		int vi = floor(x.vm);
		vec3 nxtp = {0,0,0},nxtd = {0,0,0},nxtu = {0,0,0};
		ldb min_tar_dis = INF,min_len_rq = INF,min_dis_radar = INF,min_straight_fly = INF;
		for(int i = -vi;i <= vi;++i){
			for(int j = -vi;j <= vi;++j){
				for(int k = -vi;k <= vi;++k){
					if(!i && !j && !k) continue;//不能原地不动
					if(i * i + j * j + k * k > x.vm * x.vm) continue;
					vec3 np = {(ldb)i,(ldb)j,(ldb)k};
					if(!x.can_reach(np)) continue;//必须要合法到达
					if(x.in_nxt_horizon(a[x.target])){//目标在视野内
						ldb ds = (x.p + np - a[x.target].p).dis2();//到目标的距离
						if(ds - EPS > min_tar_dis) continue;
						vec2 r = x.get_nxt_radar_r(a[x.target]);
						ldb tmp1 = INF,tmp2 = INF;
						if(x.in_radar_r(r)) tmp1 = r.dis();//在雷达范围内
						else tmp2 = r.dis_to_rectangle(x.lx,x.hy);//不在雷达范围内
						if((ds < min_tar_dis - EPS) //优先：距离最小
							|| (chkeq(ds,min_tar_dis) && tmp1 < min_len_rq - EPS) //其次：在雷达范围内且距视野中心尽可能近
							|| (chkeq(ds,min_tar_dis) && min_len_rq == INF && tmp2 < min_dis_radar - EPS)){ //再次：不在雷达范围内，距雷达范围尽可能近
							min_tar_dis = ds;
							min_len_rq = tmp1;
							min_dis_radar = tmp2;
							nxtp = x.nxtp;
							nxtd = x.nxtd;
							nxtu = x.nxtu;
						}
					}
					else{//目标不在视野内
						if(min_tar_dis < INF) continue;
						ldb ds = (np - x.vm * x.d).dis();
						if(ds < min_straight_fly - EPS){//找距离直飞最近的整点
							min_straight_fly = ds;
							nxtp = x.nxtp;
							nxtd = x.nxtd;
							nxtu = x.nxtu;
						}
					}
				}
			}
		}
		x.nxtp = nxtp;
		x.nxtd = nxtd;
		x.nxtu = nxtu;
	}
	else{//眼镜蛇机动
		x.nxtp = x.p;
		x.nxtd = x.u;
		x.nxtu = -1 * x.d;
	}
}
void stage1(){//所有无人机选定目标，并确定当前时刻内的飞行策略
	for(int i = 1;i <= m;++i) find_target(a[i]);
	for(int i = 1;i <= m;++i) get_plane_fly_info(a[i]);
}
/**************************STAGE 1 END************************************/

/**************************STAGE 2 BEGIN**********************************/
void launch_missile(plane &x){//发射导弹
	if(x.status != ALIVE || !x.tar_in_radar) return;
	if(b[x.id].status != DEAD) return;
	b[x.id].init(x.p,(a[x.target].p - x.p).norm(),x.target);
}
void stage2(){//所有能发射导弹的无人机发射导弹
	for(int i = 1;i <= m;++i) launch_missile(a[i]);
}
/**************************STAGE 2 END************************************/

/**************************STAGE 3 BEGIN**********************************/
bool chk_missile_explode(const vec3 &st,const vec3 &ed,const vec3 &tar,ldb dp){
	//从st飞到ed，距离tar的最近距离是否不超过dp
	if(st == ed) return (tar - st).dis2() <= dp * dp;
	segment seg = {st,ed};
	return seg.get_min_dis(tar) <= dp;
}
void get_missile_fly_info(missile &x){//求出导弹的飞行策略 
	if(x.status == DEAD) return;
	int vi = floor(x.vm);
	vec3 nxtp = {0,0,0},nxtd = {0,0,0};
	ldb min_tar_dis = INF,min_lock_angle = INF,min_straight_fly = INF;
	for(int i = -vi;i <= vi;++i){
		for(int j = -vi;j <= vi;++j){
			for(int k = -vi;k <= vi;++k){
				if(!i && !j && !k) continue;//不能原地不动
				if(i * i + j * j + k * k > x.vm * x.vm) continue;
				vec3 np = {(ldb)i,(ldb)j,(ldb)k};
				if(!x.can_reach(np)) continue;//必须要合法到达
				ldb tmp_angle = INF;
				
				if(x.target && x.nxt_can_lock(a[x.target],tmp_angle)){//有目标，且位移之后仍能锁定
					ldb ds = (x.p + np - a[x.target].nxtp).dis2();//到目标即将飞到的位置的距离
					if((ds < min_tar_dis - EPS) //优先：距离最小
						|| (chkeq(ds,min_tar_dis) && tmp_angle < min_lock_angle - EPS)){//其次：锁定角最小
						min_tar_dis = ds;
						min_lock_angle = tmp_angle;
						nxtp = x.nxtp;
						nxtd = x.nxtd;
					}
				}
				else{//没有目标，或位移之后脱锁
					if(min_tar_dis < INF) continue;
					ldb ds = (np - x.vm * x.d).dis();
					if(ds < min_straight_fly - EPS){//找距离直飞最近的整点
						min_straight_fly = ds;
						nxtp = x.nxtp;
						nxtd = x.nxtd;
					}
				}
			}
		}
	}
	if(min_tar_dis == INF) x.target = 0;//脱锁
	x.nxtp = nxtp;
	x.nxtd = nxtd;
}
void missile_fly(missile &x){//导弹飞行
	if(x.status == DEAD) return;
	for(int i = 1;i <= m;++i){
		plane &y = a[i];
		if(y.status == DEAD) continue;
		if(x.nxtp == y.p //导弹直接撞到飞机上，无论是否激活都摧毁 
			|| (x.status == ACTIVE && chk_missile_explode(x.p,x.nxtp,y.p,x.dp))){//判断激活的导弹x能否摧毁飞机y
			y.status = HANDLING;
			y.exploded.pb(x.id);
		}
	}
	x.p = x.nxtp;
	x.d = x.nxtd;
}
void stage3(){//所有导弹确定飞行策略并位移，该过程中部分无人机可能被摧毁；
	for(int i = 1;i <= m;++i) get_missile_fly_info(b[i]);
	for(int i = 1;i <= m;++i) missile_fly(b[i]);
}
/**************************STAGE 3 END************************************/

/**************************STAGE 4 BEGIN**********************************/
void crash(plane &x,bool flag){//飞机坠毁
	if(x.status != HANDLING) return;
	if(!flag){
		++out_en.p1;
		out_en.q1.pb(mp(x.id,x.exploded));
	}
	else{
		++out_en.p2;
		out_en.q2.pb(mp(x.id,x.exploded));
	}
	x.status = DEAD;
	for(int i = 0;i < x.exploded.size();++i) b[x.exploded[i]].status = DEAD;
	for(int i = 1;i <= m;++i){//瞄准它的导弹立刻脱锁 
		if(b[i].target == x.id) b[i].target = 0;
	} 
}
void stage4(){//所有可空爆的导弹爆炸并消失
	for(int i = 1;i <= m;++i) crash(a[i],0);
}
/**************************STAGE 4 END************************************/

/**************************STAGE 5 BEGIN**********************************/
void plane_fly(plane &x){//无人机飞行
	if(x.status == DEAD) return;
	for(int i = 1;i <= m;++i){//检查飞机能否被别的导弹摧毁 
		missile &y = b[i];
		if(y.status == DEAD) continue; 
		if(x.nxtp == y.p //导弹直接撞到飞机上，无论是否激活都摧毁  
			|| (y.status == ACTIVE && chk_missile_explode(x.p,x.nxtp,y.p,y.dp))){//判断激活的导弹y能否摧毁飞机x
			x.status = HANDLING;
			x.exploded.pb(i);
		}
	}
	x.p = x.nxtp;
	x.d = x.nxtd;
	x.u = x.nxtu;
	x.getl();
}
void stage5(){//所有无人机按 1. 中确定的飞行策略位移，该过程中部分无人机可能被摧毁；
	for(int i = 1;i <= m;++i) plane_fly(a[i]);
}
/**************************STAGE 5 END************************************/

/**************************STAGE 6 BEGIN**********************************/
void stage6(){//所有可空爆的导弹爆炸并消失
	for(int i = 1;i <= m;++i) crash(a[i],1);
}
/**************************STAGE 6 END************************************/

/**************************STAGE 7 BEGIN**********************************/
void chk_collide(plane &x){//碰撞检测
	if(x.status != ALIVE) return;
	bool flag = 0;
	vector<int> vt;vt.clear();
	for(int j = x.id + 1;j <= m;++j){
		plane &y = a[j];
		if(y.status != ALIVE) continue;
		if(y.p == x.p){
			x.status = y.status = DEAD;
			if(!flag){
				flag = 1;
				vt.pb(x.id);
				for(int k = 1;k <= m;++k){//瞄准它的导弹立刻脱锁 
					if(b[k].target == x.id) b[k].target = 0;
				} 
			}
			vt.pb(j);
			for(int k = 1;k <= m;++k){//瞄准它的导弹立刻脱锁 
				if(b[k].target == j) b[k].target = 0;
			} 
		}
	}
	if(flag){
		++out_en.p3;
		out_en.q3.pb(mp(x.id,vt));
	}
}
void stage7(){//所有位置相同的无人机发生碰撞并坠毁
	for(int i = 1;i <= m;++i) chk_collide(a[i]);
}
/**************************STAGE 7 END************************************/

/**************************STAGE 8 BEGIN**********************************/
void self_explosion(missile &x){//导弹自爆
	if(x.status == DEAD) return;
	if(x.timer++ == x.tz //超时 
		|| (!x.target && x.status == ACTIVE)) //脱锁并且已经激活 
			x.status = DEAD;
}
void stage8(){//所有超过制导时长和脱锁且已激活的导弹消失。
	for(int i = 1;i <= m;++i) self_explosion(b[i]);
}
/**************************STAGE 8 END************************************/

/**************************STAGE 9 BEGIN**********************************/
void activate(missile &x){//导弹激活
	if(x.status != INACTIVE) return;
	if(a[x.id].status == DEAD || (x.p - a[x.id].p).dis2() > x.ds * x.ds) x.status = ACTIVE;
}
void stage9(){//所有可激活的导弹被激活
	for(int i = 1;i <= m;++i) activate(b[i]);
}
/**************************STAGE 9 END************************************/

inline ldb no_neg0(ldb x) { return fabsl(x) > 1e-8 ? x : 0; }
inline char* Vec2str(const vec3 &p){
	char *s=new char[100];
	sprintf(s,"(%.6lf, %.6lf, %.6lf)",(double)no_neg0(p.x),(double)no_neg0(p.y),(double)no_neg0(p.z));
	return s;
}
void debug_out(int nw){
	FILE *f;
	if(nw == 0) f = fopen("log.txt","w");
	else f = fopen("log.txt","a+");
	fprintf(f,"T = %d\n",nw);
	for(int i = 1;i <= m;++i){
		plane &pl = a[i];
		fprintf(f,"\tplane %d:\n\t\talive = %s\n",i,pl.status == ALIVE ? "true" : "false");
		if(pl.status == ALIVE){
			fprintf(f,"\t\tp = %s\n\t\td = %s\n\t\tu = %s\n",Vec2str(pl.p),Vec2str(pl.d),Vec2str(pl.u));
			if(pl.target) fprintf(f,"\t\ttarget id = %d\n",pl.target);
		}
	}
	fprintf(f,"\n");
	for(int i = 1;i <= m;++i){
		missile &ms = b[i];
		fprintf(f,"\tmissile %d:\n\t\texist = %s\n",i,ms.status != DEAD ? "true" : "false");
		if(ms.status != DEAD){
			fprintf(f,"\t\tactive = %s\n",ms.status == ACTIVE ? "true" : "false");
			fprintf(f,"\t\tp = %s\n\t\td = %s\n",Vec2str(ms.p),Vec2str(ms.d));
			if(ms.target) fprintf(f,"\t\ttarget id = %d\n",ms.target);
		}
	}
	fprintf(f,"\n\n");
	fclose(f);
}

int main(){
	srand(time(0));rd();
	//file("");
//	freopen("i.out","w",stdout);
	int i;
	n = read();t = read();m = n + n;
	for(i = 1;i <= m;++i){
		a[i].input(i,i <= n);b[i].input(i,i <= n);
	}
	out_en.init();
	//debug_out(0);
	for(i = 1;i <= t;++i){
		stage1();
		stage2();
		stage3();
		stage4();
		stage5();
		stage6();
		stage7();
		stage8();
		stage9();
		out_en.output();
		//debug_out(i);
	}
	//fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}
