#include <cstdio>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "GrammarAnalysis/AbstractSyntaxTree.cpp"
#include "Tokenization/Tokenizer.cpp"

using namespace TOKENIZATION;

const std::string SOURCE_CODE_OLD = R"(
int main()
{
    /* Single-line multi-line comment */
    /*
        Multi-line
        comment
     */

    int your_variable_1 = 1;
    int your_variable_2 = 2;
    int your_result = your_variable_1 / your_variable_2;

    return 0;
}
)";

const std::string SOURCE_CODE = R"(
int main()
{
    return 0;
}
)";

int main(const int command_line_argument_count, const char* command_line_arguments[])
{
    // Source code -> Tokenizer -> TokenStream -> GrammarAnalysisAlgorithm -> AbstractSyntaxTree -> Code Generator -> Assembly Code
    
    std::printf("Starting compiler...\n");
    
    TokenStream token_stream = Tokenizer::Tokenize(SOURCE_CODE);

    std::printf("\nTokens:\n");
    for (const Token& token : token_stream.Tokens)
    {
        /// @todo   Token type strings!
        std::printf("%d = %s\n", token.Type, token.Value.c_str());
    }

    Program program = Parse(token_stream);
    
    for (const auto& [function_name, function_definition] : program.FunctionsByName)
    {
        std::printf("Function %s returning %s", function_definition.Header.Name.c_str(), function_definition.Header.ReturnType.c_str());
    }
    
    std::printf("\nExiting...\n");
    return 0;
}
