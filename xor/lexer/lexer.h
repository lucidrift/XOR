#pragma once

#include <string>
#include <utility>
#include <optional>

namespace xorLang {
    enum class TokenType {
        // File
        NEWLINE, SPACE, TAB, EOI, COMMENT,

        // Symbols [D_ = Double, T_ = Triple]
        D_L_PAREN, L_PAREN, D_R_PAREN, R_PAREN, D_L_BRACE, L_BRACE, D_R_BRACE,
        R_BRACE, SEMICOLON, RETURN_ARROW, D_L_ANGLE, L_ANGLE, D_R_ANGLE, R_ANGLE,
        D_L_BRACKET, L_BRACKET, D_R_BRACKET, R_BRACKET, COMMA, T_DOT, DOT, D_COLON,
        COLON, HASH, AT,

        // Reserved keywords [UN = Unsafe]
        FN, RETURN, CLASS, IF, ELSE, WHILE, FOR, IN, BREAK, CONTINUE, IMPORT, AS,
        FROM, NULL_KW, SELF, SUPER, STATIC, CONST, MUT, ENUM, STRUCT,
        UNION, TYPE, PUBLIC, PRIVATE, PROTECTED, EXTENDS, IMPLEMENTS, INSTANCE_OF,
        UNSAFE, UN_DELETE, UN_CXX, UN_C, UN_ASM, UN_EXPOSE, FRIEND,

        // Reserved data types [UN = Unsafe]
        INT_8BIT, INT_16BIT, INT_32BIT, INT_64BIT, INT_128BIT,
        UINT_8BIT, UINT_16BIT, UINT_32BIT, UINT_64BIT, UINT_128BIT,
        FLOAT_32BIT, FLOAT_64BIT, BOOL, CHAR, VOID, UN_VOID, INT_MAX,
        UINT_MAX, FLOAT_MAX,

        // Literals
        IDENTIFIER, DECIMAL_NUMBER, NUMBER, STRING, CHAR_LIT, TRUE, FALSE, NULL_LIT
    };

    struct Token {
        TokenType type;
        std::string value;

        size_t line;
        size_t column;
        size_t index;
    };

    class Lexer {
        std::string input;
        size_t line = 0;
        size_t column = 0;
        size_t index = 0;

    public:
        explicit Lexer(std::string input): input(std::move(input)) {}

        std::optional<Token> next() {
            if (input.length() == 0)
                return Token{
                        TokenType::EOI,
                        "EOI",
                        line,
                        column,
                        index
                };

            if (input[0] == '\n') {
                line++;
                column = 0;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::NEWLINE,
                        .value = "\n",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == ' ') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::SPACE,
                        .value = " ",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '\t') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::TAB,
                        .value = "\t",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '/') {
                if (input[1] == '/') {
                    input.erase(0, 2);
                    index++;

                    std::string comment = "//";

                    while (input[0] != '\n') {
                        comment += input[0];
                        input.erase(0, 1);
                        index++;
                    }

                    return Token{
                            .type = TokenType::COMMENT,
                            .value = comment,
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '(') {
                if (input[1] == '(') {
                    input.erase(0, 2);
                    index++;

                    return Token{
                            .type = TokenType::D_L_PAREN,
                            .value = "((",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::L_PAREN,
                            .value = "(",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == ')') {
                if (input[1] == ')') {
                    input.erase(0, 2);
                    index++;

                    return Token{
                            .type = TokenType::D_R_PAREN,
                            .value = "))",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::R_PAREN,
                            .value = ")",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '{') {
                if (input[1] == '{') {
                    input.erase(0, 2);
                    index++;

                    return Token{
                            .type = TokenType::D_L_BRACE,
                            .value = "{{",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::L_BRACE,
                            .value = "{",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '}') {
                if (input[1] == '}') {
                    input.erase(0, 2);
                    index++;

                    return Token{
                            .type = TokenType::D_R_BRACE,
                            .value = "}}",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::R_BRACE,
                            .value = "}",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == ';') {
                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::SEMICOLON,
                        .value = ";",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '-') {
                if (input[1] == '>') {
                    input.erase(0, 2);
                    index++;

                    return Token{
                            .type = TokenType::RETURN_ARROW,
                            .value = "->",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '<') {
                if (input[1] == '<') {
                    input.erase(0, 2);
                    index++;

                    return Token{
                            .type = TokenType::D_L_ANGLE,
                            .value = "<<",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::L_ANGLE,
                            .value = "<",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '>') {
                if (input[1] == '>') {
                    input.erase(0, 2);
                    index++;

                    return Token{
                            .type = TokenType::D_R_ANGLE,
                            .value = ">>",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::R_ANGLE,
                            .value = ">",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '[') {
                if (input[1] == '[') {
                    input.erase(0, 2);
                    index++;

                    return Token{
                            .type = TokenType::D_L_BRACKET,
                            .value = "[[",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::L_BRACKET,
                            .value = "[",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == ']') {
                if (input[1] == ']') {
                    input.erase(0, 2);
                    index++;

                    return Token{
                            .type = TokenType::D_R_BRACKET,
                            .value = "]]",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::R_BRACKET,
                            .value = "]",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == ',') {
                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::COMMA,
                        .value = ",",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '.') {
                if (input[1] == '.') {
                    input.erase(0, 2);
                    index++;

                    return Token{
                            .type = TokenType::T_DOT,
                            .value = "..",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::DOT,
                            .value = ".",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == ':') {
                if (input[1] == ':') {
                    input.erase(0, 2);
                    index++;

                    return Token{
                            .type = TokenType::D_COLON,
                            .value = "::",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::COLON,
                            .value = ":",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '#') {
                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::HASH,
                        .value = "#",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '@') {
                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::AT,
                        .value = "@",
                        .line = line,
                        .column = column,
                        .index = index
                };
            }

            // RETURN, CLASS, IF, ELSE, WHILE, FOR, IN, BREAK, CONTINUE, IMPORT, AS,
            //        FROM, NULL_KW, SELF, SUPER, STATIC, CONST, MUT, ENUM, STRUCT,
            //        UNION, TYPE, PUBLIC, PRIVATE, PROTECTED, EXTENDS, IMPLEMENTS, INSTANCE_OF,
            //        UNSAFE, UN_DELETE, UN_CXX, UN_C, UN_ASM, UN_EXPOSE, FRIEND,
            else if (input[0] == 'f' && input[1] == 'n' && !std::isalpha(input[2])) {
                input.erase(0, 2);
                index++;

                return Token{
                        .type = TokenType::FN,
                        .value = "fn",
                        .line = line,
                        .column = column,
                        .index = index
                };
            }

            // Check if it's an identifier and matches the requirements as follows:
            // -- Starts with an alpha character or underscore.
            // -- Only contains alpha characters, underscores, and numbers.
            
            if (input[0] == '_' || std::isalpha(input[0])) {
                std::string word;
                
                while (true) {
                    if (input[0] != '_' && !std::isalpha(input[0]) && !std::isalnum(input[0]))
                        break;

                    word += input[0];
                    column++;

                    input.erase(0, 1);
                }

                return Token {
                    .type = TokenType::IDENTIFIER,
                    .value = word,
                    .line = line,
                    .column = column,
                    .index = index,
                };
            }

            column++;
            input.erase(0, 1);
            return std::nullopt;
        }

        bool hasNext() {
            return input.length() != 0;
        }

        size_t getLine() {
            return line;
        }

        size_t getColumn() {
            return column;
        }
    };
}
