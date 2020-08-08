#pragma once

#include <cctype>
#include <string>
#include "CustomString.h"
#include "Tokenization/Token.h"

struct Number
{
    /// @todo More robust number handling!
    static TOKENIZATION::Token Parse(const std::string& source_code, const std::size_t start_index)
    {
        using namespace TOKENIZATION;
        
        // CREATE AN EMPTY NUMBER.
        Token number = { .Type = TokenType::CONSTANT };
        
        // ADD ALL APPROPRIATE CHARACTERS TO THE NUMBER.
        std::size_t source_code_character_count = source_code.length();
        for (std::size_t character_index = start_index; character_index < source_code_character_count; ++character_index)
        {
            char character = source_code[character_index];
            bool is_valid_for_number = std::isdigit(character);
            if (is_valid_for_number)
            {
                number.Value += character;
            }
            else
            {
                // A non-numeric character was found, so the number
                // is assumed to have ended.
                break;
            }
        }
        
        return number;
    }
};


