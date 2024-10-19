#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>

// Define Token types
enum TokenType {
    TOKEN_CANVAS,
    TOKEN_TYPOGRAPHY,
    TOKEN_PREVIEW,
    TOKEN_EXPORT,
    TOKEN_WIDTH,
    TOKEN_HEIGHT,
    TOKEN_COLOR,
    TOKEN_FONT_FAMILY,
    TOKEN_FONT_SIZE,
    TOKEN_FONT_COLOR,
    TOKEN_ALIGNMENT,
    TOKEN_EFFECT,
    TOKEN_POSITION,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_EOF
};

// Token structure
struct Token {
    TokenType type;
    std::string value;
};

// Lexer class declaration
class Lexer {
public:
    Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    std::string source;
    size_t position;

    Token consumeIdentifier();
    Token consumeNumber();
    Token consumeString();
    Token consumeSymbol();
};

#endif // LEXER_HPP
