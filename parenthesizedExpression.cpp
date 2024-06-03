#include "parenthesizedExpression.h"

ParenthesizedExpression::ParenthesizedExpression(SyntaxToken* openParenthesisToken,
											     Expression* expr,
												 SyntaxToken* closeParenthesisToken) 
{
	this->openParenthesisToken = openParenthesisToken;
	this->expr = expr;
	this->closeParenthesisToken = closeParenthesisToken;
	this->kind = ParenthesizedExpressionSyntax;
}
