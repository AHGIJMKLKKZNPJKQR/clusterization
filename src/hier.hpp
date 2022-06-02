#pragma once

#include <Eigen/Dense>
#include <vector>

enum Metric {
  single,
  full,
  average,
  centroid,
  ward
};

struct Linkage {
  int A, B;
  double dist;
  int size;
};

class HierCluster {
  std::vector<Linkage> dend;
  void assignGroup(const int &num, std::vector<int> &par, std::vector<int> &grp) const;

public:
  HierCluster(Eigen::MatrixXd &data, const Metric &metric = single);
  std::vector<Linkage> getDend() const;
  std::vector<int> clusterize(const int &groups) const;
};