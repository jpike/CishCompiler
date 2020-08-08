#include <string>
#include "LanguageConstructs/Identifier.h"
#include "LanguageConstructs/MultilineComment.h"
#include "LanguageConstructs/Number.h"
#include "LanguageConstructs/SingleLineComment.h"
#include "LanguageConstructs/StringLiteral.h"
#include "Tokenization/TokenStream.h"

namespace TOKENIZATION
{
    /// Tokenizes a string of raw source code into a stream of tokens.
    struct Tokenizer
    {
        /// Converts a string of raw source code into a token stream.
        /// @param[in] source_code - The source code to parse.
        /// @return The stream of tokens parsed from the source code.
        static TokenStream Tokenize(const std::string& source_code)
        {
            TokenStream token_stream;
            
            // PARSE EACH CHARACTER IN THE SOURCE CODE.
            std::size_t character_index = 0;
            std::size_t source_code_character_count = source_code.length();
            while (character_index < source_code_character_count)
            {
                // PROCESS THE CURRENT CHARACTER.
                char current_character = source_code[character_index];
                //std::printf("%c", current_character);
                switch (current_character)
                {
                    // COMMENT/DIVISION PARSING.
                    case '/':
                    {
                        // TRY PARSING A SINGLE-LINE COMMENT.
                        std::optional<Token> single_line_comment = SingleLineComment::Parse(source_code, character_index);
                        if (single_line_comment)
                        {
                            // ADD THE SINGLE LINE COMMENT.
                            token_stream.Tokens.push_back(*single_line_comment);
                            
                            // ADVANCE TO THE NEXT CHARACTER.
                            character_index += single_line_comment->Value.length();
                            continue;
                        }
                        else
                        {
                            // TRY PARSING A MULTILINE COMMENT.
                            std::optional<Token> multiline_comment = MultilineComment::Parse(source_code, character_index);
                            if (multiline_comment)
                            {
                                // ADD THE MULTILINE COMMENT.
                                token_stream.Tokens.push_back(*multiline_comment);
                                
                                // ADVANCE TO THE NEXT CHARACTER.
                                character_index += multiline_comment->Value.length();
                                continue;
                            }
                            else
                            {
                                // ADD THE DIVISION OPERATOR.
                                Token division_operator =
                                {
                                    .Type = TokenType::OPERATOR,
                                    .Value = "/",
                                };
                                token_stream.Tokens.push_back(division_operator);
                                
                                // ADVANCE TO THE NEXT CHARACTER.
                                ++character_index;
                                continue;
                            }
                        }
                        
                        break;
                    }
                    // BRACE, BRACKET, PARENTHESES.
                    case '{':
                    {
                        // ADD THE OPENING CURLY BRACE.
                        Token opening_curly_brace = 
                        {
                            .Type = TokenType::OPENING_CURLY_BRACE,
                            .Value = '{'
                        };
                        token_stream.Tokens.push_back(opening_curly_brace);
                        break;
                    }
                    case '}':
                    {
                        // ADD THE CLOSING CURLY BRACE.
                        Token closing_curly_brace = 
                        {
                            .Type = TokenType::CLOSING_CURLY_BRACE,
                            .Value = '}'
                        };
                        token_stream.Tokens.push_back(closing_curly_brace);
                        break;
                    }
                    case '[':
                    {
                        // ADD THE OPENING BRACKET.
                        Token opening_bracket =
                        {
                            .Type = TokenType::PUNCTUATOR,
                            .Value = "["
                        };
                        token_stream.Tokens.push_back(opening_bracket);
                        break;
                    }
                    case ']':
                    {
                        // ADD THE CLOSING BRACKET.
                        Token closing_bracket =
                        {
                            .Type = TokenType::PUNCTUATOR,
                            .Value = "]"
                        };
                        token_stream.Tokens.push_back(closing_bracket);
                        break;
                    }
                    case '(':
                    {
                        // ADD THE OPENING PARENTHESIS.
                        Token opening_parenthesis = 
                        {
                            .Type = TokenType::OPENING_PARENTHESIS,
                            .Value = '('
                        };
                        token_stream.Tokens.push_back(opening_parenthesis);
                        break;
                    }
                    case ')':
                    {
                        // ADD THE CLOSING PARENTHESIS.
                        Token closing_parenthesis = 
                        {
                            .Type = TokenType::CLOSING_PARENTHESIS,
                            .Value = ')'
                        };
                        token_stream.Tokens.push_back(closing_parenthesis);
                        break;
                    }
                    // REMAINING OPERATOR PARSING.
                    case '=':
                    {
                        std::size_t next_character_index = character_index + 1;
                        std::optional<char> next_character = String::GetCharacterIfExists(source_code, next_character_index);
                        if ('=' == next_character)
                        {
                            // ADD THE EQUALITY OPERATOR.
                            Token equality_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = "=="
                            };
                            token_stream.Tokens.push_back(equality_operator);
                            character_index = next_character_index;
                        }
                        else
                        {
                            // ADD THE ASSIGNMENT OPERATOR.
                            Token assignment_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = "="
                            };
                            token_stream.Tokens.push_back(assignment_operator);
                        }
                        break;
                    }
                    case '!':
                    {
                        std::size_t next_character_index = character_index + 1;
                        std::optional<char> next_character = String::GetCharacterIfExists(source_code, next_character_index);
                        if ('=' == next_character)
                        {
                            // ADD THE INEQUALITY OPERATOR.
                            Token inequality_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = "!="
                            };
                            token_stream.Tokens.push_back(inequality_operator);
                            character_index = next_character_index;
                        }
                        else
                        {
                            // ADD THE NOT OPERATOR.
                            Token not_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = "!"
                            };
                            token_stream.Tokens.push_back(not_operator);
                        }
                        break;
                    }
                    case '<':
                    {
                        std::size_t next_character_index = character_index + 1;
                        std::optional<char> next_character = String::GetCharacterIfExists(source_code, next_character_index);
                        if ('=' == next_character)
                        {
                            // ADD THE LESS-THAN-OR-EQUAL-TO OPERATOR.
                            Token less_than_or_equal_to_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = "<="
                            };
                            token_stream.Tokens.push_back(less_than_or_equal_to_operator);
                            character_index = next_character_index;
                        }
                        else if ('<' == next_character)
                        {
                            // ADD THE LEFT-SHIFT OPERATOR.
                            Token left_shift_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = "<<"
                            };
                            token_stream.Tokens.push_back(left_shift_operator);
                            character_index = next_character_index;
                        }
                        else
                        {
                            // ADD THE LESS-THAN OPERATOR.
                            Token less_than_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = "<"
                            };
                            token_stream.Tokens.push_back(less_than_operator);
                        }
                        break;
                    }
                    case '>':
                    {
                        std::size_t next_character_index = character_index + 1;
                        std::optional<char> next_character = String::GetCharacterIfExists(source_code, next_character_index);
                        if ('=' == next_character)
                        {
                            // ADD THE GREAT-THAN-OR-EQUAL-TO OPERATOR.
                            Token greater_than_or_equal_to_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = ">="
                            };
                            token_stream.Tokens.push_back(greater_than_or_equal_to_operator);
                            character_index = next_character_index;
                        }
                        else if ('>' == next_character)
                        {
                            // ADD THE LEFT-SHIFT OPERATOR.
                            Token right_shift_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = ">>"
                            };
                            token_stream.Tokens.push_back(right_shift_operator);
                            character_index = next_character_index;
                        }
                        else
                        {
                            // ADD THE GREATER-THAN OPERATOR.
                            Token greater_than_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = ">"
                            };
                            token_stream.Tokens.push_back(greater_than_operator);
                        }
                        break;
                    }
                    case '|':
                    {
                        std::size_t next_character_index = character_index + 1;
                        std::optional<char> next_character = String::GetCharacterIfExists(source_code, next_character_index);
                        if ('|' == next_character)
                        {
                            // ADD THE LOGICAL OR OPERATOR.
                            Token logical_or_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = "||"
                            };
                            token_stream.Tokens.push_back(logical_or_operator);
                            character_index = next_character_index;
                        }
                        else
                        {
                            // ADD THE BITWISE OR OPERATOR.
                            Token bitwise_or_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = "|"
                            };
                            token_stream.Tokens.push_back(bitwise_or_operator);
                        }
                        break;
                    }
                    case '&':
                    {
                        std::size_t next_character_index = character_index + 1;
                        std::optional<char> next_character = String::GetCharacterIfExists(source_code, next_character_index);
                        if ('&' == next_character)
                        {
                            // ADD THE LOGICAL AND OPERATOR.
                            Token logical_and_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = "&&"
                            };
                            token_stream.Tokens.push_back(logical_and_operator);
                            character_index = next_character_index;
                        }
                        else
                        {
                            // ADD THE BITWISE AND OPERATOR.
                            Token bitwise_and_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = "&"
                            };
                            token_stream.Tokens.push_back(bitwise_and_operator);
                        }
                        break;
                    }
                    case '+':
                    {
                        std::size_t next_character_index = character_index + 1;
                        std::optional<char> next_character = String::GetCharacterIfExists(source_code, next_character_index);
                        if ('+' == next_character)
                        {
                            // ADD THE INCREMENT OPERATOR.
                            Token increment_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = "++"
                            };
                            token_stream.Tokens.push_back(increment_operator);
                            character_index = next_character_index;
                        }
                        else
                        {
                            // ADD THE PLUS OPERATOR.
                            Token plus_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = "+"
                            };
                            token_stream.Tokens.push_back(plus_operator);
                        }
                        break;
                    }
                    case '-':
                    {
                        std::size_t next_character_index = character_index + 1;                       
                        std::optional<char> next_character = String::GetCharacterIfExists(source_code, next_character_index);
                        if ('>' == next_character)
                        {
                            // ADD THE DEREFERENCE OPERATOR.
                            Token dereference_to_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = "->"
                            };
                            token_stream.Tokens.push_back(dereference_to_operator);
                            character_index = next_character_index;
                        }
                        else if ('-' == next_character)
                        {
                            // ADD THE DECREMENT OPERATOR.
                            Token decrement_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = "--"
                            };
                            token_stream.Tokens.push_back(decrement_operator);
                            character_index = next_character_index;
                        }
                        else
                        {
                            // ADD THE MINUS OPERATOR.
                            Token minus_operator =
                            {
                                .Type = TokenType::OPERATOR,
                                .Value = "-"
                            };
                            token_stream.Tokens.push_back(minus_operator);
                        }
                        break;
                    }
                    case '*':
                    {
                        // ADD THE MULTIPLICATION OPERATOR.
                        Token multiplication_operator =
                        {
                            .Type = TokenType::OPERATOR,
                            .Value = "*"
                        };
                        token_stream.Tokens.push_back(multiplication_operator);
                        break;
                    }
                    // STATEMENT TERMINATOR.
                    case ';':
                    {
                        // ADD THE STATEMENT TERMINATOR.
                        Token statement_terminator =
                        {
                            .Type = TokenType::PUNCTUATOR,
                            .Value = ";"
                        };
                        token_stream.Tokens.push_back(statement_terminator);
                        break;
                    }
                    // KEYWORD PARSING.
                    case 'a':
                    {
                        const std::string AUTO_KEYWORD = "auto";
                        bool is_auto = String::CharactersMatch(source_code, character_index, AUTO_KEYWORD);
                        if (is_auto)
                        {
                            Token auto_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = AUTO_KEYWORD
                            };
                            token_stream.Tokens.push_back(auto_keyword);
                            character_index += AUTO_KEYWORD.length();
                            continue;
                        }
                        else
                        {
                            Token identifier = Identifier::Parse(source_code, character_index);
                            token_stream.Tokens.push_back(identifier);
                            character_index += identifier.Value.length();
                            continue;
                        }
                        break;
                    }
                    case 'b':
                    {
                        const std::string BREAK_KEYWORD = "break";
                        bool is_break = String::CharactersMatch(source_code, character_index, BREAK_KEYWORD);
                        if (is_break)
                        {
                            Token break_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = BREAK_KEYWORD
                            };
                            token_stream.Tokens.push_back(break_keyword);
                            character_index += BREAK_KEYWORD.length();
                            continue;
                        }
                        else
                        {
                            Token identifier = Identifier::Parse(source_code, character_index);
                            token_stream.Tokens.push_back(identifier);
                            character_index += identifier.Value.length();
                            continue;
                        }
                        break;
                    }
                    case 'c':
                    {
                        const std::string CASE_KEYWORD = "case";
                        bool is_case = String::CharactersMatch(source_code, character_index, CASE_KEYWORD);
                        if (is_case)
                        {
                            Token case_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = CASE_KEYWORD
                            };
                            token_stream.Tokens.push_back(case_keyword);
                            character_index += CASE_KEYWORD.length();
                            continue;
                        }
                        
                        const std::string CHAR_KEYWORD = "char";
                        bool is_char = String::CharactersMatch(source_code, character_index, CHAR_KEYWORD);
                        if (is_char)
                        {
                            Token char_keyword =
                            {
                                .Type = TokenType::DATA_TYPE,
                                .Value = CHAR_KEYWORD
                            };
                            token_stream.Tokens.push_back(char_keyword);
                            character_index += CHAR_KEYWORD.length();
                            continue;
                        }
                        
                        const std::string CONST_KEYWORD = "const";
                        bool is_const = String::CharactersMatch(source_code, character_index, CONST_KEYWORD);
                        if (is_const)
                        {
                            Token const_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = CONST_KEYWORD
                            };
                            token_stream.Tokens.push_back(const_keyword);
                            character_index += CONST_KEYWORD.length();
                            continue;
                        }
                        
                        const std::string CONTINUE_KEYWORD = "continue";
                        bool is_continue = String::CharactersMatch(source_code, character_index, CONTINUE_KEYWORD);
                        if (is_continue)
                        {
                            Token continue_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = CONTINUE_KEYWORD
                            };
                            token_stream.Tokens.push_back(continue_keyword);
                            character_index += CONTINUE_KEYWORD.length();
                            continue;
                        }
                        
                        Token identifier = Identifier::Parse(source_code, character_index);
                        token_stream.Tokens.push_back(identifier);
                        character_index += identifier.Value.length();
                        continue;
                    }
                    case 'd':
                    {
                        const std::string DEFAULT_KEYWORD = "default";
                        bool is_default = String::CharactersMatch(source_code, character_index, DEFAULT_KEYWORD);
                        if (is_default)
                        {
                            Token default_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = DEFAULT_KEYWORD
                            };
                            token_stream.Tokens.push_back(default_keyword);
                            character_index += DEFAULT_KEYWORD.length();
                            continue;
                        }
                        
                        const std::string DOUBLE_KEYWORD = "double";
                        bool is_double = String::CharactersMatch(source_code, character_index, DOUBLE_KEYWORD);
                        if (is_double)
                        {
                            Token double_keyword =
                            {
                                .Type = TokenType::DATA_TYPE,
                                .Value = DOUBLE_KEYWORD
                            };
                            token_stream.Tokens.push_back(double_keyword);
                            character_index += DOUBLE_KEYWORD.length();
                            break;
                        }
                        
                        const std::string DO_KEYWORD = "do";
                        bool is_do = String::CharactersMatch(source_code, character_index, DO_KEYWORD);
                        if (is_do)
                        {
                            Token do_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = DO_KEYWORD
                            };
                            token_stream.Tokens.push_back(do_keyword);
                            character_index += DO_KEYWORD.length();
                            continue;
                        }
                        
                        Token identifier = Identifier::Parse(source_code, character_index);
                        token_stream.Tokens.push_back(identifier);
                        character_index += identifier.Value.length();
                        continue;
                    }
                    case 'e':
                    {
                        const std::string ELSE_KEYWORD = "else";
                        bool is_else = String::CharactersMatch(source_code, character_index, ELSE_KEYWORD);
                        if (is_else)
                        {
                            Token else_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = ELSE_KEYWORD
                            };
                            token_stream.Tokens.push_back(else_keyword);
                            character_index += ELSE_KEYWORD.length();
                            continue;
                        }
                        
                        const std::string ENUM_KEYWORD = "enum";
                        bool is_enum = String::CharactersMatch(source_code, character_index, ENUM_KEYWORD);
                        if (is_enum)
                        {
                            Token enum_keyword =
                            {
                                .Type = TokenType::DATA_TYPE,
                                .Value = ENUM_KEYWORD
                            };
                            token_stream.Tokens.push_back(enum_keyword);
                            character_index += ENUM_KEYWORD.length();
                            continue;
                        }
                        
                        const std::string EXTERN_KEYWORD = "extern";
                        bool is_extern = String::CharactersMatch(source_code, character_index, EXTERN_KEYWORD);
                        if (is_extern)
                        {
                            Token extern_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = EXTERN_KEYWORD
                            };
                            token_stream.Tokens.push_back(extern_keyword);
                            character_index += EXTERN_KEYWORD.length();
                            continue;
                        }
                        
                        Token identifier = Identifier::Parse(source_code, character_index);
                        token_stream.Tokens.push_back(identifier);
                        character_index += identifier.Value.length();
                        continue;
                    }
                    case 'f':
                    {
                        const std::string FLOAT_KEYWORD = "float";
                        bool is_float = String::CharactersMatch(source_code, character_index, FLOAT_KEYWORD);
                        if (is_float)
                        {
                            Token float_keyword =
                            {
                                .Type = TokenType::DATA_TYPE,
                                .Value = FLOAT_KEYWORD
                            };
                            token_stream.Tokens.push_back(float_keyword);
                            character_index += FLOAT_KEYWORD.length();
                            continue;
                        }
                        
                        const std::string FOR_KEYWORD = "for";
                        bool is_for = String::CharactersMatch(source_code, character_index, FOR_KEYWORD);
                        if (is_for)
                        {
                            Token for_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = FOR_KEYWORD
                            };
                            token_stream.Tokens.push_back(for_keyword);
                            character_index += FOR_KEYWORD.length();
                            continue;
                        }
                        
                        Token identifier = Identifier::Parse(source_code, character_index);
                        token_stream.Tokens.push_back(identifier);
                        character_index += identifier.Value.length();
                        continue;
                    }
                    case 'g':
                    {
                        const std::string GOTO_KEYWORD = "goto";
                        bool is_goto = String::CharactersMatch(source_code, character_index, GOTO_KEYWORD);
                        if (is_goto)
                        {
                            Token goto_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = GOTO_KEYWORD
                            };
                            token_stream.Tokens.push_back(goto_keyword);
                            character_index += GOTO_KEYWORD.length();
                            continue;
                        }
                        else
                        {
                            Token identifier = Identifier::Parse(source_code, character_index);
                            token_stream.Tokens.push_back(identifier);
                            character_index += identifier.Value.length();
                            continue;
                        }
                        break;
                    }
                    case 'i':
                    {
                        const std::string IF_KEYWORD = "if";
                        bool is_if_keyword = String::CharactersMatch(source_code, character_index, IF_KEYWORD);
                        if (is_if_keyword)
                        {
                            // ADD THE IF KEYWORD.
                            Token if_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = IF_KEYWORD
                            };
                            token_stream.Tokens.push_back(if_keyword);
                            
                            // ADVANCE TO THE NEXT CHARACTER.
                            character_index += IF_KEYWORD.length();
                            continue;
                        }
                        
                        const std::string INT_KEYWORD = "int";
                        bool is_int_keyword = String::CharactersMatch(source_code, character_index, INT_KEYWORD);
                        if (is_int_keyword)
                        {
                            // ADD THE INT KEYWORD.
                            Token int_keyword =
                            {
                                .Type = TokenType::DATA_TYPE,
                                .Value = INT_KEYWORD
                            };
                            token_stream.Tokens.push_back(int_keyword);
                            
                            // ADVANCE TO THE NEXT CHARACTER.
                            character_index += INT_KEYWORD.length();
                            continue;
                        }
                            
                        // ADD AN IDENTIFIER.
                        Token identifier = Identifier::Parse(source_code, character_index);
                        token_stream.Tokens.push_back(identifier);
                        character_index += identifier.Value.length();
                        continue;
                    }
                    case 'l':
                    {
                        const std::string LONG_KEYWORD = "long";
                        bool is_long = String::CharactersMatch(source_code, character_index, LONG_KEYWORD);
                        if (is_long)
                        {
                            Token long_keyword =
                            {
                                .Type = TokenType::DATA_TYPE,
                                .Value = LONG_KEYWORD
                            };
                            token_stream.Tokens.push_back(long_keyword);
                            character_index += LONG_KEYWORD.length();
                            continue;
                        }
                        else
                        {
                            Token identifier = Identifier::Parse(source_code, character_index);
                            token_stream.Tokens.push_back(identifier);
                            character_index += identifier.Value.length();
                            continue;
                        }
                        break;
                    }
                    case 'r':
                    {
                        const std::string REGISTER_KEYWORD = "register";
                        bool is_register = String::CharactersMatch(source_code, character_index, REGISTER_KEYWORD);
                        if (is_register)
                        {
                            Token register_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = REGISTER_KEYWORD
                            };
                            token_stream.Tokens.push_back(register_keyword);
                            character_index += REGISTER_KEYWORD.length();
                            continue;
                        }
                        
                        const std::string RETURN_KEYWORD = "return";
                        bool is_return = String::CharactersMatch(source_code, character_index, RETURN_KEYWORD);
                        if (is_return)
                        {
                            Token return_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = RETURN_KEYWORD
                            };
                            token_stream.Tokens.push_back(return_keyword);
                            character_index += RETURN_KEYWORD.length();
                            continue;
                        }
                        
                        Token identifier = Identifier::Parse(source_code, character_index);
                        token_stream.Tokens.push_back(identifier);
                        character_index += identifier.Value.length();
                        continue;
                    }
                    case 's':
                    {
                        const std::string SHORT_KEYWORD = "short";
                        bool is_short = String::CharactersMatch(source_code, character_index, SHORT_KEYWORD);
                        if (is_short)
                        {
                            Token short_keyword =
                            {
                                .Type = TokenType::DATA_TYPE,
                                .Value = SHORT_KEYWORD
                            };
                            token_stream.Tokens.push_back(short_keyword);
                            character_index += SHORT_KEYWORD.length();
                            continue;
                        }
                        
                        const std::string SIGNED_KEYWORD = "signed";
                        bool is_signed = String::CharactersMatch(source_code, character_index, SIGNED_KEYWORD);
                        if (is_signed)
                        {
                            Token signed_keyword =
                            {
                                .Type = TokenType::DATA_TYPE,
                                .Value = SIGNED_KEYWORD
                            };
                            token_stream.Tokens.push_back(signed_keyword);
                            character_index += SIGNED_KEYWORD.length();
                            continue;
                        }
                        
                        const std::string SIZE_OF_KEYWORD = "sizeof";
                        bool is_sizeof = String::CharactersMatch(source_code, character_index, SIZE_OF_KEYWORD);
                        if (is_sizeof)
                        {
                            Token sizeof_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = SIZE_OF_KEYWORD
                            };
                            token_stream.Tokens.push_back(sizeof_keyword);
                            character_index += SIZE_OF_KEYWORD.length();
                            continue;
                        }
                        
                        const std::string STATIC_KEYWORD = "static";
                        bool is_static = String::CharactersMatch(source_code, character_index, STATIC_KEYWORD);
                        if (is_static)
                        {
                            Token static_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = STATIC_KEYWORD
                            };
                            token_stream.Tokens.push_back(static_keyword);
                            character_index = STATIC_KEYWORD.length();
                            continue;
                        }
                        
                        const std::string STRUCT_KEYWORD = "struct";
                        bool is_struct = String::CharactersMatch(source_code, character_index, STRUCT_KEYWORD);
                        if (is_struct)
                        {
                            Token struct_keyword =
                            {
                                .Type = TokenType::DATA_TYPE,
                                .Value = STRUCT_KEYWORD
                            };
                            token_stream.Tokens.push_back(struct_keyword);
                            character_index += STRUCT_KEYWORD.length();
                            continue;
                        }
                        
                        const std::string SWITCH_KEYWORD = "switch";
                        bool is_switch = String::CharactersMatch(source_code, character_index, SWITCH_KEYWORD);
                        if (is_switch)
                        {
                            Token switch_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = SWITCH_KEYWORD
                            };
                            token_stream.Tokens.push_back(switch_keyword);
                            character_index += SWITCH_KEYWORD.length();
                            continue;
                        }
                        
                        Token identifier = Identifier::Parse(source_code, character_index);
                        token_stream.Tokens.push_back(identifier);
                        character_index += identifier.Value.length();
                        continue;
                    }
                    case 't':
                    {
                        const std::string TYPEDEF_KEYWORD = "typedef";
                        bool is_typedef = String::CharactersMatch(source_code, character_index, TYPEDEF_KEYWORD);
                        if (is_typedef)
                        {
                            Token typedef_keyword =
                            {
                                .Type = TokenType::DATA_TYPE,
                                .Value = TYPEDEF_KEYWORD
                            };
                            token_stream.Tokens.push_back(typedef_keyword);
                            character_index += TYPEDEF_KEYWORD.length();
                            continue;
                        }
                        else
                        {
                            Token identifier = Identifier::Parse(source_code, character_index);
                            token_stream.Tokens.push_back(identifier);
                            character_index += identifier.Value.length();
                            continue;
                        }
                        break;
                    }
                    case 'u':
                    {
                        const std::string UNION_KEYWORD = "union";
                        bool is_union = String::CharactersMatch(source_code, character_index, UNION_KEYWORD);
                        if (is_union)
                        {
                            Token union_keyword =
                            {
                                .Type = TokenType::DATA_TYPE,
                                .Value = UNION_KEYWORD
                            };
                            token_stream.Tokens.push_back(union_keyword);
                            character_index += UNION_KEYWORD.length();
                            continue;
                        }
                        
                        const std::string UNSIGNED_KEYWORD = "unsigned";
                        bool is_unsigned = String::CharactersMatch(source_code, character_index, UNSIGNED_KEYWORD);
                        if (is_unsigned)
                        {
                            Token unsigned_keyword =
                            {
                                .Type = TokenType::DATA_TYPE,
                                .Value = UNSIGNED_KEYWORD
                            };
                            token_stream.Tokens.push_back(unsigned_keyword);
                            character_index += UNSIGNED_KEYWORD.length();
                            continue;
                        }
                        
                        Token identifier = Identifier::Parse(source_code, character_index);
                        token_stream.Tokens.push_back(identifier);
                        character_index += identifier.Value.length();
                        continue;
                    }
                    case 'v':
                    {
                        const std::string VOID_KEYWORD = "void";
                        bool is_void = String::CharactersMatch(source_code, character_index, VOID_KEYWORD);
                        if (is_void)
                        {
                            Token void_keyword =
                            {
                                .Type = TokenType::DATA_TYPE,
                                .Value = VOID_KEYWORD
                            };
                            token_stream.Tokens.push_back(void_keyword);
                            character_index += VOID_KEYWORD.length();
                            continue;
                        }
                        
                        const std::string VOLATILE_KEYWORD = "volatile";
                        bool is_volatile = String::CharactersMatch(source_code, character_index, VOLATILE_KEYWORD);
                        if (is_volatile)
                        {
                            Token volatile_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = VOLATILE_KEYWORD
                            };
                            token_stream.Tokens.push_back(volatile_keyword);
                            character_index += VOLATILE_KEYWORD.length();
                            continue;
                        }
                        
                        Token identifier = Identifier::Parse(source_code, character_index);
                        token_stream.Tokens.push_back(identifier);
                        character_index += identifier.Value.length();
                        continue;
                    }
                    case 'w':
                    {
                        const std::string WHILE_KEYWORD = "while";
                        bool is_while = String::CharactersMatch(source_code, character_index, WHILE_KEYWORD);
                        if (is_while)
                        {
                            Token while_keyword =
                            {
                                .Type = TokenType::KEYWORD,
                                .Value = WHILE_KEYWORD
                            };
                            token_stream.Tokens.push_back(while_keyword);
                            character_index += WHILE_KEYWORD.length();
                            continue;
                        }
                        else
                        {
                            Token identifier = Identifier::Parse(source_code, character_index);
                            token_stream.Tokens.push_back(identifier);
                            character_index += identifier.Value.length();
                            continue;
                        }
                        break;
                    }
                    // NUMBERS.
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9':
                    {
                        // ADD A NUMBER.
                        Token number = Number::Parse(source_code, character_index);
                        token_stream.Tokens.push_back(number);
                        character_index += number.Value.length();
                        continue;
                    }
                    // STRING LITERALS.
                    case '"':
                    {
                        // ADD A STRING LITERAL.
                        Token string_literal = StringLiteral::Parse(source_code, character_index);
                        token_stream.Tokens.push_back(string_literal);
                        character_index += string_literal.Value.length();
                        continue;
                    }
                    // REMAINING IDENTIFIER PARSING.
                    case 'h': case 'j': case 'k': case 'm': case 'n': case 'o':
                    case 'p': case 'q': case 'x': case 'y': case 'z':
                    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': 
                    case 'H': case 'I': case 'J': case 'K': case 'M': case 'N': case 'O': 
                    case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': 
                    case 'W': case 'X': case 'Y': case 'Z':
                    {
                        // ADD AN IDENTIFIER.
                        Token identifier = Identifier::Parse(source_code, character_index);
                        token_stream.Tokens.push_back(identifier);
                        character_index += identifier.Value.length();
                        continue;
                    }
                }
                
                // MOVE TO THE NEXT CHARACTER.
                ++character_index;
            }
            
            // RETURN ANY PARSED TOKEN STREAM.
            return token_stream;
        }
    };
}
