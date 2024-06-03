#pragma once
#include "syntaxKind.h"
#include <string>

using std::string;

class SyntaxToken {
    public:
        SyntaxKind kind;
        double value;
        string text;
        int position;
        SyntaxToken();
        SyntaxToken(SyntaxKind kind, int position, string text, double value);
};

