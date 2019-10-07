#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
using namespace std;

#define DEVTTY "/dev/tty"

int main(char argv[][], char **argv){

	//CONST int defaultLines 
	int displayLines = 20;
	int pd[2];
  	int pid;
	pipe(pd);
	char buffer[1024];

	
	
	if ((pid = fork()) == 0){

		char filename[1024];
		/*
			Executes the specified command (“ls –alg”)
	 		Three-step process:
				1 Set up the argument vector
				2 Find program to be executed 
					- Never be a built-in program
				3 Perform the execv()
		*/

 		close(1); 
 		dup(pd[1]); 
		vector <string> path_arr;
		string path = getenv("PATH"); //do I manually get the path or does this return a path?
		int current_path = 0
		for(int i = 0; i < path.length(); i++){
			if(path[i] != ":"){
				if(path_arr.length() == (current_path + 1)){
					path_arr[current_path].append(path[i]);
				}
				else{
					path_arr[current_path] = path[i];
				}
			}
			else{
				current_path++;
			}
		}
		char filename[1024];
		char pathname[1024];
		for(int i = 0; i < current_path + 1; i++){
			sprintf(path_arr[i], "%s/%s",directory[i], argv[0]);
			if(!access(pathname, X_OK)){
				strcopy(pathname,path_arr[i]);
				break;
			}

		}

		char** commandv;
		int offset;
		if (argv[1][0] == '-') { // optional argument
			offset = 2;
			string displayLinesString = "";
			for(int i = 1; i < argv.length(); i++){
					displayLinesString.append(argv[1][i]);
			//displayLines = argv[1];

			}
			displayLines = stoi(displayLinesString); // convert display lines value to integer

		} else { // no optional argument
			offset = 1;
		}
		commandv= &argv[offset];  // the value of an array is the address of its first element
		filename = pathname;
		filename.append("." + commandv);
/*
		if (myargv[0][0] == '/' || myargv[0][0] == '.') {
		    // A full pathname was specified
		    strcpy(pathname,myargv[0]);
		    missing = access(pathname, X_OK);
		    //  access returns 0 if the file is found
		} else {
		   for (i=0; i <  pathc; i++) {
		       sprintf(pathname, "%s/%s", pathv[i],myargv[0]);
		       if (!(missing=access(firstarg, X_OK)))
		           // access returns 0 if the file is found!
		           break;
		       } // for
		} // if-else
		if (missing) {
		     printf("%s: cannot be executed\n", myargv[0]);
		     _exit(1);
		} // if
*/


		//strcpy(buffer, getenv("PATH")); // this copies the string to the buffer char array, will test to see if I don't need it using string
		execv(filename, argv);

		close(pd[1]);
		_exit(1); 
	// child process

}
else{
/*

Main program
(continues after the fork):
	Redirects its stdin to pd[0]
	Redirects its stdout to /dev/tty
		- To defeat previous redirections:
			show ls –alg > junkfile.txt
	Displays screenful by screenful the output of the child process
*/

		close(0); 
		dup(pd[0]); 
		ofstream ofs(DEVTTY);
		int counter = 1;
		string response = "";
		while(getline(cin, line)){
			if (counter % displayLines != 0){

				ofs << line << endl;
			}
			else{
				while(response != 'Q' || response != "q" || response != "C" || response != "c"){
					ofs << "Enter c+RETURN to continue, q+RETURN to quit:" << endl;
						cin >> response >> endl;
					if(response == 'q' || response == 'Q'){
						break;
					}
					else if (r response != "C" || response != "c"){
						ofs << "Unrecognized command." << endl;
				}
				
			}
			counter++;
		}

		close(pd[1]);

		//try using ofs << whatever << endl; instead of cout << whatever << endl;
	    // while (read(pipefd[0], buffer, sizeof(buffer)) != 0)
    	// {
    	// }
		//execv(filename, argv);
		_exit(1); 


    }
	return 0;
}
