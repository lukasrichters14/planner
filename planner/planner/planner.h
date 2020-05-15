#pragma once
#ifndef PLANNER_H
#define PLANNER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "structs.h"

using namespace std;

// File path constants.
constexpr auto PLANNER_FILE_PATH = "C:/Users/lukas/OneDrive/Desktop/Planner.txt";
constexpr auto CONFIG_FILE_PATH = "C:/Users/lukas/planner/planner/planner/config.ini";

// Function declarations.
fstream open_file(string f_name);
Config get_config_data(fstream& config_file);
vector<string> str_to_vector(string str, char delim=',');
vector<string> compare_vec(vector<string> v1, vector<string> v2);
Planner read_planner(fstream& planner_file);
void generate_data(Config& config, Planner& planner);
void write_to_config(fstream& config_file, Config& config);
string vector_to_str(vector<string> vec);
void write_to_planner(fstream& planner_file, Planner& planner, vector<string> g_cal_data);
string day_to_str(int day);
bool is_special_month(int month);
void validate_date(int& day, int& date, int& month, int& year);
vector<string> parse_args(int argc, char** argv);

#endif