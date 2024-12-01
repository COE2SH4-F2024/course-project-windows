#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200 // Maximum capacity of the array list

#include "objPos.h"

/*
objPosArrayList: A dynamic array-based list to manage objPos objects.
*/

class objPosArrayList {
    private:
        objPos* aList; // Array to store objPos objects
        int listSize; // Current size of the list
        int arrayCapacity; // Maximum capacity of the array

    public:
        objPosArrayList(); // Constructor to initialize the list
        ~objPosArrayList(); // Destructor to clean up resources

        int getSize() const; // Get the current size of the list

        void insertHead(objPos thisPos); // Insert an object at the head
        void insertTail(objPos thisPos); // Insert an object at the tail
        void removeHead(); // Remove the head object
        void removeTail(); // Remove the tail object
        
        objPos getHeadElement() const; // Get the head element
        objPos getTailElement() const; // Get the tail element
        objPos getElement(int index) const; // Get an element at a given index
};

#endif
