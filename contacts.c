#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct of contactNodeLevel
// Array of 26 contactNodeLevel pointers
// Counter of number words with char at set index
typedef struct contactNodeLevel {
	long numLetters_;
	struct contactNodeLevel* letters_[26];
} Node;

// Allocates memory in heap for Node
// Instantiates value of numLetters_ = 0
// Pointer of each index in Node array set to NULL
Node* initNode() {
	return (Node *)calloc(1, sizeof(Node));
	// Node* node = (Node *)malloc(sizeof(Node));
	// node->numLetters_ = 0;
	// int index;
	// for (index = 0; index < 26; ++index) {
	// 	node->letters_[index] = NULL;
	// }
	// return node;
}

// Function adds word into trie
void addWord(Node* root, char* word) {
	int index = 0;
	if (word[index] != '\0' && word[index] != '\n') {
		int asciiVal;
		// While there are more char in word
		while (word[index] != '\0' && word[index] != '\n') {
			asciiVal = (int)word[index] - 97;
			// If char has not been added into trie yet add char to trie
			if (root->letters_[asciiVal] == NULL) {
				root->letters_[asciiVal] = initNode();
			}
			// Increment number of letters and point root to next char in word
			++root->numLetters_;
			root = root->letters_[asciiVal];
			++index;
		}
		++root->numLetters_;
	}
}

// Function finds word in trie and return num_letters
long findWord(Node* root, char* word) {
	int index = 0;
	if (word[index] != '\0' && word[index] != '\n') {
		int asciiVal;
		// While there are more char in word
		while (word[index] != '\0' && word[index] != '\n') {
			asciiVal = (int)word[index] - 97;
			// If substring does not exist in trie
			if (root->letters_[asciiVal] == NULL) {
				return 0;
			}
			// Otherwise change root to next char
			root = root->letters_[asciiVal];
			++index;
		}
		return root->numLetters_;
	}
	return 0;
}

// Function clears memory allocated to Node in heap
void freeMemory(Node* root) {
	int i;
	for (i = 0; i < 26 && root->numLetters_ >= 1; ++i) {
		if (root->letters_[i] != NULL) {
			root->numLetters_ -= root->letters_[i]->numLetters_;
			freeMemory(root->letters_[i]);
		}
	}
	free(root);
	root = NULL;
}

int main() {
	long numCommands;
	// Get number of commands to accept
	scanf("%li\n", &numCommands);
	if (numCommands >= 1 && numCommands <= 100000) {
		Node* root_ = initNode();
		int currNum;
		int addFunction;
		int findFunction;
		char add[4];
		strcpy(add, "add");
		char find[5];
		strcpy(find, "find");
		for (currNum = 0; currNum < numCommands; ++currNum) {
			char input[27];
			fgets(input, 27, stdin);
			char* line = strtok(input, " ");
			addFunction = strcmp(line, add);
			findFunction = strcmp(line, find);
			// If user adds word to trie
			if (addFunction == 0) {
				line = strtok(NULL, "\0");
				if (line[0] != '\n' && line[0] != '\0') {
					addWord(root_, line);
				}
			// If user is looking for word in trie
			} else if (findFunction == 0) {
				line = strtok(NULL, "\0");
				if ((root_->numLetters_ > 0) && 
					(line[0] != '\n'  && line[0] != '\0')) {
					printf("%li\n", findWord(root_, line));
				} else {
					printf("0\n");
				}
			}
		}
		// Free memory in heap
		freeMemory(root_);
	}
	return 0;
}
