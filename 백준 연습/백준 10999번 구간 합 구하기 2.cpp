#include <iostream>
#include <vector>

using namespace std;

vector<long long> arr, tree, lazy;

void updateLazy(int node, int start, int end)
{
    if (lazy[node] != 0){
        tree[node] += (end-start+1) * lazy[node];
        if (start != end) {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

long long query(int node, int start, int end, int left, int right)
{
    updateLazy(node, start, end);
    if (start > right || end < left) return 0;
    if (start >= left && end <= right) return tree[node];
    int mid = (start+end)/2;
    return query(node*2, start, mid, left, right) + query(node*2+1, mid+1, end, left, right);
}

void makeTree(int node, int start, int end)
{
    if (start == end) tree[node] = arr[start];
    else{
        int mid = (start+end)/2;
        makeTree(node*2,start,mid);
        makeTree(node*2+1,mid+1,end);
        tree[node] = tree[node*2]+tree[node*2+1];
    }
}

void updateRange(int node, int start, int end, int left, int right, long long diff)
{
    updateLazy(node, start, end);
    if (right < start || end < left) return;
    else if(left <= start && end <= right) {
        tree[node] += (end-start+1)*diff;
        if (start != end){
            lazy[node*2] += diff;
            lazy[node*2+1] += diff;
        }
    }
    else {
        int mid = (start+end)/2;
        updateRange(node*2, start, mid, left, right, diff);
        updateRange(node*2+1, mid+1, end, left, right, diff);
        tree[node] = tree[node*2]+tree[node*2+1];
    }
}

int main()
{
    long long N, M, K;
    scanf("%lld %lld %lld", &N, &M, &K);

    arr.resize(1000001);
    tree.resize(4000001);
    lazy.resize(4000001);
    
    for(int i=0;i<N;i++) scanf("%lld", &arr[i]);

    makeTree(1, 0, N-1);

    long long a, b, c, d;

    for(int i=0;i<M+K;i++)
    {
        scanf("%lld %lld %lld", &a, &b, &c);
        
        if (a == 1){
            scanf("%lld", &d);
            updateRange(1,0,N-1,b-1,c-1,d);
        }
        else{
            printf("%lld\n",query(1,0,N-1,b-1,c-1));
        }
    }
}