/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>
#include <iostream>
#include <vector>

//struct Option
//{
//    char token; //"-x"
//    std::string word; //"--abc"
//};

template < class FuncClass, class ParamT = std::vector<std::string> >
class Command
{
    public:
        Command(FuncClass* obj, std::string name, void (FuncClass::*mptr)(), void (FuncClass::*mptr_val)(ParamT)=0) : name(name), obj(obj), mptr(mptr), mptr_val(mptr_val)
        {

        }
    private:
        std::string name;
        FuncClass* obj; //object to execute function on
        void (FuncClass::*mptr)(); //pointer to function with no parameters
        void (FuncClass::*mptr_val)(ParamT); //pointer to function with parameter
        //std::vector<Option> options;

    public:
        std::string get_name()
        {
            return name;
        }
        void execute ()
        {
            //std::cout << "Enter execute()..." << std::endl;
            if (mptr != 0)
                ((*obj).*mptr)();
        }
        void execute(ParamT values)
        {
            if (mptr_val != 0)
                ((*obj).*mptr_val)(values);
        }
};


#endif // COMMAND_H_INCLUDED
