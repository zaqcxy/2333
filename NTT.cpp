
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
#define maxn 200000
#define mod 1004535809
#define ll long long
#define sss 3
//快速幂ntt ,sss为模意义下原根 
int quickpow(int a,int b,int c)
{
    int res=1;
    for(;b;b>>=1)
    {
        if(b&1) res=(1LL*res*a)%c;
        a=(1LL*a*a)%c;
    }
    return res;
}
int n,invn,nn,R[maxn],p,root,x,m;
void NTT(int *a,int f)
{
    int id=0;
    for(int i=1;i<nn;i++) if(i<R[i]) swap(a[i],a[R[i]]);
    for(int i=1;i<nn;i<<=1)
    {
        id++;
        int wn=quickpow(sss,f==1 ? (mod-1)/(1<<id) : mod-1-(mod-1)/(1<<id),mod);
        for(int j=0;j<nn;j+=(i<<1))
        {
            int w=1;
            for(int k=0;k<i;k++)
            {
                int x=a[j+k],y=(1LL*w*a[j+k+i])%mod;
                a[j+k]=(1LL*(x+y))%mod;
                a[j+k+i]=((1LL*(x-y))%mod+mod)%mod;
                w=(1LL*w*wn)%mod;
            }
        }
    }
    if(f==-1)
    {
        for(int i=0;i<nn;i++) a[i]=(1LL*a[i]*invn)%mod;
    }
}
int T[maxn],mm;
int aa[maxn],bb[maxn],cc[maxn],dd[maxn],pos[maxn];
inline bool judge(int x, int p)
{
    for (int i = 2; i * i <= p; i ++)
        if ((p - 1)%i==0&&quickpow(x,(p-1)/i,p)==1) return 0;
    return 1;
}
inline int Find_Root(int p)//求p的原根 
{
    if (p == 2) return 1;
    int res = 2;
    for (; !judge(res, p); res ++) ;
    return res;
}
int num[maxn];
void init()
{
    scanf("%d%d%d%d",&n,&p,&x,&m);
    for(int i=1;i<=m;i++)
        scanf("%d",&T[i]);
    mm=p*2-2;
    int l=0;
    for(nn=1;nn<=mm;nn<<=1)l++;
    for(int i=1;i<nn;i++)
        R[i]=(R[i>>1]>>1)|((i&1)<<(l-1));
    invn=quickpow(nn,mod-2,mod);
    root = Find_Root(p);
    for (int i=0;i<p-1;i++)
    {
        num[i]=!i ? 1 : num[i-1]*root%p;
        pos[num[i]] = i;
    }
}
void mul(int *ret,int *num1,int *num2)
{
    for (int i = 0; i < nn; i ++)
        cc[i] = num1[i],dd[i]=num2[i];
    NTT(cc,1);NTT(dd,1);
    for(int i=0;i<nn;i++)
    {
        ret[i]=(1LL*cc[i]*dd[i])%mod;
    }
    NTT(ret,-1);
    /*for (int i=nn-1;i>=p-1;i--)
    {
        ret[i-p+1]=1LL*(ret[i-p+1]+ret[i])%mod;
        ret[i] = 0;
    }*/
}
void quickpow2(int *a,int b)
{
    aa[0]=1;
    for(;b;b>>=1)
    {
        if(b&1)
        {
            mul(aa,a,aa);
        }
        mul(a,a,a);
    }
}
void solve()
{
    for (int i=1;i<=m;i++)
    {
        if(T[i] == 0) continue ;
        bb[pos[T[i]]]++;
    }
    quickpow2(bb,n);
    int ans=aa[pos[x]];
    printf("%d\n",ans);
}
int main()
{
    init();
    solve();
    return 0;

