#include <iostream>
#include <queue>

using namespace std;

int R, C, x, y, moved_x, moved_y, swan1, swan2;
int parents[1500][1500];
bool visited[1500][1500];
char lake[1500][1500];

queue<int> q;
queue<int> q2;

int moves[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int find(int A)
{
    if (parents[A/C][A%C] == A) return A;
    parents[A/C][A%C] = find(parents[A/C][A%C]);
    return parents[A/C][A%C];
}

void merge(int A, int B)
{
    A = find(A);
    B = find(B);
    if (A<B) parents[B/C][B%C] = A;
    else parents[A/C][A%C] = B;
}

void bfs()
{
    while(!q2.empty())
    {
        y = q2.front()/C;
        x = q2.front()%C;

        q.push(q2.front());
        q2.pop();

        lake[y][x] = '.';
    } 

    while(!q.empty())
    {
        y = q.front()/C;
        x = q.front()%C;
        q.pop();

        if (visited[y][x]) continue;
        visited[y][x] = true;
            
        for(int m=0;m<4;m++)
        {
            moved_y = y+moves[m][0];
            moved_x = x+moves[m][1];

            if (0<=moved_y && moved_y<R && 0<=moved_x && moved_x<C)
            {
                if (lake[moved_y][moved_x] == 'X') 
                {
                    lake[moved_y][moved_x] == '-';
                    q2.push(moved_y*C+moved_x);
                }
                if (lake[moved_y][moved_x] == '.') merge(y*C+x, moved_y*C+moved_x);
            }
        }
    }
}

int main()
{
    int ans = 0;

    cin >> R >> C;
    swan1 = -1;

    for(int i=0;i<R;i++)
    {
        for(int j=0;j<C;j++) 
        {
            cin >> lake[i][j];
            parents[i][j] = i*C+j;
            visited[i][j] = false;
            if (lake[i][j] == 'L')
            {
                if (swan1 == -1) swan1 = i*C+j;
                else swan2 = i*C+j;
                lake[i][j] = '.';
            }
        }
    }
    
    for(int i=0;i<R;i++)
    {
        for(int j=0;j<C;j++)
        {
            if (lake[i][j] == 'X' || lake[i][j] == '-' || visited[i][j]) continue;
            q.push(i*C+j);
            visited[i][j] = true;

            while(!q.empty())
            {
                y = q.front()/C;
                x = q.front()%C;
                q.pop();

                for(int m=0;m<4;m++)
                {
                    moved_y = y+moves[m][0];
                    moved_x = x+moves[m][1];

                    if (0<=moved_y && moved_y<R && 0<=moved_x && moved_x<C)
                    {
                        if (lake[moved_y][moved_x] == 'X') 
                        {
                            lake[moved_y][moved_x] = '-';
                            q2.push(moved_y*C+moved_x);
                            continue;
                        }
                        if (lake[moved_y][moved_x] == '-') continue;
                        merge(y*C+x, moved_y*C+moved_x);
                        if (visited[moved_y][moved_x]) continue;
                        visited[moved_y][moved_x] = true;
                        q.push(moved_y*C+moved_x);
                    }
                }
            }
        }
    }


    while(true)
    {
        bfs();
        ans++;
        if (find(swan1) == find(swan2)) break;
    }
    cout << ans;
    return 0;
}