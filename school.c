/*
 * school.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Mohamed Tarek Elsaid
 */

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "Types.h"
#include "ErrorState.h"
#include "school.h"
#include "Config.h"

ErrorState_t List_init(List_t* pl) {
    pl -> pHead     = NULL;
    pl -> pTail     = NULL;
    pl -> ListSize  =  0  ;
    return SUCCESS;
}

ErrorState_t List_insertStudent(List_t* pl, const ListEntry_t* pe) {
    // Create a new node and copy the student data
    ListNode_t* newNode = (ListNode_t*)malloc(sizeof(ListNode_t));
    if (newNode == NULL) {
        return OUT_OF_RANGE_ERR;
    }

    // Copy student ID
    newNode->entry.ID = pe->ID;

    // Copy student Name
    custom_strcpy(newNode->entry.Name, pe->Name);

    // Copy other fields similarly

    newNode->pNext = NULL;
    newNode->pPrev = NULL;

    // Handle the case of an empty list
    if (pl->pHead == NULL) {
        pl->pHead = newNode;
        pl->pTail = newNode;
    } else {
        // Find the correct position to insert the student in alphabetical order
        ListNode_t* current = pl->pHead;
        while (current != NULL && custom_strcmp(current->entry.Name, pe->Name) < 0) {
            current = current->pNext;
        }

        // Insert the student before the current node
        if (current == NULL) {
            newNode->pPrev = pl->pTail;
            pl->pTail->pNext = newNode;
            pl->pTail = newNode;
        } else {
            newNode->pNext = current;
            newNode->pPrev = current->pPrev;
            current->pPrev = newNode;

            if (newNode->pPrev == NULL) {
                pl->pHead = newNode;
            } else {
                newNode->pPrev->pNext = newNode;
            }
        }
    }

    pl->ListSize++;
    return SUCCESS;
}

ErrorState_t List_searchStudent(const List_t* pl, u8 copy_u8ID, ListNode_t** pFoundStudent) {
    // Search for the student by ID
    ListNode_t* current = pl->pHead;
    while (current != NULL) {
        if (current->entry.ID == copy_u8ID) {
            *pFoundStudent = current;
            return SUCCESS;
        }
        current = current->pNext;
    }

    // Student not found
    *pFoundStudent = NULL;
    return NULL_PTR;
}

ErrorState_t List_deleteStudent(List_t* pl, u8 copy_u8ID) {
    // Search for the student by ID
    ListNode_t* foundStudent = NULL;
    ErrorState_t result = List_searchStudent(pl, copy_u8ID, &foundStudent);

    if (result != SUCCESS) {
        return result;
    }

    // Update the pointers of adjacent nodes
    if (foundStudent->pPrev != NULL) {
        foundStudent->pPrev->pNext = foundStudent->pNext;
    } else {
        pl->pHead = foundStudent->pNext;
    }

    if (foundStudent->pNext != NULL) {
        foundStudent->pNext->pPrev = foundStudent->pPrev;
    } else {
        pl->pTail = foundStudent->pPrev;
    }

    free(foundStudent);
    pl->ListSize--;
    return SUCCESS;
}

ErrorState_t  List_printList(const List_t* pl ) {
    ListNode_t* current = pl->pHead;
    while (current != NULL) {
        // Print the student information, ID and Name
        printf("Student ID: %d, Name: %s\n", current->entry.ID, current->entry.Name);

        current = current->pNext;
    }
    return SUCCESS;
}

ErrorState_t  List_freeList(const List_t* pl) {
    List_t* nonConstPl = (List_t*)pl; // Create a non-const copy

    // Now you can modify nonConstPl as needed
    nonConstPl->pHead = NULL;
    nonConstPl->pTail = NULL;
    nonConstPl->ListSize = 0;

    return SUCCESS;
}


// Edit Student Information
ErrorState_t List_editStudent(const List_t* pl, u8 copy_u8ID) {
    // Search for the student by ID
    ListNode_t* foundStudent = NULL;
    ErrorState_t result = List_searchStudent(pl, copy_u8ID, &foundStudent);

    if (result != SUCCESS) {
        return NULL_PTR; // Student not found
    }

    // Edit the student's information
    printf("Enter new age: ");
    scanf("%u", &foundStudent->entry.age);

    printf("Enter new address: ");
    scanf("%s", foundStudent->entry.data.address);

    printf("Enter new phone number: ");
    scanf("%u", &foundStudent->entry.data.phone);

    return SUCCESS;
}

// Update Student's Score
ErrorState_t List_updateScore(const List_t* pl, u8 copy_u8ID) {
    // Search for the student by ID
    ListNode_t* foundStudent = NULL;
    ErrorState_t result = List_searchStudent(pl, copy_u8ID, &foundStudent);

    if (result != SUCCESS) {
        return NULL_PTR; // Student not found
    }

    // Update the student's score
    printf("Enter new math score: ");
    scanf("%u", &foundStudent->entry.degrees.math_deg);

    printf("Enter new English score: ");
    scanf("%u", &foundStudent->entry.degrees.english_deg);

    printf("Enter new Arabic score: ");
    scanf("%u", &foundStudent->entry.degrees.arabic_deg);

    return SUCCESS;
}