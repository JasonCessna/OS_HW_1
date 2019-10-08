#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream> 
#include <cstdio>
using namespace std;


int main(int argc, char* argv[]) {
	
	string DEVTTY = "/dev/tty";
	ofstream ofs(DEVTTY);
	ifstream ifs(DEVTTY);
	int displayLines = 20;
	char** commandv;
	int pd[2];
	int pid;
	pipe(pd);
	char buffer[1024];
	pid == fork();
	if (pid  == 0) {

		
		/*
			Executes the specified command (“ls –alg”)
			Three-step process:
				1 Set up the argument vector
				2 Find program to be executed
					- Never be a built-in program
				3 Perform the execv()
		*/

		dup(pd[0]);
		close(0);
		close(pd[1]);
		char* path_arr[];
		char path;
		strcpy(path,getenv("PATH"));
		int current_path = 0;
		int placeHolder = 0;
		ofs << path << endl;
		//path_arr = strtok(path, ":");
		
		char temp_string;

		for(int i = 0; i< sizeof(path); i++){
			if(path[i] == ':'){
				current_path++;
			}
			else{
				path_arr[current_path][sizeof(path_arr[current_path])] = path[i];
			}

		}

		/*
			for (int i = 0; i < sizeof(path); i++) {
				ofs << i << endl;
				if (path[i] != ':') {
					if (sizeof(path_arr[i]) == (current_path + 1)) {
						path_arr[current_path][0] = (path[0][i].c_str());
						placeHolder = i;

					}
					else {
						path_arr[current_path][i - placeHolder] = path[i];
					}
				}
				else {
					current_path++;
				}
			}
			*/
		char* pathname[1024]; 
		for (int i = 0; i < current_path + 1; i++) {
			if (!access(path_arr[i], X_OK)) {
				pathname[0] = path_arr[i];
				/*strcpy(pathname[0], path_arr[i]);*/
				break;
			}

		}

		int offset;
		if (argv[1][0] == '-') { 
			offset = 2;
			string displayLinesString = "";
			if (isdigit(argv[1][1])) {
				for (int i = 1; i < sizeof(argv[1]); i++) {

					displayLines = stoi(displayLinesString); 
				}
			}

		}
		else { 
			offset = 1;
		}
		commandv = &argv[offset];  
		char tempName[1024];
		for (int j = 0; j < sizeof(pathname[0]) + 1; j++) {
			if (j <= sizeof(pathname[0])) {
				tempName[j] = pathname[0][j];
			}
			else {
				for (int k = 0; k < sizeof(commandv[0]); k++) {
					int L = j + k;
					tempName[L] = commandv[0][k];
				}
			}
		}
		bool failure = execv(pathname[0], commandv);
		if (failure) {
			ofs << "Error" << endl;
		}

		/*execv(pathname[0], commandv);*/

		_exit(0);

	}
	else {
		/*
		Main program
		(continues after the fork):
			Redirects its stdin to pd[0]
			Redirects its stdout to /dev/tty
				- To defeat previous redirections:
					show ls –alg > junkfile.txt
			Displays screenful by screenful the output of the child process
		*/

		
		while (pid != wait(0));
		dup(pd[1]);
		close(1);
		close(pd[0]);
		int counter = 1;
		string response = "";
		string line = "";
		string test = "";
		while (getline(ifs, line)) {
			if (counter % displayLines != 0) {

				ofs << line << endl;
			}
			else {
				while (response != "Q" || response != "q" || response != "C" || response != "c") {
					ofs << "Enter c+RETURN to continue, q+RETURN to quit:" << endl;
					ifs >> response;
					if (response == "q" || response == "Q") {
						break;
					}
					else if (response != "C" && response != "c") {
						ofs << "Unrecognized command." << endl;
					}

				}
			}
			counter++;
		}

			


	
		_exit(0);
		
	}/*
	while (pid != wait(0));
	
	close(0);
	dup(pd[0]);
	ofstream ofs(DEVTTY);
	int counter = 1;
	string response = "";
	string line = "";
	ifstream ifs(DEVTTY);
	ofs << "test" << endl;
	while (getline(ifs, line)) {
		if (line == "\0") {
			break; 
		}
		ofs << counter % displayLines << endl;
		if (counter % displayLines != 0) {
			ofs << line << endl;
		}
		else {
			while (response != "Q" || response != "q" || response != "C" || response != "c") {
				ofs << "Enter c+RETURN to continue, q+RETURN to quit:" << endl;
				cin >> response;
				if (response == "q" || response == "Q") {
					break;
				}
				else if (response != "C" || response != "c") {
					ofs << "Unrecognized command." << endl;
				}
			}
		}
		counter++;
	}
	close(pd[1]);
	_exit(1);
	*/

	return 0;
