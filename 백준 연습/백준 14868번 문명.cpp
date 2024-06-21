#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N, K, x, y, moved_x, moved_y, swan1, swan2;
int parents[2000][2000];
int world[2000][2000];
bool visited[2000][2000];

vector<pair<int, int>> civil;
queue<int> q;
queue<int> q2;

int moves[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int find(int A)
{
    if (parents[A/N][A%N] == A) return A;
    parents[A/N][A%N] = find(parents[A/N][A%N]);
    return parents[A/N][A%N];
}

void merge(int A, int B)
{
    A = find(A);
    B = find(B);
    if (A<B) parents[B/N][B%N] = A;
    else parents[A/N][A%N] = B;
}

void bfs()
{
    while(!q2.empty())
    {
        y = q2.front()/N;
        x = q2.front()%N;

        q.push(q2.front());
        q2.pop();

        world[y][x] = 1;
    } 

    while(!q.empty())
    {
        y = q.front()/N;
        x = q.front()%N;
        q.pop();

        if (visited[y][x]) continue;
        visited[y][x] = true;
            
        for(int m=0;m<4;m++)
        {
            moved_y = y+moves[m][0];
            moved_x = x+moves[m][1];

            if (0<=moved_y && moved_y<N && 0<=moved_x && moved_x<N)
            {
                if (world[moved_y][moved_x] == 0) 
                {
                    world[moved_y][moved_x] = 2;
                    q2.push(moved_y*N+moved_x);
                }
                if (world[moved_y][moved_x] == 1) merge(y*N+x, moved_y*N+moved_x);
            }
        }
    }
}

int main()
{
    int ans = 0;

    cin >> N >> K;

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++) 
        {
            world[i][j] = 0;
            parents[i][j] = i*N+j;
            visited[i][j] = false;
        }
    }
    
    for(int i=0;i<K;i++)
    {
        cin >> x >> y;
        x--;
        y--;
        world[y][x] = 1;
        civil.push_back(make_pair(y,x));
        for(int m=0;m<4;m++)
        {
            moved_y = y+moves[m][0];
            moved_x = x+moves[m][1];

            if (0<=moved_y && moved_y<N && 0<=moved_x && moved_x<N) if (world[moved_y][moved_x] == 1) merge(y*N+x, moved_y*N+moved_x);
            
        }
    }


    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if (world[i][j] == 0 || world[i][j] == 2 || visited[i][j]) continue;
            q.push(i*N+j);
            visited[i][j] = true;

            while(!q.empty())
            {
                y = q.front()/N;
                x = q.front()%N;
                q.pop();

                for(int m=0;m<4;m++)
                {
                    moved_y = y+moves[m][0];
                    moved_x = x+moves[m][1];

                    if (0<=moved_y && moved_y<N && 0<=moved_x && moved_x<N)
                    {
                        if (world[moved_y][moved_x] == 0) 
                        {
                            world[moved_y][moved_x] = 2;
                            q2.push(moved_y*N+moved_x);
                            continue;
                        }
                        if (world[moved_y][moved_x] == 2) continue;
                        merge(y*N+x, moved_y*N+moved_x);
                        if (visited[moved_y][moved_x]) continue;
                        visited[moved_y][moved_x] = true;
                        q.push(moved_y*N+moved_x);
                    }
                }
            }
        }
    }


    while(true)
    {
         bool united = true;
        int temp1, temp2;
        
        temp1 = find(civil[0].first*N+civil[0].second);

        for(int i=1;i<K;i++)
        {
            temp2 = find(civil[i].first*N+civil[i].second);
            if (temp1 != temp2) united = false;
        }

        if (united) break;
        
        bfs();
        ans++;
    }
    cout << ans;
    return 0;
}