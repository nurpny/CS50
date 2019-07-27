# include <stdio.h>
# include <cs50.h>
# include <math.h>

int main(void)
{
    // Get user input
    long long num;
    do
    {
        num = get_long_long("Number: ");
    }
    while (num < 0);

    // number of digits
    int digits = log10(num)+1;

    // sum digits
    int sum = 0;
    int n, first, second;
    for (int i=1; i <= digits; i++){
        n = num%10;

        // find first digit
        if (i == digits){
            first = n;
        }

        // find second digit
        else if (i == digits - 1){
            second = n;
        }

        if (i%2 ==0){
            n *= 2;
            if (n >= 10){
                int r = n % 10;
                n = n/10;
                sum += n+r;
            }
            else {
                sum += n;
            }
        }
        else {
            sum += n;
        }
        num /= 10;
    }

    if (first == 3 && (second == 4 || second == 7) && digits == 15 && sum%10 == 0){
        printf("AMEX\n");
    }
    else if (first == 5 && second < 6 && digits == 16 && sum%10 == 0){
        printf("MASTERCARD\n");
    }
    else if (first == 4 && (digits == 13 || digits == 16) && sum%10 == 0){
        printf("VISA\n");
    }
    else {
        printf("INVALID\n");
    }

}