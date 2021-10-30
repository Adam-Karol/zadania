#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int l_liter;
    vector<char> litery;
    string slowo;

    char temp;
    cin >> l_liter;
    for(int i = 0; i < l_liter; i++)
    {
        cin >> temp;
        litery.push_back(temp);
    }

    cin >> slowo;

    string wyjscie = "";

    for(char i : slowo)
    {
        vector<char>::iterator it;
        if ( ( it = std::find( litery.begin(), litery.end(), i)) != litery.end())
        {
            wyjscie += i;
            wyjscie += i;
        }
        else
        {
            wyjscie += i;
        }
    }

    cout << wyjscie;
}