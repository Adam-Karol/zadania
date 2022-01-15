#include <iostream>
using namespace std;

template <typename T>
T sumowanie(T* wsk, int rozmiar)
{
    if (rozmiar == 0)
        return 0;
    return sumowanie(wsk, rozmiar - 1) + wsk[rozmiar - 1];
}

int main()
{
    int tab[5] = {5, 2, 6, 2, 5};
    cout << sumowanie(tab, 5) << endl; // wyświetli 20

    double tab2[5] = {5.5, 2.5, 6.1, 1.5, 4.5};
    cout << sumowanie(tab2, 5) << endl; // suma 20.1
}