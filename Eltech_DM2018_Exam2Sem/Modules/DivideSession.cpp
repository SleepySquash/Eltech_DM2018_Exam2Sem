//
//  DivideSession.cpp
//  Eltech_DM2018_Exam2Sem
//
//  Created by Никита Исаенко on 15.06.2018.
//  Copyright © 2018 Melanholy Hill. All rights reserved.
//

#include "DivideSession.hpp"

//----------------------------------------------------------
//void Divide(DivideSession&, Natural, Natural)
//Деление нацело натуральных чисел с использованием DivideSession.
//----------------------------------------------------------
void Divide(DivideSession& Div, Natural that, Natural other)
{
    if (Comparison(that, other) == COMPARISON_SECOND_BIGGER)
    {
        SetZero(Div.QuoAsNatural);
        Div.Quo.Sign = false;
        Div.Quo.Degree = Div.QuoAsNatural.Degree;
        Div.Quo.Digits = Div.QuoAsNatural.Digits;
        
        CopyNaturalFrom(Div.Rem, other);
    }
    else
        DivideNoStrict(Div, that, other);
}

//----------------------------------------------------------
//void InvertNatural(Natural&, Natural)
//Формирование инвертированного числа из данного.
//----------------------------------------------------------
void InvertNatural(Natural &Res, Natural Nat)
{
    Res.Degree = Nat.Degree;
    Res.Digits = (char*)malloc(sizeof(char)*(Res.Degree + 1));
    for (int i = 0; i <= Res.Degree; i++)
        Res.Digits[i] = Nat.Digits[Nat.Degree - i];
}

//----------------------------------------------------------
//void DivideNoStrict(DivideSession&, Natural, Natural)
//Деление несторого нацело натуральных чисел с использованием DivideSession.
//----------------------------------------------------------
void DivideNoStrict(DivideSession& Div, Natural that, Natural other)
{
    Natural second;
    Natural Rem;
    Natural Quo;
    
    int ComparisonResult = Comparison(that, other);
    if (ComparisonResult == COMPARISON_EQUAL_BIGGER)
    {
        SetOne(Quo);
        SetZero(Rem);
    }
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
        if (Comparison(Zero, second) == COMPARISON_EQUAL_BIGGER)
        {
            if (Comparison(Zero, other) == COMPARISON_EQUAL_BIGGER)
                cout << "Ошибка. Деление на 0." << endl;
        }
        else if (Comparison(Zero, that) == COMPARISON_EQUAL_BIGGER)
        {
            SetZero(Quo);
            CopyNaturalFrom(Rem, other);
        }
        else
        {
            // 1) Выделяем такое количество первых цифр в Rem и формируем число такое, чтобы оно было больше second
            Natural Subtracted; int firstDigitsCount = second.Degree + 1;
            FormNaturalFromPartAtBeginning(Subtracted, Rem, firstDigitsCount);
            while (Comparison(Subtracted, second) == COMPARISON_SECOND_BIGGER)
            {
                firstDigitsCount++; FreeNatural(Subtracted);
                FormNaturalFromPartAtBeginning(Subtracted, Rem, firstDigitsCount);
            }
            
            // 2) Находим результат обычного деления Subtracted на second
            //    и получаем в Divided_Quo - цифру деления, в Divided_Rem - остаток от вычета из первых цифр
            Natural Divided_Quo; SetZero(Divided_Quo);
            Natural Divided_Rem;
            Divided_Rem.Degree = Subtracted.Degree;
            Divided_Rem.Digits = Subtracted.Digits;
            while (Comparison(Divided_Rem, second) != COMPARISON_SECOND_BIGGER)
            {
                Natural Sub; Subtraction(Sub, Divided_Rem, second);
                
                FreeNatural(Divided_Rem);
                Divided_Rem.Degree = Sub.Degree;
                Divided_Rem.Digits = Sub.Digits;
                
                Natural Sum; Summary(Sum, Divided_Quo, One);
                
                FreeNatural(Divided_Quo);
                Divided_Quo.Degree = Sum.Degree;
                Divided_Quo.Digits = Sum.Digits;
            }
            Quo.Degree++;
            Quo.Digits = (char*)realloc(Quo.Digits, sizeof(char)*(Quo.Degree + 1));
            Quo.Digits[Quo.Degree] = Divided_Quo.Digits[0]; FreeNatural(Divided_Quo);
            
            bool ShallProceed{ (Rem.Degree - firstDigitsCount >= 0) };
            if (!ShallProceed)
            {
                Rem.Degree = Divided_Rem.Degree;
                Rem.Digits = Divided_Rem.Digits;
            }
            
            while (ShallProceed)
            {
                Natural InvRem; InvertNatural(InvRem, Divided_Rem);
                InvRem.Degree++;
                InvRem.Digits = (char*)realloc(InvRem.Digits, sizeof(char)*(InvRem.Degree + 1));
                InvRem.Digits[InvRem.Degree] = Rem.Digits[Rem.Degree - firstDigitsCount];
                
                Natural NewSubtracted; InvertNatural(NewSubtracted, InvRem);
                OptimazeNatural(NewSubtracted);
                
                while (Comparison(NewSubtracted, second) == COMPARISON_SECOND_BIGGER && ShallProceed)
                {
                    firstDigitsCount++;
                    
                    Quo.Degree++;
                    Quo.Digits = (char*)realloc(Quo.Digits, sizeof(char)*(Quo.Degree + 1));
                    Quo.Digits[Quo.Degree] = 0;
                    
                    if (Rem.Degree - firstDigitsCount >= 0)
                    {
                        InvRem.Degree++;
                        InvRem.Digits = (char*)realloc(InvRem.Digits, sizeof(char)*(InvRem.Degree + 1));
                        InvRem.Digits[InvRem.Degree] = Rem.Digits[Rem.Degree - firstDigitsCount];
                        
                        FreeNatural(NewSubtracted);
                        InvertNatural(NewSubtracted, InvRem);
                        OptimazeNatural(NewSubtracted);
                    }
                    else
                    {
                        ShallProceed = false;
                        FreeNatural(Divided_Rem);
                        Rem.Degree = NewSubtracted.Degree;
                        Rem.Digits = NewSubtracted.Digits;
                    }
                }
                
                if (ShallProceed)
                {
                    FreeNatural(Divided_Rem);
                    
                    SetZero(Divided_Quo);
                    Divided_Rem.Degree = NewSubtracted.Degree;
                    Divided_Rem.Digits = NewSubtracted.Digits;
                    while (Comparison(Divided_Rem, second) != COMPARISON_SECOND_BIGGER)
                    {
                        Natural Sub; Subtraction(Sub, Divided_Rem, second);
                        
                        FreeNatural(Divided_Rem);
                        Divided_Rem.Degree = Sub.Degree;
                        Divided_Rem.Digits = Sub.Digits;
                        
                        Natural Sum; Summary(Sum, Divided_Quo, One);
                        
                        FreeNatural(Divided_Quo);
                        Divided_Quo.Degree = Sum.Degree;
                        Divided_Quo.Digits = Sum.Digits;
                    }
                    Quo.Degree++;
                    Quo.Digits = (char*)realloc(Quo.Digits, sizeof(char)*(Quo.Degree + 1));
                    Quo.Digits[Quo.Degree] = Divided_Quo.Digits[0]; FreeNatural(Divided_Quo);
                    
                    firstDigitsCount++;
                    ShallProceed = (Rem.Degree - firstDigitsCount >= 0);
                    if (!ShallProceed)
                    {
                        Rem.Degree = Divided_Rem.Degree;
                        Rem.Digits = Divided_Rem.Digits;
                    }
                    //cout << "firstDigitsCount: " << firstDigitsCount << " and Rem.Degree: " << Rem.Degree << endl;
                }
                
                ShallProceed = (Rem.Degree - firstDigitsCount >= 0);
            }
        }
    }
    
    if (second.Digits != nullptr)
        free(second.Digits);
    
    Natural QuoInverted; InvertNatural(QuoInverted, Quo); FreeNatural(Quo);
    OptimazeNatural(QuoInverted);
    Div.QuoAsNatural.Degree = QuoInverted.Degree;
    Div.QuoAsNatural.Digits = QuoInverted.Digits;
    Div.Quo.Sign = false;
    Div.Quo.Degree = Div.QuoAsNatural.Degree;
    Div.Quo.Digits = Div.QuoAsNatural.Digits;
    
    OptimazeNatural(Rem);
    Div.Rem.Degree = Rem.Degree;
    Div.Rem.Digits = Rem.Digits;
}

//----------------------------------------------------------
//void FreeDivideSession(DivideSession&)
//Очистка используемой структурой типа DivideSession памяти.
//----------------------------------------------------------
void FreeDivideSession(DivideSession& Div)
{
    FreeInteger(Div.Quo);
    FreeNatural(Div.Rem);
}

//----------------------------------------------------------
//void Divide(Natural&, Natural, Natural)
//Деление нацело натуральных чисел.
//----------------------------------------------------------
void Divide(Natural& Result, Natural that, Natural other)
{
    DivideSession DivSes;
    Divide(DivSes, that, other);
    FreeNatural(DivSes.Rem);
    Result.Degree = DivSes.Quo.Degree;
    Result.Digits = DivSes.Quo.Digits;
}

//----------------------------------------------------------
//void Modulo(Natural&, Natural, Natural)
//Остаток от деления натуральных чисел.
//----------------------------------------------------------
void Modulo(Natural& Result, Natural that, Natural other)
{
    DivideSession DivSes;
    Divide(DivSes, that, other);
    FreeInteger(DivSes.Quo);
    Result.Degree = DivSes.Rem.Degree;
    Result.Digits = DivSes.Rem.Digits;
}

//----------------------------------------------------------
//void Divide(Natural&, Natural, Natural)
//Деление нацело натуральных чисел.
//----------------------------------------------------------
void Divide(Integer& QuoResult, Integer that, Natural other)
{
    QuoResult.Sign = that.Sign;
    Natural Nat; ConvertEqualToNatural(Nat, that);
    Natural NMul; Divide(NMul, Nat, other);
    QuoResult.Degree = NMul.Degree;
    QuoResult.Digits = NMul.Digits;
}
