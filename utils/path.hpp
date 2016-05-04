#ifndef thunder_utils_path_hpp__
#define thunder_utils_path_hpp__

#include <iostream>

#if defined(_WIN32)
#include <direct.h>
#include <windows.h>
#elif defined(__linux__) || defined(__CYGWIN__)
#include <limits.h>
#include <unistd.h>
#define HINSTANCE unsigned int
#else
#error This OS is currently not supported
#endif

namespace thunder
{
	namespace utils
	{
		namespace path
		{
			inline std::string get_executable_path(HINSTANCE instance = nullptr)
			{
#if defined(_WIN32)
				char buffer[ MAX_PATH ] = { 0 };
#elif defined(__linux__) || defined(__CYGWIN__)
				char buffer[ PATH_MAX ] = { 0 };
#endif

#if defined(_WIN32)
				if (::GetModuleFileNameA(instance, buffer, MAX_PATH) == 0)
#elif defined(__linux__) || defined(__CYGWIN__)
				if (::readlink("/proc/self/exe", buffer, PATH_MAX) == -1)
#endif
					std::cerr << "error while getting executable path" << std::endl;

				auto executable_path = std::string(buffer);
				auto executable_directory = executable_path.substr(0, executable_path.find_last_of("\\"));

				return std::move(executable_directory);
			}

			inline std::string get_working_directory()
			{
#if defined(_WIN32)
				constexpr auto pathlen = MAX_PATH;
#elif defined(__linux__) || defined(__CYGWIN__)
				constexpr auto pathlen = PATH_MAX;
#endif
				std::string working_directory = "";
				char buffer[ pathlen ] = { 0 };
				
#if defined(_WIN32)
				if ( ::_getcwd(buffer, MAX_PATH) != nullptr )
					working_directory = std::string( buffer );
#elif defined(__linux__) || defined(__CYGWIN__)
				if ( ::getcwd(buffer, PATH_MAX) != nullptr )
					working_directory = std::string(buffer);
#endif
				else
					std::cerr << "could not get working directory" << std::endl;

				return std::move(working_directory);
			}
		};
	};
};

#endif // thunder_utils_path_hpp__

