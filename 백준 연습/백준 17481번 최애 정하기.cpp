#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

bool done[1001];
int assign[1001];

int N, M, ans, idx, num;
string name;
map<string, int> m;

vector<int> v[1001];

bool match(int num)
{
    for(int result : v[num])
    {
        if (done[result]) continue;
        done[result] = true;

        if (assign[result] == -1 || match(assign[result]))
        {
            assign[result] = num;
            return true;
        }
    }
    return false;
}

int main()
{
    cin >> N >> M;
    ans = 0;
    idx = 0;

    for(int i=0;i<M;i++)
    {
        cin >> name;
        if (m.find(name) == m.end()) m.insert({name, ++idx});
    }

    for(int i=1;i<=N;i++)
    {
        cin >> num;
        for(int j=0;j<num;j++) 
        {
            cin >> name;
            v[i].push_back(m[name]);
        }
    }

    for(int i=1;i<=M;i++) assign[i] = -1;

    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=m.size();j++) done[j] = false;
        if (match(i)) ans++;
    }

    if (ans == N) cout << "YES";
    else cout << "NO\n" << ans;    

    return 0;
}