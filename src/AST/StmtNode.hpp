#pragma once

#include "ASTNode.hpp"

// Statement node (base class for all statements)
class StmtNode : public ASTNode {
  public:
    virtual ~StmtNode() = default;
};
