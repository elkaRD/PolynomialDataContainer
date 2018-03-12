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

class Polynomial
{
public:

    Polynomial();
    Polynomial(std::string s);
    Polynomial(const Polynomial& poly);

    void derivative();
    int getDegree();
    int calc(int x);
    void reduceFactors();

    inline bool operator == (const Polynomial& right) const;
    inline bool operator != (const Polynomial& right) const;

    Polynomial& operator = (const Polynomial& right);
    Polynomial& operator = (const std::string& right);
    Polynomial& operator = (const int& right);

    Polynomial& operator += (const Polynomial& right);
    Polynomial& operator -= (const Polynomial& right);
    Polynomial& operator += (const std::string& right);
    Polynomial& operator -= (const std::string& right);
    Polynomial& operator += (const int& right);
    Polynomial& operator -= (const int& right);
    Polynomial& operator *= (const int& right);

    Polynomial operator + (const Polynomial& right) const;
    Polynomial operator - (const Polynomial& right) const;
    Polynomial operator + (const std::string& right) const;
    Polynomial operator - (const std::string& right) const;
    Polynomial operator + (const int& right) const;
    Polynomial operator - (const int& right) const;
    Polynomial operator * (const int& right) const;

    friend std::ostream& operator << (std::ostream& out, const Polynomial& right);
    friend std::istream& operator >> (std::istream& in, Polynomial& right);


private:

    int monomial[MAX_DEGREE + 1];
    int polyDegree;

    void resetValues();
    void setPolynomial(std::string s);
    void checkDegree();
    int greatestCommonDivider(int a, int b);
};

std::ostream& operator << (std::ostream& out, const Polynomial& right);
std::istream& operator >> (std::istream& in, Polynomial& right);

#endif // POLYNOMIAL_H
