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
            err_msg = msg_not_available.end();
        }

        Command(FuncClass* obj, Mptr mptr, Mptr_val mptr_val=0) : obj(obj), mptr(mptr), mptr_val(mptr_val)
        {
            err_msg = msg_not_available.end();
        }


    private:
        bool available; //methods in 'mptr' and 'mptr_val' can only be executed if set 'true' -- otherwise '*err_msg' is shown
        std::vector<std::string> msg_not_available; //container of messages that include reasons why this method is not available
        std::vector<std::string>::iterator err_msg; //activated not-available-message
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
            return set(Command<FuncClass>(obj, mptr, mptr_val));
        }

        int check_valid() //return value: 0 = execution of 'mptr' or 'mptr_val' would be valid (regarding 'available' and 'obj') 1 = not available 2 = obj==0
        {
            if (!available)
            {
                if (err_msg != msg_not_available.end())
                    std::cout << *err_msg << std::endl;
                return 1;
            }
            if (obj == 0)
            {
                return 2;
            }
            return 0;
        }

        int execute() //return values: 0-2: 'check_valid()' 3 = no 'mptr' defined
        {
            int ret = check_valid();
            if (ret != 0)
                return ret;
            if (mptr == 0)
            {
                return 3;
            }
            ((*obj).*mptr)();
            return 0;
        }

        int execute(std::vector<std::string> values) //return values: 0-2: 'check_valid()' 4 = no 'mptr_val' defined
        {
            int ret = check_valid();
            if (ret != 0)
                return ret;
            if (mptr_val == 0)
            {
                return 3;
            }
            ((*obj).*mptr_val)(values);
            return 0;
        }
};


#endif // COMMAND_H_INCLUDED
