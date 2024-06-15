#include <iostream>
#include <map>
#include <vector>

using namespace std;

bool done[7501];
int parents[7501];
int son[2500];

int ans, idx, n;
long long a, b;
map<long long, int> m;
map<int, long long> m2;
vector<long long> v[2500];
vector<pair<int, int>> vec;

bool match(int num)
{
    for(int result : v[num])
    {
        if (done[result]) continue;
        done[result] = true;

        if (parents[result] == -1 || match(parents[result]))
        {
            parents[result] = num;
            return true;
        }
    }
    return false;
}

int main()
{
    cin >> n;
    ans = 0;
    idx = 0;

    for(int i=0;i<n;i++)
    {
        cin >> a >> b;
        vec.push_back(make_pair(a, b));
        if (m.find(a + b) == m.end()) 
        {
            m.insert({a+b, ++idx});
            m2.insert({idx, a+b});
        }
        if (m.find(a - b) == m.end())
        { 
            m.insert({a-b, ++idx});
            m2.insert({idx, a-b});
        }
        if (m.find(a * b) == m.end()) 
        {
            m.insert({a*b, ++idx});
            m2.insert({idx, a*b});
        }
        v[i].push_back(m[a + b]);
        v[i].push_back(m[a - b]);
        v[i].push_back(m[a * b]);
    }

    for(int i=1;i<=m.size();i++) parents[i] = -1;

    for(int i=0;i<n;i++)
    {
        for(int j=1;j<=m.size();j++) done[j] = false;
        if (match(i)) ans++;
    }

    for(int i=1;i<=m.size();i++)
    {
        if (parents[i] == -1) continue;
        son[parents[i]] = i;
    }

    if (ans<n) cout << "impossible";
    else
    {
        for(int i=0;i<n;i++)
        {
            a = vec[i].first;
            b = vec[i].second;
            long long result = m2[son[i]];

            if (a+b == result) cout << a << " + " << b << " = " << result << endl;
            else if (a-b == result) cout << a << " - " << b << " = " << result << endl;
            else cout << a << " * " << b << " = " << result << endl;
        }
    }

    return 0;
}