#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <string.h>
using namespace std;

int sizeT;
char *A;
int *T;
int lastIdx = 0;

void increaseSizeT(int newSize);

// stick with pointers or try index (must reserve 0 or " ")

void printHashContents(){
	for(int i=0; i < sizeT; i++){
		if(T[i] == -1){
			printf("%d: \n", i);
		} else {
			printf("%d: %d\n", i, T[i]);
		}
	}
}

void printArrayContents(){
	for(int i=0; i<15*sizeT; ++i){
		if(A[i]=='\0')
			printf("\\");
		else 
			printf("%c", A[i]);
	}
	printf("\n");
}

int simpleHash(string k, int sizeT){
	int idx=0;
	int sum=0;
	while(idx < k.length()){
		sum += (int)k[idx];
		idx++;
	}
	return (sum-2) % sizeT;
}

int hashFunction(string k, int i, int sizeT){
	//cout << "HASH: " << k << " " << i << " " << sizeT << " " << (simpleHash(k, sizeT) + (i * i) % sizeT) << endl;
	return (simpleHash(k, sizeT) + (i * i)) % sizeT;
}

void appendToArray(char *A, string k){
	int i;
	for(i=0; i < k.length(); ++i){
		A[lastIdx + i] = k[i];
	}
	A[lastIdx + i] = '\0';
	lastIdx = lastIdx + i + 1;
}

int search(string k){
	int idx;
	int found;
	for(int i=0; i < sizeT; ++i){
		idx = hashFunction(k, i, sizeT);
		// cout << "HASH " << k << ":" << i << endl;
		//cout << "IDX " << idx << endl;
		if(T[idx] != -1){
			found = 1;
			//cout << "POSSIBLE with " << T[idx] << endl;
			int j=0;
			while(j < k.length()){
				//cout << A[T[idx] + j] << " | " << k[j] << endl;
				//cout << found << " FOUND ITER" << endl;
				if(A[T[idx] + j] != k[j]){
					//cout << "BROKE " << A[T[idx] + j] << " | " << k[j] << endl;
					found = 0;
					break;
				}
				++j;
			}
			//cout << found << " FOUND?" << endl;
			if (found != 0){
				//cout << "WENT THROUGH LOOP" << endl;
			}
			if (found != 0 && A[T[idx] + j] == '\0'){
				found = 1;
				return idx;
			}
		}
	}
	return -1;
}

void deleteWordAtIndex(char *A, int i){
	while(A[i] != '\0'){
		A[i] = '*';
		++i;
	}
}

void deleteString(int *T, char *A, string k){
	int idx = search(k);
	if(idx != -1){
		int arrayIdx = T[idx];
		deleteWordAtIndex(A, arrayIdx);
		T[idx] = -1;
		cout << k << " deleted from slot " << idx << endl;
	}
}

void insert(string k){
	int idx;
	int found = 0;
	int sizeinc = 0;
	for(int i=0; i < sizeT; ++i){
		idx = hashFunction(k, i, sizeT);
		if(T[idx] == -1){
			found = 1;
			if(lastIdx + k.length() + 1 <= 15 * sizeT){
				T[idx] = lastIdx;
				// cout << "TOOK " << i << " TIMES" << endl;
				appendToArray(A, k);
				break;
			} else {
				//cout << "Word doesn't fit in " << 15 * sizeT << endl;
				increaseSizeT(2 * sizeT);
				sizeinc = 1;
				break;
			}
			//insert(k);
			// grow array
			// run again
		}
	} 
	if(!found){
		//cout << "Doesn't hash well" << endl;
		increaseSizeT(2 * sizeT);
		sizeinc = 1;
		// grow array
		// run again
	}
	if(sizeinc == 1){
		// printArrayContents();
		// printHashContents();
		insert(k);
	}
}

void insertWithAllInfo(int *T, int sizeT, int aIndex, string k){
	// tIndex
	int idx;
	int found = 0;
	// cout << '[' << k << ']' << endl;
	for(int i=0; i < sizeT; ++i){
		idx = hashFunction(k, i, sizeT);
		if(T[idx] == -1){
			if(lastIdx + k.length() + 1 <= 15 * sizeT){
				// cout << k << " placed at " << idx << endl;
				T[idx] = aIndex;
				break;
			}
		}
	}
}

int *createHashT(int N){
	int *newHash = (int *)calloc(N, sizeof(int));
	for(int i=0; i < N; ++i){
		//cout << "[" << newHash[i] << "]" << endl;
		newHash[i] = -1;
	}
	
	return &newHash[0];
}

char *createArrayA(int N){
	char *newArray = (char *)calloc(15*N, sizeof(char));
	for(int i=0; i < 15*N; ++i){
		//cout << "[" << newArray[i] << "]" << endl;
		newArray[i] = '.';
	}

	return &newArray[0];

	// cout << "A element: " << sizeof(A[0]) << endl;
	// cout << "A: " << sizeof(A) << endl;
}

void multiplexor(string opCode, string argument){
	if(opCode.length() == 2){
		switch(stoi(opCode)){
			case 10:
				// cout << "INSERT " << argument << "\t(" << opCode << ")" << endl;
				insert(argument);
				// cout << "A" << endl;
				// printArrayContents();
				// cout << "T" << endl;
				// printHashContents();
				break;
			case 11:
				// cout << "DELETE " << argument << "\t(" << opCode << ")" << endl;
				deleteString(T, A, argument);
				// cout << "A" << endl;
				// printArrayContents();
				// cout << "T" << endl;
				// printHashContents();
				break;
			case 12:
				// cout << "SEARCH " << argument << "\t(" << opCode << ")" << endl;
				int f;
				f = search(argument);
				if(f == -1){
					cout << argument << " not found" << endl;
				} else {
					cout << argument << " found at slot " << f << endl;
				}
				break;
			case 13:
				// cout << "PRINT " << "\t\t(" << opCode << ")" << endl;
				printArrayContents();
				printHashContents();
				break;
			case 14: {
				// cout << "CREATE " << argument << "\t(" << opCode << ")" << endl;
				int N = stoi(argument);
				sizeT = N;
				T = createHashT(N);
				A = createArrayA(N);
				// cout << "T" << endl;
				// for(int i=0; i < N; ++i){
				// 	cout << "[" << T[i] << "]" << endl;
				// }
				// cout << "A" << endl;
				// for(int i=0; i < 15*N; ++i){
				// 	cout << "[" << A[i] << "]" << endl;
				// }
				

				break;
			}
			case 15:
				// cout << "COMMENT " << "\t(" << opCode << ")" << endl;
				break;
			default:
				// cout << "[Undefined operation]" << endl;
				break;
		}
	}
}

void parseLine(string line){
	string opCode;
	string argument;
	int i = 0;

	while(i < line.length()){
		if(line[i] != ' '){
			break;
		}
		++i;
	}

	while(i < line.length()){
		if(line[i] == '0' || line[i] == '1' 
		|| line[i] == '2' || line[i] == '3' 
		|| line[i] == '4' || line[i] == '5'){
			opCode += line[i];
			++i;
		} else {
			++i;
			break;
		}
	}

	while(i < line.length()){
		if(line[i] != ' '){
			break;
		}
		++i;
	}

	while(i < line.length()){
		argument += line[i];
		++i;
		// consider how to chop off extra whitespace after the argument
	}

	multiplexor(opCode, argument);

	//cout << opCode << endl;
	//cout << argument << endl;
};

void increaseSizeT(int newSize){
	// create larger A
	char *newA = createArrayA(newSize);
	for(int i=0; i < 15*sizeT; ++i){
		newA[i] = A[i];
	}
	// pass changes to global A
	// A = newA;

	int *newT = createHashT(newSize);

	for(int i=0; i < sizeT; ++i){
		if(T[i] != -1){
			// 
			string word;
			int j = 0;
			while(A[T[i] + j] != '\0'){
				word += A[T[i] + j];
				++j;
			}
			// DON'T INSERT AT T[i], since it must be recalculated
			insertWithAllInfo(newT, newSize, T[i], word);
			// deleteString(T, A, word);
			// Modify the insert code so that it takes in the index of the string ()
		}
	}

	A = newA;
	T = newT;
	sizeT = newSize;
	// delete from T
	// insert to new T
	//

}

int main(int argc, char *argv[]){
	if(argc > 1){
		ifstream inFile;
		string line;
		inFile.open(argv[1]);
		while(getline(inFile, line)){
			parseLine(line);
		}
	}
	// increaseSizeT(20);
	// printArrayContents();
	// printHashContents();

	// for(int i=0; i < 11; ++i){
	// 	cout << hashFunction("jerry", i) << " ";
	// }
	// cout << endl;
	// for(int i=0; i < 11; ++i){
	// 	cout << hashFunction("mary", i) << " ";
	// }
	return 0;
};
