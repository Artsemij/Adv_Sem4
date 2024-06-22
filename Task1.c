/*
Реализовать программу 1-го практического задания с помощью биномиального коэффициента.
Данные на вход: Два целых числа N и M
Данные на выход: Одно целое число – количество вариантов

Пример №1
Данные на вход: 10 5
Данные на выход: 252
*/
#include <stdio.h>
#include <stdlib.h>

int binomial_coefficient(int n, int k) {
    if (k > n) {
        return 0;
    }

    int num = 1;
    for (int i = 1; i <= k; i++) {
        num *= n--;
        num /= i;
    }

    return num;
}

int main() {
    int n, k;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("Enter the value of k: ");
    scanf("%d", &k);

    int result = binomial_coefficient(n, k);

    printf("The binomial coefficient of %d and %d is: %d\n", n, k, result);

    return 0;
}