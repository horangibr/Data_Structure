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

typedef struct Node {
	ElementType element;
	PtrToNode next;
};

int Insert(ElementType X, List L, FILE* fp2);
int Delete(ElementType X, List L);
Position Find(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
//void PrintList(List L);
List MakeEmpty();
int IsEmpty(List L);
int IsLast(Position P, List L);
void DeleteList(List L);


int main() {

	List L = MakeEmpty();


	FILE* fp1, * fp2;
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");


	char cmd;
	int num;


	while (fscanf(fp1, "%c", &cmd) != EOF) {
		char first[20];
		char second[20];

		if (cmd == 'i') {
			fscanf(fp1, "%d%s%s", &num, first, second);

			ElementType X;

			X.studentName = (char*)malloc(strlen(first) + 1 + strlen(second) + 1);

			X.studentID = num;

			char str[50] = "";

			strcpy(str, first);

			strcat(str, " ");

			strcat(str, second);

			strcpy(X.studentName, str);

			if (Insert(X, L, fp2) == 1) {

				Position P = L->next;

				fprintf(fp2, "Current List > ");

				while (P != NULL) {

					fprintf(fp2, "%d %s\n", P->element.studentID, P->element.studentName);
					P = P->next;
				}
				fprintf(fp2, "\n");
			}
			//printf("%c %d %s %s\n", cmd, num, first, second);
		}
		if (cmd == 'd') {
			fscanf(fp1, "%d", &num);
			ElementType X;
			X.studentID = num;

			if (Delete(X, L, fp2) == 1) {
				Position P = L->next;
				fprintf(fp2, "Deletion Success : %d\n", X.studentID);
				fprintf(fp2, "Current List > ");
				while (P != NULL) {
					fprintf(fp2, "%d %s", P->element.studentID, P->element.studentName);
					P = P->next;
				}
				fprintf(fp2, "\n");
			}
		}
		/*if (cmd == 'f') {
			fscanf(fp1, "%d", &num);
			printf("%c %d\n", cmd, num);
		}
		if (cmd == 'p') {
			printf("p\n");
		}*/
	}
	fclose(fp1);
	fclose(fp2);

	return 0;
}
List MakeEmpty() {
	List L = (List)malloc(sizeof(struct Node));
	if (L == NULL) {
		printf("out of space!\n");
		return NULL;
	}
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
int Insert(ElementType X, List L, FILE* fp2) {
	Position TmpCell;
	Position P;

	TmpCell = (List)malloc(sizeof(struct Node));
	if (TmpCell == NULL) {
		printf("Out of space!!!");
		return -1;
	}
	if (Find(X, L) == NULL) {
		TmpCell->element.studentName = (char*)malloc(strlen(X.studentName) + 1);
		TmpCell->element.studentID = X.studentID;
		strcpy(TmpCell->element.studentName, X.studentName);
		P = L;
		while (P->next != NULL && P->next->element.studentID < X.studentID) {
			P = P->next;
		}
		TmpCell->next = P->next;
		P->next = TmpCell;
		fprintf(fp2, "Insertion Success : %d\n", X.studentID);
		return 1;
	}
	else {
		fprintf(fp2, "Insertion Failed. ID %d already exists.\n", X.studentID);
		return 0;
	}

}

int  Delete(ElementType X, List L, FILE* fp2) {
	Position P, TmpCell;

	if (FindPrevious(X, L) == NULL) {
		fprintf(fp2, "Deletion Failed : Student ID %d is not in the list.", X.studentID);
		return 0;
	}
	else {
		P = FindPrevious(X, L);
		if (!IsLast(P, L)) {
			TmpCell = P->next;
			P->next = TmpCell->next;
			free(TmpCell->element.studentName);
			free(TmpCell);
			return 1;
		}
	}
}

Position Find(ElementType X, List L) {
	Position P;

	P = L->next;
	while (P != NULL && P->element.studentID != X.studentID) {
		P = P->next;
	}
	return P;
}

Position FindPrevious(ElementType X, List L) {
	Position P;
	P = L;
	while (P->next != NULL && P->next->element.studentID != X.studentID) {
		P = P->next;
	}
	return P;
}

