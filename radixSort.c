#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Caso use memcpy()

void radix_sort(int *vetor, int n);

void counting_sort(int *vetor, int n, int div, int *temp);

void radix_sort_print(int *vetor, int n);

void main()
{
    int N, i;
    scanf("%i", &N);

    int *vetor = (int *)malloc(sizeof(int) * N);

    for (i = 0; i < N; i++)
        scanf("%i", &vetor[i]);

    radix_sort(vetor, N);

    for (i = 0; i < N; i++)
        printf("%i ", vetor[i]);

    printf("\n");
}

void radix_sort(int *vetor, int n)
{
    int max = vetor[0]; // Maior número
    int i;
    int div = 1;
    int *temp = (int *)malloc(sizeof(int) * n);

    // Achar a maior número
    for (i = 0; i < n; i++)
    {
        if (vetor[i] > max)
            max = vetor[i];
    }

    // Enquanto o maior número for divisivel
    while (max > 0)
    {
        counting_sort(vetor, n, div, temp); // Faça o counting sort com o divisor div
        div = div * 10; // Atualiza o div para a proxima iteração utilizar o próximo digito
        max = max / 10;
    }
    free(temp);
}

void counting_sort(int *vetor, int n, int div, int *temp)
{
    int i, aux;
    int *c = (int *)calloc(sizeof(int), 10);
    int digito;

    // contando a presença de cada digito
    for (i = 0; i < n; i++)
    {
        // Achar digito de um numero X: (X / div) % 10
        digito = (vetor[i] / div) % 10;
        c[digito]++;
    }

    int acumulador = 0;
    /*
    convertendo o vetor c de um vetor de contagem
    para um vetor de acumulo de contagem
    */
    for (i = 0; i < 10; i++)
    {
        aux = c[i];
        c[i] = acumulador;
        acumulador = acumulador + aux;
    }

    // Alocando cada número do vetor na sua posição correta no vetor temporario
    for (i = 0; i < n; i++)
    {
        digito = (vetor[i] / div) % 10;
        temp[c[digito]] = vetor[i];
        c[digito]++;
    }

    // Copiar o vetor temporario no vetor principal

    // memcpy(vetor, temp, sizeof(int) * n); // Função da biblioteca string.h que copia um vetor em um outro

    // Copiar "manualmente"
    for (i = 0; i < n; i++)
        vetor[i] = temp[i];
}

void radix_sort_print(int *vetor, int n) // Printa cada ordenação por digito usado
{
    int max = vetor[0];
    int i;
    int div = 1;
    int count = 1;
    int *temp = (int *)malloc(sizeof(int) * n);

    for (i = 0; i < n; i++)
    {
        if (vetor[i] > max)
            max = vetor[i];
    }

    while (max > 0)
    {
        counting_sort(vetor, n, div, temp);
        div = div * 10;
        max = max / 10;
        printf("%i digito: ", count++);

        for (i = 0; i < n; i++)
            printf("%i ", vetor[i]);

        printf("\n");
    }

    free(temp);
}