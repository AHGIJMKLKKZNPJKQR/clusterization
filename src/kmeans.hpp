#pragma once

#include <Eigen/Dense>
#include <vector>

class KMeans {
  std::vector<int> cluster;
  double minErr;

public:
  KMeans(Eigen::MatrixXd &data, const int &k, int runs = 10);
  std::vector<int> getClusters() const;
  double getError() const;
};
