/*  Projekt 3 PROI - Wielomiany v2
 *  Robert Dudzinski 2018
 *  Polynomial.h
 */

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

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

        T value;
        int degree;

        Factor* next;
        Factor* prev;

        const T& getValue() const;
        const int& getDegree() const;
        void setValue(const T& newValue);

    private:
        Polynomial<T>::iterator* it;

        friend class Polynomial<T>::iterator;
        friend class Polynomial<T>::const_iterator;
    };

    Factor* first = nullptr;
    Factor* last = nullptr;

    Factor* addFactor(const int deg);
    Factor* addFactor(const int deg, Factor** after);
    Factor* addFactor(const int deg, const T value);
    Factor* addToFactor(const int deg, const T value);
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
                errorDetails += "\n   znak " + std::to_string(i) + ": pusty jednomian";
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
int Polynomial<T>::nextState(const int state, const int c, const int i, bool& newError, std::string& errorDetails) const
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
                errorDetails += "\n   znak " + std::to_string(i) + ": niepoprawne rozpoczecie jednomianu";
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
                errorDetails += "\n   znak " + std::to_string(i) + ": powinna byc liczba";
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
                errorDetails += "\n   znak " + std::to_string(i) + ": powinna byc liczba";
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
                errorDetails += "\n   znak " + std::to_string(i) + ": powinna byc liczba";
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
                errorDetails += "\n   znak " + std::to_string(i) + ": powinien byc x";
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
                errorDetails += "\n   znak " + std::to_string(i) + ": brak ulamka";
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
                errorDetails += "\n   znak " + std::to_string(i) + ": niepoprawny ulamek";
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
                errorDetails += "\n   znak " + std::to_string(i) + ": powinien byc wykladnik";
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
                errorDetails += "\n   znak " + std::to_string(i) + ": powinien byc wykladnik";
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
                errorDetails += "\n   znak " + std::to_string(i) + ": powinna byc liczba";
                return SE;
        }
    }

    return SE;
}

template <class T>
int Polynomial<T>::setMonomial(const std::string s, bool& newError, std::string& errorDetails, const int beginIt, const bool isPositive)
{
    int xPos = -1;
    int carets = 0;
    std::string curValue = "";
    std::string curDegree = "";

    //unsigned int deb = s.size()-1;
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
            errorDetails += "\n   znak " + std::to_string(beginIt) + ": kilka znakow ^";
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
                errorDetails += "\n   znak " + std::to_string(beginIt) + ": znak ^ w zlym miejscu";
                return beginIt + xPos + 1;
            }
            else
            {
                for (unsigned int i = xPos + carets + 1; i < s.size(); i++)
                {
                    if (s[i] < '0' || s[i] > '9')
                    {
                        newError = true;
                        errorDetails += "\n   znak " + std::to_string(beginIt) + ": znak nie jest cyfra";
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
        if (result == 1) errorDetails += "\n   znak " + std::to_string(beginIt + xPos) + ": niepoprawny wykladnik zmiennej x";
        if (result == 2) errorDetails += "\n   znak " + std::to_string(beginIt + xPos) + ": niepoprawny wspolczynnik zmiennej x";
        return beginIt + xPos;
    }

    /*int state = BEG;
    int beginExp = -1;
    int dot = 0;
    int caret = 0;

    std::string curValue = "";
    std::string curDegree = "";

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
        errorDetails += "\n   znak " + std::to_string(index) + ": niepoprawny jednomian";
        return beginIt;
    }
    if (state == SPM)
    {
        newError = true;
        errorDetails += "\n   znak " + std::to_string(beginIt) + ": pojedynczy znak + lub -";
        return beginIt;
    }
    if (state == XC)
    {
        newError = true;
        errorDetails += "\n   znak " + std::to_string(beginIt + caret) + ": niepoprawne uzycie znaku ^";
        return beginIt + caret;
    }
    if (state == DOT)
    {
        newError = true;
        errorDetails += "\n   znak " + std::to_string(beginIt + dot) + ": niepoprawny ulamek";
        return beginIt + dot;
    }

    if (addMonomial(curValue, curDegree, state, dot, isPositive))
    {
        newError = true;
        errorDetails += "\n   znak " + std::to_string(beginIt + beginExp) + ": niepoprawny wykladnik zmiennej x";
        return beginIt + beginExp;
    }*/

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

    //char c = str.peek();

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

    /*long long valueLL = 0;
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
    }*/
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
std::ostream& operator << (std::ostream& out, const Polynomial<T>& right)
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
