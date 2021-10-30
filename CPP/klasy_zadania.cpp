#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

enum nagroda
{
    stopien1,
    stopien2,
    stopien3
};

string enum_na_napis(nagroda in)
{
    switch (in)
    {
        case stopien1:
            return "STOPIEN 1.";
        case stopien2:
            return "STOPIEN 2.";
        case stopien3:
            return "STOPIEN 3.";
    }
}

class Student
{
protected:
    string imie, nazwisko;
    unsigned rok_urodzenia;
    vector<float> tablica_ocen;

public:
    Student(string imie, string nazwisko, unsigned rok_urodzenia, vector<float> tablica_ocen)
    {
        this->imie = imie;
        this->nazwisko = nazwisko;
        this->rok_urodzenia = rok_urodzenia;
        this->tablica_ocen = tablica_ocen;
    }

    int wiek()
    {
        return (time(0) / 60 / 60 / 24 / 365 + 1970) - rok_urodzenia;
    }

    float srednia_ocen()
    {
        float wynik = 0;
        for(int i = 0; i < this->tablica_ocen.size(); i++)
        {
            wynik += this->tablica_ocen[i];
        }
        return wynik/this->tablica_ocen.size();
    }

    float najlepsza_ocena()
    {
        float naj = 0;
        for(int i = 0; i < this->tablica_ocen.size(); i++)
        {
            if(naj < tablica_ocen[i])
            {
                naj = tablica_ocen[i];
            }
        }
        return naj;
    }

    float najgorsza_ocena()
    {
        float naj = 7;
        for(int i = 0; i < this->tablica_ocen.size(); i++)
        {
            if(naj > tablica_ocen[i])
            {
                naj = tablica_ocen[i];
            }
        }
        return naj;
    }

    void dodaj_ocene(float nowa_ocena)
    {
        this->tablica_ocen.push_back(nowa_ocena);
    }

    void usun_ocene(float do_usuniecia)
    {
        for(int i = 0; i < this->tablica_ocen.size(); i++)
        {
            if(this->tablica_ocen[i] == do_usuniecia)
            {
                this->tablica_ocen.erase(this->tablica_ocen.begin()+i);
            }
        }
    }

    void wypisz()
    {
        cout << "Imie: " << this->imie << endl << "Nazwisko: " << this->nazwisko << endl << "Rok urodzenia: " << this->rok_urodzenia << endl << "Oceny: [";
        for(int i = 0; i < this->tablica_ocen.size(); i++)
        {
            cout << this->tablica_ocen[i];

            if (i != this->tablica_ocen.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "]";
    }
};

class ZdolnyStudent : public Student
{
private:
    vector<nagroda> nagrody;

public:
    ZdolnyStudent(string imie, string nazwisko, unsigned rok_urodzenia, vector<float> tablica_ocen, vector<nagroda> nagrody)
            : Student(imie, nazwisko, rok_urodzenia, tablica_ocen)
    {
        this->imie = imie;
        this->nazwisko = nazwisko;
        this->rok_urodzenia = rok_urodzenia;
        this->tablica_ocen = tablica_ocen;
        this->nagrody = nagrody;
    }

    void dodaj_nagrode(nagroda stopien)
    {
        this->nagrody.push_back(stopien);
    }

    void wyswietl_nagrody()
    {
        int s1 = 0;
        int s2 = 0;
        int s3 = 0;

        for(int i = 0; i < this->nagrody.size(); i++)
        {
            if(nagrody[i] == stopien1)
                s1 += 1;
            if(nagrody[i] == stopien2)
                s2 += 1;
            if(nagrody[i] == stopien3)
                s3 += 1;
        }
        cout << s1 << " - nagrody 1. stopnia" << endl;
        cout << s2 << " - nagrody 2. stopnia" << endl;
        cout << s3 << " - nagrody 3. stopnia" << endl;
    }
};

int main()
{
    vector<float> oceny = {5, 4, 6, 3, 6};
    vector<nagroda> nagrody = {stopien1, stopien1, stopien3};
    ZdolnyStudent uczen("Marek", "Kowalski", 1999, oceny, nagrody);

    uczen.wyswietl_nagrody();
    uczen.dodaj_nagrode(stopien2);
    cout << endl;
    uczen.wyswietl_nagrody();
}