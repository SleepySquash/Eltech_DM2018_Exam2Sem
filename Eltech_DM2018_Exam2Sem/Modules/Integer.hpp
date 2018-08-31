//
//  Integer.hpp
//  Eltech_DM2018_Exam2Sem
//
//  Created by Никита Исаенко on 07.06.2018.
//  Copyright © 2018 Melanholy Hill. All rights reserved.
//

#ifndef Integer_hpp
#define Integer_hpp

#include <stdio.h>
#include <iostream>

#include "Base.hpp"

#include "Natural.hpp"

/*Для упрощения вызова следующих функций*/
using std::endl;
using std::cout;
using std::cin;

/*Объявляем структуры*/
struct Integer
{
    bool Sign{ false };
    int Degree{ -1 };
    char *Digits{ nullptr };
    
    friend std::ostream& operator<<(std::ostream& os, const Integer& Int);
    friend std::istream& operator>>(std::istream& is, Integer& Int);
};

/*Объявляем функции работы с целыми числами*/
int Comparison(const Integer&, const Integer&);
void OptimazeInteger(Integer&);
void FreeInteger(Integer&);
void Summary(Integer&, Integer, Integer);
void Subtraction(Integer&, Integer, Integer);
void Multiply(Integer&, Integer, Integer);
void Divide(Integer&, Integer, Integer);
void DivideNoStrict(Integer&, Integer, Integer);
void Modulo(Integer&, Integer, Integer);
void ModuloNoStrict(Integer&, Integer, Integer);

/*Объявляем функции работы целых с натуральными числами*/
void Summary(Integer&, Integer, Natural);
void Multiply(Integer&, Integer, Natural);
void Divide_obsolete(Integer&, Integer, Natural);
void DivideNoStrict(Integer&, Integer, Natural);
void ConvertEqualToNatural(Natural&, Integer);

#endif /* Integer_hpp */
