#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    int id, type;
    union {
        float salary;
        struct {
            float rate;
            int hours;
        } contract;
    } pay;
} Employee;

float calculate(Employee e)
{
    if (e.type == 0)
        return e.pay.salary;
    return e.pay.contract.rate * e.pay.contract.hours;
}

void read(Employee *e, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("Enter name and ID: ");
        scanf("%19s %d", (e+i)->name, &(e+i)->id);

        printf("Type (0=Full-time, 1=Contract): ");
        scanf("%d", &(e+i)->type);

        if ((e+i)->type == 0) {
            printf("Enter salary: ");
            scanf("%f", &(e+i)->pay.salary);
        } else {
            printf("Enter rate and hours: ");
            scanf("%f %d",
                  &(e+i)->pay.contract.rate,
                  &(e+i)->pay.contract.hours);
        }
    }
}

int main(void)
{
    Employee *e;
    int n, i;
    float total = 0;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    if (n <= 0) return 1;

    e = malloc(n * sizeof(Employee));
    if (e == NULL) return 1;

    read(e, n);

    printf("\n--- Employee Payslips ---\n");

    for (i = 0; i < n; i++) {
        printf("\nName: %s\nID: %d\n",
               (e+i)->name, (e+i)->id);

        printf("Type: %s\n",
               (e+i)->type == 0 ? "Full-time" : "Contract");

        printf("Total pay: %.2f\n", calculate(*(e+i)));
        total += calculate(*(e+i));
    }

    printf("\nTotal salary bill: %.2f\n", total);

    free(e);
    return 0;
}