#pragma once
#include "expression.h"

class Evaluator
{
	private:
        Expression *root;


	public:
        Evaluator(Expression *root);
		double evaluate();
        double evaluateExpression(Expression *node);
};

