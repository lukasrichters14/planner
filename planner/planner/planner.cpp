#pragma once
#include "planner.h"
#include "structs.h"
using namespace std;

/**
Safely opens the file with the given file name.
f_name: [string] the full path name of the file to open.
Return: [fstream] the file stream of the opened file.
*/
fstream open_file(string f_name)
{
	fstream file;
	file.open(f_name);  // Open the file.

	// Provide an error message if the file fails to open.
	if (file.fail()) {
		throw "The file " + f_name + " could not be opened.";
	}

	return file;
}


/**
Converts a string to a vector.
str: [string] the string to convert to a vector.
delim: [char] the delimeter to use to seperate entries.
Return: [vector<string>] the vector representation of the string.
*/
vector<string> str_to_vector(string str, char delim)
{
	vector<string> str_vec;

	// Nothing do do for an empty string.
	if (str.empty()) { 
		return str_vec;
	}

	string temp_str;
	bool delim_found = false;
	for (char ch : str) {
		// Add all characters before the delimeter to the string.
		if (ch != delim) {
			// Allow for spaces between the delimeter and the next string.
			if (!(delim_found && ch == ' ')) {
				temp_str += ch;
				delim_found = false;
			}
		}
		
		// Once the delimeter is found, add the string to the vector.
		else { 
			str_vec.push_back(temp_str); 
			temp_str = "";
			delim_found = true;
		}
	}
	// Add the last element that was not added in the loop.
	str_vec.push_back(temp_str);

	return str_vec;
}


/**
Compares two vectors and returns everything in vector 1 that is not in vector 2.
v1: [vector<string>] the first vector.
v2: [vector<string>] the second vector.
Return: [vector<string>] vector1 - vector2 (set difference).
*/
vector<string> compare_vec(vector<string> v1, vector<string> v2)
{
	// Nothing to do with an empty comparison vector.
	if (v2.empty()) { return v1; }

	vector<string> ret_vec;
	bool found = false;

	for (string str1 : v1) {
		for (string str2 : v2) {
			// String was found.
			if (str1 == str2) {
				found = true;
				break;
			}
		}
		// If the string was not found, place it in the vector to return.
		if (!found) {
			ret_vec.push_back(str1);
		}
		// Reset found bool for the next iteration.
		found = false;
	}
	return ret_vec;
}


/**
Returns a Config struct with all of the data read from the config file.
config_file: [fstream&] the file stream for the config file.
Return: [Config] the data parsed from the config file.
*/
Config get_config_data(fstream &config_file)
{
	Config config_data;
	string str;
	int line_num = 0;
	string section;

	// Read each line from the file.
	while (getline(config_file, str)) {
		// No parsing required on comments on empty lines.
		if (str.empty() || str[0] == ';' ) {
			continue;
		} 
		// Moved to a new section.
		else if (str[0] == '[') {
			// Remove ']'.
			section = str.substr(1, str.length() - 2);
			line_num = 0;
			continue;
		}
		// Add data to the Config.
		switch (line_num) {
			// Monday.
			case 0:
				if (section == "done") {
					vector<string> done = str_to_vector(str.substr(7));
					config_data.monday_done = done;
				}
				else {
					config_data.monday = str_to_vector(str.substr(7));
				}
				break;

			// Tuesday.
			case 1:
				if (section == "done") {
					vector<string> done = str_to_vector(str.substr(8));
					config_data.tuesday_done = done;
				}
				else {
					config_data.tuesday = str_to_vector(str.substr(8));
				}
				break;

			// Wednesday.
			case 2:
				if (section == "done") {
					vector<string> done = str_to_vector(str.substr(10));
					config_data.wednesday_done = done;
				}
				else {
					config_data.wednesday = str_to_vector(str.substr(10));
				}
				break;

			// Thursday.
			case 3:
				if (section == "done") {
					vector<string> done = str_to_vector(str.substr(9));
					config_data.thursday_done = done;
				}
				else {
					config_data.thursday = str_to_vector(str.substr(9));
				}
				break;

			// Friday.
			case 4:
				if (section == "done") {
					vector<string> done = str_to_vector(str.substr(7));
					config_data.friday_done = done;
				}
				else {
					config_data.friday = str_to_vector(str.substr(7));
				}
				break;

			// Saturday.
			case 5:
				if (section == "done") {
					vector<string> done = str_to_vector(str.substr(9));
					config_data.saturday_done = done;
				}
				else {
					config_data.saturday = str_to_vector(str.substr(9));
				}
				break;

			// Sunday.
			case 6:
				if (section == "done") {
					vector<string> done = str_to_vector(str.substr(7));
					config_data.sunday_done = done;
				}
				else {
					config_data.sunday = str_to_vector(str.substr(7));
				}
				break;

		}
		++line_num;
	}

	return config_data;
}


/**
Reads the planner file to see if edits need to be made to the config.
planner_file: [fstream&] the planner file.
return: [Planner] the data from the planner.
*/
Planner read_planner(fstream& planner_file)
{
	Planner planner;
	string str, day, tasks;
	int line = 0;

	// Read from file.
	while (getline(planner_file, str)) {
		if (!str.empty()) { 
			day = str.substr(0, 3);
			// Get all of the tasks. The substring call could go out of bounds of the string,
			// so catch the error and assign tasks the empty string.
			try {
				tasks = str.substr(12);
			}
			catch (...) {
				tasks = "";
			}

			// Set the first day read from the planner file.
			if (line == 0) {
				planner.first = day;
			}

			// Get all the tasks for each day.
			if (!tasks.empty()) {
				if (day == "MON") {
					planner.monday = str_to_vector(tasks);
				}
				else if (day == "TUE") {
					planner.tuesday = str_to_vector(tasks);
				}
				else if (day == "WED") {
					planner.wednesday = str_to_vector(tasks);
				}
				else if (day == "THU") {
					planner.thursday = str_to_vector(tasks);
				}
				else if (day == "FRI") {
					planner.friday = str_to_vector(tasks);
				}
				else if (day == "SAT") {
					planner.saturday = str_to_vector(tasks);
				}
				else if (day == "SUN") {
					planner.sunday = str_to_vector(tasks);
				}
			}
			++line;
		}
	}
	return planner;
}

/**
Converts an integer day to a string representation of that day.
day: [int] the number of days since Sunday.
Return: [string] the day of the week.
*/
string day_to_str(int day)
{
	string day_str;

	switch (day) {
	case 0:
		day_str = "SUN";
		break;

	case 1:
		day_str = "MON";
		break;

	case 2:
		day_str = "TUE";
		break;

	case 3:
		day_str = "WED";
		break;

	case 4:
		day_str = "THU";
		break;

	case 5:
		day_str = "FRI";
		break;

	case 6:
		day_str = "SAT";
		break;
	}

	return day_str;
}

/**
Modifies the config and planner structs to hold the new data relevant to each file.
config: [Config&] the config data.
planner: [Planner&] the planner data.
*/
void generate_data(Config& config, Planner& planner) {
	int day;
	string day_str;
	vector<string> unfinished;

	// Get date information.
	time_t now = time(0);
	tm time_info; 
	localtime_s(&time_info, &now);

	day = time_info.tm_wday;  // Days since sunday.

	// Convert the day of the week to a string.
	day_str = day_to_str(day);

	// Config file is edited to reflect all tasks that have been finished.
	config.monday_done = compare_vec(config.monday, planner.monday);
	config.tuesday_done = compare_vec(config.tuesday, planner.tuesday);
	config.wednesday_done = compare_vec(config.wednesday, planner.wednesday);
	config.thursday_done = compare_vec(config.thursday, planner.thursday);
	config.friday_done = compare_vec(config.friday, planner.friday);
	config.saturday_done = compare_vec(config.saturday, planner.saturday);
	config.sunday_done = compare_vec(config.sunday, planner.sunday);

	// Planner needs to be reset (the first entry in the planner is yesterday).
	if (day_str != planner.first) {
		if (planner.first == "MON") {
			config.monday_done = {};
			unfinished = planner.monday;
		}
		else if (planner.first == "TUE") {
			config.tuesday_done = {};
			unfinished = planner.tuesday;
		}
		else if (planner.first == "WED") {
			config.wednesday_done = {};
			unfinished = planner.wednesday;
		}
		else if (planner.first == "THU") {
			config.thursday_done = {};
			unfinished = planner.thursday;
		}
		else if (planner.first == "FRI") {
			config.friday_done = {};
			unfinished = planner.friday;
		}
		else if (planner.first == "SAT") {
			config.saturday_done = {};
			unfinished = planner.saturday;
		}
		else if (planner.first == "SUN") {
			config.sunday_done = {};
			unfinished = planner.sunday;
		}
	}

	// Set planner fields to only user-added events not accounted for in the config file.
	planner.monday = compare_vec(planner.monday, config.monday);
	planner.tuesday = compare_vec(planner.tuesday, config.tuesday);
	planner.wednesday = compare_vec(planner.wednesday, config.wednesday);
	planner.thursday = compare_vec(planner.thursday, config.thursday);
	planner.friday = compare_vec(planner.friday, config.friday);
	planner.saturday = compare_vec(planner.saturday, config.saturday);
	planner.sunday = compare_vec(planner.sunday, config.sunday);

	// Set planner fields to what still needs to be done + whatever was already read in.
	vector<string> temp_vec = compare_vec(config.monday, config.monday_done);
	planner.monday.insert(planner.monday.end(), temp_vec.begin(), temp_vec.end());
	
	temp_vec = compare_vec(config.tuesday, config.tuesday_done);
	planner.tuesday.insert(planner.tuesday.end(), temp_vec.begin(), temp_vec.end());
	
	temp_vec = compare_vec(config.wednesday, config.wednesday_done);
	planner.wednesday.insert(planner.wednesday.end(), temp_vec.begin(), temp_vec.end());

	temp_vec = compare_vec(config.thursday, config.thursday_done);
	planner.thursday.insert(planner.thursday.end(), temp_vec.begin(), temp_vec.end());

	temp_vec = compare_vec(config.friday, config.friday_done);
	planner.friday.insert(planner.friday.end(), temp_vec.begin(), temp_vec.end());

	temp_vec = compare_vec(config.saturday, config.saturday_done);
	planner.saturday.insert(planner.saturday.end(), temp_vec.begin(), temp_vec.end());

	temp_vec = compare_vec(config.sunday, config.sunday_done);
	planner.sunday.insert(planner.sunday.end(), temp_vec.begin(), temp_vec.end());

	// Add anything that was not finished yesterday (if applicable).
	planner.append_day(day_str, unfinished);
}

/**
Converts a vector to a string.
vec: [vector<string>] the vector to convert to a string.
Return: [string] the string representation of the vector.
*/
string vector_to_str(vector<string> vec) 
{
	int i = 0;
	string str;
	for (auto e : vec) {
		// Add ", " before each element aside from the first.
		if (i != 0) {
			str += ", ";
		}
		// Add the element to the string.
		str += e;
		i++;
	}
	return str;
}

/**
Writes the data from the config struct to the config file.
config_file: [fstream&] the config file stream.
config: [Config&] the config struct.
*/
void write_to_config(fstream& config_file, Config& config)
{
	// Unfinished section.
	config_file << "[unfinished]\n";
	config_file << "monday=" << vector_to_str(config.monday) << "\n";
	config_file << "tuesday=" << vector_to_str(config.tuesday) << "\n";
	config_file << "wednesday=" << vector_to_str(config.wednesday) << "\n";
	config_file << "thursday=" << vector_to_str(config.thursday) << "\n";
	config_file << "friday=" << vector_to_str(config.friday) << "\n";
	config_file << "saturday=" << vector_to_str(config.saturday) << "\n";
	config_file << "sunday=" << vector_to_str(config.sunday) << "\n";

	// Done section.
	config_file << "\n[done]\n";
	config_file << "monday=" << vector_to_str(config.monday_done) << "\n";
	config_file << "tuesday=" << vector_to_str(config.tuesday_done) << "\n";
	config_file << "wednesday=" << vector_to_str(config.wednesday_done) << "\n";
	config_file << "thursday=" << vector_to_str(config.thursday_done) << "\n";
	config_file << "friday=" << vector_to_str(config.friday_done) << "\n";
	config_file << "saturday=" << vector_to_str(config.saturday_done) << "\n";
	config_file << "sunday=" << vector_to_str(config.sunday_done) << "\n";
}

/**
Determines if the given month has 31 days in it.
month: [int] the month since January (0-11).
*/
bool is_special_month(int month) {
	if (month > 11 || month < 0) {
		throw "Month must be between 0 and 11 inclusive.";
	}

	switch (month) {
	// January.
	case 0:
		return true;

	// March.
	case 2:
		return true;

	// May.
	case 4:
		return true;

	// July.
	case 6:
		return true;

	// August.
	case 7:
		return true;

	// October.
	case 9:
		return true;

	// December.
	case 11:
		return true;
	}

	return false;
}


/**
Takes the date information and ensures that it represents a valid date.
day: [int] the day of the week since Sunday (0-6).
date: [int] the date of the month (1-31).
month: [int] the month of the year since January (0-11)
year: [int] the year.
*/
void validate_date(int& day, int& date, int& month, int& year)
{
	// Ensure the day never goes above 6 (stays an official day).
	if (day > 6) {
		day = 0;
	}
	// Account for February.
	if (month == 1 && date > 28) {
		// Check for leap year.
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
			if (date > 29) {
				month++;
				date = 1;
			}
		}
		else {
			month++;
			date = 1;
		}
	}
	// Ensure date is legal.
	else if (date > 30) {
		if (date > 31) {
			// Starting a new year.
			if (month == 11) {
				month = 0;
				date = 1;
				year++;
			}
			else {
				month++;
				date = 1;
			}
		}
		else if (!is_special_month(month)) {
			month++;
			date = 1;
		}
	}
}


/**
Writes the data from the planner struct to the planner file.
planner_file: [fstream&] the planner file stream.
planner: [Planner&] the planner struct.
*/
void write_to_planner(fstream& planner_file, Planner& planner, vector<string> g_cal_data)
{
	int day, date, month, year;
	string day_str, out;

	// Get date information.
	time_t now = time(0);
	tm time_info;
	localtime_s(&time_info, &now);

	day = time_info.tm_wday;  // Days since sunday.
	date = time_info.tm_mday;  // Day of month (1-31).
	month = time_info.tm_mon;  // Month since January (0-11).
	year = time_info.tm_year + 1900;  // Year since 1900.

	for (int i = 0; i < 7; i++) {
		// Ensure valid dates.
		validate_date(day, date, month, year);
		// Convert day to string.
		day_str = day_to_str(day);
		// Write to planner. Format: DAY (MONTH/DATE): Tasks.
		out = day_str + " (" + to_string(month + 1) + "/" + to_string(date) + "): " + vector_to_str(planner.get_day(day_str));
		planner_file << out << endl;
		day++;
		date++;
	}
	
	// Add Google Calendar data.
	planner_file << "\nUpcoming Events:" << endl;
	for (string str : g_cal_data) {
		planner_file << str << endl;
	}
}


/**
Converts the arguments into a vector format.
argc: [int] the number of arguements.
argv: [char **] the command line arguments.
Return: [vector<string>] the arguments as a string.
*/
vector<string> parse_args(int argc, char** argv)
{
	vector<string> vec;

	// No arguments, just the program name.
	if (argc < 2) {
		return {};
	}

	// Add each argument to the vector.
	for (int i = 1; i < argc; i++) {
		vec.push_back(argv[i]);
		cout << argv[i] << endl;
	}

	return vec;
}


/**
Entry point for the program.
*/
int main(int argc, char* argv[])
{
	// Parse command line arguments. This is string data from the google calandar API.
	vector<string> g_cal_data = parse_args(argc, argv);

	// Open files for reading.
	fstream planner_file = open_file(PLANNER_FILE_PATH);
	fstream config_file = open_file(CONFIG_FILE_PATH);
	
	// Parse config file.
	Config config_data = get_config_data(config_file);
	// Parse planner file.
	Planner planner_data = read_planner(planner_file);

	// Close files.
	config_file.close();
	planner_file.close();

	// Special case allowing planner file to be initialized with config data.
	if (argc >= 2 && g_cal_data[0] == "init") {
		planner_data.monday = config_data.monday;
		planner_data.tuesday = config_data.tuesday;
		planner_data.wednesday = config_data.wednesday;
		planner_data.thursday = config_data.thursday;
		planner_data.friday = config_data.friday;
		planner_data.saturday = config_data.saturday;
		planner_data.sunday = config_data.sunday;
	}
	else {
		// Compare data between config and planner.
		generate_data(config_data, planner_data);
	}

		// Open files for writing.
		planner_file = open_file(PLANNER_FILE_PATH);
		config_file = open_file(CONFIG_FILE_PATH);

		// Write and close config file.
		write_to_config(config_file, config_data);
		config_file.close();

		// Write and close planner file.
		write_to_planner(planner_file, planner_data, g_cal_data);
		planner_file.close();
}