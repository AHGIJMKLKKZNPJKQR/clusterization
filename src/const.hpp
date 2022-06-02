#pragma once

#include <Eigen/Dense>
#include <string>
#include <random>

// typedef Eigen::MatrixXd<double, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;
// typedef Eigen::Matrix<double, Eigen::Dynamic, 1> vec;

extern std::mt19937 GEN;
const double EPS = 1e-7;

// const std::string DATA_PATH[] { 
//   "data/dane_2D_1", 
//   "data/dane_2D_2", 
//   "data/dane_2D_3", 
//   "data/dane_2D_4", 
//   "data/dane_2D_5", 
//   "data/dane_2D_6",
//   "data/dane_2D_7",
//   "data/dane_2D_8",
//   "data/dane_9D",
//   "data/rp.data"
// };
