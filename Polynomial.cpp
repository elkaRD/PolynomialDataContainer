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
}

Polynomial::Polynomial(const int x)
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

int Polynomial::getDegree() const
{
    return polyDegree;
}

int Polynomial::calc(const int x) const
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

int Polynomial::getFactor(const int x) const
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

    for (int i = 0; i < polyDegree + 1; i++)
    {
        for (int j = 0; j < right.polyDegree + 1; j++)
        {
            int newFactor = monomial[i] * right.monomial[j];
            int newDegree = i + j;

            if (newDegree > MAX_DEGREE)
            {
                isError = true;
                errorMsg = "W wyniku mnozenia za wysokie jednomiany zostaly pominiete";
                break;
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

void Polynomial::resetValues()
{
    for (int i = 0; i < MAX_DEGREE + 1; i++)
        monomial[i] = 0;

    polyDegree = 0;
}

void Polynomial::setPolynomial(const string s)
{
    resetValues();

    string curMono = "";

    bool newError = false;
    bool errorChar[s.size()];
    string errorDetails = "";

    for (unsigned int i = 0; i < s.size() + 1; i++)
    {
        if (i != s.size())
        {
            errorChar[i] = false;
        }

        if (i == s.size() || s[i] == '+' || s[i] == '-')
        {
            int result = setMonomial(curMono, newError, errorDetails, i - curMono.size());

            if (result >= 0)
            {
                errorChar[result] = true;
            }

            if (i != s.size())
            {
                curMono = s[i];
            }
        }
        else
        {
            curMono += s[i];
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

int Polynomial::typeOfChar(const char c) const
{
    if (c >= '1' && c <= '9') return CNZ;
    if (c == '0')             return CZ;
    if (c == 'x')             return CX;
    if (c == '+' || c == '-') return CPM;
    if (c == '^')             return CC;

    return CE;
}

int Polynomial::nextState(const int state, const int c, const int i, bool& newError, string& errorDetails) const
{
    if (state == BEG)
    {
        switch (c)
        {
            case CPM: return SPM;
            case CNZ: return SD;
            case CX:  return X;
            case CZ:  return SZ;
            default:
                newError = true;
                errorDetails += "\n   znak " + to_string(i) + ": niepoprawne rozpoczecie jednomianu";
                return SE;
        }
    }
    if (state == SPM)
    {
        switch (c)
        {
            case CNZ: return SD;
            case CX:  return X;
            case CZ:  return SZ;
            default:
                newError = true;
                errorDetails += "\n   znak " + to_string(i) + ": powinna byc liczba";
                return SE;
        }
    }
    if (state == SD)
    {
        switch (c)
        {
            case CZ: case CNZ: return SN;
            case CX:           return X;
            default:
                newError = true;
                errorDetails += "\n   znak " + to_string(i) + ": powinna byc liczba";
                return SE;
        }
    }
    if (state == SN)
    {
        switch (c)
        {
            case CZ: return SN;
            case CX: return X;
            default:
                newError = true;
                errorDetails += "\n   znak " + to_string(i) + ": powinna byc liczba";
                return SE;
        }
    }
    if (state == SZ)
    {
        switch (c)
        {
            case CX: return X;
            default:
                newError = true;
                errorDetails += "\n   znak " + to_string(i) + ": powinien byc x";
                return SE;
        }
    }
    if (state == X)
    {
        switch (c)
        {
            case CC:  return XC;
            case CZ:  return XZ;
            case CNZ: return XP;
            default:
                newError = true;
                errorDetails += "\n   znak " + to_string(i) + ": powinien byc wykladnik";
                return SE;
        }
    }
    if (state == XC)
    {
        switch (c)
        {
            case CNZ: return XP;
            case CZ:  return XZ;
            default:
                newError = true;
                errorDetails += "\n   znak " + to_string(i) + ": powinien byc wykladnik";
                return SE;
        }
    }
    if (state == XP)
    {
        switch (c)
        {
            case CZ: case CNZ: return XP;
            default:
                newError = true;
                errorDetails += "\n   znak " + to_string(i) + ": powinna byc liczba";
                return SE;
        }
    }

    return SE;
}

int Polynomial::setMonomial(const string s, bool& newError, string& errorDetails, const int beginIt)
{
    int state = BEG;
    int beginExp = -1;
    int caret = 0;

    string curValue = "";
    string curDegree = "";

    for (unsigned int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ') continue;

        int c = typeOfChar(s[i]);
        state = nextState(state, c, beginIt + i, newError, errorDetails);

        if ((state == SPM && s[i] == '-') || state == SD || state == SN || state == SZ)
        {
            curValue += s[i];
        }
        if (state == XZ || state == XP)
        {
            curDegree += s[i];
            if (beginExp < 0) beginExp = i;
        }
        if (state == XC)
        {
            caret = i;
        }
        if (state == SE)
        {
            return beginIt + i;
        }
    }

    if (state == BEG)
    {
        int index = beginIt + beginExp;
        if (index < 0) return -1;

        newError = true;
        errorDetails += "\n   znak " + to_string(index) + ": niepoprawny jednomian";
        return beginIt;
    }
    if (state == SPM)
    {
        newError = true;
        errorDetails += "\n   znak " + to_string(beginIt) + ": pojedynczy znak + lub -";
        return beginIt;
    }
    if (state == XC)
    {
        newError = true;
        errorDetails += "\n   znak " + to_string(beginIt + caret) + ": niepoprawne uzycie znaku ^";
        return beginIt + caret;
    }

    if (addMonomial(curValue, curDegree, state))
    {
        newError = true;
        errorDetails += "\n   znak " + to_string(beginIt + beginExp) + ": niepoprawny wykladnik zmiennej x";
        return beginIt + beginExp;
    }

    return -1;
}

int Polynomial::addMonomial(const string curValue, const string curDegree, const int state)
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

    if (state == SD || state == SN || state == XZ)
        monomial[0] +=  value;
    if (state == X)
        monomial[1] += value;
    if (state == XP)
    {
        int degree = stoi(curDegree);
        if (degree >= 0 && degree <= MAX_DEGREE)
        {
            monomial[degree] += value;
        }
        else
        {
            return 1;
        }
    }
    return 0;
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

int Polynomial::greatestCommonDivider(int a, int b) const
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
