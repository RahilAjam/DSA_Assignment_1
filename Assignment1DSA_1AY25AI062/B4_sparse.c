#include <stdio.h>

#define MAX 100

typedef struct {
    int row, col, value;
} Term;

void display(Term a[])
{
    int i;

    printf("Row\tCol\tValue\n");
    for (i = 0; i <= a[0].value; i++)
        printf("%d\t%d\t%d\n",
               a[i].row, a[i].col, a[i].value);
}

void fastTranspose(Term a[], Term b[])
{
    int rowTerms[MAX] = {0};
    int startPos[MAX] = {0};
    int i, j, cols = a[0].col, n = a[0].value;

    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = n;

    for (i = 1; i <= n; i++)
        rowTerms[a[i].col]++;

    if (n == 0) return;

    startPos[0] = 1;
    for (i = 1; i < cols; i++)
        startPos[i] = startPos[i-1] + rowTerms[i-1];

    printf("row_terms: ");
    for (i = 0; i < cols; i++)
        printf("%d ", rowTerms[i]);

    printf("\nstarting_pos: ");
    for (i = 0; i < cols; i++)
        printf("%d ", startPos[i]);

    printf("\n");

    for (i = 1; i <= n; i++) {
        j = startPos[a[i].col]++;
        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;
    }
}

int main(void)
{
    Term a[MAX+1], b[MAX+1];
    int m[MAX][MAX];
    int rows, cols, i, j, k = 1;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    if (rows <= 0 || cols <= 0 ||
        rows > MAX || cols > MAX)
        return 1;

    printf("Enter matrix elements:\n");

    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            scanf("%d", &m[i][j]);

    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            if (m[i][j] != 0) {
                if (k > MAX) {
                    printf("Too many non-zero elements.\n");
                    return 1;
                }
                a[k].row = i;
                a[k].col = j;
                a[k].value = m[i][j];
                k++;
            }

    a[0].row = rows;
    a[0].col = cols;
    a[0].value = k - 1;

    printf("\nOriginal triples:\n");
    display(a);

    fastTranspose(a, b);

    printf("\nTransposed triples:\n");
    display(b);

    printf("Triples are in row-major order.\n");

    return 0;
}