#include <iostream>

using namespace std;

int main()
{
    int arr[10][1024];
    int count[10][1024];
    int n, n1;
    int ans = -1;
    string s;
    
    for(int i=0;i<10;i++)
    {
        n=0;
        cin >> s;
        for(int j=0;j<10;j++) if (s[j] == 'O') n|=1<<j;
        for(int j=0;j<1024;j++) 
        {
            arr[i][j] = n;
            count[i][j] = 0;
        }
    }
    
    for(int i=0;i<10;i++)
    {
        n=1<<i;
        n1=(7<<(i-1))%1024;
        if (i==0) n1 = 3;

        for(int j=0;j<(1<<i);j++)
        {
            count[0][n|j] = count[0][j]+1;
            arr[0][n|j] = arr[0][j]^n1;
            arr[1][n|j] = arr[1][j]^n;
        }
    }

    for(int i=1;i<10;i++)
    {
        for(int j=0;j<1024;j++)
        {
            count[i][j] = count[i-1][j];
            for(int k=0;k<10;k++)
            {
                if (arr[i-1][j] & 1<<k)
                {
                    n = 1<<k;
                    n1 = (7<<(k-1))%1024;
                    if (k==0) n1 = 3;

                    arr[i-1][j] ^= n;
                    arr[i][j] ^= n1;
                    if (i<9) arr[i+1][j] ^= n;
                    count[i][j]++;
                }
            }
        }
    }

    for(int i=0;i<1024;i++)
    {
        if (arr[9][i]==0 && (ans == -1||ans>count[9][i])) ans = count[9][i];
    }

    cout << ans << endl;
    return 0;
}