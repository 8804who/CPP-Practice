#include <iostream>
#include <queue>

using namespace std;

int n;
int arr[100][100];
int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
bool visited[100][100];

bool bfs(int min_num, int max_num)
{
    queue<pair<int, int>> q;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) visited[i][j] = false;
    q.push(make_pair(0, 0));
    visited[0][0] = true;

    while(!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;

        q.pop();

        if (y == n-1 && x== n-1) return true;
    
        for(int m=0;m<4;m++)
        {
            int moved_y = y+moves[m][0];
            int moved_x = x+moves[m][1];
            if (n > moved_y && moved_y >= 0 && n > moved_x && moved_x >= 0)
            {
                if (visited[moved_y][moved_x]) continue;
                if (arr[moved_y][moved_x] > max_num || arr[moved_y][moved_x] < min_num) continue;
                visited[moved_y][moved_x] = true;
                q.push(make_pair(moved_y, moved_x));
            }
        }
    }
    return false;
}

int main()
{
    cin >> n;
    int ans = 200;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin >> arr[i][j];

    for(int i=0;i<=arr[0][0];i++)
    {
        int start = i;
        int end = 200;
        while(start<=end)
        {
            int mid = (start+end)/2;   

            if (mid >= arr[0][0] && bfs(i, mid))
            {
                ans = min(ans, mid-i);
                end = mid-1;
            }
            else start = mid+1;
        }
    }
    cout << ans;
    return 0;
}