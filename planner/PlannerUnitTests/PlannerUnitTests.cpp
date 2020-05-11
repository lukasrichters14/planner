#include "pch.h"
#include "CppUnitTest.h"
#include "../planner/planner.h"
#include "../planner/structs.h"
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
			std::string test = "hello, world";
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

		TEST_METHOD(TestGetConfigData)
		{
			std::fstream file = open_file(CONFIG_FILE_PATH);
			Config data, solution;

			solution.monday = { "STT Lecture"};
			solution.tuesday = { "331 homework" };
			solution.wednesday = { "320 homework" };
			solution.thursday = { "PHY homework" };
			solution.friday = { "Nothing :)" };
			solution.saturday = { "Read" };
			solution.sunday = { "Nothing again :))" };
			solution.monday_done = { "STT Lecture" };

			data = get_config_data(file);

			file.close();

			Assert::AreEqual(data.monday, solution.monday);
			Assert::AreEqual(data.tuesday, solution.tuesday);
			Assert::AreEqual(data.wednesday, solution.wednesday);
			Assert::AreEqual(data.thursday, solution.thursday);
			Assert::AreEqual(data.friday, solution.friday);
			Assert::AreEqual(data.saturday, solution.saturday);
			Assert::AreEqual(data.sunday, solution.sunday);
		}

		TEST_METHOD(TestReadPlanner) 
		{
			std::fstream file = open_file(PLANNER_FILE_PATH);
			Planner data, solution;

			solution.monday = { "Stuff1", "Stuff2" };
			solution.tuesday = { "Stuff3" };
			solution.wednesday = { "Stuff4" };
			solution.thursday = { "Stuff5" };
			solution.friday = { "Stuff6" };
			solution.saturday = { "Stuff7" };
			solution.sunday = { "Stuff8" };

			data = read_planner(file);

			file.close();

			Assert::AreEqual(data.monday, solution.monday);
			Assert::AreEqual(data.tuesday, solution.tuesday);
			Assert::AreEqual(data.wednesday, solution.wednesday);
			Assert::AreEqual(data.thursday, solution.thursday);
			Assert::AreEqual(data.friday, solution.friday);
			Assert::AreEqual(data.saturday, solution.saturday);
			Assert::AreEqual(data.sunday, solution.sunday);
		}

		TEST_METHOD(TestVectorToString)
		{
			std::vector<std::string> vec = { "Luke", "I", "am", "your", "father" };
			std::string str = "Luke, I, am, your, father";
			Assert::AreEqual(str, vector_to_str(vec));
		}

		TEST_METHOD(TestValidateDate)
		{
			int day, date, month, year, day_a, date_a, month_a, year_a;
			// Regular date, nothing should happen.
			day = 1;
			day_a = 1;
			date = 11;
			date_a = 11;
			month = 4;
			month_a = 4;
			year = 2020;
			year_a = 2020;
			validate_date(day, date, month, year);
			Assert::AreEqual(day, day_a);
			Assert::AreEqual(date, date_a);
			Assert::AreEqual(month, month_a);
			Assert::AreEqual(year, year_a);

			// Leap year in February, on February 29th 2020, should be a valid date.
			day = 6;
			day_a = 6;
			date = 29;
			date_a = 29;
			month = 1;
			month_a = 1;
			year = 2020;
			year_a = 2020;
			validate_date(day, date, month, year);
			Assert::AreEqual(day, day_a);
			Assert::AreEqual(date, date_a);
			Assert::AreEqual(month, month_a);
			Assert::AreEqual(year, year_a);

			// Not a leap year in February, on February 29th 2019, should not be a valid date.
			day = 6;
			day_a = 6;
			date = 29;
			date_a = 1;
			month = 1;
			month_a = 2;
			year = 2019;
			year_a = 2019;
			validate_date(day, date, month, year);
			Assert::AreEqual(day, day_a);
			Assert::AreEqual(date, date_a);
			Assert::AreEqual(month, month_a);
			Assert::AreEqual(year, year_a);

			// New year. December 32nd, 2020, should not be a valid date.
			day = 6;
			day_a = 6;
			date = 32;
			date_a = 1;
			month = 11;
			month_a = 0;
			year = 2020;
			year_a = 2021;
			validate_date(day, date, month, year);
			Assert::AreEqual(day, day_a);
			Assert::AreEqual(date, date_a);
			Assert::AreEqual(month, month_a);
			Assert::AreEqual(year, year_a);

			// June 31st, 2020, not a valid date.
			day = 6;
			day_a = 6;
			date = 31;
			date_a = 1;
			month = 5;
			month_a = 6;
			year = 2020;
			year_a = 2020;
			validate_date(day, date, month, year);
			Assert::AreEqual(day, day_a);
			Assert::AreEqual(date, date_a);
			Assert::AreEqual(month, month_a);
			Assert::AreEqual(year, year_a);

			// July 31st, 2020, valid date.
			day = 6;
			day_a = 6;
			date = 31;
			date_a = 31;
			month = 6;
			month_a = 6;
			year = 2020;
			year_a = 2020;
			validate_date(day, date, month, year);
			Assert::AreEqual(day, day_a);
			Assert::AreEqual(date, date_a);
			Assert::AreEqual(month, month_a);
			Assert::AreEqual(year, year_a);
		}
	};
}
