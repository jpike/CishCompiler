#pragma once

#include <string>
#include "Tokenization/TokenType.h"

namespace TOKENIZATION
{
    /// A single parsed token.
    struct Token
    {
        /// The type of the token.
        TokenType Type = TokenType::INVALID;
        /// The raw value of the token.
        std::string Value = "";
        /// The path of the file from which the token came.
        std::string Filepath = "";
        /// The line number in the file from which the token came.
        std::size_t LineNumber = 0;
        /// The column number in the file from which the token came.
        std::size_t ColumnNumber = 0;
    };
}
