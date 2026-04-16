# Word Occurrence Count

Partners:
1. Zeel Patel - Net ID: zap19
2. Shreya Vyas - Net ID: sv693

**Project 2**

**Note:** This code does not work for `’`, but it works for `'`.

## Functions

updateWordCount(const char *word)
  This function updates the word count for a given word. It iterates through the existing wordCounts array and increments the count if the word is already
  present. If the word is not found, it dynamically reallocates memory for wordCounts and adds the new word.

processFile(const char *filename)
  This function processes a given file, extracting words and updating their counts using the updateWordCount function. It handles hyphenated words and ignores
  non-alphabetic characters.

processDirectory(const char *dirname)
  This function processes all files within a specified directory. It recursively calls itself for subdirectories and invokes processFile for each text file in 
  the directory.

compareWordCounts(const void *a, const void *b)
  This function is used as a comparison function for qsort to sort the WordCount array in descending order of word frequency. If two words have the same 
  frequency, they are sorted in lexicographical order.

main(int argc, char *argv[])
  The main function serves as the entry point of the program. It parses command-line arguments, identifies whether the input is a file or directory, and then
  processes the input accordingly. After processing, it sorts and prints the word counts.




## Usage

To compile the `words` program, use the provided Makefile:

```bash
make -f Makefile
```

or

```bash
make
```

This will create an executable named `words`.

To run the `words` program, use the following syntax:

```bash
./words [file or directory]...
```

You can specify one or more files and directories as arguments, and the program will process them accordingly.

## Example

Here's an example of how to use the `words` program:

```bash
./words file1.txt directory1
```

**Note:** Replace `file1.txt` and `directory1` with the names of the text files and directories you want to process.

```bash
words.exe input.txt 
```

```bash
words.exe' input.txt TestFolder
```
