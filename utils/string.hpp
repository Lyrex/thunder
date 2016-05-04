#ifndef thunder_utils_string_hpp__
#define thunder_utils_string_hpp__

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

namespace thunder
{
	namespace utils
	{
		namespace string
		{
			std::vector<std::string> string_between( const std::string& s_, std::string start_marker, std::string end_marker, bool ignore_case )
			{
				std::vector<std::string> result;

				if ( start_marker.empty() || end_marker.empty() )
					return std::vector<std::string>();

				std::string::size_type start_found = 0;
				std::string::size_type end_found = 0;

				if ( ignore_case )
				{
					std::transform( start_marker.begin(), start_marker.end(), start_marker.begin(), ::tolower );
					std::transform( end_marker.begin(), end_marker.end(), end_marker.begin(), ::tolower );
				}

				do
				{
					start_found = s_.find( start_marker, end_found );
					end_found = s_.find( end_marker, start_found + 1 );

					if ( ( start_found == std::string::npos ) || ( end_found == std::string::npos ) )
						break;

					result.push_back( s_.substr( start_found + start_marker.length(), end_found - start_found - ( end_marker.length() + 1 ) ) );
					end_found++;

				} while ( ( start_found != std::string::npos ) && ( end_found != std::string::npos ) );

				return std::move( result );
			}
		};
	};
};

#endif // thunder_utils_string_hpp__
