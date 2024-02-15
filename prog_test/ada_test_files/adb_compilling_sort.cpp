#include <unistd.h>
#include <string>
#include <iostream>
#include <sys/wait.h>
#include <filesystem>
#include <cstring>
#include <fstream>

using namespace std;

int main() {
    string correct_path = "./correct_files/";
    string incorrect_path = "./incorrect_files/";
    string unclassed_path = "./unclassed_files/";

    char source_path[100];
    char* argv_compile[] = {"gnat", "compile", source_path, NULL};

    char destination_path[100];
    char* argv_mv[] = {"mv", source_path, destination_path, NULL};

    char filename[100];
    char* argv_clean[] = {"gnat", "clean", filename, NULL};

    pid_t cpid;
    ofstream output_file("result_last_compilling_sort.txt");
    for (auto & file:filesystem::directory_iterator(unclassed_path)) { // iterate over the files in the folder in unclassed_path
        strcpy(filename, file.path().filename().c_str()); // update filename
        strcpy(source_path, file.path().c_str()); // update source_path

        cout << argv_compile[2] << "\n";
        output_file << filename << " : ";
        
        // try to compile the current file (one file per iteration)
        if (fork()==0) { // execute it in a child process because the execution makes the process end
            execvp("gnat", argv_compile);
            exit(0);
        }

        int status;
        cpid=waitpid(-1, &status, 0); // wait for the execution to be done (i.e. the child process to be done)
        if (WEXITSTATUS(status)==0) { // no errors
            strcpy(destination_path, (correct_path+file.path().filename().string()).c_str()); // update destination_path
            output_file << "correct\n";
        } else {
            strcpy(destination_path, (incorrect_path+file.path().filename().string()).c_str()); // update destinaiton_path
            output_file << "incorrect (" << WEXITSTATUS(status) << ")\n";
        }


        if (fork()==0) {
            execvp("gnat", argv_clean); // delete the .ali and .o files
            exit(0);
        }
        cpid=waitpid(-1, &status, 0);


        if (fork()==0) {
            execvp("mv", argv_mv); // move the file to the correct folder
            exit(0);
        }
        cpid=waitpid(-1, &status, 0);
        cout << "\n";
    }

    output_file.close();

    return 0;
}