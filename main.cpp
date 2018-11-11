/*  EN: Project on the 2nd semester of CS at Warsaw University of Technology
 *      Polynomial as a data container
 *
 *  PL: Projekt PROI (Programowanie obiektowe) PW WEiTI 18L
 *      Wielomian jako kontener danych
 *
 *  Copyright (C) Robert Dudzinski 2018
 *
 *  File: main.cpp
 */

#include "Polynomial.h"
#include "Examples.h"
using namespace std;

template <class T>
void ui();

int main()
{
    cout << "   EN: Project on the 2nd semester of CS at Warsaw University of Technology" << endl;
    cout << "       Polynomial as a data container" << endl;
    cout << endl;
    cout << "   PL: Projekt PROI (Programowanie obiektowe) PW WEiTI 18L" << endl;
    cout << "       Wielomian jako kontener danych" << endl;
    cout << endl;
    cout << "   Copyright (C) Robert Dudzinski 2018" << endl;

    //testIterator<int>();
    //examples<int>();

    ui<int>();

    return 0;
}

template <class T>
void ui()
{
    Polynomial<T> poly;

    while(true)
    {
        cout << endl << endl;
        cout << "Current polynomial: " << poly << endl << endl;
        cout << "[1] Add" << endl;
        cout << "[2] Subtract" << endl;
        cout << "[3] Multiply" <<endl;
        cout << "[4] Derivative" << endl;
        cout << "[5] Set" << endl;
        cout << "[7] Calculate value" << endl;
        cout << "[8] Get factor value" << endl;
        cout << endl << "[0] Exit" << endl;

        int menu;
        cin >> menu;

        bool quit = false;

        switch (menu)
        {
        case 1:
            {
                Polynomial<T> temp;
                cout<<"Type polynomial: ";
                cin.clear();
                cin.ignore();
                cin>>temp;
                cout<<poly<<" add "<<temp<<endl;
                poly += temp;
                break;
            }
        case 2:
            {
                Polynomial<T> temp;
                cout<<"Type polynomial: ";
                cin.clear();
                cin.ignore();
                cin>>temp;
                cout<<poly<<" subtract "<<temp<<endl;
                poly -= temp;
                break;
            }
        case 3:
            {
                Polynomial<T> temp;
                cout<<"Type polynomial: ";
                cin.clear();
                cin.ignore();
                cin>>temp;
                cout<<"("<<temp<<") * ("<<poly<<")"<<endl;
                poly *= temp;
                break;
            }
        case 4:
            {
                cout<<poly<<" dx"<<endl;
                poly.derivative();
                break;
            }
        case 5:
            {
                cout<<"Override polynomial: ";
                cin.clear();
                cin.ignore();
                cin>>poly;
                break;
            }
        case 7:
            {
                int temp;
                cout<<"Value for x: ";
                cin.clear();
                cin.ignore();
                cin>>temp;
                cout<<"w("<<temp<<") = "<<poly.calc(temp)<<endl;
                break;
            }
        case 8:
            {
                int temp;
                cout<<"Which power of x: ";
                cin.clear();
                cin.ignore();
                cin>>temp;
                cout<<"Factor next to x^"<<temp<<" = "<<poly.getFactor(temp);
                break;
            }
        case 0:
            {
                quit = true;
                break;
            }
        }

        string e;
        if (Polynomial<T>::checkLastError(e)) cout << endl << e << endl;

        if (quit) break;

        cin.clear();
        cin.ignore();
    }
}

