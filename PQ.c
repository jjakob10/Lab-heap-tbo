#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "PQ.h"

// TODO: Aqui você deve implementar uma fila com prioridade mínima para
//       ordenar os eventos por tempo, isto é, o evento com o menor tempo tem
//       a maior prioridade. Veja as funções definidas em 'event.h' para
//       a manipulação das estruturas de evento. A princípio, as funções já
//       existentes em 'event.h' são suficientes para implementar a simulação,
//       isto é, você não precisa implementar mais nada lá.
//
//       Você é livre para implementar a fila com prioridade da forma que quiser
//       mas é recomendado usar um min-heap para obter um bom desempenho. As
//       simulações maiores geram uma quantidade grande de eventos: um
//       limite superior frouxo (mas seguro) para o número máximo simultâneo de
//       eventos é N^3, aonde N é o número de partículas.

// TODO: Crie a struct pq.
struct pq
{
    int size;
    int tam;
    Event **events;
};

// Pai = idx -1 /2
// filho = idx*2 +1 ou +2
void heapfy_up(PQ *pq, int idx)
{
    Event **events = pq->events;
    while (idx)
    {
        if (compare(events[idx], events[(idx - 1) / 2]) < 0)
        {
            Event *e = events[idx];
            events[idx] = events[(idx - 1) / 2];
            events[(idx - 1) / 2] = e;
            idx = (idx - 1) / 2;
        }
        else
            break;
    }
}

void heapfy_down(PQ *pq, int idx)
{
    Event **events = pq->events;
    while (1)
    {
        Event *smallestChild;
        int chd1 = 2 * idx + 1;
        int chd2 = 2 * idx + 2;
        int smallestChildIdx;
        if (chd1 > pq->size)
            break;
        if (chd2 > pq->size)
            smallestChildIdx = chd1;
        else
        {
            smallestChildIdx = compare(events[chd1], events[chd2]) < 0 ? chd1 : chd2;
        }
        smallestChild = events[smallestChildIdx];

        if (compare(events[idx], smallestChild) > 0)
        {
            events[smallestChildIdx] = events[idx];
            events[idx] = smallestChild;
            idx = smallestChildIdx;
        }
        else
            break;
    }
}

/*
 * Cria uma nova fila de prioridade mínima com o limite de elementos informado.
 */
PQ *PQ_create(int max_N)
{
    // TODO: Implemente a criação da fila que suporta no máximo o número de
    //       de eventos informados no parâmetro.
    PQ *pq = malloc(sizeof(PQ));
    pq->tam = max_N;
    pq->size = 0;
    pq->events = malloc(sizeof(Event *) * max_N);

    return pq;
}

/*
 * Libera a memória da fila.
 */
void PQ_destroy(PQ *pq)
{
    // TODO: Implemente essa função que libera toda a memória da fila,
    //       destruindo inclusive os eventos que estavam na fila.
    int i;
    for (i = 0; i < pq->size; i++)
    {
        destroy_event(pq->events[i]);
    }
    free(pq->events);
    free(pq);
}

/*
 * Insere o evento na fila segundo o seu tempo.
 */
void PQ_insert(PQ *pq, Event *e)
{
    // TODO: Implemente essa função que insere o evento dado na fila segundo
    //       o tempo do evento.
    //       Assuma que 'e' não é nulo. É importante testar overflow (inserção
    //       em uma fila que já contém o número máximo de eventos) para evitar
    //       dores de cabeça com acessos inválidos na memória.

    if (pq->size >= pq->tam)
    {
        printf("HEAP CHEIO!");
        exit(1);
        return;
    }
    pq->events[pq->size] = e;
    heapfy_up(pq, pq->size++);
}

/*
 * Remove e retorna o evento mais próximo.
 */
Event *PQ_delmin(PQ *pq)
{
    // TODO: Implemente essa função que remove o evento com o menor tempo da
    //       fila e o retorna.
    Event *e = pq->events[0];
    pq->size--;
    pq->events[0] = pq->events[pq->size];

    heapfy_down(pq, 0);
    return e;
}

/*
 * Testa se a fila está vazia.
 */
bool PQ_is_empty(PQ *pq)
{
    // TODO: Implemente essa função.
    return PQ_size(pq) == 0;
}

/*
 * Retorna o tamanho da fila.
 */
int PQ_size(PQ *pq)
{
    // TODO: Implemente essa função.
    return pq->size;
}
