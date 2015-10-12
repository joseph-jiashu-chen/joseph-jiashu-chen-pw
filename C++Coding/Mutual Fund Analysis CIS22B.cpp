/* Name: Jia-Shu (Joseph) Chen ID: 11204321
   CIS22B Assignment 5 MW
   Compiler: GNU GCC Compiler on Codeblocks*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstring>
#include <string>
#include <cstdlib>


using namespace std;
int changedatetoint(string tempdate);
int convertstring(const string& tempdate);
void printdate(int date);
class MutualFund
{
private:
    int latestdate;
    string ticker;
    float latestclose;
    float closeprice[300];
    int dates[300];
    float day50moving;
    float day200moving;
    float percentgain;
    string recommendation;
    float minimumclose;
    float maximumclose;
public:
    void readHistoryFile(string file);
    void assignTicker(string tickervar);
    void report() const;

};

int main()
{

    MutualFund vbmfx;
    vbmfx.assignTicker("VBMFX");
    vbmfx.readHistoryFile("VBMFXhistory.txt");
    vbmfx.report();

    MutualFund vtsmx;
    vtsmx.assignTicker("VTSMX");
    vtsmx.readHistoryFile("VTSMXhistory.txt");
    vtsmx.report();
}

void MutualFund::assignTicker(string tickervar)
{
    ticker = tickervar;
}

void MutualFund::readHistoryFile(string file)
{
    const int maxlength = 700;
    char line[maxlength];
    ifstream infile;
    infile.open(file.c_str());
    if(!infile)
    {
        cout << "File Open Error." << endl;
        exit(1);
    }

    infile.getline(line, maxlength);
    int linecounter = 0;
    char *p;
    string tempdate;
    float temp;
    for(int i = 0; i < 300; i++)
    {
        infile.getline(line, maxlength);
        if(linecounter == 0)
        {
            tempdate = strtok(line, ",");
            latestdate = changedatetoint(tempdate);
        }
        else
        {
            tempdate = strtok(line, ",");
            dates[linecounter] = changedatetoint(tempdate);

        }



        for(int counter = 0; counter < 5; counter++)
        {
            if(linecounter == 0 && counter == 3)
            {
                latestclose = atof(strtok(0, ","));
            }
            if(counter == 3)
            {
                p = strtok(NULL, ",");
                temp = atof(p);
                closeprice[linecounter] = temp;
            }
            else
            {
                p = strtok(NULL, ",");
            }
        }
        linecounter++;
    }

    dates[0] = latestdate;
    closeprice[0] = latestclose;
    float temp50;
    float temp200;
    for(int counter = 0; counter < 50; counter++)
    {
        temp50 += closeprice[counter];
    }
    day50moving = temp50/50;
    for(int counter = 0; counter < 200; counter++)
    {
        temp200 += closeprice[counter];
    }
    day200moving = temp200/200;

    float temppercent;
    temppercent = (latestclose - day200moving)/day200moving;
    percentgain = temppercent * 100;

    if(percentgain < -5)
    {
        recommendation = "Buy";
    }
    else if(percentgain > 5)
    {
        recommendation = "Sell";
    }
    else
    {
        recommendation = "Hold";
    }

    int tempcounter = 0;
    for(int counter = 0; counter < 300; counter++)
    {
        if(dates[counter] == latestdate - 10000)
        {
            tempcounter = counter;
        }
    }
    if(tempcounter == 0)  //in case latestdate - 10000 is not a market day.
    {
        for(int counter = 0; counter < 300; counter++)
        {
            if(dates[counter] == latestdate-9999)
            {
                tempcounter = counter;
            }
        }
    }
    if(tempcounter == 0) // in case latestdate - 9999 is not a market day.
    {
        for(int counter = 0; counter < 300; counter++)
        {
            if(dates[counter] == latestdate - 9998)
            {
                tempcounter = counter;
            }
        }
    }
    if(tempcounter == 0)  // in case latestdate - 9998 is not a market day.
    {
        for(int counter = 0; counter < 300; counter++)
        {
            if(dates[counter] == latestdate - 9997)
            {
                tempcounter = counter;
            }
        }
    }
    float minimumtemp = closeprice[0];
    for(int counter = 0; counter < tempcounter; counter++)
    {
        if(minimumtemp > closeprice[counter])
        {
            minimumtemp = closeprice[counter];
        }
    }
    minimumclose = minimumtemp;

    float maximumtemp = closeprice[0];
    for(int counter = 0; counter < tempcounter; counter++)
    {
        if(maximumtemp < closeprice[counter])
        {
            maximumtemp = closeprice[counter];
        }
    }
    maximumclose = maximumtemp;


    infile.close();
}

void MutualFund::report() const
{
    cout << "Fund: " << ticker << endl;
    cout << "Analysis Date: ";
    printdate(latestdate);
    cout << endl;
    cout << "Latest Close: $" << setprecision(4) << latestclose << endl;
    cout << "Minimum for the Last Year: $" << setprecision(4) << minimumclose << endl;
    cout << "Maximum for the Last Year: $" << setprecision(4) << maximumclose << endl;
    cout << "50 Day Moving Average: $" << setprecision(4) << day50moving << endl;
    cout << "200 Day Moving Average: $" << setprecision(4) << day200moving << endl;
    cout << "% Gain over 200 Day Moving Average: " << setprecision(3) << percentgain << "%" << endl;
    cout << "Recommendation: " << recommendation << endl;
    cout << endl;
}

int changedatetoint(string tempdate)
{
    int date = 0;

    date += 10000*convertstring(tempdate.substr(0,4));
    date += 100*convertstring(tempdate.substr(5,2));
    date += convertstring(tempdate.substr(8,2));

    return date;

}

int convertstring(const string& tempdate)
{
    if(tempdate.length() == 4)
        return 1000*(tempdate[0]-'0') + 100*(tempdate[1]-'0') + 10*(tempdate[2]-'0') + (tempdate[3]-'0');
    else
        return 10*(tempdate[0]-'0') + (tempdate[1]-'0');
}

void printdate(int date)
{
    cout << (date/100)%100 <<  "/"  << date%100 << "/" << (date/10000)%100;
}


