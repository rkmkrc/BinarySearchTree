#include <stdio.h>
#include<string.h> 
#include<stdlib.h>
#include <math.h>


long int tempTotalAccess = 0;
long int tempTotalAccessBT = 0;
char *toLower(char* tempWord);
struct node* nonSortedArrBT[2500];



struct node {
	int number;
	char word[100];
	int frequency;
	int height;
	struct node *left, *right; 
};



struct node* createNode(int frequency,char original[],int number,int counter,int totalAccess){
	
	struct node *newNode ;
	newNode = malloc(sizeof(struct node)); 
	newNode->number = number;
	newNode->frequency = frequency;
	strcpy(newNode->word,original) ;		//important..
	newNode->height = 1;				
	
	newNode->left = NULL;
    newNode->right = NULL;
    
    totalAccess = counter*(newNode->frequency);
    tempTotalAccess += totalAccess;

    
    return newNode;
	
}




struct node* insert(struct node *root, int x,char word[],int number,int counter,int totalAccess)					//defining insert func.
{
	char original[50] ;
	strcpy(original,word);
		
    if(root==NULL){
    	
		return createNode(x,original,number,counter,totalAccess);
		
	}
    	    
    else if(strcmp(toLower(word),toLower(root->word)) > 0 ){
    	counter += 1;
    	root->right = insert(root->right, x, original,number,counter,totalAccess);
	}
        
    else if(strcmp(toLower(word),toLower(root->word)) < 0){
    	counter += 1;
		root->left = insert(root->left,x,original,number,counter,totalAccess);
	}
	 

    return root;
}


char *toLower(char* tempWord){																	//lowercase func. to compare strings correctly.
	int i;
  
    for (i = 0; tempWord[i]!='\0'; i++) {
      if(tempWord[i] >= 'A' && tempWord[i] <= 'Z') {
         tempWord[i] = tempWord[i] + 32;
      }
   }
	return tempWord;
}


void readInputs(FILE *file){																	//reads inputs from input text file.
	
	struct node* root;																
	
	
	char eachLine[100];
	char *token;
	

	int a = 0;
	
	int keyForToAddRoot = 1;
	int totalAccess = 0;
	
	while(fgets(eachLine,100,file) ){
		
		token = strtok(eachLine,",");
		int tempNumber = atoi(token);
				
		token = strtok(NULL,",");
		char* tempWord = token;		

													
 				
		token = strtok(NULL,",");
		int tempFrequency = atoi(token);
		
		struct node* tempNode;
		tempNode = malloc(sizeof(struct node));
		tempNode->number = tempNumber;
		strcpy(tempNode->word,tempWord);
		tempNode->frequency = tempFrequency;
		
		nonSortedArrBT[a] = tempNode;
		
		
		
		if(keyForToAddRoot == 1){
			
			root = createNode(tempFrequency,tempWord,tempNumber,1,totalAccess);
			keyForToAddRoot = 2;
			a += 1;
			continue;
		}
		
		insert(root,tempFrequency,tempWord,tempNumber,1,totalAccess);
		
		a += 1;
	}

	fclose(file);
	inorder(root);
	printf("\n b)\n\n--Total Access Time for Binary Search Tree with key Word = %d --\n",tempTotalAccess);
	
	
}




void inorder(struct node* root){  																		// LNR traversal.
	
    if (root != NULL) { 
    	
        inorder(root->left); 
        printf("	%s  -   %d -    %d \n", root->word, root->number, root->frequency); 
        inorder(root->right); 
    } 
    
} 
void preOrder(struct node *root) 																		//NLR traversal.
{ 
    if(root != NULL) 
    { 
        printf("	%d  -  %s  -  %d \n",root->frequency,root->word,root->number); 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
} 





int main() {

	printf("\n a)	Word  -  Number  -  Frequency\n-----------------------------------------\n");
	FILE* file ;
	file = fopen("input.txt", "r");
	
	

	readInputs(file);
	
	int size = 0;
	int i = 0;
	while(nonSortedArrBT[i] != NULL){
			size += 1;
			i += 1;
		
	}
	
	


   int k, j; 
   int n = size;
   for (k = 0; k < n-1; k++){
   
  
          
       for (j = 0; j < n-k-1; j++){																//Sorting array with respect to their frequencies.
	     
           if (nonSortedArrBT[j]->frequency < nonSortedArrBT[j+1]->frequency){
		   	
		   	
			   	char tempName[100];
				int tempNum ;
				int tempFre ;
				strcpy(tempName,nonSortedArrBT[j]->word);
				tempNum = nonSortedArrBT[j]->number;
				tempFre = nonSortedArrBT[j]->frequency;
				
				strcpy(nonSortedArrBT[j]->word,nonSortedArrBT[j+1]->word);
				nonSortedArrBT[j]->number = nonSortedArrBT[j+1]->number;
				nonSortedArrBT[j]->frequency = nonSortedArrBT[j+1]->frequency;
				
				strcpy(nonSortedArrBT[j+1]->word,tempName);
				nonSortedArrBT[j+1]->number = tempNum;
				nonSortedArrBT[j+1]->frequency = tempFre;
				
	   
		   } 
		}
   }  
               
 
	printf("\n-------------------------------------------------------------------------\n\n");
	
	
	
	
	tempTotalAccess = 0;
	

	struct node* rt = nonSortedArrBT[0];     
	int totAccessTime = 0;     
	for (i=0; i<size; i++){ 																				//Creating Binary Tree.
		if(i < size){
		
 		 nonSortedArrBT[i]->left = nonSortedArrBT[i*2+1];       
 		 nonSortedArrBT[i]->right = nonSortedArrBT[i*2+2];        
		 totAccessTime += ((int)log2(i+1)+1)*nonSortedArrBT[i]->frequency;    
		}
	}    
	
	printf("\n c) \n	Preorder Shown of Binary Tree\n\n	Frequency  -  Word  -  Number\n-------------------------------------------------------------------------\n");
	preOrder(rt);    

	printf("\n-------------------------------------------------------------------------\nd)\n");
	printf("	Total Access Time for Binary Tree = %ld \n",totAccessTime);
	
	
	printf("\n-------------------------------------------------------------------------\ne)\n");
	printf("\n	In part a) I constructed a Binary Search Tree with the key word and because of\n  the total access time is related to their frequencies and their depths, total access time became bigger than\n  Binary Tree which is I constructed to minimize the total access time with the key Frequencies.\n\n\n  ");
	
		


	
	
	return 0;
}
