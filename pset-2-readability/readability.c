#include <cs50.h>
#include <stdio.h>

#include <string.h>
#include <ctype.h>
#include <math.h>

//count functions
int count_letters(string s);
int count_words(string s);
int count_sentences(string s);

//simple average function - better conversion to double
double avg(int x, int y);

int main(void)
{
    //get input text
    string text = get_string("Text: ");

    //count and store
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    //enumerate average for L and S
    double avg_L = avg(letters, words);
    double avg_S = avg(sentences, words);

    //assign a grade
    double index = (0.0588 * avg_L) - (0.296 * avg_S) - 15.8;
    int grade = round(index);

    //output
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}

//letters
int count_letters(string s)
{
    int result = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (isalpha(s[i]))
        {
            result++;
        }
    }
    return result;
}

//words
int count_words(string s)
{
    int result = 1;
    char before = ' ';
    char after = ' ';
    for (int i = 0; i < strlen(s) - 1; i++)
    {
        after = s[i + 1];
        if (s[i] == ' ' && (isalpha(after) || isalpha(before)))
        {
            result++;
        }
        before = s[i];
    }
    return result;
}

//sentences
int count_sentences(string s)
{
    int result = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            result++;
        }
    }
    return result;
}

//average
double avg(int x, int y)
{
    double result = x * 100;
    result /= y;
    return result;
}