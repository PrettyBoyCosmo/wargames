// aoc_2024_day2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool checkSafe_with_skip(const int *a, int n, int skip_idx) {
    // skip_idx = -1 means "no skip"
    int i = 0;
    // find first kept element
    while (i < n && i == skip_idx) i++;
    if (i >= n) return false; // nothing left

    int prev = a[i++];
    while (i < n && i == skip_idx) i++;

    bool ascending = true;
    bool descending = true;

    for (; i < n; i++) {
        if (i == skip_idx) continue;
        int cur = a[i];
        int d = cur - prev;
        int ad = d < 0 ? -d : d;
        if (ad > 3 || ad < 1) return false;
        if (prev > cur) ascending = false;
        if (prev < cur) descending = false;
        prev = cur;
    }
    return ascending || descending;
}

int main(void) {
    const size_t MAX_LINE = 4096;
    char line[4096];

    long long safe_count = 0;
    long long safe_count_2 = 0;

    while (fgets(line, (int)MAX_LINE, stdin)) {
        // Trim trailing newline
        size_t len = strlen(line);
        if (len && (line[len - 1] == '\n' || line[len - 1] == '\r'))
            line[len - 1] = '\0';

        // Tokenize by spaces; collect integers for the row
        int vals[1024];
        int m = 0;

        char *tok = strtok(line, " ");
        while (tok) {
            if (*tok != '\0') {
                vals[m++] = atoi(tok);
            }
            tok = strtok(NULL, " ");
        }
        if (m == 0) continue;

        if (checkSafe_with_skip(vals, m, -1)) {
            safe_count++;
        }

        // Part 2: can we remove one element to make it safe?
        bool ok = false;
        for (int i = 0; i < m; i++) {
            if (checkSafe_with_skip(vals, m, i)) {
                ok = true;
                break;
            }
        }
        if (ok) safe_count_2++;
    }

    printf("%lld\n", safe_count);
    printf("%lld\n", safe_count_2);
    return 0;
}

