///
/// @file trim.hpp
/// @brief Contains ulility functions to remove whitespace from a string 
///
/// @author Lyrex <admin@lyrex.net>
/// @version 1.0 2017/09/04
///

#pragma once

#ifndef thunder_utils_string_trim_hpp__
#define thunder_utils_string_trim_hpp__

#include <algorithm> 
#include <cctype>

#include <string>

/// @namespace thunder
namespace thunder
{
/// @namespace utils
namespace utils
{
/// @namespace string
namespace string
{	
	/// @brief Removes whitespace at the start of a string in place.
	///
    /// @param s reference to the input string. <b>Attention: The input is modified.</b>
	static inline void ltrim_inplace(std::string* s) {
        s->erase(s->begin(), std::find_if(s->begin(), s->end(), [](char ch) {
            return std::isspace(static_cast<unsigned char>(ch)) == 0;
        }));
    }

	/// @brief Removes whitespace at the end of a string in place.
	/// 
	/// @param s reference to the input string. <b>Attention: The input is modified.</b>
    static inline void rtrim_inplace(std::string* s) {
        s->erase(std::find_if(s->rbegin(), s->rend(), [](char ch) {
            return std::isspace(static_cast<unsigned char>(ch)) == 0;
        }).base(), s->end());
    }

	/// @brief Removes whitespace both at the start and at the end of a string in place.
	/// 
	/// @param s reference to the input string. <b>Attention: The input is modified.</b>
    static inline void trim_inplace(std::string* s) {
        ltrim_inplace(s);
        rtrim_inplace(s);
    }

	/// @brief Removes whitespace at the start of a string.\n
	/// 
	/// @param copy input string
	/// @returns The left-side trimmed string
    static inline std::string ltrim(std::string copy) {    	
    	ltrim_inplace(&copy);
        return copy;
    }

	/// @brief Removes whitespace at the end of a string.
	/// 
	/// @param copy input string
	/// @returns The right-side trimmed string
    static inline std::string rtrim(std::string copy) {    	
    	rtrim_inplace(&copy);
        return copy;
    }

	/// @brief Removes whitespace both at the start and at the end of a string. 
	///
	/// @param copy input string
	/// @returns The trimmed string
    static inline std::string trim(std::string copy) {
        trim_inplace(&copy);
        return copy;
    }
}; // namespace string
}; // namespace utils
}; // namespace thunder

#endif // thunder_utils_string_trim_hpp__
