#pragma once
#include "rational.h"
#include <memory>

namespace Type{

enum class NodeType{Number, Binary};
enum class CalculateOp{Plus, Minus, Multi, Devide};


class Node
{
public:
    typedef std::shared_ptr<Node> NodePtr;
    
    Node(NodePtr aleft, NodePtr aright)
    :left(aleft), right(aright){};
    virtual RationalValue calculate() = 0;

    void setLeft(const NodePtr p)
    {
        this->left = p;
    }

    void setRight(const NodePtr p)
    {
        this->right = p;
    }

protected:
    NodePtr left, right;
    // NodeType nodeType;
};

class NumberNode : public Node
{
public:
    NumberNode(const RationalValue& r);
    RationalValue calculate() override
    {
       return rational;
    }

private:
    RationalValue rational;
};

class BinaryNode : public Node
{
public:
    BinaryNode(NodePtr, NodePtr, CalculateOp);
    BinaryNode(CalculateOp op);

    RationalValue calculate() override;

private:
    CalculateOp op;
};


}
// typedef std::shared_ptr<Type::Node> NodePtr;
