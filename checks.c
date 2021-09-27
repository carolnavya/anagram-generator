#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define True 1
#define False 0
#define MAXSIZE 128
#define DICTSIZE 53000
#define MAXWORDS 50
char s[45];
// Function Prototypes
unsigned int CheckFile(const char *inp, const char *out, const char *dicitonary_file);
int LoadFile(const char *fname, size_t max_words, char *word_list[max_words]);
void FreeFile(size_t word_count, char *word_list[word_count]);
int valid(const char *word, size_t max_words, char *dictionary[max_words]);

int main(){
printf("please enter the word again\n");
scanf("%s",s);
    const char *in_name = "permutation.txt";
    const char *dict_name = "dictionary.txt";
    const char *out_name = "words.txt";
    unsigned num_words = CheckFile(in_name, out_name, dict_name);
    char *valid_words[MAXWORDS] = {0};
    size_t word_size = LoadFile(out_name, MAXWORDS, valid_words);

    int i;
    for (i=0; i<word_size; i++)
    {
        printf("Word: %s\n",valid_words[i]);
    }
    printf("Number of Valid Words: %d\n", word_size);

    int test;
    const char *rand_word = s;
    test = valid(rand_word, word_size, valid_words);
    if (test)
    {
        printf("Valid Word\n");
    }
    else
    {
        printf("Invalid Word\n");
    }
    return 0;
}

//Function: CheckFile
// Description: Inputs the location for input file and dictionary file and write the intersection of contents into output file

unsigned int CheckFile(const char *inp, const char *out, const char *dict)
{
    /*Load the dicitonary*/
    char *dictionary[DICTSIZE] = {0};
    size_t dictionary_size = LoadFile(dict, DICTSIZE, dictionary);
    int i;
    int num_words = 0;
    char *ptr_item;

    FILE *input = fopen(inp, "r");
    FILE *output = fopen(out, "w");

    if (input)
    {
        char fmt[64], word[MAXSIZE];
        sprintf(fmt, " %%%ds", MAXSIZE-1);
        while (fscanf(input, fmt, word) == 1)
        {
            for (i=0; i<dictionary_size; i++)
            {
                if (strcmp(word, dictionary[i]) == 0)
                {
                    num_words++;
                    fprintf(output, "%s\n", word);
                }
            }
        }
    }
    else
    {
        printf("Error input file %s not found", inp);
    }
    fclose(input);
    fclose(output);
    FreeFile(dictionary_size, dictionary);

    return num_words;
}


//Function: LoadFile
 //Description: Loads contents of text file into memory
int LoadFile(const char* fname, size_t max_words, char *word_list[max_words])
{
    int count = 0;
    memset(word_list, 0, sizeof(*word_list)*max_words);
    FILE *fp = fopen(fname, "r");

    if (fp)
    {
        char fmt[64], word[MAXSIZE];
        sprintf(fmt, " %%%ds", MAXSIZE-1);
        while (fscanf(fp, fmt, word) == 1 && count < max_words)
        {
            word_list[count] = malloc(strlen(word)+1);
            strcpy(word_list[count++], word);
        }
        fclose(fp);
    }
    return count;
}


//Function: FreeFile
//Descriptions: Release word list that was loaded from LoadFile
void FreeFile(size_t word_count, char *word_list[word_count])
{
    size_t i;
    for (i=0; i<word_count; free(word_list[i]), word_list[i++]=0);
}

//Function: valid
//Description: Checks if the word is valid against a dictionary

int valid(const char *word, size_t max_words, char *dictionary[max_words])
{
    int i;
    for (i=0; i<max_words; i++)
    {
        if (strcmp(word, dictionary[i]) == 0)
        {
            printf("Dictionary: %s\n", dictionary[i]);
            printf("Word: %s\n", word);
            return True;
        }
    }
    return False;
}
