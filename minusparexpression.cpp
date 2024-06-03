#include "minusparexpression.h"

MinusParExpression::MinusParExpression(SyntaxToken* openParenthesisToken,
                                       Expression* expr,
                                       SyntaxToken* closeParenthesisToken)
{
    this->openParenthesisToken = openParenthesisToken;
    this->expr = expr;
    this->closeParenthesisToken = closeParenthesisToken;
    this->kind = MinusParenthesizedExpressionSyntax;
}
