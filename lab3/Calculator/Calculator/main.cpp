#include <iostream>
#include "Calculator.h"
#include "Menu.h"
#include <fstream>

int main()
{    
    Calculator calc;
    std::cout << "Functional: var <name1> | let <name1>=<value> | let <name2>=<name1>\n"
        << "\t" << "fn <fn2>=<fn1> | fn <fn2>=<fn1|var><operation><fn|var>\n"
        << "\t" << "print <var|fn> | printvars | printfns\n";
    Menu(calc);
}
