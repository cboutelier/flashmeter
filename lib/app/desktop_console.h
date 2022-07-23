#pragma once

#include <console_delegator.h>
#include <unity.h>
#include <iostream>
using namespace std;

class DesktopConsole : public ConsoleDelegator
{

public:
    void print(char const *message)
    {

        cout << message;
    };
    void println(char const *message)
    {
        cout << message << endl;
        cout << endl;
        //UnityPrint(message);
        
    };
};