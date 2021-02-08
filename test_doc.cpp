#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

int N = 11;
char T[11] = "ask";
int nextIdxA = 0;
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

int main(){
	T[N-1] = '\0';
	A[99] = '\0';
	printf("Hello world\n");
	char input[] = "alex";
	cout << to_string(simpleHash(input)) << endl;
	printf("%s", T);
	printf("%s", A);
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
