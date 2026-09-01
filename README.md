# Athena

## Hospital Management System

Athena is a C++-based Hospital Management System developed as a
Project-Based Learning (PBL) project. The system combines
**Data Structures & Algorithms (DSA)** with **Object-Oriented Programming (OOP)**
to model and manage common hospital operations.

The primary goal of Athena is to demonstrate how custom-built data structures
and OOP principles can be integrated into a single practical application.

---

## Project Overview

A hospital involves multiple interconnected processes such as patient
registration, OPD management, emergency triage, doctor assignment,
hospital admission, ward and bed allocation, appointments, billing, and
discharge.

Athena aims to bring these processes together into one system while using
appropriate data structures for different operations.

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
Treatment   Ward/Bed Allocation
   ↓           ↓
   └────── Treatment
             ↓
           Billing
             ↓
          Discharge
             ↓
       Record Persistence