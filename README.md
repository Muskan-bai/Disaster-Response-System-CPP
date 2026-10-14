# Disaster Response & Emergency Alert System

A console-based disaster response and emergency alert simulation developed in **C++** as my second-semester Object-Oriented Programming (OOP) project.

The system allows users to report disasters, receive location-based notifications, view emergency reports, and simulate emergency service alerts.

 Features

- User Registration & Login: Users can create accounts and log into the system.
- Disaster Reporting: Report earthquakes, floods, fires, storms, landslides, and other disasters.
- Severity Classification: Categorize emergencies as Low, Medium, High, or Critical.
- Location-Based Notifications: Notify registered users in the same city when a disaster is reported.
- Emergency Service Alerts: Simulate dispatching ambulances, fire brigades, and rescue teams.
- Disaster Search: Find disaster reports by city.
- Priority-Based Sorting: Sort reports according to disaster severity using Bubble Sort.
- Sentiment Analysis: Classify comments as Positive, Negative, or Neutral using keyword matching.
- Comments System: Allow users to add comments to disaster reports.
- File Handling: Export disaster reports to a text file.
- System Dashboard: Display total registered users, disaster reports, and the highest-severity disaster.



 Object-Oriented Programming Concepts

 Concept              Implementation 
 Classes &          User, Person, Location, DisasterReport, DisasterSystem
 Objects   

 Encapsulation      Private data members with public methods 
 
 Inheritance        User inherits from Person 
 
 Polymorphism       Virtual functions and overridden methods 
 
 Abstraction        Abstract EmergencyService class 
 
 Operator           `==`, `>`, and `<<` operators 
 Overloading  
 
 STL Vectors        Dynamic storage of users, reports, comments, and notifications 
 
 File Handling      Saving disaster reports using `ofstream` 

 


Technologies Used

- C++
- Object-Oriented Programming
- Standard Template Library (STL)
- File Handling
- Basic Searching and Sorting

 How to Run

1. Download or clone this repository.
2. Open the `.cpp` source file in Visual Studio, VS Code, Dev-C++, or another C++ IDE.
3. Compile using a C++ compiler.
4. Run the executable.
5. Register a user or log in to explore the available features.

 How the System Works

1. A user registers with their name, password, and location.
2. The user reports a disaster and selects its severity.
3. Registered users in the same city receive an in-program notification.
4. Users can view reports, add comments, and search by location.
5. Emergency service responses can be simulated.
6. Reports can be sorted by priority and saved to a text file.

 Project Purpose

This project was developed to apply Object-Oriented Programming concepts to a practical disaster reporting and emergency response simulation.

Note: This is an academic simulation. It does not connect to real emergency services or send real-time alerts.

 Academic Information

Course: Object-Oriented Programming (OOP)  
Semester: 2nd Semester  
Language: C++
