#pragma once

#include "StmtNode.hpp"
#include "ExprNode.hpp"

// If statement node
class IfStmtNode : public StmtNode
{
  public:
    IfStmtNode(ExprNode* condition, StmtNode* thenBranch, StmtNode* elseBranch)
        : condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}

    ~IfStmtNode()
    {
        delete condition;
        delete thenBranch;
        delete elseBranch;
    }

    void print(int indent = 0) const override
    {
        printIndent(indent);
        std::cout << "IfStmt:" << std::endl;
        
        printIndent(indent);
        std::cout << "Condition:" << std::endl;
        condition->print(indent + 1);
        
        printIndent(indent);
        std::cout << "Then:" << std::endl;
        if (thenBranch) {
            thenBranch->print(indent + 1);
        } else {
            printIndent(indent + 1);
            std::cout << "<empty>" << std::endl;
        }
        
        if (elseBranch) {
            printIndent(indent);
            std::cout << "Else:" << std::endl;
            elseBranch->print(indent + 1);
        }
    }

    ExprNode* getCondition() const
    {
        return condition;
    }

    StmtNode* getThenBranch() const
    {
        return thenBranch;
    }

    StmtNode* getElseBranch() const
    {
        return elseBranch;
    }

  private:
    ExprNode* condition;
    StmtNode* thenBranch;
    StmtNode* elseBranch;
};
