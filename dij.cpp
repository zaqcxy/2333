#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N=10010;
const int M=100010;
const int INF=100000000;

int p[N],dis[N],n,m,S,T,numE;
int next[2*M],val[2*M],ed[2*M];

void AddE(int X,int Y,int Z)
{
    ed[++numE]=Y,val[numE]=Z,next[numE]=p[X],p[X]=numE;
}

int main()
{
    scanf("%d%d%d%d",&n,&m,&S,&T);
    int x,y,z;
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&x,&y,&z),AddE(x,y,z),AddE(y,x,z);
    pair<int,int> Heap[N+M];
    int top=0;
    for(int i=1;i<=n;i++)
        dis[i]=INF;
    dis[S]=0,Heap[++top]=make_pair(-dis[S],S),push_heap(Heap+1,Heap+top+1);
    while(top>0)
    {
        pair<int,int> Use=Heap[1];
        pop_heap(Heap+1,Heap+top+1),top--;
        if(dis[Use.second]!=-Use.first)
            continue;
        int X=Use.second;
        for(int e=p[X],Y,V;e;e=next[e])
            if(dis[ed[e]]>dis[X]+val[e])
                Y=ed[e],V=val[e],dis[Y]=dis[X]+V,
				Heap[++top]=make_pair(-dis[Y],Y),push_heap(Heap+1,Heap+top+1);
    }
    printf("%d\n",dis[T]);
    return 0;
}
