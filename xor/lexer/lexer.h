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
        D_L_BRACKET, L_BRACKET, D_R_BRACKET, R_BRACKET, COMMA, D_DOT, DOT, D_COLON,
        COLON, HASH, AT, SUBTRACT, PLUS, STAR, SLASH, PLUS_EQ, START_EQ, SLASH_EQ,
        SUBTRACT_EQ, BACK_TICK,

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
    
    enum class Type {
        SYMBOL, FILE, LITERAL, KEYWORD
    };
    
    Type getTypeCat(TokenType type) {
        switch (type) {
            case TokenType::NEWLINE:
            case TokenType::SPACE:
            case TokenType::TAB:
            case TokenType::EOI:
            case TokenType::COMMENT:
                return Type::FILE;

            case TokenType::D_L_PAREN:
            case TokenType::L_PAREN:
            case TokenType::D_R_PAREN:
            case TokenType::R_PAREN:
            case TokenType::D_L_BRACE:
            case TokenType::L_BRACE:
            case TokenType::D_R_BRACE:
            case TokenType::R_BRACE:
            case TokenType::SEMICOLON:
            case TokenType::RETURN_ARROW:
            case TokenType::D_L_ANGLE:
            case TokenType::L_ANGLE:
            case TokenType::D_R_ANGLE:
            case TokenType::R_ANGLE:
            case TokenType::D_L_BRACKET:
            case TokenType::L_BRACKET:
            case TokenType::D_R_BRACKET:
            case TokenType::R_BRACKET:
            case TokenType::COMMA:
            case TokenType::D_DOT:
            case TokenType::DOT:
            case TokenType::D_COLON:
            case TokenType::COLON:
            case TokenType::HASH:
            case TokenType::AT:
            case TokenType::SUBTRACT:
            case TokenType::PLUS:
            case TokenType::STAR:
            case TokenType::SLASH:
            case TokenType::PLUS_EQ:
            case TokenType::START_EQ:
            case TokenType::SLASH_EQ:
            case TokenType::SUBTRACT_EQ:
            case TokenType::BACK_TICK:
                return Type::SYMBOL;

            case TokenType::FN:
            case TokenType::RETURN:
                return Type::KEYWORD;
        }
    }

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

                    column += comment.length();

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
                    column += 2;

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
                    column++;

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
                    column += 2;

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
                    column++;

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
                    column += 2;

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
                    column++;

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
                    column += 2;

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
                    column++;

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
                column++;

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
                    column += 2;

                    return Token {
                            .type = TokenType::RETURN_ARROW,
                            .value = "->",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    input.erase(0, 1);
                    index++;
                    column++;

                    return Token {
                         .type = TokenType::SUBTRACT,
                         .value = "-",
                         .line = line,
                         .column = column,
                         .index = index
                    };
                }
            } else if (input[0] == '<') {
                if (input[1] == '<') {
                    input.erase(0, 2);
                    index++;
                    column += 2;

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
                    column++;

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
                    column += 2;

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
                    column++;

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
                    column += 2;

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
                    column++;

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
                    column += 2;

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
                    column++;

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
                column++;

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
                    column += 2;

                    return Token{
                            .type = TokenType::D_DOT,
                            .value = "..",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    input.erase(0, 1);
                    index++;
                    column++;

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
                    column += 2;

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
                    column++;

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
                column++;

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
                column++;

                return Token{
                        .type = TokenType::AT,
                        .value = "@",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '+') {
                if (input[1] == '=') {
                    input.erase(0, 2);
                    index++;
                    column += 2;

                    return Token{
                            .type = TokenType::PLUS_EQ,
                            .value = "+=",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    input.erase(0, 1);
                    index++;
                    column += 2;

                    return Token{
                            .type = TokenType::PLUS,
                            .value = "+",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '-') {
                if (input[1] == '=') {
                    input.erase(0, 2);
                    index++;
                    column += 2;

                    return Token{
                            .type = TokenType::SUBTRACT_EQ,
                            .value = "-=",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    input.erase(0, 1);
                    index++;
                    column += 2;

                    return Token{
                            .type = TokenType::SUBTRACT,
                            .value = "-",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '*') {
                if (input[1] == '=') {
                    input.erase(0, 2);
                    index++;
                    column += 2;

                    return Token{
                            .type = TokenType::START_EQ,
                            .value = "*=",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    input.erase(0, 1);
                    index++;
                    column += 2;

                    return Token{
                            .type = TokenType::STAR,
                            .value = "*",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '/') {
                if (input[1] == '=') {
                    input.erase(0, 2);
                    index++;
                    column += 2;

                    return Token{
                            .type = TokenType::SLASH_EQ,
                            .value = "/=",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    input.erase(0, 1);
                    index++;
                    column += 2;

                    return Token{
                            .type = TokenType::SLASH,
                            .value = "/",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '`') {
                input.erase(0, 1);
                std::string res = "`";
                index++;

                size_t escape = 0;

                while (true) {
                    if (input.length() == 0)
                        return std::nullopt;

                    if (input[0] == '`') {
                        if (escape != 0) {
                            escape = 0;
                            res += input[0];
                        } else {
                            res += "`";
                            break;
                        }
                    } else {
                        if (input[0] == '\\') {
                            res += '\\';
                            escape++;
                        } else {
                            escape = 0;
                            res += input[0];
                        }
                    }

                    input.erase(0, 1);
                }

                column += res.length();
                input.erase(0, 1);

                return Token{
                        .type = TokenType::BACK_TICK,
                        .value = res,
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '"') {
                input.erase(0, 1);
                std::string res = "\"";
                index++;

                size_t escape = 0;

                while (true) {
                    if (input.length() == 0)
                        return std::nullopt;

                    if (input[0] == '"') {
                        if (escape != 0) {
                            escape = 0;
                            res += input[0];
                        } else {
                            res += "\"";
                            break;
                        }
                    } else {
                        if (input[0] == '\\') {
                            res += '\\';
                            escape++;
                        } else {
                            escape = 0;
                            res += input[0];
                        }
                    }

                    input.erase(0, 1);
                }

                column += res.length();
                input.erase(0, 1);

                return Token{
                        .type = TokenType::STRING,
                        .value = res,
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == 'f' && input[1] == 'n' && !std::isalpha(input[2])) {
                input.erase(0, 2);
                index++;
                column += 2;

                return Token{
                        .type = TokenType::FN,
                        .value = "fn",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == 'r' && input[1] == 'e' && input[2] == 't' && !std::isalpha(input[3])) {
                input.erase(0, 3);
                index++;
                column += 3;

                return Token{
                        .type = TokenType::RETURN,
                        .value = "ret",
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

        [[nodiscard]] size_t getLine() const {
            return line;
        }

        [[nodiscard]] size_t getColumn() const {
            return column;
        }
    };
}
