#include <iostream>
#include <chrono>

#include "string.hpp"

int main( int, char** )
{
	const std::string test_1{ R"token123(mw.loader.implement("user.options",function(){mw.user.options.set({"ccmeonemails":0,"cols":80,"date":"default","diffonly":0,"disablemail":0,"disablesuggest":0,"editfont":"default","editondblclick":0,"editsection":0,"editsectiononrightclick":0,"enotifminoredits":0,"enotifrevealaddr":0,"enotifusertalkpages":1,"enotifwatchlistpages":0,"extendwatchlist":0,"externaldiff":0,"externaleditor":0,"fancysig":0,"forceeditsummary":0,"gender":"unknown","hideminor":0,"hidepatrolled":0,"imagesize":2,"justify":0,"math":1,"minordefault":0,"newpageshidepatrolled":0,"nocache":0,"noconvertlink":0,"norollbackdiff":0,"numberheadings":0,"previewonfirst":0,"previewontop":1,"quickbar":5,"rcdays":7,"rclimit":50,"rememberpassword":0,"rows":25,"searchlimit":20,"showhiddencats":0,"showjumplinks":1,"shownumberswatching":1,"showtoc":0,"showtoolbar":1,"skin":"cppreference2","stubthreshold":0,"thumbsize":2,"underline":2,"uselivepreview":0,"usenewrc":0,"watchcreations":0,"watchdefault":0,"watchdeletion":0,)token123" };

	std::vector<std::string> res;

	auto start_time = std::chrono::high_resolution_clock::now();
	for (auto i = 0; i < 1000; i++)
		res = thunder::utils::string::between(test_1, "\"", "\"", true, true);

	auto end_time = std::chrono::high_resolution_clock::now();
	
	std::cout << "Found " << res.size() << " elements!\n";
//	 for (auto& element : res)
//		std::cout << element.c_str() << "\n";
	std::cout << "thunder::utils::string::between took " << std::chrono::duration_cast<std::chrono::milliseconds>( end_time - start_time ).count() << "ms" << std::endl;

	std::cin.get();

	return 0;
}
