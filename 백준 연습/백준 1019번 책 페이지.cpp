#include <iostream>

using namespace std;

int main()
{
    int N;
    int arr[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    cin >> N;

    int num = 1;
    int temp = N;
    while(temp >= 10)
    {
        for(int i=0;i<10;i++) arr[i] = arr[i]*10+num;
        num *= 10;
        temp /= 10;
    }

    for(int i=0;i<10;i++) arr[i] = arr[i]*temp;
    for(int i=0;i<temp;i++) arr[i] = arr[i]+num;

    for(int i=temp*num;i<=N;i++)
    {
        int temp_num = i;
        while(temp_num > 0)
        {
            arr[temp_num%10]++;
            temp_num /= 10;
        }
    }  

    for(int i=1;i<=N;i*=10) arr[0] -= i;
    for(int i=0;i<10;i++) cout << arr[i] << ' ';

    return 0;
}