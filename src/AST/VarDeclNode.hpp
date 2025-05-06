#pragma once

#include <cstdlib>
#include "StmtNode.hpp"
#include "ExprNode.hpp"

// Variable declaration node
class VarDeclNode : public StmtNode
{
  public:
    VarDeclNode(DataType type, const char* name, ExprNode* value)
        : type(type), name(name), value(value) {}

    ~VarDeclNode()
    {
        free(const_cast<char*>(name));
        delete value;
    }

    void print(int indent = 0) const override
    {
        printIndent(indent);
        std::cout << "VarDecl: " << name << " of type ";

        switch (type)
        {
            case DataType::INT: std::cout << "int"; break;
            case DataType::FLOAT: std::cout << "float"; break;
            case DataType::BOOL: std::cout << "bool"; break;
            case DataType::STRING: std::cout << "str"; break;
        }

        std::cout << std::endl;
        if (value)
        {
            printIndent(indent);
            std::cout << "Value:" << std::endl;
            value->print(indent + 1);
        }
    }

    DataType getType() const
    {
        return type;
    }

    const char* getName() const
    {
        return name;
    }

    ExprNode* getValue() const
    {
        return value;
    }

  private:
    DataType type;
    const char* name;
    ExprNode* value;
};
