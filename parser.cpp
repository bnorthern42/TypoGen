#include "parser.hpp"
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens)
    , position(0)
{
}

void Parser::parse()
{
    while (tokens[position].type != TOKEN_EOF) {
        if (tokens[position].type == TOKEN_CANVAS) {
            parseCanvas();
        } else if (tokens[position].type == TOKEN_TYPOGRAPHY) {
            parseTypography();
        } else if (tokens[position].type == TOKEN_PREVIEW) {
            parsePreview();
        } else if (tokens[position].type == TOKEN_EXPORT) {
            parseExport();
        } else {
            position++;
        }
    }
}

void Parser::parseCanvas()
{
    position++; // Consume 'canvas'
    std::string productName = tokens[position].value;
    position += 2; // Consume '{'
    std::cout << "Canvas for " << productName << "\n";

    while (tokens[position].type != TOKEN_IDENTIFIER || tokens[position].value != "}") {
        std::cout << "tt: " << tokens[position].value << "\n";
        if (tokens[position].type == TOKEN_WIDTH) {
            std::cout << "Width: " << tokens[position + 2].value << "px\n";
        } else if (tokens[position].type == TOKEN_HEIGHT) {
            std::cout << "Height: " << tokens[position + 2].value << "px\n";
        }
        position += 4; // Skip to next property
    }
    position++; // Consume '}'
}

void Parser::parseTypography()
{
    position++; // Consume 'typography'
    std::string text = tokens[position].value;
    position += 2; // Consume '{'
    std::cout << "Typography: " << text << "\n";

    while (tokens[position].type != TOKEN_IDENTIFIER || tokens[position].value != "}") {
        position += 4; // Skip to next property
    }
    position++; // Consume '}'
}

void Parser::parsePreview()
{
    position++; // Consume 'preview'
    std::string productName = tokens[position + 2].value;
    std::cout << "Previewing on: " << productName << "\n";
    position += 4;
}

void Parser::parseExport()
{
    position++; // Consume 'export'
    std::string filename = tokens[position + 2].value;
    std::cout << "Exporting to: " << filename << "\n";
    position += 4;
}

Token Parser::currentToken()
{
    return tokens[position];
}
