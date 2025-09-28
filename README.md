# CS 3503 Assignment 2: Data Representation and Mapping

## Author
Parsa Rajabi

## Description
This project, assigned by Owl Tech Industries' Systems Programming Division, extends a number base conversion utility with more advanced techniques. It implements functions for direct mapping between number systems (Octal, Binary, Hexadecimal) and for representing signed 32-bit integers using Sign-Magnitude, One's Complement, and Two's Complement formats. The solution reuses the testing framework architecture from the previous assignment to ensure correctness.

## What's New
Direct Mapping: Fast, bit-pattern-based conversion functions for `oct\_to\_bin`, `hex\_to\_bin`, and `oct\_to\_hex`.
Signed Representations: Implementation of `to\_sign\_magnitude`, `to\_ones\_complement`, and `to\_twos\_complement` to model how modern and historical CPUs store negative numbers.
Reusable Test Framework: The test harness from Assignment 1 was adapted to parse the new function names and input formats.


## Build Instructions
The project is built using `gcc`. The main program takes the test case file as a command-line argument.


```bash
# Compile the project
gcc -o convert convert.c main.c -std=c99 -Wall

# Run the tests and redirect output to a file
./convert a2\_test.txt > output.txt

