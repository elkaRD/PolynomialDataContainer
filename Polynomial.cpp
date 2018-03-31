/*  Projekt 2 PROI - Wielomiany
 *  Robert Dudzinski 2018
 *  Polynomial.cpp
 */

#include "Polynomial.h"
using namespace std;

bool Polynomial::isError = false;
string Polynomial::errorMsg = "";

Polynomial::Factor::Factor(const int pos)
{
    degree = pos;
    value = 0;
    next = nullptr;
    prev = nullptr;
}

Polynomial::Factor::Factor()
{
    value = 0;
    next = nullptr;
    prev = nullptr;
}

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
    *this = poly;
}

Polynomial::Polynomial(const int x)
{
    resetValues();
    addFactor(0, x);
}

Polynomial::~Polynomial()
{
    clearMemory();
}

void Polynomial::derivative()
{
    Factor* cur = first;
    while (cur != nullptr)
    {
        if (cur->degree > 0)
        {
            cur->value = cur->degree * cur->value;
            cur->degree--;
        }
        else
        {
            freeFactor(&cur);
        }

        cur = cur->next;
    }
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
    int prevPower = 0;

    Factor* cur = first;
    while (cur != nullptr)
    {
        int addPower = cur->degree - prevPower;
        prevPower = cur->degree;

        for (int i = 0; i < addPower; i++)
            arg *= x;

        sum += arg * cur->value;

        cur = cur->next;
    }

    return sum;
}

int Polynomial::getFactor(const int x) const
{
    if (x >= 0)
    {
        Factor* cur = first;
        while (cur != nullptr)
        {
            if (cur->degree == x) return cur->value;
            if (cur->degree > x) return 0;

            cur = cur->next;
        }
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

    Factor* cur = first;
    while (cur != nullptr)
    {
        if (cur->value != 0)
        {
            if (isBegin)
            {
                isBegin = false;
                gcd = cur->value;
                if (gcd < 0) gcd *= -1;
            }
            else
            {
                gcd = greatestCommonDivider(gcd, cur->value);
            }
        }

        cur = cur->next;
    }

    cur = first;
    while (cur != nullptr)
    {
        cur->value /= gcd;
        cur = cur->next;
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

Polynomial& Polynomial::modifyFactors(const Polynomial& right, const ModifyMode mode)
{
    Factor* curL = first;
    Factor* curR = right.first;
    while (curR != nullptr)
    {
        if (curL != nullptr)
        {
            while (curL != nullptr && curR->degree > curL->degree)
            {
                curL = curL->next;
            }
            if (curL == nullptr)
            {
                curL = addFactor(curR->degree);
            }
            else if (curL->degree > curR->degree)
            {
                curL = addFactor(curR->degree, &curL);
            }
        }
        else
        {
            curL = addFactor(curR->degree);
        }
        if (mode == ADD)
            curL->value += curR->value;
        else if (mode == SUBTRACT)
            curL->value -= curR->value;

        if (curL->value == 0)
        {
            curL = freeFactor(&curL);
        }

        curR = curR->next;
    }
    checkDegree();

    return *this;
}

Polynomial& Polynomial::operator = (Polynomial const &right)
{
    clearMemory();

    Factor* curR = right.first;
    while (curR != nullptr)
    {
        addFactor(curR->degree, curR->value);

        curR = curR->next;
    }
    polyDegree = right.polyDegree;

    return *this;
}

Polynomial& Polynomial::operator += (const Polynomial& right)
{
    return modifyFactors(right, ADD);
}

Polynomial& Polynomial::operator -= (const Polynomial& right)
{
    return modifyFactors(right, SUBTRACT);
}

Polynomial& Polynomial::operator *= (const Polynomial& right)
{
    Polynomial temp;

    Factor* curL = first;
    while (curL != nullptr)
    {
        Factor* curR = right.first;
        while (curR != nullptr)
        {
            temp.addToFactor(curL->degree + curR->degree, curL->value * curR->value);

            curR = curR->next;
        }

        curL = curL->next;
    }

    curL = temp.first;
    while (curL != nullptr)
    {
        if (curL->value == 0) curL = freeFactor(&curL);
        if (curL != nullptr) curL = curL->next;
    }

    temp.checkDegree();
    *this = temp;
    return *this;
}

Polynomial::Factor* Polynomial::addFactor(const int deg)
{
    if (first == nullptr)
    {
        first = last = new Factor(deg);
        return first;
    }

    Factor* temp = last;
    last = temp->next = new Factor(deg);
    last->prev = temp;

    return last;
}

Polynomial::Factor* Polynomial::addFactor(const int deg, Polynomial::Factor** after)
{
    Factor* temp = (*after)->prev;

    if (temp == nullptr)
    {
        first = new Factor(deg);
        first->next = *after;
        (*after)->prev = first;

        return first;
    }

    temp->next = (*after)->prev = new Factor(deg);
    temp->next->prev = temp;
    temp->next->next = *after;

    return temp->next;
}

Polynomial::Factor* Polynomial::addFactor(const int deg, const int value)
{
    Factor* temp = addFactor(deg);
    temp->value = value;

    return temp;
}

void Polynomial::addToFactor(const int deg, const int value)
{
    if (first == nullptr)
    {
        first = last = new Factor(deg);
        first->value += value;
        return;
    }

    for (Factor* cur = first; cur != nullptr; cur = cur->next)
    {
        if (cur->degree == deg)
        {
            cur->value += value;
            return;
        }
        if (cur->degree > deg)
        {
            Factor* newFactor = new Factor(deg);
            Factor* prev = cur->prev;

            if (prev != NULL)
            {
                prev->next = newFactor;
            }
            else
            {
                first = newFactor;
            }
            cur->prev = newFactor;

            newFactor->prev = prev;
            newFactor->next = cur;

            newFactor->value += value;
            return;
        }
    }

    Factor* prev = last;
    prev->next = new Factor(deg);
    prev->next->prev = prev;
    last = prev->next;

    last->value += value;
}

Polynomial::Factor* Polynomial::freeFactor(Polynomial::Factor** temp)
{
    Factor* prev = (*temp)->prev;
    if (prev == nullptr)
    {
        first = (*temp)->next;
        first->prev = nullptr;
    }
    else
    {
        prev->next = (*temp)->next;
    }

    if ((*temp)->next == nullptr)
    {
        last = prev;
        last->next = nullptr;
    }
    else
    {
        (*temp)->next->prev = prev;
    }

    delete *temp;

    if (prev == nullptr) return first;
    return prev;
}

void Polynomial::clearMemory()
{
    Factor* temp = first;
    while (first != nullptr)
    {
        temp = first;
        first = first->next;
        delete temp;
    }
    first = nullptr;
    last = nullptr;
    polyDegree = 0;
}

void Polynomial::resetValues()
{
    clearMemory();
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
    {
        addToFactor(0, value);
    }
    if (state == X)
    {
        addToFactor(1, value);
    }
    if (state == XP)
    {
        int degree = stoi(curDegree);

        if (degree >= 0)
        {
            addToFactor(degree, value);
        }
        else return 1;
    }
    return 0;
}

void Polynomial::checkDegree()
{
    if (last != nullptr)
        polyDegree=last->degree;
    else
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
    Polynomial::Factor* curL = left.first;
    Polynomial::Factor* curR = right.first;

    while (curL != nullptr && curR != nullptr)
    {
        if (curL->degree != curR->degree) return false;
        if (curL->value != curR->value) return false;

        curL = curL->next;
        curR = curR->next;
    }

    if ((curL == nullptr) ^ (curR == nullptr)) return false;

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

    Polynomial::Factor* cur = right.last;
    while (cur != nullptr)
    {
        if (cur->value != 0)
        {
            if (!isFirst) out << " ";
            if (!isFirst && cur->value > 0) out << "+ ";

            if (cur->degree == 0) out << cur->value;
            else
            {
                if (cur->value != 1 && cur->value != -1)
                    out << cur->value;
                else if (cur->value == -1)
                    out << "-";

                out << "x";
                if (cur->degree != 1) out << "^" << cur->degree;
            }
            isFirst = false;
        }

        cur = cur->prev;
    }
    if (right.polyDegree == 0 && right.first != nullptr && right.first->degree == 0 && right.first->value == 0)
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
