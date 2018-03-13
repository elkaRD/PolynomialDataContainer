/*  Projekt 2 PROI - Wielomiany
 *  Robert Dudzinski 2018
 *  main.cpp
 */

#include "Polynomial.h"
using namespace std;

int main()
{
    Polynomial wielo1;
    Polynomial wielo2("x^5 + 3x^4 - 5x^2 + 1");
    Polynomial wielo3(wielo2);

    cout<<"wielo1: "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"wielo2: "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"wielo3: "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    wielo1 = "-x^3 + 5x^2 + 2";
    wielo2 += wielo1;
    wielo3 = wielo1 - wielo2;

    cout<<"wielo1:                  "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"wielo2+=wielo1:          "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"wielo3=wielo1-wielo2:    "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    wielo1 += "11x^3-18";
    wielo2 *= 4;
    wielo3.derivative();

    cout<<"wielo1:      "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"wielo2*=4:   "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"wielo3 dx:   "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    wielo1.reduceFactors();
    wielo2 = wielo2 - "4x5";
    wielo3 -= wielo2;

    cout<<"wielo1 reduce:   "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"wielo2:          "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"wielo3-=wielo2:  "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    cout<<"wielo1 (1):  "<<wielo1.getDegree()<<",   "<<wielo1.calc(1)<<endl;
    cout<<"wielo2 (-1): "<<wielo2.getDegree()<<",   "<<wielo2.calc(-1)<<endl;
    cout<<"wielo3 (2):  "<<wielo3.getDegree()<<",   "<<wielo3.calc(2)<<endl;
    cout<<endl;

    wielo1 = wielo3 * 6;
    wielo2 = 6 * wielo3;

    cout<<"wielo1=wielo3*6:     "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"wielo2=6*wielo3:     "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"wielo3:              "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    wielo1 = wielo3 - 10;
    wielo2 = -10 + wielo3;

    cout<<"wielo1=wielo3-10:    "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"wielo2=-10+wielo3:   "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"wielo3:              "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    wielo1 = "2x3 + 3x3 + 4x5 + x2" + wielo3;
    wielo2 = "2x3 + 3x3 + 4x5 + x2";

    cout<<"wielo1: "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"wielo2: "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"wielo3: "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    string e;
    if (Polynomial::checkLastError(e)) cout<<e<<endl;

    wielo1 = "2x^9 + 3x2^3^ - 4x-2sadf + 8x2 + 7xx + x + x2x";
    if (Polynomial::checkLastError(e)) cout<<e<<endl<<endl;

    cout<<"wielo1: "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<endl;

    if (Polynomial::checkLastError(e)) cout<<e<<endl;

    wielo1 = "x8+x7+x6+x5+x4+x3+x2+x+1";
    wielo2 = 7;
    wielo3 = 2*wielo1*3 + 2*wielo2;

    cout<<"wielo1: "<<wielo1.getDegree()<<",   "<<wielo1<<endl;
    cout<<"wielo2: "<<wielo2.getDegree()<<",   "<<wielo2<<endl;
    cout<<"wielo3: "<<wielo3.getDegree()<<",   "<<wielo3<<endl;
    cout<<endl;

    if (Polynomial::checkLastError(e)) cout<<e<<endl;

    return 0;
}
