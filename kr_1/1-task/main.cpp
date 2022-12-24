#include <iostream>
using namespace std;
void bitOut(int bits) {
    if (bits == 0) return;
    bitOut(bits / 2);
    cout << bits % 2;
}

int mymodexp_print(int x, int y, int N, int& count) {
    if (y == 0) {
        return 1;
    }
    int z = mymodexp_print(x, y / 2, N, count);
    count++;
    if (y % 2 == 0) {
        cout << count << ")" <<x <<"^" <<y<<"= (" << z << "^2 * " << x << "^0) (mod " << N <<")" << " = " << (z * z) % N << endl;
        return (z * z) % N;
    }
    else {
        cout << count << ")" <<x <<"^" <<y<<"= (" << z << "^2 * " << x << "^1)(mod " << N <<")" << " = " << (x * z * z) % N << endl;
        return (x * z * z) % N;
    }
}

int mymodexp(int x, int y, int N) {
    if (y == 0) {
        return 1;
    }
    int z = mymodexp(x, y / 2, N);
    if (y % 2 == 0) {
        return (z * z) % N;
    }
    else {
        return (x * z * z) % N;
    }
}

int modexp(int x, int y, int N) {
    cout << y << "_10 = ";
    bitOut(y);
    cout << "_2" << endl;
    int count = 0;
    return mymodexp_print(x, y, N, count);
}

int gcd(int a, int b) {
    cout << a <<" = " << b << " * " << a / b <<" + " << a % b<< endl;
    if (b == 0 || b == 1)
        return a;
    return gcd(b, a % b);
}
struct Ans{
    int gcd;
    int x;
    int y;
};

int extend_gcd(int a, int b, int* x, int* y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
        }

    int x1, y1; // To store results of recursive call
    int gcd = extend_gcd(b%a, a, &x1, &y1);

    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

int find_d(int p, int q, int e)
{
    cout << "a) " << endl;
    int phi_n = (p-1)*(q-1);
    cout << "phi_n = " << phi_n << endl;
    int x, y;
    gcd((p-1)*(q-1),e);
    extend_gcd(phi_n, e, &x, &y);
    if(y < 0)
        y += phi_n;
    cout << "d = " << y << endl;
    return y;
}
void encrypt(int m, int e, int n)
{
    cout << "b) " << endl;
    cout << "m = " << m << endl;
    cout << "P(m) = m^e(mod n)" << " = " << "P(" << m<< ") = " << m << "^"<<e << "(mod " << n<<")" << endl;
    modexp(m,e,n);
    cout << "P(m) = " << mymodexp(m,e, n)<< endl;
}
void decode(int m, int d, int n)
{
    cout << "c) " << endl;
    cout << "m = " << m << endl;
    cout << "S(m) = m^d(mod n)" << " = " << "S(" << m<< ") = " << m << "^"<<d << "(mod " << n<<")" << endl;
    modexp(m,d,n);
    cout << "S(m) = " << mymodexp(m,d, n);
}

int main() {
    int p = 17, q = 29, e = 9;
    cout << "p = " << p << ", ";
    cout << "q = " << q << ", ";
    cout << "e = " << e << endl;
    int n = p * q;
    cout << "n = p * q =  " << n << endl;

    //a)
    //cout << "gcd(a,b) = "<<"gcd("<< (p-1)*(q-1)<<" , "<< e<<") = " << gcd(120,20) << endl;
    int d = find_d(p,q,e);

    //b)
    int m = 23;
    encrypt(m, e, n);

    //c)
    m = 43;
    decode(m,d, n);
    return 0;
}
