
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    //******************************************************************************
    //PART 1
	char inputFile[1000]; //this had the inputFile
	sprintf(inputFile, "/proc/stat");
	FILE *f = fopen(inputFile, "r");
	char BT[50];//hold string name
	fscanf(f, "%s", &BT);
	while (strcmp("btime",BT) != 0){
		//point to next until string is found
		fscanf(f, "%s", &BT);}
	int Btime;//hold int value
	fscanf(f, "%d", &Btime);//store value
    //convert vakues of minutes seconds and hours
    int Min = Btime/ 60;
    int Sec = Btime % 60;
    int Hr = Min / 60;
    
    Min = Min % 60;//minutes
    int Day = Hr / 24;
    Hr = Hr % 24;//hour
    int Month = Day / 30;
    int Year = Day / 365;//years
    Year = Year + 1970;
    Day = Day % 30;//day
    Month = Month % 12;//month
    
    //printhing the b time to console
    printf("btime = %d-%d-%d %d:%d:%d\n",Year, Month, Day, Hr, Min, Sec);
    rewind(f);//go back to file
    
    
    //******************************************************************************
    //PART 3
    fscanf(f, "%s", &BT);//override BT with CPU
    int userMemory;
    int skip;
    int systemMemory;
    fscanf(f, "%d", &userMemory);//store value
    fscanf(f, "%d", &skip);//don't store value
    fscanf(f, "%d", &systemMemory);//store value
    fclose(f);
    
    //*****************************************************************************
    //PART 2
    //use this to take in time
    sprintf(inputFile, "/proc/uptime");
    //opens file
    FILE *c = fopen(inputFile, "r");
    
    int one;
    int two;
    int total;
    fscanf(c, "%d", &one);//store value
    fscanf(c, "%d", &two);//store value
    total = one + two;
    //convert this to minutes, seconds and hours
    int Minutes = total / 60;
    int Hours = Minutes / 60;
    int Seconds = total % 60;//seconds
    
    
    Minutes = Minutes % 60;//minutes
    int Days = Hours / 24;//days
    Hours = Hours % 24;//hours
    printf("Time since last System Boot: %d:%d:%d:%d\n",Days, Hours, Minutes, Seconds);
    printf("User mode time: %d seconds\nSystem mode time: %d seconds\n", userMemory, systemMemory);
    fclose(c);
    
    
    //*****************************************************************************
    //PART 4
    //take in memory info
    sprintf(inputFile, "/proc/meminfo");
    //ask file to open
    FILE *d = fopen(inputFile, "r");
    //space to hold name
    char tot[100];
    char Avail[100];
    //scan the file
    fscanf(d, "%s", &tot);
    
    //this loop goes through and finds strings
    while (strcmp("MemTotal:",tot) != 0){
        fscanf(d, "%s", &tot);
    }
    int TotalNum;//hold int value
    fscanf(d, "%d", &TotalNum);//store value
    printf("Total memory = %d kB\n", TotalNum);
    rewind(d);//pointer back at the beginning of file
    fscanf(d, "%s", &Avail);
    
    
    while (strcmp("MemAvailable:",Avail) != 0){
        //point to next until string is found
        fscanf(d, "%s", &Avail);
    }
    int Anum;//hold int value
    fscanf(d, "%d", &Anum);//store value
    printf("Available memory = %d kB\n", Anum);
    fclose(d);
}
