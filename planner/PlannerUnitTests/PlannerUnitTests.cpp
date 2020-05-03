#include "pch.h"
#include "CppUnitTest.h"
#include "../planner/planner.h"
#include "../planner/config.h"
#include "../planner/tostrings.h"
#include <vector>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlannerUnitTests
{
	TEST_CLASS(PlannerUnitTests)
	{
	public:
		TEST_METHOD(TestOpenFile)
		{
			bool err = false;


			// Open planner file.
			try {
				std::fstream planner = open_file(PLANNER_FILE_PATH);
			}
			catch (std::string) {
				err = true;
				Logger::WriteMessage("The Planner file was unable to be opened.");
			}
			Assert::IsFalse(err);

			// Open config file.
			err = false;
			try {
				std::fstream config = open_file(CONFIG_FILE_PATH);
			}
			catch (std::string) {
				err = true;
				Logger::WriteMessage("The Config file was unable to be opened.");
			}
			Assert::IsFalse(err);
			
			// Open file that doesn't exist.
			err = false;
			try {
				std::fstream fake = open_file("DNE.txt");
			}
			catch (std::string) {
				err = true;
				Logger::WriteMessage("The file that does not exist was unable to be opened.");
			}
			Assert::IsTrue(err); // Error should be thrown.
		}

		TEST_METHOD(TestStringToVector)
		{
			// String with ',' delimeter.
			std::string test = "hello,world";
			std::vector<std::string> solution, subject;
			solution.push_back("hello");
			solution.push_back("world");
			subject = str_to_vector(test);
			Assert::AreEqual(subject, solution);
		}

		TEST_METHOD(TestCompareVec)
		{
			// Two vectors with one entry in common.
			std::vector<std::string> solution, subject, v1, v2, v3, v4;
			solution.push_back("lecture");
			solution.push_back("homework");
			v1.push_back("lecture");
			v1.push_back("homework");
			v1.push_back("exam");
			v2.push_back("exam");
			subject = compare_vec(v1, v2);
			Assert::AreEqual(subject, solution);

			// Two vectors with no entries in common.
			solution = v1;
			v3.push_back("study");
			subject = compare_vec(v1, v3);
			Assert::AreEqual(subject, solution);

			// Empty done vector.
			solution = v1;
			subject = compare_vec(v1, v4);
			Assert::AreEqual(subject, solution);
		}
	};
}
