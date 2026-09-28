// Mehmet Inanci
// CSC 222
// Marathon Runners - Structured Data

#include <iostream>
#include <string>

using namespace std;

const int MAX_RUNNERS = 50;
const int NUM_DAYS = 7;

struct Runner
{
    string name;
    double miles[NUM_DAYS];
    double total;
    double average;
};

int main()
{
    Runner runners[MAX_RUNNERS]{};

    cout << "Marathon Runners - Structured Data" << endl;

    return 0;
}