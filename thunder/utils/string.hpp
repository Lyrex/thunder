#ifndef thunder_utils_string_hpp__
#define thunder_utils_string_hpp__

#include <vector>
#include <algorithm>

#include <string_view>

namespace thunder
{
namespace utils
{
namespace string
{
    inline auto between(const std::string_view& s_, std::string start_marker, std::string end_marker, bool ignore_case = false, bool compress = true)
    {
        std::vector<std::string_view> result;

        if (start_marker.empty() || end_marker.empty())
            return std::vector<std::string_view>();

        if (ignore_case)
        {
            std::transform(start_marker.begin(), start_marker.end(), start_marker.begin(), ::tolower);
            std::transform(end_marker.begin(), end_marker.end(), end_marker.begin(), ::tolower);
        }

        std::string_view::size_type start_found = s_.find(start_marker, 0);
        std::string_view::size_type end_found   = s_.find(end_marker, start_found + 1);

        while ((start_found != std::string_view::npos) && (end_found != std::string_view::npos))
        {
            if (!compress || (end_found - start_found) > 1 )
                result.emplace_back(s_.substr(start_found + start_marker.length(), end_found - start_found - (end_marker.length())));

            start_found = s_.find(start_marker, end_found + 1);
            end_found   = s_.find(end_marker, start_found + 1);
        }

        return std::move(result);
    }

    inline auto split(const std::string_view& s, const char* delimiter)
    {
        std::vector<std::string_view> result;

        std::string_view::size_type pos = 0;
        std::string_view::size_type last_pos = 0;

        if (s.empty())
            return result;

        pos = s.find_first_of(delimiter, last_pos);
        while (pos != std::string_view::npos)
        {
            if (pos != last_pos)
                result.emplace_back(s.substr(last_pos, pos - last_pos));

            last_pos = pos + 1;
            pos = s.find_first_of(delimiter, last_pos);
        }

        if (last_pos < s.length())
            result.emplace_back(s.substr(last_pos, s.length() - last_pos));

        return std::move(result);
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
