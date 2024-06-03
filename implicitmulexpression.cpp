#include "implicitmulexpression.h"

ImplicitMulExpression::ImplicitMulExpression(Expression *left, Expression *right)
{
    this->left = left;
    this->right = right;
    this->kind = ImplicitMulExpressionSyntax;
}
