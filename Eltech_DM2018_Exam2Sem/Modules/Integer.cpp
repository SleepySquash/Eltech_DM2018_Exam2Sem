//
//  Integer.cpp
//  Eltech_DM2018_Exam2Sem
//
//  Created by Никита Исаенко on 07.06.2018.
//  Copyright © 2018 Melanholy Hill. All rights reserved.
//

#include "Integer.hpp"

std::ostream& operator<<(std::ostream& os, const Integer& Int)
{
    if (Int.Degree != -1 && Int.Sign)
        cout << "-";
    for (int i = Int.Degree; i >= 0; i--)
        os << (int)Int.Digits[i];
    return os;
}
    
std::istream& operator>>(std::istream& is, Integer& Int)
{
    char *n = InputString();
    for (int i = GetLength(n) - 1; i >= 0; i--)
    {
        if (n[i] == 45)
            Int.Sign = true;
        else if (n[i] >= 48 && n[i] <= 57)
        {
            Int.Degree++;
            Int.Digits = (char*)realloc(Int.Digits, sizeof(char)*(Int.Degree+1));
            Int.Digits[Int.Degree] = n[i] - 48;
        }
    }
    
    return is;
}

//----------------------------------------------------------
//int Comparison(const Integer&, const Integer&)
//Сравнение по порядку натуральных частей двух целых чисел.
//----------------------------------------------------------
int Comparison(const Integer &Nat1, const Integer &Nat2)
{
    if (Nat1.Degree > Nat2.Degree)
        return COMPARISON_FIRST_BIGGER;
    else if (Nat1.Degree < Nat2.Degree)
        return COMPARISON_SECOND_BIGGER;
    else
    {
        for (int i = Nat1.Degree; i >= 0; i--)
        {
            if (Nat1.Digits[i] > Nat2.Digits[i])
                return COMPARISON_FIRST_BIGGER;
            else if (Nat1.Digits[i] < Nat2.Digits[i])
                return COMPARISON_SECOND_BIGGER;
        }
        return COMPARISON_EQUAL_BIGGER;
    }
}

//----------------------------------------------------------
//void OptimazeInteger(Integer&)
//Удаление из высших разрядов числа незначащих нулей.
//----------------------------------------------------------
void OptimazeInteger(Integer &Nat)
{
    if (Nat.Degree > 0)
    {
        while (Nat.Digits[Nat.Degree] == 0 && Nat.Degree != 0)
        {
            Nat.Degree--;
            if (Nat.Degree >= 0)
            {
                char *Digits = (char*)malloc(sizeof(char)*(Nat.Degree+1));
                for (int i = 0; i <= Nat.Degree; i++)
                    Digits[i] = Nat.Digits[i];
                free(Nat.Digits);
                Nat.Digits = Digits;
            }
            else
            {
                free(Nat.Digits);
                Nat.Digits = nullptr;
            }
        }
    }
}

//----------------------------------------------------------
//void FreeInteger(Integer&)
//Очищает используемую целым числом память.
//----------------------------------------------------------
void FreeInteger(Integer& IntegerPart)
{
    if (IntegerPart.Digits != nullptr)
        free(IntegerPart.Digits);
    IntegerPart.Digits = nullptr;
    IntegerPart.Degree = -1;
    IntegerPart.Sign = false;
}

//----------------------------------------------------------
//void Summary(Integer&, Integer, Integer)
//Сумма целых чисел.
//----------------------------------------------------------
void Summary(Integer& Sum, Integer that, Integer other)
{
    if ((that.Sign && other.Sign) || (!that.Sign && !other.Sign))
    {
        Sum.Sign = that.Sign;
        Natural Nat1; Nat1.Degree = that.Degree; Nat1.Digits = that.Digits;
        Natural Nat2; Nat2.Degree = other.Degree; Nat2.Digits = other.Digits;
        Natural NSum; Summary(NSum, Nat1, Nat2);
        Sum.Degree = NSum.Degree;
        Sum.Digits = NSum.Digits;
    }
    else
    {
        int CRes = Comparison(that, other);
        if (!that.Sign && CRes == COMPARISON_SECOND_BIGGER)
            Sum.Sign = true;
        if (!other.Sign && CRes == COMPARISON_FIRST_BIGGER)
            Sum.Sign = true;
        
        Natural Nat1; Nat1.Degree = that.Degree; Nat1.Digits = that.Digits;
        Natural Nat2; Nat2.Degree = other.Degree; Nat2.Digits = other.Digits;
        Natural NSub; Subtraction(NSub, Nat1, Nat2);
        Sum.Degree = NSub.Degree;
        Sum.Digits = NSub.Digits;
    }
}

//----------------------------------------------------------
//void Subtraction(Integer&, Integer, Integer)
//Разность целых чисел.
//----------------------------------------------------------
void Subtraction(Integer& Sum, Integer that, Integer other)
{
    other.Sign = !other.Sign;
    Summary(Sum, that, other);
}

//----------------------------------------------------------
//void Multiply(Integer&, Integer, Integer)
//Умножение целых чисел.
//----------------------------------------------------------
void Multiply(Integer &Mul, Integer that, Integer other)
{
    if ((!that.Sign && other.Sign) || (that.Sign && !other.Sign))
        Mul.Sign = true;
    
    Natural Nat1; Nat1.Degree = that.Degree; Nat1.Digits = that.Digits;
    Natural Nat2; Nat2.Degree = other.Degree; Nat2.Digits = other.Digits;
    Natural NMul; Multiply(NMul, Nat1, Nat2);
    Mul.Degree = NMul.Degree;
    Mul.Digits = NMul.Digits;
}

//----------------------------------------------------------
//void Divide(Integer&, Integer, Integer)
//Деление нацело целых чисел.
//----------------------------------------------------------
void Divide(Integer &QuoResult, Integer that, Integer other)
{
    if ((!that.Sign && other.Sign) || (that.Sign && !other.Sign))
    {
        Natural Nat1; Nat1.Degree = that.Degree; Nat1.Digits = that.Digits;
        Natural Nat2; Nat2.Degree = other.Degree; Nat2.Digits = other.Digits;
        Natural NMul; Divide(NMul, Nat1, Nat2);
        QuoResult.Degree = NMul.Degree;
        QuoResult.Digits = NMul.Digits;
    }
    else
    {
        Natural Nat1; Nat1.Degree = that.Degree; Nat1.Digits = that.Digits;
        Natural Nat2; Nat2.Degree = other.Degree; Nat2.Digits = other.Digits;
        Natural NMul; Divide(NMul, Nat1, Nat2);
        QuoResult.Degree = NMul.Degree;
        QuoResult.Digits = NMul.Digits;
    }
}

//----------------------------------------------------------
//void DivideNoStrict(Integer&, Integer, Integer)
//Деление несторого нацело целых чисел.
//----------------------------------------------------------
void DivideNoStrict(Integer &QuoResult, Integer that, Integer other)
{
    if ((!that.Sign && other.Sign) || (that.Sign && !other.Sign))
    {
        Natural Nat1; Nat1.Degree = that.Degree; Nat1.Digits = that.Digits;
        Natural Nat2; Nat2.Degree = other.Degree; Nat2.Digits = other.Digits;
        Natural NMul; DivideNoStrict(NMul, Nat1, Nat2);
        QuoResult.Degree = NMul.Degree;
        QuoResult.Digits = NMul.Digits;
    }
    else
    {
        Natural Nat1; Nat1.Degree = that.Degree; Nat1.Digits = that.Digits;
        Natural Nat2; Nat2.Degree = other.Degree; Nat2.Digits = other.Digits;
        Natural NMul; DivideNoStrict(NMul, Nat1, Nat2);
        QuoResult.Degree = NMul.Degree;
        QuoResult.Digits = NMul.Digits;
    }
}

//----------------------------------------------------------
//void Modulo(Integer&, Integer, Integer)
//Остаток от деления целых чисел.
//----------------------------------------------------------
void Modulo(Integer &RemResult, Integer that, Integer other)
{
    if ((!that.Sign && other.Sign) || (that.Sign && !other.Sign))
    {
        Natural Nat1; Nat1.Degree = that.Degree; Nat1.Digits = that.Digits;
        Natural Nat2; Nat2.Degree = other.Degree; Nat2.Digits = other.Digits;
        Natural NMul; Modulo(NMul, Nat1, Nat2);
        RemResult.Degree = NMul.Degree;
        RemResult.Digits = NMul.Digits;
    }
    else
    {
        Natural Nat1; Nat1.Degree = that.Degree; Nat1.Digits = that.Digits;
        Natural Nat2; Nat2.Degree = other.Degree; Nat2.Digits = other.Digits;
        Natural NMul; Modulo(NMul, Nat1, Nat2);
        RemResult.Degree = NMul.Degree;
        RemResult.Digits = NMul.Digits;
    }
}

//----------------------------------------------------------
//void ModuloNoStrict(Integer&, Integer, Integer)
//Остаток от деления целых чисел.
//----------------------------------------------------------
void ModuloNoStrict(Integer &RemResult, Integer that, Integer other)
{
    if ((!that.Sign && other.Sign) || (that.Sign && !other.Sign))
    {
        Natural Nat1; Nat1.Degree = that.Degree; Nat1.Digits = that.Digits;
        Natural Nat2; Nat2.Degree = other.Degree; Nat2.Digits = other.Digits;
        Natural NMul; ModuloNoStrict(NMul, Nat1, Nat2);
        RemResult.Degree = NMul.Degree;
        RemResult.Digits = NMul.Digits;
    }
    else
    {
        Natural Nat1; Nat1.Degree = that.Degree; Nat1.Digits = that.Digits;
        Natural Nat2; Nat2.Degree = other.Degree; Nat2.Digits = other.Digits;
        Natural NMul; ModuloNoStrict(NMul, Nat1, Nat2);
        RemResult.Degree = NMul.Degree;
        RemResult.Digits = NMul.Digits;
    }
}

//----------------------------------------------------------
//void Summary(Integer&, Integer, Natural)
//Сумма целого числа с натуральным.
//----------------------------------------------------------
void Summary(Integer& Sum, Integer that, Natural other)
{
    if (!that.Sign)
    {
        Sum.Sign = that.Sign;
        Natural Nat1; Nat1.Degree = that.Degree; Nat1.Digits = that.Digits;
        Natural NSum; Summary(NSum, Nat1, other);
        Sum.Degree = NSum.Degree;
        Sum.Digits = NSum.Digits;
    }
    else
    {
        Natural Nat; ConvertEqualToNatural(Nat, that);
        int CRes = Comparison(Nat, other);
        if (that.Sign && CRes == COMPARISON_SECOND_BIGGER)
            Sum.Sign = false;
        else
            Sum.Sign = true;
        
        Natural Nat1; Nat1.Degree = that.Degree; Nat1.Digits = that.Digits;
        Natural NSub; Subtraction(NSub, Nat1, other);
        Sum.Degree = NSub.Degree;
        Sum.Digits = NSub.Digits;
    }
}

//----------------------------------------------------------
//void Multiply(Integer&, Integer, Natural)
//Умножение целого числа на натуральное.
//----------------------------------------------------------
void Multiply(Integer &Mul, Integer that, Natural other)
{
    Mul.Sign = that.Sign;
    
    Natural Nat1; Nat1.Degree = that.Degree; Nat1.Digits = that.Digits;
    Natural NMul; Multiply(NMul, Nat1, other);
    Mul.Degree = NMul.Degree;
    Mul.Digits = NMul.Digits;
}

//----------------------------------------------------------
//void Divide(Integer&, Integer, Natural)
//Деление нацело целого числа на натуральное.
//----------------------------------------------------------
void Divide(Integer &QuoResult, Integer that, Natural other)
{
    QuoResult.Sign = that.Sign;
    Natural Nat1; Nat1.Degree = that.Degree; Nat1.Digits = that.Digits;
    Natural NMul; Divide(NMul, Nat1, other);
    QuoResult.Degree = NMul.Degree;
    QuoResult.Digits = NMul.Digits;
}

//----------------------------------------------------------
//void DivideNoStrict(Integer&, Integer, Natural)
//Деление нацело целого числа на натуральное.
//----------------------------------------------------------
void DivideNoStrict(Integer &QuoResult, Integer that, Natural other)
{
    QuoResult.Sign = that.Sign;
    Natural Nat1; Nat1.Degree = that.Degree; Nat1.Digits = that.Digits;
    Natural NMul; DivideNoStrict(NMul, Nat1, other);
    QuoResult.Degree = NMul.Degree;
    QuoResult.Digits = NMul.Digits;
}

//----------------------------------------------------------
//void ConvertEqualToNatural(Natural&, Integer)
//Приравнивает указанное натуральное число к указанному целому, причём массив цифр оказывается общим для обоих чисел.
//----------------------------------------------------------
void ConvertEqualToNatural(Natural& Nat, Integer Int)
{
    Nat.Degree = Int.Degree;
    Nat.Digits = Int.Digits;
}
