#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "note_tests.h"
#include "test_counter.h"

void test_add_note(test_counter_t *count) {
	char *expected = "Added new note 'random'\n";
	system("../lst -a random > test");

	FILE *fp = fopen("test", "r");
	char line[MAX_LINE_LEN];
	fgets(line, MAX_LINE_LEN * sizeof(char), fp);

	if (strcmp(expected, line)) {
		printf("%s%sERROR%s: %s\n", BOLD, RED, RESET, line);	
		printf("%sEXPECTED:%s %s\n", BOLD, RESET, expected);
	} else {
		printf("%s%sPASS%s: %s", BOLD, BLUE, RESET, expected);
		(count->num_tests_passed)++;
	}
	fclose(fp);
	(count->total_tests)++;
}

void test_listing_notes(test_counter_t *count) {
/*
	char expected[MAX_LINE_LEN];

	scandir

	fclose(fp);
	strcpy(expected, BOLD);
	strcat(expected, ITALICS);
	strcat(expected, "Found 1 memories on '");
	strcat(expected, line);
	strcat(expected, "'");
	strcat(expected, RESET);
	strcat(expected, "\n");
	strcat(expected, BOLD);
	strcat(expected, "1.");
	strcat(expected, RESET);
	strcat(expected, " trying to add a sentence with multiple words\n");
	system("../lst -l > test");
	fp = fopen("test", "r");
	char multi_lines[MAX_LINE_LEN * 2];
	strcpy(multi_lines, fgets(line, MAX_LINE_LEN * sizeof(char), fp));
	strcat(multi_lines, fgets(line, MAX_LINE_LEN * sizeof(char), fp));
	if (strcmp(expected, multi_lines)) {
		printf("%s%sERROR%s: %s\n", BOLD, RED, RESET, multi_lines);	
		printf("%sEXPECTED:%s %s\n", BOLD, RESET, expected);
	} else {
		printf("%s%sPASS%s: %s", BOLD, BLUE, RESET, expected);
		(count->num_tests_passed)++;
	}
	(count->total_tests)++;
	fclose(fp);
*/
}


/*
void test_removing_thoughts(test_counter_t *count) {
	char *expected = "Removed memory 'trying to add a sentence with multiple words'\n";
	char line[MAX_LINE_LEN];
	system("../lst -r 1 > test");

	FILE *fp = fopen("test", "r");
	fgets(line, MAX_LINE_LEN * sizeof(char), fp);

	if (strcmp(expected, line)) {
		printf("%s%sERROR%s: %s\n", BOLD, RED, RESET, line);	
		printf("%sEXPECTED:%s %s\n", BOLD, RESET, expected);
	} else {
		printf("%s%sPASS%s: %s", BOLD, BLUE, RESET, expected);
		(count->num_tests_passed)++;
	}
	fclose(fp);
	(count->total_tests)++;
}
*/
