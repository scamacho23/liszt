#ifndef NOTE_TESTS_H
#define NOTE_TESTS_H
/*
 * This file contains function declarations
 * for testing note functionality of Liszt.
 * See note_tests.c for the function definitions.
 */


/*
 * Tests adding a note.
 */
void test_add_note(test_counter_t *count);


/*
 * Tests listing notes.
 */
void test_listing_notes(test_counter_t *count);


/*
 * Tests removing notes.
 */
void test_removing_notes(test_counter_t *count);

#include "note_tests.c"
#endif
