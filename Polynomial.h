/*  Projekt 3 PROI - Wielomiany v2
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

template <class T = int>
class Polynomial
{
public:

    Polynomial();
    Polynomial(const std::string s);
    Polynomial(const char* s);
    Polynomial(const Polynomial& poly);
    Polynomial(const T x);

    ~Polynomial();

    void derivative();
    int getDegree() const;
    T calc(const T x) const;
    T getFactor(const int x) const;
    void reduceFactors();

    static bool checkLastError(std::string& getErrorMsg);

    Polynomial<T>& operator = (const Polynomial<T>& right);
    Polynomial<T>& operator += (const Polynomial<T>& right);
    Polynomial<T>& operator -= (const Polynomial<T>& right);

    Polynomial<T>& operator *= (const Polynomial<T>& right);

    template <class T2>
    friend bool operator == (const Polynomial<T2>& left, const Polynomial<T2>& right);
    template <class T2>
    friend bool operator != (const Polynomial<T2>& left, const Polynomial<T2>& right);

    template <class T2>
    friend std::ostream& operator << (std::ostream& out, const Polynomial<T2>& right);
    template <class T2>
    friend std::istream& operator >> (std::istream& in, Polynomial<T2>& right);


private:
    int polyDegree;

    static bool isError;
    static std::string errorMsg;

    class Factor
    {
    public:
        Factor(const int pos);
        Factor();

        T value;
        int degree;
        int precision;

        Factor* next;
        Factor* prev;
    };

    Factor* first = nullptr;
    Factor* last = nullptr;

    Factor* addFactor(const int deg);
    Factor* addFactor(const int deg, Factor** after);
    Factor* addFactor(const int deg, const T value);
    void addToFactor(const int deg, const T value);
    Factor* freeFactor(Factor** temp);
    void clearMemory();

    enum State
    {
        BEG,        //beginning
        SPM,        //single plus minus
        SD,         //single non-zero digit
        SN,         //single number
        DOT,        //single dot
        FR,         //fraction part
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
        CP,         //point
        CE          //different
    };

    enum ModifyMode
    {
        ADD,
        SUBTRACT
    };
    Polynomial& modifyFactors(const Polynomial& right, const ModifyMode mode);

    void resetValues();
    void setPolynomial(const std::string s);
    int typeOfChar(const char c) const;
    int nextState(const int state, const int c, const int i, bool& newError, std::string& errorDetails) const;
    int setMonomial(const std::string s, bool& newError, std::string& errorDetails, const int beginIt);
    int addMonomial(const std::string curValue, const std::string curDegree, const int state, const bool isFraction);
    void checkDegree();
    long long greatestCommonDivider(long long a, long long b) const;
};

template <class T>
bool operator == (const Polynomial<T>& left, const Polynomial<T>& right);
template <class T>
bool operator != (const Polynomial<T>& left, const Polynomial<T>& right);

template <class T>
Polynomial<T> operator + (Polynomial<T> left, const Polynomial<T>& right);
template <class T>
Polynomial<T> operator - (Polynomial<T> left, const Polynomial<T>& right);

template <class T>
Polynomial<T> operator * (Polynomial<T> left, const Polynomial<T>& right);

template <class T>
std::ostream& operator << (std::ostream& out, const Polynomial<T>& right);
template <class T>
std::istream& operator >> (std::istream& in, Polynomial<T>& right);

#endif // POLYNOMIAL_H
