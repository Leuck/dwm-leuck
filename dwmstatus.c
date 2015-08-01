/*
 * escrever uma funcao que coleta informacoes do sistema e as escreve 
 * em uma string chamada stext
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static void updatestatus(void);
char * battery(char * bat);

static char stext[256];
static clock_t waitms=1000; // refresh time in ms

int main()
{
	//system("/usr/bin/dwm &");
	//char wallpapercmd[]="nitrogen --restore";
	while ( 1 )
	{
		updatestatus();
		usleep( waitms * 1000 );
	}

}

static void updatestatus(void)
{
	char dates[80], batterys[80];
	//char wallpapercmd[]="nitrogen --restore";
	char setrootcmd[120]="xsetroot -name '";

	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	strftime (dates,80,"%d-%m-%y %R",timeinfo);
	
	strcpy (stext,battery(batterys) );
	strcat (stext,dates);
	strcat(setrootcmd,stext);
	strcat(setrootcmd,"'");

	//system(wallpapercmd);
	//puts (setrootcmd);
	system(setrootcmd);

}

char * battery(char * bat)
{
	FILE * now;
	FILE * full;
	FILE * stat;
	char buffer[14], strstatus[80];
	int bnow, bfull, bstat;

	now = fopen("/sys/class/power_supply/BAT1/charge_now","r");
	full = fopen("/sys/class/power_supply/BAT1/charge_full","r");
	stat = fopen("/sys/class/power_supply/BAT1/status","r");

	if ( now == NULL || full == NULL || stat == NULL )
		return "";

	fgets(buffer,10,now);
	fclose(now);
	bnow = atoi(buffer);

	fgets(buffer,10,full);
	fclose(full);
	bfull = atoi(buffer);
	
	fgets(buffer,12,stat);
	fclose(stat);

	/* for some reason Charging has a newline and the others dont */
	if ( (!memcmp(buffer,"Charging",4) ) || (!memcmp(buffer,"Unknown",4)))
		buffer[strlen(buffer)-1] = '\0';
	else if ( !memcmp(buffer,"Full",4) )
	{
		buffer[strlen(buffer)-1] = '\0';
		strcpy(bat,buffer);
		strcat(bat," ");
		return bat;
	}

	strcpy(strstatus,buffer);
	
	bstat = (100 * bnow )/bfull;
	sprintf(buffer," %i%%",bstat);
	strcat(strstatus,buffer);
	
	sprintf(bat, "%s ", strstatus);

	return bat;
}

