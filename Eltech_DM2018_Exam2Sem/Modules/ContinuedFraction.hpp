//
//  ContinuedFraction.hpp
//  Eltech_DM2018_Exam2Sem
//
//  Created by Никита Исаенко on 07.06.2018.
//  Copyright © 2018 Melanholy Hill. All rights reserved.
//

#ifndef ContinuedFraction_hpp
#define ContinuedFraction_hpp

#include <stdio.h>
#include <iostream>

#include "Base.hpp"

#include "Natural.hpp"
#include "Integer.hpp"
#include "Fraction.hpp"

/*Для упрощения вызова следующих функций*/
using std::endl;
using std::cout;
using std::cin;

/*Объявляем структуры*/
struct ContinuedFraction
{
    int Degree{ -1 };
    Integer *Elements{ nullptr };
    int PeriodStartPos{ -1 };
    bool isNotCompleted{ false };
    
    friend std::ostream& operator<<(std::ostream& os, const ContinuedFraction& CFrac);
    friend std::istream& operator>>(std::istream& is, ContinuedFraction& CFrac);
};

/*Объявляем функции работы с цепными дробями*/
int Comparison(const ContinuedFraction&, const ContinuedFraction&);
void WriteConvergenceFractionsTo(Fraction*&, ContinuedFraction, int);
void FreeContinuedFraction(ContinuedFraction&);

#endif /* ContinuedFraction_hpp */
