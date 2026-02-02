#include <iostream>
#include <string>
using namespace std;

class Vehicle {
private:
    int vehicleID;
    string manufacturer;
    string model;
    int year;

public:
    static int totalVehicles;

    Vehicle() {
        vehicleID = 0;
        year = 0;
        totalVehicles++;
    }

    Vehicle(int id, string mfg, string mdl, int yr) {
        vehicleID = id;
        manufacturer = mfg;
        model = mdl;
        year = yr;
        totalVehicles++;
    }

    virtual ~Vehicle() {
        totalVehicles--;
    }

    void setID(int id) { vehicleID = id; }
    int getID() { return vehicleID; }

    void setManufacturer(string mfg) { manufacturer = mfg; }
    string getManufacturer() { return manufacturer; }

    void setModel(string mdl) { model = mdl; }
    string getModel() { return model; }

    void setYear(int yr) { year = yr; }
    int getYear() { return year; }

    virtual void display() {
        cout << "ID: " << vehicleID << " | " << manufacturer << " " << model << " (" << year << ")";
    }
};

int Vehicle::totalVehicles = 0;

class Car : public Vehicle {
private:
    string fuelType;
public:
    Car() : Vehicle() {}
    Car(int id, string mfg, string mdl, int yr, string fuel) : Vehicle(id, mfg, mdl, yr) {
        fuelType = fuel;
    }
    void setFuel(string f) { fuelType = f; }
    string getFuel() { return fuelType; }
    
    void display() override {
        Vehicle::display();
        cout << " | Fuel: " << fuelType;
    }
};

class ElectricCar : public Car {
private:
    int batteryCapacity;
public:
    ElectricCar() : Car() {}
    ElectricCar(int id, string mfg, string mdl, int yr, string fuel, int cap) 
        : Car(id, mfg, mdl, yr, fuel) {
        batteryCapacity = cap;
    }
    void setCap(int c) { batteryCapacity = c; }
    int getCap() { return batteryCapacity; }

    void display() override {
        Car::display();
        cout << " | Battery: " << batteryCapacity << "kWh";
    }
};

class Aircraft {
private:
    int flightRange;
public:
    Aircraft(int range) : flightRange(range) {}
    void setRange(int r) { flightRange = r; }
    int getRange() { return flightRange; }
};

class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar(int id, string mfg, string mdl, int yr, string fuel, int range) 
        : Car(id, mfg, mdl, yr, fuel), Aircraft(range) {}
    
    void display() override {
        Car::display();
        cout << " | Range: " << getRange() << "km [Flying Mode Active]";
    }
};

class SportsCar : public ElectricCar {
private:
    int topSpeed;
public:
    SportsCar(int id, string mfg, string mdl, int yr, string fuel, int cap, int speed)
        : ElectricCar(id, mfg, mdl, yr, fuel, cap) {
        topSpeed = speed;
    }
    void display() override {
        ElectricCar::display();
        cout << " | Top Speed: " << topSpeed << "km/h";
    }
};

class Sedan : public Car {
public:
    Sedan(int id, string mfg, string mdl, int yr, string fuel) : Car(id, mfg, mdl, yr, fuel) {}
};

class SUV : public Car {
public:
    SUV(int id, string mfg, string mdl, int yr, string fuel) : Car(id, mfg, mdl, yr, fuel) {}
};

class VehicleRegistry {
private:
    Vehicle* registry[100];
    int count;
public:
    VehicleRegistry() : count(0) {}

    void addVehicle(Vehicle* v) {
        if (count < 100) {
            registry[count++] = v;
        }
    }

    void viewAll() {
        for (int i = 0; i < count; i++) {
            registry[i]->display();
            cout << endl;
        }
        cout << "Total Vehicles in System: " << Vehicle::totalVehicles << endl;
    }

    void searchById(int id) {
        for (int i = 0; i < count; i++) {
            if (registry[i]->getID() == id) {
                registry[i]->display();
                cout << endl;
                return;
            }
        }
        cout << "Vehicle not found." << endl;
    }
};

int main() {
    VehicleRegistry vr;
    int choice, id, yr, cap, range, speed;
    string mfg, mdl, fuel;

    while (true) {
        cout << "\n1. Add Car\n2. Add Electric Car\n3. Add Flying Car\n4. View All\n5. Search ID\n6. Exit\nChoice: ";
        cin >> choice;

        if (choice == 6) break;

        if (choice >= 1 && choice <= 3) {
            cout << "Enter ID, Mfg, Model, Year: ";
            cin >> id >> mfg >> mdl >> yr;
            if (choice == 1) {
                cout << "Fuel Type: "; cin >> fuel;
                vr.addVehicle(new Car(id, mfg, mdl, yr, fuel));
            } else if (choice == 2) {
                cout << "Battery Capacity: "; cin >> cap;
                vr.addVehicle(new ElectricCar(id, mfg, mdl, yr, "Electric", cap));
            } else if (choice == 3) {
                cout << "Fuel and Flight Range: "; cin >> fuel >> range;
                vr.addVehicle(new FlyingCar(id, mfg, mdl, yr, fuel, range));
            }
        } else if (choice == 4) {
            vr.viewAll();
        } else if (choice == 5) {
            cout << "Enter Search ID: "; cin >> id;
            vr.searchById(id);
        }
    }
}