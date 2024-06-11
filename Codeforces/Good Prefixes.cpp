#include <iostream>

using namespace std;

int main()
{
    int t, n, ans, num, max;
    long long sum;
    cin >> t;

    for(int testcase=0;testcase<t;testcase++)
    {
        cin >> n;
        ans = 0;
        max = 0;
        sum = 0;
        
        for(int i=0;i<n;i++)
        {
            cin >> num;
            sum = sum+num;
            
            if (max < num) max = num;
            if (sum-max == max) ans++;
        }
        cout << ans << endl;
    }
}