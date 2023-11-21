#include <stdio.h>
#include <string.h>

int main() {
    int count, src_router, i, j, k, w, v, min;
    int cost_matrix[100][100], dist[100], last[100];
    int flag[100];

    printf("\n Enter the no of routers: ");
    scanf("%d", &count);

    printf("\n Enter the cost matrix values:\n");
    for (i = 0; i < count; i++) {
        for (j = 0; j < count; j++) {
            printf("%d -> %d: ", i, j);
            scanf("%d", &cost_matrix[i][j]);
            if (cost_matrix[i][j] < 0) cost_matrix[i][j] = 1000;
        }
    }

    printf("\n Enter the source router: ");
    scanf("%d", &src_router);

    for (v = 0; v < count; v++) {
        flag[v] = 0;
        last[v] = src_router;
        dist[v] = cost_matrix[src_router][v];
    }
    flag[src_router] = 1;

    int choice;
    do {
        printf("\nMenu:");
        printf("\n1. Find Shortest Path");
        printf("\n2. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Shortest Path Routing
                for (i = 0; i < count; i++) {
                    min = 1000;
                    for (w = 0; w < count; w++) {
                        if (!flag[w] && dist[w] < min) {
                            v = w;
                            min = dist[w];
                        }
                    }
                    flag[v] = 1;
                    for (w = 0; w < count; w++) {
                        if (!flag[w] && min + cost_matrix[v][w] < dist[w]) {
                            dist[w] = min + cost_matrix[v][w];
                            last[w] = v;
                        }
                    }
                }
                for (i = 0; i < count; i++) {
                    printf("\n%d --> %d: Path taken:\n %d", src_router, i, i);
                    w = i;
                    while (w != src_router) {
                        printf("<--%d", last[w]);
                        w = last[w];
                    }
                    printf("\n Shortest path cost: %d", dist[i]);
                }
                break;
            case 2:
                // Exit the program
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (choice != 2);

    return 0;
}
