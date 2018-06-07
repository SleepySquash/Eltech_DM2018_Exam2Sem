//
//  ContinuedFraction.cpp
//  Eltech_DM2018_Exam2Sem
//
//  Created by Никита Исаенко on 07.06.2018.
//  Copyright © 2018 Melanholy Hill. All rights reserved.
//

#include "ContinuedFraction.hpp"

std::ostream& operator<<(std::ostream& os, const ContinuedFraction& CFrac)
{
    for (int i = 0; i <= CFrac.Degree; i++)
    {
        if (CFrac.PeriodStartPos != -1 && i == CFrac.PeriodStartPos+1)
            os << "(";
        
        if (CFrac.Degree == 0)
            os << "[" << CFrac.Elements[i] << ";]";
        else if (i == 0)
            os << "[" << CFrac.Elements[i] << ";";
        else if (i == CFrac.Degree)
        {
            if (CFrac.PeriodStartPos != -1)
                os << CFrac.Elements[i] << ")" << "]" ;
            else
            {
                os << CFrac.Elements[i];
                if (CFrac.isNotCompleted)
                    os << "...]";
                else
                    os << "]";
            }
        }
        else
            os << CFrac.Elements[i] << ",";
    }
    return os;
}

std::istream& operator>>(std::istream& is, ContinuedFraction& CFrac)
{
    if (CFrac.Degree == -1)
    {
        CFrac.Degree++;
        CFrac.Elements = (Integer*)realloc(CFrac.Elements, sizeof(Integer)*(CFrac.Degree + 1));
        CFrac.Elements[CFrac.Degree].Degree = -1;
        CFrac.Elements[CFrac.Degree].Digits = nullptr;
    }
    
    char *str = InputString();
    bool SignReading{ false };
    int CharsParsed{ 0 };
    int StrLength = GetLength(str);
    for (int i = 0; i <= StrLength; i++)
    {
        if (str[i] == '-')
            SignReading = true;
        if (str[i] == ',' || str[i] == ')' || str[i] == '(' || str[i] == '[' || str[i] == ']' || str[i] == ';' || str[i] == ' ')
        {
            if (str[i] == '(')
                CFrac.PeriodStartPos = CFrac.Degree;
            else if (str[i] == ';')
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
                    CFrac.Elements[0].Sign = Int.Sign;
                    CFrac.Elements[0].Degree = Int.Degree;
                    CFrac.Elements[0].Digits = Int.Digits;
                    for (int k = 0; k <= CFrac.Elements[0].Degree; k++)
                        CFrac.Elements[0].Digits[k] = Int.Digits[k];
                }
            }
            else if (str[i] == ',' || str[i] == ')' || str[i] == ']' || str[i] == '\0')
            {
                Integer Int;
                Int.Sign = SignReading;
                for (int j = i - 1; j >= i - CharsParsed; j--)
                {
                    if (str[j] >= 48 && str[j] <= 57)
                    {
                        Int.Degree++;
                        Int.Digits = (char*)realloc(Int.Digits, sizeof(char)*(Int.Degree+1));
                        Int.Digits[Int.Degree]= str[j] - 48;
                    }
                }
                
                if (Int.Degree != -1)
                {
                    CFrac.Degree++;
                    CFrac.Elements = (Integer*)realloc(CFrac.Elements, sizeof(Integer)*(CFrac.Degree + 1));
                    CFrac.Elements[CFrac.Degree].Sign = Int.Sign;
                    CFrac.Elements[CFrac.Degree].Degree = Int.Degree;
                    CFrac.Elements[CFrac.Degree].Digits = Int.Digits;
                    for (int k = 0; k <= CFrac.Elements[CFrac.Degree].Degree; k++)
                        CFrac.Elements[CFrac.Degree].Digits[k] = Int.Digits[k];
                }
            }
            
            SignReading = false;
            CharsParsed = 0;
        }
        else
            CharsParsed++;
    }
    
    return is;
}

//----------------------------------------------------------
//int Comparison(const ContinuedFraction&, const ContinuedFraction&)
//Сравнение по порядку двух цепных дробей.
//----------------------------------------------------------
int Comparison(const ContinuedFraction &CFrac1, const ContinuedFraction &CFrac2)
{
    int MaxN{ CFrac1.Degree };
    if (CFrac1.Degree > CFrac2.Degree)
        MaxN = CFrac2.Degree;
    
    for (int i = 0; i <= MaxN; i++)
    {
        int ComparisonResult = Comparison(CFrac1.Elements[i], CFrac2.Elements[i]);
        if (ComparisonResult != COMPARISON_EQUAL_BIGGER)
        {
            bool Minus = (i % 2 == 0) ? false : true;
            Integer Sub; Subtraction(Sub, CFrac1.Elements[i], CFrac2.Elements[i]);
            
            if (Sub.Sign && Minus)
                Sub.Sign = false;
            else if (!Sub.Sign && Minus)
                Sub.Sign = true;
            
            if (Sub.Sign)
                return COMPARISON_SECOND_BIGGER;
            else
                return COMPARISON_FIRST_BIGGER;
        }
    }
    if (CFrac1.Degree == CFrac2.Degree)
        return COMPARISON_EQUAL_BIGGER;
    else
    {
        if (CFrac1.Degree < CFrac2.Degree)
        {
            if (CFrac1.Degree % 2 == 0)
                return COMPARISON_SECOND_BIGGER;
            else
                return COMPARISON_FIRST_BIGGER;
        }
        else
        {
            if (CFrac2.Degree % 2 == 0)
                return COMPARISON_FIRST_BIGGER;
            else
                return COMPARISON_SECOND_BIGGER;
        }
    }
}

//----------------------------------------------------------
//void WriteConvergenceFractionsTo(Fraction *&FracArray, ContinuedFraction CFrac, int n)
//Находит первые n подходящих дробей.
//----------------------------------------------------------
void WriteConvergenceFractionsTo(Fraction *&FracArray, ContinuedFraction CFrac, int n)
{
    if (CFrac.Degree != -1 && n > 0)
    {
        int num{ 0 };
        Fraction Frac;
        
        for (int i = 0; i < n; i ++)
        {
            if (i == 0)
            {
                //p0 = a0, q0 = 1
                Frac.Num.Sign = CFrac.Elements[num].Sign;
                Frac.Num.Degree = CFrac.Elements[num].Degree;
                Frac.Num.Digits = (char*)malloc(sizeof(char)*(Frac.Num.Degree + 1));
                for (int j = 0; j <= Frac.Num.Degree; j++)
                    Frac.Num.Digits[j] = CFrac.Elements[num].Digits[j];
                
                Frac.Deno.Degree = 0;
                Frac.Deno.Digits = (char*)malloc(sizeof(char));
                Frac.Deno.Digits[0] = 1;
            }
            else if (i == 1)
            {
                //p1 = a0*a1, q0 = a1
                Natural One; SetOne(One);
                Integer MulNum; Multiply(MulNum, CFrac.Elements[num], CFrac.Elements[num - 1]);
                Summary(Frac.Num, MulNum, One);
                
                Frac.Deno.Degree = CFrac.Elements[num].Degree;
                Frac.Deno.Digits = (char*)malloc(sizeof(char)*(Frac.Deno.Degree + 1));
                for (int j = 0; j <= Frac.Deno.Degree; j++)
                    Frac.Deno.Digits[j] = CFrac.Elements[num].Digits[j];
                
                if (MulNum.Digits != nullptr)
                    free(MulNum.Digits);
            }
            else
            {
                //Pn = Pn-1*an + Pn-2, Qn = Qn-1*an + Qn-2
                Integer NumResult;
                Multiply(NumResult, FracArray[i-1].Num, CFrac.Elements[num]);
                Integer SumNum; Summary(SumNum, NumResult, FracArray[i-2].Num);
                
                Integer DenoResult;
                Multiply(DenoResult, CFrac.Elements[num], FracArray[i-1].Deno);
                Integer SumDeno; Summary(SumDeno, DenoResult, FracArray[i-2].Deno);
                
                if (SumNum.Sign && SumDeno.Sign)
                    Frac.Num.Sign = false;
                else if (!SumNum.Sign && SumDeno.Sign)
                    Frac.Num.Sign = true;
                Frac.Num.Degree = SumNum.Degree;
                Frac.Num.Digits = SumNum.Digits;
                Frac.Deno.Degree = SumDeno.Degree;
                Frac.Deno.Digits = SumDeno.Digits;
                
                if (NumResult.Digits != nullptr)
                    free(NumResult.Digits);
                if (DenoResult.Digits != nullptr)
                    free(DenoResult.Digits);
            }
            
            FracArray = (Fraction*)realloc(FracArray, sizeof(Fraction)*(i + 1));
            FracArray[i].Num.Sign = Frac.Num.Sign;
            FracArray[i].Num.Degree = Frac.Num.Degree;
            FracArray[i].Num.Digits = Frac.Num.Digits;
            FracArray[i].Deno.Degree = Frac.Deno.Degree;
            FracArray[i].Deno.Digits = Frac.Deno.Digits;
            
            num++;
            if (num > CFrac.Degree)
            {
                if (CFrac.PeriodStartPos != -1)
                    num = CFrac.PeriodStartPos + 1;
                else
                {
                    if (CFrac.Degree != 0)
                        num = 1;
                    else
                        num = 0;
                }
            }
        }
    }
    else
        cout << "Ошибка. Невозможно рассчитать подходящие дроби." << endl;
}

//----------------------------------------------------------
//void FreeContinuedFraction(ContinuedFraction&)
//Очищает используемую данной цепной дробью память.
//----------------------------------------------------------
void FreeContinuedFraction(ContinuedFraction &CFrac)
{
    if (CFrac.Elements != nullptr)
    {
        for (int i = 0; i <= CFrac.Degree; i++)
        {
            if (CFrac.Elements[i].Digits != nullptr)
                free(CFrac.Elements[i].Digits);
        }
        free(CFrac.Elements);
    }
    CFrac.Degree = -1;
    CFrac.Elements = nullptr;
    CFrac.isNotCompleted = false;
    CFrac.PeriodStartPos = -1;
}
