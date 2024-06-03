#include "binaryExpression.h"

BinaryExpression::BinaryExpression(Expression* left, SyntaxToken* operatorToken, Expression* right) {
    this->left = left;
    this->operatorToken = operatorToken;
    this->right = right;
    this->kind = BinaryExpressionSyntax;
}
