#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>

#define MAX_WORD_LEN 100

typedef struct WordCount
{
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

WordCount *wordCounts = NULL;
int wordCountSize = 0;

void updateWordCount(const char *word)
{
    for (int i = 0; i < wordCountSize; i++)
    {
        if (strcmp(wordCounts[i].word, word) == 0)
        {
            wordCounts[i].count++;
            return;
        }
    }

    if (wordCountSize % 10 == 0)
    {
        wordCounts = (WordCount *)realloc(wordCounts, (wordCountSize + 10) * sizeof(WordCount));
    }
    strcpy(wordCounts[wordCountSize].word, word);
    wordCounts[wordCountSize].count = 1;
    wordCountSize++;
}
void processFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to open file: %s\n", filename);
        return;
    }

    char word[MAX_WORD_LEN];
    int wordLen = 0;
    int c;

    while ((c = fgetc(file)) != EOF)
    {
        if (isalpha(c) || c == '\'')
        {
            // Add the character to the current word
            if (wordLen < MAX_WORD_LEN - 1)
            {
                word[wordLen++] = c;
            }
        }
        else if (c == '-' && wordLen > 0)
        {
            // Check if the hyphen is followed by a letter
            int nextChar = fgetc(file);
            ungetc(nextChar, file); // Put the character back in the stream

            if (isalpha(nextChar))
            {
                // The hyphen is part of the word
                if (wordLen < MAX_WORD_LEN - 1)
                {
                    word[wordLen++] = c;
                }
            }
            else
            {
                // The hyphen is not part of the word
                word[wordLen] = '\0';
                updateWordCount(word);
                wordLen = 0;
            }
        }
        else
        {
            // The current character is not part of the word
            if (wordLen > 0)
            {
                // Null-terminate the word and update the word count
                word[wordLen] = '\0';
                updateWordCount(word);

                // Reset wordLen for the next word
                wordLen = 0;
            }
        }
    }

    // Check if the last word in the file
    if (wordLen > 0)
    {
        word[wordLen] = '\0';
        updateWordCount(word);
    }

    fclose(file);
}
void processDirectory(const char *dirname)
{
    DIR *dir = opendir(dirname);
    if (dir == NULL)
    {
        fprintf(stderr, "Unable to open directory: %s\n", dirname);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        {

            if (strlen(entry->d_name) >= 4 && strcmp(entry->d_name + strlen(entry->d_name) - 4, ".txt") == 0)
            {
                char fullpath[1024];
                snprintf(fullpath, sizeof(fullpath), "%s/%s", dirname, entry->d_name);
                processFile(fullpath);
            }
        }
        else if (entry->d_type == DT_DIR)
        {

            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                char fullpath[1024];
                snprintf(fullpath, sizeof(fullpath), "%s/%s", dirname, entry->d_name);
                processDirectory(fullpath);
            }
        }
    }

    closedir(dir);
}

int compareWordCounts(const void *a, const void *b)
{
    WordCount *wa = (WordCount *)a;
    WordCount *wb = (WordCount *)b;
    if (wa->count == wb->count)
    {
        return strcmp(wa->word, wb->word);
    }
    return wb->count - wa->count;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s [file or directory]...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        struct stat path_stat;
        if (stat(argv[i], &path_stat) == 0)
        {
            if (S_ISREG(path_stat.st_mode))
            {
                processFile(argv[i]);
            }
            else if (S_ISDIR(path_stat.st_mode))
            {
                processDirectory(argv[i]);
            }
        }
    }

    qsort(wordCounts, wordCountSize, sizeof(WordCount), compareWordCounts);
    for (int i = 0; i < wordCountSize; i++)
    {
        printf("%s %d\n", wordCounts[i].word, wordCounts[i].count);
    }

    free(wordCounts);

    return 0;
}
