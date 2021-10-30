#include <iostream>
using namespace std;

int main() {
    string slowo;
    int dlugosc, a, b;

    cin >> dlugosc >> slowo;

    if(dlugosc % 2 != 1)
        return 0;

    a = dlugosc / 2;
    b = dlugosc / 2;

    while(a >= 0)
    {
        for(int i = 0; i < dlugosc; i++)
        {
            if(i >= a and i <= b)
            {
                cout << slowo[i];
            }
            else
            {
                cout << ".";
            }
        }
        cout << endl;
        a--; b++;
    }
}