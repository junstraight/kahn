#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

#define MAX_NODES 100

// Structure to represent a directed graph node ���� �׷��� ��带 ��Ÿ���� ����
struct Node {
    int value;
    struct Node* next;
};

// Structure to represent a directed graph ���� �׷����� ��Ÿ���� ����
struct Graph {
    int numNodes;
    struct Node* adjacencyList[MAX_NODES];
    int inDegree[MAX_NODES];
};

// Function to create a new node �� ��带 ����� �Լ�.
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with n nodes ��尡 n���� �׷����� ����� �Լ�.
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

// Function to add an edge between two nodes �� ��� ���̿� ������ �߰��ϴ� �Լ�
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;
    graph->inDegree[dest]++;
}

// Function to perform topological sorting using Kahn's algorithm Kahn �˰����� ����Ͽ� ���� ������ �����ϴ� �Լ�
void topologicalSort(struct Graph* graph) {
    int* result = (int*)malloc(graph->numNodes * sizeof(int));
    int i, j;
    int front = 0, rear = 0;

    // Enqueue nodes with in-degree 0 ������ ������ 0���� ��带 ť �ȿ� ����.
    for (i = 0; i < graph->numNodes; i++) {
        if (graph->inDegree[i] == 0) {
            result[rear++] = i;
        }
    }

    // Process until all nodes have been visited ����ڰ� �Է��� ���� ��ŭ�� ��� ��带 �湮�� ������ while�� ����.
    while (front < rear) {
        int current = result[front++];
        struct Node* temp = graph->adjacencyList[current];

        // Reduce in-degree of adjacent nodes indegree�� 0���� ��带 ���� ������ �ش� ��忡 ������ ����� indegree�� �ٿ���.
        while (temp != NULL) {
            graph->inDegree[temp->value]--;
            if (graph->inDegree[temp->value] == 0) {
                result[rear++] = temp->value;
            }
            temp = temp->next;
        }
    }

    // Check for a cycle in the graph �׷����� ����Ŭ�� �ִ��� Ȯ���ϰ�, ����Ŭ�� �߰ߵǸ� ������ �����.
    if (front != graph->numNodes) {
        printf("Graph contains a cycle!\n");
        return;
    }

    // Print the topological order ������ �����͸� �����.
    printf("Topological Order: ");
    for (j = 0; j < graph->numNodes; j++) {
        printf("%d ", result[j]);
    }
}

int main() {
    int numNodes, numEdges;
    printf("Enter the number of nodes in the graph: ");
    scanf_s("%d", &numNodes); //numNodes�� ����� ������, numEdge�� ������ ������ �Է¹޾� ������.

    if (numNodes <= 0 || numNodes > MAX_NODES) {
        printf("Invalid number of nodes. Please enter a value between 1 and %d.\n", MAX_NODES); //�Էµ� ����� ������ 0�� ������ �� ���� �޼����� ����ϴ� if��.
        return 1;
    }

    printf("Enter the number of edges in the graph: "); //1�� �̻��� ��� ������ �Է¹����� ������ ������ �Է¹ް�,
    scanf_s("%d", &numEdges);

    if (numEdges < 0 || numEdges >(numNodes * (numNodes - 1) / 2)) {
        printf("Invalid number of edges. Please enter a non-negative value up to %d.\n", numNodes * (numNodes - 1) / 2); //if���� ���� ������ ������ 0�� �̻����� Ȯ���� �� ���� �޼����� ����ϴ� �κ�.
        return 1;
    }

    struct Graph* graph = createGraph(numNodes); //createGraph�Լ��� �׷����� ����.

    printf("Enter the edges (source -> destination):\n"); //������ ����ϴ� ������ �����ϴ� ��带 ���ʷ� �ۼ��ϵ��� ������ ����Ͽ�,
    int i;
    for (i = 0; i < numEdges; i++) { //i�� ������ �Է¹��� ������ ������ �� ������ for���� ������ ��忡�� �������� ������ �Է¹���.
        int src, dest;
        scanf_s("%d %d", &src, &dest);

        if (src < 0 || src >= numNodes || dest < 0 || dest >= numNodes) {
            printf("Invalid edge. Node indices should be between 0 and %d.\n", numNodes - 1); //�ش� if�������� ����� �ε����� 0���� ū�� Ȯ���Ͽ� ���� ���� �����.
            return 1;
        }

        addEdge(graph, src, dest);
    }

    topologicalSort(graph); //topologicalSort �Լ��� ���� �������� ������ ����� �����.

    return 0;
}
