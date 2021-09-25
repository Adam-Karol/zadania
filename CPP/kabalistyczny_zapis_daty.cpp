#include <iostream>
using namespace std;

int main()
{
    int wyjscie = 0;
    string wejscie;
    cin >> wejscie;
    for (int i = 0; i < wejscie.length(); i++)
    {
        if(wejscie[i] == 'a') wyjscie += 1;
        else if(wejscie[i] == 'b') wyjscie += 2;
        else if(wejscie[i] == 'c') wyjscie += 3;
        else if(wejscie[i] == 'd') wyjscie += 4;
        else if(wejscie[i] == 'e') wyjscie += 5;
        else if(wejscie[i] == 'f') wyjscie += 6;
        else if(wejscie[i] == 'g') wyjscie += 7;
        else if(wejscie[i] == 'h') wyjscie += 8;
        else if(wejscie[i] == 'i') wyjscie += 9;
        else if(wejscie[i] == 'k') wyjscie += 10;
        else if(wejscie[i] == 'l') wyjscie += 20;
        else if(wejscie[i] == 'm') wyjscie += 30;
        else if(wejscie[i] == 'n') wyjscie += 40;
        else if(wejscie[i] == 'o') wyjscie += 50;
        else if(wejscie[i] == 'p') wyjscie += 60;
        else if(wejscie[i] == 'q') wyjscie += 70;
        else if(wejscie[i] == 'r') wyjscie += 80;
        else if(wejscie[i] == 's') wyjscie += 90;
        else if(wejscie[i] == 't') wyjscie += 100;
        else if(wejscie[i] == 'v') wyjscie += 200;
        else if(wejscie[i] == 'x') wyjscie += 300;
        else if(wejscie[i] == 'y') wyjscie += 400;
        else if(wejscie[i] == 'z') wyjscie += 500;
    }
    cout << wyjscie << endl;
    return 0;
}