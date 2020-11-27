#ifndef THOUGHT_TESTS_H
#define THOUGHT_TESTS_H
/*
 * This file contains function declarations
 * for testing thought functionality of Liszt.
 * See thought_tests.c for the function definitions.
 */


/*
 * Tests adding a thought.
 */
void test_add_thought(test_counter_t *count);


/*
 * Tests listing thoughts.
 */
void test_listing_thoughts(test_counter_t *count);


/*
 * Tests removing thoughts.
 */
void test_removing_thoughts(test_counter_t *count);

#include "thought_tests.c"
#endif
