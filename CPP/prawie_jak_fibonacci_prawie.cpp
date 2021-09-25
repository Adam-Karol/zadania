#include <iostream>
#include <vector>
using namespace std;



int main()
{
    int n, temp, ile = 0;
    vector<float> wejscie;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        wejscie.push_back(temp);
    }

    for(int i = 0; i < n; i++)
    {
        if (( wejscie[i+3] ) == (( wejscie[i+2] ) + ( wejscie[i+1] )))
        {
            ile += 1;
        }

    }
    cout << ile;
    return 0;
}