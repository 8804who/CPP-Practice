#include <iostream>

using namespace std;

int n;
int lps[1000000];
char pattern[1000000];

void get_pattern()
{
    int idx = 0;
    lps[0] = 0;
    for(int i=1;i<n;i++)
    {
        while(idx > 0 && pattern[i] != pattern[idx]) idx = lps[idx-1];

        if (pattern[i] == pattern[idx])
        {
            idx++;
            lps[i] = idx;
        }
    }
}

int main()
{
    cin >> n;

    for(int i=0;i<n;i++) cin >> pattern[i];
    get_pattern();

    cout << n-lps[n-1];

    return 0;
}