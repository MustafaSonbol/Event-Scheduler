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
   Alarm(month, day, year);

    cout << "\t\t\t\t ---------------------------------------------------------- \n";
    cout << "\t\t\t\t ------------------------Student Menu---------------------- \n";
    cout << "\t\t\t\t ---------------------------------------------------------- \n";
    cout << "\t\t\t\t 1. Add New Event \n";
    cout << "\t\t\t\t 2. Display Events \n";
    cout << "\t\t\t\t 3. Update Event \n";
    cout << "\t\t\t\t 4. Search Event \n";
    cout << "\t\t\t\t 5. Delete Event \n";
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

    Event n;;
    cout << "Enter Event Name : "<<endl;
    cin >> n.name;
    cout << "Enter Event Place : "<<endl;
    cin >> n.place;
    cout << "Enter Event Start Date : " << endl;
    cin >> n.sday >> n.smonth >> n.syear;
    cout << "Enter Event End Date : " << endl;
    cin >> n.eday >> n.emonth >> n.eyear;
    cout << "Enter Event Start Time : " << endl;
    cin >> n.hour >> n.minute;
    cout << "------------------------- " << endl;

    if (intersection(n) == true)
    {
       fstream file("event_data.txt", ios::app | ios::out);
        file << n.name << endl <<
            n.place << endl <<
            n.sday << " " << n.smonth << " " << n.syear << " " << endl <<
            n.eday << " " << n.emonth << " " << n.eyear << " " << endl <<
            n.hour << " " << n.minute << " " << endl;
            file.close();
            cout << "Event Added Successfully \n";
    }
    else
    {
        cout << "Intersect With Another Event" << endl;
    }
}

bool Event::intersection(Event e)
{
    fstream f("event_data.txt");
    Event r;
    bool check = true;
    list<Event> reading_list;

    f >> r.name >> r.place;
    f >> r.sday >> r.smonth >> r.syear;
    f >> r.eday >> r.emonth >> r.eyear;
    f >> r.hour >> r.minute;
    
    while (!f.eof())
    {
        reading_list.push_back(r);
        f >> r.name >> r.place;
        f >> r.sday >> r.smonth >> r.syear;
        f >> r.eday >> r.emonth >> r.eyear;
        f >> r.hour >> r.minute;  
    }

        for (list<Event>::iterator it = reading_list.begin(); it != reading_list.end(); it++)
        {

            if (it->sday == e.sday && it->smonth == e.smonth && it->syear == e.syear)
            {
                    check = false;
            }

        }
        reading_list.clear();
        f.close();
        return check;
    
}

void Event::display_events(int month, int day, int year)
{
    system("cls");
    fstream f("event_data.txt");
    list<pair<int, pair<int, int>>> sorted;
    list<Event> reading_list;
    list<Event> d_new;
    Event r;
    
        f >> r.name;
        f >> r.place;
        f >> r.sday >> r.smonth >> r.syear;
        f >> r.eday >> r.emonth >> r.eyear;
        f >> r.hour >> r.minute;
    while (!f.eof())
    {
        sorted.push_back(make_pair(r.syear, make_pair(r.smonth, r.sday)));
        reading_list.push_back(r);
        f >> r.name;
        f >> r.place;
        f >> r.sday >> r.smonth >> r.syear;
        f >> r.eday >> r.emonth >> r.eyear;
        f >> r.hour >> r.minute;
    }

    sorted.sort();
    for (list<pair<int, pair<int, int>>>::iterator it = sorted.begin(); it != sorted.end(); it++)
    {
        for (list<Event>::iterator i = reading_list.begin(); i != reading_list.end(); i++)
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
        if (it->Reminder_Time(month,day,year) > 0)
        {
            cout << "Number of Days between Current Date And Event Start Date : ";
            cout << it->Reminder_Time(month,day,year) << endl;
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
    system("cls");
    fstream f("event_data.txt");
    list<Event> reading_list;
    list<Event> d_new;
    Event r;
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
        f >> r.name;
        f >> r.place;
        f >> r.sday >> r.smonth >> r.syear;
        f >> r.eday >> r.emonth >> r.eyear;
        f >> r.hour >> r.minute;
  
        while (!f.eof())
        {
            reading_list.push_back(r);
            f >> r.name;
            f >> r.place;
            f >> r.sday >> r.smonth >> r.syear;
            f >> r.eday >> r.emonth >> r.eyear;
            f >> r.hour >> r.minute;
    
        }
        f.close();
        for (list<Event>::iterator it = reading_list.begin(); it != reading_list.end(); it++)
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
        if (c == reading_list.size())
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
    system("cls");
    fstream f("event_data.txt");
    list<Event> reading_list;
    list<Event> d_new;
    Event r;
    string name;
    int c = 0;
    cout << "\t\t\t\t\t\t -Update Student Data- \n";
    if (!f)
    {
        cout << "No Data \n";
        f.close();
    }
    else
    {
        cout << "Enter name :" << endl;
        cin >> name;
        f >> r.name;
        f >> r.place;
        f >> r.sday >> r.smonth >> r.syear;
        f >> r.eday >> r.emonth >> r.eyear;
        f >> r.hour >> r.minute;
      
        while (!f.eof())
        {
            reading_list.push_back(r);
            f >> r.name;
            f >> r.place;
            f >> r.sday >> r.smonth >> r.syear;
            f >> r.eday >> r.emonth >> r.eyear;
            f >> r.hour >> r.minute;
           
        }
        f.close();
        for (list<Event>::iterator it = reading_list.begin(); it != reading_list.end(); it++)
        {
            if (it->name == name)
            {
                cout << "Enter Event Name : ";
                cin >> it->name;
                cout << "Enter Event Place Name : ";
                cin >> it->place;
                cout << "Enter Event Start Date : ";
                cin >> it->sday >> it->smonth >> it->syear;
                cout << "Enter Event End Date : ";
                cin >> it->eday >> it->emonth >> it->eyear;
                cout << "Enter Start Time To Event : ";
                cin >> it->hour >> it->minute;
                c++;
            }
           
            d_new.push_back(*it);

        }

        f.open("event_data.txt", ios::out | ios::trunc);
        for (list<Event>::iterator it = d_new.begin(); it != d_new.end(); it++)
        {
            f <<it->name << endl <<
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
            cout << "Data Updated Successfully \n";

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
                
                if (Reminder_Time(month, day, year) > 0)
                {
                    cout << "Number of Days between Current Date And Event Start Date : ";
                    cout << Reminder_Time(month, day, year) << endl;
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
    list<Event> reading_list;
    list<Event> d_new;
    list<Event> Done_Event;
    Event r;

    if (!f)
    {
        f.close();
    }
    else
    {
        f >> r.name;
        f >> r.place;
        f >> r.sday >> r.smonth >> r.syear;
        f >> r.eday >> r.emonth >> r.eyear;
        f >> r.hour >> r.minute;
       
        while (!f.eof())
        {
            reading_list.push_back(r);
            f >> r.name;
            f >> r.place;
            f >> r.sday >> r.smonth >> r.syear;
            f >> r.eday >> r.emonth >> r.eyear;
            f >> r.hour >> r.minute;
          
        }
        f.close();
        for (list<Event>::iterator it = reading_list.begin(); it != reading_list.end(); it++)
        {
            if (it->check_end_date(month, day, year) < 0)
            {
                Done_Event.push_back(*it);
                continue;
            }
            d_new.push_back(*it);
        }

        f.open("event_data.txt", ios::out | ios::trunc);
        for (list<Event>::iterator it = d_new.begin(); it != d_new.end(); it++)
        {
            f <<it->name << endl <<
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

long Event::Reminder_Time(int month,int day,int year)
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

void Event::Alarm(int month, int day, int year)
{
    fstream f("event_data.txt");
    list<Event> reading_list;
    list<Event> d_new;
    Event r;
   
    if (!f)
    {
        f.close();
    }
    else
    {
        f >> r.name;
        f >> r.place;
        f >> r.sday >> r.smonth >> r.syear;
        f >> r.eday >> r.emonth >> r.eyear;
        f >> r.hour >> r.minute;

        while (!f.eof())
        {
            reading_list.push_back(r);
            f >> r.name;
            f >> r.place;
            f >> r.sday >> r.smonth >> r.syear;
            f >> r.eday >> r.emonth >> r.eyear;
            f >> r.hour >> r.minute;

        }
         f.close();
        for (list<Event>::iterator it = reading_list.begin(); it != reading_list.end(); it++)
        {
            if (it->Reminder_Time(month, day, year) == 0)
            {
                cout << "---------------------------------------------- \n";
                cout << " there is an Event ToDay"<< endl;
                cout << "Event Name : " << it->name << endl;
                cout << "Event Place : " << it->place << endl;
                cout << "Event Start Date : " << it->sday << "/" << it->smonth << "/" << it->syear << endl;
                cout << "Event End Date : " << it->eday << "/" << it->emonth << "/" << it->eyear << endl;
                cout << "Event Time : " << it->hour << ":" << it->minute << endl;
                cout << "---------------------------------------------- \n";
            }
            if (it->Reminder_Time(month, day, year) == 1)
            {
                cout << "---------------------------------------------- \n";
                cout << " there is an Event Tomorrow " << endl;
                cout << "Event Name : " << it->name << endl;
                cout << "Event Place : " << it->place << endl;
                cout << "Event Start Date : " << it->sday << "/" << it->smonth << "/" << it->syear << endl;
                cout << "Event End Date : " << it->eday << "/" << it->emonth << "/" << it->eyear << endl;
                cout << "Event Time : " << it->hour << ":" << it->minute << endl;
                cout << "---------------------------------------------- \n";
            }

        }
      
    }
   
}


