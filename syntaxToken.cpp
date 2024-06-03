#include "syntaxToken.h"

SyntaxToken::SyntaxToken() {

}

SyntaxToken::SyntaxToken(SyntaxKind kind, int position, string text, double value) {
    this->kind = kind;
    this->position = position;
    this->text = text;
    this->value = value;
}
