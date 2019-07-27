# include <stdio.h>
# include <cs50.h>

int main(void){
    //do while loop for user input
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n > 23 || n < 0);
    //print per the height
    for (int i = 0; i < n; i++){
        for (int m = n-i-1; m > 0; m--){
            printf(" ");
        }
        for (int g = 0; g <= i; g++){
            printf("#");
        }
        printf("  ");
        for (int g = 0; g <= i; g++){
            printf("#");
        }
        printf("\n");
    }

}