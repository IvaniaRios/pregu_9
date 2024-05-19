#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int i, j;
    int numVectors, numTerms;
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Ingrese el número de vectores: ");
        scanf("%d", &numVectors);

        printf("Ingrese el número de términos: ");
        scanf("%d", &numTerms);
    }

    MPI_Bcast(&numVectors, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&numTerms, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int vectors[numVectors][numTerms];

    int start = 2 + rank * numTerms * 2; // Cada proceso calcula el inicio de su rango de vectores

    for (i = 0; i < numVectors; i++) {
        int vectorStart = start + i * numTerms * 2; // El primer número de cada vector es mayor en secuencia

        for (j = 0; j < numTerms; j++) {
            vectors[i][j] = vectorStart + j * 2; // Generar los términos de la serie
        }
    }

    printf("Proceso %d: Serie generada en %d vectores:\n", rank, numVectors);
    for (i = 0; i < numVectors; i++) {
        printf("Proceso %d: Vector %d: ", rank, i);
        for (j = 0; j < numTerms; j++) {
            printf("%d ", vectors[i][j]);
        }
        printf("\n");
    }

    MPI_Finalize();

    return 0;
}
