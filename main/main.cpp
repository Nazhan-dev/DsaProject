#include <iostream>
#include <string>
// AEROSYNC AIRPORT MANAGEMENT SYSTEM
using namespace std;

// ==========================================
// 1. STRUCT DATA AND CLASS
// ==========================================
struct Terminal
{
    string terminalNo;
    string assignedFlight;
    string status;
    int totalPassengers;
    int stdLuggage;
    int oversizeLuggage;
};

class TerminalManager
{
private:
    Terminal terminals[20];
    int count;

public:
    TerminalManager() { count = 0; }

    // --- GETTERS & SETTERS (The Bridge for Encapsulation) ---
    int getCount() { return count; }
    Terminal &getTerminal(int index) { return terminals[index]; }
    // --------------------------------------------------------

    // check if terminal exists
    bool terminalExists(string tNo)
    {
        for (int i = 0; i < count; i++)
        {
            if (terminals[i].terminalNo == tNo)
            {
                return true;
            }
        }
        return false;
    }

    void addTerminal(string tNo, string stat)
    {
        // CHECK DUPLICATE TERMINAL
        if (terminalExists(tNo))
        {
            cout << "[ERROR] Terminal already exists.\n";
            return;
        }

        // TERMINAL VALIDATION
        if (stat != "Active" && stat != "Closed" && stat != "Available")
        {
            cout << "[ERROR] Invalid terminal status.\n";
            cout << "Only Active, Closed, or Available are allowed.\n";
            return;
        }

        // CHECK STORAGE LIMIT
        if (count >= 20)
        {
            cout << "[ERROR] Terminal storage full.\n";
            return;
        }

        terminals[count] = {tNo, "None", stat, 0, 0, 0};
        count++;

        cout << "[SUCCESS] Terminal added.\n";
    }

    void viewTerminals()
    {
        cout << "\n--- Terminal list ---\n";
        for (int i = 0; i < count; i++)
        {
            cout << terminals[i].terminalNo << " | Flight: " << terminals[i].assignedFlight << " | Status: " << terminals[i].status << "\n";
        }
    }

    void updateTerminalStatus(string tNo, string newStatus)
    {
        // CHECK VALIDATION
        if (newStatus != "Active" && newStatus != "Closed" && newStatus != "Available")
        {
            cout << "[ERROR] Invalid terminal status.\n";
            return;
        }

        for (int i = 0; i < count; i++)
        {
            if (terminals[i].terminalNo == tNo)
            {
                terminals[i].status = newStatus;
                cout << "[SUCCESS] Status " << tNo << " updated to " << newStatus << ".\n";
                return;
            }
        }
        cout << "[ERROR] Terminal not found\n";
    }

    void deleteTerminal(string tNo)
    {
        for (int i = 0; i < count; i++)
        {
            if (terminals[i].terminalNo == tNo)
            {
                // PREVENT DELETE IF TERMINAL HAS FLIGHT
                if (terminals[i].assignedFlight != "None")
                {
                    cout << "[ERROR] Terminal in use.\n";
                    return;
                }

                for (int j = i; j < count - 1; j++)
                    terminals[j] = terminals[j + 1];

                count--;

                cout << "[SUCCESS] Terminal deleted.\n";
                return;
            }
        }
        cout << "[ERROR] Terminal not found\n";
    }

    // add pre-set terminal data
    void addPresetTerminal(string tNo, string fNo, string stat, int tp, int sl, int ol)
    {
        if (count < 20)
        {
            terminals[count] = {tNo, fNo, stat, tp, sl, ol};
            count++;
        }
    }

    // Bubble sort for report summary
    void sortSummary(int sortBy)
    {
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - i - 1; j++)
            {
                // DRY (Don't Repeat Yourself). Using a single condition variable to determine sorting criteria based on user choice.
                bool condition = (sortBy == 1) ? (terminals[j].terminalNo > terminals[j + 1].terminalNo)
                                               : (terminals[j].totalPassengers < terminals[j + 1].totalPassengers);
                if (condition)
                {
                    Terminal temp = terminals[j];
                    terminals[j] = terminals[j + 1];
                    terminals[j + 1] = temp;
                }
            }
        }
    }

    void displaySummary()
    {
        cout << "\n=================================================================================\n";
        cout << "Terminal No.\tAssigned Flight\tStatus\t\tTotal Pass\tStd Lug\tOversized\n";
        cout << "=================================================================================\n";
        for (int i = 0; i < count; i++)
        {
            cout << terminals[i].terminalNo << "\t\t" << terminals[i].assignedFlight << "\t\t"
                 << terminals[i].status << "\t\t" << terminals[i].totalPassengers << "\t\t"
                 << terminals[i].stdLuggage << "\t" << terminals[i].oversizeLuggage << "\n";
        }
    }
};

// ==========================================
// 2. CLASS FLIGHT (INHERITANCE & POLYMORPHISM)
// ==========================================
class Flight
{
protected:
    string flightNo;
    string dest;
    string terminalNo;
    string flightType; // Custom type label

public:
    Flight(string fNo, string d, string tNo, string type = "Generic")
    {
        flightNo = fNo;
        dest = d;
        terminalNo = tNo;
        flightType = type;
    }

    virtual ~Flight() {} // Virtual destructor is critical for clean inheritance tracking

    // Getters
    string getFlightNo() { return flightNo; }
    string getDest() { return dest; }
    string getTerminalNo() { return terminalNo; }
    string getFlightType() { return flightType; }

    // Setter
    void setDest(string newDest) { dest = newDest; }

    // Polymorphic Virtual function
    virtual void displayFlightInfo()
    {
        cout << flightNo << " -> " << dest << " (Terminal: " << terminalNo << ") [" << flightType << "]\n";
    }
};

// Child Class 1 (Inheritance)
class DomesticFlight : public Flight
{
public:
    DomesticFlight(string fNo, string d, string tNo) : Flight(fNo, d, tNo, "Domestic") {}

    // Overriding Polymorphic Function
    void displayFlightInfo() override
    {
        cout << "[DOMESTIC] " << flightNo << " to " << dest << " | Assigned Terminal: " << terminalNo << "\n";
    }
};

// Child Class 2 (Inheritance)
class InternationalFlight : public Flight
{
public:
    InternationalFlight(string fNo, string d, string tNo) : Flight(fNo, d, tNo, "International") {}

    // Overriding Polymorphic Function
    void displayFlightInfo() override
    {
        cout << "[INT'L]    " << flightNo << " to " << dest << " | Passport Check Required | Terminal: " << terminalNo << "\n";
    }
};

class FlightManager
{
private:
    Flight* flights[50]; // Dynamic polymorphism tracking using Base pointers
    int count;

public:
    FlightManager() { count = 0; }

    // Destructor to safely clean pointer array allocations
    ~FlightManager()
    {
        for (int i = 0; i < count; i++)
        {
            delete flights[i];
        }
    }

    // --- GETTERS & SETTERS ---
    int getCount() { return count; }
    Flight* getFlight(int index) { return flights[index]; }
    // -------------------------

    bool flightExists(string fNo)
    {
        for (int i = 0; i < count; i++)
        {
            if (flights[i]->getFlightNo() == fNo)
            {
                return true;
            }
        }
        return false;
    }

    void addFlight(string fNo, string dest, string tNo, int typeChoice, TerminalManager &tm)
    {
        if (flightExists(fNo))
        {
            cout << "[ERROR] Flight already exists.\n";
            return;
        }

        if (count >= 50)
        {
            cout << "[ERROR] Flight storage full.\n";
            return;
        }

        // Terminal availability check
        bool tExists = false;
        for (int i = 0; i < tm.getCount(); i++)
        {
            if (tm.getTerminal(i).terminalNo == tNo)
            {
                tm.getTerminal(i).assignedFlight = fNo;
                tm.getTerminal(i).status = "Active"; 
                tExists = true;
                break;
            }
        }
        if (!tExists)
        {
            cout << "[ERROR] Terminal does not exist.\n";
            return;
        }

        // Object generation assigned based on child identity selection
        if (typeChoice == 1)
        {
            flights[count] = new DomesticFlight(fNo, dest, tNo);
        }
        else
        {
            flights[count] = new InternationalFlight(fNo, dest, tNo);
        }
        
        count++;
        cout << "[SUCCESS] Flight added and linked to " << tNo << ".\n";
    }

    void viewFlights()
    {
        cout << "\n--- FLIGHT SCHEDULE ---\n";
        for (int i = 0; i < count; i++)
        {
            // Polymorphic functional bind resolution at execution runtime
            flights[i]->displayFlightInfo();
        }
    }

    void updateFlightDest(string fNo, string newDest)
    {
        for (int i = 0; i < count; i++)
        {
            if (flights[i]->getFlightNo() == fNo)
            {
                flights[i]->setDest(newDest);
                cout << "[SUCCESS] Destination updated.\n";
                return;
            }
        }
        cout << "[ERROR] No flight was found.\n";
    }

    void deleteFlight(string fNo, TerminalManager &tm)
    {
        for (int i = 0; i < count; i++)
        {
            if (flights[i]->getFlightNo() == fNo)
            {
                for (int t = 0; t < tm.getCount(); t++)
                {
                    if (tm.getTerminal(t).assignedFlight == fNo)
                    {
                        tm.getTerminal(t).assignedFlight = "None";
                        tm.getTerminal(t).status = "Available";
                    }
                }
                
                delete flights[i]; // Clear data allocation

                for (int j = i; j < count - 1; j++)
                    flights[j] = flights[j + 1];
                    
                count--;
                cout << "[SUCCESS] Flight deleted.\n";
                return;
            }
        }
    }

    void addPresetFlight(int identity, string fNo, string dest, string tNo)
    {
        if (count < 50)
        {
            if (identity == 1)
                flights[count] = new DomesticFlight(fNo, dest, tNo);
            else
                flights[count] = new InternationalFlight(fNo, dest, tNo);
            count++;
        }
    }

    void binarySearchFlight(string fNo)
    {
        // Bubble Sort Array items sequentially for proper index target detection
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - i - 1; j++)
            {
                if (flights[j]->getFlightNo() > flights[j + 1]->getFlightNo())
                {
                    Flight* temp = flights[j];
                    flights[j] = flights[j + 1];
                    flights[j + 1] = temp;
                }
            }
        }

        int left = 0, right = count - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (flights[mid]->getFlightNo() == fNo)
            {
                cout << "\n[Found Check Summary Match] ";
                flights[mid]->displayFlightInfo();
                return;
            }
            if (flights[mid]->getFlightNo() < fNo)
                left = mid + 1;
            else
                right = mid - 1;
        }
        cout << "\n[ERROR] No flight was found.\n";
    }
};

// ==========================================
// 3. CLASS LUGGAGE (STRICT QUEUE)
// ==========================================
struct LuggageNode
{
    string owner;      
    float weight;      
    string type;       
    LuggageNode *next; 
};

class LuggageQueue
{
private:
    LuggageNode *front, *rear;

public:
    LuggageQueue() { front = rear = NULL; } 

    ~LuggageQueue()
    {
        while (front) 
        {
            LuggageNode *temp = front;
            front = front->next;
            delete temp;
        }
    }

    void enqueue(string owner, float w) 
    {
        LuggageNode *nn = new LuggageNode{owner, w, (w > 20.0) ? "Oversized" : "Standard", NULL}; 

        if (rear == NULL)
        {
            front = rear = nn; 
            cout << "Luggage added to conveyor belt.\n";
            return;
        }
        else
        {
            rear->next = nn; 
            rear = nn;       
            cout << "[Queue] Luggage added to conveyor belt.\n";
        }
    }

    void processLuggage()
    {
        if (front == NULL) 
        {
            cout << "No luggage.\n";
            return;
        }

        LuggageNode *temp = front; 
        front = front->next;       

        if (front == NULL)
        {
            rear = NULL; 
        }

        cout << "[Process] Loading luggage: " << temp->owner << " (" << temp->type << ")\n";
        delete temp;
    }

    void viewQueue()
    {
        cout << "\n--- BAGGAGE QUEUE ---\n";
        LuggageNode *temp = front; 

        if (temp == NULL)
        { 
            cout << "Empty queue.\n";
        }

        while (temp != NULL) 
        {
            cout << "owner: " << temp->owner << " | weight: " << temp->weight << "kg\n";
            temp = temp->next;
        }
    }
};

// ==========================================
// 4. CLASS PASSENGERS (LINKED LIST)
// ==========================================
struct PassNode
{
    string name, ticketNo, flightNo;
    float lugWeight;
    PassNode *next;
};

class PassengerManager
{
public:
    PassNode *head;
    PassengerManager() { head = NULL; }

    ~PassengerManager()
    {
        while (head)
        {
            PassNode *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addPassenger(string n, string t, string f, float w, FlightManager &fm, TerminalManager &tm, LuggageQueue &lq)
    {
        string targetTerminal = "";
        for (int i = 0; i < fm.getCount(); i++)
        {
            if (fm.getFlight(i)->getFlightNo() == f)
            {
                targetTerminal = fm.getFlight(i)->getTerminalNo();
                break;
            }
        }
        if (targetTerminal == "")
        {
            cout << "[ERROR] flight does not exist.\n";
            return;
        }

        for (int i = 0; i < tm.getCount(); i++)
        {
            if (tm.getTerminal(i).terminalNo == targetTerminal)
            {
                if (tm.getTerminal(i).status != "Active")
                {
                    cout << "[ERROR] Terminal closed.\n";
                    return;
                }

                PassNode *nn = new PassNode{n, t, f, w, head};
                head = nn;
                lq.enqueue(n, w);

                tm.getTerminal(i).totalPassengers++;
                if (w > 20.0)
                    tm.getTerminal(i).oversizeLuggage++;
                else
                    tm.getTerminal(i).stdLuggage++;

                cout << "[SUCCESS] Passenger " << n << " checked in.\n";
                return;
            }
        }
    }

    void viewPassengers()
    {
        PassNode *temp = head;
        cout << "\n--- PASSENGER LIST ---\n";
        while (temp)
        {
            cout << temp->name << " | Flight: " << temp->flightNo << " | Luggage: " << temp->lugWeight << "kg\n";
            temp = temp->next;
        }
    }

    void updatePassengerFlight(string n, string newF, FlightManager &fm)
    {
        bool flightExist = false;
        for (int i = 0; i < fm.getCount(); i++)
        {
            if (fm.getFlight(i)->getFlightNo() == newF)
            {
                flightExist = true;
                break;
            }
        }

        if (!flightExist)
        {
            cout << "[ERROR] flight does not exist.\n";
            return;
        }

        PassNode *temp = head;
        while (temp)
        {
            if (temp->name == n)
            {
                temp->flightNo = newF;
                cout << "[SUCCESS] Ticket exchanged.\n";
                return;
            }
            temp = temp->next;
        }

        cout << "[ERROR] Passenger not Found.\n";
    }

    void deletePassenger(string n)
    {
        PassNode *temp = head, *prev = NULL;
        while (temp && temp->name != n)
        {
            prev = temp;
            temp = temp->next;
        }
        if (!temp)
        {
            cout << "Not Found.\n";
            return;
        }
        if (!prev)
            head = temp->next;
        else
            prev->next = temp->next;
        delete temp;
        cout << "[SUCCESS] deleted.\n";
    }

    void linearSearchPassenger(string n)
    {
        PassNode *temp = head;
        while (temp)
        {
            if (temp->name == n)
            {
                cout << "\n[Found] " << temp->name << " | Flight: " << temp->flightNo << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "\n[ERROR] Passenger Not Found.\n";
    }
};

// ==========================================
// 5. MAIN FUNCTIONS & MENUS
// ==========================================
int main()
{
    TerminalManager tm;
    FlightManager fm;
    PassengerManager pm;
    LuggageQueue lq;

    // PRE-SET DATA
    tm.addPresetTerminal("T-01", "AK502", "Active", 120, 170, 15);
    tm.addPresetTerminal("T-04", "MH201", "Active", 85, 102, 8);
    tm.addPresetTerminal("T-02", "SQ118", "Active", 45, 58, 2);
    tm.addPresetTerminal("T-03", "TR442", "Closed", 0, 0, 0);
    tm.addPresetTerminal("T-05", "None", "Available", 0, 0, 0);

    // 1 = Domestic, 2 = International
    fm.addPresetFlight(1, "AK502", "KUL", "T-01");
    fm.addPresetFlight(1, "MH201", "BKI", "T-04");
    fm.addPresetFlight(2, "SQ118", "SIN", "T-02");
    fm.addPresetFlight(2, "TR442", "JHB", "T-03");

    int mainChoice, subChoice;
    do
    {
        cout << "\n=== MAIN MENU AEROSYNC ===\n";
        cout << "1. Flight Management\n2. Passenger Management\n3. Luggage Management\n";
        cout << "4. Search Operations\n5. Terminal Management\n6. Summary Report\n7. Exit\nChoice: ";
        cin >> mainChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "INVALID INPUT. Please enter choices\n";
            continue;
        }

        if (mainChoice < 1 || mainChoice > 7)
        {
            cout << "INVALID CHOICE. Please choose between 1 and 7.\n";
            continue;
        }

        switch (mainChoice)
        {
        case 1: // Flight
            do
            {
                cout << "\n-- Flight Management --\n1. Add Flight\n2. View Flights\n3. Update Flight\n4. Delete Flight\n5. Back\nChoice: ";
                cin >> subChoice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "INVALID INPUT. Please enter choices\n";
                    continue;
                }

                if (subChoice < 1 || subChoice > 5)
                {
                    cout << "INVALID CHOICE. Please choose between 1 and 5.\n";
                    continue;
                }

                if (subChoice == 1)
                {
                    string f, d, t;
                    int typeChoice;
                    cout << "Flight No: ";
                    cin >> f;
                    cout << "Destination: ";
                    cin >> d;
                    cout << "Link to Terminal: ";
                    cin >> t;
                    cout << "Flight Type (1. Domestic, 2. International): ";
                    cin >> typeChoice;
                    
                    if(typeChoice != 1 && typeChoice != 2) {
                        cout << "[ERROR] Invalid Type selection. Reverting to Domestic.\n";
                        typeChoice = 1;
                    }
                    
                    fm.addFlight(f, d, t, typeChoice, tm);
                }
                else if (subChoice == 2)
                    fm.viewFlights();
                else if (subChoice == 3)
                {
                    string f, d;
                    cout << "Flight No: ";
                    cin >> f;
                    cout << "New Destination: ";
                    cin >> d;
                    fm.updateFlightDest(f, d);
                }
                else if (subChoice == 4)
                {
                    string f;
                    cout << "Flight No. to be deleted: ";
                    cin >> f;
                    fm.deleteFlight(f, tm);
                }
            } while (subChoice != 5);
            break;

        case 2: // Passenger
            do
            {
                cout << "\n-- Passenger Management --\n1. Check In\n2. View Passengers\n3. Update Passenger\n4. Delete Passenger\n5. Back\nChoice: ";
                cin >> subChoice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "INVALID INPUT. Please enter choices\n";
                    continue;
                }

                if (subChoice < 1 || subChoice > 5)
                {
                    cout << "INVALID CHOICE. Please choose between 1 and 5.\n";
                    continue;
                }

                if (subChoice == 1)
                {
                    string n, t, f;
                    float w;
                    cout << "Name: ";
                    cin >> ws;
                    getline(cin, n);
                    cout << "Ticket No: ";
                    cin >> t;
                    cout << "Flight No: ";
                    cin >> f;
                    cout << "Luggage weight: ";
                    cin >> w;
                    pm.addPassenger(n, t, f, w, fm, tm, lq);
                }
                else if (subChoice == 2)
                    pm.viewPassengers();
                else if (subChoice == 3)
                {
                    string n, f;
                    cout << "Name: ";
                    cin >> ws;
                    getline(cin, n);
                    cout << "New flight: ";
                    cin >> f;
                    pm.updatePassengerFlight(n, f, fm);
                }
                else if (subChoice == 4)
                {
                    string n;
                    cout << "Name for deleted: ";
                    cin >> ws;
                    getline(cin, n);
                    pm.deletePassenger(n);
                }
            } while (subChoice != 5);
            break;

        case 3: // Luggage
            do
            {
                cout << "\n-- Luggage Management --\n1. Add Luggage (Manual)\n2. Process Luggage\n3. View Queue\n4. Back\nChoice: ";
                cin >> subChoice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "INVALID INPUT. Please enter choices\n";
                    continue;
                }

                if (subChoice < 1 || subChoice > 4)
                {
                    cout << "INVALID CHOICE. Please choose between 1 and 4.\n";
                    continue;
                }

                if (subChoice == 1)
                {
                    string n;
                    float w;
                    cout << "Owner Name: ";
                    cin >> ws;
                    getline(cin, n);
                    cout << "Weight: ";
                    cin >> w;
                    lq.enqueue(n, w);
                }
                else if (subChoice == 2)
                    lq.processLuggage();
                else if (subChoice == 3)
                    lq.viewQueue();
            } while (subChoice != 4);
            break;

        case 4: // Search
            do
            {
                cout << "\n-- Search Operations --\n1. Search Passenger (Linear)\n2. Search Flight (Binary)\n3. Back\nChoice: ";
                cin >> subChoice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "INVALID INPUT. Please enter choices\n";
                    continue;
                }

                if (subChoice < 1 || subChoice > 3)
                {
                    cout << "INVALID CHOICE. Please choose between 1 and 3.\n";
                    continue;
                }

                if (subChoice == 1)
                {
                    string n;
                    cout << "Find Name: ";
                    cin >> ws;
                    getline(cin, n);
                    pm.linearSearchPassenger(n);
                }
                else if (subChoice == 2)
                {
                    string f;
                    cout << "Find Flight No: ";
                    cin >> f;
                    fm.binarySearchFlight(f);
                }
            } while (subChoice != 3);
            break;

        case 5: // Terminal
            do
            {
                cout << "\n-- Terminal Management --\n1. Add Terminal\n2. View Terminal\n3. Update Terminal Status\n4. Delete Terminal\n5. Back\nChoice: ";
                cin >> subChoice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "INVALID INPUT. Please enter choices\n";
                    continue;
                }

                if (subChoice < 1 || subChoice > 5)
                {
                    cout << "INVALID CHOICE. Please choose between 1 and 5.\n";
                    continue;
                }

                if (subChoice == 1)
                {
                    string t, s;
                    cout << "No Terminal: ";
                    cin >> t;
                    cout << "Status (Active/Closed/Available): ";
                    cin >> s;
                    tm.addTerminal(t, s);
                }
                else if (subChoice == 2)
                    tm.viewTerminals();
                else if (subChoice == 3)
                {
                    string t, s;
                    cout << "No Terminal: ";
                    cin >> t;
                    cout << "New Status: ";
                    cin >> s;
                    tm.updateTerminalStatus(t, s);
                }
                else if (subChoice == 4)
                {
                    string t;
                    cout << "Terminal deleted: ";
                    cin >> t;
                    tm.deleteTerminal(t);
                }
            } while (subChoice != 5);
            break;

        case 6: // Summary
            int s;
            cout << "Sort by:\n1. Terminal No. (Default)\n2. Total Passengers\nChoice: ";
            cin >> s;
            tm.sortSummary(s);
            tm.displaySummary();
            break;
        }
    } while (mainChoice != 7);

    cout << "\nThank you for using AeroSync System. byee byee...\n";
    return 0;
}
