//#include "lexer/lexer.h"
#include <iostream>
#include "lexer/lexer.h"

int main() {
    using namespace xorLang;
    xorLang::Lexer lexer("fn main() -> i8 {\n\tret main();\n}");

    while (lexer.hasNext()) {
        auto n = lexer.next();

        if (n.has_value()) {
            if (n.value().type == TokenType::IDENTIFIER)
                std::cout << "\x1b[33m";
            else if (getTypeCat(n.value().type) == Type::KEYWORD)
                std::cout << "\x1b[31m";

            std::cout << n.value().value << "\x1b[0m";
        } else {
            std::cout << "Unknown token found:\n"
                         " -- Line & Column: " << lexer.getLine() << " - " << lexer.getColumn() << "\n";
            return 1;
        }
    }

    std::cout << "\nFinished lexing\n";
    return 0;
}
