#pragma once

#include <Eigen/Dense>
#include <string>
#include <mpi.h>

class LocalGameOfLife {
public:
    LocalGameOfLife(int local_rows, int local_cols, MPI_Comm cart_comm, int halo_size);
    void randomize(double alive_prob);
    void step();
    void set_local_block(const Eigen::MatrixXi &block);
    int local_rows() const;
    int local_cols() const;
    Eigen::MatrixXi get_current_grid();
    MPI_Comm get_cart_comm();
    void output_to_file(const std::string &identifier) const;

private:
    int local_rows_;
    int local_cols_;
    int halo_size_;
    MPI_Comm cart_comm_;
    int cart_rank_;
    int cart_size_;

    int dims_[2];       
    int coords_[2];     
    int periods_[2];    

    int nbr_n_, nbr_s_, nbr_e_, nbr_w_;
    int local_iteration_ = 0;

    Eigen::MatrixXi current_grid_;
    Eigen::MatrixXi next_grid_;

    int count_alive_neighbors(int r, int c) const;
    void exchange_halos();
};