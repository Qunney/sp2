#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<vector<string>> M {{"1", "2", "3", "1"}, {"2", "2", "10", "1"}};
    vector<string> vector {"5", "2", "3", "4"};
    const char *programname = "sp2_2";
    int lines = M.size(); // kol-vo strok
    int v_size = vector.size(); // razmer vektorov
    int argc = v_size*2+2; // kolvo peredaushihsya argumentov
    const char **args = new const char* [v_size*2+2];
    args[0] = to_string(v_size).c_str();
    args[argc-1] = NULL;
    cout << "Vector : [ ";
    for (int j = 1;  j <= v_size;  j++) //add vector in args
    {
	args[j] = vector[j-1].c_str();
	cout << args[j] << " ";
    }
    cout << "]\n";
    cout << "Matrix: [ ";
    for ( int i = 0; i < lines; i++ )
    {
	cout << "[ ";
	for (int j = 0; j < v_size; j++)
	{
	    cout << M[i][j] << " ";
	}
	cout << "] ";
    }
    cout << "]\n";
    pid_t pid;
    int status;
    int answer;
    cout << "IT IS PARENT, PID: " << getpid() << endl;
    cout << "Multiplication start! \n";
    for (int i = 0; i < lines; i++)
    {
	switch (pid=fork())
	{
	case -1: // smth wrong
	    perror ("fork");
	    exit(1);
	case 0: // new child process 
	    cout << "IT'S CHILD, PID: " << getpid();
	    cout << "; PARENT PID: " << getppid() << " \n";
	    cout << i + 1 << " line and vector\n";
	    for (int j = v_size+1;  j <= argc-2;  j++) //add lines in args
            {
	        args[j] = M[i][j-1-v_size].c_str();
            }
	    execv(programname, (char **)args);
	default: 
	    waitpid(pid, &status, 0);
	    if ( i == lines-1 ) cout << "End of multiplication! \n";
	    else cout << "next line! \n";
          }
    }
    return 0;
}


