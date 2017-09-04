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

namespace thunder
{
namespace utils
{
namespace string
{
#if _HAS_CXX17 && __has_include(<string_view>)
	using String_type = std::string_view;
#else
	using String_type = std::string;
#endif

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

	static inline auto remove_all(const String_type& s, const char delimiter)
	{
		std::string result{ s };

		result.erase(std::remove(result.begin(), result.end(), delimiter), result.end());

		return result;
	}
}
}
}

#endif // thunder_utils_string_hpp__
