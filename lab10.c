#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int isword;
    struct Trie* next[26];
}Trie;

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* new = (struct Trie*)malloc(sizeof(Trie));
    //new->next = (struct Trie*)malloc(sizeof(Trie)*26);
    new->isword = 0;

    for(int i=0;i<26;i++){
        new->next[i] = NULL;
    }

    return new;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{   
    //Check if pTrie is NULL
    if(pTrie == NULL){
        pTrie = createTrie();
    }

    struct Trie* temp = pTrie;
    int letter=0,len = strlen(word), index;

    while(letter != len-1) {

        //Get the index
        index = word[letter]-'a';

        //In case that trie is NULL, I initialize a new one
        if(temp->next[index] == NULL) {
            temp->next[index] = createTrie();
        }

        temp = temp->next[index];
        letter++;

    }

    temp->isword++;

}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* temp = pTrie;
    int letter=0,len = strlen(word), index;

    while(letter != len-1) {

        //Get the index
        index = word[letter]-'a';

        //In case that trie is NULL, I initialize a new one
        if(temp->next[index] == NULL) {
            return 0;
        }

        temp = temp->next[index];
        letter++;

    }

    //The word must have been arrived into, isword is a parameter that counts how many times a word appears in the dictionary, not only 1 and 0;
    return temp->isword;

}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    struct Trie* temp = pTrie;
    for(int i=0;i<26;i++) {
        if(temp->next[i] != NULL) {
            //Traverse all children 
            deallocateTrie(temp->next[i]);
        }

        //At this point, all child should be NULL, so dealloc trie and set to NULL
        free(temp);
        temp = NULL;
        return temp;
    }
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    //Initialize
    FILE* file = fopen(filename,"r");
   /*
    if(file == NULL) {
        printf("Could not read file");
        exit(-1);
    }
*/
    int numword; 
    fscanf(file,"%d",&numword);
    
    char neword[100];
    for(int i=0;i<numword;i++){
        fscanf(file,"%s",neword);
        pInWords[i]= strdup(neword);
        //strcpy(pInWords[i],neword);
    }
    

    printf("\n\n");

    fclose(file);
    return numword;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
    
    //Deallocate mem of word array
    for(int i=0;i<numWords;i++){
        free(inWords[i]);
    }
    //free(inWords);

	return 0;
}