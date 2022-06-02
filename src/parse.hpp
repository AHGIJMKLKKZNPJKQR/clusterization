#pragma once

#include <Eigen/Dense>

#include "const.hpp"

void getData(Eigen::MatrixXd &X, const std::string &path, const bool &omitLast = false, const bool &norm = false);

void normalize(Eigen::MatrixXd &X);
