#include <iostream>
#include <string>
#include <time.h>

using namespace std;

class Student
{
protected:
    string imie, nazwisko;
    unsigned rok_urodzenia;
    float* oceny;
    int rozmiar;

public:
    Student(string imie, string nazwisko, unsigned rok_urodzenia, float* tablica, int rozmiar)
    {
        this->imie = imie;
        this->nazwisko = nazwisko;
        this->rok_urodzenia = rok_urodzenia;
        //this->tablica_ocen = tablica_ocen;

        this->rozmiar = rozmiar;
        this->oceny = new float[rozmiar];
        for (int i = 0; i < rozmiar; i++)
            this->oceny[i] = tablica[i];

    }

    ~Student() // destruktor
    {
        delete[] this->oceny;
    }

    int wiek()
    {
        return (time(nullptr) / 60 / 60 / 24 / 365 + 1970) - this->rok_urodzenia;
    }

    float srednia_ocen()
    {
        float wynik = 0;
        for(int i = 0; i < this->rozmiar; i++)
            wynik += this->oceny[i];

        return wynik / this->rozmiar;
    }

    float najlepsza_ocena()
    {
        float naj = 0;

        for(int i = 0; i < this->rozmiar; i++)
            if(naj < oceny[i])
                naj = oceny[i];

        return naj;
    }

    float najgorsza_ocena()
    {
        float naj = 7;
        for(int i = 0; i < this->rozmiar; i++)
        {
            if(naj > this->oceny[i])
            {
                naj = this->oceny[i];
            }
        }
        return naj;
    }

    void dodaj_ocene(float nowa_ocena)
    {
        float* nowa_tablica = new float[rozmiar+1];

        for (int i = 0; i < rozmiar; i++)
            nowa_tablica[i] = this->oceny[i];

        nowa_tablica[rozmiar] = nowa_ocena;

        delete[] this->oceny;

        this->oceny = nowa_tablica;
        this->rozmiar = this->rozmiar + 1;

    }

    void usun_ocene(float do_usuniecia)
    {
        float* nowa_tablica = new float[rozmiar-1];

        int temp = 0;
        bool czy = false;
        for(int i = 0; i < this->rozmiar; i++)
        {
            if (this->oceny[i] == do_usuniecia)
            {
                czy = true;
                continue;
            }
            nowa_tablica[temp] = oceny[i];
            temp += 1;
        }
        if (czy)
        {
            oceny = nowa_tablica;
            rozmiar -= 1;
        }
    }

    void wypisz()
    {
        cout << endl << "Imie: " << this->imie << endl << "Nazwisko: " << this->nazwisko << endl << "Rok urodzenia: " << this->rok_urodzenia << endl << "Oceny: [";
        for(int i = 0; i < this->rozmiar; i++)
        {
            cout << this->oceny[i];

            if (i != this->rozmiar - 1)
                cout << ", ";

        }
        cout << "]" << endl;
    }
};


int main() {

    float oceny[] = {2, 3.5, 2, 5, 5};
    Student s1("Jan", "Kowalski", 2000, oceny, 5);

    cout << "wiek: " << s1.wiek();

    s1.wypisz();
    cout << "najgorsza: " << s1.najgorsza_ocena() << endl;
    cout << "najlepsza: " << s1.najlepsza_ocena() << endl;
    cout << "srednia: " << s1.srednia_ocen() << endl;

    s1.dodaj_ocene(4);
    s1.wypisz();

    s1.usun_ocene(3.5);
    s1.usun_ocene(3.5);
    s1.wypisz();

    return 0;
}