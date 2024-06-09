#include <iostream>

int main()
{
    int t, n;
    scanf("%d", &t);
    for (int testcase=0;testcase<t;testcase++)
    {
        scanf("%d", &n);
        int arr[n];

        for(int i=0;i<n;i++) scanf("%d", &arr[i]);
        
        if (arr[n-1]-arr[0] == 0)
        {
            printf("NO\n");
        }
        else
        {
            printf("YES\n");
            printf("RB");
            for(int i=2;i<n;i++) printf("R");
            printf("\n");
        }
    } 
}