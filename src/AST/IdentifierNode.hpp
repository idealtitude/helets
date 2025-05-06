#pragma once

#include <cstdlib>
#include "ExprNode.hpp"

// Identifier node (for variable references)
class IdentifierNode : public ExprNode
{
  public:
    IdentifierNode(const char* name) : name(name) {}
    ~IdentifierNode()
    {
        free(const_cast<char*>(name));
    }

    void print(int indent = 0) const override
    {
        printIndent(indent);
        std::cout << "Identifier: " << name << std::endl;
    }

    DataType getType() const override
    {
        // In a real implementation, we would look up the identifier's type
        // For now, default to INT
        return DataType::INT;
    }

    const char* getName() const
    {
        return name;
    }

  private:
    const char* name;
};
