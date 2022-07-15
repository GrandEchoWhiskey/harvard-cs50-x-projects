#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's your name? "); //gets name as input
    printf("hello, %s\n", name); //outputs Hello, name
}