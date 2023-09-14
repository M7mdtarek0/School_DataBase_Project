/*
 * main.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Mohamed Tarek Elsaid
 */

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "Types.h"
#include "ErrorState.h"
#include "Config.h"
#include "school.h"


int main() {
    List_t schoolList;
    ErrorState_t result = List_init(&schoolList);

    if (result != SUCCESS) {
        printf("Failed to initialize the school list.\n");
        return 1;
    }

    while (1) {
        printf("\nSchool Database Menu:\n"    );
        printf("1. Add a student\n"		      );
        printf("2. Search for a student\n"    );
        printf("3. Delete a student\n"        );
        printf("4. Print students lists\n"    );
		printf("5. Edit student information\n");
        printf("6. Update student scores\n"   );
        printf("7. Exit\n"					  );

        u32 choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Add a student
                ListEntry_t newStudent;

                printf("Enter Student ID: ");
                scanf("%d", &newStudent.ID );

                printf("Enter Student Name: ");
                scanf("%s", newStudent.Name  );
				
				printf("Enter Student Age: ");
				scanf("%u", &newStudent.age );
			
				printf("Enter Student Phone: "    );
				scanf("%u", &newStudent.data.phone);
			
				printf("Enter Math Degree: "     		);
				scanf("%u", &newStudent.degrees.math_deg);
			
				printf("Enter English Degree: "			   );
				scanf("%u", &newStudent.degrees.english_deg);
			
				printf("Enter Arabic Degree: "			  );
				scanf("%u", &newStudent.degrees.arabic_deg);
                

                result = List_insertStudent(&schoolList, &newStudent);
                if (result == SUCCESS) {
                    printf("Student added successfully.\n");
                } else {
                    printf("Failed to add the student.\n" );
                }
                break;
            }
            case 2: {
                // Search for a student
                u8 studentID;
                printf("Enter Student ID to search: ");
                scanf("%d", &studentID				 );

                ListNode_t* foundStudent = NULL;
                result = List_searchStudent(&schoolList, studentID, &foundStudent);
                if (result == SUCCESS && foundStudent != NULL) {
                    printf("Student Found: ID=%d, Name=%s\n", foundStudent->entry.ID, foundStudent->entry.Name);
                    // Print other fields as needed
                } else {
                    printf("Student not found.\n");
                }
                break;
            }
            case 3: {
                // Delete a student
                u8 studentID;
                printf("Enter Student ID to delete: ");
                scanf("%d", &studentID);

                result = List_deleteStudent(&schoolList, studentID);
                if (result == SUCCESS) {
                    printf("Student deleted successfully.\n");
                } else {
                    printf("Failed to delete the student.\n");
                }
                break;
            }
            case 4: {
                // Print student list
                result = List_printList(&schoolList);
                if (result != SUCCESS) {
                    printf("Failed to print the student list.\n");
                }
                break;
            }
			case 5: {
				// Edit Student Information
				u8 studentID;
				printf("Enter Student ID to edit: ");
				scanf("%u", &studentID);
			
				result = List_editStudent(&schoolList, studentID);
				if (result == SUCCESS) {
					printf("Student information edited successfully.\n");
				} else if (result == NULL_PTR) {
					printf("Student not found.\n");
				} else {
					printf("Failed to edit student information.\n");
				}
				break;
			}

			case 6: {
				// Update Student's Score
				u8 studentID;
				printf("Enter Student ID to update scores: ");
				scanf("%u", &studentID);
			
				result = List_updateScore(&schoolList, studentID);
				if (result == SUCCESS) {
					printf("Student scores updated successfully.\n");
				} else if (result == NULL_PTR) {
					printf("Student not found.\n");
				} else {
					printf("Failed to update student scores.\n");
				}
				break;
			}
			case 7: {
                // Cleanup and exit
                List_freeList(&schoolList);
                return 0;
            }
            default: {
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
    }

    return 0;
}