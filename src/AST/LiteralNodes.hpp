#pragma once

#include <string>
#include <cstdlib>
#include "ExprNode.hpp"

// Integer literal node
class IntLiteralNode : public ExprNode
{
  public:
    IntLiteralNode(int value) : value(value) {}

    void print(int indent = 0) const override
    {
        printIndent(indent);
        std::cout << "IntLiteral: " << value << std::endl;
    }

    DataType getType() const override
    {
        return DataType::INT;
    }

    int getValue() const
    {
        return value;
    }

  private:
    int value;
};

// Float literal node
class FloatLiteralNode : public ExprNode
{
  public:
    FloatLiteralNode(float value) : value(value) {}

    void print(int indent = 0) const override
    {
        printIndent(indent);
        std::cout << "FloatLiteral: " << value << std::endl;
    }

    DataType getType() const override
    {
        return DataType::FLOAT;
    }

    float getValue() const
    {
        return value;
    }

  private:
    float value;
};

// Boolean literal node
class BoolLiteralNode : public ExprNode
{
  public:
    BoolLiteralNode(bool value) : value(value) {}

    void print(int indent = 0) const override
    {
        printIndent(indent);
        std::cout << "BoolLiteral: " << (value ? "true" : "false") << std::endl;
    }

    DataType getType() const override
    {
        return DataType::BOOL;
    }

    bool getValue() const
    {
        return value;
    }

  private:
    bool value;
};

// String literal node
class StringLiteralNode : public ExprNode
{
  public:
    StringLiteralNode(const char* value) : value(value) {}
    ~StringLiteralNode()
    {
        free(const_cast<char*>(value));
    }

    void print(int indent = 0) const override
    {
        printIndent(indent);
        std::cout << "StringLiteral: " << value << std::endl;
    }

    DataType getType() const override
    {
        return DataType::STRING;
    }

    const char* getValue() const
    {
        return value;
    }

  private:
    const char* value;
};
