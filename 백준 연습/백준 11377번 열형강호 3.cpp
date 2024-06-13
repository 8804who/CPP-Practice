#include <iostream>
#include <vector>

using namespace std;

int N, M, K;

bool done[1001];
int assign[1001];

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
        if (match(i)) ans++;
    }

    return ans;
}

int main()
{
    cin >> N >> M >> K;

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

    cout << solution()+min(K, solution());
}