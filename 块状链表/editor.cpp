/*
块状链表 就是链表里面的元素是一块一块数组。
插入时头插到满，尾一直往后合并到不能合并；删除时断点处一直向后合并到不能合并。
code source ： NOI 2003 Edior 
*/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<list>
#include<iterator>
#include<algorithm>

using namespace std;

const int Max_Len = 2 * 1025 * 1025 + 10;
const int Block_Size = 20000;

char order[10],str[Max_Len];

struct Block {
    int size; char data[Block_Size + 5];
    Block(int _size): size(_size) {data[1]='\0';};
};
typedef list<Block> :: iterator lit;

struct Block_List {
    
    int cursor;
    list<Block> List;
    
    void Reset() {
        List.clear();
        List.push_back(Block(0));
        cursor = 0;
    }
    
    void Get_Pos(lit &b, int &p) {
        for (b = List.begin(); b != List.end(); ++b)
            if (p > b->size) p -= b->size; else break;
    }
          
    void Fill_Block(lit b, int len, char *str) {
        memcpy(b->data + 1, str, len);
        b->size = len;
    }      
        
    void Splite(lit b, int p) {
        if (p == b->size) return;
        lit next = b; next++;
        List.insert(next, Block(0)); next--;
        Fill_Block(next, b->size - p, b->data + p + 1);
        b->size = p;
    }
    
    void Get(int n, char *str) {
        lit b; int p=cursor;
        Get_Pos(b, p);
        int len=min(b->size - p, n);
        memcpy(str, b->data + p + 1, len);
        for (b++; len + b->size <= n; len += b->size, ++b) 
            memcpy(str + len, b->data + 1, b->size);
        if(n - len) memcpy(str + len, b->data + 1, n - len);
        str[n] = '\0';
    }
    
    void Maintain(lit &b) {         
        lit next = b; next++;      
        while (next != List.end() && b->size + next->size <= Block_Size) { 
            memcpy(b->data + b->size + 1, next->data + 1, next->size);
            b->size += next->size;     
            next = List.erase(next);
        }
    }
    
    void Insert(int n, char *str) {
        lit b; int p=cursor;
        Get_Pos(b, p);       
        Splite(b, p);
        int len = 0;
        if (b != List.begin() && n >= Block_Size - b->size) {
            memcpy(b->data + b->size + 1, str, Block_Size - b->size);
            len = Block_Size - b->size;
            b->size = Block_Size;
        }
        for (; len + Block_Size <= n; len += Block_Size) {
            lit next = b; next++;            
            List.insert(next, Block(0)); next--;
            Fill_Block(next, Block_Size, str + len);
            b=next;
        }
        if (n - len) {
            lit next = b; next++; 
            List.insert(next, Block(0)); next--;
            Fill_Block(next, n - len, str + len);     
            Maintain(next);  
        }
    }
    
    void Erase(int n) {
        lit b; int p=cursor;
        Get_Pos(b, p); 
        Splite(b, p);  
        for (b++; n > b->size; b = List.erase(b)) {n -= b->size;}
        Splite(b, n);          
        b = List.erase(b); b--;
        if( b!= List.begin()) Maintain(b);
    }
    
}Array;

int main() {

    int T, n, k;char ctmp;
    scanf("%d", &T);
    Array.Reset();
    while (T--) {      
        scanf("%s", order);
        switch (order[0]) {
            case 'M': scanf("%d", &k); Array.cursor = k; break; 
            case 'N': Array.cursor++; break;
            case 'P': Array.cursor--; break;
            case 'G': scanf("%d", &n); 
                      Array.Get(n, str); 
                      printf("%s\n", str);
                      break;
            case 'D': scanf("%d", &n); Array.Erase(n); break;
            case 'I': scanf("%d%c", &n, &ctmp); 
                      for (int i = 0; i < n; ++i) {
                          str[i] = getchar();
                          if(str[i] < 32 || str[i] > 126) i--;
                      }                    
                      Array.Insert(n, str);
                      break;
        }   
    }

    return (0-0);

}
