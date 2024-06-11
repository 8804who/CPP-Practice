#include <iostream>

using namespace std;

int main()
{
    int t;
    string word1, word2;
    cin >> t;

    for(int i=0;i<t;i++)
    {
        cin >> word1;
        cin >> word2;
        cout << word2[0] << word1[1] << word1[2] << ' ' << word1[0] << word2[1] << word2[2] << endl;
    }
}