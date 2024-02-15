#include <unistd.h>
#include <string>
#include <iostream>
#include <sys/wait.h>
#include <filesystem>
#include <cstring>
#include <fstream>

using namespace std;

int main() {
    char* scanner_path = "./../../src/scanner/scanner";
    string scanned_path = "./scanned_code/";
    string solution_path = "./solution/";
    string raw_code_path = "./raw_code/";

    char source_path[100], destination_path[100];
    char* argv[] = {scanner_path, source_path, destination_path, NULL};

    pid_t cpid;
    ofstream output_file("result_tests_scanner.txt");
    for (auto & file:filesystem::directory_iterator(raw_code_path)) { // iterate over the files in the folder in raw_code_path
        string file_name=file.path().filename().string();
        strcpy(source_path, file.path().c_str());
        strcpy(destination_path, (scanned_path+file_name).c_str());

        if (!filesystem::exists((solution_path+file_name).c_str())) {
            output_file << file_name << " has no solution file\n\n";
            continue;
        }

        // the file has a solution file (due to the previous if with the "continue" statement which skips the current iteration)

        cout << argv[1] << "\n" << argv[2] << "\n";
        output_file << file_name << " :\n";
        
        // execute the scanner code over the current file (one file per iteration)
        if (fork()==0) { // execute it in a child process because the execution makes the process end
            execvp(scanner_path, argv);
            exit(0);
        }

        cpid = wait(NULL); // wait for the execution to be done (i.e. the child process to be done)

        ifstream scanned_file(destination_path);
        ifstream solution((solution_path+file_name).c_str());
        
        int line_nb=1;
        string line_scanned_file, line_solution;
        // check the solution and the output of the scanner to see if it is correct
        while(getline(scanned_file, line_scanned_file)&&getline(solution, line_solution)) {
            if (line_scanned_file!=line_solution) break;
            line_nb++;
        }
        
        if (scanned_file.eof()&&!getline(solution, line_solution)) { // end of both files
            cout << "Correct\n\n";
            output_file << "Correct\n\n";
        } else { // one or both files did not end (one longer than the other or a break due to a difference in a line)
            cout << "Incorrect\n\n";
            output_file << "Incorrect, line " << line_nb << " :\n"
                        << "scanned line  :" << line_scanned_file << "\n" 
                        << "solution line :" << line_solution << "\n\n";
        }

        scanned_file.close(); solution.close();
    }

    output_file.close();

    return 0;
}