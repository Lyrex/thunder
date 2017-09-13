#ifndef thunder_utils_xorstr_hpp__
#define thunder_utils_xorstr_hpp__

namespace thunder
{
namespace utils
{
namespace xorstr
{
template <int __XORSTR_START, size_t __XORSTR__BUFLEN, size_t __XORSTR__XREFKILLER>
class XorStr
{
private:
	XorStr() = default;
public:
	char s[__XORSTR__BUFLEN];

	explicit XorStr(const char* xs);

#ifdef NDEBUG
	~XorStr()
	{
		// clear string from stack
		for (size_t i = 0; i<__XORSTR__BUFLEN; ++i)
			s[i] = 0;
	}
#endif
};

template <int __XORSTR_START, size_t __XORSTR__BUFLEN, size_t __XORSTR__XREFKILLER>
XorStr<__XORSTR_START, __XORSTR__BUFLEN, __XORSTR__XREFKILLER>::XorStr(const char* xs)
{
	int xvalue = __XORSTR_START;

	for (size_t i = 0; i<(__XORSTR__BUFLEN-1); ++i)
	{
		s[i] = xs[i - __XORSTR__XREFKILLER] ^ xvalue;
		xvalue += 1;
		xvalue %= 256;
	}

	s[__XORSTR__BUFLEN - 1] = 0;
}

};
};
};

#endif // thunder_utils_xorstr_hpp__