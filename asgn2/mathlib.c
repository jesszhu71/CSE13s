//Jessie Zhu
//Spring 2021

#include "mathlib.h"

#include <inttypes.h>
#include <math.h>
#include <stdio.h>

#define EPSILON 0.0000000001

// Absolute value of x
double Abs(double x) {
    if (x > 0) { //if x is positive, nothing changes
        return x;
    }
    //x is negative, return -1*x
    return -x;
}

// e^x function, used for Log function (from Piazza post @69 exp.c)
double Exp(double x) {
    double term = 1, sum = 1;
    for (int k = 1; Abs(term) > EPSILON; k += 1) { //adds terms until |term| is less than EPSILON
        term *= x / k; //term term
        sum += term; //term to be added into estimate sum
    }
    return sum;
}

// Square root function (from Piazza post @143 sqrt.c)
double Sqrt(double x) {
    double y = 1.0;
    for (double guess = 0.0; Abs(y - guess) > EPSILON; y = (y + x / y) / 2.0) {
        guess = y;
    }
    return y;
}

//arcSin Function
//I built this using your sin function example on lecture 9 slides as the structure
//and altered it to work for the arcSin taylor series.
double arcSin(double x) {
    // estimate is inaccurate near |x| = 1, this handles that by using inverse trig angle identities
    if (x > 0.75) {
        // 0 <= x <= 1 : arcsin(x) = arccos(sqrt(1-x^2))
        return arcCos(Sqrt(1 - x * x));
    } else if (x < -.75) {
        // -1 <= x <= 0 : arcsin(x) = -arccos(sqrt(1-x^2))
        return -1 * arcCos(Sqrt(1 - x * x));
    }

    //estimate arcSin using taylor series
    double sum = x;
    double numerator = x;
    double denominator = 1;
    double exponent = 3;
    while (Abs(numerator / denominator) > EPSILON) {
        // keeps adding new terms to taylor series sum until the newest term<EPSILON
        numerator = numerator * (exponent - 2) * (exponent - 2) * x * x; //new term's numerator
        denominator = denominator * exponent * (exponent - 1); // new terms's denominator
        sum = sum + (numerator / denominator); // add new term to current sum
        exponent = exponent + 2; // increment next term's exponent value
    }
    return sum;
}

//arcCos Function
// Uses arcSin function above by utilizing inverse trig angle identities
double arcCos(double x) {
    //estimate is inaccurate near |x| = 1, this handles that by using inverse trig angle identities
    if (x > .75) {
        // 0 <= x <= 1 : arccos(x) = arcsin(sqrt(1-x^2))
        return arcSin(Sqrt(1 - x * x));
    } else if (x < -.75) {
        // -1 <= x <= 0 : arccos(x) = pi - arcsin(sqrt(1-x^2))
        return M_PI - arcSin(Sqrt(1 - x * x));
    }
    return (M_PI / 2) - arcSin(x); // inverse trig identity: arccos(x) = pi/2 - arcsin(x)
}

//arcTan Function
// Uses arcsin function above by utilizing inverse trig angle identities
double arcTan(double x) {
    return arcSin(x / Sqrt(x * x + 1)); // inverse trig identity: arctan(x) = arcsin(x/(x^2+1))
}
//log Function
// This was given to us in a lecture slide 9, variable names altered to match variable name schemes
double Log(double x) {
    double guess = 1.0; // initial guess
    double exp_guess = Exp(guess); // e^guess
    while (Abs(x - exp_guess) > EPSILON) {
        //keeps adding to our guess value until e^guess is close enough to x
        guess = guess + ((x - exp_guess) / exp_guess); // new guess
        exp_guess = Exp(guess); // new guess's e^guess
    }
    return guess;
}
