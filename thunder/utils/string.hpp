#ifndef thunder_utils_string_hpp__
#define thunder_utils_string_hpp__

#include <vector>
#include <algorithm>

namespace thunder
{
namespace utils
{
namespace string
{
	inline std::vector<std::string> between(const std::string& s_, std::string start_marker, std::string end_marker, bool ignore_case = false, bool compress = true)
	{
		std::vector<std::string> result;

		if (start_marker.empty() || end_marker.empty())
			return std::vector<std::string>();

		if (ignore_case)
		{
			std::transform(start_marker.begin(), start_marker.end(), start_marker.begin(), ::tolower);
			std::transform(end_marker.begin(), end_marker.end(), end_marker.begin(), ::tolower);
		}


		std::string::size_type start_found = s_.find(start_marker, 0);
		std::string::size_type end_found   = s_.find(end_marker, start_found + 1);

		while ((start_found != std::string::npos) && (end_found != std::string::npos))
		{
			if (!compress || (end_found - start_found) > 1 )
				result.push_back(s_.substr(start_found + start_marker.length(), end_found - start_found - (end_marker.length())));

			start_found = s_.find(start_marker, end_found + 1);
			end_found   = s_.find(end_marker, start_found + 1);
		}

		return std::move(result);
	}

	inline std::vector<std::string> split(const std::string& s, const std::string& delimiter, const bool compress)
	{
		std::vector<std::string> result;

		if (delimiter.empty())
			return std::move(std::vector<std::string>{ s });

		auto start = s.begin();
		auto end = search(start, s.end(), delimiter.begin(), delimiter.end());
				
		while (end != s.end())
		{
			if (!compress || start != end)
				result.push_back({ start, end });

			if (end != s.end())
				start = end + delimiter.size();

			end = search(start, s.end(), delimiter.begin(), delimiter.end());
		}

		return std::move(result);
	}
};
};
};

#endif // thunder_utils_string_hpp__
