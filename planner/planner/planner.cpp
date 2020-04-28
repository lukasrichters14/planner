#pragma once
#include "planner.h"
using namespace std;

/**
* Safely open the file with the given file name.
* f_name: [string] the full path name of the file to open.
* Return: [fstream] the file stream of the opened file.
*/
fstream open_file(string f_name)
{
	fstream file;
	file.open(f_name);  // Open the file.

	// Provide an error message if the file fails to open.
	if (file.fail()) {
		cout << "The file " + f_name + " could not be opened." << endl;
		return;
	}

	return file;
}

/**
* Returns a Config struct with all of the data read from the config file.
* config_file: [fstream] the file stream for the config file.
* Return: [Config] the data parsed from the config file.
*/
Config get_config_data(fstream config_file)
{

}


/**
* Entry point for the program.
*/
int main()
{
	// Open critical files.
	fstream planner_file = open_file(PLANNER_FILE_PATH);
	fstream config_file = open_file(CONFIG_FILE_PATH);


	// Close all opened files.
	planner_file.close();
	config_file.close();
}