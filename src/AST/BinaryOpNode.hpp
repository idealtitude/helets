#pragma once

#include "ExprNode.hpp"

// Binary operation node (for arithmetic operations)
class BinaryOpNode : public ExprNode
{
  public:
    BinaryOpNode(OpType op, ExprNode* left, ExprNode* right)
        : op(op), left(left), right(right) {}

    ~BinaryOpNode()
    {
        delete left;
        delete right;
    }

    void print(int indent = 0) const override
    {
        printIndent(indent);
        std::cout << "BinaryOp: ";
        switch (op) {
            case OpType::ADD: std::cout << "+"; break;
            case OpType::SUB: std::cout << "-"; break;
            case OpType::MUL: std::cout << "*"; break;
            case OpType::DIV: std::cout << "/"; break;
            case OpType::EQ: std::cout << "=="; break;
            case OpType::NEQ: std::cout << "!="; break;
            case OpType::GT: std::cout << ">"; break;
            case OpType::GTE: std::cout << ">="; break;
            case OpType::LT: std::cout << "<"; break;
            case OpType::LTE: std::cout << "<="; break;
        }
        std::cout << std::endl;

        printIndent(indent);
        std::cout << "Left:" << std::endl;
        left->print(indent + 1);

        printIndent(indent);
        std::cout << "Right:" << std::endl;
        right->print(indent + 1);
    }

    DataType getType() const override
    {
        // For comparison operators, the result is always boolean
        switch (op) {
            case OpType::EQ:
            case OpType::NEQ:
            case OpType::GT:
            case OpType::GTE:
            case OpType::LT:
            case OpType::LTE:
                return DataType::BOOL;
            default:
                break;
        }

        // For arithmetic operators:
        DataType leftType = left->getType();
        DataType rightType = right->getType();

        // If either operand is a float, the result is a float
        if (leftType == DataType::FLOAT || rightType == DataType::FLOAT)
        {
            return DataType::FLOAT;
        }

        // Otherwise, inherit the type from the left operand
        return leftType;
    }

    OpType getOp() const
    {
        return op;
    }

    ExprNode* getLeft() const
    {
        return left;
    }

    ExprNode* getRight() const
    {
        return right;
    }

  private:
    OpType op;
    ExprNode* left;
    ExprNode* right;
};
