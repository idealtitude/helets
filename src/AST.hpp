#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <memory>

// Data types supported by Helets
enum class DataType {
    INT,
    FLOAT,
    BOOL,
    STRING
};

// Operator types for binary operations
enum class OpType {
    ADD,
    SUB,
    MUL,
    DIV
};

// Forward declarations
class ExprNode;
class StmtNode;

// Base node for the AST
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print(int indent = 0) const = 0;

protected:
    void printIndent(int indent) const {
        for (int i = 0; i < indent; ++i) {
            std::cout << "  ";
        }
    }
};

// Expression node (base class for all expressions)
class ExprNode : public ASTNode {
public:
    virtual DataType getType() const = 0;
};

// Integer literal node
class IntLiteralNode : public ExprNode {
public:
    IntLiteralNode(int value) : value(value) {}

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "IntLiteral: " << value << std::endl;
    }

    DataType getType() const override {
        return DataType::INT;
    }

    int getValue() const {
        return value;
    }

private:
    int value;
};

// Float literal node
class FloatLiteralNode : public ExprNode {
public:
    FloatLiteralNode(float value) : value(value) {}

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "FloatLiteral: " << value << std::endl;
    }

    DataType getType() const override {
        return DataType::FLOAT;
    }

    float getValue() const {
        return value;
    }

private:
    float value;
};

// Boolean literal node
class BoolLiteralNode : public ExprNode {
public:
    BoolLiteralNode(bool value) : value(value) {}

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "BoolLiteral: " << (value ? "true" : "false") << std::endl;
    }

    DataType getType() const override {
        return DataType::BOOL;
    }

    bool getValue() const {
        return value;
    }

private:
    bool value;
};

// String literal node
class StringLiteralNode : public ExprNode {
public:
    StringLiteralNode(const char* value) : value(value) {}
    ~StringLiteralNode() {
        free(const_cast<char*>(value));
    }

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "StringLiteral: " << value << std::endl;
    }

    DataType getType() const override {
        return DataType::STRING;
    }

    const char* getValue() const {
        return value;
    }

private:
    const char* value;
};

// Binary operation node (for arithmetic operations)
class BinaryOpNode : public ExprNode {
public:
    BinaryOpNode(OpType op, ExprNode* left, ExprNode* right)
        : op(op), left(left), right(right) {}
    
    ~BinaryOpNode() {
        delete left;
        delete right;
    }

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "BinaryOp: ";
        switch (op) {
            case OpType::ADD: std::cout << "+"; break;
            case OpType::SUB: std::cout << "-"; break;
            case OpType::MUL: std::cout << "*"; break;
            case OpType::DIV: std::cout << "/"; break;
        }
        std::cout << std::endl;
        
        printIndent(indent);
        std::cout << "Left:" << std::endl;
        left->print(indent + 1);
        
        printIndent(indent);
        std::cout << "Right:" << std::endl;
        right->print(indent + 1);
    }

    DataType getType() const override {
        // For now, simple type determination
        // In a more advanced implementation, we'd check both operands
        DataType leftType = left->getType();
        DataType rightType = right->getType();
        
        // If either operand is a float, the result is a float
        if (leftType == DataType::FLOAT || rightType == DataType::FLOAT) {
            return DataType::FLOAT;
        }
        
        // Otherwise, inherit the type from the left operand
        return leftType;
    }

    OpType getOp() const {
        return op;
    }

    ExprNode* getLeft() const {
        return left;
    }

    ExprNode* getRight() const {
        return right;
    }

private:
    OpType op;
    ExprNode* left;
    ExprNode* right;
};

// Statement node (base class for all statements)
class StmtNode : public ASTNode {
};

// Variable declaration node
class VarDeclNode : public StmtNode {
public:
    VarDeclNode(DataType type, const char* name, ExprNode* value)
        : type(type), name(name), value(value) {}

    ~VarDeclNode() {
        free(const_cast<char*>(name));
        delete value;
    }

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "VarDecl: " << name << " of type ";
        
        switch (type) {
            case DataType::INT: std::cout << "int"; break;
            case DataType::FLOAT: std::cout << "float"; break;
            case DataType::BOOL: std::cout << "bool"; break;
            case DataType::STRING: std::cout << "str"; break;
        }
        
        std::cout << std::endl;
        if (value) {
            printIndent(indent);
            std::cout << "Value:" << std::endl;
            value->print(indent + 1);
        }
    }

    DataType getType() const {
        return type;
    }

    const char* getName() const {
        return name;
    }

    ExprNode* getValue() const {
        return value;
    }

private:
    DataType type;
    const char* name;
    ExprNode* value;
};

// Program node (root of the AST)
class ProgramNode : public ASTNode {
public:
    ~ProgramNode() {
        for (auto stmt : statements) {
            delete stmt;
        }
    }

    void addStatement(StmtNode* stmt) {
        if (stmt) {
            statements.push_back(stmt);
        }
    }

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "Program:" << std::endl;
        for (const auto& stmt : statements) {
            if (stmt) {
                stmt->print(indent + 1);
            }
        }
    }

    const std::vector<StmtNode*>& getStatements() const {
        return statements;
    }

private:
    std::vector<StmtNode*> statements;
};
