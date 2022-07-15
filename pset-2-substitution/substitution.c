#include <cs50.h>
#include <stdio.h>

#include <string.h>
#include <ctype.h>

string to_lower(string text);

bool valid_recurrence(string key);
bool valid_alpha(string key);

string make_cipher(string key, string plain);

int main(int argc, string argv[])
{
    //checking input number of arguments
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    //checking length of the key: 26
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //checking if alphabetical
    if (!valid_alpha(key))
    {
        printf("Key must contain only alphabetical letters.\n");
        return 1;
    }

    //checking if key contains only one of each letters
    if (!valid_recurrence(key))
    {
        printf("Key must contain each letter exactly once.\n");
        return 1;
    }

    //getting user input
    string plain = get_string("plaintext: ");

    string cipher = make_cipher(key, plain);

    printf("ciphertext: %s\n", cipher);

    return 0;
}

string to_lower(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (isupper(text[i]))
        {
            text[i] += 32;
        }
    }
    return text;
}

bool valid_recurrence(string key)
{
    key = to_lower(key);
    for (int i = 1; i < strlen(key); i++)
    {
        for (int j = i-1; j >= 0; j--)
        {
            if (key[i] == key[j]) return false;
        }
    }
    return true;
}

bool valid_alpha(string key){
    for (int i=0; i<strlen(key); i++){
        if (!isalpha(key[i])){
            return false;
        }
    }
    return true;
}

string make_cipher(string key, string text){
    for (int i=0; i<strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            bool upper = false;
            if (isupper(text[i]))
            {
                upper = true;
                text[i] = tolower(text[i]);
            }
            if (islower(text[i]))
            {
                text[i] = key[text[i] - 97];
                if (upper) text[i] = toupper(text[i]);
            }
        }
    }
    return text;
}