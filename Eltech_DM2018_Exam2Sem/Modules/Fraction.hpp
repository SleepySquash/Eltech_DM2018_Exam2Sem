//
//  Fraction.hpp
//  Eltech_DM2018_Exam2Sem
//
//  Created by Никита Исаенко on 07.06.2018.
//  Copyright © 2018 Melanholy Hill. All rights reserved.
//

#ifndef Fraction_hpp
#define Fraction_hpp

#include <stdio.h>
#include <iostream>

#include "Base.hpp"

#include "Natural.hpp"
#include "Integer.hpp"
#include "DivideSession.hpp"

/*Для упрощения вызова следующих функций*/
using std::endl;
using std::cout;
using std::cin;

/*Объявляем структуры*/
struct Fraction
{
    Integer Num;
    Natural Deno;
    
    friend std::ostream& operator<<(std::ostream& os, const Fraction& Frac);
    friend std::istream& operator>>(std::istream& is, Fraction& Frac);
};

/*Объявляем функции работы с рациональными дробями*/
void SetZero(Fraction&);
void ReduceFraction(Fraction&);
void Summary(Fraction&, Fraction, Fraction);
void Summary(Fraction&, Fraction, Integer);
void FreeFraction(Fraction&);

#endif /* Fraction_hpp */
