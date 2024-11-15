
#include <stdio.h>
#include <string.h>

#define max 20
#define FILE_NAME "employee.csv"

struct employee
{
    char name[100];
    long int code;
    char designation[100];
    int exp;
    int age;
};

int num;
void showMenu();
struct employee emp[max];

void insert();

void build()
{
    printf("Build The Table\n");
    printf("Maximum Entries can be %d\n", max);

    printf("Enter the number of Entries required: ");
    scanf("%d", &num);

    if (num > 20)
    {
        printf("Maximum number of Entries are 20\n");
        num = 20;
    }
    printf("Enter the following data:\n");

    for (int i = 0; i < num; i++)
    {
        insert();
    }
}

void addDataToCSV(struct employee emp)
{
    // write data to csv file
    FILE *file = fopen(FILE_NAME, "a");
    fprintf(file, "%s,%ld,%s,%d,%d\n", emp.name, emp.code, emp.designation, emp.exp, emp.age);

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

    while (fscanf(file, "%[^,],%ld,%[^,],%d,%d\n", emp[num].name, &emp[num].code, emp[num].designation, &emp[num].exp, &emp[num].age) != EOF)
    {
        num++;
    }

    fclose(file);
}

void insert()
{
    if (num < max)
    {
        int i = num;
        num++;

        printf("Enter the information of the Employee\n");
        printf("Name: ");
        scanf("%s", emp[i].name);

        printf("Employee ID: ");
        scanf("%ld", &emp[i].code);

        printf("Designation: ");
        scanf("%s", emp[i].designation);

        printf("Experience: ");
        scanf("%d", &emp[i].exp);

        printf("Age: ");
        scanf("%d", &emp[i].age);
        // add data to csv file
        addDataToCSV(emp[i]);
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
            break;
        }
    }
}

void showTable()
{
    printf("Employee Table\n");
    printf("%-20s%-20s%-20s%-20s%-20s\n", "Name", "Employee ID", "Designation", "Experience", "Age");
    printf("----------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < num; i++)
    {
        printf("%-20s%-20ld%-20s%-20d%-20d\n", emp[i].name, emp[i].code, emp[i].designation, emp[i].exp, emp[i].age);
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
        printf("%-20s(%d)\n", "Exit", 6);

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
            break;
        }
        else
        {
            printf("Expected Options are 1/2/3/4/5\n");
            showMenu();
        }
    } while (1);

    printf("Bye Bye\n");
}

int main()
{
    loadCSVData();
    showMenu();
    return 0;
}
