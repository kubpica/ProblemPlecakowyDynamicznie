#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int n = 0;
int pojemnosc = 0;
int maxwar = 0;
int maxwag = 0;
bool czyWygenerowac = true;

int main()
{
    cout << "Program rozwiazuje dyskretny problem plecakowy (przedmioty dostepne w wielu egzemplarzach) dla wprowadzonych danych." << endl;
    srand( time( NULL ) );
    while(1){
        //cout << "Gdzie wypisac wyniki? 1 - na ekran 2 - do pliku" << endl;
        //cin >> n;
        //if(n==2) cout << "Jeszcze nie zaimplementowalem wyprowadzenia wyniku do pliku - ale to nie problem zrobic to" << endl;
        n = 0;

        cout << "Skad wziac dane? 1-wygeneruj losowe 2-pozwol mi podac" << endl;
        cin >> n;
        if(n==2) czyWygenerowac = false;

        cout << "Podaj pojemnosc plecaka: ";
        cin >> pojemnosc;
        if(!(pojemnosc<=1000 && pojemnosc>=0)){
            cout << "Podano bledne dane. Sprobuj jeszcze raz." << endl;
            continue;
        }

        cout << "Podaj liczbe przedmiotow (n): ";
        cin >> n;
        if(n>1000 || n<0){
            cout << "Podano bledne dane. Sprobuj jeszcze raz." << endl;
            continue;
        }

        if(czyWygenerowac){
            cout << "Podaj maksymalna wartosc jednego elementu: ";
            cin >> maxwar;
            if(!(maxwar<=1000 && maxwar>=0)){
                cout << "Podano bledne dane. Sprobuj jeszcze raz." << endl;
                continue;
            }

            cout << "Podaj maksymalna wage jednego elementu: ";
            cin >> maxwag;
            if(!(maxwag<=1000 && maxwag>=0)){
                cout << "Podano bledne dane. Sprobuj jeszcze raz." << endl;
                continue;
            }
        }

        break;
    }

    cout << endl;
    int *wartosci;
    int *wagi;
    char *best;
    wartosci = new int [n+1];
    wagi = new int [n+1];
    best = new char [pojemnosc+1];
    int *a;
    a = new int [pojemnosc+1];
    for(int i=0;i<pojemnosc+1;i++){
        a[i] = 0;
        best[i] = '_';
    }

    if(czyWygenerowac){
        for(int i = 0; i<n+1 ; i++){
            int wylosowana =( std::rand() % maxwar ) + 1;
            wartosci[i] = wylosowana;
            wylosowana =( std::rand() % maxwag ) + 1;
            wagi[i] = wylosowana;
        }
    }else{
        char alfabet = 'A';
        for( int i = 1; i <= n; ++i )
        {
            cout << "Podaj wage przedmiotu " << alfabet << ": ";
            cin >> wagi[ i ];
            cout << "Podaj wartosc przedmiotu " << alfabet << ": ";
            cin >> wartosci[ i ];
            cout << endl;
            alfabet++;
        }
    }

    if(czyWygenerowac){
        cout << "Wygenerowalem n-przedmiotow (" << n << "):" << endl;
        cout << "Indeks elementu: waga ; wartosc" << endl;
        char alfabet = 'A';
        for(int i=1;i<=n;i++){
            cout<< alfabet << ": " << wagi[i] << " ; " << wartosci[i] << endl;
            alfabet++;
        }
        cout<<endl;
        system("pause");
        cout<<endl;
    }

    cout << "k       ";
    for(int i = 1; i<=pojemnosc; i++){
        cout << i << " ";
    }
    cout << endl;
    for(int j = 1; j<=n; j++){
        cout << "j=" << j << endl;
        for(int i = 1; i<=pojemnosc; i++){
            if(i >= wagi[j]){
                if(a[i] < a[i-wagi[j]]+wartosci[j]){
                    a[i] = a[i-wagi[j]]+wartosci[j];
                    best[i] = 'A' + j - 1;
                }
            }
        }
        cout << "cost[k] ";
        for(int i = 1; i<=pojemnosc; i++){
            cout << a[i] << " ";
        }
        cout << endl;
        cout << "best[k] ";
        for(int i = 1; i<=pojemnosc; i++){
            cout << best[i] << " ";
        }
        cout << endl;
    }

    cout << "Koniec. Wyniki:" << endl;
    cout << endl;
    cout << "Plecak zawiera najbardziej wartosciowa mieszczaca sie kombinacje przedmiotow (przedmioty dostepne w wielu egzemplarzach)" << endl;
    cout << "Przedmioty w plecaku: ";
    int plecak2 = pojemnosc;
    int zapelnienie = 0;
    int minimalna = wagi[1];
    for(int i=2; i<n+1; i++)
        if(wagi[i]<minimalna)
            minimalna=wagi[i];
    while( plecak2-minimalna >= 0)
    {
        cout << best[plecak2] << " ";
        zapelnienie += wagi[best[plecak2] - 'A' + 1];
        plecak2 -= wagi[best[plecak2] - 'A' + 1];
    };
    cout << endl;
    cout << "Wartosc tych przedmiotow: " << a[pojemnosc] << endl;
    cout << "Zajete miejsce w plecaku: " << zapelnienie << "/" << pojemnosc << endl;
    cin >> n;
}
