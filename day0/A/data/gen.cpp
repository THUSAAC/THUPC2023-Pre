#include<bits/stdc++.h>
using namespace std;

int CNT;
const int MAXN=200100;

int get_rand(){
	return (rand()<<16)|rand();
}
struct Edge_{
	int u,v;
	Edge_(){}
	Edge_(int uu,int vv){u=uu,v=vv;}
};
int id[MAXN];
Edge_ eg[MAXN];
int fa[MAXN];

void pre_(int n,int MAXW1,int MAXW2){
	memset(eg,0,sizeof(eg));
	std::string infile = std::to_string(++CNT)+".in";
    freopen(infile.c_str(),"w",stdout);
    printf("%d\n",n);
    for(int i=1;i<n;i++){
    	if(rand()%1000)printf("%d ",get_rand()%(MAXW1+1));
    	else printf("%d ",get_rand()%(MAXW2+1));
    }
    if(rand()%1000)printf("%d",get_rand()%(MAXW1+1));
    else printf("%d",get_rand()%(MAXW2+1));
    puts("");
}

void print(Edge_* eg,int n){
	memset(id,0,sizeof(id));
	memset(fa,0,sizeof(fa));
	for(int i=1;i<=n;i++)id[i]=i;
	random_shuffle(id+2,id+n+1);
	//random_shuffle(eg+1,eg+(n-1)+1);
	for(int i=1;i<=n-1;i++){
		fa[id[eg[i].v]]=id[eg[i].u];
	} 
	for(int i=2;i<=n-1;i++)printf("%d ",fa[i]);printf("%d",fa[n]); 
}

namespace work1{
	void gen1(int n,int MAXW1,int MAXW2){
		pre_(n,MAXW1,MAXW2);
	    for(int i=2;i<=n;i++){
	    	int fa=get_rand()%(i-1)+1;
	    	eg[i-1]=Edge_(fa,i);
	    }
	    print(eg,n); 
	}
}


namespace work2{
	void gen2(int n,int MAXW1,int MAXW2){
		pre_(n,MAXW1,MAXW2);
	    for(int i=2;i<=n;i++){
	    	int fa=get_rand()%min(i-1,10)+1;
	    	eg[i-1]=Edge_(fa,i);
	    }
	    print(eg,n);
	}
}

namespace work3{
	void gen3(int n,int MAXW1,int MAXW2){
		pre_(n,MAXW1,MAXW2);
	    int N=0.8*n;
	    for(int i=2;i<=N;i++){
	    	int fa=i-1;
	    	eg[i-1]=Edge_(fa,i);
	    }
	    for(int i=N+1;i<=n;i++){
	    	int fa=get_rand()%(i-1)+1;
	    	eg[i-1]=Edge_(fa,i);
	    }
	    print(eg,n);
	}
}

int main(){
	srand((unsigned)time(NULL));
	for(int i=1;i<=5;i++)work1::gen1(rand()%3+8,1,6);
	for(int i=6;i<=7;i++)work1::gen1(get_rand()%11+199990,3,20);
	for(int i=8;i<=9;i++)work1::gen1(get_rand()%11+199990,3,100);
	for(int i=10;i<=10;i++)work1::gen1(get_rand()%11+199990,200000,200000);
	for(int i=11;i<=11;i++)work2::gen2(rand()%3+30,2,20);
	for(int i=12;i<=12;i++)work2::gen2(get_rand()%11+199990,0,0);
	for(int i=13;i<=13;i++)work2::gen2(get_rand()%11+199990,1,1);
	for(int i=14;i<=14;i++)work2::gen2(get_rand()%11+199990,3,10);
	for(int i=15;i<=15;i++)work2::gen2(get_rand()%11+199990,200000,200000);
	for(int i=16;i<=16;i++)work3::gen3(rand()%3+20,2,20);
	for(int i=17;i<=20;i++)work3::gen3(get_rand()%11+199990,20,50000);
}
