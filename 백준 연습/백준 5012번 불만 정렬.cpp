#include <iostream>

using namespace std;

int n;
int arr[100001];
int tree[400001];
long long tree2[400001];

int query(int node, int start, int end, int left, int right)
{
    if (end < left || start > right) return 0;
    if (start <= left && end >= right) return tree[node];
    int mid = (left+right)/2;
    return query(node*2, start, end, left, mid)+query(node*2+1, start, end, mid+1, right);
}

long long query2(int node, int start, int end, int left, int right)
{
    if (end < left || start > right) return 0;
    if (start <= left && end >= right) return tree2[node];
    int mid = (left+right)/2;
    return query2(node*2, start, end, left, mid)+query2(node*2+1, start, end, mid+1, right);
}

void change(int node, int idx, int left, int right)
{
    if (idx < left || idx > right) return;
    tree[node] += 1;
    if (left != right)
    {
        int mid = (left+right)/2;
        change(node*2, idx, left, mid);
        change(node*2+1, idx, mid+1, right);
    }
}

void change2(int node, int idx, long long diff, int left, int right)
{
    if (idx < left || idx > right) return;
    tree2[node] += diff;
    if (left != right)
    {
        int mid = (left+right)/2;
        change2(node*2, idx, diff, left, mid);
        change2(node*2+1, idx, diff, mid+1, right);
    }
}

int main()
{
    cin >> n;

    for(int i=1;i<=n;i++) cin >> arr[i];
    
    long long ans = 0;

    for(int i=n;i>0;i--)
    {
        change(1, arr[i], 0, 100000);
        change2(1, arr[i], query(1, 0, arr[i]-1, 0, 100000), 0, 100000);   
        ans += query2(1, 0, arr[i]-1, 0, 100000);
    }

    cout << ans;

    return 0;
}