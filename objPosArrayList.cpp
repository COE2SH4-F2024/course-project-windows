#include "objPosArrayList.h"
#include <iostream>

// Initializes an empty array list with a predefined maximum capacity
objPosArrayList::objPosArrayList() {
    aList = new objPos[ARRAY_MAX_CAP];
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
}

// Frees memory allocated for the array list
objPosArrayList::~objPosArrayList() {
    delete[] aList;
}

// Returns the current size of the array list
int objPosArrayList::getSize() const {
    return listSize;
}

// Inserts an object at the head of the array list, shifting elements to the right
void objPosArrayList::insertHead(objPos thisPos) {
    if (listSize != 0){
        for (int i = listSize; i > 0; i--){
            aList[i] = aList[i-1];
        }
    }
    aList[0] = thisPos; 
    listSize++;
}

// Inserts an object at the tail of the array list
void objPosArrayList::insertTail(objPos thisPos) {
    aList[listSize] = thisPos;
    listSize++;
}

// Removes the head element of the array list and shifts elements to the left
void objPosArrayList::removeHead() {
    if(listSize == 0) 
        return;

    for(int i = 0; i < listSize - 1; i++)
        aList[i] = aList[i + 1];
    
    listSize--;
}

// Removes the tail element of the array list
void objPosArrayList::removeTail() {
    if(listSize > 0)
        listSize--;
}

// Retrieves the head element of the array list
objPos objPosArrayList::getHeadElement() const {
    return aList[0];
}

// Retrieves the tail element of the array list
objPos objPosArrayList::getTailElement() const {
    return aList[listSize-1];
}

// Retrieves an element at a given index in the array list
objPos objPosArrayList::getElement(int index) const {
    if(index < 0) 
        index = 0;
    return aList[index];
}
