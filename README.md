# Athena

## Hospital Management System

Athena is a **C++-based Hospital Management System** designed to organize and manage the major operational processes of a hospital through a unified system.

The system combines **Data Structures & Algorithms (DSA)** and **Object-Oriented Programming (OOP)** to efficiently manage patients, doctors, appointments, OPD queues, emergency cases, admissions, wards, rooms, beds, billing, and discharge.

Athena is designed around the complete patient journey, from registration and consultation to admission, treatment, billing, and discharge, while maintaining organized and persistent records.

---

## Project Overview

A hospital consists of multiple interconnected processes that need to work together efficiently. Patient registration, OPD management, emergency handling, doctor assignment, admission, bed allocation, billing, and discharge are all dependent on accurate and timely information.

Athena brings these processes together into a centralized hospital management system.

The system provides different data structures for different operational requirements. Regular OPD patients are handled using a **Queue**, emergency patients are prioritized using a **Priority Queue**, patient records can be searched using a **Binary Search Tree**, and doctor information can be accessed efficiently using a **Hash Table**.

The overall patient workflow is:

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
Treatment   Ward / Room / Bed Allocation
   ↓           ↓
   └────── Treatment
             ↓
           Billing
             ↓
          Discharge
             ↓
      Record Persistence
```

---

## Objectives

Athena is designed to:

* Centralize major hospital management operations.
* Maintain organized patient and doctor records.
* Manage OPD patients using First-In-First-Out (FIFO) processing.
* Prioritize emergency patients according to severity.
* Provide efficient patient searching.
* Provide fast doctor information lookup.
* Manage hospital wards, rooms, and beds.
* Track doctor availability and assignments.
* Manage appointments and consultations.
* Generate itemized patient bills.
* Process patient discharge.
* Maintain records between different executions of the system.
* Demonstrate efficient use of custom Data Structures and Object-Oriented Programming.

---

## Core Features

### Patient Management

Athena provides a centralized mechanism for managing patient information.

The system can maintain details such as:

* Patient ID
* Patient name
* Age
* Contact information
* Medical-related admission information
* Assigned doctor
* Admission status
* Current hospital status

Patient records can be searched efficiently using the implemented search structure.

---

### OPD Management

The OPD module manages patients waiting for consultation.

Patients entering the OPD are placed into a **Queue** and processed according to the FIFO principle.

```text
Patient A → Patient B → Patient C → Patient D

Service Order:

A → B → C → D
```

This ensures that patients are processed in their arrival order.

---

### Emergency Management

Emergency cases require a different processing strategy from normal OPD cases.

Athena uses a **Priority Queue** to prioritize emergency patients according to their severity.

For example:

```text
Critical   → Highest Priority
Severe     → High Priority
Moderate   → Medium Priority
Stable     → Lower Priority
```

Therefore, an emergency patient with higher severity can be handled before a lower-severity case even if they arrived later.

---

### Doctor Management

The Doctor Management module maintains information about available doctors and their assignments.

The system can manage:

* Doctor ID
* Doctor name
* Department/specialization
* Availability
* Assigned patients
* Consultation information

Doctor lookup is supported using a **Hash Table** for efficient access.

---

### Doctor Assignment

After OPD or emergency processing, the patient can be assigned to an appropriate available doctor.

The system maintains doctor availability so that a doctor who is already occupied is not incorrectly assigned to another patient.

The general flow is:

```text
Patient
   ↓
OPD / Emergency
   ↓
Doctor Availability
   ↓
Doctor Assignment
   ↓
Consultation
```

---

### Appointment Management

Appointments can be organized according to patient and doctor information.

The appointment module connects:

```text
Patient
   +
Doctor
   +
Appointment Information
```

This helps maintain an organized consultation schedule.

---

### Ward, Room and Bed Management

For patients requiring admission, Athena manages hospital resources through a hierarchy:

```text
Ward
  ↓
Room
  ↓
Bed
```

The system tracks available and occupied beds and assigns an appropriate available bed to an admitted patient.

When a patient is discharged, the assigned bed can be released and made available again.

---

### Billing Management

Athena provides itemized billing for patients.

A bill can contain multiple charges such as:

```text
Consultation
Room / Bed Charges
Treatment Charges
Medicine / Service Charges
Other Hospital Services
--------------------------------
Total Amount
```

The billing module calculates and maintains the patient's total payable amount.

---

### Discharge Management

The discharge process completes the patient's hospital journey.

During discharge, the system can:

* Identify the patient.
* Finalize the patient's bill.
* Update the patient's status.
* Release the assigned bed.
* Update doctor availability.
* Preserve the patient's record.

The general process is:

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
Record Persistence
```

---

## Data Structures

Athena uses custom implementations of multiple Data Structures to handle different hospital operations.

| Data Structure     | Hospital Application                  |
| ------------------ | ------------------------------------- |
| Linked List        | Dynamic record management             |
| Queue              | OPD patient management                |
| Priority Queue     | Emergency patient prioritization      |
| Stack              | Maintaining recent operations/history |
| Binary Search Tree | Patient record searching              |
| Hash Table         | Doctor information lookup             |

### Queue

A Queue follows the **First-In-First-Out (FIFO)** principle.

It is used for normal OPD patients.

```text
Front
  ↓
[P1] [P2] [P3] [P4]
                    ↑
                   Rear
```

The first patient entering the queue is processed first.

---

### Priority Queue

A Priority Queue is used for emergency cases.

Instead of processing patients only according to arrival time, patients are processed according to their priority/severity.

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

### Binary Search Tree

A Binary Search Tree is used for organized patient searching.

For example:

```text
             50
           /    \
         30      70
        /  \    /  \
      20   40  60   80
```

For every node:

```text
Left  < Root < Right
```

This allows patient records to be searched by their identifier using comparisons rather than checking every record sequentially.

---

### Hash Table

A Hash Table is used for efficient doctor lookup.

A doctor's identifier can be converted into a table index using a hash function.

```text
Doctor ID
    ↓
Hash Function
    ↓
Table Index
    ↓
Doctor Record
```

This provides fast access to doctor information in typical cases.

---

### Stack

A Stack follows the **Last-In-First-Out (LIFO)** principle.

It can be used to maintain recent system operations or history-related information.

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

### Linked List

A Linked List provides dynamic storage where records are connected through nodes.

It can be used where the number of records can change during system operation.

```text
[Record 1] → [Record 2] → [Record 3] → NULL
```

---

## Object-Oriented Design

Athena uses Object-Oriented Programming to represent the different entities involved in hospital operations.

The basic class hierarchy is:

```text
                 Person
                /      \
               /        \
          Patient      Doctor
               
                Staff
```

The system also contains supporting classes such as:

```text
Appointment
Ward
Room
Bed
Bill
Hospital Controller
```

---

## OOP Concepts

### Encapsulation

Data and the functions operating on that data are grouped inside classes.

This allows each hospital entity to manage its own information and operations.

---

### Inheritance

Common properties can be placed inside a base `Person` class, while specialized entities such as `Patient`, `Doctor`, and `Staff` can derive from it.

```text
Person
 ├── Patient
 ├── Doctor
 └── Staff
```

---

### Abstraction

Complex hospital operations are represented through simpler interfaces.

For example, the Hospital Controller can manage patient flow without requiring the user to directly interact with the internal implementation of every data structure.

---

### Polymorphism

Common operations can be defined at a general level and implemented according to the requirements of different derived classes.

---

## System Architecture

Athena follows a modular architecture in which the Hospital Controller coordinates the major components of the system.

```text
              User / Staff Input
                     │
                     ↓
          ┌─────────────────────┐
          │ Hospital Controller  │
          └──────────┬──────────┘
                     │
                     ↓
          ┌─────────────────────┐
          │   Hospital Modules  │
          └──────────┬──────────┘
                     │
          ┌──────────┼──────────┐
          ↓          ↓          ↓
       Patient     Doctor     Admission
       Module      Module      Module
          │          │          │
          └──────────┼──────────┘
                     ↓
          ┌─────────────────────┐
          │    Custom DSA       │
          │      Engine         │
          └──────────┬──────────┘
                     │
       ┌─────────────┼─────────────┐
       ↓             ↓             ↓
    Queue       Priority Queue     BST
       │             │             │
      OPD         Emergency       Patients
                     │
                     ↓
                Hash Table
                     │
                   Doctors
                     │
                     ↓
             File Persistence
                     │
                     ↓
             Hospital Records
```

---

## Hospital Controller

The **Hospital Controller** acts as the central coordination component of Athena.

It connects the different hospital modules and manages the movement of information between them.

Its responsibilities include:

* Receiving patient/staff operations.
* Routing patients to OPD or emergency handling.
* Managing doctor assignment.
* Coordinating admission.
* Managing bed allocation.
* Initiating billing.
* Processing discharge.
* Updating system records.

The controller provides a single flow through which different hospital operations can work together.

---

## Patient Journey

Athena is designed around the complete patient journey.

### Step 1 — Registration

Patient information is entered into the system and a unique patient record is created.

### Step 2 — OPD or Emergency

The patient is directed to either:

* Normal OPD processing, or
* Emergency processing.

### Step 3 — Queue Processing

Normal OPD patients enter the FIFO Queue.

Emergency patients enter the Priority Queue according to their severity.

### Step 4 — Doctor Assignment

An available and appropriate doctor is assigned to the patient.

### Step 5 — Consultation

The doctor evaluates the patient and determines whether admission is required.

### Step 6 — Admission

If admission is required, the system checks available wards, rooms, and beds.

### Step 7 — Treatment

The patient's hospital status and assigned resources are maintained.

### Step 8 — Billing

The patient's charges are calculated and an itemized bill is generated.

### Step 9 — Discharge

The patient's bill is finalized, the patient is discharged, and allocated resources are released.

---

## Record Persistence

Athena uses **file-based persistence** to maintain important records between different executions of the system.

This allows information to remain available even after the program is closed and started again.

Persistent information can include:

* Patient records
* Doctor records
* Appointment information
* Bed allocation information
* Billing records
* Discharge information

The persistence layer separates record storage from the main operational logic.

---

## Data Flow

The general data flow through the system is:

```text
Input
  ↓
Validation
  ↓
Hospital Controller
  ↓
Relevant Hospital Module
  ↓
Custom Data Structure
  ↓
Operation / Processing
  ↓
Record Update
  ↓
File Persistence
  ↓
Output / Status
```

---

## System Modules

```text
┌─────────────────────────────┐
│      Patient Management     │
└──────────────┬──────────────┘
               │
┌──────────────▼──────────────┐
│        OPD Management        │
└──────────────┬──────────────┘
               │
┌──────────────▼──────────────┐
│     Emergency Management     │
└──────────────┬──────────────┘
               │
┌──────────────▼──────────────┐
│       Doctor Management      │
└──────────────┬──────────────┘
               │
┌──────────────▼──────────────┐
│     Admission & Bed Mgmt.    │
└──────────────┬──────────────┘
               │
┌──────────────▼──────────────┐
│      Billing Management      │
└──────────────┬──────────────┘
               │
┌──────────────▼──────────────┐
│     Discharge Management     │
└─────────────────────────────┘
```

---

## Technology

### Core System

* **Language:** C++
* **Programming Paradigms:** Object-Oriented Programming and Data Structures & Algorithms
* **Data Storage:** File-based persistence
* **Development Environment:** Visual Studio Code
* **Version Control:** Git and GitHub

The core hospital logic is designed around custom data structures rather than depending on STL implementations for the primary DSA functionality.

---

## Project Structure

```text
Athena/
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

> The structure can be modified as the system grows and additional modules are introduced.

---

## Requirements

To build and run Athena, the system requires:

* C++ compiler supporting modern C++ standards
* Visual Studio Code or another C++ development environment
* Git (for repository management)

---

## Running the System

Clone the repository:

```bash
git clone <repository-url>
```

Navigate to the project directory:

```bash
cd Athena
```

Compile the source files using a C++ compiler and run the generated executable.

The exact compilation command may vary depending on the project structure and compiler being used.

---

## Development Roadmap

### Phase 1 — System Design

* Define hospital workflow
* Design system architecture
* Identify major hospital entities
* Map data structures to hospital operations
* Design OOP class hierarchy

### Phase 2 — Core Development

* Implement patient management
* Implement doctor management
* Implement Queue
* Implement Priority Queue
* Implement BST
* Implement Hash Table
* Implement Stack
* Implement Linked List
* Implement hospital controller
* Implement file persistence

### Phase 3 — System Integration

* Integrate patient and doctor modules
* Integrate OPD and emergency processing
* Integrate admission and bed allocation
* Integrate billing
* Integrate discharge
* Connect all modules through the Hospital Controller

### Phase 4 — Testing and Refinement

* Test individual modules
* Test complete patient workflows
* Test edge cases
* Validate data consistency
* Improve performance and reliability
* Refine the overall system

---

## Future Scope

Athena is designed to be extensible and can be expanded with additional capabilities in the future.

Potential extensions include:

* Database-backed storage
* Role-based access control
* Advanced hospital analytics
* Detailed reporting
* Multiple hospital/branch management
* Pharmacy and inventory management
* Laboratory management
* Medical record management
* Insurance and payment integration
* Notification and alert systems
* Advanced appointment scheduling
* Integration with external healthcare systems
* Cloud-based deployment

These extensions can be incorporated without changing the fundamental patient-management and DSA architecture of the system.

---

## Design Principles

Athena follows several important design principles:

### Modularity

Each major hospital operation is separated into its own logical module.

### Efficiency

Different data structures are selected according to the requirements of each operation.

### Maintainability

OOP principles help keep data and functionality organized.

### Extensibility

The system is designed so that additional hospital modules can be added in the future.

### Data Consistency

Changes to patients, doctors, beds, bills, and other resources are coordinated through the system controller.

---

## Project Status

**Current Status:** In active development.

The system architecture, hospital workflow, DSA mapping, and OOP design form the foundation of the system. Individual modules are being implemented and integrated progressively.

---

## Team

| Name               | Role      | Primary Contribution                          |
| ------------------ | --------- | --------------------------------------------- |
| Dishita Gairola    | Team Lead | System workflow, architecture & DSA mapping   |
| Siddharth Dangi    | Member    | Documentation, presentation & system workflow |
| Priya Negi         | Member    | Architecture & DSA mapping                    |
| Tanmay Kulshrestha | Member    | OOP design research & feasibility study       |

---

## Repository

The source code, documentation, and system development are maintained in this repository.

**Repository:** [Care-Pulse GitHub Repository](https://github.com/siddharthdangi/Care-Pulse)

---

## License

This project is intended for development, demonstration, and further extension of the Athena Hospital Management System.

---
