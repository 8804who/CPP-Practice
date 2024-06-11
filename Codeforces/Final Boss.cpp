#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    int t, h, n;
    long long turn;
    pair<long long, int> skill;
    cin >> t;

    
    for(int testcase=0;testcase<t;testcase++)
    {
        cin >> h >> n;
        
        priority_queue<pair<long long, int>> pq;
        int dmg[n];
        int cool[n];
        turn = 1;

        for(int i=0;i<n;i++) cin >> dmg[i];
        for(int i=0;i<n;i++) cin >> cool[i];
        
        for(int i=0;i<n;i++)
        {
            h -= dmg[i];
            pq.push(make_pair(-(cool[i]+1), i));
        }

        while(h>0)
        {
            turn=-pq.top().first;
            while(!pq.empty() && -pq.top().first==turn)
            {
                skill = pq.top();
                pq.pop();
                h -= dmg[skill.second];
                pq.push(make_pair(-(turn+cool[skill.second]), skill.second));
            }
        }
        cout << turn << endl;
    }  
}