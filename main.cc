#include <iostream>
using namespace std;

#include "Node.h"
#include "rational.h"
#include "calculator.h"

int main(int argc,const char* argv[])
{
    while(true)
    {
        string exp;
        while(true)
        {
            cout << ">"; 
            getline(cin, exp);
            if(exp[0] == 'q' || exp[0] == 'Q') return 0;
            Calculator::pre_process(exp);
            NodePtr p = Calculator::build_tree(exp);
            RationalValue value = p->calculate();
            cout << value << endl;
        }
    }
}

        c = 0;

        switch((c=getch())) {
        case KEY_UP:
            cout << endl << "Up" << endl;//key up
            break;
        case KEY_DOWN:
            cout << endl << "Down" << endl;   // key down
            break;
        case KEY_LEFT:
            cout << endl << "Left" << endl;  // key left
            break;
        case KEY_RIGHT:
            cout << endl << "Right" << endl;  // key right
            break;
        default:
            cout << endl << "null" << endl;  // not arrow
            break;
        }