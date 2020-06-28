#include "Node.h"
#include <stdexcept>

using namespace Type;
using namespace std;

NumberNode::NumberNode(const RationalValue& r) 
    : rational(r), Node(nullptr, nullptr){ }

BinaryNode::BinaryNode(NodePtr aleft, NodePtr aright, CalculateOp op)
:Node(aleft, aright), op(op)
{}

BinaryNode::BinaryNode(CalculateOp op)
:Node(nullptr, nullptr), op(op)
{}

//可以使用 functional 来做
static RationalValue real_calculate(const RationalValue& a, const RationalValue& b, CalculateOp op)
{
    switch (op)
    {
    case CalculateOp::Plus:
        return a + b;
        break;
    case CalculateOp::Minus:
        return a - b;
    case CalculateOp::Multi:
        return a*b;
    case CalculateOp::Devide:
        return a / b;
    default:
        throw invalid_argument("wrong operator");
        break;
    }
}

RationalValue BinaryNode::calculate()
{
    RationalValue a = left->calculate();
    RationalValue b = right->calculate();
    return real_calculate(a, b, this->op);
}



