/**
 * @file matrix.c
 * @author Team 23
 * @brief 
 * @version 0.1
 * @date 2021-10-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "matrix_operations.h"

#define VALID   (1)
#define INVALID (0)

unsigned int matrixcalc_oper = 0;
int n;
mat operands;
error_t err;

enum opers{ DET=1,ADD,SUB,MUL,TRN,INV,EXIT };

void matrixcalc_menu(void);
int oper_valid(int oper);

int matx()
{
    printf("\n****WELCOME TO THE MATRIX OPERATIONS PROGRAM****\n");
    while(1)
    {
        matrixcalc_menu();
    }
}

void matrixcalc_menu(void)
{
    printf("\nPress a key to select the appropriate operation\n");
    printf("\n1. Determinant\n2. Addition of matrices\n3. Subtraction of matrices\n4. Product of matrices\n5. Transpose of a matrix\n6. Inverse of a matrix\n7. Exit");
    printf("\n\tEnter your choice\n");
   
    scanf("%d", &matrixcalc_oper);

    if(EXIT == matrixcalc_oper)
    {
        printf("\nThank you. Exiting the Application\n");
        exit(0);
    }

    if(INVALID != oper_valid(matrixcalc_oper))
    {
        printf("\n\tEnter your matrix elements with space between them\n");

        printf("Enter order of matrix: ");
        scanf("%d", &n);
        operands.matrix_1 = alloc_input_matrix(operands.matrix_1,n);
        if(((matrixcalc_oper != DET )&&(matrixcalc_oper != TRN )&&(matrixcalc_oper != INV))){
            operands.matrix_2 = alloc_input_matrix(operands.matrix_2,n);
        }
    }
    else
    {
        printf("\n\t---Wrong choice---\nEnter to continue\n");
        return;
        
    }
    switch(matrixcalc_oper)
    {
        case DET:
            operands.result = determinant(operands.matrix_1,n);
            printf("Determinant of the matrix is: %f \n\n\n",operands.result);
            break;
        case ADD:
            err = add_matrices(operands.matrix_1,operands.matrix_2,n);
            free_matrix_structure(&operands);
            break;
        case SUB:
            err = subtract_matrices(operands.matrix_1,operands.matrix_2,n);
            free_matrix_structure(&operands);
            break;
        case MUL:
            err = product_matrices(operands.matrix_1,operands.matrix_2,n);
            free_matrix_structure(&operands);
            break;
        case TRN:
            err = transpose(operands.matrix_1,n);
            free_matrix_structure(&operands);
            break;
        case INV:
            if(determinant(operands.matrix_1,n) == 0.00){
                printf("Inverse cannot be found..! \n");
            }
            else{
                err = inverse(operands.matrix_1,n);
                free_matrix_structure(&operands);
            }
            break;
        case EXIT:
            free_matrix_structure(&operands);
            exit(0);
            break;
        default:
            printf("\n\t---The code would never arrive here---\n");
    }
}

int oper_valid(int oper)
{
    return ((DET <= oper) && (EXIT >= oper)) ? VALID: INVALID;
}