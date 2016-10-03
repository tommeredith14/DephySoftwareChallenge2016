#include "dephygaitcycle.h"
#include <QApplication>
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
#include "gaitcycle.h"

bool readNextDataSet(ifstream & inputFile, Data & data)
{
    string target;
    if (inputFile >> target){
        inputFile >> target;
        inputFile >> target;
        inputFile >> target;
        inputFile >> target;

        data.processString(target);


        return true;
    }
    else
        return false;
}

int main(int argc, char *argv[])
{
    /////////////////////////////QT Display Setup/////////////////////////////////
    QApplication a(argc, argv);
    DephyGaitCycle w;

    QLabel l;
    QPicture pi;
    QPainter p(&pi);

    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));
    p.drawLine(0, 0, 0, 700);
    p.drawLine(0,350,1800,350);
    p.drawText(20,100,"Legend");
    p.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap));
    p.drawText(20,115,"X - Accel");
    p.setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap));
    p.drawText(20,130,"Y - Accel");
    p.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap));
    p.drawText(20,145,"Z - Accel");
    p.setPen(QPen(Qt::cyan, 1, Qt::SolidLine, Qt::RoundCap));
    p.drawText(20,160,"X - Gyro");
    p.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
    p.drawText(20,175,"Y - Gyro");
    p.setPen(QPen(Qt::yellow, 1, Qt::SolidLine, Qt::RoundCap));
    p.drawText(20,190,"Z - Gyro");

    p.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
    p.drawText(20,600,"HS  - Heel Strike (Start of Cycle)");
    p.drawText(20,615,"FF   - Foot Flat");
    p.drawText(20,630,"MSt - Mid Stance");
    p.drawText(20,645,"HO  - Heel Off");
    p.drawText(20,660,"TO  - Toe Off");
    p.drawText(20,675,"MSw - Mid Swing");
/////////////////////////////////////////////////////////////////////////////////
    string csvFile = "walkData2.csv"; //change line to change the file being read
    ifstream inputFile (csvFile);
    p.drawText(300,680,QString::fromStdString(csvFile));

    Data  data, lastData;
    for (int i = 0; i < 21; i++)
    { //Moves past headers in the .csv to get to the data
        string waste;
        inputFile >> waste;

    }
    //Markers of the last time each phase was identified
    int lastHeelStrike = 0;
    int lastFootFlat = 0;
    int lastMidStance = 0;
    int lastHeelOff = 0;
    int lastToeOff = 0;
    int lastMidSwing = 0;

    //Keep the time that each input went above (or below) certain values to help identify phases
    int lastTimeZAccelHigh = -10000;  //accelz  > 15000
    int lastTimeZAccelLow = -10000;   //accelz < 0
    int lastTimeZAccelModerateHigh = -10000; //accelz > 9000
    int lastTimeXAccelHigh = -10000; //accelx higher than 5000
    int lastTimeXAccelLow = -10000; //accelx < -14000
    int lastTimeYGyroHigh = -10000; //gyro y > 6000
    int lastTimeYGyroLow = -10000; //gyro y < -6000

    //booleans for knowing when certain inputs are in a certain range at a given time
    bool ZAccelIsModerateLow = false; //accelz < 8000
    bool YGyroIsLow = false;

    //Store the time that a stable state for an imput began (inside a certain range for a significant period of time)
    int timeSinceYGyroStable = -10000;
    int timeSinceXAccelStable = -10000;
    int timeSinceZAccelStable = -10000;
    int totalTimeYGyroStable = -5000;
    int totalTimeXAccelStable = -5000;
    int totalTimeZAccelStable = -5000;



    while(readNextDataSet(inputFile,data)) //readNextDataSet stores the information from the next line of the spreadsheet in data
    {//Main loop runs until entire file has beed read

        ///////Set lastTime__Low/High variables if inputs are beyond given ranges////////
        if (data.accelx > ACCEL_X_HIGH)
            lastTimeXAccelHigh = data.time;
        if (data.accelx < ACCEL_X_LOW)
            lastTimeXAccelLow = data.time;
        if (data.accelz > ACCEL_Z_HIGH)
            lastTimeZAccelHigh = data.time;
        if (data.accelz > ACCEL_Z_MODERATE_HIGH)
            lastTimeZAccelModerateHigh = data.time;
        if (data.accelz < ACCEL_Z_LOW)
            lastTimeZAccelLow = data.time;
        if (data.gyroy > GYRO_Y_HIGH)
            lastTimeYGyroHigh = data.time;
        if (data.gyroy < GYRO_Y_LOW)
        {
            lastTimeYGyroLow = data.time;
            YGyroIsLow = true;
        }
        else
            YGyroIsLow = false;

        if (data.gyroy < GYRO_Y_MODERATE_LOW)
        {
            ZAccelIsModerateLow = true;
        }
        else
            ZAccelIsModerateLow = false;



        ///////Check whether each input is at a stable state.////////
        // If a variable is not stable, its timeSinceStable variable is set to a negative number,otherwise it is given the time that the stability began
        if (timeSinceYGyroStable < 0)
        { //not already stable. Check if it is now
            if (data.gyroy < GYRO_Y_STABLE_UPPER && data.gyroy > GYRO_Y_STABLE_LOWER && lastData.gyroy < GYRO_Y_STABLE_UPPER && lastData.gyroy > GYRO_Y_STABLE_LOWER)
                timeSinceYGyroStable = lastData.time;
        } //else: Input was already stable. Check to see if it no longer is, while ignoring random spikes in the data
        else if ((data.gyroy > GYRO_Y_STABLE_UPPER || data.gyroy < GYRO_Y_STABLE_LOWER )&& (lastData.gyroy > GYRO_Y_STABLE_UPPER || lastData.gyroy < GYRO_Y_STABLE_LOWER)) //to ignore random spikes
            timeSinceYGyroStable = -10000; //no longer in stable state

        if (timeSinceXAccelStable < 0)
        { //not already stable. Check if it is now
            if (data.accelx < ACCEL_X_STABLE_UPPER && data.accelx > ACCEL_X_STABLE_LOWER && lastData.accelx < ACCEL_X_STABLE_UPPER && lastData.accelx > ACCEL_X_STABLE_LOWER)
                timeSinceXAccelStable = lastData.time;
        }//else: Input was already stable. Check to see if it no longer is, while ignoring random spikes in the data
        else if ((data.accelx > ACCEL_X_STABLE_UPPER || data.accelx < ACCEL_X_STABLE_LOWER )&& (lastData.accelx > ACCEL_X_STABLE_UPPER || lastData.accelx < ACCEL_X_STABLE_LOWER)) //to ignore random spikes
            timeSinceXAccelStable = -10000; //no longer in stable state

        if (timeSinceZAccelStable < 0)
        { //not already stable. Check if it is now
            if (data.accelz < ACCEL_Z_STABLE_UPPER && data.accelz > ACCEL_Z_STABLE_LOWER && lastData.accelz < ACCEL_Z_STABLE_UPPER && lastData.accelz > ACCEL_Z_STABLE_LOWER)
                timeSinceZAccelStable = lastData.time;
        }//else: Input was already stable. Check to see if it no longer is, while ignoring random spikes in the data
        else if ((data.accelz > ACCEL_Z_STABLE_UPPER || data.accelz < ACCEL_Z_STABLE_LOWER )&& (lastData.accelz > ACCEL_Z_STABLE_UPPER || lastData.accelz < ACCEL_Z_STABLE_LOWER)) //to ignore random spikes
            timeSinceZAccelStable = -10000; //no longer in stable state


        //Calculate total time since stability reached, giving a large negative value if input is not stable
        if (timeSinceYGyroStable > 0)
            totalTimeYGyroStable = data.time - timeSinceYGyroStable;
        else
            totalTimeYGyroStable = -5000;

        if (timeSinceXAccelStable > 0)
            totalTimeXAccelStable = data.time - timeSinceXAccelStable;
        else
            totalTimeXAccelStable = -5000;

        if (timeSinceZAccelStable > 0)
            totalTimeZAccelStable = data.time - timeSinceZAccelStable;
        else
            totalTimeZAccelStable = -5000;


        //////////////////////////////////////////
        /*  Check for indicators of each phase  */
        //////////////////////////////////////////

        //These booleans will be calculated for each phase check      //
        //If all three booleans are true, then the phase is identified//
        bool accelXcondition = false;
        bool accelZcondition = false;
        bool gyroYcondition = false;

        ////Check Heel strike//////
        if (data.time - lastHeelStrike > MINIMUM_CYCLE_WAIT)
        {
            accelXcondition = (data.time - lastTimeXAccelHigh) < HEEL_STRIKE_THRESHHOLD;
            accelZcondition = (data.time - lastTimeZAccelHigh) < HEEL_STRIKE_THRESHHOLD && (data.time - lastTimeZAccelLow) < HEEL_STRIKE_THRESHHOLD;
            gyroYcondition = (data.time - lastTimeYGyroHigh) < HEEL_STRIKE_THRESHHOLD;
            if (accelXcondition && accelZcondition && gyroYcondition)
            {
                cout << "Heel strike at time = " << data.time << endl;
                p.setPen(QPen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap));
                p.drawText(data.time/5,21,"HS");//Mark the phase indicator on the picture
                lastHeelStrike = data.time;
            }
        }
        //////Check foot flat//////
        if (data.time - lastFootFlat > MINIMUM_CYCLE_WAIT)
        {
            accelXcondition = (totalTimeXAccelStable) > FOOT_FLAT_STABLE_THRESHHOLD;
            accelZcondition = (totalTimeZAccelStable) > FOOT_FLAT_STABLE_THRESHHOLD;
            gyroYcondition = (data.time - lastTimeYGyroHigh) < FOOT_FLAT_HIGH_THRESHHOLD && (totalTimeYGyroStable) > FOOT_FLAT_STABLE_THRESHHOLD;
            if (accelXcondition && accelZcondition && gyroYcondition)
            {
                cout << "Foot flat at time = " << data.time << endl;
                p.setPen(QPen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap));
                p.drawText(data.time/5,21,"FF"); //Mark the phase indicator on the picture
                lastFootFlat = data.time;
            }
        }
        ///////Check Mid stance//////
        if (data.time - lastMidStance > MINIMUM_CYCLE_WAIT)
        {
            accelXcondition = (totalTimeXAccelStable) > MID_STANCE_STABLE_MIN && (totalTimeXAccelStable) < MID_STANCE_STABLE_MAX;
            accelZcondition = (totalTimeZAccelStable) > MID_STANCE_STABLE_MIN && (totalTimeZAccelStable) < MID_STANCE_STABLE_MAX;
            gyroYcondition = (totalTimeYGyroStable)  > MID_STANCE_STABLE_MIN && (totalTimeYGyroStable)  < MID_STANCE_STABLE_MAX;
            if (accelXcondition && accelZcondition && gyroYcondition)
            {
                cout << "Mid Stance = " << data.time << endl;
                p.setPen(QPen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap));
                p.drawText(data.time/5,21,"MSt");//Mark the phase indicator on the picture
                lastMidStance = data.time;
            }
        }
        ////////Check Heel off//////
        if (data.time - lastHeelOff > MINIMUM_CYCLE_WAIT)
        {
            accelXcondition = (data.time - lastTimeXAccelLow) < HEEL_OFF_WANTED_TRAIT_THRESHHOLD && (data.time - lastTimeXAccelHigh) > HEEL_OFF_UNWANTED_TRAIT_MIN_THRESHHOLD;
            accelZcondition = (data.time - lastTimeZAccelHigh) < HEEL_OFF_WANTED_TRAIT_THRESHHOLD && (data.time - lastTimeZAccelLow) > HEEL_OFF_UNWANTED_TRAIT_MIN_THRESHHOLD;
            gyroYcondition = (data.time - lastTimeYGyroHigh) < HEEL_OFF_WANTED_TRAIT_THRESHHOLD;
            if (accelXcondition && accelZcondition && gyroYcondition)
            {
                cout << "Heel off at time = " << data.time << endl;
                p.setPen(QPen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap));
                p.drawText(data.time/5,21,"HO");//Mark the phase indicator on the picture
                lastHeelOff = data.time;
            }
        }
        ///////Check Toe Off//////
        if (data.time - lastToeOff > MINIMUM_CYCLE_WAIT)
        {
            accelZcondition = (data.time - lastTimeZAccelHigh) < TOE_OFF_THRESHHOLD ;
            gyroYcondition = YGyroIsLow && (data.time - lastTimeYGyroHigh) < TOE_OFF_THRESHHOLD;
            if (accelZcondition && gyroYcondition)
            {
                cout << "Toe off at time = " << data.time << endl;
                p.setPen(QPen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap));
                p.drawText(data.time/5,600,"TO");//Mark the phase indicator on the picture
                lastToeOff = data.time;
            }
        }
        //////Check Mid Swing/////
        if (data.time - lastMidSwing > MINIMUM_CYCLE_WAIT)
        {
            accelZcondition = (ZAccelIsModerateLow && (data.time - lastTimeZAccelModerateHigh) < MID_SWING_WANTED_TRAIT_MAX_THRESHHOLD && (data.time - lastTimeZAccelHigh) > MID_SWING_UNWANTED_TRAIT_MIN_THRESHHOLD);
            gyroYcondition = YGyroIsLow && (data.time - lastTimeYGyroHigh) > MID_SWING_UNWANTED_TRAIT_MIN_THRESHHOLD;
            if (accelZcondition && gyroYcondition)
            {
                cout << "Mid Swing at time = " << data.time << endl;
                p.setPen(QPen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap));
                p.drawText(data.time/5,21,"MSw");//Mark the phase indicator on the picture
                lastMidSwing = data.time;
            }
        }
        /////QT Drawing//////
        //Draw the new data points on the image//
        p.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap));
        p.drawLine(lastData.time/5, -lastData.accelx/100 + 350, data.time/5, -data.accelx/100+350);
        p.setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap));
        p.drawLine(lastData.time/5, -lastData.accely/100 + 350, data.time/5, -data.accely/100+350);
        p.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap));
        p.drawLine(lastData.time/5, -lastData.accelz/100 + 350, data.time/5, -data.accelz/100+350);
        p.setPen(QPen(Qt::cyan, 1, Qt::SolidLine, Qt::RoundCap));
        p.drawLine(lastData.time/5, -lastData.gyrox/100 + 350, data.time/5, -data.gyrox/100+350);
        p.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
        p.drawLine(lastData.time/5, -lastData.gyroy/100 + 350, data.time/5, -data.gyroy/100+350);
        p.setPen(QPen(Qt::yellow, 1, Qt::SolidLine, Qt::RoundCap));
        p.drawLine(lastData.time/5, -lastData.gyroz/100 + 350, data.time/5, -data.gyroz/100+350);



        lastData = data;
    }//while loop end


    ////////////////QT Draw the Picture///////////
    p.end(); // Don't forget this line!
    l.setPicture(pi);
    l.show();
    //////////////////////////////////

    inputFile.close();
    return a.exec();
}
