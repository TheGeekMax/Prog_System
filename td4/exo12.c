//
// Created by Maxime Sanciaume on 17/10/2024.
//


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


// exo 12.2
pthread_t* threads_id;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int sum = 0;

typedef struct {
    int n;
    int p;
    int t;
} Params122;

void *sumItem(void *parms){
    Params122 *params = (Params122*) parms;

    //calcul de la somme
    int sumLocal = 0;
    for(int i = 1; i <= params->p; i++){
        sumLocal += (params->t-1)*params->p + i;
    }

    //on ajoute la somme locale a la somme globale
    pthread_mutex_lock(&mutex);
    sum += sumLocal;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void exo122(int n, int p) {
    //etape 0, on apelle le maloc
    threads_id = (pthread_t*)malloc(n * sizeof(pthread_t));


    //etape 1, on cree les threads
    for (int i = 0; i < n; i++) {
        Params122 *params = (Params122*)malloc(sizeof(Params122));
        params->n = n;
        params->p = p;
        params->t = i+1;
        pthread_create(&threads_id[i], NULL, sumItem, (void*)params);
    }

    //etape 2 on attend la fin des threads
    for (int i = 0; i < n; i++) {
        pthread_join(threads_id[i], NULL);
    }

    //etape 3 on affiche le resultat
    printf("sum = %d\n", sum);
}

// exo 12.3


pthread_t *threads_ex123;
pthread_mutex_t mutex_ex123 = PTHREAD_MUTEX_INITIALIZER;
int last_ex123 = -1;

void *ex123Thread(void *n){
    int *nInt = (int*)n;
    //etape 0, la boucle
    for(int i = 0; i < 10; i ++) {
        struct timespec t;
        t.tv_sec = 0;
        t.tv_nsec = 100000000 + rand() % 100000000;
        nanosleep(&t, NULL);
        printf("le thread %d en est a l'etape %d\n", *nInt, i);
    }

    //on sauvegarde la valeur du thread
    pthread_mutex_lock(&mutex_ex123);
    last_ex123 = *nInt;
    pthread_mutex_unlock(&mutex_ex123);
    free(n);
    return NULL;
}

void exo123(int i) {
    srand(time(NULL));
    //etape 0, on apelle le maloc
    threads_ex123 = (pthread_t*)malloc(i * sizeof(pthread_t));

    //etape 1, on cree les threads
    for (int j = 0; j < i; j++) {
        int *k = (int*)malloc(sizeof(int));
        *k = j;
        pthread_create(&threads_ex123[j], NULL, ex123Thread, (void*)k);
    }

    //etape 2 on attend la fin des threads
    for (int j = 0; j < i; j++) {
        pthread_join(threads_ex123[j], NULL);
    }

    //etape 3 on affiche le dernier thread
    printf("last = %d\n", last_ex123);
}

//exo 12.4

long int globalCounter = 0;
pthread_t *threads_124;

void *count_124(void* _) {
    for(int i = 0; i < 1000000; i++) {
        globalCounter++;
    }
}

void exo124(){
    //etape 0, on creer 4 threads
    threads_124 = (pthread_t*)malloc(4 * sizeof(pthread_t));
    for(int i = 0; i < 4; i++) {
        pthread_create(&threads_124[i], NULL, count_124, NULL);
    }

    //etape 1, on attend la fin des threads
    for(int i = 0; i < 4; i++) {
        pthread_join(threads_124[i], NULL);
    }

    //etape 2, on affiche le resultat
    printf("globalCounter = %ld\n", globalCounter);
}