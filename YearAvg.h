#ifndef DATASTRUCTURESSTL_YEARAVG_H
#define DATASTRUCTURESSTL_YEARAVG_H

class YearAvg {
public:

    YearAvg();
    YearAvg(double temp, int year, double rain);

    double getTemp() const{
        return temp;
    }

    int getYear() const{
        return year;
    }

    double getRain() const{
        return rain;
    }

    //Using operator overloading to make set work with object YearAvg
    bool operator < (const YearAvg& yrObj) const {
        return (temp + year + rain) < (yrObj.getTemp() + yrObj.getYear() + yrObj.getRain());
    }

    //Method, that tells sort algorithm in what way should it sort data in vector
    //Here data is sorted according to temp value, comparing two objects of YearAvg class
    static bool sortByTemperature (const YearAvg &leftObject, const YearAvg &rightObject){
        return leftObject.temp < rightObject.temp;
    }

    ~YearAvg(){

    };

private:
    double rain;
    double temp;
    int year;
};

#include "YearAvg.cpp"

#endif //DATASTRUCTURESSTL_YEARAVG_H
