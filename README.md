# Student Grade Book in C

A console-based Student Grade Book system written in C for managing student records, marks, grades, pass/fail status, ranking, and file storage.

## Project Overview

This project is a simple but complete C program that helps manage student academic data using arrays, structures, functions, and binary file handling. It supports adding students, entering marks for five subjects, calculating total and average, assigning grades, checking pass/fail status, finding highest and lowest marks, displaying rank lists, searching records, updating marks, and deleting students.

## Features

- Add new student records.
- Display all student details.
- Enter marks for 5 subjects.
- Calculate total and average marks.
- Assign grades based on average.
- Check pass/fail status.
- Find highest marks in a subject.
- Find lowest marks in a subject.
- Display students in rank order.
- Search student by ID or roll number.
- Update student marks.
- Delete student record.
- Save and load records using a binary file.

## Subjects Covered

The program supports the following 5 subjects:

1. Mathematics
2. Physics
3. Chemistry
4. Computer Science
5. English

## File Structure

```bash
StudentGradeBook-c/
│
├── gradebook.c
├── grades.dat
├── README.md
└── Makefile
```

## Requirements

- C Compiler (GCC recommended)
- Windows PowerShell, Command Prompt, or VS Code terminal
- No external libraries required

## How to Compile

Open the terminal in your project folder and run:

```bash
gcc gradebook.c -o gradebook.exe
```

If you are using Linux or Mac, use:

```bash
gcc gradebook.c -o gradebook
```

## How to Run

### On Windows PowerShell
```powershell
.\gradebook.exe
```

### On Linux/Mac
```bash
./gradebook
```

## Menu Options

When the program runs, it shows this menu:

1. Add Student
2. Display All Students
3. Enter Marks
4. Calculate Total & Average
5. Find Highest Marks
6. Find Lowest Marks
7. Assign Grades
8. Check Pass/Fail
9. Display Rank List
10. Search Student
11. Update Marks
12. Delete Student
13. Exit

## Grade Criteria

- `A` = 90 and above
- `B` = 80 to 89
- `C` = 70 to 79
- `D` = 60 to 69
- `E` = 50 to 59
- `F` = below 50

## Pass/Fail Criteria

- `PASS` = Average marks 50 or above
- `FAIL` = Average marks below 50

## Sample Test Case

### Add Student
- ID: 101
- Name: Rahul Kumar
- Roll Number: CS2024001
- Class: BSc CS Year 1

### Enter Marks
- Mathematics: 85
- Physics: 78
- Chemistry: 82
- Computer Science: 90
- English: 75

### Output
- Total: 410/500
- Average: 82.00
- Grade: B
- Status: PASS

## File Handling

The program uses a binary file named `grades.dat` to store student records permanently. When the program starts, it loads the saved data automatically. When the program exits, it saves the updated records back to the file.

## Validation Rules

- Marks must be between 0 and 100.
- Negative marks are not allowed.
- Maximum students: 100.
- Maximum subjects: 5.

## Notes

- This project is fully console-based.
- It does not use any GUI or database.
- All logic is implemented using arrays, structures, and functions.

## Author

Created for learning and academic practice in C programming.

## License

This project is free to use for educational purposes.
