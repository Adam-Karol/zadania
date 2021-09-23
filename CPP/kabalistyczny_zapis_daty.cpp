#include <iostream>
using namespace std;

int wyjscie;
string wejscie;
int main()
{
    while(cin >> wejscie)
    {
        for (int i = 0; i < wejscie.length(); i++)
        {
            if(wejscie[i] == 'a') wyjscie += 1;
            if(wejscie[i] == 'b') wyjscie += 2;
            if(wejscie[i] == 'c') wyjscie += 3;
            if(wejscie[i] == 'd') wyjscie += 4;
            if(wejscie[i] == 'e') wyjscie += 5;
            if(wejscie[i] == 'f') wyjscie += 6;
            if(wejscie[i] == 'g') wyjscie += 7;
            if(wejscie[i] == 'h') wyjscie += 8;
            if(wejscie[i] == 'i') wyjscie += 9;
            if(wejscie[i] == 'k') wyjscie += 10;
            if(wejscie[i] == 'l') wyjscie += 20;
            if(wejscie[i] == 'm') wyjscie += 30;
            if(wejscie[i] == 'n') wyjscie += 40;
            if(wejscie[i] == 'o') wyjscie += 50;
            if(wejscie[i] == 'p') wyjscie += 60;
            if(wejscie[i] == 'q') wyjscie += 70;
            if(wejscie[i] == 'r') wyjscie += 80;
            if(wejscie[i] == 's') wyjscie += 90;
            if(wejscie[i] == 't') wyjscie += 100;
            if(wejscie[i] == 'v') wyjscie += 200;
            if(wejscie[i] == 'x') wyjscie += 300;
            if(wejscie[i] == 'y') wyjscie += 400;
            if(wejscie[i] == 'z') wyjscie += 500;
        }
        cout << wyjscie << endl;
        return 0;
    }
}