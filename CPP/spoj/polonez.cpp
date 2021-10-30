#include <iostream>
#include <vector>
using namespace std;

int wynik(vector<int> klasy);

int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    vector<int> klasy ={a, b, c};
    cout << wynik(klasy);
}

int wynik(vector<int> klasy)
{
    int dziewczyny = 0, chlopcy = 0;
    string imie;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < klasy[i]; j++)
        {
            cin >> imie;
            if (imie.back() == 'a')
            {
                dziewczyny += 1;
            }
            else
            {
                chlopcy += 1;
            }
        }
    }
    if (dziewczyny > chlopcy)
    {
        return chlopcy;
    }
    return dziewczyny;
}