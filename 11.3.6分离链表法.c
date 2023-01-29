#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;
typedef struct ListNode *Position, *List;
struct ListNode {
    ElementType Element;
    Position Next;
};

typedef struct HashTbl *HashTable;
struct HashTbl
{
    int TableSize;
    List TheLists;
};

HashTable Initialize(int TableSize){
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct HashTbl));
    if (H == NULL){
        printf("空间溢出！！");
    }
    H->TableSize = TableSize;
    H->TheLists = (struct ListNode *)malloc(sizeof(struct ListNode)* H->TableSize);
    if (H->TheLists == NULL){
        printf("空间溢出！！");
    }
    for(i = 0; i < H->TableSize; i++){
        H->TheLists[i].Next = NULL;
    }
    return H;
}

int Hash(ElementType Key){
    return Key % 11;
}
Position Find(ElementType Key, HashTable H){
    Position P;
    int Pos;

    Pos = Hash(Key);
    P = H->TheLists[Pos].Next;
    while(P != NULL && P->Element != Key){
        P = P->Next;
    }
    return P;
}

void Insert(ElementType Key, HashTable H){
    Position Pos;
    Pos = Find(Key, H);
    if(Pos == NULL){
        int P = Hash(Key);
        struct ListNode * node = (struct ListNode *)malloc(sizeof(struct ListNode));
        node->Element = Key;
        node->Next = NULL;

        struct ListNode * pre = &H->TheLists[P];
        node->Next = pre->Next;
        pre->Next = node;

    }
}

int main()
{
    int nums[14] = {47, 7, 29, 11, 16, 92, 22, 8, 3, 50, 37, 89, 94, 21};
    HashTable H = Initialize(11);
    for(int i = 0; i < 14; i++){
        Insert(nums[i], H);
    }
    for(int i = 0; i < H->TableSize; i++){
        struct ListNode * p = H->TheLists[i].Next;
        while(p){
            printf("%d ", p->Element);
            p = p->Next;
        }
        printf("\n");
    }
    struct ListNode * node = Find(21, H);
    if(node){
        printf("%d\n", node->Element);
    }
    else{
        printf("404\n");
    }


    return 0;
}
