#include <stdio.h>
#include <string>
#include <iostream>
#include <string.h>
using namespace std;

int N = 11;
char T[11] = "ask";
int nextIdxA = 0;
int sizeA = 100;
char A[100] = "jeeves";

int simpleHash(char *k){
	int idx=0;
	int sum=0;
	while((int)k[idx] != 0){
		sum += (int)k[idx];
		idx++;
	}
	return (sum-2) % N;
}

int appendToArray(char *word, int wordSize, char *originalArray, int arraySize, int lastIdx){
	// add check on size
	int i=0;
	while(word[i] != '\0'){
		originalArray[lastIdx+i]=word[i];
		i++;
	}
	originalArray[lastIdx+i]='\0';
	printf("%s\n", &originalArray[lastIdx]);
	return lastIdx+i+1; // add the 0B
}

char *resizeArray(char *originalArray, char *newArray, int oldSize, int newSize){
	strcpy(newArray, originalArray);
	return newArray;
}

int main(){
	T[N-1] = '\0';
	A[99] = '\0';
	printf("Hello world\n");
	char input[] = "alex";
	cout << to_string(simpleHash(input)) << endl;
	printf("%s\n", T);
	printf("%s\n", A);
	cout << (int *) &A[0] << endl;
	cout << (int *) &A[1] << endl;
	cout << (int *) &A[99] << endl;
	char boy[4] = "hi!";
	char girl[20];
	strcpy(girl, boy);
	strcat(girl, " how are you?");
	printf("%s", girl);

	char first[20];
	char inp[4] = "the";
	int last=0;
	while (20-last >= 4){
		last = appendToArray(inp, 4, first, 20, last);
	}
	for(int i=0; i<20; ++i){
		if(first[i]=='\0')
			printf("@,");
		else 
			printf("%c,",first[i]);
	}
	return 0;
}

void insertArrayIntoTable(){
	// use hash / quadratic probing to find available spot in T
		// when can you determine that there are no spots?
	// append char array to A (strcpy)
	// place address in T spot (update nextIdxA)
}
// Insert using quadratic probing (i=0, 1, 2, until empty found)
// Delete by searching linearly
// Search by searching linearly
// REPEATS??

// How to check that A is full??
