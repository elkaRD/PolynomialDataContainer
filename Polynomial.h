/*  Projekt 2 PROI - Wielomiany
 *  Robert Dudzinski 2018
 *  Polynomial.h
 */

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <cstdlib>
#include <string>

#define MAX_DEGREE  8

/*
    ZASADA TWORZENIA CIAGU ZNAKOW DO PRZEDSTAWIANIA WIELOMIANOW

    - program pomija spacje
    - jeden string moze zawierac dowolna ilosc jednomianow
    - moze wystapic kilka jednomianow tego samego stopnia; sa wtedy sumowane
    - jednomiany sa oddzielone znakiem + (wyjatek -> czytaj nastepny pkt)
    - jezeli nastepny jednomian jest ujemny nalezy napisac pojedynczy minus (bez znaku + przed minusem)


    PRAWIDLOWY JEDNOMIAN

    [LICZBA_CALK1] x [LICZBA_CALK2]
    lub
    [LICZBA_CALK1] x^ [LICZBA_CALK2]
    lub
    [LICZBA_CALK1] x                            - zmienna x w stopniu pierwszym
    lub
    x                                           - zmienna x w stopniu pierwszym; wspolczynnik wynosi 1
    lub
    -x                                          - zmienna x w stopniu pierwszym; wspolczynnik wynosi -1
    lub
    [LICZBA_CALK]                               - wyraz wolny

    gdzie:
    LICZBA_CALK1 - wspolczynnik przy odpowiedniej potedze x (liczba calkowita o zakresie zmiennej typu int)
    LICZBA_CALK2 - potega do ktorej podniesiony jest x (liczba calkowita z zakresu [0; MAX_DEGREE]

*/

class Polynomial
{
public:

    Polynomial();
    Polynomial(const std::string s);
    Polynomial(const char* s);
    Polynomial(const Polynomial& poly);
    Polynomial(int x);

    void derivative();
    int getDegree();
    int calc(int x);
    int getFactor(int x);
    void reduceFactors();

    static bool checkLastError(std::string& getErrorMsg);

    Polynomial& operator = (const Polynomial& right);

    Polynomial& operator += (const Polynomial& right);
    Polynomial& operator -= (const Polynomial& right);
    Polynomial& operator *= (const Polynomial& right);

    friend bool operator == (const Polynomial& left, const Polynomial& right);
    friend bool operator != (const Polynomial& left, const Polynomial& right);

    friend std::ostream& operator << (std::ostream& out, const Polynomial& right);
    friend std::istream& operator >> (std::istream& in, Polynomial& right);


private:

    int monomial[MAX_DEGREE + 1];
    int polyDegree;

    static bool isError;
    static std::string errorMsg;

    enum State
    {
        BEG,        //beginning
        SPM,        //single plus minus
        SD,         //single non-zero digit
        SN,         //single number
        X,          //single x
        XC,         //x and caret
        XZ,         //x power 0
        XP,         //x power non 0
        SZ,         //single 0
        SE          //state error
    };

    enum CharType
    {
        CPM,        //plus minus
        CNZ,        //non zero digit
        CZ,         //zero digit
        CX,         //x
        CC,         //caret
        CE          //different
    };

    void resetValues();
    void setPolynomial(std::string s);
    int typeOfChar(char c);
    int nextState(int state, int c, int i, bool& newError, std::string& errorDetails);
    int setMonomial(std::string s, bool& newError, std::string& errorDetails, int beginIt);
    int addMonomial(std::string curValue, std::string curDegree, int state, bool& newError, std::string& errorDetails);
    void checkDegree();
    int greatestCommonDivider(int a, int b);
};

bool operator == (const Polynomial& left, const Polynomial& right);
bool operator != (const Polynomial& left, const Polynomial& right);

Polynomial operator + (Polynomial left, const Polynomial& right);
Polynomial operator - (Polynomial left, const Polynomial& right);

Polynomial operator * (Polynomial left, const Polynomial& right);

std::ostream& operator << (std::ostream& out, const Polynomial& right);
std::istream& operator >> (std::istream& in, Polynomial& right);

#endif // POLYNOMIAL_H
