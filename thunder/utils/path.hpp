#ifndef thunder_utils_path_hpp__
#define thunder_utils_path_hpp__

#include <array>
#include <stdexcept>

#if defined(WIN32) || defined(_WIN32) 
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
	constexpr char path_separator() noexcept
	{
#if defined(WIN32) || defined(_WIN32) 
		return '\\';
#else
		return '/';
#endif
	}

    inline auto get_executable_path(HINSTANCE instance = nullptr)
    {
#if defined(WIN32) || defined(_WIN32) 
        constexpr auto pathlen = MAX_PATH;
#elif defined(__linux__) || defined(__CYGWIN__)
        constexpr auto pathlen = PATH_MAX;
#endif
        std::array<char, pathlen> buffer = { 0 };

#if defined(WIN32) || defined(_WIN32) 
        if (::GetModuleFileNameA(instance, buffer.data(), pathlen) == 0)
#elif defined(__linux__) || defined(__CYGWIN__)
        if (::readlink("/proc/self/exe", buffer, pathlen) == -1)
#endif
            throw std::runtime_error("error while getting executable path");

        const std::string executable_path{ buffer.data() };
        const std::string executable_directory{ executable_path.substr(0, executable_path.find_last_of(path_separator())) };

        return executable_directory + path_separator();
    }

    inline auto get_working_directory()
    {
#if defined(WIN32) || defined(_WIN32) 
        constexpr auto pathlen = MAX_PATH;
#elif defined(__linux__) || defined(__CYGWIN__)
        constexpr auto pathlen = PATH_MAX;
#endif
        std::string working_directory;
        std::array<char, pathlen> buffer = { 0 };
                
#if defined(WIN32) || defined(_WIN32) 
        if ( ::_getcwd(buffer.data(), MAX_PATH) != nullptr )
			working_directory = std::string{ buffer.data() };
#elif defined(__linux__) || defined(__CYGWIN__)
        if ( ::getcwd(buffer, PATH_MAX) != nullptr )
            working_directory = std::string{ buffer.data() };
#endif
        else
            throw std::runtime_error("could not get working directory");

        return working_directory + path_separator();
    }
};
};
};

#endif // thunder_utils_path_hpp__
