#pragma once
#include "Node.h"
#include "rational.h"

#include <memory>
#include <cstddef>
#include <chrono>

typedef std::shared_ptr<Type::Node> NodePtr;

class Calculator
{
public:
    static void erase_brackets(std::string& exp);
    static void pre_process(std::string& str);
    static NodePtr build_tree(std::string& exp);
    static void trim(std::string& str);

private:
};