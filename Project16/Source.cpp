#include<iostream>
#include <conio.h>
#include"Windows.h"
#include<string>
#include"Planer.h"
using namespace std;

int main() {
    int SizeCategory = 0;
    string* AllCategories=nullptr;
    int SizeEvents = 0,numCategory;;
    Event* AllEvents = nullptr;
    string Category;
    int action=0,actionCat=0;
    do {
        CLEAR
        cout << "Enter action:\n1.Add new event\n2.Show events\n3.Add new category"
        "\n4.Show events by category\n5.Exit\n";
        cin >> action;
        CLEAR
        switch (action) {
        case 1: 
            if (SizeCategory >0) {
                do {
                    CLEAR
                    cout << "Enter action:\n1.Add new category\n2.Choose from already created\n";
                    cin >> actionCat;
                    if (actionCat != 1 && actionCat != 2) {
                        CLEAR
                            INVALID_VALUE
                    }
                } while (actionCat != 1 && actionCat != 2);
                if (actionCat == 1) {
                    CLEAR
                        cout << "Enter new category->_";
                    cin >> Category;
                    AddCategory(AllCategories, SizeCategory, Category);
                }
                else {
                    do {
                        CLEAR
                            ShowCategories(AllCategories, SizeCategory);
                        cout << "Enter number of category->_";
                        cin >> numCategory;
                        if (numCategory<1 || numCategory>SizeCategory) {
                            CLEAR
                                INVALID_VALUE
                        }
                    } while (numCategory<1 || numCategory>SizeCategory);
                    Category = AllCategories[numCategory - 1];
                }
            }
            else {
                CLEAR
                    cout << "Enter new category->_";
                cin >> Category;
                AddCategory(AllCategories, SizeCategory, Category);
            }
            CLEAR
            AddEvent(AllEvents, SizeEvents, FillEvent(),Category);
            CLEAR
                cout << "Event has been added.";
            SLEEP
            break;
        case 2:
            ShowEvents(AllEvents,SizeEvents);
            cout << "Enter space to continue.\n";
            while (_getch() != 32);
            break;
        case 3:
            cout << "Enter new category->_";
            cin >> Category;
            AddCategory(AllCategories, SizeCategory, Category);
            CLEAR
                cout << "Category has been added.";
            SLEEP
            break;
        case 4:
            ShowByCategories(AllEvents, SizeCategory, AllCategories, SizeCategory);
            cout << "Enter space to continue.\n";
            while (_getch() != 32);
            break;
        case 5:
            break;
        default:
            INVALID_VALUE;
        }
    } while (action!=5);
    delete []AllCategories;
    delete [] AllEvents;
    return 0;
}

