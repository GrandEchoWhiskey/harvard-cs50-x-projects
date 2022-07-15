#include <cs50.h>
#include <stdio.h>

/**
 * American Express     15 digits,      starts with 34, 37
 * MasterCard           16 digits,      starts with 51, 52, 53, 54, 55
 * Visa                 13/16 digits    starts with 4
**/

bool checksum(long number);
bool is_AmericanExpress(long number);
bool is_MasterCard(long number);
bool is_Visa(long number);

long multiplier(int digits);

int main(void){

    //get input
    long card_number = get_long("Number: ");

    //tests
    if(checksum(card_number)){ // checksum
        if(is_AmericanExpress(card_number)){ // American Express
            printf("AMEX\n");
            return 0;
        }else if(is_MasterCard(card_number)){ // MasterCard
            printf("MASTERCARD\n");
            return 0;
        }else if(is_Visa(card_number)){ // Visa
            printf("VISA\n");
            return 0;
        }
    }
    printf("INVALID\n");

}

bool checksum(long number){

    //define variables
    int x = 0;
    int y = 0;
    bool to_y = true;

    //take every second digit form the end, and add it to the coresponding intiger above.
    while(number > 0){
        int t = number % 10;
        number /= 10;
        if(to_y){
            y += t;
        }else{
            t *= 2;
            do{                 //if bigger than 9 it will repeat adding single digits
                x += t % 10;
                t /= 10;
            }while(t > 0);
        }
        to_y = !to_y;
    }

    //check if passes the checksum test and return value
    if((x + y) % 10 == 0) return true;
    return false;

}

bool is_AmericanExpress(long number){

    //create const for easier conditions. Aditional 0's
    const int AD_DIGITS = 13;


    //checks if starts with 34 or 37, and is 15 digits long, and returns true if so. Otherwise returns false
    if(number >= (34 * multiplier(AD_DIGITS)) && number < (35 * multiplier(AD_DIGITS))) return true;
    else if(number >= (37 * multiplier(AD_DIGITS)) && number < (38 * multiplier(AD_DIGITS))) return true;
    return false;

}

bool is_MasterCard(long number){

    //create const for easier conditions. Aditional 0's
    const int AD_DIGITS = 14;

    //checks if starts with 51 to 55, and is 16 digits long, and returns true if so. Otherwise returns false
    if(number >= (51 * multiplier(AD_DIGITS)) && number < (56 * multiplier(AD_DIGITS))) return true;
    return false;

}

bool is_Visa(long number){

    //create const for easier conditions. Aditional 0's
    const int AD_DIGITS_A = 15;
    const int AD_DIGITS_B = 12;

    //checks if starts with 4, and is 16 or 13 digits long, and returns true if so. Otherwise returns false
    if(number >= (4 * multiplier(AD_DIGITS_A)) && number < (5 * multiplier(AD_DIGITS_A))) return true;
    else if(number >= (4 * multiplier(AD_DIGITS_B)) && number < (5 * multiplier(AD_DIGITS_B))) return true;
    return false;

}

long multiplier(int digits){ // returns aditional 0's

    long result = 1;
    for(int i=0; i<digits; i++){
        result *= 10;
    }
    return result;

}