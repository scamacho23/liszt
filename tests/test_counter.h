#ifndef TEST_COUNTER_H
#define TEST_COUNTER_H
/* This file just contains the declaration
 * of the test_counter_t struct that is used
 * in several testing functions.
 */

// Also defining some color codes and the MAX_LINE_LEN
#define MAX_LINE_LEN 256
#define RED "\033[91m"
#define BLUE "\033[34m"
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define ITALICS "\033[3m"

// struct for keeping track of how many tests Liszt passed from each section
typedef struct {
	size_t num_tests_passed;
	size_t total_tests;
} test_counter_t;

#endif


