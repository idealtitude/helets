#pragma once

#include <vector>
#include "StmtNode.hpp"

// Block statement node (for grouped statements)
class BlockStmtNode : public StmtNode
{
  public:
    ~BlockStmtNode()
    {
        for (auto stmt : statements)
        {
            delete stmt;
        }
    }

    void addStatement(StmtNode* stmt)
    {
        if (stmt)
        {
            statements.push_back(stmt);
        }
    }

    void print(int indent = 0) const override
    {
        printIndent(indent);
        std::cout << "Block:" << std::endl;
        for (const auto& stmt : statements)
        {
            if (stmt) {
                stmt->print(indent + 1);
            }
        }
    }

    const std::vector<StmtNode*>& getStatements() const
    {
        return statements;
    }

  private:
    std::vector<StmtNode*> statements;
};
