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
	inline auto between(const std::string& s_, std::string start_marker, std::string end_marker, bool ignore_case = false, bool compress = true)
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
				result.emplace_back(s_.substr(start_found + start_marker.length(), end_found - start_found - (end_marker.length())));

			start_found = s_.find(start_marker, end_found + 1);
			end_found   = s_.find(end_marker, start_found + 1);
		}

		return result;
	}

	inline auto split(const std::string& s, const std::string& delimiter, const bool keepEmpty)
	{
        std::vector<std::string> result;

        std::string::size_type pos = 0;
        std::string::size_type lastPos = 0;
        std::string::size_type length = s.length();

        if (s.empty())
            return result;

        while (lastPos < length+1)
        {
            pos = s.find_first_of(delimiter, lastPos);
            if (pos == std::string::npos)
                pos = length;

            if (keepEmpty || pos != lastPos)
                result.emplace_back(s.data() + lastPos, pos - lastPos);

            lastPos = ++pos;
        }

        return result;
	}

    inline auto remove_all(const std::string& s, const char delimiter)
	{
        std::string s_{ s };

        s_.erase(std::remove(s_.begin(), s_.end(), delimiter), s_.end());

        return std::move(s_);
	}
}
}
}

#endif // thunder_utils_string_hpp__
