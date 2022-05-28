#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<stack>
#include<iterator>
#include"Event.h"
#include<ctime>

Event::Event()
{
    name = "NULL";
    place = "NULL";
    sday = smonth = syear = eday = emonth = eyear = hour = minute = day = 0;
    done = false;
}

void Event::event_menu(int month,int day,int year)
{
   delete_done_events(month, day, year);
menustart: 
    int choice;
    system("cls");
   today(month, day, year);
   tomorrow(month, day, year);

    cout << "\t\t\t\t ---------------------------------------------------------- \n";
    cout << "\t\t\t\t ------------------------Student Menu---------------------- \n";
    cout << "\t\t\t\t ---------------------------------------------------------- \n";
    cout << "\t\t\t\t 1. Add New Event \n";
    cout << "\t\t\t\t 2. Display Events \n";
    cout << "\t\t\t\t 3. Update Event \n";
    cout << "\t\t\t\t 4. Search Event \n";
    cout << "\t\t\t\t 5. Delete Event \n";
    cout << "\t\t\t\t 6. Tomorrow Events \n";
    cout << "\t\t\t\t 7. Exit \n";
    cout << "\t\t\t\t ---------------------------------------------------------- \n";
    cout << "\t\t\t\t ----------Choice Operation [1, 2 , 3 , 4 , 5 , 6 ,7]--------- \n";
    cout << "\t\t\t\t ---------------------------------------------------------- \n";
    cout << "Enter your Choice : ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        add_event();
        break;
    case 2:
        display_events(month, day, year);
        break;
    case 3:
        update_event();
        break;
    case 4:
        search_event(month, day, year);
        break;
    case 5:
        delete_event();
        break;
    case 6:
        tomorrow(month, day, year);
        break;
    case 7:
        cout << "We Hope You Found It Useful  " << endl;
        exit(0);
    default:
        cout << "Invaild Number Please try again...";
        break;
    }
    _getch();
    goto menustart;
}

void Event::add_event()
{
    system("cls");
    fstream file;
    list<Event>::iterator it;
    list<Event> l;
    Event* n = new Event();
    cout << "Enter Event Name : "<<endl;
    cin >> n->name;
    cout << "Enter Event Place : "<<endl;
    cin >> n->place;
    cout << "Enter Event Start Date : " << endl;
    cin >> n->sday >> n->smonth >> n->syear;
    cout << "Enter Event End Date : " << endl;
    cin >> n->eday >> n->emonth >> n->eyear;
    cout << "Enter Event Start Time : " << endl;
    cin >> n->hour >> n->minute;
    cout << "------------------------- " << endl;

    if (intersection(*n) == true)
    {
        file.open("event_data.txt", ios::app | ios::out);
        file << n->name << endl <<
            n->place << endl <<
            n->sday << " " << n->smonth << " " << n->syear << " " << endl <<
            n->eday << " " << n->emonth << " " << n->eyear << " " << endl <<
            n->hour << " " << n->minute << " " << endl;
            file.close();
    }
    else
    {
        cout << "Intersect With Another Event" << endl;
    }
}

bool Event::intersection(Event e)
{
    ifstream f("event_data.txt");
    Event* r = new Event();
    Event* ptr = &e;
    bool check = true;
    list<Event> reading_list;

    f >> r->name >> r->place;
    f >> r->sday >> r->smonth >> r->syear;
    f >> r->eday >> r->emonth >> r->eyear;
    f >> r->hour >> r->minute;
    
    while (!f.eof())
    {
    reading_list.push_back(*r);
        f >> r->name >> r->place;
        f >> r->sday >> r->smonth >> r->syear;
        f >> r->eday >> r->emonth >> r->eyear;
        f >> r->hour >> r->minute;
       
        
    }
        for (list<Event>::iterator it = reading_list.begin(); it != reading_list.end(); it++)
        {

            if (it->sday == e.sday && it->smonth == e.smonth && it->syear == e.syear)
            {

                if (it->hour == e.hour && it->minute == e.minute)
                    check = false;
            }

        }
        reading_list.clear();
        f.close();
        return check;
    
}

void Event::display_events(int month, int day, int year)
{
    fstream f("event_data.txt");
    list<pair<int, pair<int, int>>> sorted;
    list<Event> d;
    list<Event> d_new;
    Event Date;
    
        f >> Date.name;
        f >> Date.place;
        f >> Date.sday >> Date.smonth >> Date.syear;
        f >> Date.eday >> Date.emonth >> Date.eyear;
        f >> Date.hour >> Date.minute;
    while (!f.eof())
    {
        sorted.push_back(make_pair(Date.syear, make_pair(Date.smonth, Date.sday)));
        d.push_back(Date);
        f >> Date.name;
        f >> Date.place;
        f >> Date.sday >> Date.smonth >> Date.syear;
        f >> Date.eday >> Date.emonth >> Date.eyear;
        f >> Date.hour >> Date.minute;
    }

    sorted.sort();
    for (list<pair<int, pair<int, int>>>::iterator it = sorted.begin(); it != sorted.end(); it++)
    {
        for (list<Event>::iterator i = d.begin(); i != d.end(); i++)
        {
            if (i->sday == it->second.second && i->smonth == it->second.first && i->syear == it->first)
            {

                d_new.push_back(*i);
                break;
            }
        }
    }

    for (list<Event>::iterator it = d_new.begin(); it != d_new.end(); it++)
    {
        cout << "---------------------------------------------- \n";
        cout << "Event Name : " << it->name << endl;
        cout << "Event Place : " << it->place << endl;
        cout << "Event Start Date : " << it->sday << "/" << it->smonth << "/" << it->syear << endl;
        cout << "Event End Date : " << it->eday << "/" << it->emonth << "/" << it->eyear << endl;
        cout << "Event Time : " << it->hour << ":" << it->minute << endl;
        if (it->Remiander_Time(month,day,year) > 0)
        {
            cout << "Number of Days between Current Date And Event Start Date : ";
            cout << it->Remiander_Time(month,day,year) << endl;
        }
        else
        {
            cout << "There is No Remainder Time Because The Event is Already Started \n";
        }
        if (it->check_end_date(month, day, year) > 0)
        {
            cout << "No \n";
        }
        else
        {
            cout << "Yes \n";
        }
        
        
    }

}

void Event::delete_event()
{
    fstream f("event_data.txt");
    list<Event> d;
    list<Event> d_new;
    Event event;
    string name;
    int c = 0;
    cout << "\t\t\t\t\t\t -Delete Student Data- \n";
    if (!f)
    {
        cout << "No Data \n";
        f.close();
    }
    else
    {
        cout << "Enter name :" << endl;
        cin >> name;
        f >> event.name;
        f >> event.place;
        f >> event.sday >> event.smonth >> event.syear;
        f >> event.eday >> event.emonth >> event.eyear;
        f >> event.hour >> event.minute;
  
        while (!f.eof())
        {
            d.push_back(event);
            f >> event.name;
            f >> event.place;
            f >> event.sday >> event.smonth >> event.syear;
            f >> event.eday >> event.emonth >> event.eyear;
            f >> event.hour >> event.minute;
    
        }
        f.close();
        for (list<Event>::iterator it = d.begin(); it != d.end(); it++)
        {
            if (it->name == name)
               continue;
            d_new.push_back(*it);
            c++;
        }

        f.open("event_data.txt", ios::out | ios::trunc);
        for (list<Event>::iterator it = d_new.begin(); it != d_new.end(); it++)
        {
            f << it->name << endl <<
                it->place << endl <<
                it->sday << " " << it->smonth << " " << it->syear << " " << endl <<
                it->eday << " " << it->emonth << " " << it->eyear << " " << endl <<
                it->hour << " " << it->minute << " " << endl;
             
        }
        if (c == d.size())
        {
            cout << "Event Name Is Wrong \n";
        }
        else
        {
            cout << "Data Deleted Successfully \n";

        }

    }
}

void Event::update_event()
{
    fstream f("event_data.txt");
    list<Event> d;
    list<Event> d_new;
    Event event;
    string name;
    int c = 0;
    cout << "\t\t\t\t\t\t -Delete Student Data- \n";
    if (!f)
    {
        cout << "No Data \n";
        f.close();
    }
    else
    {
        cout << "Enter name :" << endl;
        cin >> name;
        f >> event.name;
        f >> event.place;
        f >> event.sday >> event.smonth >> event.syear;
        f >> event.eday >> event.emonth >> event.eyear;
        f >> event.hour >> event.minute;
      
        while (!f.eof())
        {
            d.push_back(event);
            f >> event.name;
            f >> event.place;
            f >> event.sday >> event.smonth >> event.syear;
            f >> event.eday >> event.emonth >> event.eyear;
            f >> event.hour >> event.minute;
           
        }
        f.close();
        for (list<Event>::iterator it = d.begin(); it != d.end(); it++)
        {
            if (it->name == name)
            {
                cout << "Enter Event Name : ";
                cin>> event.name;
                it->name = event.name;
                cout << "Enter Event Place Name : ";
                cin >> event.place;
                it->place = event.place;
                cout << "Enter Event Start Date : ";
                cin >> event.sday >> event.smonth >> event.syear;
                it->sday = event.sday; it->smonth = event.smonth; it->syear = event.syear;
                cout << "Enter Event End Date : ";
                cin >> event.eday >> event.emonth >> event.eyear;
                it->eday = event.eday; it->emonth = event.emonth; it->eyear = event.eyear;
                cout << "Enter Start Time To Event : ";
                cin >> event.hour >> event.minute;
                it->hour = event.hour; it->minute = event.minute;
                cout << "Enter Reminder Time To Event : ";
           
            
                c++;
            }
           
            d_new.push_back(*it);

        }

        f.open("event_data.txt", ios::out | ios::trunc);
        for (list<Event>::iterator it = d_new.begin(); it != d_new.end(); it++)
        {
            f << it->name << endl <<
                it->place << endl <<
                it->sday << " " << it->smonth << " " << it->syear << " " << endl <<
                it->eday << " " << it->emonth << " " << it->eyear << " " << endl <<
                it->hour << " " << it->minute << " " << endl;
               
        }
        if (c == 0)
        {
            cout << "Event Name Is Wrong \n";
        }
        else
        {
            cout << "Data Deleted Successfully \n";

        }

    }
}

void Event::search_event(int month, int day, int year) {
    system("cls");
    fstream file;
    int found = 0;
    file.open("event_data.txt", ios::in);
    if (!file)
    {
        cout << "No available data" << endl;

    }
    else 
    {
        string eventname;
        cout << "Enter Event's Name : ";
        cin >> eventname;
        cout <<"\n";
        file >> name >> place >> sday >> smonth >> syear >> eday >> emonth >> eyear >> hour >> minute;
        while (!file.eof()) {
            if (eventname == name) {
                cout << "---------------------------------------------- \n";
                cout << "Event Name : " << name << endl;
                cout << "Event Place : " << place << endl;
                cout << "Event Start Date : " << syear << "/" << smonth << "/" << sday << endl;
                cout << "Event End Date : " << eyear << "/" << emonth << "/" << eday << endl;
                cout << "Event Time : " << hour << ":" << minute << endl;
                
                if (Remiander_Time(month, day, year) > 0)
                {
                    cout << "Number of Days between Current Date And Event Start Date : ";
                    cout << Remiander_Time(month, day, year) << endl;
                }
                else
                {
                    cout << "There is No Remainder Time Because The Event is Already Started \n";
                }
                cout << "Done : ";
                if (check_end_date(month,day,year) > 0)
                {
                    cout << "No \n";
                }
                else
                {
                    cout << "Yes \n";
                }
                cout << "---------------------------------------------- \n";
                found++;
            }
            file >> name >> place >> sday >> smonth >> syear >> eday >> emonth >> eyear >> hour >> minute ;
        }
        if (found == 0) {
            cout << "Event Not Founded";
        }
        file.close();
    }
}

void Event::delete_done_events(int month, int day, int year)
{
    fstream f("event_data.txt");
    list<Event> d;
    list<Event> d_new;
    list<Event> out_of_date;
    Event event;

    if (!f)
    {
        f.close();
    }
    else
    {
        f >> event.name;
        f >> event.place;
        f >> event.sday >> event.smonth >> event.syear;
        f >> event.eday >> event.emonth >> event.eyear;
        f >> event.hour >> event.minute;
       
        while (!f.eof())
        {
            d.push_back(event);
            f >> event.name;
            f >> event.place;
            f >> event.sday >> event.smonth >> event.syear;
            f >> event.eday >> event.emonth >> event.eyear;
            f >> event.hour >> event.minute;
          
        }
        f.close();
        for (list<Event>::iterator it = d.begin(); it != d.end(); it++)
        {
            if (it->check_end_date(month, day, year) < 0)
            {
                out_of_date.push_back(*it);
                continue;
            }
            d_new.push_back(*it);
        }

        f.open("event_data.txt", ios::out | ios::trunc);
        for (list<Event>::iterator it = d_new.begin(); it != d_new.end(); it++)
        {
            f << it->name << endl <<
                it->place << endl <<
                it->sday << " " << it->smonth << " " << it->syear << " " << endl <<
                it->eday << " " << it->emonth << " " << it->eyear << " " << endl <<
                it->hour << " " << it->minute << " " << endl;
               
        }

    }
}

time_t dateToTimeT(int month, int day, int year) {
    tm tmp = tm();
    tmp.tm_mday = day;
    tmp.tm_mon = month - 1;
    tmp.tm_year = year - 1900;
    return mktime(&tmp);
}

time_t badTime() {
    return time_t(-1);
}

time_t now() {
    return time(0);
}

long Event::Remiander_Time(int month,int day,int year)
{
    time_t date1 = dateToTimeT(month, day, year);
    time_t date2 = dateToTimeT(smonth, sday, syear);
    if ((date1 == badTime()) || (date2 == badTime())) {
        cerr << "unable to create a time_t struct" << endl;
    }
    double sec = difftime(date2, date1);
    days = static_cast<long>(sec / (60 * 60 * 24));
    return days;
}

long Event::check_end_date(int month, int day, int year)
{
    time_t date1 = dateToTimeT(month, day, year);
    time_t date2 = dateToTimeT(emonth, eday, eyear);
    if ((date1 == badTime()) || (date2 == badTime())) {
        cerr << "unable to create a time_t struct" << endl;
    }
    double sec = difftime(date2, date1);
    day = static_cast<long>(sec / (60 * 60 * 24));
    return day;
}

void Event::tomorrow(int month, int day, int year)
{
    fstream f("event_data.txt");
    list<Event> d;
    list<Event> d_new;
    Event event;
    int c = 0;
    cout << "\t\t\t\t\t\t -Events Tomorrow- \n";
    if (!f)
    {
        f.close();
    }
    else
    {
        f >> event.name;
        f >> event.place;
        f >> event.sday >> event.smonth >> event.syear;
        f >> event.eday >> event.emonth >> event.eyear;
        f >> event.hour >> event.minute;

        while (!f.eof())
        {
            d.push_back(event);
            f >> event.name;
            f >> event.place;
            f >> event.sday >> event.smonth >> event.syear;
            f >> event.eday >> event.emonth >> event.eyear;
            f >> event.hour >> event.minute;

        }

        for (list<Event>::iterator it = d.begin(); it != d.end(); it++)
        {
            if (it->Remiander_Time(month, day, year) == 1)
            {
                cout << "---------------------------------------------- \n";
                cout << "Event Name : " << it->name << endl;
                cout << "Event Place : " << it->place << endl;
                cout << "Event Start Date : " << it->sday << "/" << it->smonth << "/" << it->syear << endl;
                cout << "Event End Date : " << it->eday << "/" << it->emonth << "/" << it->eyear << endl;
                cout << "Event Time : " << it->hour << ":" << it->minute << endl;

                c++;
            }

        }
        if (c == 0)
            cout << "No Events Tomorrow" << endl;
    }
    f.close();
}

void Event::today(int month, int day, int year)
{
    fstream f("event_data.txt");
    list<Event> d;
    list<Event> d_new;
    Event event;
    int c = 0;
    cout << "\t\t\t\t\t\t -Events today- \n";
    if (!f)
    {
        f.close();
    }
    else
    {
        f >> event.name;
        f >> event.place;
        f >> event.sday >> event.smonth >> event.syear;
        f >> event.eday >> event.emonth >> event.eyear;
        f >> event.hour >> event.minute;
    
        while (!f.eof())
        {
            d.push_back(event);
            f >> event.name;
            f >> event.place;
            f >> event.sday >> event.smonth >> event.syear;
            f >> event.eday >> event.emonth >> event.eyear;
            f >> event.hour >> event.minute;
         
        }

        for (list<Event>::iterator it = d.begin(); it != d.end(); it++)
        {
            if (it->Remiander_Time(month, day, year) == 0)
            {
                cout << "---------------------------------------------- \n";
                cout << "Event Name : " << it->name << endl;
                cout << "Event Place : " << it->place << endl;
                cout << "Event Start Date : " << it->sday << "/" << it->smonth << "/" << it->syear << endl;
                cout << "Event End Date : " << it->eday << "/" << it->emonth << "/" << it->eyear << endl;
                cout << "Event Time : " << it->hour << ":" << it->minute << endl;
                
                    c++;
            }

        }
        if (c == 0)
            cout << "No Events Today" << endl;
    }
    f.close();
}
Event::~Event()
{

}
