#include<stdlib.h>

char* convertIntegerToChar(unsigned int N)
{
    int m = N;
    int digit = 0;
    while (m) {
        digit++;
        m /= 10;
    }
    char* arr;
    char arr1[digit];
    arr = (char*)malloc(digit);

    int index = 0;
    while (N) {
        arr1[index++] = N % 10 + '0';
        N /= 10;
    }
    arr1[index]='\0';
    int i =0;
    for (;i < index; i++) {
        arr[i] = arr1[index-1-i];
    }
    arr[i] = '\0';
    return arr;
}
