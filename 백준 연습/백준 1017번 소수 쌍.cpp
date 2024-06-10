#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool prime_number[2001];
vector<int> group1;
vector<int> group2;
vector<bool> done;
vector<int> assign;

void is_prime_number()
{
    int num;
    for(int i=2;i<2001;i++)
    {
        if (prime_number[i])
        {
            num=i*2;
            while (num<2001)
            {
                prime_number[num] = false;
                num+=i;
            }
        }
    }
}

bool match(int num, vector<vector<int>> vec, int except)
{
    vector<int> temp = vec[num];
    for(int pair_num : temp)
    {
        if (pair_num==except) continue;
        if (done[pair_num]) continue;
        done[pair_num] = true;
        if (assign[pair_num] == -1 || match(assign[pair_num], vec, except))
        {
            assign[pair_num] = num;
            return true;
        }
    }
    return false;
}

int main()
{   
    vector<vector<int>> pair;
    int n, num;
    bool first_even;

    for(int i=0;i<2001;i++) prime_number[i] = true;

    scanf("%d", &n);
    scanf("%d", &num);

    if (num%2==1) first_even = false;
    else first_even = true;
    group1.push_back(num);

    for(int i=1;i<n;i++)
    {
        scanf("%d", &num);
        if (first_even)
        {
            if (num%2==0) group1.push_back(num);
            else 
            {
                group2.push_back(num);
                done.push_back(false);
                assign.push_back(-1);
            }
        }
        else
        {
            if (num%2==1) group1.push_back(num);
            else 
            {
                group2.push_back(num);
                done.push_back(false);
                assign.push_back(-1);
            }
        }
        
    } 

    if (group1.size() != group2.size()) 
    {
        printf("-1");
        return 0;
    }

    sort(group2.begin(), group2.end());
    is_prime_number();

    for(int i=0;i<n/2;i++)
    {
        vector<int> temp;
    
        for(int j=0;j<n/2;j++)
        {
            if (prime_number[group1[i]+group2[j]]) temp.push_back(j);
        }
        pair.push_back(temp);
    }

    bool possible = false;

    for(int i=0;i<pair[0].size();i++)
    {
        int count = 0;
        for(int j=0;j<n/2;j++) assign[j] = -1;
        for(int j=1;j<n/2;j++)
        {
            for(int k=0;k<n/2;k++) done[k] = false;
            if (match(j, pair, pair[0][i])) count++;
        }
        if (count == n/2-1)
        {
            printf("%d ", group2[pair[0][i]]);
            possible = true;
        } 
    }

    if (!possible) printf("-1");

    return 0;
}