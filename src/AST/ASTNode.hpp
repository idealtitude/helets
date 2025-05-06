#pragma once

#include <iostream>

// Base node for the AST
class ASTNode
{
  public:
    virtual ~ASTNode() = default;
    virtual void print(int indent = 0) const = 0;

  protected:
    void printIndent(int indent) const
    {
        for (int i = 0; i < indent; ++i) {
            std::cout << "  ";
        }
    }
};
