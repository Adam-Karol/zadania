#include <iostream>
using namespace std;

struct elem
{
    int wartosc;
    elem* nast;
    elem* poprz;
};

void dodaj_elem(elem** lista, int do_dodania)
{
    if (*lista == nullptr)
    {
        *lista = new elem;
        (*lista)->wartosc = do_dodania;
        (*lista)->nast = nullptr;
        (*lista)->poprz = nullptr;
    }
    else
    {
        elem *temp = *lista;
        while (temp->nast != nullptr)
        {
            temp = temp->nast;
        }
        temp->nast = new elem;
        temp->nast->wartosc = do_dodania;
        temp->nast->nast = nullptr;
        temp->nast->poprz = temp;
    }
}

void wyswietl_elem(elem* lista)
{
    cout << endl;
    if (lista == nullptr)
    {
        cout << "Lista jest pusta" << endl;
    }
    while (lista != nullptr)
    {
        cout << "poprz: " <<  lista->poprz << " | ten: " << lista << " | war:" << lista->wartosc << " | nast:" << lista->nast << endl;
        lista = lista->nast;
    }
}

void usun_elem(elem** lista, int do_usun)
{
    elem *temp = *lista;
    if (*lista == nullptr)
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
        *lista = temp->nast;

    if (temp->nast)
        temp->nast->poprz = temp->poprz;

    delete temp;
}

int liczba_elem(elem* lista)
{
    int liczba = 0;
    while (lista != nullptr)
    {
        liczba += 1;
        lista = lista->nast;
    }
    return liczba;
}

int liczba_elem_o_war(elem* lista, int x)
{
    int liczba = 0;
    while (lista != nullptr)
    {
        if (lista->wartosc == x)
        {
            liczba += 1;
        }
        lista = lista->nast;
    }
    return liczba;
}

bool czy_zawiera(elem* lista, int x)
{
    bool czy = false;
    while (lista != nullptr)
    {
        if (lista->wartosc == x)
        {
            czy = true;
        }
        lista = lista->nast;
    }
    return czy;
}

void zwolnij_liste(elem** lista)
{
    while (*lista != nullptr)
    {
        elem* nast = (*lista)->nast;
        delete *lista;
        *lista = nast;
    }
    *lista = nullptr;
}

int main()
{
    elem* wsk = nullptr;
    dodaj_elem(&wsk, 12);
    dodaj_elem(&wsk, 9);
    dodaj_elem(&wsk, 8);
    dodaj_elem(&wsk, 9);
    dodaj_elem(&wsk, 9);
    wyswietl_elem(wsk);
    cout << liczba_elem(wsk) << endl;
    cout << liczba_elem_o_war(wsk, 9) << endl;
    cout << boolalpha << czy_zawiera(wsk, 12) << endl;
    usun_elem(&wsk, 1);
    wyswietl_elem(wsk);
    zwolnij_liste(&wsk);

}