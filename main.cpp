/*  Projekt 2 PROI - Wielomiany
 *  Robert Dudzinski 2018
 *  main.cpp
 */

#include "Polynomial.h"
using namespace std;

void przyklady();
void ui();

int main()
{
    cout << "   Projekt PROI - Operacje na wielomianach" <<endl;
    cout << "   Robert Dudzinski" <<endl;

    przyklady();
    ui();

    return 0;
}

void przyklady()
{
    Polynomial wielo1;
    Polynomial wielo2("x^5 + 3x^4 - 5x^2 + 1");
    Polynomial wielo3(wielo2);

    cout<<"w1 empty:        "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"w2 wielo(str):   "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"w3 = wielo(w2):  "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<"w1 == w2:        "<<(wielo1 == wielo2)<<endl;
    cout<<"w2 != w3:        "<<(wielo2 != wielo3)<<endl;
    cout<<"w3 == str:       "<<(wielo2 == "x^5 + 3x^4 - 5x^2 + 1")<<endl;
    cout<<endl;

    if (wielo1 == wielo2)
        if (wielo2 != wielo3);

    wielo1 = "-x^3 + 5x^2 + 2";
    wielo2 += wielo1;
    wielo3 = wielo1 - wielo2;

    cout<<"w1 = str:        "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"w2 += w1:        "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"w3 = w1 - w2:    "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    wielo1 += "11x^3-18";
    wielo2 *= 4;
    wielo3.derivative();

    cout<<"w1 += str:   "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"w2 *= 4:     "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"w3 dx:       "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    wielo1.reduceFactors();
    wielo2 = wielo2 - "4x5";
    wielo3 -= wielo2;

    cout<<"w1 reduce:       "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"w2 = w2 - str:   "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"w3 -= w2:        "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    cout<<"w1 (1):      "<<wielo1.getDegree()<<",   "<<wielo1.calc(1)<<endl;
    cout<<"w2 (-1):     "<<wielo2.getDegree()<<",   "<<wielo2.calc(-1)<<endl;
    cout<<"w3 (2):      "<<wielo3.getDegree()<<",   "<<wielo3.calc(2)<<endl;
    cout<<endl;

    wielo1 = wielo3 * -6;
    wielo2 = -6 * wielo3;

    cout<<"w1 = w3 * -6:    "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"w2 = -6 * w3:    "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"w3:              "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    wielo1 = wielo3 - 10;
    wielo2 = -10 + wielo3;

    cout<<"w1 = w3 - 10:    "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"w2 = -10 + w3:   "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"w3:              "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    wielo1 = string("2x3 + 3x3 + 4x5 + x2") + wielo3;
    wielo2 = "2x3 + 3x3 + 4x5 + x2";

    cout<<"w1 = str + w3:   "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"w2 = str:        "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"w3:              "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    string e;
    if (Polynomial::checkLastError(e)) cout<<e<<endl;

    wielo1 = "2x^9 + 3x^23^1 - 4x-2sa + 8x2 + 7xx ++ x + x2x";
    if (Polynomial::checkLastError(e)) cout<<e<<endl<<endl;

    cout<<"w1 = po bledzie:   "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<endl;

    if (Polynomial::checkLastError(e)) cout<<e<<endl;

    wielo1 = "x8+x7+x6+x5+x4+x3+x2+x+1";
    wielo2 = 7;
    wielo3 = 2*wielo1*3 + 2*wielo2;

    cout<<"w1 = str:          "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"w2 = 7:            "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"w3 = 2*w1*3+2*w2:  "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    cout<<"w3: wyraz wolny:     "<<wielo3.getFactor(0)<<endl;
    cout<<"w3: wsp przy x^3:    "<<wielo3.getFactor(3)<<endl;
    cout<<"w3: wsp przy x^9:    "<<wielo3.getFactor(9)<<endl;

    if (Polynomial::checkLastError(e)) cout<<e<<endl;
}

void ui()
{
    Polynomial wielo;

    while(true)
    {
        cout << endl << endl;
        cout << "Obecny wielomian: " << wielo << endl << endl;
        cout << "[1] Dodaj" << endl;
        cout << "[2] Odejmij" << endl;
        cout << "[3] Pomnoz przez skalar" <<endl;
        cout << "[4] Pochodna" << endl;
        cout << "[5] Przypisz" << endl;
        cout << "[6] Zredukuj wspolcz" << endl;
        cout << "[7] Policz wartosc" << endl;
        cout << "[8] Podaj wspolcz" << endl;
        cout << endl << "[0] Zakoncz" << endl;

        int menu;
        cin >> menu;

        bool quit = false;

        switch (menu)
        {
        case 1:
            {
                Polynomial temp;
                cout<<"Podaj wielomian: ";
                cin.clear();
                cin.ignore();
                cin>>temp;
                cout<<wielo<<" dodaj "<<temp<<endl;
                wielo += temp;
                break;
            }
        case 2:
            {
                Polynomial temp;
                cout<<"Podaj wielomian: ";
                cin.clear();
                cin.ignore();
                cin>>temp;
                cout<<wielo<<" odejmij "<<temp<<endl;
                wielo -= temp;
                break;
            }
        case 3:
            {
                cout<<"Podaj skalar: ";
                int temp;
                cin.clear();
                cin.ignore();
                cin>>temp;
                cout<<temp<<" * ("<<wielo<<")"<<endl;
                wielo *= temp;
                break;
            }
        case 4:
            {
                cout<<wielo<<" dx"<<endl;
                wielo.derivative();
                break;
            }
        case 5:
            {
                cout<<"Podaj wielomian: ";
                cin.clear();
                cin.ignore();
                cin>>wielo;
                break;
            }
        case 6:
            {
                cout<<"zredukuj wspolczynniki"<<endl;
                wielo.reduceFactors();
                break;
            }
        case 7:
            {
                int temp;
                cout<<"Podaj x: ";
                cin.clear();
                cin.ignore();
                cin>>temp;
                cout<<"w("<<temp<<") = "<<wielo.calc(temp)<<endl;
                break;
            }
        case 8:
            {
                int temp;
                cout<<"Podaj wspolczynnik: ";
                cin.clear();
                cin.ignore();
                cin>>temp;
                cout<<"wspolczynnik przy x^"<<temp<<" = "<<wielo.getFactor(temp);
                break;
            }
        case 0:
            {
                quit = true;
                break;
            }
        }

        string e;
        if (Polynomial::checkLastError(e)) cout << endl << e << endl;

        if (quit) break;

        cin.clear();
        cin.ignore();
    }
}
