#include "Polynomial.h"
using namespace std;

int main()
{
    /*Polynomial wielo,wielo2;
    wielo = "2x2 + 2x2 + 3x4 - 5";
    wielo2 = "2x2 + 5x5";

    cout<<wielo<<endl;
    cout<<wielo2<<endl;
    cout<<wielo-wielo2<<endl;
    cout<<wielo<<endl;
    cout<<wielo2<<endl;
    wielo -= wielo2;
    cout<<wielo<<endl;
    cout<<wielo+"7x5"<<endl<<endl;
    cout<<"wielo: "<<wielo<<" d wielo: "<<wielo<<endl;
    cout<<"wielo2: "<<wielo2<<" d wielo2: "<<wielo2<<endl;
    wielo.derivative();
    wielo2.derivative();
    cout<<"wielo: "<<wielo<<" d wielo: "<<wielo<<endl;
    cout<<"wielo2: "<<wielo2<<" d wielo2: "<<wielo2<<endl;*/

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

    /*for (int i = 0; i < MAX_DEGREE + 1; i++)
    {
        //if (wielo.monomial[i] != 0)
        {
            cout << wielo.monomial[i] << "x^" << i << " + ";
        }
    }
    cout<<endl;*/

    return 0;
}
