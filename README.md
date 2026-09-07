✈️ AeroSync Airport Management System

A C++ Flight Management System designed to demonstrate the practical application of Data Structures and Algorithms (DSA) in a real-world airport environment.

The system simulates airport operations including flight management, passenger check-in, terminal management, luggage processing, searching, and report generation.

🎯 Project Objective

The main objective of this project is to understand how data structures and algorithms can be applied to solve real-world problems.

The system demonstrates the use of:

* Arrays
* Linked Lists
* Queues
* Linear Search
* Binary Search
* Bubble Sort
* Dynamic Memory Allocation
* Object-Oriented Programming (OOP)

🛠️ Technologies

* Language: C++
* Programming Concepts: Data Structures, Algorithms, OOP
* Application Type: Console-based application

✨ Features

✈️ Flight Management

* Add new flights
* View flight schedules
* Update flight destinations
* Delete flights
* Assign flights to terminals
* Support for Domestic and International flights

🏢 Terminal Management

* Add terminals
* View terminal information
* Update terminal status
* Delete unused terminals
* Link terminals with flights
* Track passenger and luggage statistics

👤 Passenger Management

* Passenger check-in
* View passenger information
* Change passenger flights
* Delete passenger records
* Search passengers by name

🧳 Luggage Management

* Add luggage to the queue
* Process luggage using FIFO
* Categorize luggage as Standard or Oversized
* View the current luggage queue

🔎 Search Operations

* Linear Search for passengers
* Binary Search for flights

📊 Summary Report

* Display terminal statistics
* Sort terminals by:
    * Terminal number
    * Total passengers

🧠 Data Structures & Algorithms

Data Structure / Algorithm	Implementation	Purpose
Array	Terminal & Flight storage	Store multiple records
Linked List	Passenger records	Dynamic passenger management
Queue	Luggage processing	FIFO luggage processing
Bubble Sort	Terminal & flight sorting	Arrange records
Linear Search	Passenger search	Find passengers
Binary Search	Flight search	Efficient flight lookup
Dynamic Memory	Flight & luggage objects	Runtime memory allocation

🏗️ Object-Oriented Programming

The project also demonstrates several important OOP concepts.

Encapsulation

Terminal information is managed through the TerminalManager class, while access is controlled through member functions.

Inheritance

DomesticFlight and InternationalFlight inherit from the base Flight class.

class DomesticFlight : public Flight
class InternationalFlight : public Flight

Polymorphism

The displayFlightInfo() function is declared as virtual in the base Flight class and overridden by the child classes.

This allows the system to display different information depending on the flight type.

Dynamic Memory Allocation

Flight objects are dynamically created using new and safely released using delete.

👨‍💻 My Contribution

My main contribution to the project was the creation and management of terminal and flight codes.

This included:

* Developing terminal management functionality
* Creating terminal validation
* Managing terminal status
* Linking flights with terminals
* Preventing deletion of terminals currently assigned to flights
* Implementing flight creation and deletion
* Managing domestic and international flight types
* Implementing flight searching using binary search
* Implementing sorting for terminal summary reports

📋 Example System Flow

Airport
│
├── Terminals
│   ├── T-01 → AK502
│   ├── T-02 → SQ118
│   └── T-05 → Available
│
├── Flights
│   ├── Domestic
│   └── International
│
├── Passengers
│   └── Linked List
│
└── Luggage
    └── Queue (FIFO)

🚀 How to Run

1. Download or clone this repository.
2. Open the .cpp file in a C++ IDE or compiler.
3. Compile the program using a C++ compiler.
4. Run the executable.
5. Use the console menu to interact with the system.

Example using g++:

g++ main.cpp -o aerosync
./aerosync

📌 Sample Operations

The main menu provides:

=== MAIN MENU AEROSYNC ===
1. Flight Management
2. Passenger Management
3. Luggage Management
4. Search Operations
5. Terminal Management
6. Summary Report
7. Exit

📚 Learning Outcomes

Through this project, I gained practical experience in:

* Applying data structures to real-world problems
* Implementing searching and sorting algorithms
* Managing dynamic memory in C++
* Understanding pointers and linked lists
* Implementing FIFO queue operations
* Applying inheritance and polymorphism
* Designing modular C++ classes
* Managing relationships between different system components

👤 Author

Danish
Muaz
Aziz
Ridh
Fakhrul

C++ | Data Structures & Algorithms | Object-Oriented Programming
