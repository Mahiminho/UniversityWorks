#include <iostream>
#include "mpi.h"

int main(int argc, char** argv)
{
    int numTasks, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numTasks);

    if (rank == 0)
    {
        int recvRank = -1;
        for (size_t i = 1; i < numTasks; ++i)
        {
            MPI_Recv(&recvRank, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "[Proc: Main] \tGot message from [" << recvRank << "]\n";
        }
    }
    else
    {
        MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        std::cout << "[Proc: " << rank << "] \tSent message to [0]" << "\n";
    }

    MPI_Finalize();
    return 0;
}
