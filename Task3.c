/*

Реализовать программу 3-го практического задания более эффективным способом со сложностью О(n) (см. код в лекции).

Пример №1
Данные на вход:

don't_panic
nick_is_a_mastodon
Данные на выход: 3


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUTS 100
#define MAX_LEN 100
#define MAX_PRE_SUFFIXES 10000

int count_prefixes_and_suffixes(const char *inputs[], int size) {
    int count = 0;
    int len;
    int *hash_table = (int *)calloc(MAX_PRE_SUFFIXES, sizeof(int));

    // Precompute prefixes and suffixes
    for (int i = 0; i < size; i++) {
        len = strlen(inputs[i]);
        hash_table[len - 1] = 1;

        // Precompute suffixes
        for (int j = 1; j < len; j++) {
            hash_table[len - j - 1] = 1;
        }
    }

    // Count prefixes and suffixes
    for (int i = 0; i < size; i++) {
        len = strlen(inputs[i]);

        // Count prefixes
        for (int j = 1; j < len; j++) {
            if (hash_table[j - 1]) {
                count++;
            }
        }
    }

    free(hash_table);
    return count;
}

int main() {
    const int MAX_INPUT_COUNT = MAX_INPUTS;
    const int MAX_INPUT_LEN = MAX_LEN;
    char inputs[MAX_INPUT_COUNT][MAX_INPUT_LEN];
    char temp[MAX_INPUT_LEN];
    int count = 0;

    printf("Введите несколько предложений (максимум %d).\n", MAX_INPUT_COUNT);
    printf("Нажмите Enter после каждого предложения или нажмите Ctrl+D для завершения ввода.\n");

    // Ввод предложений
    while (fgets(temp, sizeof(temp), stdin) != NULL && count < MAX_INPUT_COUNT) {
        // Удаление символа перевода строки
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') {
            temp[len - 1] = '\0';
        }

        // Пропуск пустых строк
        if (strlen(temp) == 0) {
            continue;
        }

        strcpy(inputs[count], temp);
        count++;
    }

    // Подсчет префиксов и суффиксов
    int pre_suff_count = count_prefixes_and_suffixes(inputs, count);

    printf("Количество общих префиксов и суффиксов: %d\n", pre_suff_count);

    return 0;
}

/*

Оптимизированная версия использует хэш-таблицу для хранения уникальных строк и их суффиксов, 
что позволяет избежать повторной проверки существования строк в массиве inputs. Это уменьшает 
время работы алгоритма с O(n^3) до O(n^2), где n это количество входных строк.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unordered_map>

#define MAX_INPUTS 100
#define MAX_LEN 100

int count_prefixes_and_suffixes(const char *inputs[], int size) {
    int count = 0;
    int len;
    std::unordered_map<std::string, int> hash_table;

    // Precompute hash table for inputs
    for (int i = 0; i < size; i++) {
        len = strlen(inputs[i]);
        hash_table[inputs[i]] = 1;

        // Precompute suffixes
        for (int j = 1; j < len; j++) {
            hash_table[std::string(inputs[i] + j, len - j)] = 1;
        }
    }

    // Count prefixes and suffixes
    for (int i = 0; i < size; i++) {
        len = strlen(inputs[i]);

        // Count prefixes
        for (int j = 1; j < len; j++) {
            if (hash_table.find(std::string(inputs[i], j)) != hash_table.end()) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    const char *inputs[] = {"don't_panic", "nick_is_a_mastodon", "in_a_galaxy"};

    int count = count_prefixes_and_suffixes(inputs, sizeof(inputs) / sizeof(inputs[0]));

    printf("Количество общих префиксов и суффиксов: %d\n", count);

    return 0;
}

*/