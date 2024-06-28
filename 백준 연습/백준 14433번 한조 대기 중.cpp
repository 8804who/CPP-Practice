#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool done[301];
int assign1[301];
int assign2[301];
vector<int> team1[301];
vector<int> team2[301];

bool match1(int num)
{
    for(int n : team1[num])
    {
        if (done[n]) continue;
        done[n] = true;
        if (assign1[n] == -1 || match1(assign1[n]))
        {
            assign1[n] = num;
            return true;
        }
    }
    return false;
}

bool match2(int num)
{
    for(int n : team2[num])
    {
        if (done[n]) continue;
        done[n] = true;
        if (assign2[n] == -1 || match2(assign2[n]))
        {
            assign2[n] = num;
            return true;
        }
    }
    return false;
}

int main()
{   
    int N, M, K1, K2;
    cin >> N >> M >> K1 >> K2;

    for(int i=0;i<K1;i++)
    {
        int p, t;   
        cin >> p >> t;
        team1[p].push_back(t);
    } 

    for(int i=1;i<=N;i++) sort(team1[i].begin(), team1[i].end());

    for(int i=0;i<K2;i++)
    {
        int p, t;   
        cin >> p >> t;
        team2[p].push_back(t);
    } 

    for(int i=1;i<=N;i++) sort(team2[i].begin(), team2[i].end());


    for(int i=1;i<=M;i++) 
    {
        assign1[i] = -1;
        assign2[i] = -1;
    }

    int cnt1 = 0;
    int cnt2 = 0;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++) done[j] = false;
        if (match1(i)) cnt1++;
        for(int j=1;j<=M;j++) done[j] = false;
        if (match2(i)) cnt2++;
    }

    if (cnt1 < cnt2) cout << "네 다음 힐딱이";
    else cout << "그만 알아보자";

    return 0;
}