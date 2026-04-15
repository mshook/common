# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

A standalone C program that reads text from stdin and prints the top 22 most-frequent words with their occurrence counts. Classic K&R-style C, no external dependencies.

## Build and Run

```bash
# Compile
gcc -o common common.c

# Run (reads from stdin)
echo "the quick brown fox the quick" | ./common

# Output format: "count word" per line, sorted by descending frequency
```

## Architecture

Single file (`common.c`) implementing a word frequency counter:

- **Hash table** — 2048 buckets (`HASHSIZE = 07777` octal), each bucket is a linked list of `struct word { char *word; int count; struct word *next; }`
- **`getword`** — reads one alpha word at a time from stdin, skipping non-alpha chars
- **`addword`** — hashes by summing character values, does inline string comparison, applies **move-to-front heuristic** on hit (promotes the matched node to the head of its chain)
- **`printwords(k)`** — counting sort into a `list[]` array indexed by frequency, then walks descending to print top-k words; `k` is hardcoded to 22 in `main`

The `total` global tracks distinct word count; `list` in `printwords` is allocated with size `total+1` and indexed by `count`, so the sort is O(n) in the number of distinct words.
