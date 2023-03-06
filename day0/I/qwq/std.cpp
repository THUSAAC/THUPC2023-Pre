
#define LOG_INFO
//#define IND
#ifdef IND
#define ind if(1 && _ind)
#else
#define ind if(0)
#endif
const int _ind = 1;

#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
#define ull unsigned lint
#define db long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define gc getchar()
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<" "
#define ln <<endl
using namespace std;


typedef pair<int,int> pii;
typedef set<int>::iterator sit;
int T;const db eps=1e-9,pi=acos(-1.0),INF=1e9;const int N=1010;
inline db rad2deg(db x) { return x/pi*180; }
inline int inn() { int x;scanf("%d",&x);return x; }
inline db indb() { double x;scanf("%lf",&x);return x; }
inline int dcmp(db x) { return x<-eps?-1:(x>eps); }
inline int dcmp(db x,db y) { return dcmp(x-y); }
struct Vector{
	db x,y,z;Vector(db _x=0,db _y=0,db _z=0):x(_x),y(_y),z(_z) {}
	inline void rd() { x=indb(),y=indb(),z=indb(); }
	inline db len2()const { return x*x+y*y+z*z; }
	inline db len()const { return sqrt(len2()); }
	inline Vector operator+(const Vector &p)const { return Vector(x+p.x,y+p.y,z+p.z); }
	inline Vector operator-(const Vector &p)const { return Vector(x-p.x,y-p.y,z-p.z); }
	inline Vector operator-()const { return Vector(-x,-y,-z); }
	inline bool operator<(const Vector &p)const { return (dcmp(x,p.x)==0)?((dcmp(y,p.y)==0)?z<p.z:(y<p.y)):(x<p.x); }
	inline bool operator==(const Vector &p)const { return dcmp((*this-p).len())==0; }
	inline db dis(const Vector &p)const { return (p-*this).len(); }
	inline db dis2(const Vector &p)const { return (p-*this).len2(); }
	inline Vector& operator-=(const Vector &p) { return (*this)=(*this)-p; }
	inline Vector operator*(const db &d)const { return Vector(x*d,y*d,z*d); }
	inline Vector operator/(const db &d)const { return Vector(x/d,y/d,z/d); }
	inline Vector unit()const { return (*this)/len(); }
	inline Vector rotate(const Vector &u,db t)const;
	inline Vector decomposition(const Vector &a,const Vector &b,const Vector &c)const;
	inline db dis2segment(const Vector &B,const Vector &C)const;
	inline friend ostream& operator<<(ostream &os,Vector v) { os<<"("<<v.x<<", "<<v.y<<", "<<v.z<<")";return os; }
};
inline db dot(const Vector &p,const Vector &q) { return p.x*q.x+p.y*q.y+p.z*q.z; }
inline Vector cross(const Vector &p,const Vector &q) { return Vector(p.y*q.z-p.z*q.y,p.z*q.x-p.x*q.z,p.x*q.y-p.y*q.x); }
inline db ang(const Vector &p,const Vector &q) { db c=dot(p,q)/p.len()/q.len();return acosl(max(min(c,(db)1.0),-(db)1.0)); }
inline db len(const Vector &p) { return p.len(); }
inline db parallel(const Vector &p,const Vector &q) { return len(cross(p,q))<eps; }
Vector Vector::rotate(const Vector &u,db t)const
{
	const Vector &v=*this;
	return v * cosl(t) + cross(u,v) * sinl(t) + u * dot(u,v) * (1 - cosl(t));
}
/*
db mat[5][5];
inline int gauss(int n)
{
	rep(i,1,n)
	{
		int x=i;rep(j,i,n) if(fabsl(mat[j][i])>fabsl(mat[x][i])) x=j;
		if(i^x) rep(j,1,n+1) swap(mat[i][j],mat[x][j]);
		mat[i][n+1]/=mat[i][i];
		for(int j=n;j>=i;j--) mat[i][j]/=mat[i][i];
		rep(j,1,n) if(i^j)
			for(int k=n;k>=i;k--) mat[j][k]-=mat[j][i]*mat[i][k];
	}
	return 0;
}
*/
inline Vector Vector::decomposition(const Vector &a,const Vector &b,const Vector &c)const
{
	//return (x,y,z) such that xa+yb+cz=p,i.e. (a b c) (x,y,z) = (*this)
	return Vector(dot(*this,a.unit()),dot(*this,b.unit()),dot(*this,c.unit()));
/*	mat[1][1]=a.x,mat[1][2]=b.x,mat[1][3]=c.z,mat[1][4]=x;
	mat[2][1]=a.y,mat[2][2]=b.y,mat[2][3]=c.z,mat[2][4]=y;
	mat[3][1]=a.z,mat[3][2]=b.z,mat[3][3]=c.z,mat[3][4]=z;
	gauss(3);return Vector(mat[1][4],mat[2][4],mat[3][4]);*/
}
db Vector::dis2segment(const Vector &B,const Vector &C)const
{
	const Vector &A=*this;
	Vector BC=C-B,CB=B-C,BA=A-B,CA=A-C;
	if(dot(BA,BC)<0) return BA.len();
	if(dot(CA,CB)<0) return CA.len();
	return cross(BA,CA).len()/BC.len();
}
struct plane;struct missile;
struct MR{
	bool able;plane *pl;missile *ms;MR() { able=false,pl=NULL,ms=NULL; }
	inline friend ostream& operator<<(ostream &os,MR mr);
};
struct missile{
	Vector p,d;bool active,exist;
	db tr,Vm,ds,dp,bs;int tz,rest_time;
	plane *pl,*tar;missile *nxt;
	missile() { tar=NULL;nxt=NULL; }
	inline void rd() { rest_time=0,exist=false,active=false,tr=indb(),Vm=indb(),ds=indb(),dp=indb(),bs=indb(),tz=inn(); }
	inline MR move_check(const Vector &q)const
	{
		MR m;m.ms=new missile(*this);
		if(len(q-p)<0.1) return m;
		m.ms->p=q,m.ms->d=(q-p).unit();
		db t1=ang(d,m.ms->d)/tr,t2=len(q-p)/Vm;
		return m.able=(dcmp(t1+t2,1)<=0),m;
	}
	inline void move() { if(exist) (*this)=*nxt,rest_time--; }
	inline bool see(const Vector &q)const { return dcmp(dot(d,q-p))>0; }
	inline db lock_ang(const Vector &q) { return ang(d,q-p); }
	inline bool lock(const Vector &q)const { return see(q)&&ang(d,q-p)<=bs; }
	inline void bomb() { exist=false,active=false; }
	inline void make_active() { active=true; }
	inline vector<MR> getall_state();	
	inline missile calc_nxt();
	inline bool no_tar() { return check_tar(),tar==NULL; }
	inline void check_tar();
	inline bool check_active()const;
	inline bool TLE()const { return rest_time==0; }
	inline ostream& show()const;
};
inline ostream& operator<<(ostream &os,missile ms);
inline vector<Vector> getall_position(const Vector &p,db d)
{
	int n=int(d);// TODO: make it faster(prelude for each posible V_m)
	vector<Vector> ans;ans.clear();
	rep(i,-n,n) rep(j,-n,n) rep(k,-n,n)
		if(dcmp(Vector(i,j,k).len(),d)<=0) ans.pb(p+Vector(i,j,k));
	return ans;
}
struct plane{
	int id,grp_id;Vector p,d,u,l;
	db tu,td,r,Vm,Lx,Hy;bool alive;
	plane *tar,*nxt;missile *ms;
	plane() { tar=nxt=NULL,ms=new missile,ms->pl=this; }
	inline void rd() { p.rd(),d.rd(),u.rd(),l=cross(u,d),tu=indb(),td=indb(),r=indb(),Vm=indb(),Lx=indb(),Hy=indb(),ms->rd(); }
	inline void check_tar() { if(tar==NULL||!tar->alive||!see(tar->p)) tar=NULL; } inline bool no_tar() { check_tar();return tar==NULL; }
	inline MR move_check(Vector q)const
	{
//		int _ind=(id==8&&q==Vector(-8, -5, -4));
		if(len(q-p)<0.1) return MR();db dr,t1,ang1,ang2,t2,t3;
		MR m;m.pl=new plane(*this);m.pl->p=q,m.pl->d=(q-p).unit();
//		ind debug(p)sp,debug(q)sp,debug(d)sp,debug(u)sp,debug(m.pl->d)sp,debug(m.pl->u)ln;
//		ind debug(parallel(d,m.pl->d))ln;
		if(!parallel(d,m.pl->d))
		{
			m.pl->u=(m.pl->d-d*dot(d,m.pl->d)).unit(),dr=ang(u,m.pl->u);
			if(dr>pi/2) dr=pi-dr,m.pl->u=-m.pl->u;
		}
		else m.pl->u=u,dr=0;
//		debug(m.pl->u)sp,debug(rad2deg(dr))ln;
		t1=dr/r;
		m.pl->l=cross(m.pl->u,d);
		ang1=ang(d,m.pl->d),ang2=ang(m.pl->u,m.pl->d);
//		debug(rad2deg(ang1))ln;
		if(!dcmp(ang1+ang2,pi/2)) t2=ang1/tu;
		else t2=ang1/td;
		t3=len(q-p)/Vm,m.pl->u=cross(m.pl->d,m.pl->l);
//		ind debug(t1)sp,debug(t2)sp,debug(t3)ln;
		return m.able=(dcmp(t1+t2+t3,1)<=0),m;
	}
	inline void move() { (*this)=*nxt; }
	inline bool see(const Vector &q) { return dcmp(dot(d,q-p))>0; }
	inline bool lock(const Vector &q)
	{
		if(!see(q)) return false;
		Vector r=(q-p).decomposition(l,u,d);//pl.p-p=x*l+y*u+z*d
		return dcmp(fabsl(r.x),Lx)<=0&&dcmp(fabsl(r.y),Hy)<=0;
	}
	inline vector<MR> getall_state()const
	{
		vector<Vector> Vs=getall_position(p,Vm);
		vector<MR> mrs;mrs.clear();MR mr;
		Rep(i,Vs)
		{
//			int _ind=(id==2&&Vs[i]-p==Vector(-1,-11,-4));
			MR mr=move_check(Vs[i]);
			if(mr.able) mrs.pb(mr);
		}
		return mrs;
	}
	inline plane* get_target(plane *pls,int n)
	{
		check_tar();
		if(tar!=NULL) return tar;
		db dis2=INF;
		rep(i,1,n) if(pls[i].alive||pls[i].grp_id==grp_id) // 如果有一个在雷达范围内的，选距离最近的 
		{
			plane pl=pls[i];if(pl.grp_id==grp_id) continue;
			if(!lock(pl.p)) continue;
			db d=pl.p.dis2(p);
			int cmp=dcmp(d,dis2);
			if(cmp>0) continue;
			if(cmp<0||pl.id<tar->id) tar=pls+i,dis2=d;
		}
		if(tar!=NULL) return tar;
		db dis=INF;
		rep(i,1,n) if(pls[i].alive||pls[i].grp_id==grp_id)
		{
			plane pl=pls[i];if(pl.grp_id==grp_id) continue;
			if(!see(pl.p)||lock(pl.p)) continue;
			Vector r=(pl.p-p).decomposition(l,u,d);
#define calc_dis(r,L) min(fabsl(r-L),fabsl(r+L))
			db d=calc_dis(r.x,Lx)+calc_dis(r.y,Hy);
#undef calc_dis
			int cmp=dcmp(d,dis);
			if(cmp>0) continue;
			if(cmp<0||pl.id<tar->id) tar=pls+i,dis=d;
		}
		return tar;
	}
	inline plane calc_nxt()
	{
		check_tar();
		if(no_tar())
		{
			nxt=new plane(*this);
			nxt->d=u,nxt->u=-d;
			return *nxt;
		}
		else{
			vector<MR> mrs=getall_state();
			assert((int)mrs.size()>0);
			nxt=NULL;
			db dis0=INF,lenr0=INF,len0=INF;bool in0=0;
			Rep(i,mrs)
			{
				MR mr=mrs[i];Vector q=mr.pl->p;
//				int _ind=(id==8&&q-p==Vector(-8, -5, -4));
//				ind debug(mr.pl->see(tar->p))ln;
				if(!mr.pl->see(tar->p)) continue;
				db dis1=(q-tar->p).len();
				Vector r=(tar->p-q).decomposition(mr.pl->l,mr.pl->u,mr.pl->d);
				r.z=0;
				bool in1=(dcmp(fabsl(r.x),Lx)<=0&&dcmp(fabsl(r.y),Hy)<=0);
				db lenr1=r.len();
#define calc_dis(r,L) min(fabsl(r-L),fabsl(r+L))
				db len1=calc_dis(r.x,Lx)+calc_dis(r.y,Hy);
#undef calc_dis
				int cmp_dis=dcmp(dis1,dis0);
				if(cmp_dis>0) continue;
				else if(cmp_dis<0) in0=in1,dis0=dis1,len0=len1,lenr0=lenr1,nxt=mr.pl;
				else{
					if(in0)
					{
						if(!in1) continue;
						else{
							int cmp_lenr=dcmp(lenr1,lenr0);
							if(cmp_lenr>0) continue;
							else if(cmp_lenr<0||q<nxt->p) in0=in1,dis0=dis1,len0=len1,lenr0=lenr1,nxt=mr.pl;
						}
					}
					else{
						if(in1) in0=in1,dis0=dis1,len0=len1,lenr0=lenr1,nxt=mr.pl;
						else{
							int cmp_len=dcmp(len1,len0);
							if(cmp_len>0) continue;
							else if(cmp_len<0||q<nxt->p) in0=in1,dis0=dis1,len0=len1,lenr0=lenr1,nxt=mr.pl;
						}
					}
				}
			}
			if(nxt!=NULL) return *nxt;
			dis0=INF;
			Rep(i,mrs)
			{
				MR mr=mrs[i];Vector q=mr.pl->p;
				db dis1=(q-p-d*Vm).len();
				int cmp_dis=dcmp(dis1,dis0);
				if(cmp_dis>0) continue;
				else if(cmp_dis<0||q<nxt->p) dis0=dis1,nxt=mr.pl;
			}
			assert(nxt!=NULL);
			return *nxt;
		}
		assert(0);
	}
	inline int fire_missile()
	{
		if(ms->exist||no_tar()) return 0;
		if(!lock(tar->p)) return 0;
		ms->exist=true;
		ms->active=false;
		ms->p=p;
		ms->d=(tar->p-p).unit();
		ms->tar=tar;
		ms->rest_time=ms->tz+1;
		return 1;
	}
	inline void crash() { alive=false; }
	inline friend ostream& operator<<(ostream &os,plane pl)
	{
		os<<"{ id = "<<pl.id<<", p = "<<pl.p<<", d = "<<pl.d<<", u = "<<pl.u<<" }";
		return os;
	}
}pls[N];
inline ostream& operator<<(ostream &os,MR mr)
{
	if(mr.able)
	{
		os<<"{ able = true, ";
		if(mr.pl!=NULL) os<<"pl = "<<*mr.pl;
		else os<<"ms = "<<*mr.ms;
		os<<" }";
	}
	else os<<"{ able = false }";
	return os;
}
inline ostream& operator<<(ostream &os,missile ms)
{
	os<<"{ id = "<<ms.pl->id<<", active = "<<(ms.active?"True":"False")<<", p = "<<ms.p<<", d = "<<ms.d<<" }";
	return os;
}
inline ostream& missile::show()const
{
	debug(pl->id)sp;
	if(!exist)
	{
		cerr<<"exist = false"<<endl;
		return cerr;
	}
	else{
		cerr<<"exist = true, active = "<<(active?"true":"false")sp,debug(p)sp,debug(d)ln;
		debug(tr)sp,debug(Vm)sp,debug(dp)sp,debug(ds)sp,debug(bs)sp,debug(tz)sp,debug(rest_time)ln;
		if(tar!=NULL) debug(tar->id)ln;
		
	}
	return cerr;
}
inline void missile::check_tar() { if(tar==NULL||!tar->alive||!lock(tar->p)) { tar=NULL;return; } }
inline vector<MR> missile::getall_state()
{
	vector<Vector> Vs=getall_position(p,Vm);
	vector<MR> mrs;
	Rep(i,Vs)
	{
//		int _ind=(pl->id==4&&Vs[i]-p==Vector(-1,-11,-4));
		MR mr=move_check(Vs[i]);
//		if(_ind) debug(Vs[i])sp,debug(mr.able)ln;
		if(mr.able) mrs.pb(mr);
	}
	return mrs;
}
inline missile missile::calc_nxt()
{
	if(!exist) { return nxt=NULL,*this; }
	vector<MR> mrs=getall_state();
	assert((int)mrs.size()>0);
	nxt=NULL;
	if(!no_tar())
	{
		assert(tar->nxt!=NULL);
		plane nxt_pl=*tar->nxt;
		MR mr=move_check(nxt_pl.p);
		if(mr.able) return *(nxt=mr.ms);
		db dis0=INF,bs0=INF;
		Rep(i,mrs)
		{
			mr=mrs[i];Vector q=mr.ms->p;
			int _ind=(pl->id==8&&q-p==Vector(-8, -5, -4));
			if(!mr.ms->lock(nxt_pl.p)) continue;
//			if(_ind) debug("=========")ln;
			db dis1=(q-nxt_pl.p).len();
			db bs1=mr.ms->lock_ang(nxt_pl.p);
			if(_ind) printf("%.12lf\n",(double)bs1);
//			if(_ind) debug(dis1)sp,debug(bs1)ln;
			int cmp_dis=dcmp(dis1,dis0);
			if(cmp_dis>0) continue;
			else if(cmp_dis<0) dis0=dis1,bs0=bs1,nxt=mr.ms;
			else{
				int cmp_bs=dcmp(bs1,bs0);
				if(cmp_bs>0) continue;
				else if(cmp_bs<0||q<nxt->p) dis0=dis1,bs0=bs1,nxt=mr.ms;
			}
		}
		if(nxt!=NULL) return *nxt;
	}
	db dis0=INF;
	Rep(i,mrs)
	{
		MR mr=mrs[i];Vector q=mr.ms->p;
		db dis1=(q-p-d*Vm).len();
		int cmp_dis=dcmp(dis1,dis0);
		if(cmp_dis>0) continue;
		else if(cmp_dis<0||q<nxt->p) dis0=dis1,nxt=mr.ms;
	}
	assert(nxt!=NULL);
	nxt->check_tar();
	return *nxt;
}
inline bool missile::check_active()const { return exist&&!active&&(!pl->alive||pl->p.dis(p)>ds); }
Vector p[N],q[N];vector<int> ans1[N],ans2[N];vector<vector<int> > ans3;
inline void all_missile_move(plane *pls,int n,vector<int> *ans,int &cnt)
{
	rep(i,1,n) if(pls[i].ms->exist) p[i]=pls[i].ms->p,pls[i].ms->move(),q[i]=pls[i].ms->p;
	rep(i,1,n) ans[i].clear();
	rep(i,1,n) if(pls[i].ms->active) rep(j,1,n)
		if(pls[j].alive&&pls[j].p.dis2segment(p[i],q[i])<=pls[i].ms->dp)
			ans[j].pb(i),pls[i].ms->bomb();
	rep(i,1,n) if(pls[i].ms->exist&&!pls[i].ms->active)
		rep(j,1,n) if(pls[j].alive&&pls[j].p==pls[i].ms->p)
			ans[j].pb(i),pls[i].ms->bomb();
	rep(i,1,n) sort(ans[i].begin(),ans[i].end());
	cnt=0;rep(i,1,n) if(ans[i].size()) pls[i].crash(),cnt++;
}
inline void all_plane_move(plane *pls,int n,vector<int> *ans,int &cnt)
{
	rep(i,1,n) if(pls[i].alive) p[i]=pls[i].p,pls[i].move(),q[i]=pls[i].p;
	rep(i,1,n) ans[i].clear();
	rep(i,1,n) if(pls[i].ms->active) rep(j,1,n)
		if(pls[j].alive&&pls[i].ms->p.dis2segment(p[j],q[j])<=pls[i].ms->dp)
			ans[j].pb(i),pls[i].ms->bomb();
	rep(i,1,n) if(pls[i].ms->exist&&!pls[i].ms->active)
		rep(j,1,n) if(pls[j].alive&&pls[j].p==pls[i].ms->p)
			ans[j].pb(i),pls[i].ms->bomb();
	rep(i,1,n) sort(ans[i].begin(),ans[i].end());
	cnt=0;rep(i,1,n) if(ans[i].size()) pls[i].crash(),cnt++;
}
inline void collision_detection(plane *pls,int n,vector<vector<int> > &ans)
{
	ans.clear();vector<int> lst;
	rep(i,1,n) if(pls[i].alive)
	{
		lst.clear(),lst.pb(i);
		rep(j,i+1,n) if(pls[j].alive&&pls[i].p.dis(pls[j].p)<eps)
			lst.pb(j),pls[j].crash(),pls[i].crash();
		if((int)lst.size()>1) ans.pb(lst);
	}
}
inline void all_missile_check_exist(int n)
{
	rep(i,1,n) if(pls[i].ms->exist&&pls[i].ms->TLE()) pls[i].ms->bomb();
	rep(i,1,n) if(pls[i].ms->exist) pls[i].ms->check_tar();
	rep(i,1,n) if(pls[i].ms->active&&pls[i].ms->no_tar()) pls[i].ms->bomb();
}
inline void print_answer(vector<int> *ans1,int cnt1,vector<int> *ans2,int cnt2,vector<vector<int> > ans3,int n)
{
	printf("%d %d %d\n",cnt1,cnt2,(int)ans3.size());
	rep(i,1,n) if(ans1[i].size())
	{
		printf("%d %d",i,(int)ans1[i].size());
		Rep(j,ans1[i]) printf(" %d",ans1[i][j]);
		printf("\n");
	}
	rep(i,1,n) if(ans2[i].size())
	{
		printf("%d %d",i,(int)ans2[i].size());
		Rep(j,ans2[i]) printf(" %d",ans2[i][j]);
		printf("\n");
	}
	Rep(i,ans3)
	{
		vector<int> &lst=ans3[i];
		printf("%d",(int)lst.size());
		Rep(j,lst) printf(" %d",lst[j]);
		printf("\n");
	}
}

inline db no_neg0(db x) { return dcmp(x)?x:0; }
inline char* Vec2str(const Vector &p)
{
	char *s=new char[100];
	sprintf(s,"(%.6lf, %.6lf, %.6lf)",(double)no_neg0(p.x),(double)no_neg0(p.y),(double)no_neg0(p.z));
	return s;
}
inline void log_info(int n)
{
	static FILE *f=fopen("log.txt","w");
	fprintf(f,"T = %d\n",T);
	rep(i,1,n)
	{
		plane pl=pls[i];
		fprintf(f,"\tplane %d:\n\t\talive = %s\n",i,pls[i].alive?"true":"false");
		if(pls[i].alive)
		{
			fprintf(f,"\t\tp = %s\n\t\td = %s\n\t\tu = %s\n",Vec2str(pl.p),Vec2str(pl.d),Vec2str(pl.u));
			if(pl.tar!=NULL) fprintf(f,"\t\ttarget id = %d\n",pl.tar->id);
		}
	}
	fprintf(f,"\n");
	rep(i,1,n)
	{
		missile ms=*pls[i].ms;
		fprintf(f,"\tmissile %d:\n\t\texist = %s\n",i,ms.exist?"true":"false");
		if(pls[i].ms->exist)
		{
			fprintf(f,"\t\tactive = %s\n",ms.active?"true":"false");
			fprintf(f,"\t\tp = %s\n\t\td = %s\n",Vec2str(ms.p),Vec2str(ms.d));
			if(ms.tar!=NULL) fprintf(f,"\t\ttarget id = %d\n",ms.tar->id);
		}
	}
	fprintf(f,"\n\n");
}
int main()
{
//	freopen("data.in","r",stdin);
	int n=inn()*2,TC=inn(),cnt1,cnt2;
	rep(i,1,n) pls[i].id=i,pls[i].rd(),pls[i].alive=1,pls[i].grp_id=(i>(n/2));
#ifdef LOG_INFO
	T=0,log_info(n);
#endif
	for(T=1;T<=TC;T++)
	{
		ind cerr<<"------------------------------ Round "<<T<<" Start ------------------------------"<<endl;
		ind rep(i,1,n) if(pls[i].alive) 
		{
			debug(i)sp,debug(pls[i])ln;
			if(pls[i].ms->exist) debug(*pls[i].ms)ln;
		}
		ind cerr ln;
		
		rep(i,1,n) if(pls[i].alive) pls[i].get_target(pls,n);
		ind cerr<<"(1) After plane.get_target() :\n";
		ind rep(i,1,n) if(pls[i].alive&&pls[i].tar!=NULL) debug(i)sp,debug(pls[i].tar->id)ln;
		ind cerr ln;
		
		rep(i,1,n) if(pls[i].alive) pls[i].fire_missile();
		rep(i,1,n) if(pls[i].alive) pls[i].calc_nxt();
		ind cerr<<"(2) After plane.calc_nxt() :\n";
		ind rep(i,1,n) if(pls[i].alive&&pls[i].nxt!=NULL) debug(i)sp,debug(*pls[i].nxt)ln;
		ind cerr ln;
		
		rep(i,1,n) pls[i].ms->calc_nxt();
		ind cerr<<"(3) After missle.calc_nxt() :\n";
		ind rep(i,1,n) if(pls[i].ms->exist)
		{
			cerr<<"\t",debug(i)sp,debug(*pls[i].ms)ln;
			if(pls[i].ms->tar!=NULL) cerr<<"\t",debug(*pls[i].ms->tar)ln;
			if(pls[i].ms->nxt!=NULL) cerr<<"\t",debug(*pls[i].ms->nxt)ln;
			cerr ln;
		}
		ind cerr ln;
		
		all_missile_move(pls,n,ans1,cnt1);
		ind cerr<<"(4) After all_missile_move() :\n";
		ind rep(i,1,n) if(pls[i].ms->exist) debug(i)sp,debug(*pls[i].ms)ln;
		ind cerr ln;
		
		all_plane_move(pls,n,ans2,cnt2);
		ind cerr<<"(5) After all_plane_move() :\n";
		ind rep(i,1,n) if(pls[i].alive) debug(i)sp,debug(pls[i])ln;
		ind cerr ln;
		
		collision_detection(pls,n,ans3);
		ind cerr<<"(6) After collision planes crash :\n";
		ind rep(i,1,n) if(pls[i].alive) cerr<<"plane "<<i<<" still alive\n";
		ind cerr ln;
		
		all_missile_check_exist(n);
		ind cerr<<"(7) After All no_tar() or TLE() missiles bomb :\n";
		ind rep(i,1,n) if(pls[i].ms->exist) cerr<<"missile "<<i<<" exists"<<endl;
		ind cerr ln;
		
		rep(i,1,n) if(pls[i].ms->check_active()) pls[i].ms->make_active();
		ind cerr<<"(8) After missile.make_active() :\n";
		ind rep(i,1,n) if(pls[i].ms->active) cerr<<"missile "<<i<<" is active"<<endl;
		ind cerr ln;
		
		ind cerr<<"(9) print_answer() :\n";
		print_answer(ans1,cnt1,ans2,cnt2,ans3,n);
		ind cerr ln;
		ind cerr<<"------------------------------ Round "<<T<<" End -----------------------------"<<endl<<endl;
#ifdef LOG_INFO
		log_info(n);
#endif
	}
	return 0;
}
