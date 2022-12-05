#include "DualHeap.cpp"
#include "Selection.cpp"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// ----------------------------------
// Program to sort records in a file
// ----------------------------------

int main(int argc, const char* argv[])
{
    ifstream inFile;
    ofstream outFile, runFile;
    string inFileName, outFileName, runFileName;
    string flag;
    char delimiter;
    int inValue;
    string strValue;

    // File Operations

    cout << "Please enter input filename: ";
    cin >> inFileName;
    inFile.open(inFileName.c_str());
    if (!inFile)
    {
        cout << "Invalid filename.";
        return 0;
    }
    cout << "Please enter output filename: ";
    cin >> outFileName;
    outFile.open(outFileName.c_str());

    // Retrieving records from input file

    getline(inFile, flag, '|');
    if (flag == "str")
    {

        // instantiate algorithm class with type string
        DualHeap<string> h(10);

        // read and insert all values into algorithm
        while (getline(inFile, strValue, '|'))
        {
            h.put(strValue);
        }
        /* retrieve the vector of vectors; each vector is
        a sorted list of items */

        vector<vector<string> > v = h.retrieve();

        // Generating run files.

        stringstream ss;
        for (int i = 0; i < v.size(); i++)
        {
            ss.str("");
            ss.clear();
            ss << inFileName << "_run" << i + 1 << ".txt";
            runFileName = ss.str();
            runFile.open(runFileName.c_str());
            for (int j = 0; j < v[i].size(); j++)
            {
                runFile << v[i][j] << "|";
            }
            runFile.close();
        }

        // Sorting.

        Selection<string> t(v);
        t.sort();
        vector<string> r = t.retrieve();

        // Saving sorted string records to output file.

        outFile << "string|";
        for (int i = 0; i < r.size(); i++)
        {
            outFile << r[i] << "|";
        }
        outFile << endl;

        ofstream outFile2;
        outFile2.open("logFile.txt");

        outFile2 << "The unsorted records are from the data file: " << inFileName << endl;

        outFile2 << "The sorted records are placed in the data file called: " << outFileName << endl;

        t.logFile(outFile2);

        cout << "Sorting records and saving into a file succeeded!\n";
    }
    else if (flag == "int")
    {
        // instantiate algorithm class with type <int>
        DualHeap<int> h(10);

        // read and insert all values into algorithm
        while (inFile >> inValue)
        {
            h.put(inValue);
            inFile >> delimiter;
        }
        // retrieve the vector of vectors
        // each vector is a sorted list of items
        vector<vector<int> > v = h.retrieve();

        // Generating run files

        stringstream ss;
        for (int i = 0; i < v.size(); i++)
        {
            ss.str("");
            ss.clear();
            ss << inFileName << "_run" << i + 1 << ".txt";

            runFileName = ss.str();
            runFile.open(runFileName.c_str());
            for (int j = 0; j < v[i].size(); j++)
            {
                runFile << v[i][j] << "|";
            }
            runFile.close();
        }

        // Sorting.
        Selection<int> t(v);
        t.sort();
        vector<int> r = t.retrieve();

        // Saving sorted integer records to output file

        outFile << "int|";
        for (int i = 0; i < r.size(); i++)
        {
            outFile << r[i] << "|";
        }
        outFile << endl;

        ofstream outFile2;
        outFile2.open("logFile.txt");

        outFile2 << "The unsorted records are from the data file: " << inFileName << endl;

        outFile2 << "The sorted records are placed in the data file called: " << outFileName << endl;

        t.logFile(outFile2);

        cout << "Sorting records and saving into file succeeded!\n";
    }
    else
    {
        cout << "The data file is not valid: the first field should specify if data is string or integer by using these flags: \"str\", \"int\".\n";
    }
    inFile.close();
    outFile.close();

    //system("pause");
    return 0;
}