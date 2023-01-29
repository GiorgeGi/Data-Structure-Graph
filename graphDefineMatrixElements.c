#include <stdio.h>
#include <stdlib.h>

struct Graph {
    int n;
    int **a;
};

int front, rear, *queue, *mark;

void printGraphAdjacencyMatrix(struct Graph *g, int s);
void bfs(struct Graph *g, int k);
int enqueue(struct Graph *g, int k);
int dequeue(int *k);

int main() {
    struct Graph g;
    int s, i, j;
    printf("Enter number of nodes in the graph: ");
    scanf("%d", &g.n);
    g.a = (int **)malloc(g.n * sizeof(int *));
    for (i = 0; i < g.n; i++) {
        g.a[i] = (int *)malloc(g.n * sizeof(int));
    }
    mark = (int *)malloc(g.n*sizeof(int));
    for (i = 0; i < g.n; i++) {
        for (j = 0; j < g.n; j++) {
            printf("Enter the value for a[%d][%d]: ", i+1, j+1);
            scanf("%d", &g.a[i][j]);
        }
    }
    printf("Give start node (1-%d) or 0 to end: ", g.n);
    scanf("%d", &s);
    while (s >= 1 && s <= g.n) {
        // Initialize queue
        queue = (int *)malloc(g.n*g.n*sizeof(int));
        front = -1;
        rear = -1;
        for (i = 0; i < g.n; i++) {
            mark[i] = 0;
        }
        bfs(&g, s-1);
        printGraphAdjacencyMatrix(&g, s);
        printf("Give start node (1-%d) or 0 to end: ", g.n);
        scanf("%d", &s);
        free(queue);
    }
    free(mark);
    return 0;
}

void bfs(struct Graph *g, int k) {
    int i, j, flag;
    flag = enqueue(g, k);
    mark[k] = 1;
    while (flag == 1) {
        flag = dequeue(&i);
        if (flag == 1) {
            printf("Now in %d\n", i+1);
            for (j = 0; j < g->n; j++) {
                if (g->a[i][j] == 1 && mark[j] == 0) {
                    flag = enqueue(g, j);
                    mark[j] = 1;
                }
            }
        }
    }
}

void printGraphAdjacencyMatrix(struct Graph *g, int s) {
	int i, j;
	printf("Adjacency matrix of the given graph:\n");
	for (i = 0; i < g->n; i++) {
		for (j = 0; j < g->n; j++) {
		printf("%d ", g->a[i][j]);
		}
	printf("\n");
	}
}

int enqueue(struct Graph *g, int k) {
	int f = 0;
	if (front == -1) {
		front = 0;
	}
	if (rear < g->n*g->n - 1) {
		rear = rear + 1;
		queue[rear] = k;
		f = 1;
	}
	return f;
}

int dequeue(int *k) {
	int f = 0;
	if (front != -1 && front <= rear) {
		*k = queue[front];
		front = front + 1;
		f = 1;
	}
	return f;
}
