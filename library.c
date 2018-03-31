#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "library.h"

/*
*@Author Faisal Burhan.
*@version v1001.
*@date 2018 / march / 25.
*/

Book myBook[1023];
Boolean state = true;
static int i = -1;
char input;

int main(int argc, char const *argv[])
{
	 printf("\n%s\n", "[------ Welcome to the maven e-library -------]");
	 printf("%s\n", "\t      (C) Maven.net 2018.");
	 printf("%s\n\n", "\t        Dev by F.burhan.");
	 displayMenu();
	 while(state){
	 	input = getchar();
	 	switch(input){
	 		case 'A':
	 			addBook();
	 		break;
	 		case 'R':
	 		break;
	 		case 'L':
	 			listBooks(myBook);
	 		break;
	 		case 'S':
	 		break;
	 		case 'Q':
	 			printf("%s\n", "Thanks for using our library!");
	 			state = false;
	 		break;
	 	}
	 }
	return 0;
}

void displayMenu(){
	printf("%s\n", "(H):=> \tDisplay help message.");
	printf("%s\n", "(A):=> \tAdd a book to the library.");
	printf("%s\n", "(R):=> \tRemove a book from the library.");
	printf("%s\n", "(L):=> \tList of books in the library.");
	printf("%s\n", "(S):=> \tSearch book from the library.");
	printf("%s\n", "(Q):=> \tQuit from the library.");
}


void addBook(){
	++i;
	char input[100];
	myBook[i].Id = i;

	printf("\n%s", "Enter book id: ");
	scanf("%s",input);
	//fgets(input, 100, stdin);
	strcpy(myBook[i].bookID, input);
	
	printf("%s", "Enter author name: ");
	scanf("%s", input);
	strcpy(myBook[i].Author, input);
	
	printf("%s", "Enter book title: ");
	scanf("%s", input);
	strcpy(myBook[i].Title, input);
	
	printf("%s", "Enter book description: ");
	scanf("%s", input);
	strcpy(myBook[i].Subject, input);

	printf("\n%s%s%s\n\n", "A new book is added to the library!");
}

void listBooks(Book book[]){
	if (i < 0)printf("%s\n", "Sorry, there are no books to be displayed!");
	for (int in = 0; in < i+1; ++in)
	{
		printf("ID => %d | BOOK_ID => %s | AUTHOR => %s | TITLE => %s | SUBJECT => %s \n",in, book[in].bookID, book[in].Author, book[in].Title, book[in].Subject);
	}
}