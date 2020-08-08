#pragma once

#include <optional>
#include "Tokenization/Token.h"
#include "Tokenization/TokenType.h"

namespace TOKENIZATION
{
    /// A stream of parsed tokens.
    /// The data type eases interaction with progressing (consuming)
    /// tokens from a stream.
    struct TokenStream
    {
        /// Checks if the stream has any more tokens.
        /// @return True if the stream has more tokens; false if not.
        bool MoreTokens() const
        {
            std::size_t token_count = Tokens.size();
            bool more_tokens = (CurrentIndex < token_count);
            return more_tokens;
        }
        
        /// Consumes the next token.  This method assumes that
        /// there is already another token.
        /// @return The next token.
        Token ConsumeNextToken()
        {
            Token& next_token = Tokens[CurrentIndex];
            ++CurrentIndex;
            return next_token;
        }
        
        /// Consumes the next token if it matches the specified type.
        /// @param[in] token_type - The type of token to look for.
        /// @return The next token, if it matches the specified type; null otherwise.
        std::optional<Token> ConsumeNextTokenIfMatch(const TokenType token_type)
        {
            bool next_token_exists = MoreTokens();
            if (!next_token_exists)
            {
                return std::nullopt;
            }
            
            Token& next_token = Tokens[CurrentIndex];
            bool token_type_matches = (token_type == next_token.Type);
            if (token_type_matches)
            {
                ++CurrentIndex;
                return next_token;
            }
            else
            {
                return std::nullopt;
            }
        }
        
        /// Consumes a series of next tokens if they match the sequence of specified types.
        /// @param[in] token_types - The types of the next sequence of tokens to look for.
        /// @return The sequence of next tokens matching the specified types, if they exists;
        ///     empty if no next sequence of tokens matching the specified types exist.
        std::vector<Token> ConsumeNextTokensIfMatch(const std::vector<TokenType>& token_types)
        {
            std::vector<Token> matching_next_tokens;
            
            std::size_t current_token_index = CurrentIndex;
            for (TokenType token_type : token_types)
            {
                bool more_tokens = (current_token_index < Tokens.size());
                if (!more_tokens)
                {
                    return {};
                }
                
                Token& current_token = Tokens[current_token_index];
                bool current_token_matches = (token_type == current_token.Type);
                if (current_token_matches)
                {
                    matching_next_tokens.push_back(current_token);
                    ++current_token_index;
                }
                else
                {
                    return {};
                }
            }
            
            CurrentIndex = current_token_index;
            
            return matching_next_tokens;
        }
        
        /// The index of the current token in the stream.
        std::size_t CurrentIndex = 0;
        /// The remaining tokens in the stream.
        std::vector<Token> Tokens = {};
    };
}
