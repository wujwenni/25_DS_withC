#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct threadedTree* threadedPointer;
typedef struct threadedTree {
    short int leftThread;   // 0: leftChild는 실제 자식, 1: leftThread는 이전 노드를 가리킴
    threadedPointer leftChild;  // 왼쪽 자식 노드 또는 스레드
    char data;             // 노드의 데이터
    threadedPointer rightChild; // 오른쪽 자식 노드 또는 스레드
    short int rightThread;  // 0: rightChild는 실제 자식, 1: rightThread는 후속 노드를 가리킴
} threadedTree;

threadedTree head = { FALSE, NULL, '\0', NULL, FALSE };
threadedTree nodeA = { FALSE, NULL, 'A', NULL, FALSE };
threadedTree nodeB = { FALSE, NULL, 'B', NULL, FALSE };
threadedTree nodeC = { FALSE, NULL, 'C', NULL, FALSE };
threadedTree nodeD = { FALSE, NULL, 'D', NULL, FALSE };
threadedTree nodeE = { TRUE, NULL, 'E', NULL, TRUE };
threadedTree nodeF = { TRUE, NULL, 'F', NULL, TRUE };
threadedTree nodeG = { TRUE, NULL, 'G', NULL, TRUE };
threadedTree nodeH = { TRUE, NULL, 'H', NULL, TRUE };
threadedTree nodeI = { TRUE, NULL, 'I', NULL, TRUE };


threadedPointer inorder_1(threadedPointer root);
void inorder_2(threadedPointer root);


int main() 
{
    head.leftChild = &nodeA; head.rightChild = &head;

    nodeA.leftChild = &nodeB;
    nodeA.rightChild = &nodeC;

    nodeB.leftChild = &nodeD;
    nodeB.rightChild = &nodeE;

    nodeC.leftChild = &nodeF;
    nodeC.rightChild = &nodeG;

    nodeD.leftChild = &nodeH;
    nodeD.rightChild = &nodeI;

    nodeE.leftChild = &nodeB;
    nodeE.rightChild = &nodeA;

    nodeF.leftChild = &nodeA;
    nodeF.rightChild = &nodeC;

    nodeG.leftChild = &nodeC;
    nodeG.rightChild = &head;

    nodeH.leftChild = &head;
    nodeH.rightChild = &nodeD;

    nodeI.leftChild = &nodeD;
    nodeI.rightChild = &nodeB;
    inorder_2(&head);
}

void inorder_2(threadedPointer root)
{
    threadedPointer a = root;
    printf("%p(%d, %p, %c, %d, %p)\n", a, a->leftThread, a->leftChild,
        a->data, a->rightThread, a->rightChild);
    while (a->leftChild != root) a = a->leftChild;
    do
    {
        printf("%p(%d, %p, %c, %d, %p)\n", a, a->leftThread, a->leftChild,
            a->data, a->rightThread, a->rightChild);
        a = inorder_1(a);
    } while (a != root);
}

// 중위 순회 함수 (스레드를 이용한 순회)
threadedPointer inorder_1(threadedPointer root) 
{
    threadedPointer a = root->rightChild;
    if (root->rightThread == TRUE)
        return a;
    while (!a->leftThread) a = a->leftChild;
    return a;
}

