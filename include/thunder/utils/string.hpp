///
/// @file string.hpp
/// @brief Contains ulility functions for string operations
///
/// @author Lyrex <admin@lyrex.net>
/// @version 1.0 2017/09/04
///

#pragma once

#ifndef thunder_utils_string_hpp__
#define thunder_utils_string_hpp__

#include <algorithm>
#include <vector>

#if _HAS_CXX17 && __has_include(<string_view>)
#include <string_view>
#else
#include <string>
#endif

#include "string/trim.hpp"

/// @namespace thunder
namespace thunder
{
/// @namespace utils
namespace utils
{
/// @namespace string
namespace string
{
#if _HAS_CXX17 && __has_include(<string_view>)
	using String_type = std::string_view;
#else
	using String_type = std::string;
#endif

	/// @brief Finds strings that lie between <tt>start_marker</tt> and <tt>end_marker</tt>
	///
	/// @param s input string that gets searched
	/// @param start_marker string that defines the start marker of the search
	/// @param start_marker string that defines the end marker of the search
	/// @param ignore_case set to true if the start and end marker case should be ignored (default: false)
	/// @param keep_empty set to true if empty results should still be keeped and returned in the result vector (default: false)
	///
	/// @returns A vector containing <tt>String_type</tt> with all found results. The vector is empty if there are no results.
	static inline auto between(const String_type& s, std::string start_marker, std::string end_marker, const bool ignore_case = false, const bool keep_empty = false)
	{
		std::vector<String_type> result;

		if (start_marker.empty() || end_marker.empty())
			return std::vector<String_type>();

		if (ignore_case)
		{
			std::transform(start_marker.begin(), start_marker.end(), start_marker.begin(), ::tolower);
			std::transform(end_marker.begin(), end_marker.end(), end_marker.begin(), ::tolower);
		}

		// pre-allocate some memory
		result.resize(s.length() / 8);
		result.reserve(s.length() / 8);

		String_type::size_type start_found = s.find(start_marker, 0);
		String_type::size_type end_found = s.find(end_marker, start_found + 1);

		while ((start_found != String_type::npos) && (end_found != String_type::npos))
		{
			if (keep_empty || (end_found - start_found) > 1)
				result.push_back(s.substr(start_found + start_marker.length(), end_found - start_found - start_marker.length()));

			start_found = s.find(start_marker, end_found + 1);
			end_found = s.find(end_marker, start_found + 1);
		}

		return result;
	}

	/// @brief Splits a string by a delimiter.
	///
	/// @param s input string that gets splitted
	/// @param delimiter string that defines the delmited by which the string gets splitted
	///
	/// @returns A vector containing <tt>String_type</tt> with all found results. The vector is empty if there are no results.
	static inline auto split(const String_type& s, const char* delimiter)
	{
		std::vector<String_type> result;

		String_type::size_type pos = 0;
		String_type::size_type last_pos = 0;

		if (s.empty())
			return result;

		// count substring occurences
		size_t count = 0;
		pos = s.find(delimiter, 0);
		while (pos != std::string::npos)
		{
			++count;
			pos = s.find(delimiter, pos + 1);
		}

		// pre-reserve vector size
		result.resize(count * 4);
		result.reserve(count * 4);

		// split string
		pos = s.find_first_of(delimiter, last_pos);
		while (pos != String_type::npos)
		{
			if (pos != last_pos)
				result.push_back(s.substr(last_pos, pos - last_pos));

			last_pos = pos + 1;
			pos = s.find_first_of(delimiter, last_pos);
		}

		if (last_pos < s.length())
			result.push_back(s.substr(last_pos, s.length() - last_pos));

		return result;
	}

	/// @brief Removes all occurences of <tt>character</tt> in a string in place. <b>Attention: The input is modified.</b>
	///
	/// @param s input string that gets modified
	/// @param character character that gets removed from the string
	static inline void remove_all_inplace(std::string* s, const char character)
	{
		s->erase(std::remove(s->begin(), s->end(), character), s->end());
	}

	/// @brief Removes all occurences of <tt>character</tt> in a string
	///
	/// @param s input string that gets searched
	/// @param character character that gets removed from the string
	///
	/// @returns The string without all <tt>character</tt> occurences.
	static inline auto remove_all(std::string copy, const char character)
	{
		remove_all_inplace(&copy, character);

		return copy;
	}

#if _HAS_CXX17 && __has_include(<string_view>)
	/// @brief Removes all occurences of <tt>character</tt> in a string
	///
	/// @param sv input string view that gets searched
	/// @param character character that gets removed from the string
	///
	/// @returns The string without all <tt>character</tt> occurences.
	static inline auto remove_all(const std::string_view& sv, const char character)
	{
		std::string result{ sv };
		remove_all_inplace(result, character);

		return result;
	}
#endif
}; // namespace string
}; // namespace utils
}; // namespace thunder

#endif // thunder_utils_string_hpp__
