#include <iostream>
using namespace std;

int wynik(int a, int b);

int main()
{
    int a, b, t;
    cin >> t;
    for(int i = 0; i < t; i++)
    {
        cin >> a >> b;
        cout << wynik(a, b) << endl;
    }
}
int wynik(int a, int b)
{
    int temp;
    while(b)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    return 2 * a;
}
