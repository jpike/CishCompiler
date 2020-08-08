#pragma once

#include <cctype>
#include <string>
#include "CustomString.h"
#include "Tokenization/Token.h"

struct Identifier
{
    static TOKENIZATION::Token Parse(const std::string& source_code, const std::size_t start_index)
    {
        using namespace TOKENIZATION;
        
        // CREATE AN EMPTY IDENTIFIER.
        Token identifier = { .Type = TokenType::IDENTIFIER };
        
        // ADD ALL APPROPRIATE CHARACTERS TO THE IDENTITIFER.
        std::size_t source_code_character_count = source_code.length();
        for (std::size_t character_index = start_index; character_index < source_code_character_count; ++character_index)
        {
            char character = source_code[character_index];
            bool is_valid_for_identifier = std::isalnum(character) || '_' == character;
            if (is_valid_for_identifier)
            {
                identifier.Value += character;
            }
            else
            {
                // A non-identifier character was found, so the identifier
                // is assumed to have ended.
                break;
            }
        }
        
        return identifier;
    }
};

