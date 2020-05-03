#pragma once
#ifndef PLANNER_H
#define PLANNER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "config.h"

using namespace std;

// File path constants.
constexpr auto PLANNER_FILE_PATH = "C:/Users/lukas/OneDrive/Desktop/Planner.txt";
constexpr auto CONFIG_FILE_PATH = "C:/Users/lukas/planner/planner/planner/config.ini";

// Function declarations.
fstream open_file(string f_name);
Config get_config_data(fstream &config_file);
vector<string> str_to_vector(string str, char delim=',');
vector<string> compare_vec(vector<string> day, vector<string> done);

#endif