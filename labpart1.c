#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

int main(int argc, char *argv[])
{
	struct utsname data;	
	if(uname(&data) != 0);
	
	printf("Lab1, Part A\n");
	printf("Name: Sharvita Paithankar\n ");
	printf("System Name: %s\n", data.sysname);
	printf("Node Name: %s\n", data.nodename);
	printf("Release: %s\n", data.release);
	printf("Version: %s\n", data.version);
	printf("Machinee: %s\n", data.machine);
	FILE *fp = fopen("/proc/stat", "r");
	if(fp = NULL){
		perror("Cannot open file");
		return(-1);
	}

	char line[1000];
	char stringToFind[] = "btime";
	while(fgets(line,sizeof(line),fp) != NULL){
		if(strstr(line, stringToFind) != NULL){
			printf("%s", line);
		}
	}
	return 0;

}
