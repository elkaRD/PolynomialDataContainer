/*  Projekt 2 PROI - Wielomiany
 *  Robert Dudzinski 2018
 *  Polynomial.cpp
 */

#include "Polynomial.h"
using namespace std;

Polynomial::Polynomial ()
{
    resetValues();
}

Polynomial::Polynomial (string s)
{
    setPolynomial(s);
}

Polynomial::Polynomial(const Polynomial& poly)
{
    for (int i = 0; i < MAX_DEGREE + 1; i++)
    {
        monomial[i] = poly.monomial[i];
    }
    checkDegree();
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

void Polynomial::reduceFactors()
{
    bool isBegin = true;
    int gcd;

    for (int i = 0; i < MAX_DEGREE + 1; i++)
    {
        if (monomial[i] != 0)
        {
            if (isBegin)
            {
                isBegin = false;
                gcd = monomial[i];
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

inline bool Polynomial::operator == (const Polynomial& right) const
{
    for (int i = 0; i < MAX_DEGREE + 1; i++)
    {
        if (monomial[i] != right.monomial[i])
            return false;
    }
    return true;
}

inline bool Polynomial::operator != (const Polynomial& right) const
{
    return !(*this == right);
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

Polynomial& Polynomial::operator = (string const &right)
{
    setPolynomial(right);
    return *this;
}

Polynomial& Polynomial::operator = (const int& right)
{
    resetValues();
    monomial[0] = right;
    polyDegree = 1;
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

Polynomial& Polynomial::operator += (const string& right)
{
    Polynomial temp(right);
    *this += temp;

    return *this;
}

Polynomial& Polynomial::operator -= (const string& right)
{
    Polynomial temp(right);
    *this -= temp;

    return *this;
}

Polynomial& Polynomial::operator += (const int& right)
{
    monomial[0] += right;
    checkDegree();
    return *this;
}

Polynomial& Polynomial::operator -= (const int& right)
{
    monomial[0] -= right;
    checkDegree();
    return *this;
}

Polynomial& Polynomial::operator *= (const int& right)
{
    for (int i = 0; i < MAX_DEGREE + 1; i++)
    {
        monomial[i] *= right;
    }
    checkDegree();
    return *this;
}

Polynomial operator + (Polynomial left, const Polynomial& right)
{
    return left += right;
}

Polynomial operator - (Polynomial left, const Polynomial& right)
{
    return left -= right;
}

Polynomial operator + (Polynomial left, const string& right)
{
    return left += right;
}

Polynomial operator - (Polynomial left, const string& right)
{
    return left -= right;
}

Polynomial operator + (Polynomial left, const int& right)
{
    return left += right;
}

Polynomial operator - (Polynomial left, const int& right)
{
    return left -= right;
}

Polynomial operator * (Polynomial left, const int& right)
{
    return left *= right;
}

Polynomial operator + (const std::string& left, Polynomial right)
{
    return right += left;
}

Polynomial operator - (const std::string& left, Polynomial right)
{
    return right -= left;
}

Polynomial operator + (const int& left, Polynomial right)
{
    return right += left;
}

Polynomial operator - (const int& left, Polynomial right)
{
    return right -= left;
}

Polynomial operator * (const int& left, Polynomial right)
{
    return right *= left;
}

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
    return out;
}

istream& operator >> (istream& in, Polynomial& right)
{
    string temp;
    in >> temp;
    right.setPolynomial(temp);
    return in;
}

void Polynomial::resetValues()
{
    for (int i = 0; i < MAX_DEGREE + 1; i++)
        monomial[i] = 0;

    polyDegree = 0;
    isError = false;
}

void Polynomial::setPolynomial(string s)
{
    resetValues();

    string curDegree;
    string curValue;

    bool isValue = true;
    bool isCorrect = true;
    bool wasCaret = false;
    bool newError = false;
    string errorDetails = "";

    for (unsigned int i = 0; i < s.size() + 1; i++)
    {
        if (i != s.size())
        {
            if (s[i] == ' ') continue;

            if (s[i] == 'x')
            {
                isValue = false;
                continue;
            }

            if (s[i] == '^')
            {
                if (isValue || curDegree.size() != 0 || wasCaret)
                {
                    isCorrect = false;
                    newError = true;

                    errorDetails += "\n   znak" + to_string(i) + ": niepoprawny znak ^";
                }
                wasCaret = true;
                continue;
            }
        }

        if (i == s.size() || s[i] == '+' || s[i] == '-')
        {
            if (isCorrect)
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
                        newError = true;
                        errorDetails += "\n   znak" + to_string(i) + ": niepoprawny wykladnik zmiennej x";
                    }
                }
            }

            isValue = true;
            isCorrect = true;
            wasCaret = false;

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
                errorDetails += "\n   znak" + to_string(i) + ": znak nie jest cyfra";
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
        errorMsg = "Blad wczytywania wielomianu " + s + "; niepoprawne jednomiany zostaly pominiete" + errorDetails;
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
