#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename x>

bool find(vector<x> lista, x zmienna)
{
    for(int i : lista)
        if(i == zmienna)
            return true;
    return false;
}

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
        if(find(litery, i))
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