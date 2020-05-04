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
	vector<string> monday;
	vector<string> tuesday;
	vector<string> wednesday;
	vector<string> thursday;
	vector<string> friday;
	vector<string> saturday;
	vector<string> sunday;
};


#endif