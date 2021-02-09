#include <stdio.h>
#include <string>
#include <iostream>
#include <string.h>
using namespace std;

int N = 11;
// char T[11] = "ask";
// int nextIdxA = 0;
// int sizeA = 100;
// char A[100] = "jeeves";

int quadraticProbing(){
	// for loop (until all spots visited?
	// calculate simpleHash with extra bit
	// return index to insert into hash table
	return 0;
}

int simpleHash(char *k){
	int idx=0;
	int sum=0;
	while((int)k[idx] != 0){
		sum += (int)k[idx];
		idx++;
	}
	return (sum-2) % N;
}

int hashFunction(char *k, int i){
	return (simpleHash(k) + (i * i)) % N;
}

int needGrow(char *word, int wordSize, char *array, int arraySize, int lastIdx){
	if(wordSize+1 <= arraySize-lastIdx){
		return 1; // FALSE
	}
	else {
		return 0; // TRUE
	}
}

int appendToArray(char *word, int wordSize, char *originalArray, int arraySize, int lastIdx, char *table[], int tableIdx){
	// add check on size
	int i=0;
	while(word[i] != '\0'){
		originalArray[lastIdx+i]=word[i];
		i++;
	}
	originalArray[lastIdx+i]='\0';
	// printf("%p\n", (int *) &originalArray[lastIdx]);
	table[tableIdx]=&originalArray[lastIdx];
	return lastIdx+i+1; // add the 0B
}

char *resizeArray(char *originalArray, char *newArray, int oldSize, int newSize, char *hashTableOld[], char *hashTableNew[], int tableSize){
	for(int i=0; i<oldSize; i++){
		newArray[i] = originalArray[i];
	}
	for(int j=0; j<tableSize; j++){
		printf("PTR: %ld\n", hashTableOld[j]-&originalArray[0]);
		hashTableNew[j] = &newArray[0] + (hashTableOld[j]-&originalArray[0]) ;
	}
	//strcpy(newArray, originalArray);
	return newArray;
}

void addToTable(char *table[], int tableIdx, char *array, int lastIdx){
	table[tableIdx] = &array[lastIdx];	
}

void printHashContents(char *table[], int size){
	for(int i=0; i < size; i++){
		printf("%p: %p  |  %ld: %s (%ld)\n", &table[i], table[i], &table[i]-&table[0], table[i], table[i]-table[0]);
		//printf("%p: %p\n", &table[i], table[i]);
		//printf("%p -- %p\n", &table[0], table[0]);
	}
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
	printf("Location of first: %p\n", &first);
	char inp[4] = "the";
	printf("Location of string 'the': %p\n", &inp);
	int last=0;
	printf("Location of int 'last': %p\n", &last);
	
	char *hashTableFirst[5];
	int i=0;
	while (20-last >= 4){ // and wordsize does not exceed bounds (see needGrow)
		last = appendToArray(inp, 4, first, 20, last, hashTableFirst, i);
		i++;
	}
	char second[50];
	char inp2[6] = "other";
	printf("Location of second: %p\n", &second);
	printf("Location of string 'other': %p\n", &inp2);
	
	char *hashTableSecond[10];

	resizeArray(first, second, 20, 50, hashTableFirst, hashTableSecond, 5);
	
	//i = 0;
	while (50-last >= 6){
		//addToTable(hashTable, i, second, last);
		last = appendToArray(inp2, 6, second, 50, last, hashTableSecond, i);
		i++;
	}

	printf("--FIRST-----------\n");
	printArrayContentsNormal(first, 20);
	printArrayContentsAddress(first, 20);
	
	cout << endl;
	printf("--SECOND----------\n");
	printArrayContentsNormal(second, 50);
	printArrayContentsAddress(second, 50);
	
	cout << endl;
	printf("--Table for FIRST----------\n");
	printHashContents(hashTableFirst, 5);
	
	cout << endl;
	printf("--Table for SECOND----------\n");
	printHashContents(hashTableSecond, 10);

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
