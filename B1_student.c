#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int roll_no;
    char name[20];
    float marks;
} Student;

Student *read(Student *p, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        printf("Enter roll, name, marks: ");
        scanf("%d %19s %f", &(p+i)->roll_no,
              (p+i)->name, &(p+i)->marks);
    }
    return p;
}

void display(Student *p, int n)
{
    int i, top = 0;
    float sum = 0;

    for (i = 0; i < n; i++) {
        sum += (p+i)->marks;
        if ((p+i)->marks > (p+top)->marks)
            top = i;
    }

    printf("Average marks: %.2f\n", sum/n);
    printf("Topper: %s (Roll %d, Marks %.2f)\n",
           (p+top)->name, (p+top)->roll_no,
           (p+top)->marks);
}

int main(void)
{
    int n, i, ch;
    Student *p, *temp;

    printf("Enter number of students: ");
    scanf("%d", &n);

    if (n <= 0) return 1;

    p = malloc(n * sizeof(Student));
    if (p == NULL) return 1;

    read(p, n);
    display(p, n);

    printf("Add 2 more students? (1 = Yes, 0 = No): ");
    scanf("%d", &ch);

    if (ch == 1) {
        temp = realloc(p, (n+2) * sizeof(Student));
        if (temp == NULL) {
            free(p);
            return 1;
        }

        p = temp;
        read(p+n, 2);
        n += 2;
        display(p, n);
    }

    free(p);
    return 0;
}