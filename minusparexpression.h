#pragma once
#include "expression.h"
#include "syntaxToken.h"

class MinusParExpression : public Expression
{
public:
SyntaxToken* openParenthesisToken;
Expression* expr;
SyntaxToken* closeParenthesisToken;
MinusParExpression(SyntaxToken* openParenthesisToken,
                        Expression* expr,
                        SyntaxToken* closeParenthesisToken);
};
