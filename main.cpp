/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#include "Cui.h"

#include <iostream>

using namespace std;

class TestClass
{
    public:
        TestClass()
        {
            cout << "Constructor of 'TestClass' called!" << endl;
        }
    private:
        int x;
        char c;
    public:
        void sample_method()
        {
            cout << "Executing 'sample_method()'" << endl;
        }
        void exit_program()
        {
            cout << "Executing function! gee :)" << endl;
            exit(0);
        }
        void mymeth(vector<string> myvals)
        {
            cout << "first val=" << myvals[0] << endl;
        }
};

int main()
{
    TestClass myobj;
    Cui<TestClass> cui;

    Command<TestClass> comm(&myobj, "exit", &TestClass::exit_program);

    cui.add_command(comm);
    cui.add_command(&myobj, "fun", 0, 0);
    cui.add_command(&myobj, "vals", 0, &TestClass::mymeth);

    cui.start();

    return 0;
}
