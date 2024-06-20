#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura do nó
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Função para inserir um novo nó no início da lista
void insertAtBeginning(Node** head, int newData) {
    // Criar um novo nó
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = (*head);
    (*head) = newNode;
}

// Função para imprimir todos os elementos da lista
void printList(Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;  // Inicializando a lista como vazia

    insertAtBeginning(&head, 10);
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 30);
    insertAtBeginning(&head, 40);
    insertAtBeginning(&head, 50);

    printf("A lista ligada é: ");
    printList(head);

    return 0;
}
