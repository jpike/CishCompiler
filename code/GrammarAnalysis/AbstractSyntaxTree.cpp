#include <optional>
#include <string>
#include <vector>
#include "Tokenization/TokenStream.h"

struct VariableDeclaration
{
    std::string DataType;
    std::string Name;
};

struct FunctionHeader
{
    std::string Name;
    std::vector<VariableDeclaration> Parameters;
    std::string ReturnType;
};

struct Statement
{
};

struct Block
{
    static std::optional<Block> Parse(TOKENIZATION::TokenStream& token_stream)
    {
        using namespace TOKENIZATION;
        
        std::optional<Block> block;
        
        while (token_stream.MoreTokens())
        {
            Token current_token = token_stream.ConsumeNextToken();
            std::printf("Block token %s\n", current_token.Value.c_str());
            if (!block)
            {
                bool is_opening_current_block = (TokenType::OPENING_CURLY_BRACE == current_token.Type);
                if (is_opening_current_block)
                {
                    block = Block();
                    continue;
                }
                else
                {
                    return std::nullopt;
                }
            }
            else
            {
                /// @todo Parse statements!
                bool is_opening_new_block = (TokenType::OPENING_CURLY_BRACE == current_token.Type);
                if (is_opening_new_block)
                {
                    /// @todo Need to not consume token for parsing block...
                    std::optional<Block> child_block = Block::Parse(token_stream);
                }
                else if (TokenType::CLOSING_CURLY_BRACE == current_token.Type)
                {
                    /// @todo Success!  Ending current block.
                    return block;
                }
            }
        }
        
        return block;
    }
};

struct FunctionDefinition
{
    FunctionHeader Header;
    //std::vector<Statement> Body;
    Block Body;
};

struct Program
{
    //std::shared_ptr<FunctionDefinition> EntryPoint;
    
    std::unordered_map<std::string, FunctionDefinition> FunctionsByName;
};


Program Parse(TOKENIZATION::TokenStream& token_stream)
{
    using namespace TOKENIZATION;
    
    Program program;
    
    while (token_stream.MoreTokens())
    {
        Token current_token = token_stream.ConsumeNextToken();
        std::printf("Current token: %s\n", current_token.Value.c_str());
        
        // PARSE ITEMS STARTING WITH THE CURRENT TOKEN.
        switch (current_token.Type)
        {
            case TokenType::DATA_TYPE:
            {
                // CHECK IF THE NEXT TOKENS ARE FOR THE START OF A FUNCTION SIGNATURE.
                std::vector<Token> function_signature_start_tokens = token_stream.ConsumeNextTokensIfMatch({ TokenType::IDENTIFIER, TokenType::OPENING_PARENTHESIS });
                bool is_start_of_function_signature = !function_signature_start_tokens.empty();
                if (is_start_of_function_signature)
                {
                    std::printf("Is start of function signature\n");
                    /// @todo Handle parameter lists!
                    std::optional<Token> function_signature_end_token = token_stream.ConsumeNextTokenIfMatch(TokenType::CLOSING_PARENTHESIS);
                    if (function_signature_end_token)
                    {
                        std::printf("Trying to parse block.\n");
                        /// @todo Handle statement ending
                        std::optional<Block> function_body = Block::Parse(token_stream);
                        if (function_body)
                        {
                            std::printf("Function body\n");
                            FunctionDefinition function_definition;
                            function_definition.Header.ReturnType = current_token.Value;
                            constexpr std::size_t FUNCTION_NAME_INDEX = 0;
                            function_definition.Header.Name = function_signature_start_tokens[FUNCTION_NAME_INDEX].Value;
                            
                            /// @todo What if function already declared?
                            program.FunctionsByName[function_definition.Header.Name] = function_definition;
                        }
                    }
                    else
                    {
                        /// @todo Error?
                    }
                }
                
                /*
                function-definition:
                    declaration-specifiers-opt declarator declaration-list-opt compound-statement
                */
                
                break;
            }
        }
    }
    
    return program;
}
