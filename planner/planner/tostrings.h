#pragma once
#ifndef TO_STRINGS_H
#define TO_STRINGS_H

#include "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/VS/UnitTest/include/CppUnitTest.h"
#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include "structs.h"

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> std::wstring ToString<std::vector<std::string>>(const std::vector<std::string>& v) 
			{ 
				std::string temp_str;
				int i = 0;

				// Create string from vector.
				for (auto s : v) {
					if (i > 0) {
						temp_str += ", ";
					}
					temp_str += s;
					++i;
				}
				// Convert string to wstring.
				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
				std::wstring wide = converter.from_bytes(temp_str);
				return wide;
			}

			template<> inline std::wstring ToString<Config>(const Config& t) { return L"config"; }
		}
	}
}

#endif