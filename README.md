# Toshokan Bookstore Management System
Toshokan-BMS is a programming written for CINS242: Information Systems Design taught by Michael Larson at California State University, Chico. The pre-requisite for CINS242 is the first programming course CSCI111. Toshokan is written in a manner for students whom have only completed CSCI111. There are features/concepts implemented that are taught in later courses.

## TanoTech
Tano Technologies, LLC. (TanoTech) is the fictitious company who designed, developed, and launched Toshokan-BMS. 

## Compiling
To compile use the included Makefile. Once you have cloned the repo, navigate to the toshokan-bms/toshokan-bms directory and type Make.

If you choose to compile in a different method, you will need to compile with C++ Standard 17 or higher.

The following set-ups have successfully compiled and ran Toshokan:
- Windows 10 with WSL2 running Ubuntu 2004 and g++ version 9.4.0
- MacOS 13.5.1 with M1 chip and clang version 14.0.3

## Running
To run toshokan after compiling, type in ./toshokan.

By default, two users are available:
- Elton John, ID: 12345, Password: test123
- Fred Johnson, ID: 98765, Password: taco

Elton John is in the SUPERUSER group, Fred Johnson is in the CLERK group.

## Data Files
In the toshokan-bms/data folder are multiple files.
- users.dat - contains the user information to include id and password. The data is encoded into base64.
- All other .dat files - contain the stores "database" of products
- All .bak files - a copy of the corresponding dat files.