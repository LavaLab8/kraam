/*
 * main.cpp
 *
 *  Created on: Oct 25, 2014
 *      Author: student
 */


#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>
#include "mongo/client/dbclient.h"
using namespace std;

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open(argv[1]);
	if(!infile)
	{
		cout<< "wrong file name " <<endl;
		return 0;
	}


	string buffer="";
	string CourseNumber;

	string CourseTitle;
	string RegistrationRestrictions;
	string unitString;
	double UnitCount;
	string Type;
	string Section;
	string sessionString;
	int Session;
	string Time;
	string startTime;
	string endTime;




	string Days;
	string seatsString;
	int Seats;
	string registeredString;
	int Registered;
	string waitlistString;
	int Waitlist;
	string Instructor;
	string Room;

	string str;
	//remove firstline
	getline(infile,str,'\n');

	while(getline(infile, str, '\n'))
	{
		stringstream ss;
		ss<<str;
		getline(ss, buffer, '\"');
		getline(ss, CourseNumber, '\"');
		getline(ss,buffer,',');

		getline(ss, buffer, '\"');
		getline(ss, CourseTitle, '\"');
		getline(ss,buffer,',');

		getline(ss, buffer, '\"');
		getline(ss, RegistrationRestrictions, '\"');
		getline(ss, buffer, ',');


		getline(ss, buffer, '\"');
		getline(ss, unitString, '\"');
		getline(ss, buffer, ',');

		stringstream stringstr_unit(unitString);
		stringstr_unit>> UnitCount;
		stringstr_unit.clear();
		stringstr_unit.ignore(10000);

		getline(ss, buffer, '\"');
		getline(ss, Type, '\"');
		getline(ss, buffer, ',');

		getline(ss, buffer, '\"');
		getline(ss, Section, '\"');
		getline(ss, buffer, ',');

		getline(ss, buffer, '\"');
		getline(ss, sessionString, '\"');
		getline(ss, buffer, ',');
		stringstream stringstr_session (sessionString);
		stringstr_session>> Session;
		stringstr_session.clear();
		stringstr_session.ignore(10000);

		getline(ss, buffer, '\"');
		getline(ss, Time, '\"');
		getline(ss, buffer, ',');

		stringstream stringstr_time(Time);
		getline(stringstr_time, startTime, '-');
		getline(stringstr_time, endTime,'\n');

		string am_or_pm= endTime.substr(endTime.length()-2);
		if(am_or_pm =="am")
		{
			startTime=startTime+"am";
		}
		if(am_or_pm=="pm")
		{
			string hourOfStartTime;
			stringstream stringstr_startTime(startTime);
			getline(stringstr_startTime, hourOfStartTime, ':');
			int hourOfStartTimeInteger= atoi(hourOfStartTime.c_str());
			//this is if the end time is pm, but the start time is am
			//this is saying if there is a pm end time, most likely if the start time's hour is 
			//9, 10, or 11, it will be an am class that goes past noon 
			if(hourOfStartTimeInteger ==9 || hourOfStartTimeInteger ==10 || hourOfStartTimeInteger ==11)
			{
				startTime=startTime+"am";
			}
			else
			{
				startTime=startTime+"pm";
			}
		}







		//have to reach ," to reach end of Days string, because the string itself can have commas (mon,wed)
		getline(ss, buffer, '\"');
		getline(ss, Days, '\"');
		getline(ss, buffer, ',');


		vector<string> days;
		stringstream stringstr_days(Days);
		string d;
		while( stringstr_days >>d)
		{
			//if the class meets (mon, wed), then mon will have a comma after it and wed will not
			if(d=="Mon" || d=="Mon,")
			{
				d= "Monday";
			}
			if(d=="Tue" || d=="Tue,")
			{
				d= "Tuesday";
			}
			if(d=="Wed" || d=="Wed,")
			{
				d= "Wednesday";
			}
			if(d=="Thu" || d=="Thu,")
			{
				d= "Thursday";
			}
			if(d=="Fri" || d=="Fri,")
			{
				d= "Friday";
			}
			days.push_back(d);
		}

		//add the last day that does not end in a comma
		//days.push_back(d);

		/*for(int ii=0; ii<days.size(); ii++)
		{
			cout<< days[ii]<<endl;
		}*/







		//the Seats will be missing the initial quotation mark because the Days string had to get buffered until the ,".
		//so buffer seats until ", and then you will just get the int number of seats, and can continue normally since all
		//of the quotation marks will now be correctly paired
		getline(ss, buffer, '\"');
		getline(ss, seatsString, '\"');
		getline(ss, buffer, ',');

		stringstream stringstr_seats(seatsString);
		stringstr_seats >> Seats;
		stringstr_seats.clear();
		stringstr_seats.ignore(10000);


		getline(ss, buffer, '\"');
		getline(ss, registeredString, '\"');
		getline(ss, buffer, ',');
		stringstream stringstr_registered(registeredString);
		stringstr_registered >> Registered;
		stringstr_registered.clear();
		stringstr_registered.ignore(10000);

		getline(ss, buffer, '\"');
		getline(ss, waitlistString, '\"');
		getline(ss, buffer, ',');
		stringstream stringstr_waitlist(waitlistString);
		stringstr_waitlist>> Waitlist;
		stringstr_waitlist.clear();
		stringstr_waitlist.ignore(10000);

		getline(ss, buffer, '\"');
		getline(ss, Instructor, '\"');
		getline(ss, buffer, ',');

		getline(ss, buffer, '\"');
		getline(ss, Room, '\"');
		getline(ss, buffer, '\n');

		
		cout<<"COURSE NUMBER: " <<CourseNumber <<endl;
		cout<<"COURSE TITLE: "<<CourseTitle<<endl;
		cout<<"REGISTRATION RESTRICTIONS: "<<RegistrationRestrictions <<endl;
		cout<<"UNIT COUNT:"<<UnitCount<<endl;
		cout<<"TYPE: "<<Type<<endl;
		cout<<"SECTION: "<<Section<<endl;
		cout<<"SESSION: "<<Session<<endl;
		

		//cout<<"TIME: "<<Time<<endl;

		cout<<"START TIME:"<< startTime<<":"<<endl;
		cout<<"END TIME:"<< endTime<<":"<<endl;
		for(int ii=0; ii<days.size(); ii++)
		{
			cout<< "DAYS: "<<days[ii]<<endl;
		}
		cout<<"SEATS: " <<Seats<<endl;
		cout<<"REGISTERED: "<<Registered<<endl;
		cout<<"WAITLIST: "<<Waitlist<<endl;
		cout<<"INSTRUCTOR: "<<Instructor<<endl;
		cout<<"ROOM: "<<Room<<endl;





	}


}

