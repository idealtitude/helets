#pragma once

#include <vector>
#include "ASTNode.hpp"
#include "StmtNode.hpp"

// Program node (root of the AST)
class ProgramNode : public ASTNode
{
  public:
    ~ProgramNode()
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
        std::cout << "Program:" << std::endl;
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
