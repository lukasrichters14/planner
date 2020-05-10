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
	}
};


#endif