#ifndef thunder_utils_convert_hex_hpp__
#define thunder_utils_convert_hex_hpp__

#include <string>
#include <vector>
#include <cstdlib>

namespace thunder
{
	namespace utils
	{
		namespace convert
		{
			class string_to_array
			{
			private:
				std::string m_source;

			public:
				explicit string_to_array(const std::string& str)
					: m_source(str)
				{
				}

				virtual ~string_to_array()
				{
				}

				void add(const std::string& add_str)
				{
					m_source += add_str;
				}

				void convert(std::vector<uint8_t>& out_buf)
				{
					if (m_source.size() == 0)
						return;

					if (m_source.size() % 2)
						m_source.insert(m_source.begin(), '0');

					out_buf.clear();

					for (auto i = 0; i < (m_source.size() / 2); i++)
					{
						char tmp[ 3 ] = {};
						memcpy(&tmp, &m_source[i * 2], 2);

						out_buf.push_back(static_cast<uint8_t>(strtoul(tmp, nullptr, 16)));
					}
				}
			};
		};
	};
};

#endif // thunder_utils_convert_hex_hpp__

