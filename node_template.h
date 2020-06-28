// #pragma once
// #include <memory>

// namespace Type{

// enum class NodeType{Number, Binary};
// enum class CalculateOp{Plus, Minus, Multi, Devide};

// template<class T>
// class Node
// {
// public:
//     typedef std::shared_ptr<Node<T>> NodePtr;
    
//     Node(NodePtr aleft, NodePtr aright)
//     :left(aleft), right(aright){};
//     virtual T calculate() = 0;

//     void setLeft(const NodePtr p)
//     {
//         this->left = p;
//     }

//     void setRight(const NodePtr p)
//     {
//         this->right = p;
//     }

// protected:
//     NodePtr left, right;
//     // NodeType nodeType;
// };

// template<class T>
// class NumberNode : public Node<T>
// {
// public:
//     NumberNode(int);
//     T calculate() override
//     {
//         return num;
//     }

// private:
//     int num;
// };


// template<class T>
// class BinaryNode : public Node<T>
// {
// public:
//     BinaryNode(NodePtr, NodePtr, CalculateOp);
//     BinaryNode(CalculateOp op);

//     int calculate() override;

// private:
//     CalculateOp op;
// };


// }
// // typedef std::shared_ptr<Type::Node> NodePtr;
