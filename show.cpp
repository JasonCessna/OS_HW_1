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

	char DEVTTY[]= "/dev/tty";
	int displayLines = 20;
	char** commandv;
	int pd[2];
	int pid;
	pipe(pd);
	char buffer[1024];

	int file_desc = open(DEVTTY, O_RDWR | O_APPEND | O_CREAT);
	pid == fork();

	if (pid == 0) {


		close(0);
		close(pd[1]);
		dup2(file_desc, pd[0]);
		char** path_arr;
		char *path= getenv("PATH");
		int current_path = 0;

		char temp_string;
		int placeHolder = 0;

		for (int i = 0; i < sizeof(path); i++) {

			if (path[i] == ':') {
				current_path++;
				placeHolder = i;
			}
			else {
				path_arr[current_path][(i - placeHolder - 1)] = path[i];
			}

		}

		char* pathname;
		for (int i = 0; i < current_path + 1; i++) {
			if (!access(path_arr[i], X_OK)) {
				pathname = path_arr[i];
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
				tempName[j] = pathname[j];
			}
			else {
				for (int k = 0; k < sizeof(commandv[0]); k++) {
					int L = j + k;
					tempName[L] = commandv[0][k];
				}
			}
		}
		bool failure = execv(tempName, commandv);
		if (failure) {
			cout << "Error" << endl;
		}
		
		/*execv(pathname[0], commandv);*/

		/*_exit(0);*/

	}
	else {
		/**** PARENT *****/
		while (pid != wait(0));
		/*fflush(0);*/
		close(0);
		dup2(file_desc,0);
		/*dup2(pd[1], 1);*/
		dup2(file_desc, 1);
		close(pd[0]);
		int counter = 1;
		string response = "";
		string line = "";
		string test = "";
		while (getline(cin, line)) {
			if (counter % displayLines != 0) {

				cout << line << endl;
			}
			else {
				while (response != "Q" || response != "q" || response != "C" || response != "c") {
					cout << "Enter c+RETURN to continue, q+RETURN to quit:" << endl;
					cin >> response;
					if (response == "q" || response == "Q") {
						break;
					}
					else if (response != "C" && response != "c") {
						cout << "Unrecognized command." << endl;
					}

				}
			}
			counter++;
		}





		_exit(0);

	}
	
	return 0;
}
