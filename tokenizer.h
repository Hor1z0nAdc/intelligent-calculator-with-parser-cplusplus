#pragma once
#include "syntaxToken.h"
#include <string>

using std::string;

class Tokenizer
{
    private:
        int position;
        string text;
        char getCurrent();
        char peek(int i);

    public:
        string *lError;
        Tokenizer(string &text, string *error);
        SyntaxToken* nextToken();
};

