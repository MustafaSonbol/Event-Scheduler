#pragma once

#include<iostream>
#include<List>
#include<stack>
using namespace std;
class Event
{
	string name, place;
	int sday, smonth, syear, eday, emonth, eyear, hour, minute;
	long day, days;
	bool done;
	
public:
	Event(void);
	void add_event();
	bool intersection(Event e);
	void update_event();
	void delete_event();
	void display_events(int, int, int);
	long Remiander_Time(int,int ,int);
	void event_menu(int,int ,int);
	long check_end_date(int, int, int);
	void search_event(int, int, int);
	void delete_done_events(int, int, int);
	void tomorrow(int, int, int);
	void today(int, int, int);
	~Event();
};