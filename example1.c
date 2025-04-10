#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} NODE;

typedef struct g {
    int v;
    NODE** alst;
} GPH;

NODE* create_node(int v) {
    NODE* nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH* g, int src, int dest) {
    NODE* nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH* create_g(int v) {
    GPH* g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE*));
    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
    }
    return g;
}

void insert_edges(GPH* g, int edg_nr) {
    int src, dest;
    printf("Adauga %d muchii (nodurile incep de la 0):\n", edg_nr);
    for (int i = 0; i < edg_nr; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
    }
}

int drum_direct(GPH* g, int src, int dest) {
    NODE* temp = g->alst[src];
    while (temp != NULL) {
        if (temp->data == dest)
            return 1;
        temp = temp->next;
    }
    return 0;
}

int main() {
    int nrv, edg_nr;
    printf("Cate noduri are graful? ");
    scanf("%d", &nrv);

    printf("Cate muchii are graful? ");
    scanf("%d", &edg_nr);

    GPH* g = create_g(nrv);

    insert_edges(g, edg_nr);

    int a, b;
    printf("Verificam daca exista drum direct intre doua restaurante.\n");
    printf("Introdu doua noduri (ex: 0 3): ");
    scanf("%d %d", &a, &b);

    if (drum_direct(g, a, b)) {
        printf("Exista drum direct intre %d si %d.\n", a, b);
    } else {
        printf("NU exista drum direct intre %d si %d.\n", a, b);
    }

    return 0;
}
