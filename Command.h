/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>
#include <iostream>
#include <vector>


template <class FuncClass>
class Command
{
    typedef void (FuncClass::*Mptr)();
    typedef void (FuncClass::*Mptr_val)(std::vector<std::string>);

    public:
        Command()
        {
            obj = 0;
            mptr = 0;
            mptr_val = 0;
        }

        Command(FuncClass* obj, Mptr mptr, Mptr_val mptr_val=0) : obj(obj), mptr(mptr), mptr_val(mptr_val)
        {

        }


    private:
        FuncClass* obj; //object to execute function on
        void (FuncClass::*mptr)(); //pointer to function with no parameters
        void (FuncClass::*mptr_val)(std::vector<std::string>); //pointer to function with parameter


    public:
        Command<FuncClass>& set(const Command<FuncClass>& other) //replace '*this' with 'other'
        {
            *this = other;
            return *this;
        }
        Command<FuncClass>& set(FuncClass* obj, Mptr mptr, Mptr_val mptr_val=0) //'set(...)' as "constructor" version
        {
            this->obj = obj;
            this->mptr = mptr;
            this->mptr_val = mptr_val;
            return *this;
        }

        bool execute()
        {
            if (obj != 0 && mptr != 0)
            {
                ((*obj).*mptr)();
                return true;
            }
            return false;
        }

        bool execute(std::vector<std::string> values)
        {
            if (obj != 0 && mptr_val != 0)
            {
                ((*obj).*mptr_val)(values);
                return true;
            }
            return false;
        }
};


#endif // COMMAND_H_INCLUDED
