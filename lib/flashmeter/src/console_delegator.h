#ifndef CONSOLE_DELEGATOR_H
#define CONSOLE_DELEGATOR_H

class ConsoleDelegator{

    public:
        virtual void print( char const *message) = 0;
        virtual void println( char const *message)= 0;
};

#endif //CONSOLE_DELEGATOR_H