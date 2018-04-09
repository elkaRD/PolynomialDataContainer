/*  Projekt 3 PROI - Wielomiany v2
 *  Robert Dudzinski 2018
 *  main.cpp
 */

#include "Polynomial.h"
#define MODE            double
using namespace std;

void przyklady();
void ui();
void testIterator();

int main()
{
    cout << "   Projekt PROI - Operacje na wielomianach v2" <<endl;
    cout << "   Robert Dudzinski" <<endl;

    Polynomial<int>wielo = Polynomial<int>("2x^9 + 3x^23^1 - 4x-2sa + 8x2 + 7xx ++ x + x2x");
    string e;
    if (Polynomial<int>::checkLastError(e)) cout<<e<<endl;
    cout<<endl<<endl;

    testIterator();
    przyklady();
    ui();

    return 0;
}

void przyklady()
{
    Polynomial<MODE> wielo1;
    Polynomial<MODE> wielo2("x^5 + 3x^4 - 5x^2 + 1");
    Polynomial<MODE> wielo3(wielo2);

    cout<<"w1 empty:        "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"w2 wielo(str):   "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"w3 = wielo(w2):  "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<"w1 == w2:        "<<(wielo1 == wielo2)<<endl;
    cout<<"w2 != w3:        "<<(wielo2 != wielo3)<<endl;
    cout<<"w3 == str:       "<<(wielo2 == Polynomial<MODE>("x^5 + 3x^4 - 5x^2 + 1"))<<endl;
    cout<<endl;

    wielo1 = "-x^3 + 5x^2 + 2";
    wielo2 += wielo1;
    wielo3 = wielo1 - wielo2;

    cout<<"w1 = str:        "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"w2 += w1:        "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"w3 = w1 - w2:    "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    wielo1 += "11x^3-17";
    wielo2 *= 4;
    wielo3.derivative();

    cout<<"w1 += str:   "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"w2 *= 4:     "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"w3 dx:       "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    //wielo1.reduceFactors();
    wielo2 = wielo2 - Polynomial<MODE>("4x5");
    wielo3 -= wielo2;

    cout<<"w1 reduce:       "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"w2 = w2 - str:   "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"w3 -= w2:        "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    cout<<"w1 (1):      "<<wielo1.getDegree()<<",   "<<wielo1.calc(1)<<endl;
    cout<<"w2 (-1):     "<<wielo2.getDegree()<<",   "<<wielo2.calc(-1)<<endl;
    cout<<"w3 (2):      "<<wielo3.getDegree()<<",   "<<wielo3.calc(2)<<endl;
    cout<<endl;

    wielo1 = wielo3 * Polynomial<MODE>(-6);
    wielo2 = Polynomial<MODE>(-6) * wielo3;

    cout<<"w1 = w3 * -6:    "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"w2 = -6 * w3:    "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"w3:              "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    wielo1 = wielo3 - Polynomial<MODE>(10);
    wielo2 = Polynomial<MODE>(-10) + wielo3;

    cout<<"w1 = w3 - 10:    "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"w2 = -10 + w3:   "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"w3:              "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    wielo1 = Polynomial<MODE>(string("2x3 + 3x3 + 4x5 + x2")) + wielo3;
    wielo2 = "2x3 + 3x3 + 4x5 + x2";

    cout<<"w1 = str + w3:   "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"w2 = str:        "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"w3:              "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    string e;
    if (Polynomial<MODE>::checkLastError(e)) cout<<e<<endl;

    wielo1 = "2x^9 + 3x^23^1 - 4x-2sa + 8x2 + 7xx ++ x + x2x";
    if (Polynomial<MODE>::checkLastError(e)) cout<<e<<endl<<endl;

    cout<<"w1 = po bledzie:   "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<endl;

    if (Polynomial<MODE>::checkLastError(e)) cout<<e<<endl;

    wielo1 = "x8+x7+x6+x5+x4+x3+x2+x+1";
    wielo2 = 7;
    //wielo3 = Polynomial<int>(2*wielo1*3 + 2*wielo2);

    cout<<"w1 = str:          "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"w2 = 7:            "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"w3 = 2*w1*3+2*w2:  "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    cout<<"w3: wyraz wolny:     "<<wielo3.getFactor(0)<<endl;
    cout<<"w3: wsp przy x^3:    "<<wielo3.getFactor(3)<<endl;
    cout<<"w3: wsp przy x^9:    "<<wielo3.getFactor(9)<<endl;

    if (Polynomial<MODE>::checkLastError(e)) cout<<e<<endl;
}

void ui()
{
    Polynomial<MODE> wielo;

    while(true)
    {
        cout << endl << endl;
        cout << "Obecny wielomian: " << wielo << endl << endl;
        cout << "[1] Dodaj" << endl;
        cout << "[2] Odejmij" << endl;
        cout << "[3] Pomnoz" <<endl;
        cout << "[4] Pochodna" << endl;
        cout << "[5] Przypisz" << endl;
        //cout << "[6] Zredukuj wspolcz" << endl;
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
                Polynomial<MODE> temp;
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
                Polynomial<MODE> temp;
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
                Polynomial<MODE> temp;
                cout<<"Podaj wielomian: ";
                cin.clear();
                cin.ignore();
                cin>>temp;
                cout<<"("<<temp<<") * ("<<wielo<<")"<<endl;
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
        /*case 6:
            {
                cout<<"zredukuj wspolczynniki"<<endl;
                wielo.reduceFactors();
                break;
            }*/
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
        if (Polynomial<MODE>::checkLastError(e)) cout << endl << e << endl;

        if (quit) break;

        cin.clear();
        cin.ignore();
    }
}

void testIterator()
{
    Polynomial<int> wielo = Polynomial<int>("12x88 + 15x70 + 10x5 + 2x15 - x70 + 3x");

    cout<<endl<<"iterator test: "<<wielo<<endl<<endl;

    for (auto it : wielo)
    {
        it.setValue(it.getValue() + 1);
        cout << it.getValue() << " " << it.getDegree() << ",     ";
    }
    cout << endl;

    Polynomial<int>::iterator it = wielo.begin();
    Polynomial<int>::const_iterator cit = it;

    while (cit != wielo.cend())
    {
        //(*cit).setValue(2);       //error - that's how it supposed to be
        cout << (*cit).getValue() << " " << (*cit).getDegree() << ",    ";
        cit++;
    }

    cout << endl;

    it = it + 2;
    cout << (*it).getValue()<<" "<<(*it).getDegree()<<endl;
    //it = wielo.erase(it);
    (*it).setValue(0);
    cout << (*it).getValue()<<" "<<(*it).getDegree()<<endl;
    cout<<wielo<<endl;

    cout<<endl<<endl<<"end of iterator test"<<endl<<endl;
}
