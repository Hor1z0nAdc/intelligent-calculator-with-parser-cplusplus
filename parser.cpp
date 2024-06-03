#include "parser.h"
#include "tokenizer.h"
#include "binaryExpression.h"
#include "numberExpression.h"
#include "parenthesizedExpression.h"
#include "minusparexpression.h"
#include "implicitmulexpression.h"

//constructor automatically performs tokenization with the tokenizer
Parser::Parser(string &text, string *error) {
    SyntaxToken* token;
    pError = error;
    position = 0;
    Tokenizer* tokenizer = new Tokenizer(text, pError);

    //tokenise the given mathematical expression
    do {
        token = tokenizer->nextToken();

        if (token->kind != WhitespaceToken &&
            token->kind != BadToken)
        {
            tokens.push_back(token);
        }
    } while (token->kind != EndOfFileToken);
}

//expression is translated first into term, then into factor and primary expression
//ensures the sequence of operations
Expression* Parser::parse() {
    Expression* expr = parseTerm();
    return expr;
}

//helper function for parsing, handles the expression in bracketss
Expression* Parser::parseExpression() {
    return parseTerm();
}

//handles the grammar of plus, minus operations
Expression* Parser::parseTerm() {
    Expression* left = parseFactor();

    while (current()->kind == PlusToken || current()->kind == MinusToken) {
        SyntaxToken* operatorToken = nextToken();
        Expression* right = parseFactor();
        BinaryExpression *expr = new BinaryExpression(left, operatorToken, right);
        left = expr;
    }

    return left;
}

//handles the grammar of multiplication
Expression* Parser::parseFactor() {
    Expression* left = parsePrimaryExpression();
    bool isParenthesized = left->kind == ParenthesizedExpressionSyntax || left->kind == MinusParenthesizedExpressionSyntax;

    //if a bracketed expression is multiplied (implicitly) by a number
    if(isParenthesized && current()->kind == NumberToken) {
        Expression *right = parsePrimaryExpression();
        ImplicitMulExpression *expr = new ImplicitMulExpression(left,right);
        left = expr;
    }

    //if a bracketed expression is multiplied (implicitly) by a bracketed expression
    else if(isParenthesized && current()->kind == OpenParenthesisToken) {
         Expression *right = parseExpression();
         ImplicitMulExpression *expr = new ImplicitMulExpression(left,right);
         left = expr;
    }

    //when multiplying a number (implicitly) by a bracketed expression
    else if(current()->kind == OpenParenthesisToken) {
        Expression *right = parseExpression();
        ImplicitMulExpression *expr = new ImplicitMulExpression(left,right);
        left = expr;
    }

    //normal multiplication
    while (current()->kind == StarToken || current()->kind == SlashToken) {
        SyntaxToken* operatorToken = nextToken();
        Expression* right = parsePrimaryExpression();
        BinaryExpression *expr = new BinaryExpression(left, operatorToken, right);
        left = expr;
    }

    return left;
}

//handles the grammar of numbers and brackets
Expression* Parser::parsePrimaryExpression() {
    Expression* forReturnExpr;

    //for a prefixed bracketed term
    if(current()->kind == MinusToken) {
         SyntaxToken* left = indexedToken(position+1);
         Expression* expr = parseExpression();
         SyntaxToken* right = match(CloseParenthesisToken);

         MinusParExpression *pExpr = new MinusParExpression(left, expr, right);
         forReturnExpr = pExpr;

         return forReturnExpr;
    }

    //in the case of an opening parenthesis, we save, parse the inner expression and then save the corresponding parenthesis
    if (current()->kind == OpenParenthesisToken) {
        SyntaxToken* left = nextToken();
        Expression* expr = parseExpression();
        SyntaxToken* right = match(CloseParenthesisToken);

        ParenthesizedExpression *pExpr = new ParenthesizedExpression(left, expr, right);
        forReturnExpr = pExpr;

        return forReturnExpr;
    }

    //if the current expression is not a bracket but is valid, then at this point we are dealing with a number
    SyntaxToken* numberToken = match(NumberToken);
    NumberExpression *numExpr = new NumberExpression(numberToken);
    forReturnExpr = numExpr;
    return forReturnExpr;
}

//private helper methods
SyntaxToken* Parser::nextToken()
{
    SyntaxToken* current = tokens[position];
    position++;
    return current;
}

SyntaxToken* Parser::indexedToken(int index)
{
    SyntaxToken* current = tokens[index];
    position = index+1;
    return current;
}

SyntaxToken* Parser::current() {
    return tokens[position];
}

//checks if the expected type of token is involved, if not, the error will be overwritten for later outputing
SyntaxToken* Parser::match(SyntaxKind kind) {
    if (current()->kind == kind) {
        return nextToken();
    }

    *pError = "Syntax hiba: nem várt karakter";
    return new SyntaxToken(kind, current()->position, "null", -0.00000000000000);
}
