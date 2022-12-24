#include <iostream>

using namespace std;
/*
Какие результаты даст тест Миллера – Рабина для числа
185 по основанию 73 (помимо собственно вычислений, нужно
явно выписать получающуюся последовательность и указать,
как на ее основании делается вывод о результатах работы теста)?
*/

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
        cout << count << ") a = (" << z << "^2 * " << x << "^0) (mod " << N <<")" << " = " << (z * z) % N << endl;
        return (z * z) % N;
    }
    else {
        cout << count << ") a = (" << z << "^2 * " << x << "^1)(mod " << N <<")" << " = " << (x * z * z) % N << endl;
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
    cout << "a = 1" << endl;
    int count = 0;
    return mymodexp_print(x, y, N, count);
}

enum class Ans {
    PROBABLY_SIMPLE = 0,
    COMPOSITE
};

Ans TestMR(int n, int a) {
    int s = 0, t = n - 1;
    while (t % 2 == 0)
    {
        s++;
        t = t / 2;
    }

    int x = mymodexp(a, t, n);
    if (x == 1 || x == n - 1) return Ans::PROBABLY_SIMPLE;

    for (int i = 0; i < s - 1; i++) {
        x = mymodexp(x, 2, n);
        if (x == 1) return Ans::COMPOSITE;
        if (x == n - 1) return Ans::PROBABLY_SIMPLE;
    }

    return Ans::PROBABLY_SIMPLE;
}

int main(void) {
    int n = 137, a = 13;

    cout << "n = " << n << endl;
    cout << "a = " << a << endl;

    int t = 0, u = n - 1;
    while (u%2 == 0)
    {
        t++;
        u = u / 2;
    }
    cout << "n - 1 = 2^t * u" << endl
         << n - 1 << " = 2^" << t << " * " << u
         << " => t=" << t << " u=" << u << endl;

    cout << "a^u, a^2u , ... , a^(2^(t)u)" << endl;

    int *tu = new int[t + 1];
    int* atu = new int[t + 1];
    int temp = 1;
    for (int i = 0; i <= t; i++, temp *= 2) {
        cout << a << "^" << temp * u << ", ";
        tu[i] = temp * u;
    }
    cout << endl;

    modexp(a, n-1, n);

    cout << "final sequence: ";
    for (int i = 0; i <= t; i++) {
        atu[i] = mymodexp(a, tu[i], n);
        cout << atu[i] << ", ";
    }

    delete[] atu;
    delete[] tu;

    cout << endl << (TestMR(n, a) == Ans::COMPOSITE ? "COMPOSITE" : "PROBABLY_SIMPLE");

    return 0;
}