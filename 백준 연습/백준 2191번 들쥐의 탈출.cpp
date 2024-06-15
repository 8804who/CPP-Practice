#include <iostream>
#include <vector>

using namespace std;

int N, M, S, V, ans;
double x, y;

bool done[100];
int assign[100];

vector<int> vec[100];
vector<pair<double, double>> mouse;
vector<pair<double, double>> tunnel;

double get_distance(double x1, double y1, double x2, double y2)
{
    return (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2);
}

bool match(int n)
{
    for(int t : vec[n])
    {
        if (done[t]) continue;
        done[t] = true;

        if (assign[t] == -1 || match(assign[t]))
        {
            assign[t] = n;
            return true;
        }
    }
    return false;
}

int main()
{
    cin >> N >> M >> S >> V;
    ans = N;

    for(int i=0;i<N;i++)
    {
        cin >> x >> y;
        mouse.push_back(make_pair(x, y));
    }

    for(int i=0;i<M;i++)
    {
        cin >> x >> y;
        tunnel.push_back(make_pair(x, y));
    }

    for(int i=0;i<N;i++) for(int j=0;j<M;j++) if (get_distance(mouse[i].first, mouse[i].second, tunnel[j].first, tunnel[j].second) <= V*V*S*S) vec[i].push_back(j);
    
    for(int i=0;i<M;i++) assign[i] = -1;

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<M;j++) done[j] = false;
        if (match(i)) ans--;
    }

    cout << ans;
    return 0;
}