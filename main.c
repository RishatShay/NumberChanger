#include <stdio.h>
#define N 50


int raiseDegree();
int decToDec();
int binToDec();
int octToDec();
int hexToDec();
int checkDec();
int performOperation();

int main(void) {
    FILE *fptr = fopen("input.txt", "r");

    // input count of numbers in lines
    int n = 0;
    fscanf(fptr, "%d\n", &n);

    // input numbers in different bases
    char numbers[n][N];
    for (int i=0; i < n; i++)
        fscanf(fptr, "%s", numbers[i]);

    // input bases
    int bases[n];
    for (int i=0; i < n; i++)
        fscanf(fptr, "%d", &bases[i]);

    // finish parsing input.txt and open output.txt to write a result
    fclose(fptr);
    fptr = fopen("output.txt", "w");

    int result = 0;
    for (int i = 0; i < n; i ++) {
        int temp;
        switch (bases[i]) {
            case 2:
                temp = binToDec(numbers[i]);
                break;
            case 8:
                temp = octToDec(numbers[i]);
                break;
            case 16:
                temp = hexToDec(numbers[i]);
                break;
            case 10:
                temp = decToDec(numbers[i]);
                break;
            default:
                temp = -1;
        }

        // check a validness of input numbers
        if (temp == -1) {
            fprintf(fptr, "Invalid inputs\n");
            fclose(fptr);
            return 0;
        }
        else result += temp;
    }

    fprintf(fptr, "%d\n", result + performOperation(n));
    fclose(fptr);
    return 0;
}


// to raise number n to the d-th degree
int raiseDegree(int n, int d) {
    if (d==0) return 1;
    if (d==1) return n;

    int result = 1;
    for (int i = 0; i < d; i++) result *= n;
    return result;
}


// converting decimal(char array) to decimal(integer)
int decToDec(char dec[]) {
    // found a lenght of decimal array
    int len = 0;
    for (;dec[len] != '\0'; len++) {};

    // convert dec chars to dec
    int decimal = 0;
    for(int i = 0; i < len; i++) {
        // checking validness
        int temp = (dec[i] - '0');
        if (temp < 0 || temp > 9 ) return -1;

        decimal += temp * raiseDegree(10, len - (i+1));
    }
    return decimal;
}


// converting binary(char array) to decimal(integer)
int binToDec(char bin[]) {
    // found a lenght of binary
    int len = 0;
    for (;bin[len] != '\0'; len++) {};

    // convert bin to dec
    int decimal = 0;
    for(int i = 0; i < len; i++) {
        // checking validness
        int temp = (bin[i] - '0');
        if (temp < 0 || temp > 1) return -1;

        decimal += temp * raiseDegree(2, len - (i+1));
    }
    return decimal;
}


// converting octal(char array) to decimal(integer)
int octToDec(char oct[]) {
    // found a lenght of octal
    int len = 0;
    for (;oct[len] != '\0'; len++) {};

    // convert bin to dec
    int decimal = 0;
    for(int i = 0; i < len; i++) {
        // checking validness
        int temp = (oct[i] - '0');
        if (temp < 0 || temp > 7) return -1;

        decimal += temp * raiseDegree(8, len - (i+1));
    }

    return decimal;
}


// converting hexadecimal(char array) to decimal(integer)
int hexToDec(char hex[]) {
    // found a lenght of hexadecimal
    int len = 0;
    for (;hex[len] != '\0'; len++) {};

    // convert bin to dec
    int decimal = 0;
    for(int i = 0; i < len; i++) {
        int temp;

        if ((int)hex[i] < 60) temp = hex[i] - '0';
        else temp = hex[i] - '0' - 7;

        // checking validness
        if (temp < 0 || temp > 15) return -1;

        decimal += temp * raiseDegree(16, len - (i+1));
    }

    return decimal;
}


// if count of indexes odd returns -10, else 0 *(the requirement of the task conditions)
int performOperation(int n) {
    if (n % 2 == 0) return 0;
    return -10;
}