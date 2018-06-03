//
//  main.cpp
//  Eltech_DM2018_Exam2Sem
//
//  Created by Никита Исаенко on 24.05.2018.
//  Copyright © 2018 Melanholy Hill. All rights reserved.
//

#include <iostream>

/*Для кроссплатформенности между консолью (cmd.exe) Windows и терминалом (Terminal.app) UNIX*/
void systempause();
void systemclear();
#ifdef _WIN32
    void systemclear()
    {
        system("cls");
    }
    void systempause()
    {
        system("pause");
    }
#else
    void systempause()
    {
        std::cout << '\n' << "-----Нажмите Enter, чтобы продолжить-----";
        do {
            /* nothing */
        } while (getchar() != '\n');
    }
    void systemclear()
    {
        system("clear");
    }
#endif

/*Для упрощения вызова следующих функций*/
using std::endl;
using std::cout;
using std::cin;

/*Объявляем константы*/
#define COMPARISON_FIRST_BIGGER 0
#define COMPARISON_SECOND_BIGGER 1
#define COMPARISON_EQUAL_BIGGER 2
#define COMPARISON_UNUSED_EQUAL 3

/*Объявляем структуры*/
struct Natural;
struct Integer;
struct Fraction;
struct ContinuedFraction;
struct QuadIrrationality;

/*Объявляем функции инициализации некоторых часто используемых чисел*/
void SetZero(Natural&);
void SetOne(Natural&);

/*Объявляем функции работы с натуральными числами*/
int Comparison(const Natural&, const Natural&);
void OptimazeNatural(Natural&);
void ConvertToNatural(Natural&, int);
void Summary(Natural&, Natural, Natural);
void Subtraction(Natural&, Natural, Natural);
void Multiply(Natural&, Natural, Natural);
void Divide(Natural&, Natural, Natural);
void DivideNoStrict(Natural&, Natural, Natural);
void Modulo(Natural&, Natural, Natural);
void ModuloNoStrict(Natural&, Natural, Natural);
void PowerOfTen(Natural&, Natural, int);
void GreatestCommonDivisor(Natural&, Natural, Natural);
void LeastCommonMultiple(Natural&, Natural, Natural);

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
void Divide(Integer&, Integer, Natural);
void DivideNoStrict(Integer&, Integer, Natural);
void ConvertEqualToNatural(Natural&, Integer);

/*Объявляем функции работы с рациональными дробями*/
void SetZero(Fraction&);
void ReduceFraction(Fraction&);
void Summary(Fraction&, Fraction, Fraction);
void Summary(Fraction&, Fraction, Integer);
void FreeFraction(Fraction&);

/*Объявляем функции работы с цепными дробями*/
int Comparison(const ContinuedFraction&, const ContinuedFraction&);
void WriteConvergenceFractionsTo(Fraction*&, ContinuedFraction, int);
void FreeContinuedFraction(ContinuedFraction&);

/*Объявляем функции работы целых с квадратичными иррациональностями*/
int Comparison(const QuadIrrationality&, const QuadIrrationality&);
bool IsQuadCorrect(const QuadIrrationality&);
void IsQuadIrrationalityValid(Fraction&, QuadIrrationality);
void Summary(QuadIrrationality&, QuadIrrationality, QuadIrrationality);
void Subtraction(QuadIrrationality&, QuadIrrationality, QuadIrrationality);
void FreeQuad(QuadIrrationality&);
void FreeQuad(QuadIrrationality*);
void EstimateRootLowerThat(Natural&, Natural);
void MultiplyByConjugate(Integer&, QuadIrrationality);
void ReduceQuadIrrationality(QuadIrrationality& Quad);
void QuadIrrationalityEquasion(QuadIrrationality&, QuadIrrationality&);
void GetIntegerPartFromQuadIrrationality(Integer&, QuadIrrationality);
void ExpandAsContinuedFraction(ContinuedFraction&, QuadIrrationality);
void ExpandAsContinuedFractionN(ContinuedFraction&, QuadIrrationality, int);

/*Объявляем функции меню*/
int InputDecision();
void Menu();
void SubMenu_QuadraticIrrationalities();
void Menu_QuadraticIrrationalities();
void PrintHelp();

/*Объявляем вспомогательные функции*/
char* InputString();
int GetLength(const char*);

struct Natural
{
    int Degree{ -1 };
    int *Digits{ nullptr };
    
    friend std::ostream& operator<<(std::ostream& os, const Natural& Nat)
    {
        for (int i = Nat.Degree; i >= 0; i--)
            os << Nat.Digits[i];
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Natural& Nat)
    {
        char *n = InputString();
        for (int i = GetLength(n) - 1; i >= 0; i--)
        {
            if (n[i] >= 48 && n[i] <= 57)
            {
                Nat.Degree++;
                Nat.Digits = (int*)realloc(Nat.Digits, sizeof(int)*(Nat.Degree+1));
                Nat.Digits[Nat.Degree] = n[i] - 48;
            }
        }
        
        return is;
    }
};

struct Integer
{
    bool Sign{ false };
    int Degree{ -1 };
    int *Digits{ nullptr };
    
    friend std::ostream& operator<<(std::ostream& os, const Integer& Int)
    {
        if (Int.Degree != -1 && Int.Sign)
            cout << "-";
        for (int i = Int.Degree; i >= 0; i--)
            os << Int.Digits[i];
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Integer& Int)
    {
        char *n = InputString();
        for (int i = GetLength(n) - 1; i >= 0; i--)
        {
            if (n[i] == 45)
                Int.Sign = true;
            else if (n[i] >= 48 && n[i] <= 57)
            {
                Int.Degree++;
                Int.Digits = (int*)realloc(Int.Digits, sizeof(int)*(Int.Degree+1));
                Int.Digits[Int.Degree] = n[i] - 48;
            }
        }
        
        return is;
    }
};

struct Fraction
{
    Integer Num;
    Natural Deno;
    
    friend std::ostream& operator<<(std::ostream& os, const Fraction& Frac)
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
    
    friend std::istream& operator>>(std::istream& is, Fraction& Frac)
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
                            Int.Digits = (int*)realloc(Int.Digits, sizeof(int)*(Int.Degree + 1));
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
            Frac.Num.Digits = (int*)malloc(sizeof(int));
            Frac.Num.Digits[0] = 1;
        }
        if (Frac.Num.Degree != -1 && Frac.Deno.Degree == -1)
        {
            Frac.Deno.Degree = 0;
            Frac.Deno.Digits = (int*)malloc(sizeof(int));
            Frac.Deno.Digits[0] = 1;
        }
        
        return is;
    }
};

struct ContinuedFraction
{
    int Degree{ -1 };
    Integer *Elements{ nullptr };
    int PeriodStartPos{ -1 };
    bool isNotCompleted{ false };
    
    friend std::ostream& operator<<(std::ostream& os, const ContinuedFraction& CFrac)
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
    
    friend std::istream& operator>>(std::istream& is, ContinuedFraction& CFrac)
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
                            Int.Digits = (int*)realloc(Int.Digits, sizeof(int)*(Int.Degree + 1));
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
                            Int.Digits = (int*)realloc(Int.Digits, sizeof(int)*(Int.Degree+1));
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
};

struct QuadIrrationality
{
    Integer a;
    Integer b;
    Natural c;
    Natural d;
    
    friend std::ostream& operator<<(std::ostream& os, const QuadIrrationality& Quad)
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
    
    friend std::istream& operator>>(std::istream& is, QuadIrrationality& Quad)
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
                                Int.Digits = (int*)realloc(Int.Digits, sizeof(int)*(Int.Degree + 1));
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
                                Int.Digits = (int*)realloc(Int.Digits, sizeof(int)*(Int.Degree + 1));
                                Int.Digits[Int.Degree] = str[j] - 48;
                            }
                        }
                        for (int j = i-1; j > vPos; j--)
                        {
                            if (str[j] >= 48 && str[j] <= 57)
                            {
                                Nat.Degree++;
                                Nat.Digits = (int*)realloc(Nat.Digits, sizeof(int)*(Nat.Degree + 1));
                                Nat.Digits[Nat.Degree] = str[j] - 48;
                            }
                        }
                        
                        if (Nat.Degree != -1 && Int.Degree == -1)
                        {
                            Int.Degree = 0;
                            Int.Digits = (int*)malloc(sizeof(int));
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
                Quad.a.Digits = (int*)malloc(sizeof(int));
                Quad.a.Digits[0] = 0;
            }
            
            if (Quad.d.Degree == -1)
            {
                Quad.d.Degree = 0;
                Quad.d.Digits = (int*)malloc(sizeof(int));
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
};

//----------------------------------------------------------
//void IsQuadIrrationalityValid(Integer&, QuadIrrationality)
//Инициализация нуля.
//----------------------------------------------------------
void IsQuadIrrationalityValid(Fraction &Result, QuadIrrationality Quad)
{
    Integer BSquared; Multiply(BSquared, Quad.b, Quad.b);
    Natural BSquaredNat; BSquaredNat.Degree = BSquared.Degree; BSquaredNat.Digits = BSquared.Digits;
    Natural PreciseRoot; Multiply(PreciseRoot, Quad.c, BSquaredNat);
    Natural RootEstimation; EstimateRootLowerThat(RootEstimation, PreciseRoot);
    Natural RootEstimationSquared; Multiply(RootEstimationSquared, RootEstimation, RootEstimation);
    
    if (Comparison(RootEstimationSquared, PreciseRoot) == COMPARISON_EQUAL_BIGGER)
    {
        Integer FromCPart; FromCPart.Sign = Quad.b.Sign; FromCPart.Degree = RootEstimation.Degree; FromCPart.Digits = RootEstimation.Digits;
        
        Integer NumeIntegerPart; Summary(NumeIntegerPart, Quad.a, FromCPart);
        
        Result.Num.Sign = NumeIntegerPart.Sign;
        Result.Num.Degree = NumeIntegerPart.Degree;
        Result.Num.Digits = NumeIntegerPart.Digits;
        
        Result.Deno.Degree = Quad.d.Degree;
        Result.Deno.Digits = (int*)malloc(sizeof(int)*(Result.Deno.Degree + 1));
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
//void SetZero(Natural&)
//Инициализация нуля.
//----------------------------------------------------------
void SetZero(Natural& Nat)
{
    if (Nat.Digits != nullptr)
        free(Nat.Digits);
    Nat.Degree = 0;
    Nat.Digits = (int*)malloc(sizeof(int));
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
    Nat.Digits = (int*)malloc(sizeof(int));
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
        Nat.Digits = (int*)realloc(Nat.Digits, sizeof(int)*(Nat.Degree+1));
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
                int *Digits = (int*)malloc(sizeof(int)*(Nat.Degree+1));
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
        Sum.Digits = (int*)realloc(Sum.Digits, sizeof(int)*(Sum.Degree + 1));
        
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
        Sum.Digits = (int*)realloc(Sum.Digits, sizeof(int)*(Sum.Degree + 1));
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
                Sub.Digits = (int*)realloc(Sub.Digits, sizeof(int)*(Sub.Degree + 1));
                
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
                Sub.Digits = (int*)realloc(Sub.Digits, sizeof(int)*(Sub.Degree + 1));
                
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
//void Divide(Natural&, Natural, Natural)
//Деление нацело натуральных чисел.
//----------------------------------------------------------
void Divide(Natural &QuoResult, Natural that, Natural other)
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
            second.Digits = (int*)malloc(sizeof(int)*(second.Degree+1));
            for (int i = 0; i <= second.Degree; i++)
                second.Digits[i] = (that).Digits[i];
            
            Rem.Degree = (other).Degree;
            Rem.Digits = (int*)malloc(sizeof(int)*(Rem.Degree+1));
            for (int i = 0; i <= Rem.Degree; i++)
                Rem.Digits[i] = (other).Digits[i];
        }
        else
        {
            second.Degree = (other).Degree;
            second.Digits = (int*)malloc(sizeof(int)*(second.Degree+1));
            for (int i = 0; i <= second.Degree; i++)
                second.Digits[i] = (other).Digits[i];
            
            Rem.Degree = (that).Degree;
            Rem.Digits = (int*)malloc(sizeof(int)*(Rem.Degree+1));
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
//void Modulo(Natural&, Natural, Natural)
//Деление нацело натуральных чисел.
//----------------------------------------------------------
void Modulo(Natural &RemResult, Natural that, Natural other)
{
    if (Comparison(that, other) == COMPARISON_SECOND_BIGGER)
    {
        RemResult.Degree = that.Degree;
        RemResult.Digits = (int*)malloc(sizeof(int)*(RemResult.Degree + 1));
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
            second.Digits = (int*)malloc(sizeof(int)*(second.Degree+1));
            for (int i = 0; i <= second.Degree; i++)
                second.Digits[i] = (that).Digits[i];
            
            Rem.Degree = (other).Degree;
            Rem.Digits = (int*)malloc(sizeof(int)*(Rem.Degree+1));
            for (int i = 0; i <= Rem.Degree; i++)
                Rem.Digits[i] = (other).Digits[i];
        }
        else
        {
            second.Degree = (other).Degree;
            second.Digits = (int*)malloc(sizeof(int)*(second.Degree+1));
            for (int i = 0; i <= second.Degree; i++)
                second.Digits[i] = (other).Digits[i];
            
            Rem.Degree = (that).Degree;
            Rem.Digits = (int*)malloc(sizeof(int)*(Rem.Degree+1));
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
        Result.Digits = (int*)malloc(sizeof(int)*(Result.Degree + 1));
        for (int i = 0; i <= Result.Degree; i++)
            Result.Digits[i] = Nat.Digits[i];
    }
    else
    {
        Result.Degree = Nat.Degree + Power;
        Result.Digits = (int*)malloc(sizeof(int)*(Result.Degree + 1));
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
void GreatestCommonDivisor(Natural& GCD, Natural Nat1, Natural Nat2)
{
    Natural Zero; SetZero(Zero);
    if (Comparison(Zero, Nat1) == COMPARISON_EQUAL_BIGGER)
    {
        GCD.Degree = Nat2.Degree;
        if (GCD.Digits != nullptr)
            free(GCD.Digits);
        GCD.Digits = (int*)malloc(sizeof(int)*(GCD.Degree+1));
        for (int i = 0; i <= GCD.Degree; i++)
            GCD.Digits[i] = Nat2.Digits[i];
    }
    else if (Comparison(Zero, Nat2) == COMPARISON_EQUAL_BIGGER)
    {
        GCD.Degree = Nat1.Degree;
        if (GCD.Digits != nullptr)
            free(GCD.Digits);
        GCD.Digits = (int*)malloc(sizeof(int)*(GCD.Degree+1));
        for (int i = 0; i <= GCD.Degree; i++)
            GCD.Digits[i] = Nat1.Digits[i];
    }
    else
    {
        Natural A;
        A.Degree = Nat1.Degree;
        A.Digits = (int*)malloc(sizeof(int)*(A.Degree+1));
        for (int i = 0; i <= A.Degree; i++)
            A.Digits[i] = Nat1.Digits[i];
        
        Natural B;
        B.Degree = Nat2.Degree;
        B.Digits = (int*)malloc(sizeof(int)*(B.Degree+1));
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
                A.Digits = (int*)malloc(sizeof(int)*(A.Degree+1));
                for (int i = 0; i <= A.Degree; i++)
                    A.Digits[i] = Sub.Digits[i];
            }
            else
            {
                if (B.Digits != nullptr)
                    free(B.Digits);
                B.Degree = Sub.Degree;
                B.Digits = (int*)malloc(sizeof(int)*(B.Degree+1));
                for (int i = 0; i <= B.Degree; i++)
                    B.Digits[i] = Sub.Digits[i];
            }
        }
        
        GCD.Degree = A.Degree;
        if (GCD.Digits != nullptr)
            free(GCD.Digits);
        GCD.Digits = (int*)malloc(sizeof(int)*(GCD.Degree+1));
        for (int i = 0; i <= GCD.Degree; i++)
            GCD.Digits[i] = A.Digits[i];
        
        if (B.Digits != nullptr)
            free(B.Digits);
    }
    
    if (Zero.Digits != nullptr)
        free(Zero.Digits);
}

//----------------------------------------------------------
//void LeastCommonMultiple(Natural&, Natural, Natural)
//НОК натуральных чисел.
//----------------------------------------------------------
void LeastCommonMultiple(Natural& LCM, Natural Nat1, Natural Nat2)
{
    Natural Mul; Multiply(Mul, Nat1, Nat2);
    Natural GCD; GreatestCommonDivisor(GCD, Nat1, Nat2);
    Divide(LCM, Mul, GCD);
    
    if (Mul.Digits != nullptr)
        free(Mul.Digits);
    if (GCD.Digits != nullptr)
        free(GCD.Digits);
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
                int *Digits = (int*)malloc(sizeof(int)*(Nat.Degree+1));
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
    Frac.Num.Digits = (int*)malloc(sizeof(int));
    Frac.Num.Digits[0] = 0;
    
    Frac.Deno.Degree = 0;
    Frac.Deno.Digits = (int*)malloc(sizeof(int));
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
        Result.Deno.Digits = (int*)malloc(sizeof(int)*(Result.Deno.Degree + 1));
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
                Frac.Num.Digits = (int*)malloc(sizeof(int)*(Frac.Num.Degree + 1));
                for (int j = 0; j <= Frac.Num.Degree; j++)
                    Frac.Num.Digits[j] = CFrac.Elements[num].Digits[j];
                
                Frac.Deno.Degree = 0;
                Frac.Deno.Digits = (int*)malloc(sizeof(int));
                Frac.Deno.Digits[0] = 1;
            }
            else if (i == 1)
            {
                //p1 = a0*a1, q0 = a1
                Natural One; SetOne(One);
                Integer MulNum; Multiply(MulNum, CFrac.Elements[num], CFrac.Elements[num - 1]);
                Summary(Frac.Num, MulNum, One);
                
                Frac.Deno.Degree = CFrac.Elements[num].Degree;
                Frac.Deno.Digits = (int*)malloc(sizeof(int)*(Frac.Deno.Degree + 1));
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
            Result.c.Digits = (int*)malloc(sizeof(Result.c.Degree + 1));
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
        Natural RootEstimation; EstimateRootLowerThat(RootEstimation, PreciseRoot);
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
            NextQuad.b.Digits = (int*)malloc(sizeof(int)*(NextQuad.b.Degree + 1));
            for (int i = 0; i <= NextQuad.b.Degree; i++)
                NextQuad.b.Digits[i] = Quad.b.Digits[i];
            
            NextQuad.c.Degree = Quad.c.Degree;
            NextQuad.c.Digits = (int*)malloc(sizeof(int)*(NextQuad.c.Degree + 1));
            for (int i = 0; i <= NextQuad.c.Degree; i++)
                NextQuad.c.Digits[i] = Quad.c.Digits[i];
            
            NextQuad.d.Degree = Quad.d.Degree;
            NextQuad.d.Digits = (int*)malloc(sizeof(int)*(NextQuad.d.Degree + 1));
            for (int i = 0; i <= NextQuad.d.Degree; i++)
                NextQuad.d.Digits[i] = Quad.d.Digits[i];
            
            Integer ConjugatedDeno; MultiplyByConjugate(ConjugatedDeno, NextQuad);
            
            QuadIrrationality CompleteQuad;
            
            Multiply(CompleteQuad.a, NextQuad.a, Quad.d); CompleteQuad.a.Sign = !CompleteQuad.a.Sign;
            Multiply(CompleteQuad.b, NextQuad.b, Quad.d);
            FreeQuad(NextQuad);
            
            CompleteQuad.c.Degree = Quad.c.Degree;
            CompleteQuad.c.Digits = (int*)malloc(sizeof(int)*(CompleteQuad.c.Degree + 1));
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
            NextQuad.b.Digits = (int*)malloc(sizeof(int)*(NextQuad.b.Degree + 1));
            for (int i = 0; i <= NextQuad.b.Degree; i++)
                NextQuad.b.Digits[i] = Quad.b.Digits[i];
            
            NextQuad.c.Degree = Quad.c.Degree;
            NextQuad.c.Digits = (int*)malloc(sizeof(int)*(NextQuad.c.Degree + 1));
            for (int i = 0; i <= NextQuad.c.Degree; i++)
                NextQuad.c.Digits[i] = Quad.c.Digits[i];
            
            Integer ConjugatedDeno; MultiplyByConjugate(ConjugatedDeno, NextQuad);
            
            QuadIrrationality CompleteQuad;
            
            Multiply(CompleteQuad.a, NextQuad.a, Quad.d); CompleteQuad.a.Sign = !CompleteQuad.a.Sign;
            Multiply(CompleteQuad.b, NextQuad.b, Quad.d);
            FreeQuad(NextQuad);
            
            CompleteQuad.c.Degree = Quad.c.Degree;
            CompleteQuad.c.Digits = (int*)malloc(sizeof(int)*(CompleteQuad.c.Degree + 1));
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

//----------------------------------------------------------
//int InputDecision()
//Возвращает введённый пользователем пункт меню.
//----------------------------------------------------------
int InputDecision()
{
    int MenuDecision;
    
    cout << "Пожалуйста, выберите один из пунктов меню:" << endl;
    cin >> MenuDecision; cout << endl;
    fflush(stdin);  cin.clear();
    
    return MenuDecision;
}

//----------------------------------------------------------
//char* InputString()
//Возвращает введённую пользователем строку с признаком завершения строки, память для хранения которой выделяется динамически.
//----------------------------------------------------------
char *InputString()
{
    char *str{ nullptr }; //Переменная для хранения введённой строки
    char wc;       //Временная переменная для хранения введённого пользователем символа.
    int strLen{ 0 };  //Временная переменная для хранения длины строки, учитываем сразу
    
    bool MemError{ false }; //Флаг ошибки выделения памяти
    
    while ((wc = getchar()) != '\n' && !MemError)
    {
        if (wc == 8)
        {
            if (strLen > 0)
            {
                strLen--;
                char *temp = (char*)realloc(str, (strLen + 1) * sizeof(char));
                if (temp != nullptr)
                {
                    str = temp;
                }
                else
                {
                    free(str); str = nullptr;
                    MemError = true;
                    cout << "Ошибка выделения памяти для хранения введённой строки." << endl;
                }
            }
        }
        else
        {
            /*Пока производится ввод пользователем, добавляем введённый символ к строке*/
            /*Добавляем на одну ячейку памяти больше, чтобы потом учесть признак завершения строки*/
            char *temp = (char*)realloc(str, (strLen + 2) * sizeof(char));
            if (temp != nullptr)
            {
                str = temp;
                str[strLen] = wc;
                strLen++;
            }
            else
            {
                free(str); str = nullptr;
                MemError = true;
                cout << "Ошибка выделения памяти для хранения введённой строки." << endl;
            }
        }
    }
    
    if (!MemError)
    {
        if (strLen == 0)
        {
            /*Если не произошло ошибки выделения памяти, но не было введено ни одного символа...*/
            str = (char*)malloc(sizeof(char));
        }
        /*Учитываем в конце признак завершения строки*/
        str[strLen] = '\0';
    }
    
    fflush(stdin); cin.clear();
    return str;
}

//----------------------------------------------------------
//int GetLength(char*)
//Возвращает длину строки, имеющую признак завершения строки, без учёта этого самого признака завершения строки.
//----------------------------------------------------------
int GetLength(const char *str)
{
    int i{ 0 };
    if (str != nullptr)
    {
        while (*(str + i) != '\0')
        {
            i++;
        }
    }
    return i;
}

//----------------------------------------------------------
//void Menu()
//Выводит на экран меню.
//----------------------------------------------------------
void Menu()
{
    systemclear();
    
    cout << "Альтернативный экзамен \"КВАДРАТИЧНЫЕ ИРРАЦИОНАЛЬНОСТИ\"." << endl;
    cout << "Version 1.0.0 (29.05.2018)." << endl;
    cout << "Автор: Исаенко Никита, 7305." << endl << endl;
    
    cout << "Данная программа реализует работу компьютерной алгебры с модулями на тему  \"Квадратичные иррациональности\"." << endl << endl;
    
    cout << "---------------------МЕНЮ:---------------------" << endl;
    cout << "1 - Квадратичные иррациональности" << endl;
    cout << "2 - Справка по программе" << endl;
    cout << "3 - Завершение программы" << endl;
    cout << "-----------------------------------------------" << endl;
    
}

//----------------------------------------------------------
//void SubMenu_QuadraticIrrationalities()
//Реализация подменю главного меню программы.
//----------------------------------------------------------
void SubMenu_QuadraticIrrationalities()
{
    int SubMenuDecision{ 0 };
    int N{ 0 };
    char OrderSign{ '?' };
    
    QuadIrrationality Quad1;
    QuadIrrationality Quad2;
    QuadIrrationality Result;
    
    ContinuedFraction CFrac;
    Integer IntegerPart;
    
    Fraction *FracArray{ nullptr };
    
    do
    {
        Menu_QuadraticIrrationalities();
        SubMenuDecision = InputDecision();
        
        fflush(stdin); cin.clear(); cin.ignore();
        switch (SubMenuDecision)
        {
            case 1:
                cout << "Первая квадратичная иррациональность: ";
                cin >> Quad1;
                
                cout << "Вторая квадратичная иррациональность: ";
                cin >> Quad2;
                
                cout << endl << "Результат: ";
                N = Comparison(Quad1, Quad2);
                if (N == COMPARISON_UNUSED_EQUAL)
                    OrderSign = '?';
                else if (N == COMPARISON_EQUAL_BIGGER)
                    OrderSign = '=';
                else if (N == COMPARISON_FIRST_BIGGER)
                    OrderSign = '>';
                else if (N == COMPARISON_SECOND_BIGGER)
                    OrderSign = '<';
                
                cout << Quad1 << " " << OrderSign << " " << Quad2 << endl;
                
                FreeQuad(Quad1);
                FreeQuad(Quad2);
                systempause();
                break;
            case 2:
                cout << "Первая квадратичная иррациональность: ";
                cin >> Quad1;
                
                cout << "Вторая квадратичная иррациональность: ";
                cin >> Quad2;
                
                cout << Quad1 << endl;
                cout << "   +" << endl;
                cout << Quad2 << endl;
                cout << "   =" << endl;
                
                Summary(Result, Quad1, Quad2);
                cout << Result << endl;
                
                FreeQuad(Quad1);
                FreeQuad(Quad2);
                FreeQuad(Result);
                systempause();
                break;
            
            case 3:
                cout << "Первая квадратичная иррациональность: ";
                cin >> Quad1;
                
                cout << "Вторая квадратичная иррациональность: ";
                cin >> Quad2;
                
                cout << Quad1 << endl;
                cout << "   +" << endl;
                cout << Quad2 << endl;
                cout << "   =" << endl;
                
                Subtraction(Result, Quad1, Quad2);
                cout << Result << endl;
                
                FreeQuad(Quad1);
                FreeQuad(Quad2);
                FreeQuad(Result);
                systempause();
                break;
            
            case 4:
                cout << "Введите квадратичную иррациональность: ";
                cin >> Quad1; //Сокращение встроено в ввод
                cout << "Сокращённая квадратичная иррациональность: " << Quad1 << endl;
                
                FreeQuad(Quad1);
                systempause();
                break;
                
            case 5:
                cout << "Введите квадратичную иррациональность: ";
                cin >> Quad1;
                
                GetIntegerPartFromQuadIrrationality(IntegerPart, Quad1);
                cout << "Целая часть: " << IntegerPart << endl;
                
                FreeInteger(IntegerPart);
                FreeQuad(Quad1);
                systempause();
                break;
            
            case 6:
                cout << "Введите квадратичную иррациональность: ";
                cin >> Quad1;
                
                cout << "Цепная дробь: ";
                ExpandAsContinuedFraction(CFrac, Quad1);
                cout << CFrac << endl;
                
                FreeContinuedFraction(CFrac);
                
                systempause();
                break;
            
            case 7:
                cout << "Введите квадратичную иррациональность: ";
                cin >> Quad1;
                
                do
                {
                    cout << "Введите N: ";
                    cin >> N;
                    if (N <= 0)
                        cout << "Ошибка ввода. N не может быть неположительным." << endl;
                    cin.clear(); cin.ignore();
                } while (N <= 0);
                
                cout << "Цепная дробь: ";
                ExpandAsContinuedFractionN(CFrac, Quad1, N);
                cout << CFrac << endl;
                
                FreeContinuedFraction(CFrac);
                
                systempause();
                break;
                
            case 8:
                cout << "Введите квадратичную иррациональность: ";
                cin >> Quad1;
                
                cout << "Цепная дробь: ";
                ExpandAsContinuedFraction(CFrac, Quad1);
                cout << CFrac << endl; FreeContinuedFraction(CFrac);
                cout << "Первые 50 неполных частных: ";
                ExpandAsContinuedFractionN(CFrac, Quad1, 50);
                cout << CFrac << endl;
                
                FreeContinuedFraction(CFrac);
                
                systempause();
                break;
            
            case 9:
                cout << "Введите квадратичную иррациональность: ";
                cin >> Quad1;
                
                cout << "Цепная периодическая дробь: ";
                ExpandAsContinuedFraction(CFrac, Quad1);
                cout << CFrac << endl;
                
                do
                {
                    cout << "Введите N: ";
                    cin >> N;
                    if (N <= 0)
                        cout << "Ошибка ввода. N не может быть неположительным." << endl;
                    cin.clear(); cin.ignore();
                } while (N <= 0);
                
                cout << "Наилучшие приближения (подходящие дроби): " << endl;
                WriteConvergenceFractionsTo(FracArray, CFrac, N);
                if (FracArray != nullptr)
                {
                    for (int i = 0; i < N; i++)
                        cout << i+1 << ") " << FracArray[i] << endl;
                }
                
                FreeQuad(Quad1);
                FreeContinuedFraction(CFrac);
                if (FracArray != nullptr)
                {
                    for (int i = 0; i < N; i++)
                        FreeFraction(FracArray[i]);
                    free(FracArray);
                }
                FracArray = nullptr;
                
                systempause();
                break;
                
            case 10:
                break;
            
            default:
                cout << "Ошибка. Введён некорректный пункт меню." << endl;
                systempause();
                break;
        }
        
    } while (SubMenuDecision != 10);
}

//----------------------------------------------------------
//void Menu_QuadraticIrrationalities()
//Выводит на экран меню.
//----------------------------------------------------------
void Menu_QuadraticIrrationalities()
{
    systemclear();
    
    cout << "--------------------ПОДМЕНЮ:--------------------" << endl;
    cout << "1 - Сравнение по порядку квадратичных иррациональностей" << endl;
    cout << "2 - Сложение квадратичных иррациональностей" << endl;
    cout << "3 - Разность квадратичных иррациональностей" << endl;
    cout << "4 - Сокращение квадратичной иррациональности" << endl;
    cout << "5 - Выделение целой части квадратичной иррациональности" << endl;
    cout << "6 - Разложение квадратичной иррациональности в периодическую цепную дробь" << endl;
    cout << "7 - Разложение квадратичной иррациональности в цепную дробь с N элементами" << endl;
    cout << "8 - Разложение квадратичной иррациональности в периодическую цепную дробь со сравнением из 50 элементов" << endl;
    cout << "9 - Найти N приближений квадратичной иррациональности" << endl;
    cout << "10 - Возврат в надменю" << endl;
    cout << "------------------------------------------------" << endl;
}

//----------------------------------------------------------
//void PrintHelp()
//Вывод на экран справки по программе.
//----------------------------------------------------------
void PrintHelp()
{
    cout << "Данная программа тыры-пыры..." << endl;
    cout << "Ввод квадратичных иррациональностей осуществляется следующим образом: " << endl;
    cout << "\"a +- bVc/d\", где a, b - целые числа, +- - любой знак, c, d - натуральные числа, V/v - значок корня. В записи могут отсутствовать a, b и d." << endl;
}

int main()
{
    setlocale (LC_ALL, "Russian");
    
    /*cout << "Введите первое натуральное число: ";
    Natural Nat1; cin >> Nat1;
    cout << "Введите второе натуральное число: ";
    Natural Nat2; cin >> Nat2;
    
    Natural Sum; Summary(Sum, Nat1, Nat2);
    cout << "Их сумма: " << Sum << endl;
    
    Natural Sub; Subtraction(Sub, Nat1, Nat2);
    cout << "Их разность: " << Sub << endl;
    
    Natural Mul; Multiply(Mul, Nat1, Nat2);
    cout << "Их произведение: " << Mul << endl;
    
    Natural Quo; Divide(Quo, Nat1, Nat2);
    cout << "Их частное: " << Quo << endl;
    
    Natural Mod; Modulo(Mod, Nat1, Nat2);
    cout << "Их остаток: " << Mod << endl;
    
    Natural GCD; GreatestCommonDivisor(GCD, Nat1, Nat2);
    cout << "Их НОД: " << GCD << endl;*/
    
    /*cout << "Введите первое целое число: ";
    Integer Int1; cin >> Int1;
    cout << "Введите второе целое число: ";
    Integer Int2; cin >> Int2;
    
    Integer Sum; Summary(Sum, Int1, Int2);
    cout << "Их сумма: " << Sum << endl;
    
    Integer Sub; Subtraction(Sub, Int1, Int2);
    cout << "Их разность: " << Sub << endl;
    
    Integer Mul; Multiply(Mul, Int1, Int2);
    cout << "Их произведение: " << Mul << endl;
    
    Integer Quo; Divide(Quo, Int1, Int2);
    cout << "Их частное: " << Quo << endl;
    
    Integer Mod; Modulo(Mod, Int1, Int2);
    cout << "Их остаток: " << Mod << endl;*/
    
    /*cout << "Первая квадратичная иррациональность: ";
    QuadIrrationality Quad1; cin >> Quad1;
    ReduceQuadIrrationality(Quad1); cout << Quad1 << endl;*/
    
    /*cout << "Вторая квадратичная иррациональность: ";
    QuadIrrationality Quad2; cin >> Quad2;
    
    cout << "Их сумма: ";
    QuadIrrationality Sum; Summary(Sum, Quad1, Quad2);
    cout << Sum << endl;
    
    cout << "Их разность: ";
    QuadIrrationality Sub; Subtraction(Sub, Quad1, Quad2);
    cout << Sub << endl;*/
    
    /*cout << "Первая цепная дробь: ";
    ContinuedFraction CFrac; ExpandAsContinuedFraction(CFrac, Quad1);
    cout << CFrac << endl;
    
    cout << "Первые 40 элементов: ";
    ContinuedFraction CFrac1; ExpandAsContinuedFractionN(CFrac1, Quad1, 40);
     cout << CFrac1 << endl;*/
    
    /*cout << "Введите дробь 1: ";
    Fraction Frac1; cin >> Frac1;
    cout << Frac1 << endl;
    
    cout << "Введите дробь 2: ";
    Fraction Frac2; cin >> Frac2;
    cout << Frac2 << endl;
    
    Fraction Sum; Summary(Sum, Frac1, Frac2);
    cout << "Сумма: " << Sum << endl;*/
    
    //systempause();
    
    int MenuDecision{ 0 };
    
    do
    {
        Menu();
        MenuDecision = InputDecision();
        
        fflush(stdin); cin.clear(); cin.ignore();
        switch (MenuDecision)
        {
            case 1:
                SubMenu_QuadraticIrrationalities();
                break;
            case 2:
                PrintHelp();
                systempause();
                break;
            case 3:
                cout << "Завершение программы..." << endl;
                break;
            default:
                cout << "Ошибка. Введён некорректный пункт меню." << endl;
                systempause();
                break;
        }
        
    } while (MenuDecision != 3);
}
