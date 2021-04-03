#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int answer = 0;
    int rv;
    int size = atoi(argv[0]); // convert to int from char
    for (int i = 1; i <= size; i++)
    {
	answer = answer + atoi(argv[i])*atoi(argv[i+size]);
    }
    cout << "Result: " << answer << "\n";
    exit(rv);
}
