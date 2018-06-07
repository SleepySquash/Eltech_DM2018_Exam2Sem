//
//  Fraction.cpp
//  Eltech_DM2018_Exam2Sem
//
//  Created by Никита Исаенко on 07.06.2018.
//  Copyright © 2018 Melanholy Hill. All rights reserved.
//

#include "Fraction.hpp"

std::ostream& operator<<(std::ostream& os, const Fraction& Frac)
{
    if (Frac.Num.Degree != -1)
    {
        if (Frac.Deno.Degree == 0 && Frac.Deno.Digits[0] == 1)
            cout << Frac.Num;
        else
            cout << Frac.Num << "/" << Frac.Deno;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Fraction& Frac)
{
    char *str = InputString();
    bool SignReading{ false }, NowComesDeno{ false };
    int CharsParsed{ 0 };
    int StrLength = GetLength(str);
    for (int i = 0; i <= StrLength; i++)
    {
        if (str[i] == '-')
            SignReading = true;
        if (str[i] == '/' || str[i] == '\\' || str[i] == '\0' || str[i] == ' ')
        {
            if (CharsParsed > 0)
            {
                Integer Int; Int.Sign = SignReading;
                for (int j = i - 1; j >= i - CharsParsed; j--)
                {
                    if (str[j] >= 48 && str[j] <= 57)
                    {
                        Int.Degree++;
                        Int.Digits = (char*)realloc(Int.Digits, sizeof(char)*(Int.Degree + 1));
                        Int.Digits[Int.Degree] = str[j] - 48;
                    }
                }
                
                if (Int.Degree != -1)
                {
                    if (NowComesDeno)
                    {
                        Frac.Deno.Degree = Int.Degree;
                        Frac.Deno.Digits = Int.Digits;
                        for (int k = 0; k <= Frac.Deno.Degree; k++)
                            Frac.Deno.Digits[k] = Int.Digits[k];
                    }
                    else
                    {
                        Frac.Num.Sign = Int.Sign;
                        Frac.Num.Degree = Int.Degree;
                        Frac.Num.Digits = Int.Digits;
                        for (int k = 0; k <= Frac.Num.Degree; k++)
                            Frac.Num.Digits[k] = Int.Digits[k];
                    }
                }
            }
            
            SignReading = false;
            CharsParsed = 0;
            if (str[i] == '/')
                NowComesDeno = true;
        }
        else
            CharsParsed++;
    }
    if (Frac.Num.Degree != -1 && Frac.Deno.Degree != -1)
        ReduceFraction(Frac);
    if (Frac.Num.Degree == -1 && Frac.Deno.Degree != -1)
    {
        Frac.Num.Sign = false;
        Frac.Num.Degree = 0;
        Frac.Num.Digits = (char*)malloc(sizeof(char));
        Frac.Num.Digits[0] = 1;
    }
    if (Frac.Num.Degree != -1 && Frac.Deno.Degree == -1)
    {
        Frac.Deno.Degree = 0;
        Frac.Deno.Digits = (char*)malloc(sizeof(char));
        Frac.Deno.Digits[0] = 1;
    }
    
    return is;
}


//----------------------------------------------------------
//void SetZero(Fraction&)
//Инициализация нуля как рациональной дроби.
//----------------------------------------------------------
void SetZero(Fraction& Frac)
{
    if (Frac.Num.Digits != nullptr)
        free(Frac.Num.Digits);
    if (Frac.Deno.Digits != nullptr)
        free(Frac.Deno.Digits);
    
    Frac.Num.Sign = false;
    Frac.Num.Degree = 0;
    Frac.Num.Digits = (char*)malloc(sizeof(char));
    Frac.Num.Digits[0] = 0;
    
    Frac.Deno.Degree = 0;
    Frac.Deno.Digits = (char*)malloc(sizeof(char));
    Frac.Deno.Digits[0] = 1;
}
//----------------------------------------------------------
//void ReduceFraction(Fraction&)
//Сокращение дроби.
//----------------------------------------------------------

void ReduceFraction(Fraction &Frac)
{
    Natural NumNat; ConvertEqualToNatural(NumNat, Frac.Num);
    Natural GCD; GreatestCommonDivisor(GCD, NumNat, Frac.Deno);
    
    Integer NumResult; Divide(NumResult, Frac.Num, GCD);
    Natural DenoResult; Divide(DenoResult, Frac.Deno, GCD);
    
    FreeInteger(Frac.Num);
    if (Frac.Deno.Digits != nullptr)
        free(Frac.Deno.Digits);
    
    Frac.Num.Sign = NumResult.Sign;
    Frac.Num.Degree = NumResult.Degree;
    Frac.Num.Digits = NumResult.Digits;
    
    Frac.Deno.Degree = DenoResult.Degree;
    Frac.Deno.Digits = DenoResult.Digits;
}

//----------------------------------------------------------
//void Summary(Fraction&, Fraction, Fraction)
//Сумма рациональных дробей.
//----------------------------------------------------------
void Summary(Fraction &Result, Fraction that, Fraction other)
{
    if (that.Num.Degree != -1 && that.Deno.Degree != -1 && other.Num.Degree != -1 && other.Deno.Degree != -1)
    {
        Natural LCM; LeastCommonMultiple(LCM, that.Deno, other.Deno);
        Natural MultiplyByThat; Divide(MultiplyByThat, LCM, that.Deno);
        Integer MultipliedThatNum; Multiply(MultipliedThatNum, that.Num, MultiplyByThat);
        
        Natural MultiplyByOther; Divide(MultiplyByOther, LCM, other.Deno);
        Integer MultipliedOtherNum; Multiply(MultipliedOtherNum, other.Num, MultiplyByOther);
        
        Integer Sum; Summary(Sum, MultipliedThatNum, MultipliedOtherNum);
        Result.Num.Sign = Sum.Sign;
        Result.Num.Degree = Sum.Degree;
        Result.Num.Digits = Sum.Digits;
        Result.Deno.Degree = LCM.Degree;
        Result.Deno.Digits = LCM.Digits;
        
        if (MultiplyByThat.Digits != nullptr)
            free(MultiplyByThat.Digits);
        if (MultipliedThatNum.Digits != nullptr)
            free(MultipliedThatNum.Digits);
        if (MultiplyByOther.Digits != nullptr)
            free(MultiplyByOther.Digits);
        if (MultipliedOtherNum.Digits != nullptr)
            free(MultipliedOtherNum.Digits);
        
        ReduceFraction(Result);
    }
    else
        cout << "Ошибка. Данные дроби некорректны." << endl;
}

//----------------------------------------------------------
//void Summary(Fraction&, Fraction, Integer)
//Сумма рациональной дроби и целого числа.
//----------------------------------------------------------
void Summary(Fraction &Result, Fraction that, Integer other)
{
    if (that.Num.Degree != -1 && that.Deno.Degree != -1 && other.Degree != -1)
    {
        Integer MultipliedOtherNum; Multiply(MultipliedOtherNum, other, that.Deno);
        
        Integer Sum; Summary(Sum, that.Num, MultipliedOtherNum);
        Result.Num.Sign = Sum.Sign;
        Result.Num.Degree = Sum.Degree;
        Result.Num.Digits = Sum.Digits;
        
        Result.Deno.Degree = that.Deno.Degree;
        Result.Deno.Digits = (char*)malloc(sizeof(char)*(Result.Deno.Degree + 1));
        for (int i = 0; i <= Result.Deno.Degree; i++)
            Result.Deno.Digits[i] = that.Deno.Digits[i];
        
        if (MultipliedOtherNum.Digits != nullptr)
            free(MultipliedOtherNum.Digits);
        
        ReduceFraction(Result);
    }
    else
        cout << "Ошибка. Данные дроби некорректны." << endl;
}

//----------------------------------------------------------
//void FreeFraction(Fraction&)
//Очищает используемую рациональной дробью память.
//----------------------------------------------------------
void FreeFraction(Fraction &Frac)
{
    if (Frac.Num.Digits != nullptr)
        free(Frac.Num.Digits);
    if (Frac.Deno.Digits != nullptr)
        free(Frac.Deno.Digits);
    Frac.Num.Digits = nullptr;
    Frac.Deno.Digits = nullptr;
    Frac.Num.Sign = false;
    Frac.Num.Degree = -1;
    Frac.Deno.Degree = -1;
}
