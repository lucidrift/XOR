//#include "lexer/lexer.h"
#include <iostream>
#include "lexer/lexer.h"

int main() {
    xorLang::Lexer lexer("fn main() -> i8 {}");

    while (lexer.hasNext()) {
        auto n = lexer.next();

        if (n.has_value()) {
            std::cout << n.value().value << std::endl;
        } else {
            std::cout << "Unknown token found:\n"
                         " -- Line & Column: " << lexer.getLine() << " - " << lexer.getColumn() << "\n";
            return 1;
        }
    }

    std::cout << "\nFinished lexxing\n";
    return 0;
}
