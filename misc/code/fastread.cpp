#define getchar() (tt == ss && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
char In[1 << 20], *ss=In, *tt=In;
int read() {
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
    return x*f;
}
