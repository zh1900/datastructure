#!/bin/bash
gcc -ansi main_test.c -o main_test
cp main_test ../../test_data/random/main_test
cp main_test ../../test_data/special/main_test
cp main_test ../../test_data/complete/main_test
