#include <iostream>
#include <cmath>
#include "../headers/TrigPoly.h"
using namespace std;

TrigPoly::TrigPoly(size_t x, double angle) {
    n = x;
    alpha = angle;
    a = new double[x];
    b = new double[x];

}

TrigPoly::TrigPoly() {
    
}

TrigPoly::~TrigPoly() {
    n = 0;
    alpha = 0;
    delete [] a;
    delete [] b;
}

int input_TrigPoly(TrigPoly* x) {
    int numFails = -2;
    x = new TrigPoly();
    size_t n = 0;
    do {
        cout << "Enter polynomial degree: ";
        cin >> n;
        numFails++;
    } while (cin.fail());

    double angle = 0;
    do {
        cout << "Enter angle: ";
        cin >> angle;
        numFails++;
    }
    while(cin.fail());

    x->alpha = angle;

    x-> n = n;

    x->a = new double[n];
    x->b = new double[n];

    for (int i = 0; i < n; i++) {
        int aTemp = 0;
        cout << "Enter a: ";
        cin >> aTemp;
        if (cin.fail()) {
            numFails++;
            i--;
            continue;
        }

        int bTemp = 0;
        cout << "Enter b: ";
        cin >> bTemp;
        if (cin.fail()) {
            numFails++;
            i--;
            continue;
        }

        x->a[i] = aTemp;
        x->b[i] = bTemp;

    }
    return numFails;
}

void output_TrigPoly(TrigPoly x) {
    cout << x.alpha;
    for (int i = 0; i < x.n; i++) {
        cout << " + " << x.a[i] << "sin(" << i + 1 << "x) + " << x.b[i] << "cos(" << i + 1 << "x)";
    }
}

TrigPoly generate_TrigPoly(int a) {
    TrigPoly temp;
    temp.n = a;
    temp.alpha = (rand() % 25) + 1;
    temp.a = new double [a];
    temp.b = new double [a];

    for (int i = 0; i < temp.n; i++) {
        temp.a[i] = (double)(rand() % 10) + 1;
        temp.b[i] = (double)(rand() % 10) + 1;
    }
    return temp;
}

double value_x(TrigPoly p, Dtype x){
    double result = p.alpha;
    for (int i = 0; i < p.n; i++) {
        result += sin(p.a[i])*(i+1);
        result += cos(p.b[i])*(i+1);
    }
    return result;
}

TrigPoly add_TrigPoly(TrigPoly x, TrigPoly y) {
    TrigPoly temp;
    if (x.n < y.n) {
        temp.n = y.n;
    }
    else {
        temp.n = x.n;
    }

    temp.alpha = x.alpha + y.alpha;
    temp.a = new double [temp.n];
    temp.b = new double [temp.n];

    for (int i = 0; i < x.n; i++) {
        temp.a[i] = x.a[i];
        temp.b[i] = x.b[i];
    }
    for (int i = 0; i < y.n; i++) {
        temp.a[i] += y.a[i];
        temp.b[i] += y.b[i];
    }
    return temp;
}

TrigPoly sub_TrigPoly(TrigPoly x, TrigPoly y) {
    TrigPoly temp;
    if (x.n < y.n) {
        temp.n = y.n;
    }
    else {
        temp.n = x.n;
    }

    temp.alpha = x.alpha - y.alpha;
    temp.a = new double [temp.n];
    temp.b = new double [temp.n];

    for (int i = 0; i < x.n; i++) {
        temp.a[i] -= x.a[i];
        temp.b[i] -= x.b[i];
    }
    for (int i = 0; i < y.n; i++) {
        temp.a[i] -= y.a[i];
        temp.b[i] -= y.b[i];
    }
    return temp;
}

TrigPoly mul_TrigPoly(TrigPoly x, TrigPoly y) {
    TrigPoly temp;
    temp.n = x.n + y.n;
    temp.alpha = x.alpha * y.alpha;
    temp.a = new double [temp.n];
    temp.b = new double [temp.n];

    for (int i = 0; i < temp.n; i++) {
        temp.a[i] = 0;
        temp.b[i] = 0;
    }
    for (int i = 0; i < x.n; i++) {
        for (int j = 0; j < y.n; j++) {
            temp.a[i + j] += x.a[i] * y.a[j];
            temp.a[i + j] += x.a[i] * y.a[j];
        }
    }
    return temp;
}

TrigPoly derivative(TrigPoly p){
    TrigPoly temp;
    temp.n = p.n;
    temp.alpha = p.alpha;
    temp.a = new double [p.n];
    temp.b = new double [p.n];

    for (int i = 0; i < p.n; i++) {
        temp.a[i] = p.b[i]*(i+1);
        temp.b[i] = -p.a[i]*(i+1);
    }
    return temp;
}

TrigPoly integral(TrigPoly p, Dtype C) {
    TrigPoly temp;
    temp.n = p.n;
    temp.alpha = p.alpha + C;
    temp.a = new double [p.n];
    temp.b = new double [p.n];

    for (int i = 0; i < p.n; i++) {
        temp.a[i] = p.b[i]/(temp.n + 1);
        temp.b[i] = -p.a[i]/(temp.n + 1);
    }
    return temp;
}

Dtype integrate(TrigPoly p, Dtype a, Dtype b) {
    Dtype upperRes, lowerRes, finalRes;
    TrigPoly temp;
    temp.n = p.n;
    temp.alpha = p.alpha;

    for (int i = 0; i < p.n; i++) {
        temp.a[i] = p.b[i]/(temp.n + 1);
        temp.b[i] = -p.a[i]/(temp.n + 1);
    }

    upperRes = a*temp.alpha;
    lowerRes = b*temp.alpha;
    for (int i = 0; i < temp.n; i++) {
        upperRes += temp.a[i]*sin((temp.n + 1) * a);
        upperRes += temp.b[i]*cos((temp.n + 1) * a);
        lowerRes += temp.a[i]*sin((temp.n + 1) * b);
        lowerRes += temp.a[i]*cos((temp.n + 1) * b);
    }
    finalRes = upperRes - lowerRes;
    return finalRes;
}