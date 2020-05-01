#pragma once
#include "planner.h"
#include "config.h"
using namespace std;

/**
* Safely open the file with the given file name.
* \param f_name: [string] the full path name of the file to open.
* Return: [fstream] the file stream of the opened file.
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
* Converts a string to a vector.
* \param str: [string] the string to convert to a vector.
* \param delim: [char] the delimeter to use to seperate entries.
* Return: [vector<string>] the vector representation of the string.
*/
vector<string> str_to_vector(string str, char delim)
{
	vector<string> str_vec;

	// Nothing do do for an empty string.
	if (str.empty()) { 
		return str_vec;
	}

	string temp_str;
	for (char ch : str) {
		// Add all characters before the delimeter to the string.
		if (ch != delim) { temp_str += ch; }
		
		// Once the delimeter is found, add the string to the vector.
		else { str_vec.push_back(temp_str); }
	}
	// Add the last element that was not added in the loop.
	str_vec.push_back(temp_str);

	return str_vec;
}


/**
* Compares two vectors and returns everything in vector 1 that is not in vector 2.
* \param day: [vector<string>] the tasks for the current day.
* \param done: [vector<string>] the completed tasks for the current day.
* Return: [vector<string>] the tasks that are not completed.
*/
vector<string> compare_vec(vector<string> day, vector<string> done)
{
	// Nothing to do with an empty comparison vector.
	if (done.empty()) { return day; }

	vector<string> ret_vec;
	bool found = false;

	for (string str1 : day) {
		for (string str2 : done) {
			// String was found.
			if (str1 == str2) {
				found = true;
				continue;
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
* Returns a Config struct with all of the data read from the config file.
* \param config_file: [fstream] the file stream for the config file.
* Return: [Config] the data parsed from the config file.
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
		if (str.front() == ';' || str.empty()) {
			continue;
		} 
		// Moved to a new section.
		else if (str.front() == '[') {
			// Remove ']'.
			section = str.substr(1, str.length() - 2);
			line_num = 0;
			continue;
		}
		// Add data to the Config.
		switch (line_num) {
			// Monday.
			case 0:
				// Ensure that tasks that are done are not being added.
				if (section == "done") {
					vector<string> done = str_to_vector(str.substr(7));
					config_data.monday = compare_vec(config_data.monday, done);
				}
				else {
					config_data.monday = str_to_vector(str.substr(7));
				}
				break;

			// Tuesday.
			case 1:
				// Ensure that tasks that are done are not being added.
				if (section == "done") {
					vector<string> done = str_to_vector(str.substr(7));
					config_data.tuesday = compare_vec(config_data.tuesday, done);
				}
				else {
					config_data.tuesday = str_to_vector(str.substr(7));
				}
				break;

			// Wednesday.
			case 2:
				// Ensure that tasks that are done are not being added.
				if (section == "done") {
					vector<string> done = str_to_vector(str.substr(7));
					config_data.wednesday = compare_vec(config_data.wednesday, done);
				}
				else {
					config_data.wednesday = str_to_vector(str.substr(7));
				}
				break;

			// Thursday.
			case 3:
				// Ensure that tasks that are done are not being added.
				if (section == "done") {
					vector<string> done = str_to_vector(str.substr(7));
					config_data.thursday = compare_vec(config_data.thursday, done);
				}
				else {
					config_data.thursday = str_to_vector(str.substr(7));
				}
				break;

			// Friday.
			case 4:
				// Ensure that tasks that are done are not being added.
				if (section == "done") {
					vector<string> done = str_to_vector(str.substr(7));
					config_data.friday = compare_vec(config_data.friday, done);
				}
				else {
					config_data.friday = str_to_vector(str.substr(7));
				}
				break;

			// Saturday.
			case 5:
				// Ensure that tasks that are done are not being added.
				if (section == "done") {
					vector<string> done = str_to_vector(str.substr(7));
					config_data.saturday = compare_vec(config_data.saturday, done);
				}
				else {
					config_data.saturday = str_to_vector(str.substr(7));
				}
				break;

			// Sunday.
			case 6:
				// Ensure that tasks that are done are not being added.
				if (section == "done") {
					vector<string> done = str_to_vector(str.substr(7));
					config_data.sunday = compare_vec(config_data.sunday, done);
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
* Entry point for the program.
*/
int main()
{
	// Open critical files.
	fstream planner_file = open_file(PLANNER_FILE_PATH);
	fstream config_file = open_file(CONFIG_FILE_PATH);
	
	// Parse config file.
	Config config_data = get_config_data(config_file);


	// Close all opened files.
	planner_file.close();
	config_file.close();
}