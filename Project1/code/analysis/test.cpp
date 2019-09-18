#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(void)
{
    /** 8 different values of n */
    const int n[8] = {1000, 5000, 10000, 20000, 40000, 60000, 80000, 100000};

    /** the file name of programs */
    const string prog_file_name[3] = {"algo_1", "algo_2_recursive", "algo_2_iterative"};

    for (int i = 0; i < 3; i ++) {
        cout << prog_file_name[i] << " : " << endl;
        for (int j = 0; j < 8; j ++) {
            cout << "n = " << n[j] << "," << endl;

            int iterations;
        	if (i == 0) {
	            /**
	             * To make the total time which the program cost in the same range (several seconds),
	             * the value of iterations is set to be (iterations / n[j]).
	             *
	             * command : ./prog iterations n
	             */
	            iterations = 1000000000 / n[j];
	        } else {
	        	iterations = 10000000;
	        }
            system(("./" + prog_file_name[i] + " " + to_string(iterations) + " " + to_string(n[j])).c_str());
            cout << endl;
        }
        cout << endl << endl;
    }
    return 0;
}
