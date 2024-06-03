#pragma once
#include "expression.h"
#include "syntaxToken.h"

class ParenthesizedExpression : public Expression
{
	public:
	SyntaxToken* openParenthesisToken;
	Expression* expr;
	SyntaxToken* closeParenthesisToken;
	ParenthesizedExpression(SyntaxToken* openParenthesisToken, 
							Expression* expr, 
							SyntaxToken* closeParenthesisToken);
};

