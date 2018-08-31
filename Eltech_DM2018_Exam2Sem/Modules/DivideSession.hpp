//
//  DivideSession.hpp
//  Eltech_DM2018_Exam2Sem
//
//  Created by Никита Исаенко on 15.06.2018.
//  Copyright © 2018 Melanholy Hill. All rights reserved.
//

#ifndef DivideSession_hpp
#define DivideSession_hpp

#include <stdio.h>
#include <iostream>

#include "Base.hpp"

//Да, для работы этих алгоритмов деления необходимо включить функции и натуральных чисел, и целых чисел.
//Да, это тупо. Но в дальнейшем, когда я реализую все сессии деления, я исправлю это.
#include "Natural.hpp"
#include "Integer.hpp"

/*Для упрощения вызова следующих функций*/
using std::endl;
using std::cout;
using std::cin;

/*Объявляем структуры*/
struct DivideSession
{
    Integer Quo;
    Natural QuoAsNatural;
    Natural Rem;
};

/*Объявляем функции работы с сессией деления*/
void Divide(DivideSession&, Natural, Natural);
void DivideNoStrict(DivideSession&, Natural, Natural);
/*
 void Divide(DivideSession&, Integer, Integer);
 void DivideNoStrict(DivideSession&, Integer, Integer);
 void Divide(DivideSession&, Integer, Natural);
 void DivideNoStrict(DivideSession&, Integer, Natural);
*/
void FreeDivideSession(DivideSession&);

/*Объявляем функции работы с делением*/
void Divide(Natural&, Natural, Natural);
void Modulo(Natural&, Natural, Natural);
void Divide(Integer&, Integer, Natural);

#endif /* DivideSession_hpp */
