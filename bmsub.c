/*
 *	Smart substring search, basing this off of the Boyer-Moore substring
 *	search. Found this from the Algos textbook fourth edition and I thought
 *	it was cool.
 */

/*	Author: Sebastian Fiorini */

#include <string.h>

#define ASCII_LEN 127
#define SEARCH_MISS -1

/*	Returns first index of substring found using BM Substring search */
static char *substring (char *pat, char *text) {
	int pat_len = strlen(pat);
	int text_len = strlen(text);
	
	int most_right[ASCII_LEN] = { SEARCH_MISS};

	for (int i = 0; i < pat_len; i++)
		most_right[(unsigned int)pat[i]] = i;

	int skip = 0;
	for (int i = pat_len - 1; i < text_len; skip) {
		if (right[text[i]] == SEARCH_MISS) {
			skip = pat_len;
		} else {
			// Search hit, move fwd right chars for the associated val
			int offset = pat_len - right[text[i]];
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
				return text[start_sub];
		}
	}
	
	return NULL;
}

int main (int argc, char ** args) {

}
