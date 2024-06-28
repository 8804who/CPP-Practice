#include <iostream>

using namespace std;

int N, M;
int graph[201][201];
int max_dist[201][201];

void floyd_warshall()
{
    for(int k=1;k<=N;k++) for(int i=1;i<=N;i++) for(int j=1;j<=N;j++) if (graph[i][k] + graph[k][j] < graph[i][j]) graph[i][j] = graph[i][k]+graph[k][j];
}

int main()
{
    cin >> N >> M;
    
    for(int i=1;i<=N;i++) for(int j=1;j<=N;j++) 
    {
        if (i == j) graph[i][j] = 0;
        else graph[i][j] = 1e9;
        max_dist[i][j] = 0;
    }

    for(int i=0;i<M;i++)
    {
        int S, E, L;
        cin >> S >> E >> L;

        if (graph[S][E] > L)
        {
            graph[S][E] = L;
            graph[E][S] = L;
        }
        if (max_dist[S][E] < L)
        {
            max_dist[S][E] = L;
            max_dist[E][S] = L;
        }
    }

    floyd_warshall();

    float ans = 1e9;
    for(int i=1;i<=N;i++)
    {
        float min_time = 0;
        for(int j=1;j<=N;j++)
        {
            min_time = max(min_time, (float)graph[i][j]);
            for(int k=1;k<=N;k++)
            {
                if (graph[i][j] > graph[i][k]) continue;
                else if (graph[i][j] == graph[i][k])  min_time = max(min_time, (float)graph[i][j]+(float)max_dist[j][k]/2);             
                else
                {
                    if (graph[i][j] + max_dist[j][k] <= graph[i][k]) min_time = max(min_time, (float)(graph[i][j]+max_dist[j][k]));
                    else min_time = max(min_time, (float)(graph[i][j] + max_dist[j][k] - graph[i][k])/2 + (float)graph[i][k]);
                }
            }
        }
        ans = min(ans, min_time);
    }

    cout << fixed; cout.precision(1);
    cout << ans;

    return 0;
}