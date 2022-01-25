#pragma once
#include "UM-Memory.h"
#include <iostream>
#include <map>
#include <list>
#include <algorithm> 
#include <stdlib.h>
#include <fstream>
#include "settings.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

std::vector<std::string> selectedItems;

std::string left(string line, char delimeter) {
	string str = line.substr(0, line.find(delimeter));
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

std::string right(string line, char delimeter) {
	string str = line.substr(line.find(delimeter) + 1, line.length());
	return str;
}

bool getSettings() {

	//readLines
	string myText;
	bool READ = false;
	string currSection;
	
	//FIND THE CURRENT PATH TO THE RUNNING EXE THEN FIND "config.txt" IN THAT SAME DIRECTORY
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string directory(buffer);
	directory.erase(directory.find_last_of('\\') + 1, directory.length());
	directory += "Config.txt";
	cout << "Current Directory:" << directory << endl;

	ifstream in(directory);
	if (!in) {	//return error
		cout << "ERROR: Failed to find config.txt" << endl;
		return false;
	}
	while (getline(in, myText)) { //read the lines
		if (left(myText, ':').compare("X") == 0) {
			selectedItems.emplace_back(right(myText, ':'));
		}
	}
	in.close();
	return true;
}

