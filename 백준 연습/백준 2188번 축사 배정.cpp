#include <iostream>
#include <vector>

using namespace std;

bool done[201];
int assign[201];
int N, M;
int ans = 0;

vector<int> vec[201];

bool match(int cow)
{
    for(int n : vec[cow])
    {
        if (done[n]) continue;
        done[n] = true;

        if (assign[n] == -1 || match(assign[n]))
        {
            assign[n] = cow;
            return true;
        }
    }
    return false;
}

int main()
{
    cin >> N >> M;

    for(int i=0;i<N;i++)
    {
        int n, num;
        cin >> n;

        for(int j=0;j<n;j++)
        {
            cin >> num;
            vec[i].push_back(num);
        }
    }

    for(int i=1;i<=M;i++) assign[i] = -1;

    for(int i=0;i<N;i++)
    {
        for(int j=1;j<=M;j++) done[j] = false;
        if (match(i)) ans++;
    }

    cout << ans;

    return 0;
}