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

    vector<string> testvals;
    testvals.push_back("TestValue");

    cui["valmeth"].set(Command<TestClass>(&myobj, 0, &TestClass::mymeth)).execute(testvals);
    cui["sample"].set(&myobj, &TestClass::sample_method);

    cui.run();

    return 0;
}
