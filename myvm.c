#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
double prtop(void);
void swap(void);
void clear(void);

int main()
{
    int type, top;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) {
                    push(pop() / op2);
                } else {
                    printf("error: zero divisor\n");
                }
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0) {
                    push((int)pop() % (int)op2);
                } else {
                    printf("error: zero divisor for modulus\n");
                }
                break;
            case 'p':
                top = prtop();
                printf("top element: %d\n", top);
                break;
            case 's':
                swap();
                printf("1st and 2nd elements are swapped, now 1st is:%.8g\n", prtop());
                break;
            case 'c':
                clear();
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;

        }
    }
    return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

double pop(void)
{
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

double prtop(void)
{
    int t;
    if (sp > 0) {
        t = sp - 1;
        return val[t];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void swap(void)
{
    int t1, t2;
    if (sp > 1) {
        t1 = val[sp-1];
        t2 = val[sp-2];
        val[sp-1] = t2;
        val[sp-2] = t1;
    } else {
        printf("error: stack doesn't have enough elements to swap\n");
    }
}

void clear(void)
{
    if (sp == 0) {
        printf("error: stack already empty\n");
        return;
    }
    for (--sp; sp > 0; pop()) {
    }
}

#include <ctype.h>
int getch(void);
void ungetch(int);

/*getop: get next operator or numeric operand*/
int getop(char s[])
{
    int i, c;
    int d;

    while ((s[0] = c = getch()) == ' ' || c == '\t' ) {
    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-') {
        return c; /*not a number*/
    }

    i = 0;
    // for minus operator
    if (c == '-') {
        if (isdigit(d = getch())) {
            s[++i] = c = d;
        } else {
            ungetch(d);
            return c;
        }
    }

    /*for positive number*/
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch())) {
        }
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = getch())) {
        }
    }
    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }
    return NUMBER;
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many character\n");
    } else {
        buf[bufp++] = c;
    }

}
