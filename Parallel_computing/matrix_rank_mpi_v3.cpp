#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <mpi.h>

using namespace std;

// Размер матрицы
#define MATRIX_SIZE 1000
#define N_ROWS MATRIX_SIZE
#define N_COLS MATRIX_SIZE
// Точность вычислений
#define EPS 0.01

int ProcNum = 0; // The number of the available processes
int ProcRank = 0; // The rank of the current process 

int *pParallelPivotPos; // The number of rows selected as the pivot ones
int *pProcPivotIter; // The number of iterations, at which the processor rows were used as the pivot ones 

// Нулевая ли строка
bool row_null(double* pMatrix, int Size, int Row)
{ 
    for (int i=0; i<Size; i++) {
        if (pMatrix[Size*Row + i] != 0) {
            return false;
        }
    }
    return true;
}

void PrintMatrix(double* pMatrix, int n_rows, int n_cols)
{
    for (int i=0; i<n_rows; i++) {
        for (int j=0; j<n_cols; j++) {
            printf("%f ", pMatrix[i*n_cols + j]);
        }
        printf("\n");
    }
}

void PrintVector(double* pVector, int Size)
{
    for (int i=0; i<Size; i++) {
        printf("%f ", pVector[i]);
    }
    printf("\n");
}

void ProcessInitialization 
    (double* &pMatrix, double* &pProcRows, int &Size, int &RowNum) 
{
    if (ProcRank == 0) {
        Size = MATRIX_SIZE;
    }

    MPI_Bcast(&Size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int RestRows = Size;
    for (int i=0; i<ProcRank; i++)
        RestRows = RestRows-RestRows/(ProcNum-i);
    RowNum = RestRows/(ProcNum-ProcRank);
    pProcRows = new double [RowNum*Size];

    if (ProcRank == 0) {
        pMatrix = new double [Size*Size];
        
        srand(100); // фиксируем генератор
        int i,j;
        for (i = 0; i < Size; i++) {
            for (j = 0; j < Size; j++) {
                pMatrix[i*Size + j] = (double)(rand())/RAND_MAX * 100;
            }
        }
    } 
}

// Function for computational process termination
void ProcessTermination (double* pMatrix, double* pProcRows)
{
    if (ProcRank == 0) {
        delete [] pMatrix;
    }
    delete [] pProcRows;
}

int* pProcInd;
int* pProcNum;

// Data distribution among the processes
void DataDistribution(double* pMatrix, double* pProcRows, int Size, int RowNum)
{
    int *pSendNum; // The number of the elements sent to the process
    int *pSendInd; // The index of the first data element sent
    // to the process
    int RestRows=Size; // The number of rows, that have not been
    // distributed yet
    int i; // Loop variable
    // Alloc memory for temporary objects
    pSendInd = new int [ProcNum];
    pSendNum = new int [ProcNum];
    // Define the disposition of the matrix rows for the current process
    RowNum = (Size/ProcNum);
    pSendNum[0] = RowNum*Size;
    pSendInd[0] = 0;
    for (i=1; i<ProcNum; i++) {
        RestRows -= RowNum;
        RowNum = RestRows/(ProcNum-i);
        pSendNum[i] = RowNum*Size;
        pSendInd[i] = pSendInd[i-1]+pSendNum[i-1];
    }
    // Scatter the rows
    MPI_Scatterv(pMatrix, pSendNum, pSendInd, MPI_DOUBLE, pProcRows,
        pSendNum[ProcRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // Free the memory
    delete [] pSendNum;
    delete [] pSendInd;

    pProcInd = new int [ProcNum];
    pProcNum = new int [ProcNum];
    RestRows = Size;
    pProcInd[0] = 0;
    pProcNum[0] = Size/ProcNum;
    for (i=1; i<ProcNum; i++) {
        RestRows -= pProcNum[i-1];
        pProcNum[i] = RestRows/(ProcNum-i);
        pProcInd[i] = pProcInd[i-1]+pProcNum[i-1];
    }
}

// Function for testing the data distribution
void TestDistribution(double* pMatrix, double* pVector, double* pProcRows,
    double* pProcVector, int Size, int RowNum)
{
    if (ProcRank == 0) {
        printf("Initial Matrix: \n");
        PrintMatrix(pMatrix, Size, Size);
        printf("Initial Vector: \n");
        PrintVector(pVector, Size);
    }
    for (int i=0; i<ProcNum; i++) {
        if (ProcRank == i) {
            printf("\nProcRank = %d \n", ProcRank);
            printf(" Matrix Stripe:\n");
            PrintMatrix(pProcRows, RowNum, Size);
            printf(" Vector: \n");
            PrintVector(pProcVector, RowNum);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
}

// Fuction for column elimination
void ParallelEliminateColumns(double* pProcRows, double* pPivotRow, int Size, int RowNum, int Iter)
{
    double PivotFactor;
    for (int i=0; i<RowNum; i++) {
        if (pProcPivotIter[i] == -1) {
            PivotFactor = pProcRows[i*Size+Iter] / pPivotRow[Iter];
            for (int j=Iter; j<Size; j++) {
                pProcRows[i*Size + j] -= PivotFactor * pPivotRow[j];
                if (pProcRows[i*Size + j] < EPS)
                    pProcRows[i*Size + j] = 0;
            }
        }
    }
} 

// Gaussian elimination
void ParallelGaussianElimination (double* pProcRows, int Size, int RowNum)
{
    double MaxValue; // The value of the pivot element of thе process
    int PivotPos; // The Position of the pivot row in the stripe of thе process
    struct { double MaxValue; int ProcRank; } ProcPivot, Pivot;
    double *pPivotRow; // Pivot row of the current iteration
    pPivotRow = new double [Size];
    // The iterations of the Gaussian elimination
    for (int i=0; i<Size; i++) {
        // Calculating the local pivot row
        for (int j=0; j<RowNum; j++) {
            if ((pProcPivotIter[j] == -1) && (MaxValue < fabs(pProcRows[j*Size+i]))) {
                    MaxValue = fabs(pProcRows[j*Size+i]);
                    PivotPos = j;
            }
        }
        // После определения ведущей строки на каждом процессе, необходимо выбрать максимальный среди
        // полученных ведущих элементов и определить, на каком процессе он располагается
        // Finding the global pivot row
        ProcPivot.MaxValue = MaxValue;
        ProcPivot.ProcRank = ProcRank;
        // Finding the pivot process
        MPI_Allreduce(&ProcPivot, &Pivot, 1, MPI_DOUBLE_INT, MPI_MAXLOC, MPI_COMM_WORLD);

        // Storing the number of the pivot row
        if ( ProcRank == Pivot.ProcRank ){
            pProcPivotIter[PivotPos]= i;
            pParallelPivotPos[i]= pProcInd[ProcRank] + PivotPos;
        }
    
        MPI_Bcast(&pParallelPivotPos[i], 1, MPI_INT, Pivot.ProcRank, MPI_COMM_WORLD);
        // Broadcasting the pivot row
        if ( ProcRank == Pivot.ProcRank ){
            // Fill the pivot row
            for (int j=0; j<Size; j++) {
                pPivotRow[j] = pProcRows[PivotPos*Size + j];
            }
        }
        MPI_Bcast(pPivotRow, Size, MPI_DOUBLE, Pivot.ProcRank, MPI_COMM_WORLD);

        // Column elimination
        ParallelEliminateColumns(pProcRows, pPivotRow, Size, RowNum, i); 
    }
    delete [] pPivotRow; 
}

// Function for execution of the parallel Gauss algorithm
void ParallelResultCalculation(double* pProcRows, int Size, int RowNum)
{
     // Memory allocation
    pParallelPivotPos = new int [Size];
    pProcPivotIter = new int [RowNum];
    for (int i=0; i<RowNum; i++)
        pProcPivotIter[i] = -1;

    // Gaussian elimination
    ParallelGaussianElimination (pProcRows, Size, RowNum);

    // Memory deallocation
    delete [] pParallelPivotPos;
    delete [] pProcPivotIter;
} 

// Function for gathering the result vector
void ResultCollection(double* pProcRows, double* pMatrix, int Size, int RowNum) {
    //Gathering the result vector on the pivot processor
    MPI_Gatherv(pProcRows, Size*RowNum, MPI_DOUBLE, pMatrix,
        pProcNum, pProcInd, MPI_DOUBLE, 0, MPI_COMM_WORLD);
} 

int main(int argc, char **argv)
{
    // MPI
    // Будем распределять строки блочно via MPI_Scatterv
    // Уйдем от представления vector, как это делали в OMP
    // Так как в MPI есть встроенные типы при рассылке (MPI_Double)
    // избежим конфликтов
    // Собираем результат с помощью MPI_Gatherv

    double* pMatrix; // The matrix
    double *pProcRows; // The Rows of matrix on the process
    int Size; // The Sizes of the initial matrix and vector
    int RowNum; // The Number of the matrix rows on the current process
    double Start, Finish; 
   

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank); 

    // Memory allocation and definition of object elements
    ProcessInitialization(pMatrix, pProcRows, Size, RowNum);

    /*if (ProcRank == 0) {
        printf("Initial matrix \n");
        PrintMatrix(pMatrix, Size, Size);
        printf("Initial vector \n");
        PrintVector(pVector, Size);
    }*/

    Start = MPI_Wtime(); // засекаем время

    // Distributing the initial data between the processes
    DataDistribution(pMatrix, pProcRows, Size, RowNum);
    //TestDistribution(pMatrix, pVector, pProcRows, pProcVector, Size, RowNum);

    // The execution of the parallel Gauss algorithm
    ParallelResultCalculation (pProcRows, Size, RowNum);
    // TestDistribution(pMatrix, pVector, pProcRows, pProcVector, Size, RowNum);

    // Gathering the result matrix
    ResultCollection(pProcRows, pMatrix, Size, RowNum);

    Finish = MPI_Wtime(); // Засекаем время

    // После сбора матрицы считаем ранг в root процессе
    if (ProcRank == 0) {
        // считаем ранг
        int r = min(N_ROWS, N_COLS);
        while (r > 1 && row_null(pMatrix, Size, r)) {
            r--;
        }
        // Выводим результаты работы
        double data_size = sizeof(double*)*N_ROWS + sizeof(double)*N_ROWS*N_COLS;
        cout << "data size is " << data_size / 8 / 1024 << " KByte " << data_size / 8 / 1024 /1024 << " MByte" << endl;
        cout << "number of proc-s = " << ProcNum << endl;
        cout << "matrix size is " << N_ROWS << "*" << N_COLS << endl;
        cout << "time = " << Finish - Start << " sec"<< endl;
        printf("r = %d\n", r);
    }

    // Process termination
    ProcessTermination (pMatrix, pProcRows); 
    MPI_Finalize();
}