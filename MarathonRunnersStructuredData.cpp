// Mehmet Inanci
// CSC 222
// Marathon Runners - Structured Data

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
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

// Function prototypes
int readRunnerData(Runner runners[]);

void calculateTotalsAndAverages(
    Runner runners[],
    int runnerCount
);

void displayResults(
    const Runner runners[],
    int runnerCount
);

int main()
{
    Runner runners[MAX_RUNNERS]{};

    int runnerCount = readRunnerData(runners);

    if (runnerCount == 0)
    {
        cout << "No runner data was loaded." << endl;
        return 1;
    }

    calculateTotalsAndAverages(runners, runnerCount);

    displayResults(runners, runnerCount);

    return 0;
}


// Reads runner data from runners.txt
// and returns the number of complete records read.
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

    while (getline(inputFile, line) &&
        runnerCount < MAX_RUNNERS)
    {
        if (line.empty())
        {
            continue;
        }

        istringstream lineStream(line);

        // The provided file begins with a header such as "5 7".
        // Skip it if it is present.
        if (firstLine)
        {
            firstLine = false;

            int possibleRunnerCount;
            int possibleDayCount;

            if (lineStream >> possibleRunnerCount
                >> possibleDayCount)
            {
                string extraText;

                if (!(lineStream >> extraText))
                {
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


// Calculates weekly total and daily average
// for each valid runner record.
void calculateTotalsAndAverages(
    Runner runners[],
    int runnerCount
)
{
    for (int runner = 0;
        runner < runnerCount;
        runner++)
    {
        runners[runner].total = 0.0;

        for (int day = 0; day < NUM_DAYS; day++)
        {
            runners[runner].total +=
                runners[runner].miles[day];
        }

        runners[runner].average =
            runners[runner].total / NUM_DAYS;
    }
}


// Displays all valid runner records
// in a formatted table.
void displayResults(
    const Runner runners[],
    int runnerCount
)
{
    string days[NUM_DAYS] =
    {
        "Day 1",
        "Day 2",
        "Day 3",
        "Day 4",
        "Day 5",
        "Day 6",
        "Day 7"
    };

    cout << "\nMarathon Runners - Structured Data\n\n";

    cout << left << setw(12) << "Runner";

    for (int day = 0; day < NUM_DAYS; day++)
    {
        cout << right << setw(8) << days[day];
    }

    cout << setw(10) << "Total"
        << setw(10) << "Average"
        << endl;

    cout << fixed << setprecision(2);

    for (int runner = 0;
        runner < runnerCount;
        runner++)
    {
        cout << left
            << setw(12)
            << runners[runner].name;

        for (int day = 0;
            day < NUM_DAYS;
            day++)
        {
            cout << right
                << setw(8)
                << runners[runner].miles[day];
        }

        cout << setw(10)
            << runners[runner].total
            << setw(10)
            << runners[runner].average
            << endl;
    }

    cout << "\nRunner records processed: "
        << runnerCount
        << endl;
}