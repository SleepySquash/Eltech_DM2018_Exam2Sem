//
//  main.cpp
//  Eltech_DM2018_Exam2Sem
//
//  Created by Никита Исаенко on 24.05.2018.
//  Copyright © 2018 Melanholy Hill. All rights reserved.
//

#include "Essentials/Base.hpp"

#include "Modules/Natural.hpp"
#include "Modules/Integer.hpp"
#include "Modules/Fraction.hpp"
#include "Modules/ContinuedFraction.hpp"
#include "Modules/QuadIrrationality.hpp"

/*Для упрощения вызова следующих функций*/
using std::endl;
using std::cout;
using std::cin;

/*Объявляем функции меню*/
int InputDecision();
void Menu();
void SubMenu_QuadraticIrrationalities();
void Menu_QuadraticIrrationalities();
void PrintHelp();

int main()
{
    setlocale (LC_ALL, "Russian");
    
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
    cout << "Ввод квадратичных иррациональностей осуществляется следующим образом: " << endl;
    cout << "\"a +- bVc/d\", где a, b - целые числа, +- - любой знак, c, d - натуральные числа, V/v - значок корня. В записи могут отсутствовать a, b и d." << endl;
}
