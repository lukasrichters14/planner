#pragma once
#ifndef PLANNER_H
#define PLANNER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "config.h"

// File path constants.
constexpr auto PLANNER_FILE_PATH = "C:/Users/lukas/OneDrive/Desktop/planner.txt";
constexpr auto CONFIG_FILE_PATH = "config.ini";

// Function definitions.
fstream open_file(string f_name);
Config get_config_data(fstream &config_file);
vector<string> str_to_vector(string str, char delim=',');
vector<string> compare_vec(vector<string> day, vector<string> done);

#endif