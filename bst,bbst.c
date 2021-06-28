#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// BST
typedef struct BSTNode
{
    int data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

// 1. search
// 평균 logN, 편향트리면 O(n)
BSTNode *findInBST(BSTNode *root, int data)
{
    if (root == NULL)
        return NULL;
    while (root)
    {
        if (root->data == data)
        {
            return root;
        }
        else if (root->data > data)
        {
            root = root->left;
        }
        else if (root->data < data)
        {
            root = root->right;
        }
    }
    return NULL;
}

// recursive
BSTNode *find(BSTNode *root, int data)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->data > data)
    {
        return find(root->left, data);
    }
    else if (root->data < data)
    {
        return find(root->right, data);
    }
    return root;
}

// 2. insert
// 평균 logN, 최악 O(n)-편향트리
// 위치잡기 -> 트리 높이만큼
BSTNode *bstInsert(BSTNode *root, int data)
{
    if (!root)
    {
        root = (BSTNode *)malloc(sizeof(BSTNode));
        if (root == NULL)
        {
            printf("Memory Error");
            return NULL;
        }
        else
        {
            root->data = data;
            root->left = root->right = NULL;
        }
    }
    else if (root->data > data)
    {
        root->left = bstInsert(root->left, data);
    }
    else if (root->data < data)
    {
        root->right = bstInsert(root->right, data);
    }
    return root;
}

BSTNode *FindMax(BSTNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root;
};

// 3. Delete
// 평균 logN, 최악 O(n)
BSTNode *Delete(BSTNode *root, int data)
{
    BSTNode *temp;
    if (root == NULL)
    {
        printf("Element not there in tree");
        return NULL;
    }
    else if (root->data > data)
    {
        root->left = Delete(root->left, data);
    }
    else if (root->data < data)
    {
        root->right = Delete(root->right, data);
    }
    else
    {
        if (root->right && root->left)
        {
            temp = FindMax(root->left);
            root->data = temp->data;
            root->left = Delete(root->left, root->data);
        }
        else
        {
            if (root->right == NULL)
            {
                root = root->left;
            }
            else if (root->left == NULL)
            {
                root = root->right;
            }
            free(root);
        }
    }
    return root;
}

// AVL
typedef struct AVLTreeNode
{
    int data;
    struct AVLTreeNode *left;
    struct AVLTreeNode *right;
    int height;
} AVLTreeNode;

// 보조연산 - 높이구하기, 최대값, 최소값
int height(AVLTreeNode *root)
{
    if (root == NULL)
    {
        return -1;
    }
    return root->height;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

// 회전 ; O(1)
// - 단순회전
AVLTreeNode *SingleRotateLeft(AVLTreeNode *target)
{ // 위반된 노드(target)
    AVLTreeNode *temp = target->left;
    target->left = temp->right;
    temp->right = target;
    target->height = max(height(target->left), height(target->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    return temp;
}

AVLTreeNode *SingleRotateRight(AVLTreeNode *target)
{
    AVLTreeNode *temp = target->right;
    target->right = temp->left;
    temp->left = target;
    target->height = max(height(target->left), height(target->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    return temp;
}

// - 이중회전
AVLTreeNode *RotateLeftRight(AVLTreeNode *target)
{
    target->left = SingleRotateRight(target->left);
    return SingleRotateLeft(target);
}

AVLTreeNode *RotateRightLeft(AVLTreeNode *target)
{
    target->right = SingleRotateLeft(target->right);
    return SingleRotateRight(target);
}

// AVL - insert
AVLTreeNode *AVLInsert(AVLTreeNode *root, int data)
{
    if (!root)
    {
        root = (AVLTreeNode *)malloc(sizeof(AVLTreeNode));
        if (root == NULL)
        {
            printf("Memory Error");
            return NULL;
        }
        else
        {
            root->data = data;
            root->left = root->right = NULL;
            root->height = 0;
        }
    }
    else if (root->data > data)
    {
        root->left = AVLInsert(root->left, data);
        if (height(root->left) - height(root->right) == 2)
        {
            if (root->left->data > data)
            {
                root = SingleRotateLeft(root);
            }
            else
            {
                root = RotateLeftRight(root);
            }
        }
    }
    else if (root->data < data)
    {
        root->right = AVLInsert(root->right, data);
        if (height(root->right) - height(root->left) == 2)
        {
            if (root->right->data < data)
            {
                root = SingleRotateRight(root);
            }
            else
            {
                root = RotateRightLeft(root);
            }
        }
    }
    root->height = max(height(root->left), height(root->right)) + 1;
    return root;
}

// AVL - find
AVLTreeNode *findInAVL(AVLTreeNode *root, int data)
{
    if (root == NULL)
        return NULL;
    while (root)
    {
        if (root->data == data)
        {
            return root;
        }
        else if (root->data > data)
        {
            root = root->left;
        }
        else if (root->data < data)
        {
            root = root->right;
        }
    }
    return NULL;
}

// 메모리 할당 해제
void *freeBST(BSTNode *root)
{
    if (root)
    {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
    return NULL;
}

void *freeAVL(AVLTreeNode *root)
{
    if (root)
    {
        freeAVL(root->left);
        freeAVL(root->right);
        free(root);
    }
    return NULL;
}

// 반복수행
BSTNode *BSTRepeat(BSTNode *rootBST, int numOfRepeat, char *command)
{
    int random;
    if (!strcmp(command, "insert"))
    {
        for (int i = 0; i < numOfRepeat; i++)
        {
            random = (rand() << 7 | rand()) % (numOfRepeat + 1);
            rootBST = bstInsert(rootBST, random);
        }
    }
    else if (!strcmp(command, "find"))
    {
        for (int i = 0; i < numOfRepeat; i++)
        {
            random = (rand() << 7 | rand()) % (numOfRepeat + 1);
            findInBST(rootBST, random);
        }
    }
    else
    {
        for (int i = 0; i < numOfRepeat; i++)
        {
            rootBST = bstInsert(rootBST, i);
        }
    }
    return rootBST;
}

AVLTreeNode *AVLRepeat(AVLTreeNode *rootAVL, int numOfRepeat, char *command)
{
    int random;
    if (!strcmp(command, "insert"))
    {
        for (int i = 0; i < numOfRepeat; i++)
        {
            random = (rand() << 7 | rand()) % (numOfRepeat + 1);
            rootAVL = AVLInsert(rootAVL, random);
        }
    }
    else if (!strcmp(command, "find"))
    {
        for (int i = 0; i < numOfRepeat; i++)
        {
            random = (rand() << 7 | rand()) % (numOfRepeat + 1);
            findInAVL(rootAVL, random);
        }
    }
    else
    {
        for (int i = 0; i < numOfRepeat; i++)
        {
            rootAVL = AVLInsert(rootAVL, i);
        }
    }
    return rootAVL;
}

int main(void)
{
    const int numOfRepeat = 100000;
    srand((unsigned int)time(NULL));
    BSTNode *rootBST = NULL;
    AVLTreeNode *rootAVL = NULL;
    clock_t start, end;

    // (1) 랜덤데이터 삽입, 1회 수행시간(십만)
    // - BST
    start = clock();
    rootBST = BSTRepeat(rootBST, numOfRepeat, "insert");
    end = clock();
    printf("BST, random data insert time: %.5f\n", (float)(end - start) / numOfRepeat);
    rootBST = freeBST(rootBST);

    // - AVL
    start = clock();
    rootAVL = AVLRepeat(rootAVL, numOfRepeat, "insert");
    end = clock();
    printf("AVL, random data insert time: %.5f\n", (float)(end - start) / numOfRepeat);
    rootAVL = freeAVL(rootAVL);

    // (1) 랜덤데이터 삽입, find 1회 수행시간 (십만~백만)
    // - BST
    for (int i = numOfRepeat; i <= numOfRepeat * 10; i += numOfRepeat)
    {
        rootBST = BSTRepeat(rootBST, i, "insert");
        start = clock();
        BSTRepeat(rootBST, i, "find");
        end = clock();
        printf("BST, random data find time: %.5f\n", (float)(end - start) / i);
        rootBST = freeBST(rootBST);
    }

    printf("\n");
    // - AVL
    for (int i = numOfRepeat; i <= numOfRepeat * 10; i += numOfRepeat)
    {
        rootAVL = AVLRepeat(rootAVL, i, "insert");
        start = clock();
        AVLRepeat(rootAVL, i, "find");
        end = clock();
        printf("AVL, random data find time: %.5f\n", (float)(end - start) / i);
        rootAVL = freeAVL(rootAVL);
    }

    printf("\n");
    // (2) 정렬데이터 삽입, 1회 수행시간(천)
    // - BST
    start = clock();
    rootBST = BSTRepeat(rootBST, 1000, "project6-(2)");
    end = clock();
    printf("BST, insert time: %.5f\n", (float)(end - start) / 1000);
    rootBST = freeBST(rootBST);

    // - AVL
    start = clock();
    rootAVL = AVLRepeat(rootAVL, 1000, "project6-(2)");
    end = clock();
    printf("AVL, insert time: %.5f\n", (float)(end - start) / 1000);
    rootAVL = freeAVL(rootAVL);

    // (2) 정렬데이터 삽입, find 1회 수행시간(천~오천)
    // - BST
    for (int i = 1000; i <= 5000; i += 1000)
    {
        rootBST = BSTRepeat(rootBST, i, "project6-(2)");
        start = clock();
        BSTRepeat(rootBST, i, "find");
        end = clock();
        printf("BST, find time: %.6f\n", (float)(end - start) / i);
        rootBST = freeBST(rootBST);
    }

    printf("\n");
    // - AVL
    for (int i = 1000; i <= 5000; i += 1000)
    {
        rootAVL = AVLRepeat(rootAVL, i, "project6-(2)");
        start = clock();
        AVLRepeat(rootAVL, i, "find");
        end = clock();
        printf("AVL, find time: %.6f\n", (float)(end - start) / i);
        rootAVL = freeAVL(rootAVL);
    }

    return 0;
}

// 수행시간 비교
// - input: random data(=평균의 경우라 가정)
// 1) insert: BST < AVL  *BST가 적게걸림
// BST, AVL 둘 다, 수행시간은 트리의 높이와 비례하지만,
// AVL은 트리 높이 보장을 위한 추가 연산을 수행하기에,
// BST가 근소하게 빠르다.

// 2) find: AVL < BST
// 트리의 높이를 logn으로 보장하는 AVL이 더빠르다
// BST는 삽입된 데이터의 값과 순서에 따라 가장 최선일 때, AVL과 수행시간이 비슷함.

// - input: sorting data
// 1) insert: AVL < BST
// 2) find : AVL < BST
// BST는 편향트리로, O(n) 수행
// AVL은 트리 높이 보장을 위한 추가연산(단순회전, 이중회전, 높이 업데이트)에 의해 O(logn) 걸림

// [정리]**
// 1) 트리 높이 제한 조건을 맞추기 위해, 추가 연산이 수행되지만 더 짧은 시간복잡도를 가진다. 
// 2) 다루는 데이터의 양이 많을수록, 트리 높이 제한이 시간복잡도에 얼마나 큰 영향을 미치는지 직접 확인할 수 있었다
