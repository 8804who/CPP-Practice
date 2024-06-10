#include <iostream>
#include <vector>

using namespace std;

vector<long long> tree, tree2;

void change(int node, int left, int right, int idx)
{
    if (idx < left || idx > right) return;
    tree[node]+=idx;
    if (left != right)
    {
        int mid = (left+right)/2;
        change(node*2,left, mid, idx);
        change(node*2+1, mid+1, right, idx);
    }
}

long long query(int node, int start, int end, int left, int right)
{
    if (start > right || end < left) return 0;
    if (start <= left && end >= right) return tree[node];
    int mid = (left+right)/2;
    return query(node*2, start, end, left, mid) + query(node*2+1, start, end, mid+1, right);
}

void change2(int node, int left, int right, int idx)
{
    if (idx < left || idx > right) return;
    tree2[node]++;
    if (left != right)
    {
        int mid = (left+right)/2;
        change2(node*2,left, mid, idx);
        change2(node*2+1, mid+1, right, idx);
    }
}

long long query2(int node, int start, int end, int left, int right)
{
    if (start > right || end < left) return 0;
    if (start <= left && end >= right) return tree2[node];
    int mid = (left+right)/2;
    return query2(node*2, start, end, left, mid) + query2(node*2+1, start, end, mid+1, right);
}

int main()
{
    int N, num;
    scanf("%d", &N);

    tree.resize(800001);
    tree2.resize(800001);
    
    for(int i=0;i<800001;i++)
    { 
        tree[i] = 0;
        tree2[i] = 0;
    }

    int div = 1000000007;
    long long ans = 1;
    long long n1, n2, n3, n4, total;

    scanf("%d", &num);
    change(1,0,200000,num);
    change2(1,0,200000,num);

    for(int i=1;i<N;i++)
    {
        scanf("%d", &num);
        n1 = query(1,0,num-1,0,200000);
        n2 = query2(1,0,num-1,0,200000);
        n3 = query(1,num+1,200000,0,200000);
        n4 = query2(1,num+1,200000,0,200000);
        
        total = (n2*num)-n1+n3-(n4*num);
        total %= div;
        ans *= total;
        ans %= div;    

        change(1,0,200000,num);
        change2(1,0,200000,num);
    }
    printf("%lld", ans);
}