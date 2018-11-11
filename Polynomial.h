/*  EN: Project on the 2nd semester of CS at Warsaw University of Technology
 *      Polynomial as a data container
 *
 *  PL: Projekt PROI (Programowanie obiektowe) PW WEiTI 18L
 *      Wielomian jako kontener danych
 *
 *  Copyright (C) Robert Dudzinski 2018
 *
 *  File: Polynomial.h
 */

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

/*
    RULES OF CREATING A STRING TO REPRESENT A POLYNOMIAL

     - single string could contain any number of monomials
     - few monomials of the same degree are allowed; they will be summed
     - monomials are separated by character '+' (one exception -> read the next point)
     - if the next monomial is negative, user should type a single '-' (without '+' before the minus)
     - given factor [TEMP] could not contain '+' and '-' characters (they are used for separating monomials)


    CORRECT SYNTAX OF THE MONOMIAL:

    [TEMP]x[INTEGER]    - degree = INTEGER; factor = TEMP
    or
    [TEMP]x^[INTEGER]   - degree = INTEGER; factor = TEMP
    or
    [TEMP]x				- degree = 1; factor = TEMP
    or
    x				    - degree = 1; factor = 1
    or
    -x				    - degree = 1; factor = -1
    or
    [TEMP]				- a constant term; in this case [TEMP] could not contain 'x' character

    where:
    [TEMP]		- value of the factor next to x; its type depends on the type used when created an object of Polynomial<TEMP_TYPE> class
    [INTEGER]	- exponent of the x (values greater or equal 0]

*/

template <class T>
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

    class iterator
    {
    private:
        friend Polynomial<T>;

        class Polynomial<T>::Factor* ptr;
        class Polynomial<T>::Factor* prevPtr;
        bool isBegin;
        int degree;

        Polynomial<T>* parent;

    public:
        class Polynomial<T>::Factor& operator * ();

        iterator& operator ++ (int);
        iterator& operator -- (int);
        iterator& operator ++ ();
        iterator& operator -- ();
        iterator& operator = (const class Polynomial<T>::iterator& right);

        iterator operator + (const unsigned int right);
        iterator operator - (const unsigned int right);

        bool operator == (const class Polynomial<T>::iterator& right) const;
        bool operator != (const class Polynomial<T>::iterator& right) const;
        bool operator == (std::nullptr_t) const;
        bool operator != (std::nullptr_t) const;
    };

    class const_iterator
    {
    private:
        friend Polynomial<T>;

        class Polynomial<T>::Factor* ptr;
        class Polynomial<T>::Factor* prevPtr;
        bool isBegin;
        int degree;

        Polynomial<T>* parent;

    public:
        const_iterator();
        const_iterator(iterator& it);

        const class Polynomial<T>::Factor& operator * ();

        const_iterator& operator ++ (int);
        const_iterator& operator -- (int);
        const_iterator& operator ++ ();
        const_iterator& operator -- ();
        const_iterator& operator = (const class Polynomial<T>::const_iterator& right);

        const_iterator operator + (const unsigned int right);
        const_iterator operator - (const unsigned int right);

        bool operator == (const class Polynomial<T>::const_iterator& right) const;
        bool operator != (const class Polynomial<T>::const_iterator& right) const;
        bool operator == (std::nullptr_t) const;
        bool operator != (std::nullptr_t) const;
    };

    iterator begin();
    iterator end();
    iterator erase(iterator it);

    const_iterator cbegin() const;
    const_iterator cend() const;

private:
    int polyDegree;

    static bool isError;
    static std::string errorMsg;

    class Factor
    {
    public:
        Factor(const int deg);
        Factor();

        Factor* next;
        Factor* prev;

        const T& getValue() const;
        const int& getDegree() const;
        void setValue(const T& newValue);

    private:
        T value;
        int degree;

        Polynomial<T>::iterator* it;

        friend class Polynomial<T>;
    };

    Factor* first = nullptr;
    Factor* last = nullptr;

    Factor* addFactor(const int deg);
    Factor* addFactor(const int deg, Factor** after);
    Factor* addFactor(const int deg, const T value);
    Factor* addToFactor(const int deg, const T value);
    Factor* freeFactor(Factor** temp);
    void clearMemory();

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
    int setMonomial(const std::string s, bool& newError, std::string& errorDetails, const int beginIt, const bool isPositive);
    int addMonomial(const std::string curValue, const std::string curDegree, const bool isPositive);
    void checkDegree();
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

template <class T>
bool Polynomial<T>::isError = false;
template <class T>
std::string Polynomial<T>::errorMsg = "";

template <class T>
Polynomial<T>::Factor::Factor(const int deg)
{
    degree = deg;
    value = 0;
    next = nullptr;
    prev = nullptr;
    it = nullptr;
}

template <class T>
Polynomial<T>::Factor::Factor()
{
    value = 0;
    degree = 0;
    next = nullptr;
    prev = nullptr;
    it = nullptr;
}

template <class T>
const T& Polynomial<T>::Factor::getValue() const
{
    return value;
}

template <class T>
const int& Polynomial<T>::Factor::getDegree() const
{
    return degree;
}

template <class T>
void Polynomial<T>::Factor::setValue(const T& newValue)
{
    value = newValue;
    if (value == 0)
    {
        if (it != nullptr)
        {
            iterator temp = *it;
            (*it)++;
            temp.parent->erase(temp);
        }
    }
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
Polynomial<T>::Polynomial (const std::string s)
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
            cur->value = static_cast<T>(cur->degree) * cur->value;
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
        errorMsg = "Error: trying to read non-existing factor";
    }
    return 0;
}

template <class T>
bool Polynomial<T>::checkLastError(std::string& getErrorMsg)
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

        if (curL->value == static_cast<T>(0))
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
        if (curL->value == static_cast<T>(0)) curL = freeFactor(&curL);
        if (curL != nullptr) curL = curL->next;
    }

    temp.checkDegree();
    *this = temp;
    return *this;
}

template <class T>
typename Polynomial<T>::Factor* Polynomial<T>::addFactor(const int deg)
{
    Factor* temp = addToFactor(deg, 0);
    temp->value = 0;
    return temp;
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
typename Polynomial<T>::Factor* Polynomial<T>::addToFactor(const int deg, const T value)
{
    if (first == nullptr)
    {
        first = last = new Factor(deg);
        first->value += value;
        return first;
    }

    for (Factor* cur = first; cur != nullptr; cur = cur->next)
    {
        if (cur->degree == deg)
        {
            cur->value += value;
            return cur;
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
            return newFactor;
        }
    }

    Factor* prev = last;
    prev->next = new Factor(deg);
    prev->next->prev = prev;
    last = prev->next;

    last->value += value;

    return last;
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
void Polynomial<T>::setPolynomial(const std::string s)
{
    resetValues();

    std::string curMono = "";

    bool newError = false;
    bool errorChar[s.size()];
    bool isPositive = true;
    bool isFirst = true;
    std::string errorDetails = "";

    for (unsigned int i = 0; i < s.size() + 1; i++)
    {
        if (i != s.size())
        {
            errorChar[i] = false;
            if (s[i] == ' ') continue;
        }

        if (i == s.size() || s[i] == '+' || s[i] == '-')
        {
            int result = -1;

            if (curMono.size() > 0) result = setMonomial(curMono, newError, errorDetails, i - curMono.size(), isPositive);
            else if (!isFirst)
            {
                result = i;
                newError = true;
                errorDetails += "\n   character " + std::to_string(i) + ": empty monomial";
            }
            isFirst = false;

            if (result >= 0)
            {
                errorChar[result] = true;
            }

            curMono = "";

            if (i != s.size() && s[i] == '-')
            {
                isPositive = false;
            }
            else isPositive = true;
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
        errorMsg = "Error loading polynomial \"" + s + "\"\n";
        errorMsg+= "   Incorrect characters:  ";
        for (unsigned int i = 0; i < s.size(); i++)
        {
            if (errorChar[i]) errorMsg += "^";
            else errorMsg += "-";
        }
        errorMsg += errorDetails + "\nIncorrect monomials have been skipped.";
    }
}

template <class T>
int Polynomial<T>::setMonomial(const std::string s, bool& newError, std::string& errorDetails, const int beginIt, const bool isPositive)
{
    int xPos = -1;
    int carets = 0;
    std::string curValue = "";
    std::string curDegree = "";

    for (unsigned int i = s.size() - 1;; i--)
    {
        if (s[i] == '^') carets++;

        if (s[i] == 'x')
        {
            xPos = i;
            break;
        }
        if (i == 0) break;
    }

    if (xPos < 0)
    {
        curValue = s;
    }
    else
    {
        if (carets > 1)
        {
            newError = true;
            errorDetails += "\n   character " + std::to_string(beginIt) + ": few '^' characters";
            return beginIt + xPos + 1;
        }
        if (xPos == (int)s.size() - 1)
        {
            curDegree = "1";
            for (int i = 0; i < xPos; i++)
                curValue += s[i];
        }
        else
        {
            if (carets == 1 && s[xPos + 1] != '^')
            {
                newError = true;
                errorDetails += "\n   character " + std::to_string(beginIt) + ": character '^' in the wrong place";
                return beginIt + xPos + 1;
            }
            else
            {
                for (unsigned int i = xPos + carets + 1; i < s.size(); i++)
                {
                    if (s[i] < '0' || s[i] > '9')
                    {
                        newError = true;
                        errorDetails += "\n   character " + std::to_string(beginIt) + ": this character is not a number";
                        return beginIt + i;
                    }
                    curDegree += s[i];
                }
                for (int i = 0; i < xPos; i++)
                    curValue += s[i];
            }
        }
    }

    if (curValue.size() == 0)
    {
        if (curDegree.size() > 0) curValue = "1";
        else curValue = "0";
    }
    if (curDegree.size() == 0) curDegree = "0";

    int result = addMonomial(curValue, curDegree, isPositive);

    if (result)
    {
        newError = true;
        if (result == 1)
        {
            errorDetails += "\n   character " + std::to_string(beginIt + xPos) + ": incorrect exponent of variable x";
            return beginIt + xPos;
        }
        if (result == 2) errorDetails += "\n   character " + std::to_string(beginIt) + ": incorrect exponent of variable x";
        if (result == 3) errorDetails += "\n   warning: character " + std::to_string(beginIt) + ": monomial is zero";
        return beginIt;
    }

    return -1;
}

template <class T>
int Polynomial<T>::addMonomial(const std::string curValue, const std::string curDegree, const bool isPositive)
{
    int degree = stoi(curDegree);
    std::stringstream str;
    T val;

    str << curValue;
    str >> val;

    if (str.peek() != -1)
    {
        str.clear();
        return 2;
    }

    if (degree >= 0)
    {
        if (isPositive) addToFactor(degree, val);
        else addToFactor(degree, -val);
    }
    else return 1;

    if (val == static_cast<T>(0))
    {
        return 3;
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
bool operator == (const Polynomial<T>& left, const Polynomial<T>& right)
{
    class Polynomial<T>::Factor* curL = left.first;
    class Polynomial<T>::Factor* curR = right.first;

    while (curL != nullptr && curR != nullptr)
    {
        if (curL->getDegree() != curR->getDegree()) return false;
        if (curL->getValue() != curR->getValue()) return false;

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
std::ostream& operator << (std::ostream& out, const Polynomial<T>& right)
{
    bool isFirst = true;

    class Polynomial<T>::Factor* cur = right.last;
    while (cur != nullptr)
    {
        if (cur->getValue() != static_cast<T>(0))
        {
            if (!isFirst) out << " + ";

            if (cur->getDegree() == 0) out << cur->getValue();
            else
            {
                if (cur->getValue() != static_cast<T>(1) && cur->getValue() != static_cast<T>(-1))
                    out << cur->getValue();
                else if (cur->getValue() == static_cast<T>(-1))
                    out << "-";

                out << "x";
                if (cur->getDegree() != 1) out << "^" << cur->getDegree();
            }
            isFirst = false;
        }

        cur = cur->prev;
    }
    if (right.polyDegree == 0 && right.first != nullptr && right.first->getDegree() == 0 && right.first->getValue() == static_cast<T>(0))
        out << "0";

    return out;
}

template <class T>
std::istream& operator >> (std::istream& in, Polynomial<T>& right)
{
    std::string temp;
    in >> temp;
    right.setPolynomial(temp);
    return in;
}

template <class T>
typename Polynomial<T>::iterator Polynomial<T>::begin()
{
    iterator it;
    it.ptr = first;
    it.parent = this;
    return it;
};

template <class T>
typename Polynomial<T>::iterator Polynomial<T>::end()
{
    iterator it;
    it.ptr = last;
    it.parent = this;
    return ++it;
};

template <class T>
typename Polynomial<T>::iterator Polynomial<T>::erase(class Polynomial<T>::iterator it)
{
    iterator newIt;
    newIt.ptr = freeFactor(&(it.ptr));
    newIt++;
    return newIt;
}

template <class T>
typename Polynomial<T>::const_iterator Polynomial<T>::cbegin() const
{
    const_iterator it;
    it.ptr = first;
    it.parent = this;
    return it;
}

template <class T>
typename Polynomial<T>::const_iterator Polynomial<T>::cend() const
{
    const_iterator it;
    it.ptr = last;

    return ++it;
}

template <class T>
typename Polynomial<T>::Factor& Polynomial<T>::iterator::operator * ()
{
    if (ptr == nullptr)
    {
        ptr = parent->addFactor(degree);
    }

    ptr->it = this;
    return *ptr;
}

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
typename Polynomial<T>::iterator& Polynomial<T>::iterator::operator ++ ()
{
    (*this)++;
    return *this;
}

template <class T>
typename Polynomial<T>::iterator& Polynomial<T>::iterator::operator -- ()
{
    (*this)--;
    return *this;
}

template <class T>
typename Polynomial<T>::iterator& Polynomial<T>::iterator::operator = (const class Polynomial<T>::iterator& right)
{
    ptr = right.ptr;
    return *this;
}

template <class T>
typename Polynomial<T>::iterator Polynomial<T>::iterator::operator + (const unsigned int right)
{
    iterator it = *this;
    for (unsigned int i = 0; i < right; i++)
    {
        it++;
    }
    return it;
}

template <class T>
typename Polynomial<T>::iterator Polynomial<T>::iterator::operator - (const unsigned int right)
{
    iterator it = *this;
    for (unsigned int i = 0; i < right; i++)
    {
        it--;
    }
    return it;
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

template <class T>
const typename Polynomial<T>::Factor& Polynomial<T>::const_iterator::operator * ()
{
    if (ptr == nullptr)
    {
        ptr = parent->addFactor(degree);
    }

    return *ptr;
}

template <class T>
Polynomial<T>::const_iterator::const_iterator()
{

}

template <class T>
Polynomial<T>::const_iterator::const_iterator(class Polynomial<T>::iterator& it)
{
    ptr = it.ptr;
    prevPtr = it.prevPtr;
    isBegin = it.isBegin;
    degree = it.degree;
    parent = it.parent;
}

template <class T>
typename Polynomial<T>::const_iterator& Polynomial<T>::const_iterator::operator ++ (int)
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
typename Polynomial<T>::const_iterator& Polynomial<T>::const_iterator::operator -- (int)
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
typename Polynomial<T>::const_iterator& Polynomial<T>::const_iterator::operator ++ ()
{
    (*this)++;
    return *this;
}

template <class T>
typename Polynomial<T>::const_iterator& Polynomial<T>::const_iterator::operator -- ()
{
    (*this)--;
    return *this;
}

template <class T>
typename Polynomial<T>::const_iterator& Polynomial<T>::const_iterator::operator = (const class Polynomial<T>::const_iterator& right)
{
    ptr = right.ptr;
    return *this;
}

template <class T>
typename Polynomial<T>::const_iterator Polynomial<T>::const_iterator::operator + (const unsigned int right)
{
    const_iterator it = this;
    for (int i = 0; i < right; i++)
    {
        it++;
    }
    return it;
}

template <class T>
typename Polynomial<T>::const_iterator Polynomial<T>::const_iterator::operator - (const unsigned int right)
{
    const_iterator it = this;
    for (int i = 0; i < right; i++)
    {
        it--;
    }
    return it;
}

template <class T>
bool Polynomial<T>::const_iterator::operator == (const class Polynomial<T>::const_iterator& right) const
{
    return ptr == right.ptr;
}

template <class T>
bool Polynomial<T>::const_iterator::operator != (const class Polynomial<T>::const_iterator& right) const
{
    return ptr != right.ptr;
}

template <class T>
bool Polynomial<T>::const_iterator::operator == (std::nullptr_t) const
{
    return ptr == nullptr;
}

template <class T>
bool Polynomial<T>::const_iterator::operator != (std::nullptr_t) const
{
    return ptr != nullptr;
}

#endif // POLYNOMIAL_H
