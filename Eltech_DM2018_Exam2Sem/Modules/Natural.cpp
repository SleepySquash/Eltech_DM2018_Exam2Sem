//
//  Natural.cpp
//  Eltech_DM2018_Exam2Sem
//
//  Created by Никита Исаенко on 07.06.2018.
//  Copyright © 2018 Melanholy Hill. All rights reserved.
//

#include "Natural.hpp"

std::ostream& operator<<(std::ostream& os, const Natural& Nat)
{
    for (int i = Nat.Degree; i >= 0; i--)
        os << (int)Nat.Digits[i];
    return os;
}

std::istream& operator>>(std::istream& is, Natural& Nat)
{
    char *n = InputString();
    for (int i = GetLength(n) - 1; i >= 0; i--)
    {
        if (n[i] >= 48 && n[i] <= 57)
        {
            Nat.Degree++;
            Nat.Digits = (char*)realloc(Nat.Digits, sizeof(char)*(Nat.Degree+1));
            Nat.Digits[Nat.Degree] = n[i] - 48;
        }
    }
    
    return is;
}

//----------------------------------------------------------
//void SetZero(Natural&)
//Инициализация нуля.
//----------------------------------------------------------
void SetZero(Natural& Nat)
{
    if (Nat.Digits != nullptr)
        free(Nat.Digits);
    Nat.Degree = 0;
    Nat.Digits = (char*)malloc(sizeof(char));
    Nat.Digits[0] = 0;
}

//----------------------------------------------------------
//void SetOne(Natural&)
//Инициализация единицы.
//----------------------------------------------------------
void SetOne(Natural& Nat)
{
    if (Nat.Digits != nullptr)
        free(Nat.Digits);
    Nat.Degree = 0;
    Nat.Digits = (char*)malloc(sizeof(char));
    Nat.Digits[0] = 1;
}

//----------------------------------------------------------
//int Comparison(const Natural&, const Natural&)
//Сравнение по порядку двух натуральных чисел.
//----------------------------------------------------------
int Comparison(const Natural &Nat1, const Natural &Nat2)
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
//void ConvertToNatural(Natural&, int)
//Преобразование целого числа типа int в натуральное число типа Natural.
//----------------------------------------------------------
void ConvertToNatural(Natural& Nat, int n)
{
    while (n != 0)
    {
        int dig = n % 10;
        Nat.Degree++;
        Nat.Digits = (char*)realloc(Nat.Digits, sizeof(char)*(Nat.Degree+1));
        Nat.Digits[Nat.Degree] = dig;
        n /= 10;
    }
}

//----------------------------------------------------------
//void OptimazeNatural(Natural&)
//Удаление из высших разрядов числа незначащих нулей.
//----------------------------------------------------------
void OptimazeNatural(Natural &Nat)
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
//void CopyNaturalFrom(Natural&, Natural)
//Создание копии указанного натурального числа.
//----------------------------------------------------------
void CopyNaturalFrom(Natural& Result, Natural Root)
{
    if (Result.Digits != nullptr)
        free(Result.Digits);
    Result.Degree = Root.Degree;
    Result.Digits = (char*)malloc(sizeof(char)*(Result.Degree + 1));
    for (int i = 0; i <= Result.Degree; i++)
        Result.Digits[i] = Root.Digits[i];
}

//----------------------------------------------------------
//void FreeNatural(Natural&)
//Очистка используемой натуральным числом памяти.
//----------------------------------------------------------
void FreeNatural(Natural& Nat)
{
    if (Nat.Digits != nullptr)
        free(Nat.Digits);
    Nat.Degree = -1;
    Nat.Digits = nullptr;
}

//----------------------------------------------------------
//void Summary(Natural&, Natural, Natural)
//Сумма натуральных чисел.
//----------------------------------------------------------
void Summary(Natural& Sum, Natural that, Natural other)
{
    int MaxDegree{ that.Degree };
    int ComparisonResult = Comparison(that, other);
    if (ComparisonResult == COMPARISON_SECOND_BIGGER)
        MaxDegree = other.Degree;
    
    bool Memorize{ false };
    for (int i = 0; i <= MaxDegree; i++)
    {
        Sum.Degree++;
        Sum.Digits = (char*)realloc(Sum.Digits, sizeof(char)*(Sum.Degree + 1));
        
        if (that.Degree >= i && other.Degree >= i)
            Sum.Digits[i] = that.Digits[i] + other.Digits[i];
        else if (that.Degree < i)
            Sum.Digits[i] = other.Digits[i];
        else
            Sum.Digits[i] = that.Digits[i];
        
        if (Memorize)
        {
            Sum.Digits[i] += 1;
            Memorize = false;
        }
        if (Sum.Digits[i] >= 10)
        {
            Sum.Digits[i] -= 10;
            Memorize = true;
        }
    }
    if (Memorize)
    {
        Sum.Degree++;
        Sum.Digits = (char*)realloc(Sum.Digits, sizeof(char)*(Sum.Degree + 1));
        Sum.Digits[Sum.Degree] = 1;
    }
    
    OptimazeNatural(Sum);
}

//----------------------------------------------------------
//void Subtraction(Natural&, Natural, Natural)
//Разность натуральных чисел.
//----------------------------------------------------------
void Subtraction(Natural &Sub, Natural that, Natural other)
{
    int ComparisonResult = Comparison(that, other);
    if (ComparisonResult == COMPARISON_EQUAL_BIGGER)
        SetZero(Sub);
    else
    {
        int MaxDegree{ that.Degree };
        int Memorize{ 0 };
        if (ComparisonResult == COMPARISON_SECOND_BIGGER)
        {
            MaxDegree = other.Degree;
            for (int i = 0; i <= MaxDegree; i++)
            {
                Sub.Degree++;
                Sub.Digits = (char*)realloc(Sub.Digits, sizeof(char)*(Sub.Degree + 1));
                
                if ((that).Degree >= i)
                    Sub.Digits[i] = other.Digits[i] - (that).Digits[i];
                else
                    Sub.Digits[i] = other.Digits[i];
                
                if (Memorize > 0)
                {
                    Sub.Digits[i] -= 1;
                    Memorize -= 1;
                }
                if (Sub.Digits[i] < 0)
                {
                    Sub.Digits[i] += 10;
                    Memorize += 1;
                }
            }
        }
        else
        {
            for (int i = 0; i <= MaxDegree; i++)
            {
                Sub.Degree++;
                Sub.Digits = (char*)realloc(Sub.Digits, sizeof(char)*(Sub.Degree + 1));
                
                if (other.Degree >= i)
                    Sub.Digits[i] = (that).Digits[i] - other.Digits[i];
                else
                    Sub.Digits[i] = (that).Digits[i];
                
                if (Memorize > 0)
                {
                    Sub.Digits[i] -= 1;
                    Memorize -= 1;
                }
                if (Sub.Digits[i] < 0)
                {
                    Sub.Digits[i] += 10;
                    Memorize += 1;
                }
            }
        }
        
        OptimazeNatural(Sub);
    }
}

//----------------------------------------------------------
//void Multiply(Natural&, Natural, Natural)
//Умножение натуральных чисел.
//----------------------------------------------------------
void Multiply(Natural &Mul, Natural that, Natural other)
{
    SetZero(Mul);
    
    for (int i = 0; i <= other.Degree; i++)
    {
        if (other.Digits[i] != 0)
        {
            Natural CurrentNat; PowerOfTen(CurrentNat, that, i);
            Natural SumResult; SetZero(SumResult);
            
            for (int j = 1; j <= other.Digits[i]; j++)
            {
                Natural Sum; Summary(Sum, SumResult, CurrentNat);
                
                SumResult.Degree = Sum.Degree;
                if (SumResult.Digits != nullptr)
                    free(SumResult.Digits);
                SumResult.Digits = Sum.Digits;
            }
            free(CurrentNat.Digits);
            
            Natural Sum; Summary(Sum, Mul, SumResult);
            
            Mul.Degree = Sum.Degree;
            if (Mul.Digits != nullptr)
                free(Mul.Digits);
            Mul.Digits = Sum.Digits;
            
            free(SumResult.Digits);
        }
    }
}

//----------------------------------------------------------
//void Divide_obsolete(Natural&, Natural, Natural)
//Деление нацело натуральных чисел.
//----------------------------------------------------------
void Divide_obsolete(Natural &QuoResult, Natural that, Natural other)
{
    if (Comparison(that, other) == COMPARISON_SECOND_BIGGER)
        SetZero(QuoResult);
    else
        DivideNoStrict(QuoResult, that, other);
}

//----------------------------------------------------------
//void DivideNoStrict(Natural&, Natural, Natural)
//Деление несторого нацело натуральных чисел.
//----------------------------------------------------------
void DivideNoStrict(Natural &QuoResult, Natural that, Natural other)
{
    Natural second;
    Natural Rem;
    Natural Quo;
    
    int ComparisonResult = Comparison(that, other);
    if (ComparisonResult == COMPARISON_EQUAL_BIGGER)
        SetOne(Quo);
    else
    {
        if (ComparisonResult == COMPARISON_SECOND_BIGGER)
        {
            second.Degree = (that).Degree;
            second.Digits = (char*)malloc(sizeof(char)*(second.Degree+1));
            for (int i = 0; i <= second.Degree; i++)
                second.Digits[i] = (that).Digits[i];
            
            Rem.Degree = (other).Degree;
            Rem.Digits = (char*)malloc(sizeof(char)*(Rem.Degree+1));
            for (int i = 0; i <= Rem.Degree; i++)
                Rem.Digits[i] = (other).Digits[i];
        }
        else
        {
            second.Degree = (other).Degree;
            second.Digits = (char*)malloc(sizeof(char)*(second.Degree+1));
            for (int i = 0; i <= second.Degree; i++)
                second.Digits[i] = (other).Digits[i];
            
            Rem.Degree = (that).Degree;
            Rem.Digits = (char*)malloc(sizeof(char)*(Rem.Degree+1));
            for (int i = 0; i <= Rem.Degree; i++)
                Rem.Digits[i] = (that).Digits[i];
        }
        
        Natural Zero; SetZero(Zero);
        Natural One; SetOne(One);
        SetZero(Quo);
        if (Comparison(Zero, second) == COMPARISON_EQUAL_BIGGER)
        {
            if (Comparison(Zero, other) == COMPARISON_EQUAL_BIGGER)
                cout << "Ошибка. Деление на 0." << endl;
        }
        else if (Comparison(Zero, that) == COMPARISON_EQUAL_BIGGER)
        {
            //Quo = 0
        }
        else
        {
            while (Comparison(Rem, second) != COMPARISON_SECOND_BIGGER)
            {
                Natural Sub; Subtraction(Sub, Rem, second);
                
                Rem.Degree = Sub.Degree;
                if (Rem.Digits != nullptr)
                    free(Rem.Digits);
                Rem.Digits = Sub.Digits;
                
                Natural Sum; Summary(Sum, Quo, One);
                
                Quo.Degree = Sum.Degree;
                if (Quo.Digits != nullptr)
                    free(Quo.Digits);
                Quo.Digits = Sum.Digits;
            }
            OptimazeNatural(Quo);
        }
    }
    
    if (second.Digits != nullptr)
        free(second.Digits);
    if (Rem.Digits != nullptr)
        free(Rem.Digits);
    
    QuoResult.Degree = Quo.Degree;
    QuoResult.Digits = Quo.Digits;
}

//----------------------------------------------------------
//void Modulo_obsolete(Natural&, Natural, Natural)
//Остаток от деления натуральных чисел.
//----------------------------------------------------------
void Modulo_obsolete(Natural &RemResult, Natural that, Natural other)
{
    if (Comparison(that, other) == COMPARISON_SECOND_BIGGER)
    {
        RemResult.Degree = that.Degree;
        RemResult.Digits = (char*)malloc(sizeof(char)*(RemResult.Degree + 1));
        for (int i = 0; i <= RemResult.Degree; i++)
            RemResult.Digits[i] = that.Digits[i];
    }
    else
        ModuloNoStrict(RemResult, that, other);
}

//----------------------------------------------------------
//void ModuloNoStrict(Natural&, Natural, Natural)
//Остаток от деления нестрого натуральных чисел.
//----------------------------------------------------------
void ModuloNoStrict(Natural &RemResult, Natural that, Natural other)
{
    Natural second;
    Natural Rem;
    
    int ComparisonResult = Comparison(that, other);
    if (ComparisonResult == COMPARISON_EQUAL_BIGGER)
        SetZero(Rem);
    else
    {
        if (ComparisonResult == COMPARISON_SECOND_BIGGER)
        {
            second.Degree = (that).Degree;
            second.Digits = (char*)malloc(sizeof(char)*(second.Degree+1));
            for (int i = 0; i <= second.Degree; i++)
                second.Digits[i] = (that).Digits[i];
            
            Rem.Degree = (other).Degree;
            Rem.Digits = (char*)malloc(sizeof(char)*(Rem.Degree+1));
            for (int i = 0; i <= Rem.Degree; i++)
                Rem.Digits[i] = (other).Digits[i];
        }
        else
        {
            second.Degree = (other).Degree;
            second.Digits = (char*)malloc(sizeof(char)*(second.Degree+1));
            for (int i = 0; i <= second.Degree; i++)
                second.Digits[i] = (other).Digits[i];
            
            Rem.Degree = (that).Degree;
            Rem.Digits = (char*)malloc(sizeof(char)*(Rem.Degree+1));
            for (int i = 0; i <= Rem.Degree; i++)
                Rem.Digits[i] = (that).Digits[i];
        }
        
        Natural Zero; SetZero(Zero);
        if (Comparison(Zero, second) == COMPARISON_EQUAL_BIGGER)
            cout << "Ошибка. Деление на 0." << endl;
        else
        {
            while (Comparison(Rem, second) != COMPARISON_SECOND_BIGGER)
            {
                Natural Sub; Subtraction(Sub, Rem, second);
                
                Rem.Degree = Sub.Degree;
                if (Rem.Digits != nullptr)
                    free(Rem.Digits);
                Rem.Digits = Sub.Digits;
            }
            if (second.Digits != nullptr)
                free(second.Digits);
            
            OptimazeNatural(Rem);
        }
    }
    
    RemResult.Degree = Rem.Degree;
    RemResult.Digits = Rem.Digits;
}

//----------------------------------------------------------
//void PowerOfTen(Natural&, Natural, int)
//Умножает данное натуральное число на 10^k.
//----------------------------------------------------------
void PowerOfTen(Natural& Result, Natural Nat, int Power)
{
    if (Power == 0)
    {
        Result.Degree = Nat.Degree;
        Result.Digits = (char*)malloc(sizeof(char)*(Result.Degree + 1));
        for (int i = 0; i <= Result.Degree; i++)
            Result.Digits[i] = Nat.Digits[i];
    }
    else
    {
        Result.Degree = Nat.Degree + Power;
        Result.Digits = (char*)malloc(sizeof(char)*(Result.Degree + 1));
        for (int i = 0; i < Power; i++)
            Result.Digits[i] = 0;
        for (int i = Power; i <= Result.Degree; i++)
            Result.Digits[i] = Nat.Digits[i - Power];
    }
}

//----------------------------------------------------------
//void GreatestCommonDivisor(Natural&, Natural, Natural)
//НОД натуральных чисел.
//----------------------------------------------------------
void GreatestCommonDivisor2(Natural& GCD, Natural Nat1, Natural Nat2)
{
    Natural Zero; SetZero(Zero);
    Natural One; SetOne(One);
    if (Comparison(Zero, Nat1) == COMPARISON_EQUAL_BIGGER)
    {
        GCD.Degree = Nat2.Degree;
        if (GCD.Digits != nullptr)
            free(GCD.Digits);
        GCD.Digits = (char*)malloc(sizeof(char)*(GCD.Degree+1));
        for (int i = 0; i <= GCD.Degree; i++)
            GCD.Digits[i] = Nat2.Digits[i];
    }
    else if (Comparison(Zero, Nat2) == COMPARISON_EQUAL_BIGGER)
    {
        GCD.Degree = Nat1.Degree;
        if (GCD.Digits != nullptr)
            free(GCD.Digits);
        GCD.Digits = (char*)malloc(sizeof(char)*(GCD.Degree+1));
        for (int i = 0; i <= GCD.Degree; i++)
            GCD.Digits[i] = Nat1.Digits[i];
    }
    else if (Comparison(One, Nat1) == COMPARISON_EQUAL_BIGGER || Comparison(One, Nat2) == COMPARISON_EQUAL_BIGGER)
        SetOne(GCD);
    else
    {
        Natural A;
        A.Degree = Nat1.Degree;
        A.Digits = (char*)malloc(sizeof(char)*(A.Degree+1));
        for (int i = 0; i <= A.Degree; i++)
            A.Digits[i] = Nat1.Digits[i];
        
        Natural B;
        B.Degree = Nat2.Degree;
        B.Digits = (char*)malloc(sizeof(char)*(B.Degree+1));
        for (int i = 0; i <= B.Degree; i++)
            B.Digits[i] = Nat2.Digits[i];
        
        while (Comparison(A, B) != COMPARISON_EQUAL_BIGGER)
        {
            Natural Sub; Subtraction(Sub, A, B);
            if (Comparison(A, B) == COMPARISON_FIRST_BIGGER)
            {
                if (A.Digits != nullptr)
                    free(A.Digits);
                A.Degree = Sub.Degree;
                A.Digits = (char*)malloc(sizeof(char)*(A.Degree+1));
                for (int i = 0; i <= A.Degree; i++)
                    A.Digits[i] = Sub.Digits[i];
            }
            else
            {
                if (B.Digits != nullptr)
                    free(B.Digits);
                B.Degree = Sub.Degree;
                B.Digits = (char*)malloc(sizeof(char)*(B.Degree+1));
                for (int i = 0; i <= B.Degree; i++)
                    B.Digits[i] = Sub.Digits[i];
            }
        }
        
        GCD.Degree = A.Degree;
        if (GCD.Digits != nullptr)
            free(GCD.Digits);
        GCD.Digits = (char*)malloc(sizeof(char)*(GCD.Degree+1));
        for (int i = 0; i <= GCD.Degree; i++)
            GCD.Digits[i] = A.Digits[i];
        
        if (B.Digits != nullptr)
            free(B.Digits);
    }
    
    if (Zero.Digits != nullptr)
        free(Zero.Digits);
    if (One.Digits != nullptr)
        free(One.Digits);
}

void ConvertFromNatural(unsigned long long &n, Natural Nat)
{
    n = 0;
    for (int i = 0; i <= Nat.Degree; i++)
    {
        unsigned long long Sum; Sum = Nat.Digits[i];
        for (int j = 0; j < i; j++)
            Sum = Sum * 10;
        
        n += Sum;
    }
}

//----------------------------------------------------------
//void GreatestCommonDivisor(Natural&, Natural, Natural)
//НОД натуральных чисел.
//----------------------------------------------------------
void GreatestCommonDivisor(Natural& GCD, Natural Nat1, Natural Nat2)
{
    if (Nat1.Degree > 18 || Nat2.Degree > 18)
        GreatestCommonDivisor2(GCD, Nat1, Nat2);
    else
    {
        unsigned long long First; ConvertFromNatural(First, Nat1);
        unsigned long long Second; ConvertFromNatural(Second, Nat2);
        
        while ( Second != 0)
        {
            unsigned long long r = First % Second;
            First = Second;
            Second = r;
        }
        
        ConvertToNatural(GCD, First);
    }
}

//----------------------------------------------------------
//void LeastCommonMultiple(Natural&, Natural, Natural)
//НОК натуральных чисел.
//----------------------------------------------------------
void LeastCommonMultiple(Natural& LCM, Natural Nat1, Natural Nat2)
{
    Natural Mul; Multiply(Mul, Nat1, Nat2);
    Natural GCD; GreatestCommonDivisor(GCD, Nat1, Nat2);
    Divide_obsolete(LCM, Mul, GCD);
    
    if (Mul.Digits != nullptr)
        free(Mul.Digits);
    if (GCD.Digits != nullptr)
        free(GCD.Digits);
}

//----------------------------------------------------------
//void FormNaturalFromPartAtBeginning(Natural&, Natural, int)
//Формирование нового числа из первых dig цифр указанного.
//----------------------------------------------------------
void FormNaturalFromPartAtBeginning(Natural& Res, Natural Nat, int dig)
{
    if (Nat.Degree > dig - 1)
    {
        Res.Degree = dig - 1;
        Res.Digits = (char*)malloc(sizeof(char)*(Res.Degree + 1));
        for (int i = Nat.Degree; i > Nat.Degree - dig; i--)
        {
            Res.Digits[i - Nat.Degree + dig - 1] = Nat.Digits[i];
        }
    }
    else if (Nat.Degree == dig - 1)
        CopyNaturalFrom(Res, Nat);
    else
        cout << "Ошибка. Попытка выделить первые " << dig << " цифр из числа со степенью " << Nat.Degree << "." << endl;
}
