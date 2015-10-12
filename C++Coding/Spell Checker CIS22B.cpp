/*Name:Jia-Shu (Joseph) Chen ID: 11204321
  CIS22B Assignment 3 MW
  Compiler: GNU GCC Compiler on Codeblocks*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

void sortdictionary(string secondarray[]);
void binarysearch(char* fourtharray[], string secondarray[], int counter4, int line);


int wordsfilesize = 23907;
int main()
{
    ifstream infile;
    ifstream infile2;
    infile.open("Assignment3Words.txt");
    infile2.open("Assignment3Gettysburg.txt");
    char *parray = new char[wordsfilesize];
    string secondarray[wordsfilesize];

    if(!infile)
    {
        cout << "File Open Error." << endl;
        return 1;
    }
    if(!infile2)
    {
        cout << "File Open Error." << endl;
        return 1;
    }


    int counter1 = 0;
    while(infile >> parray)
    {
        for(int counter = 0; parray[counter] != '\0'; counter++)
        {
            if(parray[counter] >= 'A' && parray[counter] <= 'Z')
            {
                parray[counter] += 32;
            }
        }
        if(strchr(parray, '\0'))
        {
            secondarray[counter1] = string(strtok(parray, "\0"));
            counter1++;
        }
    }

    sortdictionary(secondarray);


    const int maxcharsperline = 512;
    const int maxwordsperline = 30;
    const char* const DELIMITER = " ,.-";

    int line = 1;
    while(!infile2.eof())
    {
        char thirdarray[maxcharsperline];
        infile2.getline(thirdarray, maxcharsperline);

        for(int counter5 = 0; thirdarray[counter5] != '\0'; counter5++)
        {
            if(thirdarray[counter5] >= 'A' && thirdarray[counter5] <= 'Z')
            {
                thirdarray[counter5] += 32;
            }
        }



        int n = 0;
        char* fourtharray[maxwordsperline] = {};
        fourtharray[0] = strtok(thirdarray, DELIMITER);
        if(fourtharray[0])
        {
            for(n=1; n < maxwordsperline; n++)
            {
                fourtharray[n] = strtok(0, DELIMITER);
                if(!fourtharray[n])break;
            }
        }



        for(int counter4 = 0; counter4 < n; counter4++)
        {
            binarysearch(fourtharray, secondarray, counter4, line);
        }
        line++;
    }


    delete [] parray;
    infile.close();
    infile2.close();
    return 0;
}

void sortdictionary(string secondarray[])
{
    int minindex;
    for(int counter = 0; counter < wordsfilesize - 1; counter++)
    {
        minindex = counter;
        for(int counter2 = counter + 1; counter2 < wordsfilesize; counter2++)
        {
            if(secondarray[counter2] < secondarray[minindex])
            {
                minindex = counter2;
            }
        }
        if(minindex != counter)
        {
            string temp = secondarray[counter];
            secondarray[counter] = secondarray[minindex];
            secondarray[minindex] = temp;
        }
    }
}


void binarysearch(char* fourtharray[], string secondarray[], int counter4, int line)
{
    int lowest = 0;
    int highest = 23906;
    int middle;
    string tempstring;
    bool found = false;
    while(found == false && lowest <= highest)
    {
        tempstring = fourtharray[counter4];
        int length = tempstring.length();
        size_t alert = tempstring.find("ly");
        if(alert != std::string::npos)
        {
            tempstring = tempstring.substr(0, length-2);
        }

        size_t alert2 = tempstring.find("ed");
        if(alert2 != std::string::npos && tempstring[tempstring.length() - 2] == 'e')
        {
            tempstring = tempstring.substr(0, length-1);
        }

        size_t alert3 = tempstring.find("s");
        if(alert3 != std::string::npos && tempstring[tempstring.length()] == 's')
        {
            tempstring = tempstring.substr(0, length-1);
        }


        middle = (highest + lowest)/2;
        if(secondarray[middle] == tempstring)
        {
            found = true;
        }
        else if(secondarray[middle] < tempstring)
        {
            lowest = middle + 1;
        }
        else
        {
            highest = middle - 1;
        }

    }
    if(found == false)
    {
        cout << "Misspelled word, " << fourtharray[counter4] << " on line " << line << endl;
        tempstring.clear();
    }
}













