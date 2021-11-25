/*
 * buttonTable.c
 *
 *  Created on: Feb 13, 2019
 *      Author: JohnnyMa
 */

#include "buttonTable.h"

void clearbuttonTable(ButtonTable* buttonTable){ //frees all buttons too
	for(int i = 0; i<buttonTable->length; i++){
		free(buttonTable->array[i]);
	}
	buttonTable->length = 0;
	free(buttonTable);
}

ButtonTable* init_buttonTable(int size){
	ButtonTable* buttonTable = (ButtonTable *)malloc(sizeof(ButtonTable));
	buttonTable->length = 0;
	buttonTable->size = size;
	buttonTable->array = (Button **) malloc(sizeof(Button*)*size);
	return buttonTable;
}

void insertButton(ButtonTable* buttonTable, Button *button){
	// double size if needed (probably won't happen)
	if(buttonTable->length == buttonTable->size){
		buttonTable->size *= 2;
		buttonTable->array	= (Button **)realloc(buttonTable->array, buttonTable->size * sizeof(Button *));
	}
	buttonTable->array[buttonTable->length] = button;
	buttonTable->length++;
}

void removeButton(ButtonTable* buttonTable, Button *button){
	for(int i = 0; i<buttonTable->length; i++){
		if(button == buttonTable->array[i]){
			for(;i<buttonTable->length-1; i++)
				buttonTable->array[i] = buttonTable->array[i+1];
			buttonTable->array[i] = NULL;
			buttonTable->length--;
			free(button);
			return;
		}
	}
}


void drawButtonTable(ButtonTable* buttonTable){
	for(int i = 0; i<buttonTable->length; i++)
		buttonTable->array[i]->draw();

	return;
}
