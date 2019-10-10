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
#include <cstdio>
#include <iomanip>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {

	char DEVTTY[]= "/dev/tty";
	int displayLines = 20;
	char** commandv;
	int pd[2];
	int pid;
	pipe(pd);
	char buffer[1024];

	int file_desc = open("/dev/tty", O_RDWR);
	pid = fork();

	if (pid == 0) {

		dup2(file_desc, file_desc);
		dup2(pd[0], 1);
		close(pd[0]);
		close(1);
		string path_arr = "";
		string pathname;

		string path = getenv("PATH");
		int current_path = 0;

		char temp_string;
		int placeHolder = 0;
		int offset;
		if (argv[1][0] == '-') {
			offset = 2;
			string displayLinesString = "";
			if (isdigit(argv[1][1])) {
				char* tempArg = argv[1];
				displayLinesString = &tempArg[1];
				displayLines = stoi(displayLinesString);
			}

		}
		else {
			offset = 1;
		}
		cout << displayLines << endl;

		commandv = &argv[offset];
		string  tempCommand;
		tempCommand.append(commandv[0]);
		int counter = 0;
		int validPath = 0;
		for (int i = 0; i < sizeof(path); i++) {
			if (!validPath) {
				if (path[i] == ':') {
					char pathHolder[] = "";
					int tempCount = 1;
					for (int j = 0; j < sizeof(path_arr); j++) {
						tempCount += 1;
						pathHolder[j] = path_arr[j];
					}
					if (!access(pathHolder, X_OK)) {
						validPath = 1;
						pathname.append(pathHolder);

						pathname += "/";
						pathname += tempCommand;
						break;

					}
					else {
						path_arr = "";
					}
					counter = 0;
				}
				else {
					path_arr[counter] = path[i];
					counter++;
				}
			}


		}

		char fullPath[] = "";
		for (int i = 0; i < pathname.size(); i++) {
			fullPath[i] = pathname[i];
		}


	/*	bool failure = execv(fullPath, argv);
		if (failure) {
			cout << ("Error") << endl;
			
		}*/

		execv(fullPath, commandv);
		exit(errno);
		

	}
	else {
		/***
	while (pid != wait(0));
		* PARENT *****/
	/*	*/
		/*fflush(0);*///parent stuff
    int status;
    wait(&status);       /*you made a exit call in child you 
                           need to wait on exit status of child*/
    if(WIFEXITED(status))
         cout << WEXITSTATUS(status) << endl;
		dup2(pd[0],0);
		close(pd[1]);
		dup2(file_desc, file_desc);

		/*dup2(file_desc, 0);
		
		dup2(pd[1], 1);*/
		int counter = 1;
		string response = "";
		string line = "";
		string test = "";
		/*FILE* input = fdopen(pipe[0], "r");*/
		ifstream inFile;
		inFile.open("/dev/tty");
		cout << "here" << endl;
		while (inFile >> line) {
			response = "";
			if (counter % displayLines != 0) {

				cout << line << endl;
				counter++;
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
		}

	}
	
	return 0;
}
