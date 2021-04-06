#include <stdio.h>
#include <cs50.h>

// length helper: return length

int length(long n)
{
    if (n > 9999999999999999)
    {
        return false;
    }
    else if (n > 999999999999999)
    {
        return 16;
    }
    else if (n > 99999999999999)
    {
        return 15;
    }
    else if (n > 9999999999999)
    {
        return false;
    }
    else if (n > 999999999999)
    {
        return 13;
    }
    else
    {
        return false;
    }
}

// Luhn's algorithm/sumcheck

int sumcheck(long n)
{
    // get length
    int len = length(n);
    
    // create variable to hold digits
    int digits[len];
    
    // add digits to digits variable in reverse order
    for (int i = 0; i < len; i++)
    {
        digits[i] = n % 10;
        n /= 10;
    }
    
    // work out size of arrays to be doubled and not doubled
    
    int double_size = 0;
    int other_size = 0;
    
    if (len % 2 == 0)
    {
        double_size = len / 2;
        other_size = len / 2;
    }
    else
    {
        float len_float = len;
        double_size = len_float / 2 - 0.5;
        other_size = len_float / 2 + 0.5;
    }
    // printf("Double size: %i\n",double_size);
    // printf("Other size: %i\n",other_size);
    
    // divide digits into those to be doubled and the rest
    
    int double_dig[double_size];
    int other_dig[other_size];
    
    int double_index = 0;
    int other_index = 0;
    
    for (int i = 0; i < len; i++)

        if (i % 2 == 0)
        {
            other_dig[other_index] = digits[i];
            other_index++;
        }
        else
        {
            double_dig[double_index] = digits[i];
            double_index++;
        }

    // double digits
    
    // printf("%i %i %i %i %i %i\n",double_dig[0],double_dig[1],double_dig[2],double_dig[3],double_dig[4],double_dig[5]);
    
    for (int i = 0; i < double_size; i++)
    {
        double_dig[i] = double_dig[i] * 2;
    }
    
    // printf("%i %i %i %i %i %i\n",double_dig[0],double_dig[1],double_dig[2],double_dig[3],double_dig[4],double_dig[5]);
    
    // in new array, for each element in doubled digits array, if length is 2, split and add, else just add
    
    int double_dig_split [] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double_index = 0;
    
    for (int i = 0; i < double_size; i++)
    {
        if (double_dig[i] > 9)
        {
            double_dig_split[double_index] = (double_dig[i] - double_dig[i] % 10) / 10;
            double_index++;
            double_dig_split[double_index] = double_dig[i] % 10;
            double_index++;
        }
        else
        {
            double_dig_split[double_index] = double_dig[i];
            double_index++;
        }
    }
    
    // printf("Doubled: %i %i %i %i %i %i %i %i\n",double_dig[0],double_dig[1],double_dig[2],double_dig[3],double_dig[4],double_dig[5],double_dig[6],double_dig[7]);
    // printf("Doubled split: %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i\n",double_dig_split[0],double_dig_split[1],double_dig_split[2],double_dig_split[3],double_dig_split[4],double_dig_split[5],double_dig_split[6],double_dig_split[7],double_dig_split[8],double_dig_split[9],double_dig_split[10],double_dig_split[11],double_dig_split[12],double_dig_split[13],double_dig_split[14],double_dig_split[15]);
    // printf("Other: %i %i %i %i %i %i %i %i\n",other_dig[0],other_dig[1],other_dig[2],other_dig[3],other_dig[4],other_dig[5],other_dig[6],other_dig[7]);
    
    // sum all digits
    
    int total = 0;
    
    for (int i = 0; i < 16; i++)
    {
        total += double_dig_split[i];
    }
    
    for (int i = 0; i < other_size; i++)
    {
        total += other_dig[i];
    }
    
    // printf("Total: %i\n", total);
    
    // %10 final sum and return true if 0, else false
    
    if (total % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int type(long n)
{
    // get length
    int len = length(n);
    
    // create variable to hold digits
    int digits[len];
    
    // add digits to digits variable in reverse order
    for (int i = len - 1; i >= 0; i--)
    {
        digits[i] = n % 10;
        n /= 10;
    }
    
    if (digits[0] == 3)
    {
        if (digits[1] == 4 || digits[1] == 7)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (digits[0] == 4)
    {
        printf("VISA\n");
    }
    else if (digits[0] == 5)
    {
        if (digits[1] > 0 && digits[1] < 6)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    // printf("%i%i\n",digits[0],digits[1]);
    // printf("yay, almost there\n");
    return 0;
}

int main(void)
{
    // prompt user for their card number
    long n = get_long("Card number: \n");
    
    // if length and sumcheck evaluate to true, check type; else, print "INVALID"
    if (length(n) && sumcheck(n))
    {
        type(n);
    }
    else
    {
        printf("INVALID\n");
    }
}