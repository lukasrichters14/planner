#pragma once
#ifndef PLANNER_CONFIG_H
#define PLANNER_CONFIG_H

#include <vector>

/**
* The Config struct is a container for all of the data read from the config file.
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
};


#endif