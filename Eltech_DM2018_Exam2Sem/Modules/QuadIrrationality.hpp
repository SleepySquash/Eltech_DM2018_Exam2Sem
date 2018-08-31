//
//  QuadIrrationality.hpp
//  Eltech_DM2018_Exam2Sem
//
//  Created by Никита Исаенко on 07.06.2018.
//  Copyright © 2018 Melanholy Hill. All rights reserved.
//

#ifndef QuadIrrationality_hpp
#define QuadIrrationality_hpp

#include <stdio.h>
#include <iostream>

#include "Base.hpp"

#include "Natural.hpp"
#include "Integer.hpp"
#include "DivideSession.hpp"
#include "Fraction.hpp"
#include "ContinuedFraction.hpp"

/*Для упрощения вызова следующих функций*/
using std::endl;
using std::cout;
using std::cin;

/*Объявляем структуры*/
struct QuadIrrationality
{
    Integer a;
    Integer b;
    Natural c;
    Natural d;
    
    friend std::ostream& operator<<(std::ostream& os, const QuadIrrationality& Quad);
    friend std::istream& operator>>(std::istream& is, QuadIrrationality& Quad);
};

/*Объявляем функции работы целых с квадратичными иррациональностями*/
void IsQuadIrrationalityValid(Fraction&, QuadIrrationality);
int Comparison(const QuadIrrationality&, const QuadIrrationality&);
bool IsQuadCorrect(const QuadIrrationality&);
void IsQuadIrrationalityValid(Fraction&, QuadIrrationality);
void Summary(QuadIrrationality&, QuadIrrationality, QuadIrrationality);
void Subtraction(QuadIrrationality&, QuadIrrationality, QuadIrrationality);
void FreeQuad(QuadIrrationality&);
void FreeQuad(QuadIrrationality*);
void EstimateRootLowerThat(Natural&, Natural);
void EstimateRootLowerThat_binary(Natural&, Natural);
void MultiplyByConjugate(Integer&, QuadIrrationality);
void ReduceQuadIrrationality(QuadIrrationality& Quad);
void QuadIrrationalityEquasion(QuadIrrationality&, QuadIrrationality&);
void GetIntegerPartFromQuadIrrationality(Integer&, QuadIrrationality);
void ExpandAsContinuedFraction(ContinuedFraction&, QuadIrrationality);
void ExpandAsContinuedFractionN(ContinuedFraction&, QuadIrrationality, int);

#endif /* QuadIrrationality_hpp */
