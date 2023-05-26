#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

#define MAX_NODES 100

// Structure to represent a directed graph node 방향 그래프 노드를 나타내는 구조
struct Node {
    int value;
    struct Node* next;
};

// Structure to represent a directed graph 방향 그래프를 나타내는 구조
struct Graph {
    int numNodes;
    struct Node* adjacencyList[MAX_NODES];
    int inDegree[MAX_NODES];
};

// Function to create a new node 새 노드를 만드는 함수.
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with n nodes 노드가 n개인 그래프를 만드는 함수.
struct Graph* createGraph(int n) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numNodes = n;
    int i;
    for (i = 0; i < n; i++) {
        graph->adjacencyList[i] = NULL;
        graph->inDegree[i] = 0;
    }
    return graph;
}

// Function to add an edge between two nodes 두 노드 사이에 에지를 추가하는 함수
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;
    graph->inDegree[dest]++;
}

// Function to perform topological sorting using Kahn's algorithm Kahn 알고리즘을 사용하여 위상 정렬을 수행하는 함수
void topologicalSort(struct Graph* graph) {
    int* result = (int*)malloc(graph->numNodes * sizeof(int));
    int i, j;
    int front = 0, rear = 0;

    // Enqueue nodes with in-degree 0 들어오는 엣지가 0개인 노드를 큐 안에 넣음.
    for (i = 0; i < graph->numNodes; i++) {
        if (graph->inDegree[i] == 0) {
            result[rear++] = i;
        }
    }

    // Process until all nodes have been visited 사용자가 입려한 개수 만큼의 모든 노드를 방문할 때까지 while문 수행.
    while (front < rear) {
        int current = result[front++];
        struct Node* temp = graph->adjacencyList[current];

        // Reduce in-degree of adjacent nodes indegree가 0개인 노드를 지울 때마다 해당 노드에 인접한 노드의 indegree를 줄여줌.
        while (temp != NULL) {
            graph->inDegree[temp->value]--;
            if (graph->inDegree[temp->value] == 0) {
                result[rear++] = temp->value;
            }
            temp = temp->next;
        }
    }

    // Check for a cycle in the graph 그래프에 사이클이 있는지 확인하고, 사이클이 발견되면 문구를 출력함.
    if (front != graph->numNodes) {
        printf("Graph contains a cycle!\n");
        return;
    }

    // Print the topological order 정렬한 데이터를 출력함.
    printf("Topological Order: ");
    for (j = 0; j < graph->numNodes; j++) {
        printf("%d ", result[j]);
    }
}

int main() {
    int numNodes, numEdges;
    printf("Enter the number of nodes in the graph: ");
    scanf_s("%d", &numNodes); //numNodes에 노드의 개수를, numEdge에 엣지의 개수를 입력받아 저장함.

    if (numNodes <= 0 || numNodes > MAX_NODES) {
        printf("Invalid number of nodes. Please enter a value between 1 and %d.\n", MAX_NODES); //입력된 노드의 개수가 0개 이하일 때 오류 메세지를 출력하는 if문.
        return 1;
    }

    printf("Enter the number of edges in the graph: "); //1개 이상의 노드 개수를 입력받으면 엣지의 개수도 입력받고,
    scanf_s("%d", &numEdges);

    if (numEdges < 0 || numEdges >(numNodes * (numNodes - 1) / 2)) {
        printf("Invalid number of edges. Please enter a non-negative value up to %d.\n", numNodes * (numNodes - 1) / 2); //if문을 통해 엣지의 개수가 0개 이상인지 확인한 후 오류 메세지를 출력하는 부분.
        return 1;
    }

    struct Graph* graph = createGraph(numNodes); //createGraph함수로 그래프를 생성.

    printf("Enter the edges (source -> destination):\n"); //엣지가 출발하는 노드부터 도착하는 노드를 차례로 작성하도록 문장을 출력하여,
    int i;
    for (i = 0; i < numEdges; i++) { //i가 위에서 입력받은 엣지의 개수가 될 때까지 for문을 돌리며 노드에서 노드까지의 방향을 입력받음.
        int src, dest;
        scanf_s("%d %d", &src, &dest);

        if (src < 0 || src >= numNodes || dest < 0 || dest >= numNodes) {
            printf("Invalid edge. Node indices should be between 0 and %d.\n", numNodes - 1); //해당 if문에서도 노드의 인덱스가 0보다 큰지 확인하여 오류 문구 출력함.
            return 1;
        }

        addEdge(graph, src, dest);
    }

    topologicalSort(graph); //topologicalSort 함수를 통해 토폴로지 솔팅한 결과를 출력함.

    return 0;
}
