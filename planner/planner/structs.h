#pragma once
#ifndef PLANNER_CONFIG_H
#define PLANNER_CONFIG_H

#include <vector>
#include <string>

using namespace std;

/**
* The Config struct is a container for all of the data for the config file.
*/
struct Config 
{
	vector<string> monday;
	vector<string> tuesday;
	vector<string> wednesday;
	vector<string> thursday;
	vector<string> friday;
	vector<string> saturday;
	vector<string> sunday;

	vector<string> monday_done;
	vector<string> tuesday_done;
	vector<string> wednesday_done;
	vector<string> thursday_done;
	vector<string> friday_done;
	vector<string> saturday_done;
	vector<string> sunday_done;
};


/**
* The Planner struct is a container for all of the data for the planner file.
*/
struct Planner
{
	string first;
	vector<string> monday;
	vector<string> tuesday;
	vector<string> wednesday;
	vector<string> thursday;
	vector<string> friday;
	vector<string> saturday;
	vector<string> sunday;

	// Member functions.

	/**
	Returns the vector at the given day.
	day: [string] the day to get the vector at.
	Return: [vector<string>] the vector at the given day.
	*/
	vector<string> get_day(string day) {
		if (day == "MON") {
			return monday;
		}
		else if (day == "TUE") {
			return tuesday;
		}
		else if (day == "WED") {
			return wednesday;
		}
		else if (day == "THU") {
			return thursday;
		}
		else if (day == "FRI") {
			return friday;
		}
		else if (day == "SAT") {
			return saturday;
		}
		else if (day == "SUN") {
			return sunday;
		}
		return {};
	}

	/**
	Appends the elements of to_append to the given day.
	day: [string] the day to append to.
	to_append: [vector<string>] the elements to append.
	*/
	void append_day(string day, vector<string> to_append) {
		if (day == "MON") {
			for (auto e : to_append) {
				monday.push_back(e);
			}
		}
		else if (day == "TUE") {
			for (auto e : to_append) {
				tuesday.push_back(e);
			}
		}
		else if (day == "WED") {
			for (auto e : to_append) {
				wednesday.push_back(e);
			}
		}
		else if (day == "THU") {
			for (auto e : to_append) {
				thursday.push_back(e);
			}
		}
		else if (day == "FRI") {
			for (auto e : to_append) {
				friday.push_back(e);
			}
		}
		else if (day == "SAT") {
			for (auto e : to_append) {
				saturday.push_back(e);
			}
		}
		else if (day == "SUN") {
			for (auto e : to_append) {
				sunday.push_back(e);
			}
		}
	}
};


#endif