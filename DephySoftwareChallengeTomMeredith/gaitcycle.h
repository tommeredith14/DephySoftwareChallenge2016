#ifndef GAITCYCLE_H
#define GAITCYCLE_H
#include <QtGui>
#include <QLabel>
#include <QPicture>
#include <QPainter>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;

//////Constants to be used by main loop////////

//Time threshhold constants. Certain events must occur within or not less than these time  constraints
const int MINIMUM_CYCLE_WAIT = 300;
const int HEEL_STRIKE_THRESHHOLD = 50;
const int FOOT_FLAT_STABLE_THRESHHOLD = 50;
const int FOOT_FLAT_HIGH_THRESHHOLD = 200;
const int MID_STANCE_STABLE_MIN = 225;
const int MID_STANCE_STABLE_MAX = 400;
const int HEEL_OFF_WANTED_TRAIT_THRESHHOLD = 80;
const int HEEL_OFF_UNWANTED_TRAIT_MIN_THRESHHOLD = 300;
const int TOE_OFF_THRESHHOLD = 90;
const int MID_SWING_WANTED_TRAIT_MAX_THRESHHOLD = 40;
const int MID_SWING_UNWANTED_TRAIT_MIN_THRESHHOLD = 250;

//High and Low constants. Cut offs for considering useful spikes in the data
const int ACCEL_X_HIGH = 5000;
const int ACCEL_X_LOW = -14000;
const int ACCEL_Z_HIGH = 15000;
const int ACCEL_Z_LOW = 0;
const int ACCEL_Z_MODERATE_HIGH = 9000;
const int GYRO_Y_HIGH = 6000;
const int GYRO_Y_LOW = -6000;
const int GYRO_Y_MODERATE_LOW = 8000;

//Stable range constants. The inputs have periods of time where they stay in
//these ranges constantly. Usefull for identifying phases.
const int ACCEL_X_STABLE_UPPER = 0;
const int ACCEL_X_STABLE_LOWER = -5000;
const int ACCEL_Z_STABLE_UPPER = 10000;
const int ACCEL_Z_STABLE_LOWER = 5000;
const int GYRO_Y_STABLE_UPPER = 2200;
const int GYRO_Y_STABLE_LOWER = -500;


// Data class
// Stores the 6 inputs and the time of the current input
// Some functions are included to abstract or make certain operations simpler in main.
class Data
{
    public:
        int time;
        int accelx;
        int accely;
        int accelz;
        int gyrox;
        int gyroy;
        int gyroz;

        Data()
        { //constructor
            time = 0;
            accelx = 0;
            accely = 0;
            accelz = 0;
            gyrox = 0;
            gyroy = 0;
            gyroz = 0;
        }

        Data & operator =(Data other)
        { //for setting lastData = Data;
            time = other.time;
            accelx = other.accelx;
            accely = other.accely;
            accelz = other.accelz;
            gyrox = other.gyrox;
            gyroy = other.gyroy;
            gyroz = other.gyroz;
            return (*this);
        }

        //Takes the string input from the .csv file and breaks it into individual inputs
        bool processString(string input)
        { //incoming string looks like : 2016,2,-3804,526,7102,66,2,-31,13203,1067,1021,444,0,0,0,199,206,131,2,1

            input.erase(0,input.find(",")+1); //gets rid of the 2016 at the start of every string

            size_t pos;
            string nextValue;
            //timestamp
            pos = input.find(",");
            nextValue = input.substr(0,pos);
            time = atoi(nextValue.c_str());
            input.erase(0,pos+1);

            //accel x
            pos = input.find(",");
            nextValue = input.substr(0,pos);
            accelx = atoi(nextValue.c_str());
            input.erase(0,pos+1);

            //accel y
            pos = input.find(",");
            nextValue = input.substr(0,pos);
            accely = atoi(nextValue.c_str());
            input.erase(0,pos+1);

            //accel z
            pos = input.find(",");
            nextValue = input.substr(0,pos);
            accelz = atoi(nextValue.c_str());
            input.erase(0,pos+1);

            //gyro x
            pos = input.find(",");
            nextValue = input.substr(0,pos);
            gyrox = atoi(nextValue.c_str());
            input.erase(0,pos+1);

            //gyro y
            pos = input.find(",");
            nextValue = input.substr(0,pos);
            gyroy = atoi(nextValue.c_str());
            input.erase(0,pos+1);

            //gyro z
            pos = input.find(",");
            nextValue = input.substr(0,pos);
            gyroz = atoi(nextValue.c_str());
            input.erase(0,pos+1);
            return true;
        }

        void output(ostream & out){ //for debugging purposes
            out << time << " " << accelx << " "<< accely << " "<< accelz << " "<< gyrox << " " << gyroy << " "<< gyroz << endl;
        }
};

bool readNextDataSet(ifstream & inputFile, Data & data);


#endif // GAITCYCLE_H
