#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool done[2001];
int assign[2001];
vector<int> group;
vector<int> graph[2001];

bool match(int num)
{
    for(int n : graph[num])
    {
        if (done[n]) continue;
        done[n] = true;
        if (assign[n] == -1 || match(assign[n]))
        {
            assign[n] = num;
            return true;
        }
    }
    return false;
}

int main()
{   
    int n, m;
    cin >> n >> m;

    for(int i=0;i<n;i++)
    {
        int num;
        char major;
    
        cin >> num >> major;

        if (major == 'c') group.push_back(num);
    } 

    sort(group.begin(), group.end());

    for(int i=0;i<m;i++)
    {
        int n1, n2;
        cin >> n1 >> n2;

        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    for(int i=1;i<=n;i++) assign[i] = -1;
    
    int ans = n;

    for(int i : group)
    {
        for(int j=1;j<=n;j++) done[j] = false;
        if (match(i)) ans--;
    }

    cout << ans;

    return 0;
}