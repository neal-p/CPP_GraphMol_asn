// Chem 274B: Software Engineering Fundataions for
//            Molecular Sciences
// Creator: Dr.  Tony Drummond
// Date Created: 8/20/2022
// Last revisited: 8/15/2023
//
//  High resolution timing routines available on C++ 11 and
//  later versions.
//
//  mytimings.h contains the necessary include files and API
//  declarations to support our timing functions in C++

#pragma once  // Ensures that this file is only included once
              // during compilation

// List of include files:
// - chrono: system include file with the API to the C and C++ chrono
// high-resultion
//           timing functions
//
#ifndef STDLIB
#define STDLIB
#include <iostream>
using namespace std;
#endif
#include <chrono>
using namespace std::chrono;
#include <functional>

// API: Application Programming Interface to my timing functions
//      Only the function protypes are included here

// Function WTimeChrono:
//      INPUTS: Takes no inputs. This functions access the system's wall-clock
//      time OUTPUT: A high resultion snapshot of the system time. Returns a
//      structure
//              of type std::chrono::high_resolution_clock::time_point
//              with the current wall-clock time

high_resolution_clock::time_point WTimeChrono();

// Function WTElapse:
//   Computes the elapse Wall-clock time between start and endt (i.e.
//   startt-endt) INPUTS: startt : start wall-clock timestamp
//             endt : end wall-clock timestamp
//   OUTPUT: Elapse time in nanoseconds
long double WTElapsed(high_resolution_clock::time_point startt,
                      high_resolution_clock::time_point endt);

// WTElapseMicro: Elapse wall-clock time between start and endt in microseconds
//                (i.e. Elapsed = startt - endt). Similar to WTElapse but
//                µseconds
//   INPUTS: startt : start wall-clock timestamp
//             endt : end wall-clock timestamp
//   OUTPUT: Elapse time in microseconds
long double WTElapsedMicro(high_resolution_clock::time_point startt,
                           high_resolution_clock::time_point endt);

// time_function: Time the execution of a function
//   INPUTS: func: a function that takes no arguments
//           repeats: how many times to run the function (will return the
//           average execution time)
//   OUTPUT: Elapsed time in microseconds
float time_function(std::function<void()>, int repeats = 3);
