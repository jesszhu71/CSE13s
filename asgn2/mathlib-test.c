//Jessie
//Spring 2021

#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "asctl" //5 input options

//I followed Eugene's tutoral on how use getopt
int main(int argc, char **argv) {
    int opt = 0;
    //s, c, t, l are flags to keep track of which tests need to be run
    bool s = false;
    bool c = false;
    bool t = false;
    bool l = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) { // evaluated each part of the input
        switch (opt) {
        case 'a':
            //all four tests need to be run
            s = true;
            c = true;
            t = true;
            l = true;
            break;
        case 's':
            //arcsin test needs to be run
            s = true;
            break;
        case 'c':
            //arccos test needs to be run
            c = true;
            break;
        case 't':
            //arctan test needs to be run
            t = true;
            break;
        case 'l':
            // log test needs to be run
            l = true;
            break;
        }
    }
    //Either no input was given or wrong input
    //Prints all input optins and how to run the test
    if (s == false && c == false && t == false && l == false) {
        printf("Program usage: ./asgn2_mathlib-test -[asctl]\n");
        printf("  -a   Runs all tests (arcsin, arccos, arctan, log)\n");
        printf("  -s   Runs arcsin tests\n");
        printf("  -c   Runs arccos tests\n");
        printf("  -t   Runs arctan tests\n");
        printf("  -l   Runs log tests\n");

        return 1; // error input
    }

    //arcSin test, my function vs library function
    if (s == true) {
        printf("  x            arcSin           Library        Difference\n");
        printf("  -            ------           -------        ----------\n");
        for (double i = -1.0; i <= 1.0; i = i + .1) {
            printf(
                " %7.4lf %16.8lf %16.8lf %16.10lf\n", i, arcSin(i), asin(i), arcSin(i) - asin(i));
        }
    }

    //arcCos test, my function vs library function
    if (c == true) {
        printf("  x            arcCos           Library        Difference\n");
        printf("  -            ------           -------        ----------\n");
        for (double i = -1.0; i <= 1.0; i = i + .1) {
            printf(
                " %7.4lf %16.8lf %16.8lf %16.10lf\n", i, arcCos(i), acos(i), arcCos(i) - acos(i));
        }
    }

    //arcTan test, my function vs library function
    if (t == true) {
        printf("  x            arcTan           Library        Difference\n");
        printf("  -            ------           -------        ----------\n");
        for (double i = 1.0; i <= 10; i = i + .1) {
            printf(
                " %7.4lf %16.8lf %16.8lf %16.10lf\n", i, arcTan(i), atan(i), arcTan(i) - atan(i));
        }
    }

    //Log test, my function vs library function
    if (l == true) {
        printf("  x            log              Library        Difference\n");
        printf("  -            ------           -------        ----------\n");
        for (double i = 1.0; i <= 10; i = i + .1) {
            printf(" %7.4lf %16.8lf %16.8lf %16.10lf\n", i, Log(i), log(i), Log(i) - log(i));
        }
    }
    return 0;
}
