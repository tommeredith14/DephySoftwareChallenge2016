This is my entry for Dephy's Software/Controls Engineer Design Challenge

In the challenge, a subject walks 6 steps forward with a sensor containing a 3 axis accelerometer and a 3 axis gyroscope on their foot. I am given 2 .csv files (walkData1.csv and walkData2.csv) constaining the sensor output for two trials.
The challenge was to identify the start of gait cycle, along with each phase as a bonus, using the data in real time.

Refer to "DephySoftwareChallengeExplanation.docx" for explanation of my apporach.
Refer to "dephyResults1.PNG" and "dephyResults2.PNG" for the results from processing "walkData1.csv" and "walkData2.csv" respectively.

All my code is in "main.cpp" and "gaitcycle.h". All other files are Qt related files that I did not touch.
