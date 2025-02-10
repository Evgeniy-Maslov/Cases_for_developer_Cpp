#pragma once
#ifdef alphabet_identifiers_DLL_EXPORTS
#define alphabet_identifiers_DLL __declspec(dllexport)
#else
#define alphabet_identifiers_DLL __declspec(dllimport)
#endif
#include <string>
#include <vector>


namespace DynamicMathPower
{
	class alphabet_identifiers
	{
		std::string max_str_id_out{ "Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9" };
		std::vector<std::string> id_accumulation;
		std::string numbers{ "123456789" };
		size_t len_numbers = numbers.length();
		std::string letters{ "ABCEHIKLNOPRSTUWXYZ" };
		size_t len_letters = letters.length();
		size_t i_vec = 0;

		void one_discret();
		void parser_string(std::string& str_id_in);
		void string_assembly(std::string& str_id_out);
	public:
		alphabet_identifiers_DLL alphabet_identifiers();
		alphabet_identifiers_DLL std::string GenerateNextIdentifier(const std::string& str_id);
		alphabet_identifiers_DLL ~alphabet_identifiers();
	};
}