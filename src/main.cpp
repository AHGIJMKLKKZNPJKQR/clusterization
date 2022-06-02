#include <iostream>
#include <string>
#include <fstream>

#include "parse.hpp"
#include "const.hpp"
#include "hier.hpp"
#include "kmeans.hpp"

void saveClusters(const std::string filename, const std::vector<int> &cluster) {
  std::ofstream file;
  file.open(filename);
  for (const int &x : cluster)
    file << x << ' ';
  file << '\n';
  file.close();
}

void doHierarchy() {
  Eigen::MatrixXd X;
  getData(X, std::getenv("DATA_FILE"), true);

  for (int metric = 0; metric <= ward; ++metric) {
    HierCluster hierCluster(X, static_cast<Metric>(metric));
    std::vector<Linkage> v(hierCluster.getDend());
    
    std::ofstream dendrogram;
    dendrogram.open("out/hier/dendrogram" + std::to_string(metric));
    for (auto [x, y, z, t] : v)
      dendrogram << x << " " << y << " " << z << " " << t << "\n";
    dendrogram.close();

    std::vector<int> groups(5);
    std::ifstream grpFile;
    grpFile.open(std::getenv("HIER_GRP"));
    for (int &i : groups)
      grpFile >> i;
    grpFile.close();  
    saveClusters("out/hier/cluster" + std::to_string(metric), hierCluster.clusterize(groups[metric]));
  }
}

void doKMeans() {
  Eigen::MatrixXd X;
  getData(X, std::getenv("DATA_FILE"), true, true);

  std::ofstream elbow;
  elbow.open("out/kmeans/elbow");

  int maxK = std::stoi(std::getenv("MAX_K"));
  for (int k = 1; k <= maxK; ++k) {
    KMeans kMeans(X, k, 100);
    saveClusters("out/kmeans/cluster" + std::to_string(k), kMeans.getClusters());
    elbow << kMeans.getError() << ' ';
  }
  elbow << '\n';
  elbow.close();  
}

int main() {
  // doHierarchy();
  doKMeans();
}