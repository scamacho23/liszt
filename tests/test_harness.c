#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "test_counter.h"
#include "thought_tests.h"
#include "note_tests.h"


#define THOUGHT_TESTS true
#define NOTE_TESTS true 
#define ARCHIVE_TESTS false

#define NUM_COMMENDATIONS 5
const char COMMENDATIONS[NUM_COMMENDATIONS][70] = {"Almost there!", "So close!", "You got this!", "Keep up the good work!",
			"Come on, Chief!"};


void run_thought_tests(test_counter_t *count) {
	// testing adding a thought
	printf("%sTest A-I: Adding a thought%s\n", BOLD, RESET);
	test_add_thought(count);	
	printf("\n");

	// testing listing thoughts
	printf("%sTest A-II: Listing thoughts%s\n", BOLD, RESET);
	test_listing_thoughts(count);
	printf("\n");

	// testing removing a thought
	printf("%sTest A-III: Removing thoughts%s\n", BOLD, RESET);
	test_removing_thoughts(count);
	printf("\n");
}

void run_note_tests(test_counter_t *count) {
	// testing adding a note
	printf("%sTest B-I: Adding a note%s\n", BOLD, RESET);
	test_add_note(count);	
	printf("\n");

/*
	// testing listing thoughts
	printf("%sTest A-II: Listing thoughts%s\n", BOLD, RESET);
	test_listing_thoughts(count);
	printf("\n");

	// testing removing a thought
	printf("%sTest A-III: Removing thoughts%s\n", BOLD, RESET);
	test_removing_thoughts(count);
	printf("\n");
*/
}

void run_archive_tests() {
	return;
}


int main(int argc, char *argv[]) {

	printf("Running tests on %sLiszt%s...\n\n", BOLD, RESET);
	printf("%sSECTIONS%s\n", BOLD, RESET);
	printf("Section A: thought functionality --> %s%s%s\n", BOLD, THOUGHT_TESTS ? "true" : "false" , RESET);
	printf("Section B: note functionality --> %s%s%s\n", BOLD, NOTE_TESTS ? "true" : "false" , RESET);
	printf("Section C: archive functionality --> %s%s%s\n", BOLD, ARCHIVE_TESTS ? "true" : "false" , RESET);
	printf("\n");

	test_counter_t count = {0, 0};

	if (THOUGHT_TESTS) {
		printf("%s––––––SECTION A–––––––%s\n", BOLD, RESET);
		run_thought_tests(&count);
		printf("\n");
	}
	if (NOTE_TESTS) {
		printf("%s––––––SECTION B–––––––%s\n", BOLD, RESET);
		run_note_tests(&count);
		printf("\n");
	}
	if (ARCHIVE_TESTS) {
		printf("%s––––––SECTION C–––––––%s\n", BOLD, RESET);
		run_archive_tests();
		printf("\n");
	}
	size_t num_passed = count.num_tests_passed;
	size_t total_num_tests = count.total_tests;
	if (num_passed == total_num_tests) {
		printf("Passed all %lu tests! Congratulations!\n", total_num_tests);
	} else {
		srand(time(NULL));
		size_t random_commendation = rand() % NUM_COMMENDATIONS;
		printf("Passed %lu out of %lu tests. %s\n", num_passed, total_num_tests, COMMENDATIONS[random_commendation]);
	}
	printf("Thanks for testing!\n");
	return 0;
}
