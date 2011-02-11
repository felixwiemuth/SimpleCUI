/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>
#include <iostream>

struct Option
{
    char token;
    std::string word;
}

template <typename FuncClass>
class Command
{
    public:
        Command(FuncClass& obj, void (FuncClass::*mptr)(), char token, const std::string word) : token(token), word(word)
        {
            std::cout << "Simple constructor called..." << std::endl;
            (obj.*mptr)();
        }
        //Command( void (FuncClass::*func)(), char token, const std::string word = "" );
    private:
        const char token; //"-x"
        const std::string word; //"--abc"
        void (FuncClass::*func)(); //pointer to function

    public:
        char get_token()
        {
            return token;
        }
        std::string get_word()
        {
            return word;
        }
};


#endif // COMMAND_H_INCLUDED
