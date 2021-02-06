#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef struct {
	int studentID;
	char* studentName;
}ElementType;

struct Node {
	ElementType element;
	PtrToNode next;
};

void Insert(ElementType X, List L, Position P);
void Delete(ElementType X, List L);
Position Find(ElementType X, List L);
void PrintList(List L);
List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void DeleteList(List L);

List MakeEmpty(List L) {
	L = (List)malloc(sizeof(struct Node));
	L->next = NULL;
	return L;
}

int IsLast(Position P, List L) {
	return P->next == NULL;
}

int IsEmpty(List L) {
	return L->next == NULL;
}

void DeleteList(List L) {
	Position P, Tmp;

	P = L->next;
	L->next = NULL;
	while (P != NULL) {
		Tmp = P->next;
		free(P->element.studentName);
		free(P);
		P = Tmp;
	}
}

int main() {

	Node* L = MakeEmpty(L);







	return 0;
}