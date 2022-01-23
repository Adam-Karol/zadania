#include <iostream>
#include <vector>
using namespace std;

struct pozycja
{
    int x; // 1-8
    int y; // 1-8
};

void wczytaj_pozycje(pozycja& pozycja1, pozycja& pozycja2);

std::vector<pozycja> oblicz_ataki(pozycja skoczek);

int main()
{
    pozycja k1;
    pozycja k2;
    wczytaj_pozycje(k1, k2);

//    cout << k1.x << k1.y << k2.x << k2.y;

    std::vector<pozycja> ataki = oblicz_ataki(k1);

    for (pozycja a : ataki)
    {
        if (a.x == k2.x and a.y == k2.y)
        {
            cout << "TAK";
            return 0;
        }
    }
    cout << "NIE";

    return 0;
}

std::vector<pozycja> oblicz_ataki(pozycja skoczek)
{
    vector<pozycja> ataki {};

    pozycja atak = {skoczek.x + 2, skoczek.y + 1};
    ataki.push_back(atak);
    atak = {skoczek.x - 2, skoczek.y - 1};
    ataki.push_back(atak);
    atak = {skoczek.x + 1, skoczek.y + 2};
    ataki.push_back(atak);
    atak = {skoczek.x + 2, skoczek.y - 1};
    ataki.push_back(atak);
    atak = {skoczek.x - 2, skoczek.y + 1};
    ataki.push_back(atak);
    atak = {skoczek.x - 1, skoczek.y + 2};
    ataki.push_back(atak);
    atak = {skoczek.x - 1, skoczek.y - 2};
    ataki.push_back(atak);
    atak = {skoczek.x + 1, skoczek.y - 2};
    ataki.push_back(atak);

    return ataki;
}

void wczytaj_pozycje(pozycja& pozycja1, pozycja& pozycja2)
{
    string temp1, temp2;
    cin >> temp1 >> temp2;
    pozycja1.x = temp1[0]-96;
    pozycja1.y = temp1[1]-48;
    pozycja2.x = temp2[0]-96;
    pozycja2.y = temp2[1]-48;
}