/*  Projekt 3 PROI - Wielomiany v2
 *  Robert Dudzinski 2018
 *  Polynomial.cpp
 */

#include "Polynomial.h"
using namespace std;

template <class T>
bool Polynomial<T>::isError = false;
template <class T>
string Polynomial<T>::errorMsg = "";

template <class T>
Polynomial<T>::Factor::Factor(const int pos)
{
    degree = pos;
    value = 0;
    next = nullptr;
    prev = nullptr;
}

template <class T>
Polynomial<T>::Factor::Factor()
{
    value = 0;
    next = nullptr;
    prev = nullptr;
}

template <class T>
Polynomial<T>::Polynomial ()
{
    resetValues();
}

template <class T>
Polynomial<T>::Polynomial(const char* s)
{
    setPolynomial(s);
}

template <class T>
Polynomial<T>::Polynomial (const string s)
{
    setPolynomial(s);
}

template <class T>
Polynomial<T>::Polynomial(const Polynomial& poly)
{
    *this = poly;
}

template <class T>
Polynomial<T>::Polynomial(const T x)
{
    resetValues();
    addFactor(0, x);
}

template <class T>
Polynomial<T>::~Polynomial()
{
    clearMemory();
}

template <class T>
void Polynomial<T>::derivative()
{
    Factor* cur = first;
    while (cur != nullptr)
    {
        if (cur->degree > 0)
        {
            cur->value = cur->degree * cur->value;
            cur->degree--;

            cur = cur->next;
        }
        else
        {
            cur = freeFactor(&cur);
        }
    }
    checkDegree();
}

template <class T>
int Polynomial<T>::getDegree() const
{
    return polyDegree;
}

template <class T>
T Polynomial<T>::calc(const T x) const
{
    T sum = 0;
    T arg = 1;
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

template <class T>
T Polynomial<T>::getFactor(const int x) const
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

template <class T>
void Polynomial<T>::reduceFactors()
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

template <class T>
bool Polynomial<T>::checkLastError(string& getErrorMsg)
{
    if(isError)
        getErrorMsg = errorMsg;
    else
        getErrorMsg = "";

    bool temp = isError;
    isError = false;
    return temp;
}

template <class T>
Polynomial<T>& Polynomial<T>::modifyFactors(const Polynomial<T>& right, const ModifyMode mode)
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

template <class T>
Polynomial<T>& Polynomial<T>::operator = (Polynomial<T> const &right)
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

template <class T>
Polynomial<T>& Polynomial<T>::operator += (const Polynomial<T>& right)
{
    return modifyFactors(right, ADD);
}

template <class T>
Polynomial<T>& Polynomial<T>::operator -= (const Polynomial<T>& right)
{
    return modifyFactors(right, SUBTRACT);
}

template <class T>
Polynomial<T>& Polynomial<T>::operator *= (const Polynomial<T>& right)
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

template <class T>
typename Polynomial<T>::Factor* Polynomial<T>::addFactor(const int deg)
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

template <class T>
typename Polynomial<T>::Factor* Polynomial<T>::addFactor(const int deg, Polynomial<T>::Factor** after)
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

template <class T>
typename Polynomial<T>::Factor* Polynomial<T>::addFactor(const int deg, const T value)
{
    Factor* temp = addFactor(deg);
    temp->value = value;

    return temp;
}

template <class T>
void Polynomial<T>::addToFactor(const int deg, const T value)
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

template <class T>
typename Polynomial<T>::Factor* Polynomial<T>::freeFactor(Polynomial<T>::Factor** temp)
{
    Factor* prev = (*temp)->prev;
    if (*temp != first || *temp != last)
    {
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
    }
    else
    {
        first = nullptr;
        last = nullptr;
    }

    delete *temp;

    if (prev == nullptr) return first;
    return prev;
}

template <class T>
void Polynomial<T>::clearMemory()
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

template <class T>
void Polynomial<T>::resetValues()
{
    clearMemory();
}

template <class T>
void Polynomial<T>::setPolynomial(const string s)
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

template <class T>
int Polynomial<T>::typeOfChar(const char c) const
{
    if (c >= '1' && c <= '9') return CNZ;
    if (c == '0')             return CZ;
    if (c == 'x')             return CX;
    if (c == '+' || c == '-') return CPM;
    if (c == '^')             return CC;
    if (c == '.')             return CP;

    return CE;
}

template <class T>
int Polynomial<T>::nextState(const int state, const int c, const int i, bool& newError, string& errorDetails) const
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
            case CP:           return DOT;
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
            case CZ: case CNZ: return SN;
            case CX:           return X;
            case CP:           return DOT;
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
            case CP: return DOT;
            default:
                newError = true;
                errorDetails += "\n   znak " + to_string(i) + ": powinien byc x";
                return SE;
        }
    }
    if (state == DOT)
    {
        switch (c)
        {
            case CZ: case CNZ: return FR;
            default:
                newError = true;
                errorDetails += "\n   znak " + to_string(i) + ": brak ulamka";
                return SE;
        }
    }
    if (state == FR)
    {
        switch (c)
        {
            case CZ: case CNZ: return FR;
            case CX:           return X;
            default:
                newError = true;
                errorDetails += "\n   znak " + to_string(i) + ": niepoprawny ulamek";
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

template <class T>
int Polynomial<T>::setMonomial(const string s, bool& newError, string& errorDetails, const int beginIt)
{
    int state = BEG;
    int beginExp = -1;
    int dot = 0;
    int caret = 0;

    string curValue = "";
    string curDegree = "";

    for (unsigned int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ') continue;

        int c = typeOfChar(s[i]);
        state = nextState(state, c, beginIt + i, newError, errorDetails);

        if ((state == SPM && s[i] == '-') || state == SD || state == SN || state == SZ || state == DOT || state == FR)
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
        if (state == DOT)
        {
            dot = i;
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
    if (state == DOT)
    {
        newError = true;
        errorDetails += "\n   znak " + to_string(beginIt + dot) + ": niepoprawny ulamek";
        return beginIt + dot;
    }

    if (addMonomial(curValue, curDegree, state, dot))
    {
        newError = true;
        errorDetails += "\n   znak " + to_string(beginIt + beginExp) + ": niepoprawny wykladnik zmiennej x";
        return beginIt + beginExp;
    }

    return -1;
}

template <class T>
int Polynomial<T>::addMonomial(const string curValue, const string curDegree, const int state, const bool isFraction)
{
    long long valueLL = 0;
    long double valueLD = 0;
    if (curValue.size() == 0)
    {
        valueLL = 1;
        valueLD = 1;
    }
    else if (curValue.size() == 1 && curValue[0] == '-')
    {
        valueLL = -1;
        valueLD = -1;
    }
    else
    {
        if (!isFraction) valueLL = stoll(curValue);
        else             valueLD = stold(curValue);
    }

    if (state == SD || state == SN || state == XZ || state == FR)
    {
        if (!isFraction) addToFactor(0, valueLL);
        else             addToFactor(0, valueLD);
    }
    if (state == X)
    {
        if (!isFraction) addToFactor(1, valueLL);
        else             addToFactor(1, valueLD);
    }
    if (state == XP)
    {
        int degree = stoi(curDegree);

        if (degree >= 0)
        {
            if (!isFraction) addToFactor(degree, valueLL);
            else             addToFactor(degree, valueLD);
        }
        else return 1;
    }
    return 0;
}

template <class T>
void Polynomial<T>::checkDegree()
{
    if (last != nullptr)
        polyDegree=last->degree;
    else
        polyDegree = 0;
}

template <class T>
long long Polynomial<T>::greatestCommonDivider(long long a, long long b) const
{
    /*int maxPow = 0;        // prototype for fraction numbers; currently only for integers
    Factor* cur = first;
    while (cur != nullptr)
    {
        int i;
        long double temp = cur->value;
        for (i = 0; temp - (long long)temp != 0; i++)
        {
            temp *= 10;
        }
        if (i > maxPow) maxPow = i;

        cur = cur->next;
    }

    for (int i = 0; i < maxPow; i++)
    {
        a *= 10;
        b *= 10;
    }*/

    if (a < 0) a *= -1;
    if (b < 0) b *= -1;

    while (b != 0)
    {
        long long c = a % b;
        a = b;
        b = c;
    }
    return a;
}

template <class T>
bool operator == (const Polynomial<T>& left, const Polynomial<T>& right)
{
    class Polynomial<T>::Factor* curL = left.first;
    class Polynomial<T>::Factor* curR = right.first;

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

template <class T>
bool operator != (const Polynomial<T>& left, const Polynomial<T>& right)
{
    return !(left == right);
}

template <class T>
Polynomial<T> operator + (Polynomial<T> left, const Polynomial<T>& right)
{
    return left += right;
}

template <class T>
Polynomial<T> operator - (Polynomial<T> left, const Polynomial<T>& right)
{
    return left -= right;
}

template <class T>
Polynomial<T> operator * (Polynomial<T> left, const Polynomial<T>& right)
{
    return left *= right;
}

template <class T>
ostream& operator << (ostream& out, const Polynomial<T>& right)
{
    bool isFirst = true;

    class Polynomial<T>::Factor* cur = right.last;
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

template <class T>
istream& operator >> (istream& in, Polynomial<T>& right)
{
    string temp;
    in >> temp;
    right.setPolynomial(temp);
    return in;
}

template <class T>
typename Polynomial<T>::iterator Polynomial<T>::begin() const
{
    iterator it;
    it.ptr = first;
    return it;
};

template <class T>
typename Polynomial<T>::iterator Polynomial<T>::end() const
{
    iterator it;
    it.ptr = last;
    return it;
};

template <class T>
typename Polynomial<T>::iterator& Polynomial<T>::iterator::operator ++ (int)
{
    if (ptr != nullptr)
    {
        prevPtr = ptr;
        ptr = ptr->next;
        isBegin = true;
    }
    else if (!isBegin) ptr = prevPtr;
    return *this;
}

template <class T>
typename Polynomial<T>::iterator& Polynomial<T>::iterator::operator -- (int)
{
    if (ptr != nullptr)
    {
        prevPtr = ptr;
        ptr = ptr->prev;
        isBegin = false;
    }
    else if (isBegin) ptr = prevPtr;
    return *this;
}

template <class T>
typename Polynomial<T>::iterator& Polynomial<T>::iterator::operator = (const class Polynomial<T>::iterator& right)
{
    ptr = right.ptr;
    return *this;
}

template <class T>
const class Polynomial<T>::Factor* Polynomial<T>::iterator::operator -> () const
{
    return ptr;
}

template <class T>
bool Polynomial<T>::iterator::operator == (const class Polynomial<T>::iterator& right) const
{
    return ptr == right.ptr;
}

template <class T>
bool Polynomial<T>::iterator::operator != (const class Polynomial<T>::iterator& right) const
{
    return ptr != right.ptr;
}

template <class T>
bool Polynomial<T>::iterator::operator == (std::nullptr_t) const
{
    return ptr == nullptr;
}

template <class T>
bool Polynomial<T>::iterator::operator != (std::nullptr_t) const
{
    return ptr != nullptr;
}

template class Polynomial<int>;
template ostream& operator << <int>(ostream& out, const Polynomial<int>& right);
template std::istream& operator >> (std::istream& in, Polynomial<int>& right);
template bool operator == (const Polynomial<int>& left, const Polynomial<int>& right);
template bool operator != (const Polynomial<int>& left, const Polynomial<int>& right);
template Polynomial<int> operator + (Polynomial<int> left, const Polynomial<int>& right);
template Polynomial<int> operator - (Polynomial<int> left, const Polynomial<int>& right);
template Polynomial<int> operator * (Polynomial<int> left, const Polynomial<int>& right);

template class Polynomial<long long>;
template ostream& operator << <long long>(ostream& out, const Polynomial<long long>& right);
template std::istream& operator >> (std::istream& in, Polynomial<long long>& right);
template bool operator == (const Polynomial<long long>& left, const Polynomial<long long>& right);
template bool operator != (const Polynomial<long long>& left, const Polynomial<long long>& right);
template Polynomial<long long> operator + (Polynomial<long long> left, const Polynomial<long long>& right);
template Polynomial<long long> operator - (Polynomial<long long> left, const Polynomial<long long>& right);
template Polynomial<long long> operator * (Polynomial<long long> left, const Polynomial<long long>& right);

template class Polynomial<float>;
template ostream& operator << <float>(ostream& out, const Polynomial<float>& right);
template std::istream& operator >> (std::istream& in, Polynomial<float>& right);
template bool operator == (const Polynomial<float>& left, const Polynomial<float>& right);
template bool operator != (const Polynomial<float>& left, const Polynomial<float>& right);
template Polynomial<float> operator + (Polynomial<float> left, const Polynomial<float>& right);
template Polynomial<float> operator - (Polynomial<float> left, const Polynomial<float>& right);
template Polynomial<float> operator * (Polynomial<float> left, const Polynomial<float>& right);

template class Polynomial<double>;
template ostream& operator << <double>(ostream& out, const Polynomial<double>& right);
template std::istream& operator >> (std::istream& in, Polynomial<double>& right);
template bool operator == (const Polynomial<double>& left, const Polynomial<double>& right);
template bool operator != (const Polynomial<double>& left, const Polynomial<double>& right);
template Polynomial<double> operator + (Polynomial<double> left, const Polynomial<double>& right);
template Polynomial<double> operator - (Polynomial<double> left, const Polynomial<double>& right);
template Polynomial<double> operator * (Polynomial<double> left, const Polynomial<double>& right);
