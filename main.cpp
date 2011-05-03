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
            cout << "Exit program by member function!" << endl;
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

    //examples of correct using
    cui["valmeth"].set(&myobj, 0, &TestClass::mymeth).execute(testvals);
    cui["valmeth"].set_help("A method to demonstrate commands with values");
    cui["sample"].set(&myobj, &TestClass::sample_method);
    cui["sample"].set_help("A method to demonstrate simple commands without parameters");
    //examples of no-good using
    //NOTE: Even if you intend to set the missing values later,
    //      it is not guaranteed that the user does not call an invalid method in meantime!
    //      (Anyway this will cause no crashes because Cui is careful)
    //      In that case you should better set the needed values,
    //      turn the "available"-switch off and set a "not-available"-message!
    cui["wrong"].set(0, &TestClass::sample_method); //WRONG USAGE: no object is passed with the method, calling it will cause an error message!
    cui["wrong2"].set(&myobj, 0, 0); //WRONG USAGE: none of both method types passed, user will get (maybe confusing) errors while trying to use the method!

    //example of overwriting standard "exit" of Cui
    cui["exit"].set(&myobj, &TestClass::exit_program);

    //test activation/deactivation, error messages
    std::string testerr = "mauuerr!";
    cui["valmeth"].point_err_msg(&testerr); //set an own string ('testerr') as error message for this command
    cui["valmeth"].deactivate(); //deactivate comman "valmeth"
    cui["valmeth"].activate(); //reactivate comman "valmeth"
    cui["sample"].add_err_msg("This command is not available!"); //error message to show when command not available
    cui["sample"].set_err_msg(0); //activate added error message
    cui["sample"].deactivate(); //deactivate command "sample"

    cui.run();

    return 0;
}
