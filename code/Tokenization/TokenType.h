#pragma once

namespace TOKENIZATION
{
    /// Different types of tokens in the C programming language.
    /// Section A2.1 of the C Programming Language book states that there are
    /// 6 classes of tokens.  Those specific kinds of tokens are very generic,
    /// and keeping that same representation here introduces extra complexity.
    /// Therefore, more specific types of tokens are used for this enum.
    /// However, some more generic enum values are retained until replaced
    /// by more-specific token types as determined by needs of the actual
    /// usage code.
    enum class TokenType
    {
        INVALID = 0,
        KEYWORD,
        IDENTIFIER,
        CONSTANT,
        STRING_LITERAL,
        OPERATOR,
        PUNCTUATOR,
        COMMENT,
        
        DATA_TYPE, /// type-specifier from the C grammer.
        OPENING_PARENTHESIS,
        CLOSING_PARENTHESIS,
        OPENING_CURLY_BRACE,
        CLOSING_CURLY_BRACE,
    };
}

