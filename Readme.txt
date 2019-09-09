*******************************************************
*  Name      :  Sharvita Paithankar        
*  Student ID:  108172438               
*  Class     :  Operating Systems          
*  HW#       :  Lab 1              
*  Due Date  :  February 26 2019
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

The program part A uses the uname function to get system information. You can see the following information about the system:
System Name.
Current release level of operating system
Current version level of operating system
Machine name or hardware type of the machine
Node name of the machine
Part B proves this information:
The time when system was last booted. (File name: /proc/stat). Look for line with the label btime. Time is in seconds since 1970-01-01 (epoch time). Display the time in the format yyyy-mm-dd hh:mm:ss.
The amount of time since system was last booted (File name: /proc/uptime). This file contains two numbers: the uptime of the system in seconds and the amount of time spent in idle process in seconds. Display the amount of time since system was last booted in the form dd:hh:mm:ss.
Amount of time that the CPU has spent in user mode and system mode. (File name: /proc/stat). Use the line with label cpu. The first number is the time spent in user mode and the third number is the time spent in system mode.
The total amount of memory in the system and the amount of memory currently available. (File name: /proc/meminfo). Use the lines with labels MemTotal and MemAvailable.



*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
   Main program.  This is the driver program that calls multiple sub-functions to call functions to create objects, randomize input and create new objects.


*******************************************************
*  Circumstances of programs
*******************************************************

   The program compiles and runs successfully on linux

   The program was developed and tested on gnu g++ 4.8.2.  It was 
   compiled, run, and tested on gcc


*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the homework.  The homework file is compressed.  
   To uncompress it use the following commands 
       % unzip Sharvita_Paithankar_Lab1.zip

   Now you should see a directory named homework with the files:
        Labpart1.c
	labpart2.c

2. Build the program.

    Change to the directory that contains the file by:
    % cd Lab1

    Compile the program by:
    Gcc labpart1.c or gcc labpart2.c

3. Run the program by:
   % ./a.out

4. Delete the obj files, executables, and core dump by
   %./make clean
