#include <set>
#include <random>
#include <limits>
#include <iostream>

#include "const.hpp"
#include "kmeans.hpp"

inline int d(const Eigen::VectorXd &a, const Eigen::VectorXd &b) {
  return (a - b).norm();
}

KMeans::KMeans(Eigen::MatrixXd &data, const int &k, int runs) : minErr(std::numeric_limits<double>::max()) {
  const int n = data.rows(), m = data.cols();

  while (runs--) {
    std::set<int> used;
    Eigen::MatrixXd centroid(k, m);
    std::uniform_int_distribution distrib(0, n - 1);

    for (int i = 0, cent = distrib(GEN); i < k; ++i) {
      while (used.count(cent))
        cent = distrib(GEN);
      used.insert(cent);
      centroid.row(i) = data.row(cent);
    }

    std::uniform_int_distribution randClus(0, k - 1);

    std::vector<int> clust(n);
    for (int &i : clust)
      i = randClus(GEN);

    bool change = true;
    while (change) {
      change = false;
      for (int i = 0; i < n; ++i) {
        int closest = clust[i];
        for (int j = 0; j < k; ++j) {
          if (j == clust[i])
            continue;
          if (d(data.row(i), centroid.row(j)) < d(data.row(i), centroid.row(closest)))
            closest = j;
        }

        if (closest != clust[i]) {
          clust[i] = closest;
          change = true;
        }
      }

      Eigen::MatrixXd newCent = Eigen::MatrixXd::Zero(k, m);
      std::vector<int> count(k, 0);
      for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
          newCent.row(clust[j]) += data.row(j);
          ++count[clust[j]];
        }
      }

      for (int i = 0; i < k; ++i) {
        if (count[i])
          newCent.row(i) /= (double)count[i];
        else newCent.row(i) = centroid.row(i);
        
        if (d(newCent.row(i), centroid.row(i)) > EPS)
          change = true;
      }
      centroid = newCent;
    }

    double err = 0;
    for (int i = 0; i < n; ++i)
      err += (data.row(i) - centroid.row(clust[i])).squaredNorm();
    if (err < minErr) {
      minErr = err;
      cluster = clust;
    }
  }
}

std::vector<int> KMeans::getClusters() const {
  return cluster;
}

double KMeans::getError() const {
  return minErr;
}