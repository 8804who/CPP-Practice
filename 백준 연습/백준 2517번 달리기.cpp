#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> arr, temp, tree;
int N;

void change(int node, int left, int right, int idx)
{
    if (idx < left || idx > right) return;
    tree[node]++;
    if (left != right)
    {
        int mid = (left+right)/2;
        change(node*2,left, mid, idx);
        change(node*2+1, mid+1, right, idx);
    }
}

int query(int node, int start, int end, int left, int right)
{
    if (start > right || end < left) return 0;
    if (start <= left && end >= right) return tree[node];
    int mid = (left+right)/2;
    return query(node*2, start, end, left, mid) + query(node*2+1, start, end, mid+1, right);
}

int main()
{
    scanf("%d", &N);
    arr.resize(N);
    temp.resize(N);
    tree.resize(N*4);

    for (int i=0;i<N;i++) 
    {
        scanf("%d", &arr[i]);
        temp[i] = arr[i];
    }
    for (int i=0;i<N*4;i++) tree[i] = 0;

    sort(temp.begin(), temp.end());

    for (int i=0;i<N;i++)
    {
        arr[i] = lower_bound(temp.begin(), temp.end(), arr[i]) - temp.begin();
    }

    for (int i=0;i<N;i++)
    {
        change(1, 0, N-1, arr[i]);
        printf("%d\n", query(1, arr[i], N-1, 0, N-1));
    }
}