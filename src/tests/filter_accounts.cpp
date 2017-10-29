#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

#if _HAS_CXX17
#include <string_view>
#else
#include <string>
#endif

#if defined(WIN32) && !defined(FMT_HEADER_ONLY)
#define FMT_HEADER_ONLY
#endif

#include <fmt/format.h>

#include <thunder/utils/string.hpp>

int main(int /*argc*/, char** /*argv*/)
{
	std::ifstream account_sql{ R"(C:\undergroundmt2_account.sql)", std::ios::in | std::ios::binary };
	std::ofstream filtered_account_sql{ R"(C:\undergroundmt2_account_filtered.sql)", std::ios::out | std::ios::binary };
	if (!account_sql.is_open())
		return 1;

	// for a bit of efficiency
	account_sql.seekg(0, account_sql.end);
	const auto len = account_sql.tellg();
	account_sql.seekg(0, account_sql.beg);

	std::vector<char> data_vec(len);
	account_sql.read(data_vec.data(), len);

	auto lines = thunder::utils::string::split(data_vec.data(), "\r\n");

	fmt::MemoryWriter w;

	for (auto&& line: lines)
	{
		auto query_data = thunder::utils::string::between(line, "INSERT INTO account VALUES (", ");");
		if (query_data.empty())
			continue;

		auto split_data = thunder::utils::string::between(query_data[0], "'", "', ", false, false);
		
		if (split_data.size() < 6)
			continue;

		w.write("INSERT INTO account (id, login, password, email) VALUES ('{}', '{}', '{}', '{}');\n", std::string(split_data[0]), std::string(split_data[1]), std::string(split_data[2]), std::string(split_data[5]));
	}

	filtered_account_sql << w.str();
	filtered_account_sql.flush();

	filtered_account_sql.close();

	std::cout << "finished. press enter to close" << std::endl;

	std::cin.get();
	
	return 0;
}
