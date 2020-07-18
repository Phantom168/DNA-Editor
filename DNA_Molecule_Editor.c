#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

/***************************************
        Made By: Brijesh Aghav
***************************************/

typedef struct Nucleotide{ //struct for the nucleotide
  char c;
  struct Nucleotide* next; //Next nucleotide
  struct Nucleotide* side; //Link across the chain to another nucleotide.
}Nucleotide;

typedef struct Molecule{ //Struct for the molecule.
  Nucleotide* alphaHead; //start pointer for the alpha chain.
  Nucleotide* betaHead;//start pointer for the beta chain
  int len; //Length of both the alpha and the beta chains.
  int id; //Id of the molecule.
}Molecule;


void initMolecule(Molecule *l); //Function Prototype
int isEmpty(Molecule *l); //Function Prototype
void insertEnd(Molecule* l,char value); //Function Prototype
void deleteEnd(Molecule* l); //Function Prototype
void insert(Molecule* l,int chain,int location, char value); //Function Prototype
void PrintChain(Molecule* l); //Function Prototype
char giveComplimentary(char input); //Function Prototype
void insertFront(Molecule* l,int chain,char value); //Function Prototype
void deleteByPosition(Molecule* l,int position); //Function Prototype
void deleteFront(Molecule* l); //Function Prototype
void delete(Molecule* l,int position); //Function Prototype
void Instructions(); //Function Prototype
Molecule split(Molecule* l); //Function Prototype
void completeMolecule(Molecule* l,int chain); //Function Prototype


int dnaID = 1; //Start the dna id from 1.


int main()
{
  int choice,pos,moleculeID,chainID; //variables to select the options from menu from the user.
  char input;
  Molecule DNA_Array[100]; //Molecule array to store the dna molecules.
  Instructions();
  scanf(" %d",&choice); //Ask the user
  while(choice!=7){
    switch(choice){ //Select the option
      case 1:
        initMolecule(&DNA_Array[dnaID]); //Initiate the molecule struct.
        dnaID++; //increase the ID by one.
      break;

      case 2:
        printf("Enter Molecule ID:"); //Prompt
        scanf(" %d",&moleculeID);
        printf("Enter Chain ID (0 for Alpha, 1 for Beta): "); //Prompt
        scanf(" %d",&chainID);
        printf("Enter Nucleotide(A,T,G,C):"); //Prompt
        scanf(" %c",&input);
        printf("Enter Position:"); //Prompt
        scanf(" %d",&pos);
        insert(&DNA_Array[moleculeID],chainID,pos,input);
        printf("Nucleotide inserted successfully.\n");
      break;

      case 3:
        printf("Enter Molecule ID:"); //Prompt
        scanf(" %d",&moleculeID);
        if(moleculeID<dnaID){
          printf("Enter Position:"); //Prompt
          scanf(" %d",&pos);
            if(pos<=DNA_Array[moleculeID].len&&pos>0){
              delete(&DNA_Array[moleculeID],pos);
            }else{
              printf("Molecule %d does not have the number of nucleotides entered.\n",moleculeID);
            }
        }else{
          printf("Molecule %d does not exist.\n",moleculeID);
        }
      break;

      case 4:
        printf("Enter Molecule ID:"); //Prompt
        scanf(" %d",&moleculeID);
        if(moleculeID<dnaID){
          DNA_Array[dnaID++]=split(&DNA_Array[moleculeID]); //Create a new DNA MOlecule and store the splitted molecule in that.
          DNA_Array[dnaID-1].id=dnaID-1;
          printf("The new molecule has ID %d.",dnaID-1);
        }else{
          printf("Molecule %d does not exist.",moleculeID);
        }
        //DNA_Array[dnaID++]=DNA_Array[moleculeID];
      break;

      case 5:
        printf("Enter Molecule ID:"); //Prompt
        scanf(" %d",&moleculeID);
        PrintChain(&DNA_Array[moleculeID]);
      break;

      case 6:
          for(int i=1;i<dnaID;i++){ //Loop until all the dna molecules are not covered.
            printf("Molecule %d: ",i);
            PrintChain(&DNA_Array[i]); //Print the DNA Molecule.
          }

    }
    Instructions();
    scanf(" %d",&choice); //Scan the user's choice again
  }
}


void initMolecule(Molecule *l)
{
  l->alphaHead=NULL; //initialise the members of the l
  l->betaHead=NULL; //initialise the members of the l
  l->len=0; //initialise the members of the l
  l->id=dnaID; //initialise the members of the l
  printf("Enter String: "); //Prompt
  char input;
  scanf(" %c",&input); //Take the input from the user.
  while(input!='\n'){ //Loop Until the end of the character sequence is not reached
    insertEnd(l,input); //Insert a new node with the character as the nucleotide.
    scanf("%c",&input);
  }
  printf("A DNA Molecule with ID %d has been created.\n",dnaID); //Message stating that task has been completed.
}

int isEmpty(Molecule *l)

{
  return (l->alphaHead==NULL); //Check if the starting node is empty or not.
}

void insertEnd(Molecule* l,char value)
{
  Nucleotide* newAlpha=(Nucleotide*)malloc(sizeof(Nucleotide)); //Allocate memory for the new nucleotide.
  Nucleotide* newBeta = (Nucleotide*)malloc(sizeof(Nucleotide)); //Allocate memory for the new nucleotide.
  if(newAlpha!=NULL){
    l->len++; //Increment the number of elements in the list.
    if(isEmpty(l)){
      newAlpha->c=value; //Set the nucleotide value.
      newBeta->c=giveComplimentary(value);
      newBeta->side=newAlpha;
      newAlpha->side=newBeta;
      newAlpha->next=NULL;
      newBeta->next=NULL;
      l->alphaHead=newAlpha;
      l->betaHead=newBeta;
    }else{
      Nucleotide* aptr = l->alphaHead;
      Nucleotide* bptr = l->betaHead;

      while(aptr->next!=NULL){ //Reach the end of the current list.
        aptr=aptr->next;
      }

      while(bptr->next!=NULL){ //Reach the end of the current list.
        bptr=bptr->next;
      }

      aptr->next=newAlpha;
      bptr->next=newBeta;
      newBeta->side=newAlpha;
      newAlpha->side=newBeta;
      newAlpha->c=value;
      newBeta->c =giveComplimentary(value);
      newAlpha->next=NULL;
      newBeta->next = NULL;
    }
  }
}


void deleteEnd(Molecule* l)
{
  if(!isEmpty(l)){ //Check if the list is empty.
    Nucleotide* nextalpha = l->alphaHead->next;
    Nucleotide* currentAlpha = l->alphaHead;
    Nucleotide* nextBeta = l->alphaHead->next;
    Nucleotide* currentBeta = l->alphaHead;

    while(nextalpha->next!=NULL){
      currentAlpha=nextalpha;
      nextalpha=nextalpha->next;
    }
    while(nextBeta->next!=NULL){
      currentBeta=nextBeta;
      nextBeta=nextBeta->next;
    }
    currentAlpha->next=NULL;
    currentBeta->next=NULL;
    free(nextalpha);
    free(nextBeta);
    (l->len)--;
  }
}

void insert(Molecule* l,int chain,int location, char value)
{
  if(location>l->len+1||location<1){ //Check that position enterec by the user is below the number of nodes currently the list has.
    printf("invalid location");
  }else{
    if(location ==1){
      insertFront(l,chain,value);
    }else{
      int currentNucleotideLocation=1;
      l->len++;
      Nucleotide* ptr = l->alphaHead;
      Nucleotide* bptr = l->betaHead;
      Nucleotide* newAlpha = (Nucleotide*)malloc(sizeof(Nucleotide)); //Allocate memory for the new nucleotide.
      Nucleotide* newBeta = (Nucleotide*)malloc(sizeof(Nucleotide)); //Allocate memory for the new nucleotide.
      if(chain==0){
        newAlpha->c=value;
        newBeta->c=giveComplimentary(value);
      }else{
        newAlpha->c=giveComplimentary(value);
        newBeta->c=value;
      }
      while(currentNucleotideLocation+1!=location){
        ptr=ptr->next;
        bptr=bptr->next;
        currentNucleotideLocation++;
      }
      newAlpha->next=ptr->next;
      newBeta->next=bptr->next;
      newBeta->side=newAlpha;
      newAlpha->side=newBeta;
      ptr->next=newAlpha;
      bptr->next=newBeta;
    }
  }
}

void PrintChain(Molecule* l)
{
  Nucleotide* ptr = l->alphaHead;
  if(ptr==NULL){
    printf("The Molecule is empty");
  }else{
    printf("The DNA Molecule with ID %d and %d nucleotides is:\n",l->id,l->len);
    while(ptr->next!=NULL){
      printf("%c-",toupper(ptr->c));
      ptr=ptr->next;
    }
    printf("%c",toupper(ptr->c));
  }
  printf("\n");
  for(int i=0;i<l->len;i++){
    printf("| ");
  }
  printf("\n");

  ptr = l->betaHead;
    while(ptr->next!=NULL){
      printf("%c-",toupper(ptr->c));
      ptr=ptr->next;
    }
    printf("%c",toupper(ptr->c));

    printf("\n\n");


}

void insertFront(Molecule* l,int chain,char value)
{
  Nucleotide* newAlpha = (Nucleotide*)malloc(sizeof(Nucleotide)); //Allocate memory for the new nucleotide.
  Nucleotide* newBeta = (Nucleotide*)malloc(sizeof(Nucleotide)); //Allocate memory for the new nucleotide.

  if(newAlpha!=NULL){
    l->len++;
    if(isEmpty(l)){
      if(chain==0){
        newAlpha->c=value;
        newBeta->c=giveComplimentary(value);
      }else{
        newAlpha->c=giveComplimentary(value);
        newBeta->c=value;
      }
      newAlpha->next=NULL;
      newBeta->next=NULL;
      l->alphaHead=newAlpha;
      l->betaHead=newBeta;
      newBeta->side=newAlpha;
      newAlpha->side=newBeta;
    }else{
      if(chain==0){
        newAlpha->c=value;
        newBeta->c=giveComplimentary(value);
      }else{
        newAlpha->c=giveComplimentary(value);
        newBeta->c=value;
      }
      newAlpha->next=l->alphaHead;
      newBeta->next=l->betaHead;
      l->alphaHead=newAlpha;
      l->betaHead=newBeta;
      newBeta->side=newAlpha;
      newAlpha->side=newBeta;
    }
  }
}

char giveComplimentary(char input)
{
  if(input=='a'||input=='A'){
    return 't';
  }else if(input =='t'||input=='T'){
    return 'a';
  }else if(input =='g'||input=='G'){
    return 'c';
  }else if(input =='c'||input=='C'){
    return 'g';
  }
}


void deleteByPosition(Molecule* l,int position)
{
  Nucleotide* currentAlpha = l->alphaHead;
  Nucleotide* currentBeta= l->betaHead;

  for(int i=1;i<position-1;i++){
    currentAlpha=currentAlpha->next;
  }
  for(int i=1;i<position-1;i++){
    currentBeta=currentBeta->next;
  }
  Nucleotide* nextAlpha = currentAlpha->next;
  Nucleotide* nextBeta= currentBeta->next;

  currentAlpha->next=nextAlpha->next;
  currentBeta->next=nextBeta->next;
  free(nextAlpha);
  free(nextBeta);

  (l->len)--;
}

void deleteFront(Molecule* l)
{
  if(!isEmpty(l)){
    Nucleotide* aptr = l->alphaHead;
    Nucleotide* bptr = l->betaHead;
    l->alphaHead=l->alphaHead->next;
    l->betaHead=l->betaHead->next;
    free(aptr);
    free(bptr);
    (l->len)--;
  }
}

void delete(Molecule* l,int position)
{
  if(position==1){
    deleteFront(l);
  }else{
    deleteByPosition(l,position);
  }
}

void Instructions()
{
  printf("\nMenu\n");
  printf("1.Create Molecule\n");
  printf("2.Insert\n");
  printf("3.Delete\n");
  printf("4.Split\n");
  printf("5.Print Molecule\n");
  printf("6.Print All Molecule\n");
  printf("7.Quit\n\n");

}

Molecule split(Molecule* l)
{
  Molecule duplicate;

  Nucleotide* temp1;
  Nucleotide* temp2;
  temp1=l->alphaHead;
  Nucleotide* newBetaHead;
  for(int i=1;temp1!=NULL;i++){
    if(i==1){
      Nucleotide* newNucleotide = (Nucleotide*)malloc(sizeof(Nucleotide)); //Allocate memory for the new nucleotide.
      newNucleotide->c=giveComplimentary(temp1->c);
      newNucleotide->next=NULL;
      newBetaHead= newNucleotide;
      temp2=newNucleotide;
    }else{
      Nucleotide* newNucleotide = (Nucleotide*)malloc(sizeof(Nucleotide)); //Allocate memory for the new nucleotide.
      newNucleotide->c=giveComplimentary(temp1->c);
      temp2->next = newNucleotide;
      newNucleotide->next=NULL;
      newNucleotide->side=temp1;
      temp2=newNucleotide;
    }
    temp1=temp1->next;

  }
  duplicate.betaHead=newBetaHead;
  duplicate.len=l->len;
  completeMolecule(l,1);
  completeMolecule(&duplicate,0);

  return duplicate;
}

void completeMolecule(Molecule* l,int chain)
{
  Nucleotide* temp1;
  Nucleotide* newHead;
  Nucleotide* temp2;
  if(chain==0){
    temp1 = l->betaHead;
  }else{
    temp1=l->alphaHead;
  }

  for(int i=1;temp1!=NULL;i++){
    if(i==1){
      Nucleotide* newNucleotide = (Nucleotide*)malloc(sizeof(Nucleotide)); //Allocate memory for the new nucleotide.
      newNucleotide->c=giveComplimentary(temp1->c);
      newNucleotide->next=NULL;
      newNucleotide->side=temp1;
      temp1->side=newNucleotide;
      newHead=newNucleotide;
      temp2=newNucleotide;
    }else{
      Nucleotide* newNucleotide = (Nucleotide*)malloc(sizeof(Nucleotide)); //Allocate memory for the new nucleotide.
      newNucleotide->c=giveComplimentary(temp1->c);
      newNucleotide->next=NULL;
      newNucleotide->side=temp1;
      temp1->side=newNucleotide;
      temp2->next=newNucleotide;
      temp2=newNucleotide;
    }
    temp1=temp1->next;

  }

  if(chain==0){
    l->alphaHead=newHead;
  }else{
    l->betaHead=newHead;
  }


}
