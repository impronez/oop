#include <iostream>
#include "CStringList.h"
#include <list>

int main()
{
    CStringList list;
    list.PushBack("lo");
    list.PushBack("lo");
    list.PushBack("lo");
    list.PushBack("lo");

    auto ir = list.rbegin()--;

}