//
//  Base.hpp
//  Eltech_DM2018_Exam2Sem
//
//  Created by Никита Исаенко on 07.06.2018.
//  Copyright © 2018 Melanholy Hill. All rights reserved.
//

#ifndef BaseFunctions_hpp
#define BaseFunctions_hpp

#include <iostream>

/*Для кроссплатформенности между консолью (cmd.exe) Windows и терминалом (Terminal.app) UNIX*/
void systempause();
void systemclear();

/*Объявляем константы*/
#define COMPARISON_FIRST_BIGGER 0
#define COMPARISON_SECOND_BIGGER 1
#define COMPARISON_EQUAL_BIGGER 2
#define COMPARISON_UNUSED_EQUAL 3

/*Объявляем вспомогательные функции*/
char* InputString();
int GetLength(const char*);

#endif /* BaseFunctions_hpp */
