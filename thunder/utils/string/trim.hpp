///
/// @file trim.hpp
/// @brief Purpose: Ulility functions to remove whitespace from a string 
///
/// @author Lyrex <admin@lyrex.net>
/// @version 1.0 2017/09/04
///

#ifndef thunder_utils_string_trim_hpp__
#define thunder_utils_string_trim_hpp__

#include <algorithm> 
#include <cctype>

#if _HAS_CXX17 && __has_include(<string_view>)
#include <string_view>
#else
#include <string>
#endif

/// @namespace thunder
namespace thunder
{
/// @namespace utils
namespace utils
{
/// @namespace string
namespace string
{	
	/// @fn ltrim_inplace
	/// @brief Removes whitespace at the start of a string in place.
	/// 
    /// @param s Reference to the input string. Attention: The input is modified.
	static inline void ltrim_inplace(std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
    }

	/// @fn rtrim_inplace
	/// @brief Removes whitespace at the end of a string in place.
	/// 
	/// @param s Reference to the input string. Attention: The input is modified.
    static inline void rtrim_inplace(std::string& s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

	/// @fn trim_inplace
	/// @brief Removes whitespace both at the start and at the end of a string in place.
	/// 
	/// @param s Reference to the input string. Attention: The input is modified.
    static inline void trim_inplace(std::string &s) {
        ltrim_inplace(s);
        rtrim_inplace(s);
    }

	/// @fn ltrim
	/// @brief Removes whitespace at the start of a string.
	/// 
	/// @param copy Input string
	///
	/// @return The trimmed string
    static inline std::string ltrim(std::string copy) {    	
    	ltrim_inplace(copy);
        return copy;
    }

	/// @fn rtrim
	/// @brief Removes whitespace at the end of a string.
	/// 
	/// @param copy Input string
	///
	/// @return The trimmed string
    static inline std::string rtrim(std::string copy) {    	
    	rtrim_inplace(copy);
        return copy;
    }

	/// @fn trim
	/// @brief Removes whitespace both at the start and at the end of a string.
	/// 
	/// @param copy Input string
	///
	/// @return The trimmed string
    static inline std::string trim(std::string copy) {
        trim_inplace(copy);
        return copy;
    }
}
}
}

#endif // thunder_utils_string_trim_hpp__
