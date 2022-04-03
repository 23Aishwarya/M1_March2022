/**
 * @file matrix_operations.c
 * @author Team 23
 * @brief 
 * @version 0.1
 * @date 2021-10-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "matrix_operations.h"

void free_matrix_structure(mat *m)
{
    free(m->matrix_1);
    free(m->matrix_2);
}

void dynamic_alloc_mat(float **matrix,int n)
{
    matrix = (float **)calloc(n,sizeof(float));
    for(int i=0;i<n;i++)
    {
        matrix[i] = (float *)calloc(n,sizeof(float));
    }
}

float ** alloc_input_matrix(float **matrix,int n)
{
    int i,j;
    matrix = (float **)calloc(n,sizeof(float));
    for(i=0;i<n;i++)
    {
        matrix[i] = (float *)calloc(n,sizeof(float));
    }
    float element;
    printf("Enter the matrix: \n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%f", &element);
            matrix[i][j]= element;
        }
    }
    return matrix;
}

void output_matrix(float **matrix,int n)
{
    int i,j;
    float x;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}

error_t add_matrices(float **matrix1,float **matrix2, int n)
{
    int i,j;
    float **result;
    result = (float **)calloc(n,sizeof(float));
    for(int i=0;i<n;i++)
    {
        result[i] = (float *)calloc(n,sizeof(float));
    }
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    printf("The sum of the matrices is: \n");
    output_matrix(result,n);
    free(result);
    return SUCCESS;

}

error_t subtract_matrices(float **matrix1,float **matrix2, int n)
{
    int i,j;
    float **result;
    result = (float **)calloc(n,sizeof(float));
    for(int i=0;i<n;i++)
    {
        result[i] = (float *)calloc(n,sizeof(float));
    }
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    printf("The difference of the matrices is: \n");
    output_matrix(result,n);
    free(result);
    return SUCCESS;
}

error_t product_matrices(float **matrix1,float **matrix2, int n)
{
    int i,j,k;
    float **result;
    result = (float **)calloc(n,sizeof(float));
    for(int i=0;i<n;i++)
    {
        result[i] = (float *)calloc(n,sizeof(float));
    }
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            result[i][j] = 0;
            for(k = 0;k < n; k++)
            {
                result[i][j]+= matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    printf("The product of the matrices is: \n");
    output_matrix(result,n);
    free(result);
    return SUCCESS;
}

float determinant(float **matrix,int k)
{
    float s = 1, det = 0, **b;
    b = (float **)calloc(k,sizeof(float));
    for(int ai=0;ai<k;ai++)
    {
        b[ai] = (float *)calloc(k,sizeof(float));
    }
    int i, j, m, n, c;
    if (k == 1)
    {
        return (matrix[0][0]);
    }
    else
    {
        det = 0;
        for (c = 0; c < k; c++)
        {
            m = 0;
            n = 0;
            for (i = 0;i < k; i++)
            {
                for (j = 0 ;j < k; j++)
                {
                    b[i][j] = 0;
                    if (i != 0 && j != c)
                    {
                        b[m][n] = matrix[i][j];
                        if (n < (k - 2))
                        {   
                            n++;
                        }
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (matrix[0][c] * determinant(b, k - 1));
            s = -1 * s;
        }
    }
    free(b);
    return (det); 
}

error_t inverse(float **num, int f)
{
    float **matb, **fac,**transp, **invers, d;
    int mem;
    matb = (float **)calloc(f,sizeof(float));
    fac = (float **)calloc(f,sizeof(float));
    transp = (float **)calloc(f,sizeof(float));
    invers = (float **)calloc(f,sizeof(float));
    for(int mem=0;mem<f;mem++)
    {
        matb[mem] = (float *)calloc(f,sizeof(float));
        fac[mem] = (float *)calloc(f,sizeof(float));
        transp[mem] = (float *)calloc(f,sizeof(float));
        invers[mem] = (float *)calloc(f,sizeof(float));
    }
    int p, q, m, n, i, j;
    for (q = 0;q < f; q++)
    {
        for (p = 0;p < f; p++)
        {
            m = 0;
            n = 0;
            for (i = 0;i < f; i++)
            {
                for (j = 0;j < f; j++)
                {
                    if (i != q && j != p)
                    {
                        matb[m][n] = num[i][j];
                        if (n < (f - 2))
                        {   
                            n++;
                        }
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = power(q + p) * determinant(matb, f - 1);
        }
    }
    d = determinant(num, f);
    for (i = 0;i < f; i++)
    {
        for (j = 0;j < f; j++)
        {
            transp[i][j] = fac[j][i];
        }
    }
    for (i = 0;i < f; i++)
    {
        for (j = 0;j < f; j++)
        {
            invers[i][j] = transp[i][j] / d;
        }
    }
    printf("Inverse is :\n");
    output_matrix(invers,f);
    free(matb);
    free(fac);
    free(transp);
    free(invers);
    return SUCCESS;
}

error_t transpose(float **matrix,int n)
{
    float **result;
    int i,j;
    result = (float **)calloc(n,sizeof(float));
    for(int i=0;i<n;i++)
    {
        result[i] = (float *)calloc(n,sizeof(float));
    }
    for (i = 0;i < n; i++)
    {
        for (j = 0;j < n; j++)
        {
            result[i][j] = matrix[j][i];
        }
    }
    printf("The Transpose of the matrix is: \n");
    output_matrix(result,n);
    free(result);
    return SUCCESS;    
}

float power(int exp)
{
    float result=1;
    while(exp != 0)
    {
        result*=(-1);
        exp--;
    }
    return result;
}
