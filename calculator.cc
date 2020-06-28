#include "matetemplate_test.h"
#include "Node.h"
#include "rational.h"

#include <iostream>
#include <cassert>
#include <sstream>
#include <chrono>
using namespace std;

typedef shared_ptr<Type::Node> NodePtr;

void testNode()
{
    // shared_ptr<double> p = shared_ptr<int>
    NodePtr a = std::make_shared<Type::NumberNode>(10);
    NodePtr b(static_cast<Type::Node*>(new Type::NumberNode(20)));
    NodePtr c  = std::make_shared<Type::NumberNode>(30);
    NodePtr d = std::make_shared<Type::NumberNode>(0);

    NodePtr add = std::make_shared<Type::BinaryNode>(a, b, Type::CalculateOp::Plus);
    NodePtr minus = std::make_shared<Type::BinaryNode>(a, b, Type::CalculateOp::Minus);
    NodePtr devide = std::make_shared<Type::BinaryNode>(b, a, Type::CalculateOp::Devide);
    NodePtr multi = std::make_shared<Type::BinaryNode>(b, a, Type::CalculateOp::Multi);
    NodePtr devide_zero = std::make_shared<Type::BinaryNode>(b, d, Type::CalculateOp::Devide);

    NodePtr sum = std::make_shared<Type::BinaryNode>(add, a, Type::CalculateOp::Plus);

    assert(add->calculate().getInteger() == 30);
    assert(minus->calculate().getInteger() == -10);
    assert(multi->calculate().getInteger() == 200);
    assert(devide->calculate().getInteger() == 2);

    assert(sum->calculate().getInteger() == 40);

    // try
    // {
    //     devide_zero->calculate();
    // }
    // catch(const std::invalid_argument& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
    
    
}

string& trim(string& str)
{
    if(str.empty()) return str;

    str.erase(0, str.find_first_not_of(" "));
    str.erase(str.find_last_not_of(" ") + 1);
    return str;
}

void pre_process(string& str)
{
    string result;
    for(char c : str)
    {
        if(c == ' ') continue;
        if(c == '-') 
        {
            result += "+-";
        }
        else
        {
            result += c;
        }
    }
    str = result;
}

size_t symbol_find(const string& exp, const string& symbols)
{
    for(auto symbol : symbols)
    {
        auto pos = exp.find_last_of(symbol);
        if(pos != string::npos)
            return pos;
    }
    return string::npos;
}

// NodePtr build_tree_with_brackets(string& exp)
// {
//     auto pos = symbol_find(exp, "+/*");
//     if(pos != string::npos)
//     {
//         NodePtr root = nullptr;
//         if(exp[pos] == '+')
//         {
//             root = make_shared<Type::BinaryNode>(Type::CalculateOp::Plus);
//         }
//         else if(exp[pos] == '*')
//         {
//             root = make_shared<Type::BinaryNode>(Type::CalculateOp::Multi);
//         }
//         else if(exp[pos] == '/')
//         {
//             root = make_shared<Type::BinaryNode>(Type::CalculateOp::Devide);
//         }
//         string left_str = exp.substr(0, pos);
//         string right_str = exp.substr(pos + 1);
//         root->setLeft(build_tree(left_str));
//         root->setRight(build_tree(right_str));

//         return root;
//     }

//     // exp = std::replace(exp.begin(), exp.end(), '(', '');
//     exp = trim(exp);
//     if(exp.empty())
//     {
//         throw invalid_argument("warong expression");
//     }

//     pos = exp.find(".");
//     if(pos != string::npos)
//     {
//         double value = atof(exp.c_str());
//         RationalValue rv(static_cast<int>(value), value - static_cast<int>(value));
//         return make_shared<Type::NumberNode>(rv);
//     }
//     else
//     {
//         int value = atoi(exp.c_str());
//         RationalValue rv(value);
//         return  make_shared<Type::NumberNode>(value);
//     }
// }

NodePtr build_tree(string& str)
{

    auto pos = str.find_last_of("+-");
    if(pos != string::npos)
    {
        NodePtr root = nullptr;
        if(str[pos] == '+')
        {
            root = make_shared<Type::BinaryNode>(Type::CalculateOp::Plus);
        }
        else 
        {
            root = make_shared<Type::BinaryNode>(Type::CalculateOp::Minus);
        }
        string left_str = str.substr(0, pos);
        string right_str = str.substr(pos + 1);
        root->setLeft(build_tree(left_str));
        root->setRight(build_tree(right_str));

        return root;
    }
    
    pos = str.find_last_of("/*");
    if(pos != string::npos)
    {
        NodePtr root = nullptr;
        if(str[pos] == '*')
        {
            root = make_shared<Type::BinaryNode>(Type::CalculateOp::Multi);
        }
        else 
        {
            root = make_shared<Type::BinaryNode>(Type::CalculateOp::Devide);
        }
        string left_str = str.substr(0, pos);
        string right_str = str.substr(pos + 1);
        root->setLeft(build_tree(left_str));
        root->setRight(build_tree(right_str));

        return root;
    }

    str = trim(str);
    if(str.empty())
    {
        throw invalid_argument("warong expression");
    }

    pos = str.find(".");
    if(pos != string::npos)
    {
        double value = atof(str.c_str());
        RationalValue rv(static_cast<int>(value), value - static_cast<int>(value));
        return make_shared<Type::NumberNode>(rv);
    }
    else
    {
        int value = atoi(str.c_str());
        RationalValue rv(value);
        return  make_shared<Type::NumberNode>(value);
    }
}

void trim_test()
{
    std::cout << "trim test start ..." << endl;
    string test_str = "  ";
    assert(trim(test_str) == string(""));
    test_str = " 3 4 ";
    assert(trim(test_str) == string("3 4"));
    test_str = "";
    assert(trim(test_str) == test_str);
    cout << "trim test all passed ... " << endl;

}



void build_test()
{
    cout << "build test ..." << endl;
    // string exp1 = "2*3 + 4*3 - 10";
    string exp1 = "2*3";
    auto ptr = build_tree(exp1);
    assert(ptr->calculate().getInteger() == 6);

    string exp2 = "18/3*2";
    ptr = build_tree(exp2);
    // cout << exp2 << " = " << ptr->calculate() << endl;
    assert(ptr->calculate().getInteger() == 12);

    string exp3 = "6+3";
    ptr = build_tree(exp3);
    assert(ptr->calculate().getInteger() == 9);

    string exp4 = "6-3";
    // pre_process(exp4);
    ptr = build_tree(exp4);
    assert(ptr->calculate().getInteger() == 3);

    string exp5 = "2*3 - 2 + 2/2";
    // pre_process(exp5);
    ptr = build_tree(exp5);
    assert(ptr->calculate().getInteger() == 5);

    string exp = "100 * 10 + 50 /2 -60+20/2";
    // pre_process(exp);
    ptr = build_tree(exp);
    assert(ptr->calculate().getInteger() == 975);

    exp = "100*10/2*5/4";
    // pre_process(exp);
    ptr = build_tree(exp);
    assert(ptr->calculate().getInteger() == 625);


    cout << "build test passed ..." << endl;
    return;
}


// void mate_template_test()
// {
//     auto start_t = chrono::system_clock::now();
//     int result = Fibonacci<45>::value;
//     auto end_t = chrono::system_clock::now();

//     std::cout << "Fibonacci(100) = " << result << "\t" 
//         << "elapsed time: " << (chrono::duration_cast<chrono::milliseconds>(end_t - start_t)).count() 
//         << "s" << std::endl;

//     start_t = chrono::system_clock::now();
//     result = fibonacci(45);
//     end_t = chrono::system_clock::now();
//     std::cout << "Fibonacci(100) = " << result << "\t" 
//     << "elapsed time: " << (chrono::duration_cast<chrono::milliseconds>(end_t - start_t)).count() 
//     << "s" << std::endl;
// }

int main()
{
    // mate_template_test();
    build_test();
    // trim_test();
    testNode();
}