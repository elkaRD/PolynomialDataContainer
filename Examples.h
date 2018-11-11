/*  EN: Project on the 2nd semester of CS at Warsaw University of Technology
 *      Polynomial as a data container
 *
 *  PL: Projekt PROI (Programowanie obiektowe) PW WEiTI 18L
 *      Wielomian jako kontener danych
 *
 *  Copyright (C) Robert Dudzinski 2018
 *
 *  File: Examples.h
 */

#ifndef EXAMPLES_H
#define EXAMPLES_H

#include <iostream>
#include "Polynomial.h"

template <class T>
void examples();
template <class T>
void testIterator();

template <class T>
void examples()
{
    Polynomial<T> poly1;
    Polynomial<T> poly2("x^5 + 3x^4 - 5x^2 + 1");
    Polynomial<T> poly3(poly2);

    std::cout << "w1 empty:        " << poly1.getDegree() << ",   " << poly1 << std::endl;
    std::cout << "w2 poly(str):   " << poly2.getDegree() << ",   " << poly2 << std::endl;
    std::cout << "w3 = poly(w2):  " << poly3.getDegree() << ",   " << poly3 << std::endl;
    std::cout << "w1 == w2:        " << (poly1 == poly2) << std::endl;
    std::cout << "w2 != w3:        " << (poly2 != poly3) << std::endl;
    std::cout << "w3 == str:       " << (poly2 == Polynomial<T>("x^5 + 3x^4 - 5x^2 + 1")) << std::endl;
    std::cout << std::endl;

    poly1 = "-x^3 + 5x^2 + 2";
    poly2 += poly1;
    poly3 = poly1 - poly2;

    std::cout << "w1 = str:        " << poly1.getDegree() << ",   " << poly1 << std::endl;
    std::cout << "w2 += w1:        " << poly2.getDegree() << ",   " << poly2 << std::endl;
    std::cout << "w3 = w1 - w2:    " << poly3.getDegree() << ",   " << poly3 << std::endl;
    std::cout << std::endl;

    poly1 += "11x^3-17";
    poly2 *= Polynomial<T>(4);
    poly3.derivative();

    std::cout << "w1 += str:   " << poly1.getDegree() << ",   " << poly1 << std::endl;
    std::cout << "w2 *= 4:     " << poly2.getDegree() << ",   " << poly2 << std::endl;
    std::cout << "w3 dx:       " << poly3.getDegree() << ",   " << poly3 << std::endl;
    std::cout << std::endl;

    poly2 = poly2 - Polynomial<T>("4x5");
    poly3 -= poly2;

    std::cout << "w1 reduce:       " << poly1.getDegree() << ",   " << poly1 << std::endl;
    std::cout << "w2 = w2 - str:   " << poly2.getDegree() << ",   " << poly2 << std::endl;
    std::cout << "w3 -= w2:        " << poly3.getDegree() << ",   " << poly3 << std::endl;
    std::cout << std::endl;

    std::cout << "w1 (1):      " << poly1.getDegree() << ",   " << poly1.calc(1) << std::endl;
    std::cout << "w2 (-1):     " << poly2.getDegree() << ",   " << poly2.calc(-1) << std::endl;
    std::cout << "w3 (2):      " << poly3.getDegree() << ",   " << poly3.calc(2) << std::endl;
    std::cout << std::endl;

    poly1 = poly3 * Polynomial<T>(-6);
    poly2 = Polynomial<T>(-6) * poly3;

    std::cout << "w1 = w3 * -6:    " << poly1.getDegree() << ",   " << poly1 << std::endl;
    std::cout << "w2 = -6 * w3:    " << poly2.getDegree() << ",   " << poly2 << std::endl;
    std::cout << "w3:              " << poly3.getDegree() << ",   " << poly3 << std::endl;
    std::cout << std::endl;

    poly1 = poly3 - Polynomial<T>(10);
    poly2 = Polynomial<T>(-10) + poly3;

    std::cout << "w1 = w3 - 10:    " << poly1.getDegree() << ",   " << poly1 << std::endl;
    std::cout << "w2 = -10 + w3:   " << poly2.getDegree() << ",   " << poly2 << std::endl;
    std::cout << "w3:              " << poly3.getDegree() << ",   " << poly3 << std::endl;
    std::cout << std::endl;

    poly1 = Polynomial<T>(std::string("2x3 + 3x3 + 4x5 + x2")) + poly3;
    poly2 = "2x3 + 3x3 + 4x5 + x2";

    std::cout << "w1 = str + w3:   " << poly1.getDegree() << ",   " << poly1 << std::endl;
    std::cout << "w2 = str:        " << poly2.getDegree() << ",   " << poly2 << std::endl;
    std::cout << "w3:              " << poly3.getDegree() << ",   " << poly3 << std::endl;
    std::cout << std::endl;

    std::string e;
    if (Polynomial<T>::checkLastError(e)) std::cout << e << std::endl;

    poly1 = "2x^9 + 3x^23^1 - 4x-2sa + 8x2 + 7xx ++ x + x2x";
    if (Polynomial<T>::checkLastError(e)) std::cout << e << std::endl << std::endl;

    std::cout << "w1 = after error:   " << poly1.getDegree() << ",   " << poly1 << std::endl;
    std::cout << std::endl;

    if (Polynomial<T>::checkLastError(e)) std::cout << e << std::endl;

    poly1 = "x8+x7+x6+x5+x4+x3+x2+x+1";
    poly2 = Polynomial<T>(7);

    std::cout << "w1 = str:          " << poly1.getDegree() << ",   " << poly1 << std::endl;
    std::cout << "w2 = 7:            " << poly2.getDegree() << ",   " << poly2 << std::endl;
    std::cout << "w3 = 2*w1*3+2*w2:  " << poly3.getDegree() << ",   " << poly3 << std::endl;
    std::cout << std::endl;

    std::cout << "w3: constant term:     " << poly3.getFactor(0) << std::endl;
    std::cout << "w3: factor next to x^3:    " << poly3.getFactor(3) << std::endl;
    std::cout << "w3: factor next to x^9:    " << poly3.getFactor(9) << std::endl;

    if (Polynomial<T>::checkLastError(e)) std::cout << e << std::endl;
}


template <class T>
void testIterator()
{
    Polynomial<int> poly = Polynomial<int>("12x88 + 15x70 + 10x5 + 2x15 - x70 + 3x");

    std::cout << std::endl << "iterator test: " << poly << std::endl << std::endl;

    for (auto it : poly)
    {
        it.setValue(it.getValue() + 1);
        std::cout << it.getValue() << " " << it.getDegree() << ",     ";
    }
    std::cout << std::endl;

    Polynomial<int>::iterator it = poly.begin();
    Polynomial<int>::const_iterator cit = it;

    while (cit != poly.cend())
    {
        std::cout << (*cit).getValue() << " " << (*cit).getDegree() << ",    ";
        cit++;
    }

    std::cout << std::endl;

    it = it + 2;
    std::cout << (*it).getValue() << " " << (*it).getDegree() << std::endl;
    //it = poly.erase(it);  //the same like (*it).setValue(0);
    (*it).setValue(0);
    std::cout << (*it).getValue() << " " << (*it).getDegree() << std::endl;
    std::cout << poly << std::endl;

    std::cout << std::endl << "end of iterator test" << std::endl << std::endl;
}

#endif // EXAMPLES_H
