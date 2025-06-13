//threaded binary tree, 중위 순회의 결과를 포인터에 미리 기억시킨 트리.
//왼쪽 스레드는 중위 전임, 오른쪽 스레드는 중위 후임. 스택, 재귀를 사용하지 않는 중위 순회 (스택 사용은 반복)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define TRUE 1
#define FALSE 0

typedef struct threadedTree* tP;
typedef struct threadedTree {
	int lThread;
	tP left;
	char val;
	tP right;
	int rThread;
}threadedTree;

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

void mainPrint(tP head);
tP inOrder(tP node);

int main()
{
    head.left = &nodeA; head.right = &head;

    nodeA.left = &nodeB;
    nodeA.right = &nodeC;

    nodeB.left = &nodeD;
    nodeB.right = &nodeE;

    nodeC.left = &nodeF;
    nodeC.right = &nodeG;

    nodeD.left = &nodeH;
    nodeD.right = &nodeI;

    nodeE.left = &nodeB;
    nodeE.right = &nodeA;

    nodeF.left = &nodeA;
    nodeF.right = &nodeC;

    nodeG.left = &nodeC;
    nodeG.right = &head;

    nodeH.left = &head;
    nodeH.right = &nodeD;

    nodeI.left = &nodeD;
    nodeI.right = &nodeB;
    mainPrint(&head);
}

void mainPrint(tP head)
{
    tP node = head;
    printf("%p(%d, %p, %c, %d, %p)\n", node,
        node->lThread, node->left, node->val, node->rThread, node->right);
    while (node->left != head) node = node->left;
    do {
        printf("%p(%d, %p, %c, %d, %p)\n", node,
            node->lThread, node->left, node->val, node->rThread, node->right);
        node = inOrder(node);
    } while (node != head);
}

tP inOrder(tP node)
{
    tP temp = node->right;
    if (node->rThread) {
        return temp; // 스레드라면 후임자 반환
    }
    while (!temp->lThread) temp = temp->left;
    return temp; // 오른쪽 서브트리의 가장 왼쪽 노드
}