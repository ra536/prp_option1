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
	// printf("%p\n", (int *) &originalArray[lastIdx]);
	return lastIdx+i+1; // add the 0B
}

char *resizeArray(char *originalArray, char *newArray, int oldSize, int newSize){
	for(int i=0; i<oldSize; i++){
		newArray[i] = originalArray[i];
	}
	//strcpy(newArray, originalArray);
	return newArray;
}

void printArrayContentsAddress(char *array, int size){
	int idx=0;

	while(idx < size){
		int wordIdx=0;
		int readIdx=idx;
		char word[30];
		while(array[readIdx] != '\0'){
			word[wordIdx] = array[readIdx];
			// printf("%c\n", word[wordIdx]);
			readIdx++;
			wordIdx++;
		}
		word[wordIdx] = '\0';
		printf("%p: %s\n", &array[idx], word);
		idx=readIdx+1;
	}
}

void printArrayContentsNormal(char *array, int size){
	for(int i=0; i<size; ++i){
		if(array[i]=='\0')
			printf("\\");
		else 
			printf("%c", array[i]);
	}
	printf("\n");
}

int main(){
	char input[] = "alex";
	cout << to_string(simpleHash(input)) << endl;
	cout << endl;

	char first[20];
	char inp[4] = "the";
	int last=0;
	while (20-last >= 4){
		last = appendToArray(inp, 4, first, 20, last);
	}
	char second[50];
	char inp2[6] = "other";

	resizeArray(first, second, 20, 50);
	
	while (50-last >= 6){
		last = appendToArray(inp2, 6, second, 50, last);
	}

	printf("--FIRST-----------\n");
	printArrayContentsNormal(first, 20);
	printArrayContentsAddress(first, 20);

	cout << endl;
	printf("--SECOND----------\n");
	printArrayContentsNormal(second, 50);
	printArrayContentsAddress(second, 50);
	
	cout << endl;
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
