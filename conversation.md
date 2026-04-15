# Conversation Log

---

**User:** /init

**Assistant:** Analyzed the codebase and created `CLAUDE.md` with build instructions and architectural summary covering the hash table design, move-to-front heuristic, and counting-sort output strategy.

`CLAUDE.md` contents:

```
# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

A standalone C program that reads text from stdin and prints the top 22 most-frequent words with their occurrence counts. Classic K&R-style C, no external dependencies.

## Build and Run

    # Compile
    gcc -o common common.c

    # Run (reads from stdin)
    echo "the quick brown fox the quick" | ./common

    # Output format: "count word" per line, sorted by descending frequency

## Architecture

Single file (`common.c`) implementing a word frequency counter:

- **Hash table** — 2048 buckets (`HASHSIZE = 07777` octal), each bucket is a linked list of `struct word { char *word; int count; struct word *next; }`
- **`getword`** — reads one alpha word at a time from stdin, skipping non-alpha chars
- **`addword`** — hashes by summing character values, does inline string comparison, applies **move-to-front heuristic** on hit (promotes the matched node to the head of its chain)
- **`printwords(k)`** — counting sort into a `list[]` array indexed by frequency, then walks descending to print top-k words; `k` is hardcoded to 22 in `main`

The `total` global tracks distinct word count; `list` in `printwords` is allocated with size `total+1` and indexed by `count`, so the sort is O(n) in the number of distinct words.
```

---

**User:** compile and run it, fixing errors if you find them

**Assistant:** Compiled with `gcc -o common common.c` and got warnings (no errors):

- `calloc` conflicting types — missing `#include <stdlib.h>`
- `exit` implicit declaration — missing `#include <stdlib.h>`
- `strcpy` implicit declaration — missing `#include <string.h>`

Fixes applied to `common.c`:
1. Added `#include <stdlib.h>` and `#include <string.h>`
2. Removed K&R-style forward declaration `*calloc()` from `alloc()`

Recompiled cleanly (`-Wall` shows only a harmless assignment-in-condition warning in `printwords`, idiomatic K&R style). Test run:

```
$ echo "the quick brown fox jumps over the lazy dog the quick brown fox the" | ./common
4 the
2 brown
2 quick
2 fox
1 jumps
1 lazy
1 over
1 dog
```

---

**User:** write the whole conversation into a file

**Assistant:** Wrote this conversation to `conversation.md`.
