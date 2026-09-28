// Mehmet Inanci
// CSC 222
// Marathon Runners - Structured Data

#include <iostream>
#include <fstream>
#include <sstream>
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

int readRunnerData(Runner runners[]);

int main()
{
    Runner runners[MAX_RUNNERS]{};

    int runnerCount = readRunnerData(runners);

    if (runnerCount == 0)
    {
        cout << "No runner data was loaded." << endl;
        return 1;
    }

    cout << "Runner records loaded: " << runnerCount << endl;

    for (int runner = 0; runner < runnerCount; runner++)
    {
        cout << runners[runner].name << ": ";

        for (int day = 0; day < NUM_DAYS; day++)
        {
            cout << runners[runner].miles[day] << " ";
        }

        cout << endl;
    }

    return 0;
}

int readRunnerData(Runner runners[])
{
    ifstream inputFile("runners.txt");

    if (!inputFile)
    {
        cout << "Error opening runners.txt" << endl;
        return 0;
    }

    int runnerCount = 0;
    string line;
    bool firstLine = true;

    while (getline(inputFile, line) && runnerCount < MAX_RUNNERS)
    {
        if (line.empty())
        {
            continue;
        }

        istringstream lineStream(line);

        if (firstLine)
        {
            firstLine = false;

            int possibleRunnerCount;
            int possibleDayCount;

            if (lineStream >> possibleRunnerCount >> possibleDayCount)
            {
                string extraText;

                if (!(lineStream >> extraText))
                {
                    // The first line is a numeric header such as "5 7".
                    continue;
                }
            }

            lineStream.clear();
            lineStream.str(line);
        }

        Runner tempRunner{};

        if (!(lineStream >> tempRunner.name))
        {
            continue;
        }

        bool completeRecord = true;

        for (int day = 0; day < NUM_DAYS; day++)
        {
            if (!(lineStream >> tempRunner.miles[day]))
            {
                completeRecord = false;
                break;
            }
        }

        if (completeRecord)
        {
            runners[runnerCount] = tempRunner;
            runnerCount++;
        }
    }

    inputFile.close();

    return runnerCount;
}