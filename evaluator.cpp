#include "evaluator.h"
#include "numberExpression.h"
#include "binaryExpression.h"
#include "implicitmulexpression.h"
#include "parenthesizedExpression.h"
#include <iostream>

Evaluator::Evaluator(Expression* root) {
    this->root = root;
}

double Evaluator::evaluate() {
    return evaluateExpression(root);
}

double Evaluator::evaluateExpression(Expression* node) {

    //in case of number syntax returns the value of the number
    if (node->kind == NumberExpressionSyntax) {
        double value = static_cast<NumberExpression*>(node)->numberToken->value;
        return value;
    }

    //specifies the left and right operands and the operator for a simple expression
    //returns the calculated result of the expression
    if (node->kind == BinaryExpressionSyntax) {
        double leftValue = evaluateExpression(static_cast<BinaryExpression*>(node)->left);
        double rightValue = evaluateExpression(static_cast<BinaryExpression*>(node)->right);

        SyntaxKind operatorKind = static_cast<BinaryExpression*>(node)->operatorToken->kind;

        if (operatorKind == PlusToken) {
            return leftValue + rightValue;
        }
        else if (operatorKind == MinusToken) {
            return leftValue - rightValue;
        }
        else if (operatorKind == StarToken) {
            return leftValue * rightValue;
        }
        else if (operatorKind == SlashToken) {
            return leftValue / rightValue;
        }
        std::cout << "error at evaluation";
        return -666;
  
    }

    //implicit multiplication, despite the absence of the mul operator, multiplies the left and right operands
    if (node->kind == ImplicitMulExpressionSyntax) {
        double leftValue = evaluateExpression(static_cast<ImplicitMulExpression*>(node)->left);
        double rightValue = evaluateExpression(static_cast<ImplicitMulExpression*>(node)->right);
        return  leftValue * rightValue;
    }

    if (node->kind == ParenthesizedExpressionSyntax) {
        return evaluateExpression(static_cast<ParenthesizedExpression*>(node)->expr);
    }

    if (node->kind == MinusParenthesizedExpressionSyntax) {
        double value =  evaluateExpression(static_cast<ParenthesizedExpression*>(node)->expr);
        return -value;
    }

    return -666;
}
