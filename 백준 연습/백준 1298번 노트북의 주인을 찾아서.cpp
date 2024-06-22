#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool done[101];
int assign[101];
vector<int> vec[101];

bool match(int n)
{
    for(int num : vec[n])
    {
        if (done[num]) continue;
        done[num] = true;
        if (assign[num] == -1 || match(assign[num]))
        {
            assign[num] = n;
            return true;
        }
    }
    return false;
}

int main()
{   
    int N, M, a, b, ans = 0;

    cin >> N >> M;

    for(int i=0;i<M;i++)
    {
        cin >> a >> b;
        vec[a].push_back(b);
    }

    for(int i=1;i<=N;i++) 
    {
        sort(vec[i].begin(), vec[i].end());
        assign[i] = -1;
    }

    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++) done[j] = false;
        if (match(i)) ans++;
    }

    cout << ans;

    return 0;
}