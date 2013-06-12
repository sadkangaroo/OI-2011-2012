#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include<iterator>
#include<vector>
#include<list>
#include<deque>
#include<queue>
#include<stack>
#include<algorithm>
#include<map>
#include<set>
#include<complex>

using namespace std;

const int Max_Len=10005;

char c[Max_Len];
int cbuf;
int T,p;

struct node{
  char o;
  node *lc,*rc;
  node(){}
  node(char _o,node *_lc,node *_rc):o(_o){lc=_lc,rc=_rc;}
}*t1,*t2,buf[Max_Len],*root,*tmp;
stack<node*> stk;
deque<node*> deq;

void build(){
  p=0;
  while(!stk.empty()) stk.pop();
  while(c[p]!='\0'){
    if(c[p]>='A'&&c[p]<='Z'){
      t1=stk.top();stk.pop();
      t2=stk.top();stk.pop();
      cbuf++,stk.push(&(buf[cbuf]=node(c[p],t1,t2)));
    }
    else cbuf++,stk.push(&(buf[cbuf]=node(c[p],NULL,NULL)));
    p++;
  }
  root=stk.top();
}

void convert(){
  while(!deq.empty()) deq.pop_back();
  deq.push_back(root);
  p=0;
  while(!deq.empty()){
    tmp=deq.back();
    c[p]=tmp->o;p++;
    deq.pop_back();
    if(tmp->o>='A'&&tmp->o<='Z'){
      deq.push_front(tmp->rc);
      deq.push_front(tmp->lc);
    }
  }
  int mid=(p+1)/2-1;
  for(int i=0;i<=mid;++i) swap(c[i],c[p-1-i]);
  c[p]='\0';puts(c);
}

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  scanf("%d\n",&T);
  while(T--){
    cbuf=-1;
    gets(c);
    build();
    convert();
  }

  return 0;

}
