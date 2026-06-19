#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 5
#define FILENAME "grades.dat"

const char *subjectNames[MAX_SUBJECTS] = {
    "Mathematics",
    "Physics",
    "Chemistry",
    "Computer Science",
    "English"};

typedef struct
{
    int studentID;
    char name[50];
    char rollNumber[20];
    char className[20];

    float subjects[MAX_SUBJECTS];

    float total;
    float average;

    char grade;
    char status[10];

} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

void saveToFile();
void loadFromFile();
void displayMenu();

void addStudent();
void displayAllStudents();
void enterMarks();
void calculateStudentResult(int index);

void findHighest();
void findLowest();

char assignGrade(float avg);
void assignGrades();

void updateMarks();
void deleteStudent();

void displayRankList();
void searchStudent();

int findStudentIndexByID(int id);

void saveToFile()
{
    FILE *fp = fopen(FILENAME, "wb");

    if (fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    fwrite(&studentCount, sizeof(int), 1, fp);
    fwrite(students, sizeof(Student), studentCount, fp);

    fclose(fp);
}

void loadFromFile()
{
    FILE *fp = fopen(FILENAME, "rb");

    if (fp == NULL)
        return;

    fread(&studentCount, sizeof(int), 1, fp);
    fread(students, sizeof(Student), studentCount, fp);

    fclose(fp);
}

void displayMenu()
{
    printf("\n");
    printf("=====================================\n");
    printf("     STUDENT GRADE BOOK SYSTEM\n");
    printf("=====================================\n");

    printf("1. Add Student\n");
    printf("2. Display All Students\n");
    printf("3. Enter Marks\n");
    printf("4. Calculate Results\n");
    printf("5. Find Highest Marks\n");
    printf("6. Find Lowest Marks\n");
    printf("7. Assign Grades\n");
    printf("8. Display Rank List\n");
    printf("9. Search Student\n");
    printf("10. Update Marks\n");
    printf("11. Delete Student\n");
    printf("12. Save Data\n");
    printf("13. Exit\n");

    printf("Enter Choice: ");
}

void addStudent()
{
    if (studentCount >= MAX_STUDENTS)
    {
        printf("Storage Full!\n");
        return;
    }

    Student s;

    printf("Enter Student ID: ");
    scanf("%d", &s.studentID);

    getchar();

    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter Roll Number: ");
    fgets(s.rollNumber, sizeof(s.rollNumber), stdin);
    s.rollNumber[strcspn(s.rollNumber, "\n")] = 0;

    printf("Enter Class: ");
    fgets(s.className, sizeof(s.className), stdin);
    s.className[strcspn(s.className, "\n")] = 0;

    for (int i = 0; i < MAX_SUBJECTS; i++)
        s.subjects[i] = 0;

    s.total = 0;
    s.average = 0;
    s.grade = 'F';

    strcpy(s.status, "FAIL");

    students[studentCount++] = s;

    saveToFile();

    printf("Student Added Successfully.\n");
}

void calculateStudentResult(int index)
{
    float total = 0;

    for (int i = 0; i < MAX_SUBJECTS; i++)
        total += students[index].subjects[i];

    students[index].total = total;
    students[index].average = total / MAX_SUBJECTS;

    students[index].grade =
        assignGrade(students[index].average);

    if (students[index].average >= 50)
        strcpy(students[index].status, "PASS");
    else
        strcpy(students[index].status, "FAIL");
}

char assignGrade(float avg)
{
    if (avg >= 90)
        return 'A';
    else if (avg >= 80)
        return 'B';
    else if (avg >= 70)
        return 'C';
    else if (avg >= 60)
        return 'D';
    else if (avg >= 50)
        return 'E';
    else
        return 'F';
}

void enterMarks()
{
    int id;

    printf("Enter Student ID: ");
    scanf("%d", &id);

    int index = findStudentIndexByID(id);

    if (index == -1)
    {
        printf("Student Not Found!\n");
        return;
    }

    for (int i = 0; i < MAX_SUBJECTS; i++)
    {
        float mark;

        do
        {
            printf("%s: ", subjectNames[i]);
            scanf("%f", &mark);

            if (mark < 0 || mark > 100)
                printf("Marks must be 0-100\n");

        } while (mark < 0 || mark > 100);

        students[index].subjects[i] = mark;
    }

    calculateStudentResult(index);

    saveToFile();

    printf("Marks Updated Successfully.\n");
}

void displayAllStudents()
{
    if (studentCount == 0)
    {
        printf("No Records Found.\n");
        return;
    }

    printf("\n==========================================================================\n");

    for (int i = 0; i < studentCount; i++)
    {
        printf("ID       : %d\n", students[i].studentID);
        printf("Name     : %s\n", students[i].name);
        printf("Roll No  : %s\n", students[i].rollNumber);
        printf("Class    : %s\n", students[i].className);

        printf("Marks: ");

        for (int j = 0; j < MAX_SUBJECTS; j++)
            printf("%.2f ", students[i].subjects[j]);

        printf("\n");

        printf("Total    : %.2f\n", students[i].total);
        printf("Average  : %.2f\n", students[i].average);
        printf("Grade    : %c\n", students[i].grade);
        printf("Status   : %s\n", students[i].status);

        printf("----------------------------------------------------------------\n");
    }
}

void findHighest()
{
    if (studentCount == 0)
        return;

    for (int subject = 0; subject < MAX_SUBJECTS; subject++)
    {
        float highest = students[0].subjects[subject];
        int idx = 0;

        for (int i = 1; i < studentCount; i++)
        {
            if (students[i].subjects[subject] > highest)
            {
                highest = students[i].subjects[subject];
                idx = i;
            }
        }

        printf("%s -> %.2f (%s)\n",
               subjectNames[subject],
               highest,
               students[idx].name);
    }
}

void findLowest()
{
    if (studentCount == 0)
        return;

    for (int subject = 0; subject < MAX_SUBJECTS; subject++)
    {
        float lowest = students[0].subjects[subject];
        int idx = 0;

        for (int i = 1; i < studentCount; i++)
        {
            if (students[i].subjects[subject] < lowest)
            {
                lowest = students[i].subjects[subject];
                idx = i;
            }
        }

        printf("%s -> %.2f (%s)\n",
               subjectNames[subject],
               lowest,
               students[idx].name);
    }
}

void assignGrades()
{
    for (int i = 0; i < studentCount; i++)
        calculateStudentResult(i);

    printf("Grades Assigned.\n");
}

void displayRankList()
{
    Student temp[MAX_STUDENTS];

    for (int i = 0; i < studentCount; i++)
        temp[i] = students[i];

    for (int i = 0; i < studentCount - 1; i++)
    {
        for (int j = 0; j < studentCount - i - 1; j++)
        {
            if (temp[j].average < temp[j + 1].average)
            {
                Student t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }

    printf("\nRANK LIST\n");

    for (int i = 0; i < studentCount; i++)
    {
        printf("%d. %s | Avg: %.2f | Grade: %c\n",
               i + 1,
               temp[i].name,
               temp[i].average,
               temp[i].grade);
    }
}

int findStudentIndexByID(int id)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].studentID == id)
            return i;
    }

    return -1;
}

void searchStudent()
{
    int id;

    printf("Enter Student ID: ");
    scanf("%d", &id);

    int index = findStudentIndexByID(id);

    if (index == -1)
    {
        printf("Not Found.\n");
        return;
    }

    printf("Name: %s\n", students[index].name);
    printf("Average: %.2f\n", students[index].average);
    printf("Grade: %c\n", students[index].grade);
}

void updateMarks()
{
    enterMarks();
}

void deleteStudent()
{
    int id;

    printf("Enter Student ID: ");
    scanf("%d", &id);

    int index = findStudentIndexByID(id);

    if (index == -1)
    {
        printf("Student Not Found.\n");
        return;
    }

    for (int i = index; i < studentCount - 1; i++)
        students[i] = students[i + 1];

    studentCount--;

    saveToFile();

    printf("Deleted Successfully.\n");
}

int main()
{
    int choice;

    loadFromFile();

    do
    {
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayAllStudents();
            break;
        case 3:
            enterMarks();
            break;
        case 4:
            assignGrades();
            break;
        case 5:
            findHighest();
            break;
        case 6:
            findLowest();
            break;
        case 7:
            assignGrades();
            break;
        case 8:
            displayRankList();
            break;
        case 9:
            searchStudent();
            break;
        case 10:
            updateMarks();
            break;
        case 11:
            deleteStudent();
            break;
        case 12:
            saveToFile();
            printf("Saved.\n");
            break;
        case 13:
            saveToFile();
            printf("Goodbye.\n");
            break;
        default:
            printf("Invalid Choice.\n");
        }

    } while (choice != 13);

    return 0;
}