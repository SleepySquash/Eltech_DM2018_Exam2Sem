//
//  obsolete.h
//  Eltech_DM2018_Exam2Sem
//
//  Created by Никита Исаенко on 27.05.2018.
//  Copyright © 2018 Melanholy Hill. All rights reserved.
//

#ifndef obsolete_h
#define obsolete_h

//----------------------------------------------------------
//Integer InputInteger()
//Выводит на экран меню.
//----------------------------------------------------------
Natural InputNatural()
{
    Natural Nat;
    int n;
    
    cin >> n;
    
    SetZero(Nat);
    while (n != 0)
    {
        int dig = n % 10;
        Nat.Digits = (int*)realloc(Nat.Digits, sizeof(int)*(Nat.Degree+1));
        Nat.Digits[Nat.Degree+1] = dig;
        Nat.Degree++;
        n /= 10;
    }
    if (Nat.Degree == -1)
        Nat.Degree = 0;
    
    return Nat;
}

//----------------------------------------------------------
//Integer InputInteger()
//Выводит на экран меню.
//----------------------------------------------------------
Integer InputInteger()
{
    Integer Int;
    int n;
    
    cin >> n;
    
    if (n < 0)
    {
        Int.Sign = true;
        n = -n;
    }
    
    Int.Digits = (int*)malloc(sizeof(int));
    Int.Digits[0] = 0;
    while (n != 0)
    {
        int dig = n % 10;
        Int.Digits = (int*)realloc(Int.Digits, sizeof(int)*(Int.Degree+1));
        Int.Digits[Int.Degree+1] = dig;
        Int.Degree++;
        n /= 10;
    }
    if (Int.Degree == -1)
        Int.Degree = 0;
    
    return Int;
}

Natural operator/(const Natural& other)
{
    Natural Quo;
    Natural Rem;
    
    int ComparisonResult = Comparison(*this, other);
    if (ComparisonResult == COMPARISON_EQUAL_BIGGER)
        SetZero(Rem);
    else
    {
        int QuoDeg = -1;
        int *QuoArr = nullptr;
        Natural second;
        
        if (ComparisonResult == COMPARISON_SECOND_BIGGER)
        {
            second = *this;
            Rem = other;
        }
        else
        {
            Rem = *this;
            second = other;
        }
        
        Natural Zero = ConvertToNatural(0);
        if (Comparison(Zero, second) == COMPARISON_EQUAL_BIGGER)
            cout << "Ошибка. Деление на 0." << endl;
        else
        {
            Natural One; SetOne(One);
            
            bool isFirst = true;
            int OffsetToPos = 0;
            while (Comparison(Rem, second) != COMPARISON_SECOND_BIGGER)
            {
                cout << "Comparsion: Rem " << Rem << " and second " << second << endl;
                
                Natural Temp;
                if (isFirst)
                    Temp.Degree = second.Degree;
                else
                    Temp.Degree = second.Degree + 1;
                Temp.Digits = (int*)malloc(sizeof(int)*(Temp.Degree+1));
                for (int i = Rem.Degree; i >= Rem.Degree - Temp.Degree; i--)
                {
                    if (i > Rem.Degree)
                        Temp.Digits[i - Rem.Degree + Temp.Degree] = 0;
                    else
                        Temp.Digits[i - Rem.Degree + Temp.Degree] = Rem.Digits[i];
                }
                //OffsetToPos = 0;
                
                cout << Temp << endl;
                OptimazeNatural(Temp);
                
                isFirst = false;
                
                int Count = 0;
                while (Comparison(Temp, second) == COMPARISON_SECOND_BIGGER)
                {
                    free(Temp.Digits);
                    Temp.Degree = Temp.Degree + 1;
                    Temp.Digits = (int*)malloc(sizeof(int)*(Temp.Degree+1));
                    for (int i = Rem.Degree; i >= Rem.Degree - Temp.Degree; i--)
                        Temp.Digits[i - Rem.Degree + Temp.Degree] = Rem.Digits[i];
                    cout << "second was bigger, so "<< Temp << endl;
                    
                    QuoDeg++;
                    QuoArr = (int*)realloc(QuoArr, sizeof(int)*(QuoDeg + 1));
                    QuoArr[QuoDeg] = 0;
                    Count++;
                }
                
                /*cout << "RemDegreeLast - Rem.Degree: " << RemDegreeLast - Rem.Degree << endl;
                 for (int i = 0; i < RemDegreeLast - Rem.Degree - 1 + Count; i++)
                 {
                 QuoDeg++;
                 QuoArr = (int*)realloc(QuoArr, sizeof(int)*(QuoDeg + 1));
                 QuoArr[QuoDeg] = 0;
                 }
                 RemDegreeLast = Rem.Degree;*/
                
                Natural C;
                while (Comparison(Temp, second) != COMPARISON_SECOND_BIGGER)
                {
                    Temp = Temp - second;
                    C = C + One;
                }
                cout << "C: " << C << endl;
                QuoDeg++;
                QuoArr = (int*)realloc(QuoArr, sizeof(int)*(QuoDeg + 1));
                QuoArr[QuoDeg] = C.Digits[0];
                
                Natural SubRes = InverseSub(Rem, C*second);
                cout << "SubRes: " << SubRes << endl;
                if (SubRes.Degree+1 < Rem.Degree && Comparison(SubRes, second) != COMPARISON_SECOND_BIGGER)
                {
                    Natural Omg;
                    Omg.Degree = second.Degree+1;
                    Omg.Digits = (int*)malloc(sizeof(int)*(Omg.Degree+1));
                    for (int i = Rem.Degree-1; i >= Rem.Degree - Omg.Degree-1; i--)
                    {
                        if (i > SubRes.Degree)
                            Omg.Digits[i - Rem.Degree + Omg.Degree+1] = 0;
                        else
                            Omg.Digits[i - Rem.Degree + Omg.Degree+1] = SubRes.Digits[i];
                    }
                    OptimazeNatural(Omg);
                    cout <<"OMG: "<< Omg << endl;
                    int kount = 2;
                    while (Comparison(Omg, second) == COMPARISON_SECOND_BIGGER)
                    {
                        free(Omg.Digits);
                        
                        Omg.Degree = second.Degree + kount;
                        Omg.Digits = (int*)malloc(sizeof(int)*(Omg.Degree+1));
                        for (int i = Rem.Degree-1; i >= Rem.Degree - Omg.Degree-1; i--)
                        {
                            if (i > SubRes.Degree)
                                Omg.Digits[i - Rem.Degree + Omg.Degree+1] = 0;
                            else
                                Omg.Digits[i - Rem.Degree + Omg.Degree+1] = SubRes.Digits[i];
                        }
                        OptimazeNatural(Omg);
                        cout <<"OMG: "<< Omg << endl;
                        
                        QuoDeg++;
                        QuoArr = (int*)realloc(QuoArr, sizeof(int)*(QuoDeg + 1));
                        QuoArr[QuoDeg] = 0;
                        
                        kount++;
                    }
                    cout << "OffsetToPos: " << OffsetToPos << endl;
                }
                
                //Natural SubRes = RemRev - C*second;
                free(Rem.Digits);
                Rem.Degree = SubRes.Degree;
                Rem.Digits = (int*)malloc(sizeof(int)*(Rem.Degree + 1));
                for (int i = 0; i <= SubRes.Degree; i++)
                    Rem.Digits[i] = SubRes.Digits[i];
                
                
            }
            
            Quo.Degree = QuoDeg;
            Quo.Digits = (int*)malloc(sizeof(int)*Quo.Degree);
            for (int i = 0; i <= Quo.Degree; i++)
                Quo.Digits[i] = QuoArr[Quo.Degree - i];
            
            OptimazeNatural(Rem);
            OptimazeNatural(Quo);
        }
    }
    
    return Quo;
}

Natural operator%(const Natural& other)
{
    Natural Rem;
    
    int ComparisonResult = Comparison(*this, other);
    if (ComparisonResult == COMPARISON_EQUAL_BIGGER)
        SetZero(Rem);
    else
    {
        Natural second;
        
        if (ComparisonResult == COMPARISON_SECOND_BIGGER)
        {
            second = *this;
            Rem = other;
        }
        else
        {
            Rem = *this;
            second = other;
        }
        
        Natural Zero = ConvertToNatural(0);
        if (Comparison(Zero, second) == COMPARISON_EQUAL_BIGGER)
            cout << "Ошибка. Деление на 0." << endl;
        else
        {
            Natural One; SetOne(One);
            
            while (Comparison(Rem, second) != COMPARISON_SECOND_BIGGER)
            {
                cout << "Comparsion: Rem " << Rem << " and second " << second << endl;
                
                Natural Temp;
                Temp.Degree = second.Degree;
                Temp.Digits = (int*)malloc(sizeof(int)*(Temp.Degree+1));
                for (int i = Rem.Degree; i >= Rem.Degree - second.Degree; i--)
                    Temp.Digits[i - Rem.Degree + second.Degree] = Rem.Digits[i];
                cout << Temp << endl;
                
                bool WasBigger = false;
                if (Comparison(Temp, second) == COMPARISON_SECOND_BIGGER)
                {
                    free(Temp.Digits);
                    Temp.Degree = Temp.Degree + 1;
                    Temp.Digits = (int*)malloc(sizeof(int)*(Temp.Degree+1));
                    for (int i = Rem.Degree; i >= Rem.Degree - second.Degree - 1; i--)
                        Temp.Digits[i - Rem.Degree + second.Degree + 1] = Rem.Digits[i];
                    cout << "second was bigger, so "<< Temp << endl;
                    WasBigger = true;
                }
                
                Natural C;
                while (Comparison(Temp, second) != COMPARISON_SECOND_BIGGER)
                {
                    Temp = Temp - second;
                    C = C + One;
                }
                cout << "C: " << C << endl;
                
                //if (Quo.Degree)
                //запись в результат
                
                Natural SubRes = InverseSub(Rem, C*second);
                cout << "SubRes: " << SubRes << endl;
                
                //Natural SubRes = RemRev - C*second;
                free(Rem.Digits);
                Rem.Degree = SubRes.Degree;
                Rem.Digits = (int*)malloc(sizeof(int)*(Rem.Degree + 1));
                for (int i = 0; i <= SubRes.Degree; i++)
                    Rem.Digits[i] = SubRes.Digits[i];
                
            }
            
            OptimazeNatural(Rem);
        }
    }
    
    return Rem;
    
    
    Natural InverseSub(const Natural &first, const Natural &second)
    {
        Natural Sub;
        
        cout << "INVS! " << first << " and " << second << endl;
        
        Natural Temp;
        Temp.Degree = second.Degree;
        Temp.Digits = (int*)malloc(sizeof(int)*(Temp.Degree+1));
        for (int i = first.Degree; i >= first.Degree - second.Degree; i--)
            Temp.Digits[i - first.Degree + second.Degree] = first.Digits[i];
        cout << "INVS! Temp: " << Temp << endl;
        
        int startFrom = second.Degree;
        if (Comparison(Temp, second) == COMPARISON_SECOND_BIGGER)
            startFrom = second.Degree + 1;
        
        Sub.Degree = first.Degree;
        Sub.Digits = (int*)malloc(sizeof(int)*(Sub.Degree + 1));
        int Memorize = 0;
        for (int i = 0; i < first.Degree - startFrom; i++)
            Sub.Digits[i] = first.Digits[i];
        for (int i = first.Degree - startFrom; i <= first.Degree; i++)
        {
            Sub.Digits[i] = first.Digits[i] - second.Digits[i - (first.Degree - startFrom)];
            
            if (Memorize > 0)
            {
                Sub.Digits[i] -= 1;
                Memorize--;
            }
            if (Sub.Digits[i] < 0)
            {
                Sub.Digits[i] += 10;
                Memorize++;
            }
        }
        
        OptimazeNatural(Sub);
        
        return Sub;
    }
    
    
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
            std::string n;
            cin >> n;
            
            for (int i = GetLength(n.c_str()) - 1; i >= 0; i--)
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
        
        Natural operator+(const Natural& other)
        {
            Natural Sum;
            
            int MaxDegree{ this->Degree };
            int ComparisonResult = Comparison(*this, other);
            if (ComparisonResult == COMPARISON_SECOND_BIGGER)
                MaxDegree = other.Degree;
            
            bool Memorize{ false };
            for (int i = 0; i <= MaxDegree; i++)
            {
                Sum.Degree++;
                Sum.Digits = (int*)realloc(Sum.Digits, sizeof(int)*(Sum.Degree + 1));
                
                if (this->Degree >= i && other.Degree >= i)
                    Sum.Digits[i] = this->Digits[i] + other.Digits[i];
                else if (this->Degree < i)
                    Sum.Digits[i] = other.Digits[i];
                else
                    Sum.Digits[i] = this->Digits[i];
                
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
            
            return Sum;
        }
        
        Natural operator-(const Natural& other)
        {
            Natural Sub;
            
            int ComparisonResult = Comparison(*this, other);
            if (ComparisonResult == COMPARISON_EQUAL_BIGGER)
                SetZero(Sub);
            else
            {
                //Natural first;
                //first.Digits = nullptr;
                //Natural second;
                //second.Digits = nullptr;
                
                int MaxDegree{ this->Degree };
                int Memorize{ 0 };
                if (ComparisonResult == COMPARISON_SECOND_BIGGER)
                {
                    MaxDegree = other.Degree;
                    //first = other;
                    //second = *this;
                    
                    for (int i = 0; i <= MaxDegree; i++)
                    {
                        Sub.Degree++;
                        Sub.Digits = (int*)realloc(Sub.Digits, sizeof(int)*(Sub.Degree + 1));
                        
                        if ((*this).Degree >= i)
                            Sub.Digits[i] = other.Digits[i] - (*this).Digits[i];
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
                    //first = *this;
                    //second = other;
                    
                    for (int i = 0; i <= MaxDegree; i++)
                    {
                        Sub.Degree++;
                        Sub.Digits = (int*)realloc(Sub.Digits, sizeof(int)*(Sub.Degree + 1));
                        
                        if (other.Degree >= i)
                            Sub.Digits[i] = (*this).Digits[i] - other.Digits[i];
                        else
                            Sub.Digits[i] = (*this).Digits[i];
                        
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
                
                //free(first.Digits);
                //free(second.Digits);
            }
            
            return Sub;
        }
        
        bool operator!=(int Num)
        {
            return false;
        }
        
        Natural operator*(const Natural& other)
        {
            Natural Mul;
            SetZero(Mul);
            
            for (int i = 0; i <= other.Degree; i++)
            {
                if (other.Digits[i] != 0)
                {
                    Natural CurrentNat;
                    PowerOfTen(CurrentNat, *this, i);
                    
                    Natural SumResult;
                    SetZero(SumResult);
                    
                    for (int j = 1; j <= other.Digits[i]; j++)
                        SumResult = SumResult + CurrentNat;
                    
                    Mul = Mul + SumResult;
                    
                    free(SumResult.Digits);
                    SumResult.Digits = nullptr;
                    free(CurrentNat.Digits);
                    CurrentNat.Digits = nullptr;
                }
            }
            
            return Mul;
        }
        
        Natural operator=(const Natural& other)
        {
            if (this != &other)
            {
                Degree = other.Degree;
                if (Digits != nullptr)
                    free(Digits);
                Digits = nullptr;
                
                if (Degree >= 0)
                {
                    Digits = (int*)malloc(sizeof(int)*(Degree + 1));
                    //std::copy(other.Digits, other.Digits + Degree + 1, Digits);
                    //Digits = std::move(other.Digits);
                    for (int i = 0; i <= Degree; i++)
                        Digits[i] = other.Digits[i];
                }
                if (other.Digits != nullptr)
                    free(other.Digits);
            }
            return *this;
        }
        
        Natural operator/(const Natural& other)
        {
            Natural Quo;
            
            int ComparisonResult = Comparison(*this, other);
            if (ComparisonResult == COMPARISON_EQUAL_BIGGER)
                SetOne(Quo);
            else
            {
                Natural second;
                Natural Rem;
                
                if (ComparisonResult == COMPARISON_SECOND_BIGGER)
                {
                    //second = *this;
                    second.Degree = (*this).Degree;
                    second.Digits = (int*)malloc(sizeof(int)*(second.Degree+1));
                    for (int i = 0; i <= second.Degree; i++)
                        second.Digits[i] = (*this).Digits[i];
                    
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
                    
                    Rem.Degree = (*this).Degree;
                    Rem.Digits = (int*)malloc(sizeof(int)*(Rem.Degree+1));
                    for (int i = 0; i <= Rem.Degree; i++)
                        Rem.Digits[i] = (*this).Digits[i];
                    //Rem = *this;
                    //second = other;
                }
                
                Natural Zero = ConvertToNatural(0);
                if (Comparison(Zero, second) == COMPARISON_EQUAL_BIGGER)
                    cout << "Ошибка. Деление на 0." << endl;
                else
                {
                    Natural One; SetOne(One);
                    while (Comparison(Rem, second) != COMPARISON_SECOND_BIGGER)
                    {
                        Rem = Rem - (second);
                        Quo = Quo + One;
                    }
                    
                    OptimazeNatural(Quo);
                }
                
                //free(second.Digits);
            }
            
            return Quo;
        }
        
        Natural operator%(const Natural& other)
        {
            Natural Rem;
            Natural second;
            
            int ComparisonResult = Comparison(*this, other);
            if (ComparisonResult == COMPARISON_EQUAL_BIGGER)
                SetZero(Rem);
            else
            {
                //Rem = *this;
                
                if (ComparisonResult == COMPARISON_SECOND_BIGGER)
                {
                    //second = *this;
                    //Rem = other;
                    second.Degree = (*this).Degree;
                    second.Digits = (int*)malloc(sizeof(int)*(second.Degree+1));
                    for (int i = 0; i <= second.Degree; i++)
                        second.Digits[i] = (*this).Digits[i];
                    
                    Rem.Degree = (other).Degree;
                    Rem.Digits = (int*)malloc(sizeof(int)*(Rem.Degree+1));
                    for (int i = 0; i <= Rem.Degree; i++)
                        Rem.Digits[i] = (other).Digits[i];
                }
                else
                {
                    //Rem = *this;
                    //second = other;
                    second.Degree = (other).Degree;
                    second.Digits = (int*)malloc(sizeof(int)*(second.Degree+1));
                    for (int i = 0; i <= second.Degree; i++)
                        second.Digits[i] = (other).Digits[i];
                    
                    Rem.Degree = (*this).Degree;
                    Rem.Digits = (int*)malloc(sizeof(int)*(Rem.Degree+1));
                    for (int i = 0; i <= Rem.Degree; i++)
                        Rem.Digits[i] = (*this).Digits[i];
                }
                
                Natural Zero = ConvertToNatural(0);
                if (Comparison(Zero, second) == COMPARISON_EQUAL_BIGGER)
                    cout << "Ошибка. Деление на 0." << endl;
                else
                {
                    while (Comparison(Rem, second) != COMPARISON_SECOND_BIGGER)
                    {
                        Natural Sub = Rem - (second);
                        Rem = Sub;
                    }
                    
                    OptimazeNatural(Rem);
                }
            }
            
            return Rem;
        }
    };
    
    
    
    void MoveNat(Natural Nat1, Natural Nat2)
    {
        Nat1.Degree = Nat2.Degree;
        if (Nat1.Digits != nullptr)
            free(Nat1.Digits);
        Nat1.Digits = std::move(Nat2.Digits);
    }
    
    void Free(Natural Nat)
    {
        if (Nat.Digits != nullptr)
            free(Nat.Digits);
        Nat.Digits = nullptr;
        Nat.Degree = -1;
    }
    
    
    //----------------------------------------------------------
    //Natural InputNatural()
    //Выводит на экран меню.
    //----------------------------------------------------------
    Natural InputNatural()
    {
        Natural Nat;
        std::string n;
        
        cin >> n;
        for (int i = GetLength(n.c_str()) - 1; i >= 0; i--)
        {
            if (n[i] >= 48 && n[i] <= 57)
            {
                Nat.Degree++;
                Nat.Digits = (int*)realloc(Nat.Digits, sizeof(int)*(Nat.Degree+1));
                Nat.Digits[Nat.Degree] = n[i] - 48;
            }
        }
        
        return Nat;
    }
    
    //----------------------------------------------------------
    //Integer InputInteger()
    //Выводит на экран меню.
    //----------------------------------------------------------
    Integer InputInteger()
    {
        Integer Int;
        std::string n;
        
        cin >> n;
        int Length = GetLength(n.c_str()) - 1;
        for (int i = Length; i >= 0; i--)
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
        
        return Int;
    }
    
    //----------------------------------------------------------
    //PrintNumber(Natural &Nat)
    //Выводит на экран меню.
    //----------------------------------------------------------
    void PrintNumber(Natural &Nat)
    {
        if (Nat.Degree == -1 || Nat.Digits == nullptr)
            cout << "Числа не существует." << endl;
        else
        {
            for (int i = Nat.Degree; i >= 0; i--)
                cout << Nat.Digits[i];
            cout << endl;
        }
    }
    
    //----------------------------------------------------------
    //PrintNumber(Integer &Int)
    //Выводит на экран меню.
    //----------------------------------------------------------
    void PrintNumber(Integer &Int)
    {
        if (Int.Degree == -1 || Int.Digits == nullptr)
            cout << "Числа не существует." << endl;
        else
        {
            if (Int.Sign)
                cout << "-";
            for (int i = Int.Degree; i >= 0; i--)
                cout << Int.Digits[i];
            cout << endl;
        }
    }
    
    //----------------------------------------------------------
    //void SetZero(Natural&)
    //Выводит на экран меню.
    //----------------------------------------------------------
    Natural ConvertToNatural(int n)
    {
        Natural Nat;
        
        SetZero(Nat);
        while (n != 0)
        {
            int dig = n % 10;
            Nat.Digits = (int*)realloc(Nat.Digits, sizeof(int)*(Nat.Degree+1));
            Nat.Digits[Nat.Degree+1] = dig;
            Nat.Degree++;
            n /= 10;
        }
        if (Nat.Degree == -1)
            Nat.Degree = 0;
        
        return Nat;
    }
    
    
    //----------------------------------------------------------
    //void Subtraction(QuadIrrationality&, QuadIrrationality, QuadIrrationality)
    //Разность квадратичных иррациональностей.
    //----------------------------------------------------------
    void ExpandAsContinuedFraction(ContinuedFraction& Result, QuadIrrationality Quad)
    {
        QuadIrrationality *PeriodArray{ nullptr };
        int PeriodArrayCount{ 0 };
        
        bool PeriodFound{ false };
        int PeriodStartPos{ 0 };
        for (int i = 0; i <= 10000 && !PeriodFound; i++)
        {
            Integer BSquared; Multiply(BSquared, Quad.b, Quad.b);
            Natural BSquaredNat; BSquaredNat.Degree = BSquared.Degree; BSquaredNat.Digits = BSquared.Digits;
            Natural PreciseRoot; Multiply(PreciseRoot, Quad.c, BSquaredNat); cout << "PreciseRoot: " << PreciseRoot << endl;
            Natural RootEstimation; EstimateRootLowerThat(RootEstimation, PreciseRoot); cout << "RootEstimation: " << RootEstimation << endl;
            Integer FromCPart; FromCPart.Sign = Quad.b.Sign; FromCPart.Degree = RootEstimation.Degree; FromCPart.Digits = RootEstimation.Digits; cout << "FromCPart: " << FromCPart << endl;
            
            Integer NumeIntegerPart; Summary(NumeIntegerPart, Quad.a, FromCPart); cout << "NumeIntegerPart: " << NumeIntegerPart << endl;
            Integer IntegerPart; Divide(IntegerPart, NumeIntegerPart, Quad.d); cout << "IntegerPart: " << IntegerPart << endl;
            
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
            
            cout << "NextQuad: " << NextQuad << endl;
            
            Integer ConjugatedDeno; MultiplyByConjugate(ConjugatedDeno, NextQuad);
            cout << "ConjugatedDeno: " << ConjugatedDeno << endl;
            
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
            
            cout << "CompleteQuad: " << CompleteQuad << endl;
            ReduceQuadIrrationality(CompleteQuad);
            cout << "CompleteQuadReduced: " << CompleteQuad << endl;
            
            if (i != 0)
            {
                PeriodArrayCount++;
                PeriodArray = (QuadIrrationality*)realloc(PeriodArray, sizeof(QuadIrrationality)*(PeriodArrayCount));
                QuadIrrationalityEquasion(PeriodArray[PeriodArrayCount - 1], Quad);
                
                for (int j = 0; j < PeriodArrayCount-1 && !PeriodFound; j++)
                {
                    for (int k = j + 1; k < PeriodArrayCount && !PeriodFound; k++)
                    {
                        PeriodFound = (Comparison(PeriodArray[j], PeriodArray[k]) == COMPARISON_EQUAL_BIGGER);
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
            
            /*if (IntegerPart.Digits != nullptr)
             free(IntegerPart.Digits);*/
            if (RootEstimation.Digits != nullptr)
                free(RootEstimation.Digits);
            if (PreciseRoot.Digits != nullptr)
                free(PreciseRoot.Digits);
            if (BSquared.Digits != nullptr)
                free(BSquared.Digits);
            if (NumeIntegerPart.Digits != nullptr)
                free(NumeIntegerPart.Digits);
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
    
    //----------------------------------------------------------
    //void ExpandAsContinuedFraction(ContinuedFraction&, QuadIrrationality)
    //Преобразование квадратичной иррациональности в цепную периодическую дробь.
    //----------------------------------------------------------
    void ExpandAsContinuedFraction(ContinuedFraction& Result, QuadIrrationality Quad)
    {
        QuadIrrationality *PeriodArray{ nullptr };
        int PeriodArrayCount{ 0 };
        
        bool PeriodFound{ false };
        int PeriodStartPos{ 0 };
        for (int i = 0; i <= 10000 && !PeriodFound; i++)
        {
            Integer BSquared; Multiply(BSquared, Quad.b, Quad.b);
            Natural BSquaredNat; BSquaredNat.Degree = BSquared.Degree; BSquaredNat.Digits = BSquared.Digits;
            Natural PreciseRoot; Multiply(PreciseRoot, Quad.c, BSquaredNat);
            Natural RootEstimation; EstimateRootLowerThat(RootEstimation, PreciseRoot);
            Integer FromCPart; FromCPart.Sign = Quad.b.Sign; FromCPart.Degree = RootEstimation.Degree; FromCPart.Digits = RootEstimation.Digits;
            
            Integer NumeIntegerPart; Summary(NumeIntegerPart, Quad.a, FromCPart);
            Integer IntegerPart; Divide(IntegerPart, NumeIntegerPart, Quad.d);
            
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
                        PeriodFound = (Comparison(PeriodArray[j], PeriodArray[k]) == COMPARISON_EQUAL_BIGGER);
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
            
            /*if (IntegerPart.Digits != nullptr)
             free(IntegerPart.Digits);*/
            if (RootEstimation.Digits != nullptr)
                free(RootEstimation.Digits);
            if (PreciseRoot.Digits != nullptr)
                free(PreciseRoot.Digits);
            if (BSquared.Digits != nullptr)
                free(BSquared.Digits);
            if (NumeIntegerPart.Digits != nullptr)
                free(NumeIntegerPart.Digits);
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
    
    //----------------------------------------------------------
    //void ExpandAsContinuedFractionN(ContinuedFraction&, QuadIrrationality, int)
    //Преобразование квадратичной иррациональности в периодическую дробь из N элементов.
    //----------------------------------------------------------
    void ExpandAsContinuedFractionN(ContinuedFraction& Result, QuadIrrationality Quad, int N)
    {
        Result.isNotCompleted = true;
        for (int i = 0; i < N; i++)
        {
            Integer IntegerPart; GetIntegerPartFromQuadIrrationality(IntegerPart, Quad);
            /*Integer BSquared; Multiply(BSquared, Quad.b, Quad.b);
             Natural BSquaredNat; BSquaredNat.Degree = BSquared.Degree; BSquaredNat.Digits = BSquared.Digits;
             Natural PreciseRoot; Multiply(PreciseRoot, Quad.c, BSquaredNat);
             Natural RootEstimation; EstimateRootLowerThat(RootEstimation, PreciseRoot);
             Integer FromCPart; FromCPart.Sign = Quad.b.Sign; FromCPart.Degree = RootEstimation.Degree; FromCPart.Digits = RootEstimation.Digits;
             
             Integer NumeIntegerPart; Summary(NumeIntegerPart, Quad.a, FromCPart);
             Integer IntegerPart; Divide(IntegerPart, NumeIntegerPart, Quad.d);*/
            
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
            
            /*if (RootEstimation.Digits != nullptr)
             free(RootEstimation.Digits);
             if (PreciseRoot.Digits != nullptr)
             free(PreciseRoot.Digits);
             if (BSquared.Digits != nullptr)
             free(BSquared.Digits);
             if (NumeIntegerPart.Digits != nullptr)
             free(NumeIntegerPart.Digits);*/
            if (IntegerPartMultipliedByD.Digits != nullptr)
                free(IntegerPartMultipliedByD.Digits);
        }
    }

#endif /* obsolete_h */
