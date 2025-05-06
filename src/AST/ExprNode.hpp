#pragma once

#include "ASTNode.hpp"
#include "Types.hpp"

// Expression node (base class for all expressions)
class ExprNode : public ASTNode
{
  public:
    virtual DataType getType() const = 0;
};
