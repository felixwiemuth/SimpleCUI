/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#ifndef CUI_H_INCLUDED
#define CUI_H_INCLUDED

#include "Command.h"

#include <boost/algorithm/string/split.hpp>
#include <vector>
#include <list>

//struct Instruction
//{
//    std::string option; //ooption X called ("-X")
//    std::vector<std::string> values; //values A, B, C, ... added to the option ("-X A B C")
//
//    Instruction(std::string option, std::vector<std::string> values)
//    {
//        this->option = option;
//        this->values = values;
//    }
//};

template <typename FuncClass>
class Cui
{
    public:
        Cui()
        {

        }
    private:
        std::vector< Command<FuncClass> > cmds;
    public:
        void add_command(FuncClass* obj, std::string name, void (FuncClass::*mptr)(), void (FuncClass::*mptr_val)(std::vector<std::string>)=0)
        {
            cmds.push_back(Command<FuncClass>(obj, name, mptr, mptr_val));
        }
        void add_command(Command<FuncClass>& cmd)
        {
            cmds.push_back(cmd);
        }
        void start()
        {
            std::string in;
            while(true)
            {
                std::cout << "> ";
                getline(std::cin, in);
                std::cout << std::endl;
                std::list<std::string> words;
                boost::split(words, in, [](const char c)->bool{return c == ' ';});
                //check if command
                int cmd = -1;
                for (int i = 0; i < cmds.size(); i++)
                {
                    if (cmds[i].get_name() == words.front())
                    {
                        cmd = i;
                        break;
                    }
                }
                if (cmd == -1)
                {
                    //not a command
                    std::cout << "ERROR: not a command" << std::endl; //DEBUG
                    continue;
                }

                words.pop_front();
                //words[0]...words[n] == values
                //std::cout << "WORDS.SIZE=" << words.size() << std::endl;
                if (words.size() == 0)
                    cmds[cmd].execute();
                else
                    cmds[cmd].execute(std::vector<std::string>(words.begin(), words.end()));


//                std::vector<Instruction> instr;
//                for (std::vector<std::string>::iterator it = words.begin(); it != words.end(); ++it)
//                {
//                    if ((*it)[0] != '-')
//                    {
//                        std::vector<std::string> options;
//
//                    }
//
//                }

            }

        }

};


#endif // CUI_H_INCLUDED
