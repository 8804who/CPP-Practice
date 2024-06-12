#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int V, E, node, next_node, idx;

bool finished[10001];
int parents[10001];

stack<int> st;
vector<vector<int>> ans;
vector<vector<int>> vec;

int dfs(int n)
{
    parents[n] = ++idx;
    st.push(n);

    int parent = parents[n];
    for(int nn : vec[n])
    {
        if (parents[nn] == -1) parent = min(parent, dfs(nn));
        else if(!finished[nn]) parent = min(parent, parents[nn]);
    }

    if(parent == parents[n])
    {
        vector<int> temp;
        while(true)
        {
            node = st.top();
            st.pop();
            finished[node] = true;
            temp.push_back(node);
            if(node==n) break;
        }
        sort(temp.begin(), temp.end());
        ans.push_back(temp);
    }
    return parent;
}

int main()
{
    cin >> V >> E;

    idx = 0;
    vec.resize(V+1);

    for(int i=0;i<E;i++)
    {
        cin >> node >> next_node;
        vec[node].push_back(next_node);
    }

    for(int i=1;i<=V;i++)
    {
        sort(vec[i].begin(), vec[i].end());
        finished[i] = false;
        parents[i] = -1;
    }

    for(int i=1;i<=V;i++)
    {
        if (!finished[i]) dfs(i);
    }

    sort(ans.begin(), ans.end());

    cout << ans.size() << endl;

    for(int i=0;i<ans.size();i++)
    {
        for(int j=0;j<ans[i].size();j++) cout << ans[i][j] << ' ';
        cout << -1 << endl;
    }
}