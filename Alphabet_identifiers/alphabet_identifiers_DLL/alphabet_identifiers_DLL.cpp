#include "alphabet_identifiers_DLL.h"

namespace DynamicMathPower
{
    alphabet_identifiers::alphabet_identifiers() {}

    std::string alphabet_identifiers::GenerateNextIdentifier(const std::string& str_id)
    {
        std::string str_id_in = str_id;
        std::string str_id_out;
        if (str_id_in != max_str_id_out)
        {
            parser_string(str_id_in);
            one_discret();
            string_assembly(str_id_out);
        }
        id_accumulation.clear();
        i_vec = 0;
        return str_id_out;
    }

    void alphabet_identifiers::one_discret()
    {
        std::string temp_str;
        if (id_accumulation[i_vec].back() == numbers[len_numbers - 1])
        {
            if (id_accumulation[i_vec].front() != letters[len_letters - 1])
            {
                for (size_t i = 0; i < len_letters; i++)
                    if (id_accumulation[i_vec].front() == letters[i])
                    {
                        temp_str.push_back(letters[i + 1]);
                        temp_str.push_back(numbers[0]);
                        id_accumulation[i_vec] = temp_str;
                        break;
                    }
            }
            else
            {
                if (id_accumulation.size() == i_vec + 1)
                {
                    id_accumulation[i_vec] = "A1";
                    id_accumulation.push_back("A1");
                }
                else
                {
                    id_accumulation[i_vec] = "A1";
                    i_vec++;
                    one_discret();
                }
            }

        }
        else
        {
            for (size_t i = 0; i < len_numbers; i++)
                if (id_accumulation[i_vec].back() == numbers[i])
                {
                    temp_str.push_back(id_accumulation[i_vec].front());
                    temp_str.push_back(numbers[i + 1]);
                    id_accumulation[i_vec] = temp_str;
                    break;
                }

        }
        temp_str.clear();
    }

    void alphabet_identifiers::parser_string(std::string& str_id_in)
    {
        std::string separator{ "-" };
        bool flag = true;
        while (flag)
        {
            size_t start{ str_id_in.rfind(separator) };
            if (str_id_in.length() == 2)
            {
                id_accumulation.push_back(str_id_in);
                flag = false;
            }
            else
            {
                id_accumulation.push_back(str_id_in.substr(start + 1, 2));
                str_id_in = str_id_in.substr(0, str_id_in.length() - 3);
            }
        }
    }

    void alphabet_identifiers::string_assembly(std::string& str_id_out)
    {
        str_id_out.clear();
        for (int i = id_accumulation.size() - 1; i != -1; i--)
        {
            if (i != 0)
            {
                str_id_out += id_accumulation[i];
                str_id_out += "-";
            }
            else { str_id_out += id_accumulation[i]; }
        }
    }

    alphabet_identifiers::~alphabet_identifiers() {}
}