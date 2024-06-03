#pragma once
enum SyntaxKind {
    NumberToken,
    WhitespaceToken,
    PlusToken,
    MinusToken,
    StarToken,
    SlashToken,
    OpenParenthesisToken,
    CloseParenthesisToken,
    BadToken,
    EndOfFileToken,
    NumberExpressionSyntax,
    BinaryExpressionSyntax,
    ParenthesizedExpressionSyntax,
    MinusParenthesizedExpressionSyntax,
    ImplicitMulExpressionSyntax,
    SyntaxTokenNode
};
