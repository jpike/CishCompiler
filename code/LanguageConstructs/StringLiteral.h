#pragma once

#include <string>
#include "Tokenization/Token.h"

struct StringLiteral
{
    static TOKENIZATION::Token Parse(const std::string& source_code, const std::size_t start_index)
    {
        using namespace TOKENIZATION;
        
        // CREATE AN EMPTY STRING LITERAL.
        Token string_literal = { .Type = TokenType::STRING_LITERAL };
        
        // ADD ALL APPROPRIATE CHARACTERS TO THE STRING.
        std::size_t source_code_character_count = source_code.length();
        for (std::size_t character_index = start_index; character_index < source_code_character_count; ++character_index)
        {
            // ADD THE CHARACTER TO THE STRING.
            char character = source_code[character_index];
            string_literal.Value += character;
            
            // CHECK IF THE END OF THE STRING WAS FOUND.
            bool end_of_string = '"' == character;
            if (end_of_string)
            {
                
            }
        }
        
        return string_literal;
    }
};


