#pragma once
#include "expression.h"

class ImplicitMulExpression : public Expression
{
public:
    Expression* left;
    Expression* right;
    ImplicitMulExpression(Expression *left,Expression *right);
};


