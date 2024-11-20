#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "employee.csv"

struct employee
{
    char name[100];
    long int code;
    char designation[100];
    int exp;
    int age;
    float baseSalary; // New field for base salary
    float salary; // New field for salary
};

int num = 0;
int max = 20;
struct employee *emp = NULL;

void showMenu();
void insert();
void build();
void addDataToCSV(struct employee emp);
void loadCSVData();
void deleteIndex(int i);
void deleteRecord();
void searchRecord();
void showTable();
void updateRecord();
float calculateSalary(float baseSalary);
int isUniqueCode(long int code);

void build()
{
    printf("Build The Table\n");
    printf("Maximum Entries can be %d\n", max);

    printf("Enter the number of Entries required: ");
    scanf("%d", &num);

    if (num > max)
    {
        printf("Maximum number of Entries are %d. Setting entries to %d.\n", max, max);
        num = max;
    }

    emp = (struct employee *)malloc(max * sizeof(struct employee));
    if (emp == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    printf("Enter the following data:\n");

    for (int i = 0; i < num; i++)
    {
        printf("Enter the information of Employee %d\n", i + 1);
        printf("Name: ");
        scanf("%s", emp[i].name);

        printf("Employee ID: ");
        scanf("%ld", &emp[i].code);
        while (!isUniqueCode(emp[i].code))
        {
            printf("Employee ID already exists. Enter a unique Employee ID: ");
            scanf("%ld", &emp[i].code);
        }

        printf("Designation: ");
        scanf("%s", emp[i].designation);

        printf("Experience: ");
        scanf("%d", &emp[i].exp);

        printf("Age: ");
        scanf("%d", &emp[i].age);

        printf("Base Salary: ");
        scanf("%f", &emp[i].baseSalary);
        emp[i].salary = calculateSalary(emp[i].baseSalary);

        // Add the data to the CSV file
        addDataToCSV(emp[i]);
    }
    // Reload data from CSV after building the table
    loadCSVData();
}

void addDataToCSV(struct employee emp)
{
    // write data to csv file
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL)
    {
        printf("Error opening file for writing\n");
        return;
    }
    fprintf(file, "%s,%ld,%s,%d,%d,%.2f,%.2f\n", emp.name, emp.code, emp.designation, emp.exp, emp.age, emp.baseSalary, emp.salary);
    fclose(file);
}

void loadCSVData()
{
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL)
    {
        printf("File not found\n");
        return;
    }

    emp = (struct employee *)malloc(max * sizeof(struct employee));
    if (emp == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    num = 0; // Initialize num to 0 before loading data
    while (fscanf(file, "%[^,],%ld,%[^,],%d,%d,%f,%f\n", emp[num].name, &emp[num].code, emp[num].designation, &emp[num].exp, &emp[num].age, &emp[num].baseSalary, &emp[num].salary) != EOF)
    {
        if (num >= max)
        {
            printf("Maximum number of Entries are %d. Some entries in the file are not loaded.\n", max);
            break;
        }
        num++;
    }

    fclose(file);
}

void insert()
{
    if (num < max)
    {
        int i = num;

        printf("Enter the information of the Employee\n");
        printf("Name: ");
        scanf("%s", emp[i].name);

        printf("Employee ID: ");
        scanf("%ld", &emp[i].code);
        while (!isUniqueCode(emp[i].code))
        {
            printf("Employee ID already exists. Enter a unique Employee ID: ");
            scanf("%ld", &emp[i].code);
        }

        printf("Designation: ");
        scanf("%s", emp[i].designation);

        printf("Experience: ");
        scanf("%d", &emp[i].exp);

        printf("Age: ");
        scanf("%d", &emp[i].age);

        printf("Base Salary: ");
        scanf("%f", &emp[i].baseSalary);
        emp[i].salary = calculateSalary(emp[i].baseSalary);

        // add data to csv file
        addDataToCSV(emp[i]);
        num++;
    }
    else
    {
        printf("Employee Table Full\n");
    }
}

void deleteIndex(int i)
{
    for (int j = i; j < num - 1; j++)
    {
        emp[j] = emp[j + 1];
    }
}

void deleteRecord()
{
    printf("Enter the Employee ID to Delete Record: ");

    long int code;
    scanf("%ld", &code);
    for (int i = 0; i < num; i++)
    {
        if (emp[i].code == code)
        {
            deleteIndex(i);
            num--;
            break;
        }
    }

    // Update the CSV file after deletion
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing\n");
        return;
    }
    for (int i = 0; i < num; i++)
    {
        fprintf(file, "%s,%ld,%s,%d,%d,%.2f,%.2f\n", emp[i].name, emp[i].code, emp[i].designation, emp[i].exp, emp[i].age, emp[i].baseSalary, emp[i].salary);
    }
    fclose(file);
}

void searchRecord()
{
    printf("Enter the Employee ID to Search Record: ");

    long int code;
    scanf("%ld", &code);

    for (int i = 0; i < num; i++)
    {
        if (emp[i].code == code)
        {
            printf("Name: %s\n", emp[i].name);
            printf("Employee ID: %ld\n", emp[i].code);
            printf("Designation: %s\n", emp[i].designation);
            printf("Experience: %d\n", emp[i].exp);
            printf("Age: %d\n", emp[i].age);
            printf("Base Salary: %.2f\n", emp[i].baseSalary);
            printf("Salary: %.2f\n", emp[i].salary);
            break;
        }
    }
}

void showTable()
{
    printf("Employee Table\n");
    printf("%-20s%-20s%-20s%-20s%-20s%-20s%-20s\n", "Name", "Employee ID", "Designation", "Experience", "Age", "Base Salary", "Salary");
    printf("----------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < num; i++)
    {
        printf("%-20s%-20ld%-20s%-20d%-20d%-20.2f%-20.2f\n", emp[i].name, emp[i].code, emp[i].designation, emp[i].exp, emp[i].age, emp[i].baseSalary, emp[i].salary);
    }
}

void updateRecord()
{
    printf("Enter the Employee ID to Update Record: ");

    long int code;
    scanf("%ld", &code);

    for (int i = 0; i < num; i++)
    {
        if (emp[i].code == code)
        {
            printf("Enter the new information of the Employee\n");
            printf("Name: ");
            scanf("%s", emp[i].name);

            printf("Designation: ");
            scanf("%s", emp[i].designation);

            printf("Experience: ");
            scanf("%d", &emp[i].exp);

            printf("Age: ");
            scanf("%d", &emp[i].age);

            printf("Base Salary: ");
            scanf("%f", &emp[i].baseSalary);
            emp[i].salary = calculateSalary(emp[i].baseSalary);
            
             printf("Record is updated succesfully.\n");
            // Update the CSV file after updating the record
            FILE *file = fopen(FILE_NAME, "w");
            if (file == NULL)
            {
                printf("Error opening file for writing\n");
                return;
            }
            for (int j = 0; j < num; j++)
            {
                fprintf(file, "%s,%ld,%s,%d,%d,%.2f,%.2f\n", emp[j].name, emp[j].code, emp[j].designation, emp[j].exp, emp[j].age, emp[j].baseSalary, emp[j].salary);
            }
            fclose(file);
            break;
            
        }
    }
}

void showMenu()
{
    do
    {
        printf("-------------------------Employee Management System-------------------------\n\n");

        printf("Available Options:\n\n");
        printf("%-20s(%d)\n", "Build Table", 1);
        printf("%-20s(%d)\n", "Insert New Entry", 2);
        printf("%-20s(%d)\n", "Delete Entry", 3);
        printf("%-20s(%d)\n", "Search a Record", 4);
        printf("%-20s(%d)\n", "Show Table", 5);
        printf("%-20s(%d)\n", "Update Record", 6); // New option for updating a record
        printf("%-20s(%d)\n", "Exit", 7);

        int option;
        scanf("%d", &option);

        if (option == 1)
        {
            build();
        }
        else if (option == 2)
        {
            insert();
        }
        else if (option == 3)
        {
            deleteRecord();
        }
        else if (option == 4)
        {
            searchRecord();
        }
        else if (option == 5)
        {
            showTable();
        }
        else if (option == 6)
        {
            updateRecord();
        }
        else if (option == 7)
        {
            break;
        }
        else
        {
            printf("Expected Options are 1/2/3/4/5/6/7\n");
        }
    } while (1);

    printf("Bye Bye\n");
}

float calculateSalary(float baseSalary)
{
    return baseSalary * 0.82 * 1.05; // Deduct 18% GST and add 5% household allowance
}

int isUniqueCode(long int code)
{
    for (int i = 0; i < num; i++)
    {
        if (emp[i].code == code)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    loadCSVData();
    showMenu();
    free(emp);
    return 0;
}
