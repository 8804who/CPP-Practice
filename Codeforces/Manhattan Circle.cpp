#include <iostream>

using namespace std;

int main()
{

    int t, n, m, min_w, max_w, min_h, max_h;
    string str;
    cin >> t;

    for(int testcase=0;testcase<t;testcase++)
    {
        cin >> n >> m;
        min_h = n;
        min_w = m;
        max_h = 0;
        max_w = 0;
        
        for(int i=1;i<=n;i++)
        {
            cin >> str;
            for(int j=1;j<=m;j++)
            {
                if(str[j-1]=='#')
                {
                    if(i<min_h) min_h = i;
                    if(i>max_h) max_h = i;
                    if(j<min_w) min_w = j;
                    if(j>max_w) max_w = j;
                }
            }
        }
        cout << (min_h+max_h)/2 << ' ' << (min_w+max_w)/2 << endl;
    }
}