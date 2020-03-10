#include "Planer.h"
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

#define COLOR(num)\
if (num == 1) SetConsoleTextAttribute(handle, FOREGROUND_GREEN); \
else if (num == 2) SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN); \
else if (num == 3)SetConsoleTextAttribute(handle, FOREGROUND_RED); \
else SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

int DaysInMonths[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

void ShowCategories(string*AllCategories, int size) {
    for (int i = 0; i < size; i++)
        cout << i + 1 << " " << AllCategories[i] << endl;
    cout << endl;
}
Date FillDate() {
    Date NewDate;
    do {
        CLEAR
            cout << "Enter year->_";
        cin >> NewDate.year;
        if (NewDate.year < 0) {
            CLEAR
                INVALID_VALUE
        }
    } while (NewDate.year < 0);
    do {
        CLEAR
            cout << "Enter month->_";
        cin >> NewDate.month;
        if (NewDate.month < 1 || NewDate.month>12) {
            CLEAR
                INVALID_VALUE
        }
    } while (NewDate.month < 1 || NewDate.month>12);
    if (NewDate.year % 4 == 0 && NewDate.year % 100 == 0 && NewDate.year % 400 == 0 && NewDate.month == 2)
        ++DaysInMonths[2];
    do {
        CLEAR
            cout << "Enter day->_";
        cin >> NewDate.day;
        if (NewDate.day<1 || NewDate.day>DaysInMonths[NewDate.month]) {
            CLEAR
                INVALID_VALUE
        }
    } while (NewDate.day<1 || NewDate.day>DaysInMonths[NewDate.month]);
    DaysInMonths[2] = 28;
    return NewDate;
}
Time FillTime(){
    Time NewTime;
    do {
        CLEAR
            cout << "Enter hour(0-23)->_";
        cin >> NewTime.hour;
        if (NewTime.hour < 0 || NewTime.hour>23) {
            CLEAR
            INVALID_VALUE
        }
    } while (NewTime.hour < 0 || NewTime.hour>23);
    do {
        CLEAR
        cout << "Enter minute(0-59)->_";
        cin >> NewTime.minute;
        if (NewTime.minute < 0 || NewTime.minute>59) {
            CLEAR
           INVALID_VALUE
        }
    } while (NewTime.minute < 0 || NewTime.minute>59);
    return NewTime;
}
Event FillEvent() {
    Event NewEvent;
    Date NewDate;
    Time NewTime;
    CLEAR
        cin.ignore(131313, '\n');
    cout << "Enter header for event->_";
    getline(cin, NewEvent.Header);

    CLEAR
    cout << "Enter descriptions for event->";
    getline(cin, NewEvent.Descriptions);

    NewDate = FillDate();
    NewEvent.date.day = NewDate.day;
    NewEvent.date.month = NewDate.month;
    NewEvent.date.year = NewDate.year;
    CLEAR
    NewTime = FillTime();
    NewEvent.time.hour = NewTime.hour;
    NewEvent.time.minute = NewTime.minute;
    CLEAR
        do {
            CLEAR
                cout << "Enter severity(1-3)->_";
            cin >> NewEvent.Severity;
            if (NewEvent.Severity < 1 || NewEvent.Severity>3) {
                CLEAR
                    INVALID_VALUE
            }
        } while (NewEvent.Severity < 1 || NewEvent.Severity>3);

        CLEAR
        return NewEvent;
}

void AddCategory(string*& AllCategories, int& size, string NewCategory) {
    string* res = new string[++size];
    for (int i = 0; i < size - 1; i++)
        res[i] = AllCategories[i];

    res[size-1] = NewCategory;
    delete[]AllCategories;
    AllCategories = res;
}
void AddEvent(Event*&AllEvents, int& size,Event NewEvent,string Category ) {
    Event* res = new Event[++size];
    
    for (int i = 0; i < size - 1; i++) {
        res[i].Header = AllEvents[i].Header;
        res[i].Descriptions = AllEvents[i].Descriptions;
        res[i].date.day = AllEvents[i].date.day;
        res[i].date.month = AllEvents[i].date.month;    
        res[i].date.year = AllEvents[i].date.year;
        res[i].time.hour = AllEvents[i].time.hour;
        res[i].time.minute = AllEvents[i].time.minute;
        res[i].Severity = AllEvents[i].Severity;
        res[i].Category = AllEvents[i].Category;
    }
    res[size - 1].Header = NewEvent.Header;
    res[size - 1].Descriptions = NewEvent.Descriptions;
    res[size - 1].date.day = NewEvent.date.day;
    res[size - 1].date.month = NewEvent.date.month;
    res[size - 1].date.year = NewEvent.date.year;
    res[size - 1].time.hour = NewEvent.time.hour;
    res[size - 1].time.minute = NewEvent.time.minute;
    res[size - 1].Severity = NewEvent.Severity;
    res[size - 1].Category = Category;
    delete[]AllEvents;
    AllEvents = res;
}
void SortForDate(Event* AllEvents, int size) {
    int imin = 0;
    for (int i = 0; i < size - 1; i++) {
        imin = i;
        for (int j = i + 1; j < size; j++)
            if (AllEvents[j].time.minute < AllEvents[imin].time.minute)
                imin = j;
        if (imin > i) {
            swap(AllEvents[i].Header, AllEvents[imin].Header);
            swap(AllEvents[i].Descriptions, AllEvents[imin].Descriptions);
            swap(AllEvents[i].date.day, AllEvents[imin].date.day);
            swap(AllEvents[i].date.month, AllEvents[imin].date.month);
            swap(AllEvents[i].date.year, AllEvents[imin].date.year);
            swap(AllEvents[i].time.hour, AllEvents[imin].time.hour);
            swap(AllEvents[i].time.minute, AllEvents[imin].time.minute);
            swap(AllEvents[i].Severity, AllEvents[imin].Severity);
            swap(AllEvents[i].Category, AllEvents[imin].Category);
        }
    }
    for (int i = 0; i < size - 1; i++) {
        imin = i;
        for (int j = i + 1; j < size; j++)
            if (AllEvents[j].time.hour < AllEvents[imin].time.hour)
                imin = j;
        if (imin > i) {
            swap(AllEvents[i].Header, AllEvents[imin].Header);
            swap(AllEvents[i].Descriptions, AllEvents[imin].Descriptions);
            swap(AllEvents[i].date.day, AllEvents[imin].date.day);
            swap(AllEvents[i].date.month, AllEvents[imin].date.month);
            swap(AllEvents[i].date.year, AllEvents[imin].date.year);
            swap(AllEvents[i].time.hour, AllEvents[imin].time.hour);
            swap(AllEvents[i].time.minute, AllEvents[imin].time.minute);
            swap(AllEvents[i].Severity, AllEvents[imin].Severity);
            swap(AllEvents[i].Category, AllEvents[imin].Category);
        }
    }
    for (int i = 0; i < size - 1; i++) {
        imin = i;
        for (int j = i + 1; j < size; j++)
            if (AllEvents[j].date.day < AllEvents[imin].date.day)
                imin = j;
        if (imin > i) {
            swap(AllEvents[i].Header, AllEvents[imin].Header);
            swap(AllEvents[i].Descriptions, AllEvents[imin].Descriptions);
            swap(AllEvents[i].date.day, AllEvents[imin].date.day);
            swap(AllEvents[i].date.month, AllEvents[imin].date.month);
            swap(AllEvents[i].date.year, AllEvents[imin].date.year);
            swap(AllEvents[i].time.hour, AllEvents[imin].time.hour);
            swap(AllEvents[i].time.minute, AllEvents[imin].time.minute);
            swap(AllEvents[i].Severity, AllEvents[imin].Severity);
            swap(AllEvents[i].Category, AllEvents[imin].Category);
        }
    }
    for (int i = 0; i < size - 1; i++) {
        imin = i;
        for (int j = i + 1; j < size; j++)
            if (AllEvents[j].date.month < AllEvents[imin].date.month)
                imin = j;
        if (imin > i) {
            swap(AllEvents[i].Header, AllEvents[imin].Header);
            swap(AllEvents[i].Descriptions, AllEvents[imin].Descriptions);
            swap(AllEvents[i].date.day, AllEvents[imin].date.day);
            swap(AllEvents[i].date.month, AllEvents[imin].date.month);
            swap(AllEvents[i].date.year, AllEvents[imin].date.year);
            swap(AllEvents[i].time.hour, AllEvents[imin].time.hour);
            swap(AllEvents[i].time.minute, AllEvents[imin].time.minute);
            swap(AllEvents[i].Severity, AllEvents[imin].Severity);
            swap(AllEvents[i].Category, AllEvents[imin].Category);
        }
    }
    for (int i = 0; i < size - 1; i++) {
        imin = i;
        for (int j = i + 1; j < size; j++)
            if (AllEvents[j].date.year < AllEvents[imin].date.year)
                imin = j;
        if (imin > i) {
            swap(AllEvents[i].Header, AllEvents[imin].Header);
            swap(AllEvents[i].Descriptions, AllEvents[imin].Descriptions);
            swap(AllEvents[i].date.day, AllEvents[imin].date.day);
            swap(AllEvents[i].date.month, AllEvents[imin].date.month);
            swap(AllEvents[i].date.year, AllEvents[imin].date.year);
            swap(AllEvents[i].time.hour, AllEvents[imin].time.hour);
            swap(AllEvents[i].time.minute, AllEvents[imin].time.minute);
            swap(AllEvents[i].Severity, AllEvents[imin].Severity);
            swap(AllEvents[i].Category, AllEvents[imin].Category);
        }
    }
}

void ShowEvent(Event& Event) {
    COLOR(Event.Severity);
    cout <<Event.Category<<endl<< Event.Header << endl << Event.date.day
        << " " << Event.date.month << " " << Event.date.year << endl;
    Event.time.hour < 10 ? cout << 0 << Event.time.hour  : cout << Event.time.hour;
    cout << ":";
    Event.time.minute < 10 ? cout << 0 << Event.time.minute : cout << Event.time.minute;
    cout<<endl<< Event.Descriptions << "\n\n";
   COLOR(4)
}

void ShowEvents(Event* AllEvents, int size) {
    if (size > 0) {
        SortForDate(AllEvents, size);
        for (int i = 0; i < size; i++) {
            cout << i + 1 << ". ";
            ShowEvent(AllEvents[i]);
            Sleep(500);
        }
    }
    else {
        cout << "No events.\n";
        SLEEP
    }
}
void ShowByCategories(Event* AllEvents, int size,string*AllCategories,int sizeCategories) {
    if (size > 0) {
        int numCategory = 0;
        do {
            CLEAR
                ShowCategories(AllCategories, sizeCategories);
            cout << "Enter number of category->_";
            cin >> numCategory;
            if (numCategory<1 || numCategory>size) {
                CLEAR
                    INVALID_VALUE
            }
        } while (numCategory<1 || numCategory>size);
        CLEAR
            SortForDate(AllEvents, size);
        for (int i = 0; i < size; i++) {
            if (AllEvents[i].Category.find(AllCategories[numCategory - 1]) != string::npos) {
                ShowEvent(AllEvents[i]);
                Sleep(500);

            }
        }
    }
    else {
        cout << "No events.\n";
        SLEEP
    }
   
}
