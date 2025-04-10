#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} NODE;

typedef struct Graph {
    int vertices;
    int* visited;
    NODE** adjacency_lists;
} GPH;

NODE* create_node(int v) {
    NODE* new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GPH* create_graph(int vertices) {
    GPH* graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE*));
    graph->visited = malloc(vertices * sizeof(int));
    
    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(GPH* graph, int src, int dest) {
    NODE* new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insert_edges(GPH* graph, int nr_of_edges) {
    int src, dest;
    printf("Adauga %d muchii (nodurile incep de la 0):\n", nr_of_edges);
    for (int i = 0; i < nr_of_edges; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void wipe_visited_list(GPH* graph) {
    for (int i = 0; i < graph->vertices; i++)
        graph->visited[i] = 0;
}

void print_graph(GPH* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        printf("%d: ", i);
        NODE* temp = graph->adjacency_lists[i];
        while (temp) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void DFS(GPH* graph, int vertex) {
    NODE* temp = graph->adjacency_lists[vertex];

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp) {
        int connected_vertex = temp->data;
        if (!graph->visited[connected_vertex])
            DFS(graph, connected_vertex);
        temp = temp->next;
    }
}

typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

QueueNode* create_queue_node(int data) {
    QueueNode* node = malloc(sizeof(QueueNode));
    node->data = data;
    node->next = NULL;
    return node;
}

void enqueue(QueueNode** rear, QueueNode** front, int data) {
    QueueNode* new_node = create_queue_node(data);
    if (*rear == NULL) {
        *front = *rear = new_node;
    } else {
        (*rear)->next = new_node;
        *rear = new_node;
    }
}

int dequeue(QueueNode** front, QueueNode** rear) {
    if (*front == NULL) return -1;
    int data = (*front)->data;
    QueueNode* temp = *front;
    *front = (*front)->next;
    if (*front == NULL) *rear = NULL;
    free(temp);
    return data;
}

void BFS(GPH* graph, int start_vertex) {
    QueueNode* front = NULL;
    QueueNode* rear = NULL;

    graph->visited[start_vertex] = 1;
    enqueue(&rear, &front, start_vertex);

    while (front != NULL) {
        int current = dequeue(&front, &rear);
        printf("%d ", current);

        NODE* temp = graph->adjacency_lists[current];
        while (temp) {
            int adj = temp->data;
            if (!graph->visited[adj]) {
                graph->visited[adj] = 1;
                enqueue(&rear, &front, adj);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int nr_of_vertices, nr_of_edges, starting_vertex;

    printf("Cate noduri are graful? ");
    scanf("%d", &nr_of_vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &nr_of_edges);

    GPH* graph = create_graph(nr_of_vertices);
    insert_edges(graph, nr_of_edges);

    printf("\nStructura grafului:\n");
    print_graph(graph);

    printf("\nDe unde plecam in DFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere DFS: ");
    DFS(graph, starting_vertex);

    wipe_visited_list(graph);

    printf("\n\nDe unde plecam in BFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere BFS: ");
    BFS(graph, starting_vertex);

    printf("\n");
    return 0;
}
