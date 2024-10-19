#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"
#include <string>
#include <vector>

// Parser class declaration
class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    void parse();

private:
    std::vector<Token> tokens;
    size_t position;

    void parseCanvas();
    void parseTypography();
    void parsePreview();
    void parseExport();

    Token currentToken();
};

#endif // PARSER_HPP
