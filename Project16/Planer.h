#pragma once
#include<iostream>
#include <conio.h>
#include"Windows.h"
#include<string>
using namespace std;


#define CLEAR system("cls");
#define INVALID_VALUE cout<<"Invalid value."; Sleep(1500);
#define SLEEP Sleep(1500);
struct Time {
	int hour;
	int minute;
};
struct Date {
	int day;
	int month;
	int year;
};
struct  Event {
	string Header;
	string Descriptions;
	Date date;
	Time time;
	int Severity;
	string Category;
};


void AddCategory(string*& AllCategories, int& size, string NewCategory);
void ShowCategories(string* AllCategories, int size);
Date FillDate();
Time FillTime();
Event FillEvent();
void AddEvent(Event*&AllEvents, int& size,Event NewEvent,string Category);
void SortForDate(Event* AllEvents, int size);
void ShowEvent(Event& Event);
void ShowEvents(Event* AllEvents, int size);
void ShowByCategories(Event* AllEvents, int size, string* AllCategories, int sizeCategories);
