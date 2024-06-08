#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

int moves[8][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    bool visited[N][M];
    int arr[N][M];
    queue<pair<int, int>> q;

    for(int i=0;i<N;i++)
    {
        for (int j=0;j<M;j++) scanf("%d", &arr[i][j]);
    }

    for(int i=0;i<N;i++)
    {
        for (int j=0;j<M;j++) visited[i][j] = false;
    }

    int x, y, moved_x, moved_y;

    q.push(make_pair(0, 0));

    bool poss = false;

    while (!q.empty())
    {
        pair<int, int> now = q.front();
        y = now.first;
        x = now.second;
        q.pop();

        if (y == N-1 && x == M-1)
        {
            poss = true;
            break;
        }
        
        for (int i=0;i<4;i++)
        {   
            moved_y = y+moves[i][0];
            moved_x = x+moves[i][1];

            if (0<=moved_y && moved_y < N && 0<=moved_x && moved_x < M)
            {
                if (visited[moved_y][moved_x]) continue;
                visited[moved_y][moved_x] = true;
                if (arr[moved_y][moved_x] == 0) q.push(make_pair(moved_y, moved_x));
            }
        }
    }

    if (!poss) 
    {
        printf("0");
        return 0;
    }

    if (N == 1 || M == 1)
    {
        printf("1");
        return 0;
    }

    int u[N][M];
    int d[N][M];
    int l[N][M];
    int r[N][M];

    for (int i=0;i<N;i++)
    {
        for (int j=0;j<M;j++)
        {
            u[i][j] = 0;
            d[i][j] = 0;
            l[i][j] = 0;
            r[i][j] = 0;
        }
    }

    for(int i=0;i<N;i++)
    {
        for (int j=0;j<M;j++) visited[i][j] = false;
    }

    while (!q.empty()) q.pop();

    for(int i=0;i<M;i++)  if (arr[0][i] == 1) q.push(make_pair(0, i));

    while (!q.empty())
    {   
        pair<int, int> now = q.front();

        q.pop();
        y = now.first;
        x = now.second;

        for (int i=0;i<8;i++)
        {   
            moved_y = y+moves[i][0];
            moved_x = x+moves[i][1];
            if (0<=moved_y && moved_y < N && 0<=moved_x && moved_x < M)
            {
                if (visited[moved_y][moved_x]) continue;
                visited[moved_y][moved_x] = true;
                if (arr[moved_y][moved_x] == 1) q.push(make_pair(moved_y, moved_x));
                else u[moved_y][moved_x] = 1;
            }
        }
    }

    for(int i=0;i<N;i++)
    {
        for (int j=0;j<M;j++) visited[i][j] = false;
    }

    while (!q.empty()) q.pop();

    for(int i=0;i<M;i++)  if (arr[N-1][i] == 1) q.push(make_pair(N-1, i));

    while (!q.empty())
    {   
        pair<int, int> now = q.front();

        q.pop();
        y = now.first;
        x = now.second;

        for (int i=0;i<8;i++)
        {   
            moved_y = y+moves[i][0];
            moved_x = x+moves[i][1];
            if (0<=moved_y && moved_y < N && 0<=moved_x && moved_x < M)
            {
                if (visited[moved_y][moved_x]) continue;
                visited[moved_y][moved_x] = true;
                if (arr[moved_y][moved_x] == 1) q.push(make_pair(moved_y, moved_x));
                else d[moved_y][moved_x] = 1;
            }
        }
    }

    for(int i=0;i<N;i++)
    {
        for (int j=0;j<M;j++) visited[i][j] = false;
    }

    while (!q.empty()) q.pop();

    for(int i=0;i<N;i++)  if (arr[i][0] == 1) q.push(make_pair(i, 0));

    while (!q.empty())
    {   
        pair<int, int> now = q.front();

        q.pop();
        y = now.first;
        x = now.second;

        for (int i=0;i<8;i++)
        {   
            moved_y = y+moves[i][0];
            moved_x = x+moves[i][1];
            if (0<=moved_y && moved_y < N && 0<=moved_x && moved_x < M)
            {
                if (visited[moved_y][moved_x]) continue;
                visited[moved_y][moved_x] = true;
                if (arr[moved_y][moved_x] == 1) q.push(make_pair(moved_y, moved_x));
                else l[moved_y][moved_x] = 1;
            }
        }
    }

    for(int i=0;i<N;i++)
    {
        for (int j=0;j<M;j++) visited[i][j] = false;
    }

    while (!q.empty()) q.pop();

    for(int i=0;i<N;i++)  if (arr[i][M-1] == 1) q.push(make_pair(i, M-1));

    while (!q.empty())
    {   
        pair<int, int> now = q.front();

        q.pop();
        y = now.first;
        x = now.second;

        for (int i=0;i<8;i++)
        {   
            moved_y = y+moves[i][0];
            moved_x = x+moves[i][1];
            if (0<=moved_y && moved_y < N && 0<=moved_x && moved_x < M)
            {
                if (visited[moved_y][moved_x]) continue;
                visited[moved_y][moved_x] = true;
                if (arr[moved_y][moved_x] == 1) q.push(make_pair(moved_y, moved_x));
                else r[moved_y][moved_x] = 1;
            }
        }
    }

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<M;j++) 
        {
            if (i==0 && j==0) continue;
            if (i==N-1 && j==M-1) continue;
            if (u[i][j] == 1)
            {
                if (d[i][j] == 1 || l[i][j] == 1)
                {
                    printf("1");
                    return 0;
                }
                if (i==N-1 || j==0)
                {
                    printf("1");
                    return 0;
                }
            }
            if (d[i][j] == 1)
            {
                if (r[i][j] == 1)
                {
                    printf("1");
                    return 0;
                }
                if (i==0 || j==M-1)
                {
                    printf("1");
                    return 0;
                }
            }
            if (l[i][j] == 1)
            {
                if (r[i][j] == 1)
                {
                    printf("1");
                    return 0;
                }
                if (i==0 || j==M-1)
                {
                    printf("1");
                    return 0;
                }
            }
            if (r[i][j] == 1)
            {
                if (i==N-1 || j==0)
                {
                    printf("1");
                    return 0;
                }
            }
        }
    }
    printf("2");
    return 0;
}