#pragma once

#include <cstdio>
#include <optional>
#include <string>
#include "CustomString.h"
#include "Tokenization/Token.h"

struct SingleLineComment
{
    static std::optional<TOKENIZATION::Token> Parse(const std::string& source_code, const std::size_t start_index)
    {
        using namespace TOKENIZATION;
        
        // MAKE SURE THE STARTING CHARACTERS ARE FOR THE START OF A SINGLE LINE COMMENT.
        const std::string SINGLE_LINE_COMMENT_START = "//";
        bool is_start_of_single_line_comment = String::CharactersMatch(source_code, start_index, SINGLE_LINE_COMMENT_START);
        if (!is_start_of_single_line_comment)
        {
            return std::nullopt;
        }
        
        // READ THE ENTIRETY OF THE SINGLE LINE COMMENT.
        Token single_line_comment =
        {
            .Type = TokenType::COMMENT,
            .Value = SINGLE_LINE_COMMENT_START
        };
        std::size_t comment_body_start_index = start_index + SINGLE_LINE_COMMENT_START.length();
        std::size_t source_code_character_count = source_code.length();
        for (std::size_t next_character_index = comment_body_start_index; next_character_index < source_code_character_count; ++next_character_index)
        {
            // CHECK IF THE END OF THE LINE HAS BEEN REACHED.
            char next_character = source_code[next_character_index];
            bool line_end_reached = ('\r' == next_character || '\n' == next_character);
            if (line_end_reached)
            {
                // RETURN THE SINGLE LINE COMMENT.
                return single_line_comment;
            }
            
            // ADD THE NEXT CHARACTER TO THE COMMENT.
            single_line_comment.Value += next_character;
        }
        
        // RETURN THE SINGLE LINE COMMENT.
        // If the end of the line was reached above, we would have already returned.
        // If we reach this point, then we've exhausted the source code, so this must
        // be a single line comment at the end of a file.
        return single_line_comment;
    }
};

