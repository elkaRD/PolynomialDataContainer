/*  Projekt 2 PROI - Wielomiany
 *  Robert Dudzinski 2018
 *  Polynomial.cpp
 */

#include "Polynomial.h"
using namespace std;

bool Polynomial::isError = false;
string Polynomial::errorMsg = "";

Polynomial::Polynomial ()
{
    resetValues();
}

Polynomial::Polynomial(const char* s)
{
    setPolynomial(s);
}

Polynomial::Polynomial (const string s)
{
    setPolynomial(s);
}

Polynomial::Polynomial(const Polynomial& poly)
{
    for (int i = 0; i < MAX_DEGREE + 1; i++)
    {
        monomial[i] = poly.monomial[i];
    }
    polyDegree = poly.polyDegree;
    //checkDegree();
}

Polynomial::Polynomial(int x)
{
    resetValues();
    monomial[0] = x;
}

void Polynomial::derivative()
{
    for (int i = 0; i < MAX_DEGREE; i++)
    {
        monomial[i] = monomial[i+1] * (i + 1);
    }
    monomial[MAX_DEGREE] = 0;
    checkDegree();
}

int Polynomial::getDegree()
{
    return polyDegree;
}

int Polynomial::calc(int x)
{
    int sum = 0;
    int arg = 1;

    for (int i = 0; i < MAX_DEGREE + 1; i++)
    {
        sum += arg * monomial[i];
        arg *= x;
    }

    return sum;
}

int Polynomial::getFactor(int x)
{
    if (x >= 0 && x<= MAX_DEGREE)
    {
        return monomial[x];
    }
    else
    {
        isError = true;
        errorMsg = "Blad: Proba odczytania nieistniejacego wspolczynnika";
    }
    return 0;
}

void Polynomial::reduceFactors()
{
    bool isBegin = true;
    int gcd = 1;

    for (int i = 0; i < MAX_DEGREE + 1; i++)
    {
        if (monomial[i] != 0)
        {
            if (isBegin)
            {
                isBegin = false;
                gcd = monomial[i];
                if (gcd < 0) gcd *= -1;
            }
            else
            {
                gcd = greatestCommonDivider(gcd, monomial[i]);
            }
        }
    }

    for (int i = 0; i < MAX_DEGREE + 1; i++)
    {
        monomial[i] /= gcd;
    }
}

bool Polynomial::checkLastError(string& getErrorMsg)
{
    if(isError)
        getErrorMsg = errorMsg;
    else
        getErrorMsg = "";

    bool temp = isError;
    isError = false;
    return temp;
}

Polynomial& Polynomial::operator = (Polynomial const &right)
{
    for (int i = 0; i < MAX_DEGREE + 1; i++)
    {
        monomial[i] = right.monomial[i];
    }
    checkDegree();
    return *this;
}

Polynomial& Polynomial::operator += (const Polynomial& right)
{
    for (int i = 0; i < MAX_DEGREE + 1; i++)
    {
        monomial[i] += right.monomial[i];
    }
    checkDegree();
    return *this;
}

Polynomial& Polynomial::operator -= (const Polynomial& right)
{
    for (int i = 0; i < MAX_DEGREE + 1; i++)
    {
        monomial[i] -= right.monomial[i];
    }
    checkDegree();
    return *this;
}

Polynomial& Polynomial::operator *= (const Polynomial& right)
{
    Polynomial temp;

    for (int i = 0; i < MAX_DEGREE + 1; i++)
    {
        for (int j = 0; j < MAX_DEGREE + 1; j++)
        {
            int newFactor = monomial[i] * right.monomial[j];
            int newDegree = i + j;

            if (newDegree > MAX_DEGREE && newFactor != 0)
            {
                isError = true;
                errorMsg = "W wyniku mnozenia za wysokie jednomiany zostaly pominiete";
            }
            else
            {
                temp.monomial[newDegree] += newFactor;
            }
        }
    }

    temp.checkDegree();
    *this = temp;
    return *this;
}

/*Polynomial& Polynomial::operator *= (const int& right)
{
    for (int i = 0; i < MAX_DEGREE + 1; i++)
    {
        monomial[i] *= right;
    }
    checkDegree();
    return *this;
}*/

void Polynomial::resetValues()
{
    for (int i = 0; i < MAX_DEGREE + 1; i++)
        monomial[i] = 0;

    polyDegree = 0;
}

void Polynomial::setPolynomial(string s)
{
    resetValues();

    string curDegree;
    string curValue;

    bool isValue = true;
    bool isCorrect = true;
    bool isFirstChar = true;
    bool hFirstChar = true;
    bool wasCaret = false;
    bool wasX = false;
    bool newError = false;
    string errorDetails = "";
    bool errorChar[s.size()];

    for (unsigned int i = 0; i < s.size() + 1; i++)
    {
        if (i != s.size())
        {
            errorChar[i] = false;
            isFirstChar = hFirstChar;

            if (s[i] == ' ') continue;
            else hFirstChar = false;

            if (isFirstChar && !hFirstChar && s[i] != '+' && s[i] != '-')
                isFirstChar = false;

            if (s[i] == 'x')
            {
                if (wasX)
                {
                    isCorrect = false;
                    newError = true;
                    errorChar[i] = true;

                    errorDetails += "\n   znak " + to_string(i) + ": znak x wystapil juz w tym jednomianie";
                }

                wasX = true;
                isValue = false;
                continue;
            }

            if (s[i] == '^')
            {
                if (isValue || curDegree.size() != 0 || wasCaret)
                {
                    isCorrect = false;
                    newError = true;
                    errorChar[i] = true;

                    errorDetails += "\n   znak " + to_string(i) + ": niepoprawne uzycie znaku ^";
                }
                wasCaret = true;
                continue;
            }
        }

        if (i == s.size() || s[i] == '+' || s[i] == '-')
        {
            if ((curValue.size() == 0 || curValue.compare("-") == 0) && curDegree.size() == 0 && !wasX && i != 0)
            {
                int index = i<1 ? 0 : i-1;
                //int index=i;
                isCorrect = false;
                newError = true;
                errorChar[index] = true;
                errorDetails += "\n   znak " + to_string(index) + ": pojedynczy znak + lub -";
            }

            if (isCorrect && !isFirstChar)
            {
                int value;
                if (curValue.size() == 0)
                {
                    value = 1;
                }
                else if (curValue.size() == 1 && curValue[0] == '-')
                {
                    value = -1;
                }
                else
                {
                    value = stoi(curValue);
                }

                if (isValue)
                    monomial[0] +=  value;
                else
                {
                    int degree;
                    if (curDegree.size() == 0) degree = 1;
                    else degree = stoi(curDegree);

                    if (degree >= 0 && degree <= MAX_DEGREE)
                    {
                        monomial[degree] += value;
                    }
                    else
                    {
                        int index = i-1<0 ? 0 : i-1;
                        newError = true;
                        errorChar[index] = true;
                        errorDetails += "\n   znak " + to_string(index) + ": niepoprawny wykladnik zmiennej x";
                    }
                }
            }

            isValue = true;
            isCorrect = true;
            wasCaret = false;
            wasX = false;

            curDegree.clear();
            curValue.clear();

            if (i != s.size() && s[i] == '-') curValue = "-";
            continue;
        }

        if (i != s.size())
        {
            if (!(s[i] >= '0' && s[i] <= '9'))
            {
                isCorrect = false;
                newError = true;
                errorChar[i] = true;
                errorDetails += "\n   znak " + to_string(i) + ": znak nie jest cyfra";
            }

            if (isValue)
                curValue += s[i];
            else
                curDegree += s[i];
        }
    }
    checkDegree();

    if (newError)
    {
        isError = true;
        errorMsg = "Blad wczytywania wielomianu \"" + s + "\"\n";
        errorMsg+= "              Bledne znaki:  ";
        for (unsigned int i = 0; i < s.size(); i++)
        {
            if (errorChar[i]) errorMsg += "^";
            else errorMsg += "-";
        }
        errorMsg += errorDetails + "\nNiepoprawne jednomiany zostaly pominiete.";
    }
}

void Polynomial::checkDegree()
{
    for (int i = MAX_DEGREE; i >= 0; i--)
    {
        if (monomial[i] != 0)
        {
            polyDegree = i;
            return;
        }
    }
    polyDegree = 0;
}

int Polynomial::greatestCommonDivider(int a, int b)
{
    if (a < 0) a *= -1;
    if (b < 0) b *= -1;

    while (b != 0)
    {
        int c = a % b;
        a = b;
        b = c;
    }
    return a;
}

bool operator == (const Polynomial& left, const Polynomial& right)
{
    for (int i = 0; i < MAX_DEGREE + 1; i++)
    {
        if (left.monomial[i] != right.monomial[i])
            return false;
    }
    return true;
}

bool operator != (const Polynomial& left, const Polynomial& right)
{
    return !(left == right);
}

Polynomial operator + (Polynomial left, const Polynomial& right)
{
    return left += right;
}

Polynomial operator - (Polynomial left, const Polynomial& right)
{
    return left -= right;
}

Polynomial operator * (Polynomial left, const Polynomial& right)
{
    return left *= right;
}

/*Polynomial operator * (Polynomial left, const int& right)
{
    return left *= right;
}

Polynomial operator * (const int& left, Polynomial right)
{
    return right *= left;
}*/

ostream& operator << (ostream& out, const Polynomial& right)
{
    bool isFirst = true;
    for (int i = MAX_DEGREE; i >= 0; i--)
    {
        if (right.monomial[i] != 0)
        {
            if (!isFirst) out << " ";
            if (!isFirst && right.monomial[i] > 0) out << "+ ";

            if (i == 0) out << right.monomial[i];
            else
            {
                if (right.monomial[i] != 1 && right.monomial[i] != -1)
                    out << right.monomial[i];
                else if (right.monomial[i] == -1)
                    out << "-";

                out << "x";
                if (i != 1) out << "^" << i;
            }
            isFirst = false;
        }
    }
    if (right.polyDegree == 0 && right.monomial[0] == 0)
        out << "0";

    return out;
}

istream& operator >> (istream& in, Polynomial& right)
{
    string temp;
    in >> temp;
    right.setPolynomial(temp);
    return in;
}
