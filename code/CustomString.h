#pragma once

#include <optional>
#include <string>

struct String
{   
    static std::optional<char> GetCharacterIfExists(const std::string& string, const std::size_t index)
    {
        std::size_t character_count = string.length();
        bool character_exists = (index < character_count);
        if (character_exists)
        {
            char character = string[index];
            return character;
        }
        else
        {
            return std::nullopt;
        }
    }
    
    static bool CharactersMatch(const std::string& string, const std::size_t start_index, const std::string& starting_substring)
    {
        // MAKE SURE ENOUGH CHARACTERS EXIST.
        std::size_t substring_character_count = starting_substring.length();
        constexpr std::size_t FIRST_CHARACTER_ALREADY_COUNTED = 1;
        std::size_t last_character_index = start_index + substring_character_count - FIRST_CHARACTER_ALREADY_COUNTED;
        std::size_t main_string_character_count = string.length();
        bool enough_characters_exist = (last_character_index < main_string_character_count);
        if (!enough_characters_exist)
        {
            return false;
        }
        
        // MAKE SURE THE CHARACTERS AT THE START OF THE MAIN STRING MATCH THE SUBSTRING.
        for (std::size_t substring_index = 0; substring_index < substring_character_count; ++substring_index)
        {
            std::size_t main_string_index = start_index + substring_index;
            char main_string_character = string[main_string_index];
            char substring_character = starting_substring[substring_index];
            bool characters_match = (main_string_character == substring_character);
            if (!characters_match)
            {
                return false;
            }
        }
        
        // INDICATE THAT ALL STARTING CHARACTERS MATCHED.
        // If a character didn't, then we would have returned false earlier.
        return true;
    }
};
