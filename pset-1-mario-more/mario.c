#include <cs50.h>
#include <stdio.h>

void line(int id, int max); //print one line of piramid

int main(void){

    //get valid input
    int h;
    do{
        h = get_int("Height: ");
    }while(h<1 || h>8);

    //print piramid
    for(int i=0; i<h; i++){
        line(i, h);
        printf("\n");
    }
}

void line(int id, int max){

    //print left site
    for(int i=max-1; i>=0; i--){
        if(i<=id){
            printf("%c", '#');
        }else{
            printf("%c", ' ');
        }
    }

    //print gap
    printf("  ");

    //print right side
    for(int i=0; i<max; i++){
        if(id>=i){
            printf("%c", '#');
        }else{
            break;
        }
    }

}