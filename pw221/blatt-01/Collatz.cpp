//  Copyright 2022
//  Collatz.cpp
//  Clang
//
//  Created by Paramie Willmann on 29.04.22.
//

#include <stdio.h>
#include <iostream>

int collatz(int n, int maxIterations, bool verbose) {
    int s_value = n;
    int count = 0;
    bool done = false;
    if (n == 0) {
        return 0;
    }
    // check if verbose is true
    if (verbose) {
        while (count < maxIterations) {
            printf("%d\n", n);
            if (n == 1) {
                done = true;
                printf("Number of iterations required: %d\n", count);
                break;
            } else {
                if (n % 2 == 0) {
                    n = n / 2;
                    count++;
                } else {
                    n = n * 3 + 1;
                    count++;
                }
            }
        }
    } else {
        // loop until n = 1 then return count as a result
        while (count < maxIterations) {
            if (n == 1) {
                done = true;
                break;
            } else {
                if (n % 2 == 0) {
                    n = n / 2;
                    count++;
                } else {
                    n = n * 3 + 1;
                    count++;
                }
            }
        }
    }
    // if (verbose == true) {
    //     printf("%d\n", s_value);
    //     printf("%d\n", n);
    //     if (done == true) {
    //         printf("%d\n", count);
    //     } else {
    //         printf("MaxIterations\n");
    //     }
    // }
    if (done == false) {
        return -1;
    }
    return 1;
}
