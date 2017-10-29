#ifndef thunder_utils_convert_hex_hpp__
#define thunder_utils_convert_hex_hpp__

#include <array>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace thunder
{
namespace utils
{
namespace convert
{
    class string_to_array
    {
        std::string m_source;

    public:
        explicit string_to_array(const std::string& str)
            : m_source(str)
        { }

        virtual ~string_to_array()
        { }

        void add(const std::string& add_str)
        {
            m_source += add_str;
        }

        std::vector<uint8_t> convert()
        {
            if (m_source.size() == 0)
                return std::move(std::vector<uint8_t>());

            if (m_source.size() % 2)
                m_source.insert(m_source.begin(), '0');

            std::vector<uint8_t> temp;

            for (size_t i = 0; i < (m_source.size() / 2); i++)
            {
                std::array<char, 3> tmp = { 0 };
                memcpy(&tmp, &m_source[i * 2], 2);

                temp.push_back(static_cast<uint8_t>(strtoul(tmp.data(), nullptr, 16)));
            }

            return std::move(temp);
        }
    };
    
    inline auto array_to_string(uint8_t* data, size_t len)
    {
        std::ostringstream ss;
        ss << std::hex;
        for (size_t i = 0; i < len; ++i)
            ss << std::setw(2) << std::setfill('0') << static_cast<uint32_t>(data[i]);
        return std::move(ss.str());
    }

    inline auto array_to_string(int8_t* data, size_t len)
    {
        std::ostringstream ss;
        ss << std::hex;
        for (size_t i = 0; i < len; ++i)
            ss << std::setw(2) << std::setfill('0') << static_cast<uint32_t>(data[i]);
        return std::move(ss.str());
    }
}; // namespace convert
}; // namespace utils
}; // namespace thunder

#endif // thunder_utils_convert_hex_hpp__
