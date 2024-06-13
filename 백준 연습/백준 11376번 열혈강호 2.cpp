#include <iostream>
#include <vector>

using namespace std;

bool done[1001];
int assign[1001];

int N, M;

vector<int> vec[1001];

bool match(int worker)
{
    for(int work : vec[worker])
    {
        if (done[work]) continue;
        done[work] = true;

        if (assign[work] == -1 || match(assign[work]))
        {
            assign[work] = worker;
            return true;
        }
    }
    return false;
}

int solution()
{
    int ans = 0;

    for(int i=0;i<N;i++)
    {
        for(int j=1;j<=M;j++) done[j] = false;
        if (match(i)) ans += 1;
    }
    return ans;
}

int main()
{
    cin >> N >> M;

    for(int i=0;i<N;i++)
    {
        int num, work;

        cin >> num;
        for(int j=0;j<num;j++)
        {
            cin >> work;
            vec[i].push_back(work);
        }
    }

    for(int i=1;i<=M;i++) assign[i] = -1;
    
    cout << solution()+solution();
}