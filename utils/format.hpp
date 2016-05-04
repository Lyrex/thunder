#ifndef PUTILS_FORMAT_HPP__
#define PUTILS_FORMAT_HPP__

#include <string>
#include <ostream>
#include <memory>
#include <exception>
#include <utility>

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/format.hpp>

namespace padmak
{
namespace utils
{
namespace format
{
	template<class ostream>
	class basic_format
	{
	public:
		basic_format( ostream& os, const std::string& format_str )
			: m_os(os), m_format( format_str )
		{
			// ensures 'os' has 'std::basic_ostream<char>' as base class
			static_cast<std::basic_ostream<char>&>( os );
		}

		void format()
		{
		}

		template<typename T, typename ... Ts>
		void format( const T& item, const Ts& ... ts )
		{
			m_format % item;

			if (sizeof...( ts ) > 0)
				format( ts ... );
		}

		void finalize()
		{
			m_os << boost::str( m_format ) << std::flush;
		}
	private:
		ostream& m_os;
		boost::format m_format;
	};
	/*
		* provides an easy-to-use wrapper to format data directly to an ostream
		*/
	template<class ostream, class ... T>
	static void static_format( ostream& ostr, const std::string& format, T&& ... args )
	{
		utils::format::basic_format<ostream> sf( ostr, format );
		// enables perfect forwarding
		sf.format( std::forward<T>( args ) ... );
		sf.finalize();
	}

	/*
		* provides an easy-to-use wrapper to format data to a string which
		* will be returned
		*/
	template<class... T>
	static std::string static_format_string( const std::string& format, T&& ... args )
	{
		std::ostringstream oss;
		utils::format::basic_format<std::ostringstream> sf( oss, format );
		// provides perfect forwarding
		sf.format( std::forward<T>(args) ... );
		sf.finalize();
		return oss.str();
	}
};
};
};
/*
 * Example-code
 */
/*
int main(int argc, const char * argv[])
{
	std::ostringstream f;
	utils::basic_format<std::ostringstream> o(f, "%s %.2X %s %.2X");
	o.format( "hello", 0x12, "meow", 8 );
	o.finalize();
	std::cout << f.str() << std::endl;
	
	std::ostringstream g;
	utils::static_format( g, "%s", "even more tests");
	std::cout << g.str() << std::endl;
	
	int bla = 3;
	utils::static_format( std::cout, "%d %s\n", 3, "rd test to cout");
	
	std::string str = utils::static_format_string("%d%s", 4, "th test");
	std::cout << str  << std::endl;
	return 0;
}
*/

#endif // PUTILS_FORMAT_HPP__
