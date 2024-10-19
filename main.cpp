#include "lexer.hpp"
#include "parser.hpp"
#include "render.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename.typogen>" << std::endl;
        return 1;
    }

    // Read the TypoGen file
    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    // Tokenize the source code
    Lexer lexer(source);
    std::vector<Token> tokens = lexer.tokenize();
    std::cout << "tokens\n";
    for (Token i : tokens) {
        std::cout << "type: " << i.type << " value: " << i.value << "\n";
    }
    // Parse the tokens
    Parser parser(tokens);
    parser.parse();

    // Example: Render typography
    // renderTypography("Code is Life", "Arial", 42, 500, 700, "mockup.png");

    return 0;
}
