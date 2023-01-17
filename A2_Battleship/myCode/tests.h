/*
 * tests.h
 *
 *  Created on: 7 Dec 2021
 *      Author: JASON
 */

#ifndef TESTS_H_
#define TESTS_H_
/*
 * Standard (system) header files.
 */
#include <iostream>
#include <stdlib.h>
using namespace std;
/*
 * More system header files.
 */
#include <string>
#include <set>
/*
 * Project header files.
 */
#include "Board.h"
#include "ConsoleView.h"
/**
 * Outputs the failedMessage on the console if condition is false.
 *
 * @param condition the condition
 * @param failedMessage the message
 */
void assertTrue(bool condition, string failedMessage);
/**
 * \brief Assertion tests for task 1 of the assignment.
 */
void part1tests ();
/**
 * \brief Assertion tests for task 2 of the assignment.
 */
void part2tests ();
/**
 * \brief Assertion tests for task 3 of the assignment.
 */
void part3tests ();

#endif /* TESTS_H_ */
