/*
 * buttonTable.h
 *
 *  Created on: Feb 13, 2019
 *      Author: JohnnyMa
 */

#ifndef BUTTONTABLE_H_
#define BUTTONTABLE_H_

#include "button.h"

typedef struct {
	Button **array;
	size_t length; //num of items
	size_t size; //allocated size
}ButtonTable;

void insertButton(ButtonTable* buttonTable, Button *button);
ButtonTable* init_buttonTable(int size);
void clearbuttonTable(ButtonTable* buttonTable);
void removeButton(ButtonTable* buttonTable, Button *button);
void drawButtonTable(ButtonTable* buttonTable);
#endif /* BUTTONTABLE_H_ */
