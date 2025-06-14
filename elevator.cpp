#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib> 
#include <ctime> 

using namespace std;

mutex mtx;

void simulateElevator(int &currentFloor, int targetFloor, int elevatorID);

int main() {
    srand(time(0)); 
    int elevator1CurrentFloor = rand() % 9 + 1;
    int elevator2CurrentFloor = rand() % 9 + 1;
    int selectedElevator, elevatorFloor;
    char userChoice;

    cout << "=======================================" << endl;
    cout << "          ELEVATOR SIMULATION          " << endl;
    cout << "=======================================" << endl;

    do {
        cout << "Elevator 1 Current Floor: " << elevator1CurrentFloor << endl;
        cout << "Elevator 2 Current Floor: " << elevator2CurrentFloor << endl;

        cout << "Choose Elevator (1 or 2): ";
        while (!(cin >> selectedElevator) || (selectedElevator != 1 && selectedElevator != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please select Elevator 1 or 2: ";
        }

        int &currentFloor = (selectedElevator == 1) ? elevator1CurrentFloor : elevator2CurrentFloor;

        cout << "Current Floor of Elevator " << selectedElevator << ": " << currentFloor << endl;
        cout << "Choose Floor (1-9): ";
        while (!(cin >> elevatorFloor) || elevatorFloor < 1 || elevatorFloor > 9) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please select a floor between 1 and 9: ";
        }

        if (elevatorFloor == currentFloor) {
            cout << "You are already on Floor " << currentFloor 
                 << " using Elevator " << selectedElevator << ". Please choose a different floor." << endl;
        } else {
            thread t(simulateElevator, ref(currentFloor), elevatorFloor, selectedElevator);
            t.join();
        }

        cout << "You have reached Floor Level #" << currentFloor 
             << " using Elevator " << selectedElevator << ". Do you want to use the elevator again? (Y/N): ";
        cin >> userChoice;
    } while (userChoice == 'Y' || userChoice == 'y');

    cout << "Exiting Program. Goodbye!" << endl;
    return 0;
}

void simulateElevator(int &currentFloor, int targetFloor, int elevatorID) {
    if (currentFloor < targetFloor) {
        for (int floorLevel = currentFloor; floorLevel <= targetFloor; ++floorLevel) {
            mtx.lock();
            cout << "Elevator " << elevatorID << " - Floor Level: " << floorLevel 
                 << " - Thread ID: " << this_thread::get_id() << endl;
            currentFloor = floorLevel;
            mtx.unlock();
            this_thread::sleep_for(chrono::seconds(2));
        }
    } else {
        for (int floorLevel = currentFloor; floorLevel >= targetFloor; --floorLevel) {
            mtx.lock();
            cout << "Elevator " << elevatorID << " - Floor Level: " << floorLevel 
                 << " - Thread ID: " << this_thread::get_id() << endl;
            currentFloor = floorLevel;
            mtx.unlock();
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
}
