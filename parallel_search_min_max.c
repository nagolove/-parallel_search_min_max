#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <stdint.h>
#include <limits.h>

struct Thread {
    thrd_t  id;
    int     *arr;
    int     i_start, i_end;
    int     max, min;
};

int worker_search(void *arg) {
    assert(arg);
    struct Thread *ctx = arg;
    int max = INT_MIN, min = INT_MAX;
    const int *arr = ctx->arr;
    for (int i = ctx->i_start; i < ctx->i_end; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min)
            min = arr[i];
    }
    ctx->max = max;
    ctx->min = min;
    return 0;
}

static void search_min_max(
    int *arr, int num, int threads_num, int *min, int *max
) {
    assert(arr);
    assert(min);
    assert(max);
    assert(num > 0);
    assert(threads_num);
    assert(num % threads_num == 0);

    clock_t start = clock();

    struct Thread threads[threads_num];

    int range = num / threads_num;
    int i_start = 0;
    for (int i = 0; i < threads_num; ++i) {
        threads[i] = (struct Thread) {
            .arr = arr,
            .i_start = range * i,
            .i_end = range * i + range + 1,
        };
        i_start += range;
        thrd_create(&threads[i].id, worker_search, &threads[i]);
    }

    for (int i = 0; i < threads_num; ++i) {
        thrd_join(threads[i].id, NULL);
    }

    *max = INT_MIN;
    *min = INT_MAX;
    for (int i = 0; i < threads_num; ++i) {
        const struct Thread *t = &threads[i];
        if (t->max > *max)
            *max = t->max;
        if (t->min < *min)
            *min = t->min;
    }

    clock_t end = clock();
    double elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
    printf("elapsed time: %.2f.\n", elapsed_time);
}

int main() {
    const int num = 600'000'000;
    int threads_num;

    int *arr = malloc(sizeof(arr[0]) * num);
    assert(arr);

    srand(time(NULL));
    for (int i = 0; i < num; i++) {
        arr[i] = rand() * rand();
        //arr[i] = rand();
    }

    int min, max;

    //__builtin___clear_cache((char*)arr, (char*)(arr + num));
    threads_num = 1;
    search_min_max(arr, num, threads_num, &min, &max);
    printf("thread_num: %d, max %d, min %d\n", threads_num, max, min);

    //__builtin___clear_cache((char*)arr, (char*)(arr + num));
    threads_num = 2;
    search_min_max(arr, num, threads_num, &min, &max);
    printf("thread_num: %d, max %d, min %d\n", threads_num, max, min);

    //__builtin___clear_cache((char*)arr, (char*)(arr + num));
    threads_num = 3;
    search_min_max(arr, num, threads_num, &min, &max);
    printf("thread_num: %d, max %d, min %d\n", threads_num, max, min);

    //__builtin___clear_cache((char*)arr, (char*)(arr + num));
    threads_num = 4;
    search_min_max(arr, num, threads_num, &min, &max);
    printf("thread_num: %d, max %d, min %d\n", threads_num, max, min);

    //__builtin___clear_cache((char*)arr, (char*)(arr + num));
    threads_num = 5;
    search_min_max(arr, num, threads_num, &min, &max);
    printf("thread_num: %d, max %d, min %d\n", threads_num, max, min);

    //__builtin___clear_cache((char*)arr, (char*)(arr + num));
    threads_num = 6;
    search_min_max(arr, num, threads_num, &min, &max);
    printf("thread_num: %d, max %d, min %d\n", threads_num, max, min);


    free(arr);
    return EXIT_SUCCESS;
}
