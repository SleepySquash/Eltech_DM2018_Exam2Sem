//
//  Natural.hpp
//  Eltech_DM2018_Exam2Sem
//
//  Created by Никита Исаенко on 07.06.2018.
//  Copyright © 2018 Melanholy Hill. All rights reserved.
//

#ifndef Natural_hpp
#define Natural_hpp

#include <stdio.h>
#include <iostream>

#include "Base.hpp"

/*Для упрощения вызова следующих функций*/
using std::endl;
using std::cout;
using std::cin;

/*Объявляем структуры*/
struct Natural
{
    int Degree{ -1 };
    char *Digits{ nullptr };
    
    friend std::ostream& operator<<(std::ostream& os, const Natural& Nat);
    friend std::istream& operator>>(std::istream& is, Natural& Nat);
};

/*Объявляем функции инициализации некоторых часто используемых чисел*/
void SetZero(Natural&);
void SetOne(Natural&);

/*Объявляем функции работы с натуральными числами*/
int Comparison(const Natural&, const Natural&);
void OptimazeNatural(Natural&);
void ConvertToNatural(Natural&, int);
void Summary(Natural&, Natural, Natural);
void Subtraction(Natural&, Natural, Natural);
void Multiply(Natural&, Natural, Natural);
void Divide(Natural&, Natural, Natural);
void DivideNoStrict(Natural&, Natural, Natural);
void Modulo(Natural&, Natural, Natural);
void ModuloNoStrict(Natural&, Natural, Natural);
void PowerOfTen(Natural&, Natural, int);
void GreatestCommonDivisor(Natural&, Natural, Natural);
void LeastCommonMultiple(Natural&, Natural, Natural);

#endif /* Natural_hpp */
