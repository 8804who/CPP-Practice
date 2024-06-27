#include <iostream>
#include <vector>

using namespace std;

int n, m;
int depths[30001];
int parents[30001][15];
vector<int> graph[30001];

void makeTree(int node, int depth);
void set_parent();
int get_dist(int node1, int node2);
int get_parent(int node1, int node2);

int main()
{
    cin >> n;

    for(int i=0;i<n-1;i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for(int i=1;i<=n;i++)
    {
        depths[i] = -1;
        for(int j=0;j<15;j++) parents[i][j] = 0;
    }

    makeTree(1, 1);
    set_parent();

    cin >> m;

    int prev = 1, ans = 0;

    for(int i=0;i<m;i++)
    {
        int a;
        cin >> a;

        int p = get_parent(prev, a);
        ans += get_dist(prev, p)+get_dist(a,p);
        prev = a;
    }
    cout << ans;
    return 0;
}

void makeTree(int node, int depth)
{
    depths[node] = depth;

    for(int next_node : graph[node])
    {
        if (depths[next_node] != -1) continue;
        parents[next_node][0] = node;
        makeTree(next_node, depth+1);
    }
}

void set_parent()
{
    for(int i=1;i<15;i++)
    {
        for(int j=1;j<=n;j++) parents[j][i] = parents[parents[j][i-1]][i-1];
    }
}

int get_dist(int node1, int node2)
{
    int n = 0;
    if (depths[node1] > depths[node2])
    {
        int temp = node1;
        node1 = node2;
        node2 = temp;
    }
    int i;
    for(i=14;i>-1;i--) 
    {    
        if (depths[node2] - depths[node1] >= (1 << i)) 
        { 
            node2 = parents[node2][i];
            n += 1 << i;
        }
    }

    if (node1 == node2) return n;

    for(i=14;i>-1;i--) 
    {
        if (parents[node1][i] != parents[node2][i])
        {
            node1 = parents[node1][i];
            node2 = parents[node2][i];
        }
        else if(parents[node1][i] != 0) break;
    }
    return n + (1 << i);
}

int get_parent(int node1, int node2)
{
    if (depths[node1] > depths[node2])
    {
        int temp = node1;
        node1 = node2;
        node2 = temp;
    }

    for(int i=14;i>-1;i--) 
    {    
        if (depths[node2] - depths[node1] >= (1 << i)) 
        { 
            node2 = parents[node2][i];
        }
    }

    if (node1 == node2) return node1;

    for(int i=14;i>-1;i--) 
    {
        if (parents[node1][i] != parents[node2][i])
        {
            node1 = parents[node1][i];
            node2 = parents[node2][i];
        }
    }
    return parents[node1][0];
}