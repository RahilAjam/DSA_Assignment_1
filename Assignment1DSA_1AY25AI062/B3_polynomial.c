#include <stdio.h>

typedef struct {
    int degree;
    float coef[101];
} Polynomial;

Polynomial add(Polynomial a, Polynomial b)
{
    Polynomial c;
    int i, j, k;

    c.degree = a.degree > b.degree ?
               a.degree : b.degree;

    for (i = 0; i <= c.degree; i++) {
        j = c.degree - i;
        c.coef[i] = 0;

        if (j <= a.degree)
            c.coef[i] += a.coef[a.degree-j];

        if (j <= b.degree)
            c.coef[i] += b.coef[b.degree-j];
    }

    return c;
}

void read(Polynomial *p)
{
    int i;

    printf("Enter degree: ");
    scanf("%d", &p->degree);

    for (i = 0; i <= p->degree; i++)
        scanf("%f", &p->coef[i]);
}

void display(Polynomial p)
{
    int i, exp, first = 1;
    float c;

    for (i = 0; i <= p.degree; i++) {
        exp = p.degree - i;
        c = p.coef[i];

        if (c == 0) continue;

        if (!first)
            printf(c > 0 ? " + " : " - ");
        else if (c < 0)
            printf("-");

        if (exp == 0 || (c != 1 && c != -1))
            printf("%g", c < 0 ? -c : c);

        if (exp > 0) {
            printf("x");
            if (exp > 1) printf("^%d", exp);
        }

        first = 0;
    }

    if (first) printf("0");
    printf("\n");
}

int main(void)
{
    Polynomial a, b, c;

    printf("Polynomial A: ");
    read(&a);

    printf("Polynomial B: ");
    read(&b);

    c = add(a, b);

    printf("A(x) = ");
    display(a);
    printf("B(x) = ");
    display(b);
    printf("Sum = ");
    display(c);

    return 0;
}