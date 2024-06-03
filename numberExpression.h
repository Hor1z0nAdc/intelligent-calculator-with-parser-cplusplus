#pragma once
#include "expression.h"
#include "syntaxToken.h"

class NumberExpression : public Expression
{
    public:
    SyntaxToken* numberToken;
    NumberExpression(SyntaxToken* numberToken);
};

