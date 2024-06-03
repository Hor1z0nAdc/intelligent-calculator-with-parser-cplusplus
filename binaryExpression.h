#pragma once
#include "expression.h"
#include "syntaxToken.h"

class BinaryExpression : public Expression
{
    public:
    Expression* left;
    SyntaxToken* operatorToken;
    Expression* right;
    BinaryExpression(Expression* left, SyntaxToken* operatorToken, Expression* right);
};

