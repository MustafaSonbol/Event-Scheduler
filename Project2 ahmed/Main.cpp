#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Event.h"
#include<ctime>

using namespace std;

int main()
{
    time_t ttime = time(0);
    tm* local_time = localtime(&ttime);
    int year = 1900 + local_time->tm_year;
    int month= 1 + local_time->tm_mon ;
    int day= local_time->tm_mday;
  
	Event e;
	e.event_menu(month,day,year);
	return 0;
}