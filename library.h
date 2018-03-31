#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifndef LIBRARY_H
#define SYMBOL LIBRARY_H

#define _MAX_SIZE 1023

typedef char String[_MAX_SIZE];
typedef enum { false, true }Boolean;
typedef struct Books{
	int Id;
	String bookID;
	String Author;
	String Title;
	String Subject;
}Book;

//function declaration.
void displayMenu();
void addBook();
void removeBook(int pos);
void listBooks(Book book[]);
#endif //LIBRARY_H