#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <windows.h>
using namespace std;

struct PASSAPPA_airline
{
    string passport;
    string name;
    int seat_num;
    string email;
    PASSAPPA_airline *following;
};

PASSAPPA_airline *head = nullptr, *current = nullptr, *temp = nullptr;

void details(PASSAPPA_airline *current)
{
    cout << "\n\t Enter your passport number: ";
    cin >> current->passport;
    cin.ignore();

    cout << "\n\t Enter your name: ";
    getline(cin, current->name);

    cout << "\n\t Enter your email address: ";
    cin >> current->email;
}

void reserve(int x)
{
    if (x > 15) // FULL SEATS
    {
        cout << "\n\t\t Seat Full.";
        return;
    }

    current = head;
    if (head == nullptr)
    {
        // first user
        head = current = new PASSAPPA_airline;
        details(current);
        current->following = nullptr;
        current->seat_num = x;
        cout << "\n\t Seat booking successful!";
        cout << "\n\t Your seat number is: Seat A-" << x;
    }
    else
    {
        // next user
        while (current->following)
            current = current->following;

        current->following = new PASSAPPA_airline;
        current = current->following;
        details(current);
        current->following = nullptr;
        current->seat_num = x;
        cout << "\n\t Seat booking successful!";
        cout << "\n\t Your seat number is: Seat A-" << x;
    }
}

void savefile()
{
    ofstream file("PASSAPPA_records.txt");
    if (!file)
    {
        cout << "\n Error in opening file!";
        Sleep(800);
        return;
    }

    current = head;
    while (current)
    {
        file << current->passport << "\t";
        file << current->name << "\t";
        file << current->email << "\t";
        file << "A-" << current->seat_num << "\n";
        current = current->following;
    }

    cout << "\n\n\t Details have been saved to a file (PASSAPPA_records.txt)";
    file.close();
}

void display()
{
    if (head == nullptr)
    {
        cout << "\n\n No records to display.";
        return;
    }

    current = head;
    while (current)
    {
        cout << "\n\n Passport Number : " << current->passport;
        cout << "\n         Name : " << current->name;
        cout << "\n      Email Address: " << current->email;
        cout << "\n      Seat Number: A-" << current->seat_num;
        cout << "\n\n++*=====================================================*++";
        current = current->following;
    }
}

void cancel()
{
    if (head == nullptr)
    {
        cout << "\n\n No bookings to cancel.";
        return;
    }

    string passport;
    cout << "\n\n Enter passport number to delete record: ";
    cin >> passport;

    if (head->passport == passport)
    {
        temp = head;
        head = head->following;
        delete temp;
        cout << "\n Booking has been deleted.";
        Sleep(800);
        return;
    }

    current = head;
    while (current->following)
    {
        if (current->following->passport == passport)
        {
            temp = current->following;
            current->following = current->following->following;
            delete temp;
            cout << "\n Booking has been deleted.";
            Sleep(800);
            return;
        }
        current = current->following;
    }

    cout << "\n Passport number is wrong. Please check your passport.";
}

int main()
{
    int choice, num = 1;

    do
    {
        cout << "\n\n\t\t ********************************************************************";
        cout << "\n\t\t                   Welcome to PASSAPPA's Airline Reservation System                   ";
        cout << "\n\t\t ********************************************************************";
        cout << "\n\n\n\t\t Please enter your choice from below (1-4):";
        cout << "\n\n\t\t 1. Reservation";
        cout << "\n\n\t\t 2. Cancel";
        cout << "\n\n\t\t 3. Display Records";
        cout << "\n\n\t\t 4. Exit";
        cout << "\n\n\t\t Enter your choice: ";
        cin >> choice;
        cin.ignore();
        system("cls");

        switch (choice)
        {
        case 1:
            reserve(num);
            num++;
            break;
        case 2:
            cancel();
            break;
        case 3:
            display();
            break;
        case 4:
            savefile();
            break;
        default:
            cout << "\n\n\t SORRY INVALID CHOICE!";
            cout << "\n\n\t PLEASE CHOOSE FROM 1-4";
        }

        cout << "\n Press any key to continue...";
        cin.get();

    } while (choice != 4);

    return 0;
}
