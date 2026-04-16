# CS214 Project Grades

## Assignment 1 - My Little Malloc

**Score:** `76/100`

- `README:` 20 points
- `memgrind:` 20 points
- `Autograder tests:` 36 points (6/10 tests passed)
- Note: Code was reported to have major bugs.

## Assignment 2 - Word Occurrence Count

**Score:** `82/100`

### README (20 points total)

- `[10]` Code compiles correctly without additional steps/corrections
- `[5]` README exists
- `[5]` README describes a testing strategy that shows some thought

### Word Count (20 points total)

- `[5]` Test 1: File containing 10 words, once each
- `[5]` Test 2: File containing 1 word ten times
- `[5]` Test 3: File containing two words three times, two words twice, and two words once
- `[5]` Test 4: All three files above (see `t4.out` for expected counts and word order)

### Tokenization (30 points total)

- `[0]` Exclusive use of `read()` (no `fgets()`, `fscanf()`, etc.)
- `[4]` Test 5: Regular words, including some punctuation
- `[4]` Test 6: Apostrophes and dashes
- `[0]` Test 7: Apostrophes combined with dashes
- `[0]` Test 8: A very long word
- `[4]` Test 9: A few small words repeated many times

### Directory (30 points total)

- `[6]` Test 10: `words bar`
- `[6]` Test 11: `words foo`
- `[6]` Test 12: `words foo bar`
- `[6]` Test 13: `words foo/baz`
- `[6]` Test 14: `words foo t5.txt t9.txt bar bar/ignore`

### Category Totals

- `README:` 20
- `Word Count:` 20
- `Tokenization:` 12
- `Directory:` 30
- `Total:` 82

## Assignment 3 - My Shell

**Score:** `75/100`

### Key Results

- `make` success: +10
- `README` quality: +10
- `execv()` call found: +2
- Bare words work: +3
- Pathnames work: +5
- `which` checks (`ls`, `cd`, non-existent command): +3
- `cd` and `pwd` check: +8
- Wildcard checks (multiple cases): +7
- Redirection tests: +4
- Redirect/pipe output of `pwd`: +1
- Interactive mode: +10

### Areas That Lost Points

- Conditional behavior (some true/false branch cases)
- Redirection tests 1-3
- Pipe test (`cat p1 | sort`)
- Tokenization-related cases
- No-crash checks for `cd`/`pwd` with pipes or redirections
