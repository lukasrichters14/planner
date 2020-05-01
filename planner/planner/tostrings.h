#pragma once
#ifndef TO_STRINGS_H
#define TO_STRINGS_H

#include "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/VS/UnitTest/include/CppUnitTest.h"
#include <string>
#include <vector>
#include "config.h"

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> inline std::wstring ToString<std::vector<std::string>>(const std::vector<std::string>& t) { return L"vector"; }
			template<> inline std::wstring ToString<Config>(const Config& t) { return L"config"; }
		}
	}
}

#endif