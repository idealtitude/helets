#pragma once

// Data types supported by Helets
enum class DataType
{
    INT,
    FLOAT,
    BOOL,
    STRING
};

// Operator types for binary operations
enum class OpType
{
    ADD,
    SUB,
    MUL,
    DIV,
    EQ,  // ==
    NEQ, // !=
    GT,  // >
    GTE, // >=
    LT,  // <
    LTE  // <=
};
