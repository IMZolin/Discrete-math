#include <bits/stdc++.h>

using namespace std;

// Node structure containing power and
// coefficient of variable
struct Node {
    float coeff;
    int pow;
    struct Node *next;
};

// Function to create new node
void create_node(float x, int y, struct Node **temp) {
    struct Node *r, *z;
    z = *temp;

// If temp is NULL
    if (z == NULL) {

        r = (struct Node *) malloc(
                sizeof(struct Node));

// Update coefficient and
// power in the LL z
        r->coeff = x;
        r->pow = y;
        *temp = r;
        r->next = (struct Node *) malloc(
                sizeof(struct Node));
        r = r->next;
        r->next = NULL;
    }

// Otherwise
    else {
        r->coeff = x;
        r->pow = y;
        r->next = (struct Node *) malloc(sizeof(struct Node));
        r = r->next;
        r->next = NULL;
    }
}

// Function to create a LL that stores
// the value of the quotient while
// performing polynomial division
void store_quotient(float mul_c, int diff,
                    struct Node *quo) {
// Till quo is non-empty
    while (quo->next != NULL) {
        quo = quo->next;
    }

// Update powers and coefficient
    quo->pow = diff;
    quo->coeff = mul_c;
    quo->next = (struct Node *) malloc(
            sizeof(struct Node));
    quo = quo->next;
    quo->next = NULL;
}

// Function to create a new polynomial
// whenever subtraction is performed
// in polynomial division
void formNewPoly(int diff, float mul_c,
                 struct Node *poly) {
// Till poly is not empty
    while (poly->next != NULL) {
        poly->pow += diff;
        poly->coeff *= mul_c;
        poly = poly->next;
    }
}

// Function to copy one polynomial
// into another linkedlist
void copyList(struct Node *r,
              struct Node **copy) {
// Copy the values of r in the
// polynomial copy
    while (r != NULL) {

        struct Node *z = (struct Node *) malloc(sizeof(struct Node));
// Store coefficient and power
        z->coeff = r->coeff;
        z->pow = r->pow;
        z->next = NULL;

        struct Node *dis = *copy;
        if (dis == NULL) {
            *copy = z;
        } else {
            while (dis->next != NULL) {
                dis = dis->next;
            }
            dis->next = z;
        }
        r = r->next;
    }
}

// Function to subtract two polynomial
void polySub(struct Node *poly1, struct Node *poly2, struct Node *poly) {
    // Compute until poly1 and poly2 is empty
    while (poly1->next && poly2->next) {
        // If power of 1st polynomial
// > 2nd, then store 1st as
// it is and move its pointer
        if (poly1->pow > poly2->pow) {

            poly->pow = poly1->pow;
            poly->coeff = poly1->coeff;
            poly1 = poly1->next;
            poly->next = (struct Node *) malloc(
                    sizeof(struct Node));
            poly = poly->next;
            poly->next = NULL;
        }

// If power of 2nd polynomial >
// 1st then store 2nd as it is
// and move its pointer
        else if (poly1->pow < poly2->pow) {
            poly->pow = poly2->pow;
            poly->coeff = -1 * poly2->coeff;
            poly2 = poly2->next;
            poly->next = (struct Node *) malloc(sizeof(struct Node));
            poly = poly->next;
            poly->next = NULL;
        }

// If power of both polynomial
// is same then subtract their
// coefficients
        else {
            if ((poly1->coeff - poly2->coeff) != 0) {
                poly->pow = poly1->pow;
                poly->coeff = (poly1->coeff - poly2->coeff);
                poly->next = (struct Node *) malloc(sizeof(struct Node));
                poly = poly->next;
                poly->next = NULL;
            }

// Update the pointers
// poly1 and poly2
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

// Add the remaining value of polynomials
    while (poly1->next || poly2->next) {

// If poly1 exists
        if (poly1->next) {
            poly->pow = poly1->pow;
            poly->coeff = poly1->coeff;
            poly1 = poly1->next;
        }

// If poly2 exists
        if (poly2->next) {
            poly->pow = poly2->pow;
            poly->coeff = -1 * poly2->coeff;
            poly2 = poly2->next;
        }

// Add the new node to poly
        poly->next = (struct Node *) malloc(sizeof(struct Node));
        poly = poly->next;
        poly->next = NULL;
    }
}

// Function to display linked list
void show(struct Node *node) {
    int count = 0;
    while (node->next != NULL && node->coeff != 0) {
// If count is non-zero, then
// print the positive value
        if (count == 0)
            cout << node->coeff;

// Otherwise
        else
            cout << abs(node->coeff);
        count++;
// Print polynomial power
        if (node->pow != 0)
            cout << "x^" << node->pow;
        node = node->next;

        if (node->next != NULL)
// If coeff of next term
// > 0 then next sign will
// be positive else negative
            if (node->coeff > 0)
                cout << " + ";
            else
                cout << " - ";
    }

    cout << "\n";
}

// Function to divide two polynomials
void divide_poly(struct Node *poly1,
                 struct Node *poly2) {
// Initialize Remainder and Quotient
    struct Node *rem = NULL, *quo = NULL;

    quo = (struct Node *) malloc(sizeof(struct Node));
    quo->next = NULL;

    struct Node *q = NULL, *r = NULL;

// Copy poly1, i.e., dividend to q
    copyList(poly1, &q);

// Copy poly, i.e., divisor to r
    copyList(poly2, &r);

// Perform polynomial subtraction till
// highest power of q > highest power of divisor
    while (q != NULL && (q->pow >= poly2->pow)) {
// difference of power
        int diff = q->pow - poly2->pow;

        float mul_c = (q->coeff
                       / poly2->coeff);

// Stores the quotient node
        store_quotient(mul_c, diff, quo);

        struct Node *q2 = NULL;

// Copy one LL in another LL
        copyList(r, &q2);
// formNewPoly forms next value
// of q after performing the
// polynomial subtraction
        formNewPoly(diff, mul_c, q2);
        struct Node *store = NULL;
        store = (struct Node *) malloc(sizeof(struct Node));

// Perform polynomial subtraction
        polySub(q, q2, store);

// Now change value of q to the
// subtracted value i.e., store
        q = store;
        free(q2);
    }

// Print the quotient
    cout << "Quotient: ";
    show(quo);

// Print the remainder
    cout << "Remainder: ";
    rem = q;
    show(rem);
}

// Driver Code
int main() {
    struct Node *poly1 = NULL;
    struct Node *poly2 = NULL, *poly = NULL;

// Create 1st Polynomial (Dividend):
// x^2022 - 1077x^500 - 15ч^13 -30
    create_node(1.0, 2023, &poly1);
    create_node(-1053.0, 502, &poly1);
    create_node(19.0, 22, &poly1);
    create_node(-58.0, 0, &poly1);

// Create 2nd Polynomial (Divisor):
// x^1 + 1
    create_node(1.0, 1, &poly2);
    create_node(1.0, 0, &poly2);

// Function Call
    divide_poly(poly1, poly2);

    return 0;
}
