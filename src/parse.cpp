#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

#include "parse.hpp"
#include "const.hpp"

void legitCheck() {
    std::cout << "DUPA\n";
}

void getData(Eigen::MatrixXd &X, const std::string &path, const bool &omitLast, const bool &norm) {
    std::ifstream data;
    data.open(path);

    std::vector<std::vector<double>> input;

    std::string line;
    int cols = 0;
    while (std::getline(data, line)) {
        std::vector<double> row;
        std::stringstream lstream(line);
        while (lstream) {
            row.push_back(0);
            lstream >> row.back();
        }
        row.pop_back();
        if (omitLast)
            row.pop_back();
        input.push_back(row);
        if (!cols)
            cols = row.size();
        assert(cols == (int)row.size());
    }
    data.close();

    // std::shuffle(input.begin(), input.end(), GEN);

    X.resize(input.size(), cols);
    for (int i = 0; i < X.rows(); ++i)
        for (int j = 0; j < X.cols(); ++j)
            X(i, j) = input[i][j];
    if (norm)
        normalize(X);
}

void normalize(Eigen::MatrixXd &X) {
    int n = X.rows(), m = X.cols();
    Eigen::VectorXd var = Eigen::VectorXd::Zero(m);

    Eigen::VectorXd avg = X.colwise().sum() / (double)n;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            var[j] += (X(i, j) - avg[j]) * (X(i, j) - avg[j]);
    var /= (double)n;

    std::ofstream normalized;
    normalized.open("data/normalized.txt");

    for (int i = 0; i < n; ++i)
        for (int j = 1; j < m; ++j)
            X(i, j) = (X(i, j) - avg[j]) / sqrt(var[j]);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            normalized << X(i, j) << ' ';
        normalized << '\n';
    }
    normalized << '\n';

    normalized.close();
}
