#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

struct Ticket {
    string passengerName;
    int trainNumber;
    int seatNumber;
    string departure;
    string destination;
};

vector<Ticket> tickets;
int seatCounter = 1;


void saveTickets() {
    ofstream file("tickets.txt");
    if (!file) {
        cout << "Error opening file!\n";
        return;
    }
    for (const auto &t : tickets) {
        file << t.passengerName << "," << t.trainNumber << ","
             << t.seatNumber << "," << t.departure << "," << t.destination << "\n";
    }
    file.close();
}

void loadTickets() {
    ifstream file("tickets.txt");
    if (!file) {
        cout << "No previous bookings found.\n";
        return;
    }

    Ticket t;
    while (file >> t.passengerName >> t.trainNumber >> t.seatNumber >> t.departure >> t.destination) {
        tickets.push_back(t);
        seatCounter = t.seatNumber + 1;  
    }
    file.close();
}

void bookTicket() {
    Ticket t;
    cout << "Enter Passenger Name: ";
    cin.ignore();
    getline(cin, t.passengerName);
    cout << "Enter Train Number: ";
    cin >> t.trainNumber;
    cout << "Enter Departure Station: ";
    cin.ignore();
    getline(cin, t.departure);
    cout << "Enter Destination Station: ";
    getline(cin, t.destination);
    t.seatNumber = seatCounter++;

    tickets.push_back(t);
    saveTickets();
    cout << "Ticket booked successfully! Seat Number: " << t.seatNumber << endl;
}

void displayTickets() {
    if (tickets.empty()) {
        cout << "No tickets booked yet.\n";
        return;
    }

    cout << "\nBooked Tickets:\n";
    cout << setw(15) << left << "Passenger" << setw(10) << "Train No"
         << setw(10) << "Seat No" << setw(15) << "Departure"
         << setw(15) << "Destination" << endl;
    cout << string(65, '-') << endl;

    for (const auto &t : tickets) {
        cout << setw(15) << left << t.passengerName
             << setw(10) << t.trainNumber
             << setw(10) << t.seatNumber
             << setw(15) << t.departure
             << setw(15) << t.destination << endl;
    }
}


void cancelTicket() {
    int seatNo, found = 0;
    cout << "Enter Seat Number to Cancel: ";
    cin >> seatNo;

    for (auto it = tickets.begin(); it != tickets.end(); ++it) {
        if (it->seatNumber == seatNo) {
            tickets.erase(it);
            saveTickets();  // Save updated list after deletion
            cout << "Ticket with Seat Number " << seatNo << " cancelled successfully!\n";
            found = 1;
            break;
        }
    }

    if (!found)
        cout << "Ticket not found!\n";
}

int main() {
    loadTickets(); 

    int choice;
    while (true) {
        cout << "\n1. Book Ticket\n2. Display Tickets\n3. Cancel Ticket\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bookTicket(); break;
            case 2: displayTickets(); break;
            case 3: cancelTicket(); break;
            case 4: return 0;
            default: cout << "Invalid choice! Try again.\n";
        }
    }
}
