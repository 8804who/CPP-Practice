#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<long long> arr, tree, tree2;
int N;

int init(int n, int start, int end){
    if (start == end) return tree[n] = start;
    int mid = (start+end)/2;
    int v1 = init(n*2, start, mid);
    int v2 = init(n*2+1, mid+1, end);
    return tree[n] = arr[v1] < arr[v2] ? v1 : v2;
}

int query(int n, int start, int end, int left, int right)
{
    if (end < left || start > right) return -1;
    if (start >= left && end <= right) return tree[n]; 

    int mid = (start+end)/2;
    int v1 = query(n*2, start, mid, left, right);
    int v2 = query(n*2+1, mid+1, end, left, right);

    if (v1 == -1) return v2;
    if (v2 == -1) return v1;
    return arr[v1] < arr[v2] ? v1 : v2;
}   

long long init2(int n, int start, int end){
    if (start == end) return tree2[n] = arr[start];
    int mid = (start+end)/2;
    return tree2[n] = init2(n*2, start, mid) + init2(n*2+1, mid+1, end);
}

long long query2(int n, int start, int end, int left, int right)
{
    if (end < left || start > right) return 0;
    if (start >= left && end <= right) return tree2[n]; 
    int mid = (start+end)/2;
    return query2(n*2, start, mid, left, right)+query2(n*2+1, mid+1, end, left, right);
}   


long long get_score(int left, int right)
{
    int min_idx = query(1, 0, N-1, left, right);
    long long sum = query2(1, 0, N-1, left, right);
    long long score = arr[min_idx]*sum;

    if (left < min_idx) score = max(score, get_score(left, min_idx-1));
    if (right > min_idx) score = max(score, get_score(min_idx+1, right));
    
    return score;
}

int main()
{
    scanf("%d", &N);
    arr.resize(N);
    tree.resize(N*4);
    tree2.resize(N*4);

    for (int i=0;i<N;i++) scanf("%d", &arr[i]);
    
    init(1,0,N-1);
    init2(1,0,N-1);
    printf("%lld", get_score(0, N-1));
    return 0;
}