#include "LocalGameOfLife.h"

#include <random>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "Logger.h"

LocalGameOfLife::LocalGameOfLife(int local_rows, int local_cols, MPI_Comm cart_comm, int halo_size)
    : local_rows_(local_rows), local_cols_(local_cols), cart_comm_(cart_comm), halo_size_(halo_size) {
    
    MPI_Comm_rank(cart_comm_, &cart_rank_);
    MPI_Comm_size(cart_comm_, &cart_size_);


    MPI_Cart_get(cart_comm_, 2, dims_, periods_, coords_);

    MPI_Cart_shift(cart_comm_, 0, -1, &nbr_n_, &nbr_s_);
    MPI_Cart_shift(cart_comm_, 1, -1, &nbr_w_, &nbr_e_);

    current_grid_ = Eigen::MatrixXi::Zero(local_rows_ + 2 * halo_size_, local_cols_ + 2 * halo_size_);
    next_grid_ = Eigen::MatrixXi::Zero(local_rows_ + 2 * halo_size_, local_cols_ + 2 * halo_size_);
}

void LocalGameOfLife::randomize(double alive_prob) {
    std::random_device rd;
    std::mt19937 gen(rd() + cart_rank_);
    std::bernoulli_distribution dist(alive_prob);
    for (int r = halo_size_; r < local_rows_ + halo_size_; ++r) {
        for (int c = halo_size_; c < local_cols_ + halo_size_; ++c) {
            current_grid_(r, c) = dist(gen) ? 1 : 0;
        }
    }
}

int LocalGameOfLife::count_alive_neighbors(int r, int c) const {
    int count = 0;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;

            int neighbor_r = r + dr;
            int neighbor_c = c + dc;


            if (neighbor_r < 0 || neighbor_r >= current_grid_.rows() ||
                neighbor_c < 0 || neighbor_c >= current_grid_.cols()) {
                std::cerr << "Invalid access at (" << neighbor_r << "," << neighbor_c << ") for grid size "
                          << current_grid_.rows() << "x" << current_grid_.cols()
                          << " in rank " << cart_rank_ << "\n";
                continue;
            }

            if (current_grid_(neighbor_r, neighbor_c) != 0) {
                ++count;
            }
        }
    }
    return count;
}

void LocalGameOfLife::exchange_halos() {
    MPI_Request requests[8];

    std::vector<int> send_n(local_cols_), recv_s(local_cols_);
    std::vector<int> send_s(local_cols_), recv_n(local_cols_);
    std::vector<int> send_w(local_rows_), recv_e(local_rows_);
    std::vector<int> send_e(local_rows_), recv_w(local_rows_);

    for (int i = 0; i < local_cols_; ++i) {
        send_n[i] = current_grid_(halo_size_, halo_size_ + i);
        send_s[i] = current_grid_(halo_size_ + local_rows_ - 1, halo_size_ + i);
    }

    for (int i = 0; i < local_rows_; ++i) {
        send_w[i] = current_grid_(halo_size_ + i, halo_size_);
        send_e[i] = current_grid_(halo_size_ + i, halo_size_ + local_cols_ - 1);
    }

    MPI_Isend(send_n.data(), local_cols_, MPI_INT, nbr_n_, 0, cart_comm_, &requests[0]);
    MPI_Irecv(recv_s.data(), local_cols_, MPI_INT, nbr_s_, 0, cart_comm_, &requests[1]);

    MPI_Isend(send_s.data(), local_cols_, MPI_INT, nbr_s_, 1, cart_comm_, &requests[2]);
    MPI_Irecv(recv_n.data(), local_cols_, MPI_INT, nbr_n_, 1, cart_comm_, &requests[3]);

    MPI_Isend(send_w.data(), local_rows_, MPI_INT, nbr_w_, 2, cart_comm_, &requests[4]);
    MPI_Irecv(recv_e.data(), local_rows_, MPI_INT, nbr_e_, 2, cart_comm_, &requests[5]);

    MPI_Isend(send_e.data(), local_rows_, MPI_INT, nbr_e_, 3, cart_comm_, &requests[6]);
    MPI_Irecv(recv_w.data(), local_rows_, MPI_INT, nbr_w_, 3, cart_comm_, &requests[7]);

    MPI_Waitall(8, requests, MPI_STATUSES_IGNORE);

    for (int i = 0; i < local_cols_; ++i) {
        current_grid_(halo_size_ - 1, halo_size_ + i) = recv_n[i];
        current_grid_(halo_size_ + local_rows_, halo_size_ + i) = recv_s[i];
    }

    for (int i = 0; i < local_rows_; ++i) {
        current_grid_(halo_size_ + i, halo_size_ - 1) = recv_w[i];
        current_grid_(halo_size_ + i, halo_size_ + local_cols_) = recv_e[i];
    }
}

void LocalGameOfLife::step() {
    exchange_halos();
    for (int r = halo_size_; r < local_rows_ + halo_size_; ++r) {
        for (int c = halo_size_; c < local_cols_ + halo_size_; ++c) {
            int neighbors = count_alive_neighbors(r, c);
            if (current_grid_(r, c) != 0) {
                next_grid_(r, c) = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                next_grid_(r, c) = (neighbors == 3) ? 1 : 0;
            }
        }
    }
    current_grid_.swap(next_grid_);
    ++local_iteration_;

    #ifdef DEBUG
    std::cout << "[Rank " << cart_rank_ << "] finished step " << local_iteration_ << std::endl;
    #endif

}

void LocalGameOfLife::set_local_block(const Eigen::MatrixXi &block) {
    if (block.rows() != local_rows_ || block.cols() != local_cols_)
        throw std::runtime_error("set_local_block: size mismatch");

    current_grid_.setZero();
    current_grid_.block(halo_size_, halo_size_, local_rows_, local_cols_) = block;
}

int LocalGameOfLife::local_rows() const { return local_rows_; }
int LocalGameOfLife::local_cols() const { return local_cols_; }
Eigen::MatrixXi LocalGameOfLife::get_current_grid() { return current_grid_; }
MPI_Comm LocalGameOfLife::get_cart_comm() { return cart_comm_; }