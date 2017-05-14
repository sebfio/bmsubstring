/*
 *	Smart substring search, basing this off of the Boyer-Moore substring
 *	search. Found this from the Algos textbook fourth edition and I thought
 *	it was cool.
 */

/*	Author: Sebastian Fiorini */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define ASCII_LEN 127
#define SEARCH_MISS -1

/*	Returns first index of substring found using BM Substring search */
static char *substring (char *pat, char *text) {
	int pat_len = strlen(pat);
	int text_len = strlen(text);
	
	int most_right[ASCII_LEN];
	for (int i = 0; i < ASCII_LEN; i++)
		most_right[i] = -1;

	for (int i = 0; i < pat_len; i++)
		most_right[(unsigned int)pat[i]] = i;

	int skip = 0;
	for (int i = pat_len - 1; i < text_len; i += skip) {
		if (most_right[text[i]] == SEARCH_MISS) {
			skip = pat_len;
		} else {
			// Search hit, move fwd right chars for the associated val
			int offset = pat_len - most_right[text[i]];
			int curr_sub = i + offset - 1;
			int start_sub = i - offset;
			for (; curr_sub >= start_sub; curr_sub--) {
				if (text[curr_sub] == pat[curr_sub - i]) {
					continue;
				} else {
					// Not a hit
					skip += offset + pat_len;
					break;
				}
			}
			if (curr_sub <= start_sub)
				return &(text[start_sub]);
		}
	}
	
	return NULL;
}

int main (int argc, char ** argv) {
	if (argc == 3) {
		char *sub = substring(argv[1], argv[2]);
		if (sub)
			printf("%s", sub);
	}
	return 0;
}
