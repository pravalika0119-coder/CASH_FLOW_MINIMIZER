#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structure for storing expense details */
typedef struct Expense {
    char category[30];
    float amount;
    struct Expense* next;
} Expense;

/* Structure for storing user income and expenses */
typedef struct Person {
    char name[30];
    float income;
    Expense* expenses;
} Person;

/* Function to create a new expense */
Expense* createExpense(char* category, float amount) {
    Expense* newExpense = (Expense*)malloc(sizeof(Expense));
    strcpy(newExpense->category, category);
    newExpense->amount = amount;
    newExpense->next = NULL;
    return newExpense;
}

/* Function to add an expense to the person's expense list */
void addExpense(Person* person, char* category, float amount) {
    Expense* newExpense = createExpense(category, amount);
    newExpense->next = person->expenses;
    person->expenses = newExpense;
}

/* Function to display all expenses */
void displayExpenses(Person* person) {
    printf("Expenses for %s:\n", person->name);
    Expense* temp = person->expenses;

    while (temp != NULL) {
        printf(" - %s: %.2f\n", temp->category, temp->amount);
        temp = temp->next;
    }
}

/* Function to calculate total expenses */
float calculateTotalExpenses(Person* person) {
    float total = 0;
    Expense* temp = person->expenses;

    while (temp != NULL) {
        total += temp->amount;
        temp = temp->next;
    }

    return total;
}

/* Function to provide cash flow minimization strategies */
void suggestStrategies(Person* person) {
    float totalExpenses = calculateTotalExpenses(person);
    float savings = person->income - totalExpenses;

    printf("\nCash Flow Analysis for %s:\n", person->name);
    printf(" Total Income: %.2f\n", person->income);
    printf(" Total Expenses: %.2f\n", totalExpenses);
    printf(" Savings: %.2f\n", savings);

    printf("\nStrategies to Minimize Cash Flow:\n");

    if (savings < 0) {
        printf(" - You're spending more than your income. "
               "Consider cutting discretionary expenses.\n");
    } else if (savings < 0.2 * person->income) {
        printf(" - Your savings are below 20%% of your income. "
               "Limit unnecessary expenses.\n");
        printf(" - Focus on reducing expenses in categories like "
               "entertainment or dining out.\n");
    } else {
        printf(" - Your savings are in a healthy range. "
               "Continue monitoring and optimizing expenses.\n");
    }
}

/* Main function */
int main() {
    Person person;

    person.expenses = NULL;

    printf("Enter your name: ");
    scanf("%29s", person.name);

    printf("Enter your monthly income: ");
    scanf("%f", &person.income);

    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. View Cash Flow Analysis and Strategies\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char category[30];
                float amount;

                printf("Enter expense category (eg. Rent, food...): ");
                scanf("%29s", category);

                printf("Enter expense amount: ");
                scanf("%f", &amount);

                addExpense(&person, category, amount);
                break;
            }

            case 2:
                displayExpenses(&person);
                break;

            case 3:
                suggestStrategies(&person);
                break;

            case 4:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 4);

    
    Expense* current = person.expenses;
    while (current != NULL) {
        Expense* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
