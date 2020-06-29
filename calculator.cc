#include "calculator.h"
#include <stack>
#include <stdexcept>

using namespace std;
void Calculator::trim(string& str)
{
    if(str.empty()) return ;

    str.erase(0, str.find_first_not_of(" "));
    str.erase(str.find_last_not_of(" ") + 1);
}

void Calculator::pre_process(string& str)
{
    string result;
    for(char c : str)
    {
        if(c == ' ') continue;
        else result.push_back(c);
    }
    str = result;
}

static NodePtr split_exp(size_t pos, const string& exp,  string& left, string& right)
{
    // pos = exp.find_first_of("+-*/", pos);
    char op_char = exp[pos];
    NodePtr root;
    switch (op_char)
    {
        case '+':
            root =make_shared<Type::BinaryNode>(Type::CalculateOp::Plus);
            break;
        case '-':
            root = make_shared<Type::BinaryNode>(Type::CalculateOp::Minus);
            break;
        case '*':
            root = make_shared<Type::BinaryNode>(Type::CalculateOp::Multi);
            break;
        case '/':
            root = make_shared<Type::BinaryNode>(Type::CalculateOp::Devide);
            break;
        default:
            throw out_of_range(string("symbol is not support '") + string(op_char, 1) + string("'"));
    }
    
    left = exp.substr(0, pos);
    right = exp.substr(pos + 1);
    return root;
}

void Calculator::erase_brackets(string& exp)
{
    if(exp[0] != '(' || exp[exp.size() -1] != ')') return;
    stack<int> s;
    for(size_t i = 0; i < exp.size() - 1; i++)
    {
        char ch = exp[i];
        if(ch == '(') s.push(i);
        if(ch == ')') s.pop();
        if(s.empty()) return;
    }
    exp.erase(exp.size() -1, 1);
    exp.erase(0, 1);
    erase_brackets(exp);
    return;
}

static size_t search_symbol(string& exp, const string& symbol)
{
    if(exp.find_first_of(symbol) == string::npos) return string::npos;

    auto pos = exp.find_first_of("(");
    if(pos == string::npos)
    {
        return exp.find_last_of(symbol);
    }

    Calculator::erase_brackets(exp);
    stack<char> s;
    auto result = string::npos;
    for(size_t i = 0; i < exp.size(); i++)
    {
        char ch = exp[i];
        if(ch == '(') s.push('(');
        else if(ch == ')') s.pop(); //解析方式不可靠，可以后期换成栈解析
        else if(s.empty()) //没有被括号内的运算符号
        {
            if(symbol.find(ch) != string::npos)
            {
                result = i;
            }
        }
        
    }
    return result;
    // return search_symbol(exp, symbol); //最多递归两次

}

NodePtr Calculator::build_tree(string& exp)
{
    auto pos = search_symbol(exp ,"+-");
    if(pos != string::npos)
    {
        string left_exp, right_exp;
        NodePtr root = split_exp(pos, exp, left_exp, right_exp);

        root->setLeft(build_tree(left_exp));
        root->setRight(build_tree(right_exp));
        return root;
    }
    
    pos = search_symbol(exp, "/*");
    if(pos != string::npos)
    {
        string left_exp, right_exp;
        NodePtr root = split_exp(pos, exp, left_exp, right_exp);

        root->setLeft(build_tree(left_exp));
        root->setRight(build_tree(right_exp));
        return root;
    }

    // trim(exp);
    if(exp.empty())
    {
        throw invalid_argument("warong expression");
    }
    if(exp[0] == '(')
    {
        if(exp[exp.size() -1 ] != ')')
        {
            throw invalid_argument("warong expression");
        }
        exp.erase(exp.size()-1, 1);
        exp.erase(0, 1);
    }
    if(exp.empty())
    {
        throw invalid_argument("warong expression");
    }

    pos = exp.find(".");
    if(pos != string::npos)
    {
        double value = atof(exp.c_str());
        RationalValue rv(static_cast<int>(value), value - static_cast<int>(value));
        return make_shared<Type::NumberNode>(rv);
    }
    else
    {
        int value = atoi(exp.c_str());
        RationalValue rv(value);
        return  make_shared<Type::NumberNode>(value);
    }
}