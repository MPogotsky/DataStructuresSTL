#include <iostream>
#include <iomanip>
#include <string>

#include <sstream>
#include <fstream>

#include <algorithm>
#include <vector>
#include <set>
#include <map>

#include "YearAvg.h"

using namespace std;

template<typename T>
void printVect(const vector<T> &vect) {
    cout << setw(13) << "Temperature: " << setw(10) << "Year: " << setw(10) << "Rain: " << endl;
    for (const YearAvg &el: vect) {
        cout << setw(10) << el.getTemp() << setw(10) << el.getYear() << setw(10) << el.getRain() << endl;
    }
}

void printSet(const set<YearAvg> &st) {
    cout << setw(13) << "Temperature: " << setw(10) << "Year: " << setw(10) << "Rain: " << endl;
    for (auto &it : st) {
        cout << setw(10) << it.getTemp() << setw(10) << it.getYear() << setw(10) << it.getRain() << endl;
    }
}

//Searching for the element in a map with the yearToSearch key using find() and writing it`s value
void printInfo(const int &yearToSearch, const map<int, YearAvg> &mp) {
    if (mp.find(yearToSearch) != mp.end()) {
        cout << "Year: " << yearToSearch << endl;
        cout << "Temperature: " << mp.find(yearToSearch)->second.getTemp() << endl;
        cout << "Rain: " << mp.find(yearToSearch)->second.getRain() << endl;
    }else{
        cerr << "No such element" << endl;
    }
}

set<YearAvg> intoSet(const vector<YearAvg> &avgs) {
    set<YearAvg> st;
    for (const YearAvg &elementOfAvgs : avgs) {
        st.emplace(elementOfAvgs);
    }
    return st;
}

string *splitLine(string *tokens, string line) {
    stringstream strStream(line);
    char delim = ';';
    //token is "temple" string to hold splited parts of line
    string token;
    int i = 0;
    while (getline(strStream, token, delim)) {
        tokens[i] = token;
        i++;
    }
    return tokens;
}

int main() {
    //Creating vector to store data from file
    vector<YearAvg> avgs;

    //Using map to fast searching by year
    map<int, YearAvg> mapOfAvgs;

    //Creating file stream to take data from file
    ifstream fromFile("..\\Files\\Book1.csv");

    string headers;
    string line;

    if (fromFile.is_open()) {
        getline(fromFile, headers);
        string tokens[3];
        while (getline(fromFile, line)) {

            //Function that splits line and returns array of tokens[<Temperature>,<Year>,<Rain>]
            splitLine(tokens, line);
            avgs.emplace_back(YearAvg(stod(tokens[0]), stoi(tokens[1]), stod(tokens[2])));

            //Inserting new pair(<year><object>) to map
            mapOfAvgs.insert(make_pair(stoi(tokens[1]), YearAvg(stod(tokens[0]), stoi(tokens[1]), stod(tokens[2]))));
        }

        fromFile.close();

    } else {
        cerr << "Can`t open file." << endl;
        return 0;
    }

    cout << "Data: " << endl;
    printVect(avgs);

    //Getting rid of duplicates using set
    set<YearAvg> setOfAvg = intoSet(avgs);//Returns set of objects YearAvg
    cout << "\n" << "Data in SET: " << endl;
    printSet(setOfAvg);

    vector<YearAvg> newAvgs;
    newAvgs.assign(setOfAvg.begin(), setOfAvg.end());

    //Sorting all data by Temperatures with a help of sortByTemperature method
    sort(newAvgs.begin(), newAvgs.end(), YearAvg::sortByTemperature);
    cout << "\n" << "Sorted by temp. SET: " << endl;
    printVect(newAvgs);

    cout << "Please, enter year to get weather data: " << endl;
    int yearToSearch;
    cin >> yearToSearch;
    printInfo(yearToSearch, mapOfAvgs);

    return 0;

}
