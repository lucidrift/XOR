#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer/lexer.h"

int main() {
    using namespace xorLang;
    using namespace std;

    stringstream cc;

    ifstream myFile_Handler;
    string myLine;

    // File Open in the Read Mode
    myFile_Handler.open("libstd/src/util/string.xor");

    if(myFile_Handler.is_open())
    {
        // Keep reading the file
        while(getline(myFile_Handler, myLine))
        {
            // print the line on the standard output
            cc << myLine << endl;
        }
        // File Close
        myFile_Handler.close();
    }
    else
    {
        cout << "Unable to open the file!";
    }

    xorLang::Lexer lexer(cc.str());

    while (lexer.hasNext()) {
        auto n = lexer.next();
        std::string error;

        if (n.has_value()) {
            if (n.value().type == TokenType::IDENTIFIER)
                std::cout << "\x1b[93m";
            else if (getTypeCat(n.value().type) == Type::KEYWORD)
                std::cout << "\x1b[91m";
            else if (n.value().type == TokenType::BACK_TICK || n.value().type == TokenType::STRING || n.value().type == TokenType::CHAR_LIT)
                std::cout << "\x1b[32m";
            else if (getTypeCat(n.value().type) == Type::SYMBOL)
                std::cout << "\x1b[90m";

            std::cout << n.value().value << "\x1b[0m";
        } else {
            error = "\nUnknown token found:\n"
                         " -- Line & Column: " + std::to_string(lexer.getLine()) + " - " + std::to_string(lexer.getColumn()) + "\n";
            std::cerr << error;
        }
    }

    std::cout << "\nFinished lexing\n";
    return 0;
}
