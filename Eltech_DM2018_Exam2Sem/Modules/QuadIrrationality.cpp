//
//  QuadIrrationality.cpp
//  Eltech_DM2018_Exam2Sem
//
//  Created by Никита Исаенко on 07.06.2018.
//  Copyright © 2018 Melanholy Hill. All rights reserved.
//

#include "QuadIrrationality.hpp"

std::ostream& operator<<(std::ostream& os, const QuadIrrationality& Quad)
{
    if (IsQuadCorrect(Quad))
    {
        if (!(Quad.d.Degree == 0 && Quad.d.Digits[0] == 1))
            os << "(";
        
        bool bEqualsToOne = (Quad.b.Degree == 0 && Quad.b.Digits[0] == 1);
        if (!(Quad.a.Degree == 0 && Quad.a.Digits[0] == 0))
        {
            os << Quad.a;
            if (Quad.b.Sign)
            {
                os << " - ";
                if (!(bEqualsToOne))
                {
                    for (int i = Quad.b.Degree; i >= 0; i--)
                        os << Quad.b.Digits[i];
                }
            }
            else
            {
                os << " + ";
                if (!bEqualsToOne)
                    os << Quad.b;
            }
        }
        else
        {
            if (!bEqualsToOne)
                os << Quad.b;
        }
        os << "√" << Quad.c;
        
        if (!(Quad.d.Degree == 0 && Quad.d.Digits[0] == 1))
            os << ")/" << Quad.d;
    }
    return os;
}

std::istream& operator>>(std::istream& is, QuadIrrationality& Quad)
{
    char* str = InputString();
    
    bool SignReading{ false };
    bool ReadingDeno{ false };
    int CharsParsed{ 0 };
    int StrLength = GetLength(str);
    for (int i = 0; i <= StrLength; i++)
    {
        if (str[i] == '+' || str[i] == '-' || str[i] == ' ' || str[i] == '/' || str[i] == '(' || str[i] == ')' || str[i] == '\0')
        {
            //we've done parsing a number
            if (CharsParsed > 0)
            {
                int vPos = -1;
                for (int j = i - CharsParsed; j < i && vPos == -1; j++)
                {
                    //searching for 'V' in the word we've parsed
                    if (str[j] == 'v' || str[j] == 'V')
                        vPos = j;
                }
                if (vPos == -1)
                {
                    //it's an a or d: 12, -1, 2 etc...
                    Integer Int; Int.Sign = SignReading;
                    for (int j = i-1; j >= i - CharsParsed; j--)
                    {
                        if (str[j] >= 48 && str[j] <= 57)
                        {
                            Int.Degree++;
                            Int.Digits = (char*)realloc(Int.Digits, sizeof(char)*(Int.Degree + 1));
                            Int.Digits[Int.Degree] = str[j] - 48;
                        }
                    }
                    
                    if (ReadingDeno)
                    {
                        //writing to D
                        if (Quad.d.Digits != nullptr)
                            free(Quad.d.Digits);
                        
                        Quad.d.Degree = Int.Degree;
                        Quad.d.Digits = Int.Digits;
                    }
                    else
                    {
                        //writing to A
                        if (Quad.a.Digits != nullptr)
                            free(Quad.a.Digits);
                        
                        Quad.a.Sign = Int.Sign;
                        Quad.a.Degree = Int.Degree;
                        Quad.a.Digits = Int.Digits;
                    }
                }
                else
                {
                    //it's an b and c: bVc
                    Integer Int; Int.Sign = SignReading;
                    Natural Nat;
                    
                    for (int j = vPos-1; j >= i - CharsParsed; j--)
                    {
                        if (str[j] >= 48 && str[j] <= 57)
                        {
                            Int.Degree++;
                            Int.Digits = (char*)realloc(Int.Digits, sizeof(char)*(Int.Degree + 1));
                            Int.Digits[Int.Degree] = str[j] - 48;
                        }
                    }
                    for (int j = i-1; j > vPos; j--)
                    {
                        if (str[j] >= 48 && str[j] <= 57)
                        {
                            Nat.Degree++;
                            Nat.Digits = (char*)realloc(Nat.Digits, sizeof(char)*(Nat.Degree + 1));
                            Nat.Digits[Nat.Degree] = str[j] - 48;
                        }
                    }
                    
                    if (Nat.Degree != -1 && Int.Degree == -1)
                    {
                        Int.Degree = 0;
                        Int.Digits = (char*)malloc(sizeof(char));
                        Int.Digits[0] = 1;
                    }
                    
                    if (Quad.b.Digits != nullptr)
                        free(Quad.b.Digits);
                    Quad.b.Sign = Int.Sign;
                    Quad.b.Degree = Int.Degree;
                    Quad.b.Digits = Int.Digits;
                    
                    if (Quad.c.Digits != nullptr)
                        free(Quad.c.Digits);
                    Quad.c.Degree = Nat.Degree;
                    Quad.c.Digits = Nat.Digits;
                }
                CharsParsed = 0;
                SignReading = false;
            }
            
            if (str[i] == '-')
                SignReading = true;
            if (str[i] == '/')
                ReadingDeno = true;
        }
        else
        {
            if (str[i] == '-')
                SignReading = true;
            if (str[i] == '/')
                ReadingDeno = true;
            CharsParsed++;
        }
    }
    if (Quad.c.Degree != -1)
    {
        if (Quad.a.Degree == -1)
        {
            Quad.a.Degree = 0;
            Quad.a.Digits = (char*)malloc(sizeof(char));
            Quad.a.Digits[0] = 0;
        }
        
        if (Quad.d.Degree == -1)
        {
            Quad.d.Degree = 0;
            Quad.d.Digits = (char*)malloc(sizeof(char));
            Quad.d.Digits[0] = 1;
        }
    }
    
    if (!IsQuadCorrect(Quad))
    {
        cout << "Ошибка. Квадратичная иррациональность была введена некорректно." << endl;
        FreeQuad(Quad);
    }
    else
    {
        ReduceQuadIrrationality(Quad);
        Fraction FracResult; IsQuadIrrationalityValid(FracResult, Quad);
        if (FracResult.Num.Degree != -1)
        {
            cout << "Введённая квадратичная иррациональность не является квадратичной иррациональностью." << endl;
            cout << Quad << " = " << FracResult << endl;
            FreeQuad(Quad);
        }
    }
    
    return is;
}

//----------------------------------------------------------
//void IsQuadIrrationalityValid(Fraction&, QuadIrrationality)
//Оценка корректности введённой иррациональности (является введённое иррациональностью или извлекается как число).
//----------------------------------------------------------
void IsQuadIrrationalityValid(Fraction &Result, QuadIrrationality Quad)
{
    Integer BSquared; Multiply(BSquared, Quad.b, Quad.b);
    Natural BSquaredNat; BSquaredNat.Degree = BSquared.Degree; BSquaredNat.Digits = BSquared.Digits;
    Natural PreciseRoot; Multiply(PreciseRoot, Quad.c, BSquaredNat);
    Natural RootEstimation; EstimateRootLowerThat_binary(RootEstimation, PreciseRoot);
    Natural RootEstimationSquared; Multiply(RootEstimationSquared, RootEstimation, RootEstimation);
    
    if (Comparison(RootEstimationSquared, PreciseRoot) == COMPARISON_EQUAL_BIGGER)
    {
        Integer FromCPart; FromCPart.Sign = Quad.b.Sign; FromCPart.Degree = RootEstimation.Degree; FromCPart.Digits = RootEstimation.Digits;
        
        Integer NumeIntegerPart; Summary(NumeIntegerPart, Quad.a, FromCPart);
        
        Result.Num.Sign = NumeIntegerPart.Sign;
        Result.Num.Degree = NumeIntegerPart.Degree;
        Result.Num.Digits = NumeIntegerPart.Digits;
        
        Result.Deno.Degree = Quad.d.Degree;
        Result.Deno.Digits = (char*)malloc(sizeof(char)*(Result.Deno.Degree + 1));
        for (int i = 0; i <= Result.Deno.Degree; i++)
            Result.Deno.Digits[i] = Quad.d.Digits[i];
        
        ReduceFraction(Result);
    }
    
    if (BSquared.Digits != nullptr)
        free(BSquared.Digits);
    if (PreciseRoot.Digits != nullptr)
        free(PreciseRoot.Digits);
    if (RootEstimation.Digits != nullptr)
        free(RootEstimation.Digits);
    if (RootEstimationSquared.Digits != nullptr)
        free(RootEstimationSquared.Digits);
}

//----------------------------------------------------------
//int Comparison(const QuadIrrationality&, const QuadIrrationality&)
//Сравнение по порядку двух квадратичных иррациональностей.
//----------------------------------------------------------
int Comparison(const QuadIrrationality &Quad1, const QuadIrrationality &Quad2)
{
    int ComparsionResultA = Comparison(Quad1.a, Quad2.a);
    int ComparsionResultB = Comparison(Quad1.b, Quad2.b);
    int ComparsionResultC = Comparison(Quad1.c, Quad2.c);
    int ComparsionResultD = Comparison(Quad1.d, Quad2.d);
    if (ComparsionResultA == COMPARISON_EQUAL_BIGGER &&
        ComparsionResultB == COMPARISON_EQUAL_BIGGER &&
        ComparsionResultC == COMPARISON_EQUAL_BIGGER &&
        ComparsionResultD == COMPARISON_EQUAL_BIGGER)
        return COMPARISON_EQUAL_BIGGER;
    
    ContinuedFraction CFrac1; ExpandAsContinuedFraction(CFrac1, Quad1);
    ContinuedFraction CFrac2; ExpandAsContinuedFraction(CFrac2, Quad2);
    
    int ComparisonResult = Comparison(CFrac1, CFrac2);
    FreeContinuedFraction(CFrac1);
    FreeContinuedFraction(CFrac2);
    return ComparisonResult;
}

//----------------------------------------------------------
//int ComparisonEqual(const QuadIrrationality&, const QuadIrrationality&)
//Сравнение по равенству двух квадратичных иррациональностей.
//----------------------------------------------------------
int ComparisonEqual(const QuadIrrationality &Quad1, const QuadIrrationality &Quad2)
{//1242 + v51512/531
    if (Quad1.a.Degree == Quad2.a.Degree && Quad1.b.Degree == Quad2.b.Degree && Quad1.c.Degree == Quad2.c.Degree && Quad1.d.Degree == Quad2.d.Degree)
    {
        if (Quad1.a.Digits[0] == Quad2.a.Digits[0] && Quad1.b.Digits[0] == Quad2.b.Digits[0] && Quad1.d.Digits[0] == Quad2.d.Digits[0])
        {
            int ComparsionResultA = Comparison(Quad1.a, Quad2.a);
            int ComparsionResultB = Comparison(Quad1.b, Quad2.b);
            int ComparsionResultD = Comparison(Quad1.d, Quad2.d);
            if (ComparsionResultA == COMPARISON_EQUAL_BIGGER &&
                ComparsionResultB == COMPARISON_EQUAL_BIGGER &&
                ComparsionResultD == COMPARISON_EQUAL_BIGGER)
                return COMPARISON_EQUAL_BIGGER;
        }
    }
    
    return COMPARISON_UNUSED_EQUAL;
}

//----------------------------------------------------------
//bool IsQuadCorrect(QuadIrrationality&)
//Истина, если данная квадратичная иррациональность корректна.
//----------------------------------------------------------
bool IsQuadCorrect(const QuadIrrationality& Quad)
{
    if (Quad.a.Degree == -1 || Quad.b.Degree == -1 || Quad.c.Degree == -1 || Quad.d.Degree == -1)
        return false;
    return true;
}

//----------------------------------------------------------
//void Summary(QuadIrrationality&, QuadIrrationality, QuadIrrationality)
//Сумма квадратичных иррациональностей.
//----------------------------------------------------------
void Summary(QuadIrrationality& Result, QuadIrrationality that, QuadIrrationality other)
{
    if (IsQuadCorrect(that) && IsQuadCorrect(other))
    {
        if (Comparison(that.c, other.c) == COMPARISON_EQUAL_BIGGER)
        {
            Natural LCM; LeastCommonMultiple(LCM, that.d, other.d);
            Natural MultiplyByThat; Divide(MultiplyByThat, LCM, that.d);
            Integer MultipliedAThat; Multiply(MultipliedAThat, that.a, MultiplyByThat);
            Integer MultipliedBThat; Multiply(MultipliedBThat, that.b, MultiplyByThat);
            
            Natural MultiplyByOther; Divide(MultiplyByOther, LCM, other.d);
            Integer MultipliedAOther; Multiply(MultipliedAOther, other.a, MultiplyByOther);
            Integer MultipliedBOther; Multiply(MultipliedBOther, other.b, MultiplyByOther);
            
            Integer SumA; Summary(SumA, MultipliedAThat, MultipliedAOther);
            if (Result.a.Digits != nullptr)
                free(Result.a.Digits);
            Result.a.Sign = SumA.Sign;
            Result.a.Degree = SumA.Degree;
            Result.a.Digits = SumA.Digits;
            
            Integer SumB; Summary(SumB, MultipliedBThat, MultipliedBOther);
            if (Result.b.Digits != nullptr)
                free(Result.b.Digits);
            Result.b.Sign = SumB.Sign;
            Result.b.Degree = SumB.Degree;
            Result.b.Digits = SumB.Digits;
            
            if (Result.c.Digits != nullptr)
                free(Result.c.Digits);
            Result.c.Degree = that.c.Degree;
            Result.c.Digits = (char*)malloc(sizeof(char)*(Result.c.Degree + 1));
            for (int i = 0; i <= Result.c.Degree; i++)
                Result.c.Digits[i] = that.c.Digits[i];
            
            if (Result.d.Digits != nullptr)
                free(Result.d.Digits);
            Result.d.Degree = LCM.Degree;
            Result.d.Digits = LCM.Digits;
            
            if (MultiplyByThat.Digits != nullptr)
                free(MultiplyByThat.Digits);
            if (MultipliedAThat.Digits != nullptr)
                free(MultipliedAThat.Digits);
            if (MultipliedBThat.Digits != nullptr)
                free(MultipliedBThat.Digits);
            if (MultiplyByOther.Digits != nullptr)
                free(MultiplyByOther.Digits);
            if (MultipliedAOther.Digits != nullptr)
                free(MultipliedAOther.Digits);
            if (MultipliedBOther.Digits != nullptr)
                free(MultipliedBOther.Digits);
            
            ReduceQuadIrrationality(Result);
        }
        else
            cout << "Действие невозможно (сумма или разность), поскольку коэффициенты под корнями не совпадают." << endl;
    }
    else
        cout << "Ошибка. Данные квадратичные иррациональности некорректны." << endl;
}

//----------------------------------------------------------
//void Subtraction(QuadIrrationality&, QuadIrrationality, QuadIrrationality)
//Разность квадратичных иррациональностей.
//----------------------------------------------------------
void Subtraction(QuadIrrationality& Result, QuadIrrationality that, QuadIrrationality other)
{
    if (IsQuadCorrect(that) && IsQuadCorrect(other))
    {
        other.a.Sign = !other.a.Sign;
        other.b.Sign = !other.b.Sign;
        Summary(Result, that, other);
    }
    else
        cout << "Ошибка. Данные квадратичные иррациональности некорректны." << endl;
}

//----------------------------------------------------------
//void FreeQuad(QuadIrrationality&)
//Очищает используемую квадратичной иррациональностью память
//----------------------------------------------------------
void FreeQuad(QuadIrrationality &Quad)
{
    Quad.a.Degree = -1;
    Quad.b.Degree = -1;
    Quad.c.Degree = -1;
    Quad.d.Degree = -1;
    
    if (Quad.a.Digits != nullptr)
        free(Quad.a.Digits);
    Quad.a.Digits = nullptr;
    
    if (Quad.b.Digits != nullptr)
        free(Quad.b.Digits);
    Quad.b.Digits = nullptr;
    
    if (Quad.c.Digits != nullptr)
        free(Quad.c.Digits);
    Quad.c.Digits = nullptr;
    
    if (Quad.d.Digits != nullptr)
        free(Quad.d.Digits);
    Quad.d.Digits = nullptr;
}

//----------------------------------------------------------
//void FreeQuad(QuadIrrationality&)
//Очищает используемую квадратичной иррациональностью память
//----------------------------------------------------------
void FreeQuad(QuadIrrationality *Quad)
{
    Quad->a.Degree = -1;
    Quad->b.Degree = -1;
    Quad->c.Degree = -1;
    Quad->d.Degree = -1;
    
    if (Quad->a.Digits != nullptr)
        free(Quad->a.Digits);
    Quad->a.Digits = nullptr;
    
    if (Quad->b.Digits != nullptr)
        free(Quad->b.Digits);
    Quad->b.Digits = nullptr;
    
    if (Quad->c.Digits != nullptr)
        free(Quad->c.Digits);
    Quad->c.Digits = nullptr;
    
    if (Quad->d.Digits != nullptr)
        free(Quad->d.Digits);
    Quad->d.Digits = nullptr;
}

//----------------------------------------------------------
//void EstimateRootLowerThat(Natural&, Natural)
//Оценка корня снизу.
//----------------------------------------------------------
void EstimateRootLowerThat(Natural& Result, Natural Root)
{
    Natural One; SetOne(One);
    if (Comparison(Root, One) == COMPARISON_SECOND_BIGGER)
        SetZero(Result);
    else
    {
        bool StillLower{ true };
        for (int i = 2; StillLower; i++)
        {
            Natural Nat; ConvertToNatural(Nat, i);
            Natural Mul; Multiply(Mul, Nat, Nat);
            
            StillLower = (Comparison(Mul, Root) != COMPARISON_FIRST_BIGGER);
            if (!StillLower)
            {
                Natural Sub; Subtraction(Sub, Nat, One);
                
                Result.Degree = Sub.Degree;
                Result.Digits = Sub.Digits;
            }
            
            if (Nat.Digits != nullptr)
                free(Nat.Digits);
            if (Mul.Digits != nullptr)
                free(Mul.Digits);
        }
    }
    
    if (One.Digits != nullptr)
        free(One.Digits);
}

//----------------------------------------------------------
//void EstimateRootLowerThat_binary(Natural&, Natural)
//Оценка корня снизу методом бинарного (двоичного) поиска.
//----------------------------------------------------------
void EstimateRootLowerThat_binary(Natural& Result, Natural Root)
{
    Natural One; SetOne(One);
    if (Comparison(Root, One) == COMPARISON_SECOND_BIGGER)
        SetZero(Result);
    else
    {
        Natural Left; SetZero(Left);
        Natural Right; CopyNaturalFrom(Right, Root);
        
        //небольшая отсылка к ZeroTwo из Darling in the FranXX ( ͡° ͜ʖ ͡°)
        //Кто лучше: ZeroTwo или 2B?
        Natural ZeroTwo; SetZero(ZeroTwo); ZeroTwo.Digits[0] = 2;
        Natural Sum; Summary(Sum, Left, Right);
        Natural Middle; Divide(Middle, Sum, ZeroTwo); FreeNatural(Sum);
        
        Natural Sub; Subtraction(Sub, Right, Left);
        while (Comparison(Sub, One) == COMPARISON_FIRST_BIGGER)
        {
            Natural Mul; Multiply(Mul, Middle, Middle);
            
            if (Comparison(Mul, Root) != COMPARISON_FIRST_BIGGER)
            {
                FreeNatural(Left);
                Left.Degree = Middle.Degree;
                Left.Digits = Middle.Digits;
            }
            else
            {
                FreeNatural(Right);
                Right.Degree = Middle.Degree;
                Right.Digits = Middle.Digits;
            }
            Summary(Sum, Left, Right);
            Divide(Middle, Sum, ZeroTwo); FreeNatural(Sum);
            
            FreeNatural(Sub);
            Subtraction(Sub, Right, Left);
        }
        FreeNatural(Sub);
        
        Result.Degree = Middle.Degree;
        Result.Digits = Middle.Digits;
        
        FreeNatural(Left);
        FreeNatural(Right);
        FreeNatural(ZeroTwo);
    }
    
    FreeNatural(One);
}

//----------------------------------------------------------
//void MultiplyByConjugate(Integer&, QuadIrrationality)
//Умножение квадратичной иррациональности на сопряжённую квадратичную иррациональность (без учёта знаменателя).
//----------------------------------------------------------
void MultiplyByConjugate(Integer& ConjugatedDeno, QuadIrrationality NextQuad)
{
    Integer MulA; Multiply(MulA, NextQuad.a, NextQuad.a); MulA.Sign = true;
    Integer MulB; Multiply(MulB, NextQuad.b, NextQuad.b);
    Integer MulBandC; Multiply(MulBandC, MulB, NextQuad.c);
    Summary(ConjugatedDeno, MulA, MulBandC);
    
    if (MulA.Digits != nullptr)
        free(MulA.Digits);
    if (MulB.Digits != nullptr)
        free(MulB.Digits);
    if (MulBandC.Digits != nullptr)
        free(MulBandC.Digits);
}

//----------------------------------------------------------
//void ReduceQuadIrrationality(QuadIrrationality& Quad)
//Сокращение квадратичной иррациональности.
//----------------------------------------------------------
void ReduceQuadIrrationality(QuadIrrationality& Quad)
{
    if (IsQuadCorrect(Quad))
    {
        Natural NatA; NatA.Degree = Quad.a.Degree; NatA.Digits = Quad.a.Digits;
        Natural NatB; NatB.Degree = Quad.b.Degree; NatB.Digits = Quad.b.Digits;
        Natural GCD_AB; GreatestCommonDivisor(GCD_AB, NatA, NatB);
        Natural GCD; GreatestCommonDivisor(GCD, GCD_AB, Quad.d);
        Natural One; SetOne(One); Natural Zero; SetOne(Zero);
        if (Comparison(One, GCD) != COMPARISON_EQUAL_BIGGER)
        {
            Integer NewA; Divide(NewA, Quad.a, GCD);
            Integer NewB; Divide(NewB, Quad.b, GCD);
            Natural NewD; Divide(NewD, Quad.d, GCD);
            
            Quad.a.Degree = NewA.Degree;
            if (Quad.a.Digits != nullptr)
                free(Quad.a.Digits);
            Quad.a.Digits = NewA.Digits;
            
            Quad.b.Degree = NewB.Degree;
            if (Quad.b.Digits != nullptr)
                free(Quad.b.Digits);
            Quad.b.Digits = NewB.Digits;
            
            Quad.d.Degree = NewD.Degree;
            if (Quad.d.Digits != nullptr)
                free(Quad.d.Digits);
            Quad.d.Digits = NewD.Digits;
        }
        
        if (GCD_AB.Digits != nullptr)
            free(GCD_AB.Digits);
        if (GCD.Digits != nullptr)
            free(GCD.Digits);
        if (One.Digits != nullptr)
            free(One.Digits);
        if (Zero.Digits != nullptr)
            free(Zero.Digits);
    }
    else
        cout << "Ошибка. Данная квадратичная иррациональность некорректна." << endl;
}

//----------------------------------------------------------
//void QuadIrrationalityEquasion(QuadIrrationality&, QuadIrrationality&)
//Ресурсы двух квадратичных иррациональностей становятся общими.
//----------------------------------------------------------
void QuadIrrationalityEquasion(QuadIrrationality& Quad, QuadIrrationality& CompleteQuad)
{
    Quad.a.Sign = CompleteQuad.a.Sign;
    Quad.a.Degree = CompleteQuad.a.Degree;
    Quad.a.Digits = CompleteQuad.a.Digits;
    Quad.b.Sign = CompleteQuad.b.Sign;
    Quad.b.Degree = CompleteQuad.b.Degree;
    Quad.b.Digits = CompleteQuad.b.Digits;
    Quad.c.Degree = CompleteQuad.c.Degree;
    Quad.c.Digits = CompleteQuad.c.Digits;
    Quad.d.Degree = CompleteQuad.d.Degree;
    Quad.d.Digits = CompleteQuad.d.Digits;
}

//----------------------------------------------------------
//void GetIntegerPartFromQuadIrrationality(Integer&, QuadIrrationality)
//Выделение целой части из квадратичной иррациональности.
//----------------------------------------------------------
void GetIntegerPartFromQuadIrrationality(Integer& IntegerPart, QuadIrrationality Quad)
{
    if (IsQuadCorrect(Quad))
    {
        Integer BSquared; Multiply(BSquared, Quad.b, Quad.b);
        Natural BSquaredNat; BSquaredNat.Degree = BSquared.Degree; BSquaredNat.Digits = BSquared.Digits;
        Natural PreciseRoot; Multiply(PreciseRoot, Quad.c, BSquaredNat);
        Natural RootEstimation; EstimateRootLowerThat_binary(RootEstimation, PreciseRoot);
        Integer FromCPart; FromCPart.Sign = Quad.b.Sign; FromCPart.Degree = RootEstimation.Degree; FromCPart.Digits = RootEstimation.Digits;
        
        Integer NumeIntegerPart; Summary(NumeIntegerPart, Quad.a, FromCPart);
        Divide(IntegerPart, NumeIntegerPart, Quad.d);
        
        if (BSquared.Digits != nullptr)
            free(BSquared.Digits);
        if (PreciseRoot.Digits != nullptr)
            free(PreciseRoot.Digits);
        if (RootEstimation.Digits != nullptr)
            free(RootEstimation.Digits);
        if (NumeIntegerPart.Digits != nullptr)
            free(NumeIntegerPart.Digits);
    }
    else
        cout << "Ошибка. Данная квадратичная иррациональность некорректна." << endl;
}

//----------------------------------------------------------
//void ExpandAsContinuedFraction(ContinuedFraction&, QuadIrrationality)
//Преобразование квадратичной иррациональности в цепную периодическую дробь.
//----------------------------------------------------------
void ExpandAsContinuedFraction(ContinuedFraction& Result, QuadIrrationality Quad)
{
    if (IsQuadCorrect(Quad))
    {
        QuadIrrationality *PeriodArray{ nullptr };
        int PeriodArrayCount{ 0 };
        
        bool PeriodFound{ false };
        int PeriodStartPos{ 0 };
        for (int i = 0; i <= 10000 && !PeriodFound; i++)
        {
            Integer IntegerPart; GetIntegerPartFromQuadIrrationality(IntegerPart, Quad);
            Integer IntegerPartMultipliedByD; Multiply(IntegerPartMultipliedByD, IntegerPart, Quad.d);
            Integer NextA; Subtraction(NextA, Quad.a, IntegerPartMultipliedByD);
            
            QuadIrrationality NextQuad;
            
            NextQuad.a.Sign = NextA.Sign;
            NextQuad.a.Degree = NextA.Degree;
            NextQuad.a.Digits = NextA.Digits;
            
            NextQuad.b.Sign = Quad.b.Sign;
            NextQuad.b.Degree = Quad.b.Degree;
            NextQuad.b.Digits = (char*)malloc(sizeof(char)*(NextQuad.b.Degree + 1));
            for (int i = 0; i <= NextQuad.b.Degree; i++)
                NextQuad.b.Digits[i] = Quad.b.Digits[i];
            
            NextQuad.c.Degree = Quad.c.Degree;
            NextQuad.c.Digits = (char*)malloc(sizeof(char)*(NextQuad.c.Degree + 1));
            for (int i = 0; i <= NextQuad.c.Degree; i++)
                NextQuad.c.Digits[i] = Quad.c.Digits[i];
            
            NextQuad.d.Degree = Quad.d.Degree;
            NextQuad.d.Digits = (char*)malloc(sizeof(char)*(NextQuad.d.Degree + 1));
            for (int i = 0; i <= NextQuad.d.Degree; i++)
                NextQuad.d.Digits[i] = Quad.d.Digits[i];
            
            Integer ConjugatedDeno; MultiplyByConjugate(ConjugatedDeno, NextQuad);
            
            QuadIrrationality CompleteQuad;
            
            Multiply(CompleteQuad.a, NextQuad.a, Quad.d); CompleteQuad.a.Sign = !CompleteQuad.a.Sign;
            Multiply(CompleteQuad.b, NextQuad.b, Quad.d);
            FreeQuad(NextQuad);
            
            CompleteQuad.c.Degree = Quad.c.Degree;
            CompleteQuad.c.Digits = (char*)malloc(sizeof(char)*(CompleteQuad.c.Degree + 1));
            for (int i = 0; i <= CompleteQuad.c.Degree; i++)
                CompleteQuad.c.Digits[i] = Quad.c.Digits[i];
            
            CompleteQuad.d.Degree = ConjugatedDeno.Degree;
            CompleteQuad.d.Digits = ConjugatedDeno.Digits;
            
            Natural Zero; SetZero(Zero);
            if (Comparison(CompleteQuad.d, Zero) == COMPARISON_EQUAL_BIGGER)
                cout << "Ошибка. Введённая квадратичная иррациональность не является квадартичной иррациональностью." << endl;
            if (Zero.Digits != nullptr)
                free(Zero.Digits);
            
            ReduceQuadIrrationality(CompleteQuad);
            
            if (i != 0)
            {
                PeriodArrayCount++;
                PeriodArray = (QuadIrrationality*)realloc(PeriodArray, sizeof(QuadIrrationality)*(PeriodArrayCount));
                QuadIrrationalityEquasion(PeriodArray[PeriodArrayCount - 1], Quad);
                
                for (int j = 0; j < PeriodArrayCount-1 && !PeriodFound; j++)
                {
                    for (int k = j + 1; k < PeriodArrayCount && !PeriodFound; k++)
                    {
                        PeriodFound = (ComparisonEqual(PeriodArray[j], PeriodArray[k]) == COMPARISON_EQUAL_BIGGER);
                        if (PeriodFound)
                            PeriodStartPos = j;
                    }
                }
            }
            
            if (PeriodFound)
            {
                Result.PeriodStartPos = PeriodStartPos;
                FreeQuad(CompleteQuad);
            }
            else
            {
                Result.Degree++;
                Result.Elements = (Integer*)realloc(Result.Elements, (sizeof(Integer)*(Result.Degree + 1)));
                Result.Elements[Result.Degree].Sign = IntegerPart.Sign;
                Result.Elements[Result.Degree].Degree = IntegerPart.Degree;
                Result.Elements[Result.Degree].Digits = IntegerPart.Digits;
                
                QuadIrrationalityEquasion(Quad, CompleteQuad);
            }
            
            if (IntegerPartMultipliedByD.Digits != nullptr)
                free(IntegerPartMultipliedByD.Digits);
        }
        for (int i = 0; i < PeriodArrayCount; i++)
            FreeQuad(PeriodArray[i]);
        if (PeriodArray != nullptr)
            free(PeriodArray);
        
        if (!PeriodFound)
            cout << "Период данной иррациональности превышает 10000 элементов." << endl;
    }
    else
        cout << "Ошибка. Данная квадратичная иррациональность некорректна." << endl;
}

//----------------------------------------------------------
//void ExpandAsContinuedFractionN(ContinuedFraction&, QuadIrrationality, int)
//Преобразование квадратичной иррациональности в периодическую дробь из N элементов.
//----------------------------------------------------------
void ExpandAsContinuedFractionN(ContinuedFraction& Result, QuadIrrationality Quad, int N)
{
    if (IsQuadCorrect(Quad))
    {
        Result.isNotCompleted = true;
        for (int i = 0; i < N; i++)
        {
            Integer IntegerPart; GetIntegerPartFromQuadIrrationality(IntegerPart, Quad);
            Integer IntegerPartMultipliedByD; Multiply(IntegerPartMultipliedByD, IntegerPart, Quad.d);
            Integer NextA; Subtraction(NextA, Quad.a, IntegerPartMultipliedByD);
            
            QuadIrrationality NextQuad;
            
            NextQuad.a.Sign = NextA.Sign;
            NextQuad.a.Degree = NextA.Degree;
            NextQuad.a.Digits = NextA.Digits;
            
            NextQuad.b.Sign = Quad.b.Sign;
            NextQuad.b.Degree = Quad.b.Degree;
            NextQuad.b.Digits = (char*)malloc(sizeof(char)*(NextQuad.b.Degree + 1));
            for (int i = 0; i <= NextQuad.b.Degree; i++)
                NextQuad.b.Digits[i] = Quad.b.Digits[i];
            
            NextQuad.c.Degree = Quad.c.Degree;
            NextQuad.c.Digits = (char*)malloc(sizeof(char)*(NextQuad.c.Degree + 1));
            for (int i = 0; i <= NextQuad.c.Degree; i++)
                NextQuad.c.Digits[i] = Quad.c.Digits[i];
            
            Integer ConjugatedDeno; MultiplyByConjugate(ConjugatedDeno, NextQuad);
            
            QuadIrrationality CompleteQuad;
            
            Multiply(CompleteQuad.a, NextQuad.a, Quad.d); CompleteQuad.a.Sign = !CompleteQuad.a.Sign;
            Multiply(CompleteQuad.b, NextQuad.b, Quad.d);
            FreeQuad(NextQuad);
            
            CompleteQuad.c.Degree = Quad.c.Degree;
            CompleteQuad.c.Digits = (char*)malloc(sizeof(char)*(CompleteQuad.c.Degree + 1));
            for (int i = 0; i <= CompleteQuad.c.Degree; i++)
                CompleteQuad.c.Digits[i] = Quad.c.Digits[i];
            
            CompleteQuad.d.Degree = ConjugatedDeno.Degree;
            CompleteQuad.d.Digits = ConjugatedDeno.Digits;
            
            ReduceQuadIrrationality(CompleteQuad);
            
            if (i != 0)
                FreeQuad(Quad);
            
            Result.Degree++;
            Result.Elements = (Integer*)realloc(Result.Elements, (sizeof(Integer)*(Result.Degree + 1)));
            Result.Elements[Result.Degree].Sign = IntegerPart.Sign;
            Result.Elements[Result.Degree].Degree = IntegerPart.Degree;
            Result.Elements[Result.Degree].Digits = IntegerPart.Digits;
            
            QuadIrrationalityEquasion(Quad, CompleteQuad);
            
            if (IntegerPartMultipliedByD.Digits != nullptr)
                free(IntegerPartMultipliedByD.Digits);
        }
    }
    else
        cout << "Ошибка. Данная квадратичная иррациональность некорректна." << endl;
}
