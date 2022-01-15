#include <iostream>
using namespace std;

template <typename T>
struct elem
{
    T wartosc;
    elem* nast;
    elem* poprz;
};

template <typename T>
class ListaDwukierunkowa
{
protected:
    elem<T>* lista;

public:
    ListaDwukierunkowa()
    {

        this->lista = nullptr;
    }

    ~ListaDwukierunkowa()
    {
        zwolnij_liste();
    }

    T& operator[] (int a)
    {
        return zwroc_wartosc_ref(a);
    }

    void dodaj_elem(const T do_dodania)
    {
        if (lista == nullptr)
        {
            lista = new elem<T>;
            lista->wartosc = do_dodania;
            lista->nast = nullptr;
            lista->poprz = nullptr;
        }
        else
        {
            elem<T> *temp = lista;
            while (temp->nast != nullptr)
            {
                temp = temp->nast;
            }
            temp->nast = new elem<T>;
            temp->nast->wartosc = do_dodania;
            temp->nast->nast = nullptr;
            temp->nast->poprz = temp;
        }
    }

    void wyswietl_elem()
    {
        elem<T> *temp = lista;
        cout << endl;
        if (temp == nullptr)
        {
            cout << "Lista jest pusta" << endl;
        }
        while (temp != nullptr)
        {
            cout << "poprz: " <<  temp->poprz << " | ten: " << temp << " | war:" << temp->wartosc << " | nast:" << temp->nast << endl;
            temp = temp->nast;
        }
    }

    T& zwroc_wartosc_ref(int index)
    {
        if (index < 0 or index >= liczba_elem())
        {
            throw invalid_argument("Nieporawny index");
        }
        elem<T> *temp = lista;
        int i = 0;
        while (i != index)
        {
            temp = temp->nast;
            i++;
        }
        return temp->wartosc;
    }

    void usun_elem(int do_usun)
    {
        elem<T> *temp = lista;
        if (lista == nullptr)
            return;

        while (temp->wartosc != do_usun)
        {
            temp = temp->nast;
            if (temp == nullptr)
                return;
        }

        if (temp->poprz)
            temp->poprz->nast = temp->nast;
        else
            lista = temp->nast;

        if (temp->nast)
            temp->nast->poprz = temp->poprz;

        delete temp;
    }

    T sumowanie()
    {
        elem<T> *temp = lista;
        T suma = 0;

        while (temp != nullptr)
        {
            suma += temp->wartosc;
            temp = temp->nast;
        }
        return suma;
    }

    int liczba_elem()
    {
        elem<T> *temp = lista;
        int liczba = 0;
        while (temp != nullptr)
        {
            liczba += 1;
            temp = temp->nast;
        }
        return liczba;
    }

    int liczba_elem_o_war(int x)
    {
        elem<T> *temp = lista;
        int liczba = 0;
        while (temp != nullptr)
        {
            if (temp->wartosc == x)
            {
                liczba += 1;
            }
            temp = temp->nast;
        }
        return liczba;
    }

    int indeks_od(T war)
    {
        elem<T> *temp = lista;
        int indeks = -1;
        int i = 0;
        while (temp != nullptr)
        {
            if (temp->wartosc == war)
            {
                indeks = i;
            }
            i++;
            temp = temp->nast;
        }
        if (indeks != -1)
        {
            return indeks;
        }
        throw invalid_argument("Nie ma takiego elementu w liscie");
    }

    bool czy_zawiera(int x)
    {
        elem<T> *temp = lista;
        bool czy = false;
        while (temp != nullptr)
        {
            if (temp->wartosc == x)
            {
                czy = true;
            }
            temp = temp->nast;
        }
        return czy;
    }

    void zwolnij_liste()
    {
        while (lista != nullptr)
        {
            elem<T>* nast = lista->nast;
            delete lista;
            lista = nast;
        }
        lista = nullptr;
    }
};

int main()
{
    ListaDwukierunkowa<int> lista;
    lista.dodaj_elem(2.1);
    lista.dodaj_elem(3.2);
    lista.dodaj_elem(4.3);

    cout << lista.sumowanie();
}