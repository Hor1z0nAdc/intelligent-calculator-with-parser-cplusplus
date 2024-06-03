#include "numberExpression.h"

NumberExpression::NumberExpression(SyntaxToken* numberToken) {
    this->numberToken = numberToken;
    this->kind = NumberExpressionSyntax;
}
