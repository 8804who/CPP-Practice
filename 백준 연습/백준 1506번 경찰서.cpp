#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int N, idx;

bool finished[101];
int cost[101];
int parents[101];

stack<int> st;
vector<int> vec[101];
vector<vector<int>> SCC;

int dfs(int n)
{
    parents[n] = ++idx;
    st.push(n);
    
    int parent = parents[n];

    for(int city : vec[n])
    {
        if (parents[city] == -1) parent = min(parent, dfs(city));
        else if(!finished[city]) parent = min(parent, parents[city]);
    }

    if (parent == parents[n])
    {
        vector<int> scc;

        while(!st.empty())
        {
            int temp = st.top();
            st.pop();
            finished[temp] = true;
            scc.push_back(temp);
            if (temp==n) break;
        }
        SCC.push_back(scc);
    }
    return parent;
}

int main()
{
    cin >> N;

    idx = 0;

    for(int i=1;i<=N;i++) cin >> cost[i];

    for(int i=1;i<=N;i++)
    {
        string n;
        cin >> n;
        for(int j=1;j<=N;j++) if (n[j-1]=='1') vec[i].push_back(j);
    }

    for(int i=1;i<=N;i++)
    {
        sort(vec[i].begin(), vec[i].end());
        finished[i] = false;
        parents[i] = -1;
    }

    for(int i=1;i<=N;i++) if (!finished[i]) dfs(i);

    int min, ans;
    ans = 0;

    for(int i=0;i<SCC.size();i++)
    {   
        min = 1e9;
        for(int city : SCC[i]) if (min>cost[city]) min = cost[city];
        ans += min;
    }

    cout << ans;

    return 0;
}