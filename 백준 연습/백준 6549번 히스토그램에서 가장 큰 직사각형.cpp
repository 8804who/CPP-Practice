#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> arr, tree;

int make_tree(int node, int left, int right)
{
    if (left == right) return tree[node] = left;
    int mid = (left+right)/2;
    int v1 = make_tree(node*2, left, mid);
    int v2 = make_tree(node*2+1,mid+1,right);
    return tree[node] = arr[v1] < arr[v2] ? v1:v2;
}

int query(int node, int start, int end, int left, int right)
{
    if (right < start || left > end) return -1;
    if (left >= start && right <= end) return tree[node];

    int mid = (left+right)/2;
    int v1 = query(node*2, start, end, left, mid);
    int v2 = query(node*2+1, start, end, mid+1, right);

    if (v1 == -1) return v2;
    if (v2 == -1) return v1;
    return arr[v1] < arr[v2] ? v1:v2;
}

long get_area(int start, int end)
{
    int min_idx = query(1, start, end, 0, N-1);
    long area = (long)arr[min_idx]*(long)(end-start+1);

    if (start < min_idx) area = max(area, get_area(start, min_idx-1));
    if (end > min_idx) area = max(area, get_area(min_idx+1, end));
    
    return area;
}

int main()
{
    while(true)
    {
        cin >> N;
        if (N == 0) break;
        arr.resize(N);
        tree.resize(N*4);

        for (int i=0;i<N;i++) cin >> arr[i];
    
        make_tree(1,0,N-1);
        cout << get_area(0, N-1) << endl;
    }    
    return 0;
}