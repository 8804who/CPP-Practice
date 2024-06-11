#include <iostream>

using namespace std;

int main()
{
    int t, n, num, sum, ans, max_sum;
    cin >> t;

    for(int i=0;i<t;i++)
    {
        cin >> n;
        max_sum = 0;
        ans = 0;
        for(int j=2;j<=n;j++)
        {
            sum = 0;
            num = j;

            while(num<=n)
            {
                sum += num;
                num += j;
                
            }

            if (sum > max_sum)
            {
                max_sum = sum;
                ans = j;
            } 
        }
        cout << ans << endl;
    }
}