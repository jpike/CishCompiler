#pragma once

#include <cstdio>
#include <optional>
#include <string>
#include "CustomString.h"
#include "Tokenization/Token.h"

struct MultilineComment
{
    static std::optional<TOKENIZATION::Token> Parse(const std::string& source_code, const std::size_t start_index)
    {
        using namespace TOKENIZATION;
        
        // MAKE SURE THE STARTING CHARACTERS ARE FOR THE START OF A MULTILINE COMMENT.
        const std::string MULTILINE_COMMENT_START = "/*";
        bool is_start_of_multiline_comment = String::CharactersMatch(source_code, start_index, MULTILINE_COMMENT_START);
        if (!is_start_of_multiline_comment)
        {
            return std::nullopt;
        }
        
        // READ THE ENTIRETY OF THE MULTILINE COMMENT.
        Token multiline_comment =
        {
            .Type = TokenType::COMMENT,
            .Value = MULTILINE_COMMENT_START
        };
        bool looking_for_closing_asterisk = true;
        bool looking_for_closing_slash = false;
        bool end_of_comment_found = false;
        std::size_t comment_body_start_index = start_index + MULTILINE_COMMENT_START.length();
        std::size_t source_code_character_count = source_code.length();
        for (std::size_t next_character_index = comment_body_start_index; next_character_index < source_code_character_count; ++next_character_index)
        {
            // ADD THE NEXT CHARACTER TO THE COMMENT.
            char next_character = source_code[next_character_index];
            multiline_comment.Value += next_character;
            
            // DETERMINE IF WE'RE STILL LOOKING FOR THE CLOSING OF THE COMMENT.
            if (looking_for_closing_asterisk)
            {
                if ('*' == next_character)
                {
                    // After a closing asterisk should come a closing slash.
                    looking_for_closing_asterisk = false;
                    looking_for_closing_slash = true;
                }
            }
            else if (looking_for_closing_slash)
            {
                if ('/' == next_character)
                {
                    // After a closing slash, that should end the multiline comment.
                    looking_for_closing_slash = false;
                    end_of_comment_found = true;
                }
                else
                {
                    // If a closing slash didn't appear right after an asterisk,
                    // then that means we're just seeing those characters in the
                    // middle of a multiline comment.
                    looking_for_closing_asterisk = true;
                    looking_for_closing_slash = false;
                }
            }
            
            // CHECK IF WE'VE FOUND THE END OF A COMMENT.
            if (end_of_comment_found)
            {
                // END PARSING THE MULTILINE COMMENT.
                return multiline_comment;
            }
            else
            {
                // CONTINUE LOOKING FOR THE END OF THE COMMENT.
                continue;
            }
        }
        
        // CHECK IF THE END OF THE COMMENT WAS FOUND.
        if (end_of_comment_found)
        {
            // RETURN THE MULTILINE COMMENT.
            return multiline_comment;
        }
        else
        {
            // INDICATE AN ERROR OCCURRED.
            // If it was confirmed that a multiline commented started,
            // it must end at some point for the program to be valid.
            // If we reach the end of the above loop without finding
            // the end of the comment, that's an error.
            std::printf("Unterminated multiline comment found.");
            return std::nullopt;
        }
    }
};

