#include "tokenizer.h"

Tokenizer::Tokenizer(string &text, string *error) {
    position = 0;
    lError = error;
    this->text = text;
}

char Tokenizer::getCurrent() {
    if (position >= text.size()) {
        return '\0';
    }
    return text[position];
}

char Tokenizer::peek(int i) {
    if (i >= text.size()) {
        return 'n';
    }
    return text[i];
}

SyntaxToken* Tokenizer::nextToken() {

    //if we have processed all characters of the expression it will generate the end of file token, otherwise we go for the next
    if (position >= this->text.size()) {
        return new SyntaxToken(EndOfFileToken, position, "\0", NULL);
    }
    char current = getCurrent();

    //for a number (even a signed number), we add the character to the token until we find another number or dot(.)
    bool isSign = current == '+' || current == '-';
    bool isComplexSigned = isdigit(peek(position+1)) && !isdigit(peek(position-1)) && peek(position-1) != ')';
    bool isSignedNum = isSign && isComplexSigned;

    if (isdigit(current) || isSignedNum)
    {
        int start = position;
        position++;

        while (isdigit(getCurrent()) || getCurrent() == '.') {
                    position++;
        }

        int length = position - start;
        string subString = text.substr(start, length);
        double value = stod(subString);
        return new SyntaxToken(NumberToken, start, subString, value);
    }

    //for space characters, characters are added to the token as long as the space string lasts
    if (isspace(current))
    {
        int start = position;
        position++;
        while (isspace(getCurrent())) {
            position++;
        }

        int length = position - start;
        string subString = text.substr(start, length);
        return new SyntaxToken(WhitespaceToken, start, subString, NULL);
    }

    //if the current character is a mathematical operator, a token is created from it
    //at this point, if the current character is not a mat. operator, then the character is incorrect
    if (current == '+') {
        return new SyntaxToken(PlusToken, position++, "+", NULL);
    }
    else if (current == '-') {
        return new SyntaxToken(MinusToken, position++, "-", NULL);
    }
    else if (current == '*') {
        return new SyntaxToken(StarToken, position++, "*", NULL);
    }
    else if (current == '/') {
        return new SyntaxToken(SlashToken, position++, "/", NULL);
    }
    else if (current == '(') {
        return new SyntaxToken(OpenParenthesisToken, position++, "(", NULL);
    }
    else if (current == ')') {
        return new SyntaxToken(CloseParenthesisToken, position++, ")", NULL);
    }

    //before returning the bad token overwrite the error for later write out
   *lError = "Syntax hiba: helytelen karakter";
    return new SyntaxToken(BadToken, position++, text.substr(position - 1, 1), NULL);
}
