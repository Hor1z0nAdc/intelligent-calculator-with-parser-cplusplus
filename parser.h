#pragma once
#include "syntaxToken.h"
#include "expression.h"
#include "syntaxKind.h"
#include <vector>
#include <QString>

using std::vector;
using std::string;

class Parser
{
    private:
        int position;
        SyntaxToken* indexedToken(int index);
        SyntaxToken* nextToken();
        SyntaxToken* current();
        SyntaxToken* match(SyntaxKind kind);
    public:
        string *pError;
        vector<SyntaxToken*> tokens;

        Parser(string &text, string *error);
        Expression* parseExpression();
        Expression* parseTerm();
        Expression* parseFactor();
        Expression* parsePrimaryExpression();
        Expression* parse();
};

