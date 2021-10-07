# eBike-Hack
For my 2016 Haibike SDURO Trekking 5.0 500Wh
Allows to have motor support up to 50Km/h (in theorie)
Do not test in public areas, i am not responsible for any damages to you, your bike or others

To use this modification: 
-get microcontroller, i used Arduino\
-upload code to controller\
-take out bike battery\
-find cables of the sensor and the bike computer\
-find power supply for the controller
-connect cables from sensor to input and ground + put high resistance between input and ground\
-connect cables from bike computer to output and ground\
-connect power supply to microcontroller\
-put back bike battery

test everything, i hope it works\
maybe you have to adjust the triggerpoints in the code so the functions switch at the speed you want them to switch\
the set triggerpoints are for 28inch wheel
