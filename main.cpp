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
    /*
        ----- Working contructor arguments -----
*/
        //typedef void (TestClass::*sample_method_pointer)();
        //Command<TestClass> cmd( sample_method_pointer );
/*

        Command<TestClass> cmd( void (TestClass::*)() );
    */

    TestClass myobj;
//    Command<TestClass> cmd(&myobj, "mycmdname", &TestClass::sample_method);
//    cout << "adress of sample_method: " << &TestClass::sample_method << endl;
    Cui<TestClass> cui;

    Command<TestClass> comm(&myobj, "exit", &TestClass::exit_program);
    //cui.add_command(comm);
    cui.add_command(comm);
    cui.add_command(&myobj, "fun", 0, 0);
    cui.add_command(&myobj, "vals", 0, &TestClass::mymeth);
    //cui.add_command(&myobj, "exit", &TestClass::exit_program);

    cui.start();

//    Command<TestClass> cmd(myobj, &TestClass::sample_method, '-s', "-sample");
    //Command<TestClass> cmda(myobj, void (TestClass::*)());

    //Command<TestClass> cmd( void (TestClass::*)() );
    //typedef void (TestClass::*sample_method_pointer)();
//    sample_method_pointer myptr;
//    myptr = &TestClass::sample_method;
//    cout << "Hello world!" << endl;
//    TestClass myobj;
//    (myobj.*myptr)();

    //Command<TestClass> cmd( void (TestClass::*)() );
    //Command<TestClass> cmd(sample_method_pointer);
    //Command<TestClass> cmd(myobj, sample_method_pointer);

//    Command<TestClass> cmd_b(&TestClass::sample_method);
    //Command<TestClass> cmd_a( (myptr)() );
    //Command<TestClass> cmd(myptr, 'ü', "rüber");


    return 0;
}
