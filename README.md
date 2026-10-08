# Care-Pulse

## Hospital Management System

Care-Pulse is a **Hospital Management System developed in C++**. It is designed to manage the main activities of a hospital in an organized way.

The system uses **Data Structures and Algorithms (DSA)** and **Object-Oriented Programming (OOP)** to manage:

* Patients
* Doctors
* Appointments
* OPD waiting queues
* Emergency cases
* Admissions
* Wards, rooms, and beds
* Billing
* Patient discharge
* Hospital records

The project follows the complete patient journey, starting from registration and consultation and ending with billing and discharge.

---

## Project Overview

A hospital has many activities that need to be managed properly. Care-Pulse brings these activities together into one system.

The system uses different data structures according to the requirement:

* **Linked List** – Used for managing dynamic records.
* **Queue** – Used for normal OPD patients.
* **Priority Queue** – Used for emergency patients based on their severity.
* **Stack** – Used to maintain recent operations or history.
* **Binary Search Tree (BST)** – Used to search patient records.
* **Hash Table** – Used for quick doctor information lookup.

### Patient Workflow

```text
Patient Registration
        ↓
   OPD / Emergency
        ↓
 Doctor Consultation
        ↓
  Admission Required?
      ↙       ↘
    No         Yes
    ↓           ↓
Treatment   Ward / Room / Bed
    ↓           ↓
    └────── Treatment
             ↓
          Billing
             ↓
         Discharge
             ↓
      Record Storage
```

---

## Objectives

Care-Pulse aims to:

* Manage major hospital activities in one system.
* Store patient and doctor information properly.
* Manage OPD patients using **FIFO (First-In-First-Out)**.
* Give higher priority to serious emergency cases.
* Search patient records efficiently.
* Find doctor information quickly.
* Manage wards, rooms, and beds.
* Track doctor availability and assignments.
* Manage appointments and consultations.
* Generate patient bills.
* Process patient discharge.
* Save important records for future use.
* Demonstrate the use of DSA and OOP concepts.

---

# Core Features

## 1. Patient Management

The Patient Management module stores and manages patient information.

It can contain:

* Patient ID
* Patient name
* Age
* Contact information
* Medical and admission information
* Assigned doctor
* Admission status
* Current hospital status

Patient records can also be searched using the implemented search structure.

---

## 2. OPD Management

The OPD module manages patients waiting for a normal consultation.

Patients are added to a **Queue** and are treated according to the order in which they arrive.

Example:

```text
Patient A → Patient B → Patient C → Patient D

Service Order:

A → B → C → D
```

This follows the **FIFO principle**, meaning the patient who enters first is served first.

---

## 3. Emergency Management

Emergency patients need to be handled according to the seriousness of their condition.

Care-Pulse uses a **Priority Queue** for emergency cases.

Example:

```text
Critical   → Highest Priority
Severe     → High Priority
Moderate   → Medium Priority
Stable     → Lower Priority
```

Therefore, a more serious emergency case can be handled before a less serious case, even if it arrived later.

---

## 4. Doctor Management

The Doctor Management module stores information about doctors.

It manages:

* Doctor ID
* Doctor name
* Department or specialization
* Availability
* Assigned patients
* Consultation information

A **Hash Table** is used to provide quick access to doctor information.

---

## 5. Doctor Assignment

After OPD or emergency processing, the patient can be assigned to a suitable available doctor.

The system checks doctor availability before assigning a patient.

### Basic Flow

```text
Patient
   ↓
OPD / Emergency
   ↓
Check Doctor Availability
   ↓
Doctor Assignment
   ↓
Consultation
```

---

## 6. Appointment Management

The Appointment module manages appointment information for patients and doctors.

It connects:

* Patient
* Doctor
* Appointment details

This helps keep consultation schedules organized.

---

## 7. Ward, Room and Bed Management

Patients who need admission are assigned hospital resources.

The hospital structure is:

```text
Ward
  ↓
Room
  ↓
Bed
```

The system keeps track of:

* Available beds
* Occupied beds
* Patient bed allocation

When a patient is discharged, their bed can be released and made available for another patient.

---

## 8. Billing Management

The Billing module manages the patient's hospital charges.

A bill can include:

* Consultation charges
* Room or bed charges
* Treatment charges
* Medicine charges
* Other hospital service charges
* Total amount

Example:

```text
Consultation
Room / Bed Charges
Treatment Charges
Medicine / Service Charges
Other Services
-----------------------
Total Amount
```

The system calculates and stores the total amount payable by the patient.

---

## 9. Discharge Management

The Discharge module completes the patient's hospital process.

During discharge, the system can:

* Identify the patient.
* Finalize the patient's bill.
* Update the patient's status.
* Release the assigned bed.
* Update doctor availability.
* Save the patient's final record.

### Discharge Flow

```text
Treatment Completed
        ↓
     Final Bill
        ↓
      Discharge
        ↓
     Release Bed
        ↓
Update Availability
        ↓
   Save Record
```

---

# Data Structures Used

Care-Pulse uses custom implementations of different data structures.

| Data Structure     | Use in Care-Pulse             |
| ------------------ | ----------------------------- |
| Linked List        | Managing dynamic records      |
| Queue              | Managing OPD patients         |
| Priority Queue     | Managing emergency patients   |
| Stack              | Maintaining recent operations |
| Binary Search Tree | Searching patient records     |
| Hash Table         | Finding doctor information    |

## Queue

A Queue follows the **FIFO (First-In-First-Out)** principle.

It is mainly used for normal OPD patients.

```text
Front
  ↓
[P1] [P2] [P3] [P4]
                    ↑
                   Rear
```

The patient who enters first is processed first.

---

## Priority Queue

A Priority Queue is used for emergency patients.

Instead of considering only arrival time, patients are handled according to their priority or severity.

```text
Highest Priority
       ↓
    Critical
       ↓
     Severe
       ↓
    Moderate
       ↓
     Stable
```

---

## Binary Search Tree

A **Binary Search Tree (BST)** is used for searching patient records using their IDs.

Example:

```text
             50
            /  \
          30    70
         /  \  /  \
       20  40 60  80
```

The basic rule is:

```text
Left < Root < Right
```

This allows patient records to be searched using comparisons instead of checking every record one by one.

---

## Hash Table

A **Hash Table** is used for quick doctor lookup.

The basic process is:

```text
Doctor ID
    ↓
Hash Function
    ↓
Table Index
    ↓
Doctor Record
```

This provides fast access to doctor information in normal cases.

---

## Stack

A Stack follows the **LIFO (Last-In-First-Out)** principle.

It can be used to store recent operations or history.

```text
       TOP
        ↓
       [D]
       [C]
       [B]
       [A]
```

The most recently added item is accessed first.

---

## Linked List

A Linked List stores records using connected nodes.

It is useful when the number of records can change during program execution.

```text
[Record 1] → [Record 2] → [Record 3] → NULL
```

---

# Object-Oriented Design

Care-Pulse uses **Object-Oriented Programming (OOP)** to represent different hospital entities.

The main class structure is:

```text
              Person
             /  |   \
            /   |    \
       Patient Doctor Staff
```

Other supporting classes include:

* Appointment
* Ward
* Room
* Bed
* Bill
* Hospital Controller

---

# OOP Concepts Used

## Encapsulation

Data and the functions related to that data are kept together inside classes.

This helps keep the information organized and controlled.

## Inheritance

Common properties are placed inside the `Person` class.

Other classes can inherit from it:

```text
Person
 ├── Patient
 ├── Doctor
 └── Staff
```

## Abstraction

Complex operations are hidden behind simpler functions or interfaces.

For example, the Hospital Controller can manage patient flow without requiring the user to know how every data structure works internally.

## Polymorphism

Common functions can be defined at a general level and can work differently for different classes when required.

---

# System Architecture

Care-Pulse follows a modular design.

The **Hospital Controller** manages the major hospital modules.

```text
User / Staff Input
        ↓
Hospital Controller
        ↓
Hospital Modules
        ↓
Patient / Doctor / Admission
        ↓
Custom Data Structures
        ↓
Hospital Operations
        ↓
Record Storage
```

The main modules include:

* Patient Management
* OPD Management
* Emergency Management
* Doctor Management
* Appointment Management
* Admission and Bed Management
* Billing
* Discharge
* Record Storage

---

# Hospital Controller

The **Hospital Controller** acts as the main coordination part of Care-Pulse.

Its responsibilities include:

* Receiving patient or staff operations.
* Sending patients to OPD or emergency processing.
* Managing doctor assignment.
* Managing admission.
* Allocating beds.
* Starting the billing process.
* Processing discharge.
* Updating hospital records.

It helps different modules work together in an organized way.

---

# Patient Journey

Care-Pulse follows the complete patient journey.

### Step 1 – Registration

* Patient information is entered.
* A patient record is created.

### Step 2 – OPD or Emergency

The patient is sent to either:

* Normal OPD processing, or
* Emergency processing.

### Step 3 – Queue Processing

* Normal patients enter the FIFO Queue.
* Emergency patients enter the Priority Queue according to severity.

### Step 4 – Doctor Assignment

An available and suitable doctor is assigned.

### Step 5 – Consultation

The doctor checks the patient and decides whether admission is required.

### Step 6 – Admission

If admission is required:

* Available ward is checked.
* Available room is checked.
* Available bed is assigned.

### Step 7 – Treatment

The patient's status and assigned hospital resources are maintained.

### Step 8 – Billing

The patient's charges are calculated and the bill is generated.

### Step 9 – Discharge

* The final bill is prepared.
* The patient is discharged.
* The bed is released.
* Doctor availability is updated.
* The record is saved.

---

# Record Storage

Care-Pulse uses **file-based storage** to keep important records.

This allows records to remain available even after the program is closed.

Records may include:

* Patient records
* Doctor records
* Appointment details
* Bed allocation details
* Billing records
* Discharge information

---

# Technology Used

## Core System

* **Language:** C++
* **Concepts:** Object-Oriented Programming and Data Structures & Algorithms
* **Data Storage:** File-based storage
* **Development Environment:** Visual Studio Code
* **Version Control:** Git and GitHub

The main DSA components are implemented using custom data structures instead of directly depending on STL implementations.

---

# Project Structure

```text
Care-Pulse/
│
├── src/
│   ├── main.cpp
│   ├── patient.cpp
│   ├── doctor.cpp
│   ├── appointment.cpp
│   ├── queue.cpp
│   ├── priorityqueue.cpp
│   ├── bst.cpp
│   ├── hashtable.cpp
│   ├── stack.cpp
│   └── ...
│
├── data/
│   ├── patients
│   ├── doctors
│   ├── appointments
│   └── bills
│
├── docs/
│   ├── System_Architecture.png
│   └── System_Workflow.png
│
├── README.md
└── .gitignore
```

The project structure can be changed as new modules are added.

---

# Requirements

To run Care-Pulse, you need:

* A C++ compiler that supports modern C++ standards.
* Visual Studio Code or another C++ development environment.
* Git for repository management.

---

# Running the Project

Clone the repository:

```bash
git clone <repository-url>
```

Go to the project folder:

```bash
cd Care-Pulse
```

Compile the required C++ files using a C++ compiler and run the generated executable.

The exact compilation command may depend on the module or project structure.

---

# Development Phases

## Phase 1 – Planning and Design

* Define the hospital workflow.
* Design the system architecture.
* Identify the main hospital entities.
* Decide which data structure will be used for each operation.
* Design the OOP class hierarchy.

## Phase 2 – Module Development

* Develop patient management.
* Develop doctor management.
* Implement Queue.
* Implement Priority Queue.
* Implement BST.
* Implement Hash Table.
* Implement Stack.
* Implement Linked List.
* Develop the Hospital Controller.
* Implement file-based storage.
* Develop individual modules separately for testing.

## Phase 3 – System Integration

* Connect patient and doctor modules.
* Connect OPD and emergency modules.
* Connect admission and bed management.
* Connect billing.
* Connect discharge.
* Connect all modules through the Hospital Controller.

## Final Testing

* Test individual modules.
* Test complete patient workflows.
* Test different possible cases.
* Check data consistency.
* Improve performance and reliability.

---

# Future Scope

Care-Pulse can be extended in the future with:

* Database-based storage
* Role-based login and access
* Hospital reports and analytics
* Pharmacy management
* Laboratory management
* Medical record management
* Insurance and payment integration
* Notifications and alerts
* Advanced appointment scheduling
* Multiple hospital or branch management
* Integration with other healthcare systems
* Cloud deployment

---

# Project Status

**Status: In Active Development**

The project has its basic architecture, hospital workflow, DSA mapping, and OOP design planned. Individual modules are being developed and tested separately before final integration.

---

# Team

| Name               | Role      | Main Contribution                               |
| ------------------ | --------- | ----------------------------------------------- |
| Dishita Gairola    | Team Lead | System workflow, architecture and DSA mapping   |
| Siddharth Dangi    | Member    | Documentation, presentation and system workflow |
| Priya Negi         | Member    | Architecture and DSA mapping                    |
| Tanmay Kulshrestha | Member    | OOP design research and feasibility study       |

---

# Repository

The source code and project documentation are maintained on GitHub.

**Repository:** Care-Pulse GitHub Repository

---

# License

This project is developed for academic purposes, demonstration, and further development of the Care-Pulse Hospital Management System.
