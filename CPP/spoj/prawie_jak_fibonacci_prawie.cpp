#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, temp, ile = 0;
    vector<int> wejscie;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        wejscie.push_back(temp);
    }

    for(int i = 0; i < (n-2); i++)
    {
        if (( wejscie[i+2] ) == (( wejscie[i+1] ) + ( wejscie[i] )))
        {
            ile += 1;
        }

    }
    cout << ile;
    return 0;
}