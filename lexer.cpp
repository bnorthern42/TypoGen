
#include "lexer.hpp"
#include <cctype>

Lexer::Lexer(const std::string& source)
    : source(source)
    , position(0)
{
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;
    while (position < source.length()) {
        char current = source[position];
        if (isspace(current)) {
            position++;
            continue;
        }
        if (isalpha(current)) {
            tokens.push_back(consumeIdentifier());
        } else if (isdigit(current)) {
            tokens.push_back(consumeNumber());
        } else if (current == '"') {
            tokens.push_back(consumeString());
        } else {
            tokens.push_back(consumeSymbol());
        }
    }
    tokens.push_back({ TOKEN_EOF, "" });
    return tokens;
}

Token Lexer::consumeIdentifier()
{
    size_t start = position;
    while (isalpha(source[position]))
        position++;
    std::string value = source.substr(start, position - start);
    if (value == "canvas")
        return { TOKEN_CANVAS, value };
    if (value == "typography")
        return { TOKEN_TYPOGRAPHY, value };
    if (value == "preview")
        return { TOKEN_PREVIEW, value };
    if (value == "export")
        return { TOKEN_EXPORT, value };
    return { TOKEN_IDENTIFIER, value };
}

Token Lexer::consumeNumber()
{
    size_t start = position;
    while (isdigit(source[position]))
        position++;
    return { TOKEN_NUMBER, source.substr(start, position - start) };
}

Token Lexer::consumeString()
{
    position++; // Skip opening quote
    size_t start = position;
    while (source[position] != '"')
        position++;
    std::string value = source.substr(start, position - start);
    position++; // Skip closing quote
    return { TOKEN_STRING, value };
}

Token Lexer::consumeSymbol()
{
    char current = source[position++];
    switch (current) {
    case ':':
        return { TOKEN_IDENTIFIER, ":" };
    case ';':
        return { TOKEN_IDENTIFIER, ";" };
    case '{':
        return { TOKEN_IDENTIFIER, "{" };
    case '}':
        return { TOKEN_IDENTIFIER, "}" };
    case '(':
        return { TOKEN_IDENTIFIER, "(" };
    case ')':
        return { TOKEN_IDENTIFIER, ")" };
    case ',':
        return { TOKEN_IDENTIFIER, "," };
    default:
        return { TOKEN_IDENTIFIER, std::string(1, current) };
    }
}
