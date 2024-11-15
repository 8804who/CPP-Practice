#include <iostream>
#include <vector>

using namespace std;

vector<int> arr, tree, lazy;

void updateLazy(int node, int start, int end)
{
    if (lazy[node] != 0){
        tree[node] = (end-start+1)-tree[node];
        if (start != end) {
            lazy[node*2] = (lazy[node*2]+1)%2;
            lazy[node*2+1] = (lazy[node*2+1]+1)%2;
        }
        lazy[node] = 0;
    }
}

int query(int node, int start, int end, int left, int right)
{
    updateLazy(node, start, end);
    if (start > right || end < left) return 0;
    if (start >= left && end <= right) return tree[node];
    int mid = (start+end)/2;
    return query(node*2, start, mid, left, right) + query(node*2+1, mid+1, end, left, right);
}

void updateRange(int node, int start, int end, int left, int right)
{
    updateLazy(node, start, end);
    if (right < start || end < left) return;
    else if(left <= start && end <= right) {
        tree[node] = (end-start+1)-tree[node];
        if (start != end){
            lazy[node*2] = (lazy[node*2]+1)%2;
            lazy[node*2+1] = (lazy[node*2+1]+1)%2;
        }
    }
    else {
        int mid = (start+end)/2;
        updateRange(node*2, start, mid, left, right);
        updateRange(node*2+1, mid+1, end, left, right);
        tree[node] = tree[node*2]+tree[node*2+1];
    }
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    arr.resize(1000001);
    tree.resize(4000001);
    lazy.resize(4000001);

    int a, b, c;

    for(int i=0;i<1000000;i++) arr[i] = 0;
    for(int i=0;i<4000000;i++) tree[i] = 0;
    for(int i=0;i<4000000;i++) lazy[i] = 0;

    for(int i=0;i<M;i++)
    {
        scanf("%d %d %d", &a, &b, &c);
        
        if (a == 0){
            updateRange(1,0,N-1,b-1,c-1);
        }
        else{
            printf("%d\n",query(1,0,N-1,b-1,c-1));
        }
    }
}