#include "hier.hpp"
#include <iostream>

HierCluster::HierCluster(Eigen::MatrixXd &data, const Metric &metric) {
  const int n = data.rows();
  Eigen::MatrixXd D(n, n);
  std::vector<int> num(n);
  std::vector<int> size(n, 1);
  for (int i = 0; i < n; ++i)
    num[i] = i;
  
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      D(i, j) = (data.row(i) - data.row(j)).norm();
  
  int next_num = n;

  switch (metric) {
    case single:
      for (int it = 0; it < n - 1; ++it) {
        int x = 0, y = 1;
        for (int i = 1; i < n - it; ++i)
          for (int j = 0; j < i; ++j)
            if (D(i, j) < D(x, y))
              y = i, x = j;          
        
        dend.push_back({ num[x], num[y], D(x, y), size[x] + size[y] });

        for (int i = 0; i < n - it; ++i)
          D(x, i) = D(i, x) = (D(i, x) + D(i, y) - abs(D(i, x) - D(i, y))) * .5;

        num[x] = next_num++;
        size[x] += size[y];
        D.row(y).swap(D.row(n - it - 1));
        D.col(y).swap(D.col(n - it - 1));
        std::swap(num[y], num[n - it - 1]);
        std::swap(size[y], size[n - it - 1]);
      }
      break;
      
    case full:
      for (int it = 0; it < n - 1; ++it) {
        int x = 0, y = 1;
        for (int i = 1; i < n - it; ++i)
          for (int j = 0; j < i; ++j)
            if (D(i, j) < D(x, y))
              y = i, x = j;          
        
        dend.push_back({ num[x], num[y], D(x, y), size[x] + size[y] });
        
        for (int i = 0; i < n - it; ++i)
          D(x, i) = D(i, x) = (D(i, x) + D(i, y) + abs(D(i, x) - D(i, y))) * .5;

        num[x] = next_num++;
        size[x] += size[y];
        D.row(y).swap(D.row(n - it - 1));
        D.col(y).swap(D.col(n - it - 1));
        std::swap(num[y], num[n - it - 1]);
        std::swap(size[y], size[n - it - 1]);
      }
      break;
    
    case average:
      for (int it = 0; it < n - 1; ++it) {
        int x = 0, y = 1;
        for (int i = 1; i < n - it; ++i)
          for (int j = 0; j < i; ++j)
            if (D(i, j) < D(x, y))
              y = i, x = j;          

        dend.push_back({ num[x], num[y], D(x, y), size[x] + size[y] });

        const double A = (double)size[x] / (double)(size[x] + size[y]), B = (double)size[y] / (double)(size[x] + size[y]);
        for (int i = 0; i < n - it; ++i)
          D(x, i) = D(i, x) = D(i, x) * A + D(i, y) * B;

        num[x] = next_num++;
        size[x] += size[y];
        D.row(y).swap(D.row(n - it - 1));
        D.col(y).swap(D.col(n - it - 1));
        std::swap(num[y], num[n - it - 1]);
        std::swap(size[y], size[n - it - 1]);
      }
      break;
    
    case centroid:
      for (int it = 0; it < n - 1; ++it) {
        int x = 0, y = 1;
        for (int i = 1; i < n - it; ++i)
          for (int j = 0; j < i; ++j)
            if (D(i, j) < D(x, y))
              y = i, x = j;          
        
        dend.push_back({ num[x], num[y], D(x, y), size[x] + size[y] });

        const double A = (double)size[x] / (double)(size[x] + size[y]), B = (double)size[y] / (double)(size[x] + size[y]);
        const double old = D(x, y) * A * B;

        for (int i = 0; i < n - it; ++i)
          D(x, i) = D(i, x) = D(i, x) * A + D(i, y) * B - old;

        num[x] = next_num++;
        size[x] += size[y];
        D.row(y).swap(D.row(n - it - 1));
        D.col(y).swap(D.col(n - it - 1));
        std::swap(num[y], num[n - it - 1]);
        std::swap(size[y], size[n - it - 1]);
      }
      break;
    
    default:
      for (int it = 0; it < n - 1; ++it) {
        int x = 0, y = 1;
        for (int i = 1; i < n - it; ++i)
          for (int j = 0; j < i; ++j)
            if (D(i, j) < D(x, y))
              y = i, x = j;          

        dend.push_back({ num[x], num[y], D(x, y), size[x] + size[y] });
        
        const double tmp = size[x] + size[y], s = tmp + tmp;
        const double A = (size[x] + tmp) / s, B = (size[y] + tmp) / s;
        const double old = D(x, y) * tmp / s;

        for (int i = 0; i < n - it; ++i)
          D(x, i) = D(i, x) = D(i, x) * A + D(i, y) * B - old;

        num[x] = next_num++;
        size[x] += size[y];
        D.row(y).swap(D.row(n - it - 1));
        D.col(y).swap(D.col(n - it - 1));
        std::swap(num[y], num[n - it - 1]);
        std::swap(size[y], size[n - it - 1]);
      }
  }
}

std::vector<Linkage> HierCluster::getDend() const {
  return dend;
}

void HierCluster::assignGroup(const int &num, std::vector<int> &par, std::vector<int> &grp) const {
  if (par[num] < 0)
    return;
  assignGroup(par[num], par, grp);
  grp[num] = grp[par[num]];
  par[num] = -1;
}


std::vector<int> HierCluster::clusterize(const int &groups) const {
  int n = dend.size() + 1;
  std::vector<int> res(n);
  std::vector<int> par((n << 1) - groups, -1);
  int next_num = n;

  for (int i = 0; i < n - groups; ++i)
    par[dend[i].A] = par[dend[i].B] = next_num++;

  std::vector<int> grp((n << 1) - groups, -1);
  next_num = 0;
  for (int i = 0; i < (n << 1) - groups; ++i)
    if (par[i] < 0)
      grp[i] = next_num++;

  assert(next_num == groups);

  for (int i = 0; i < n; ++i)
    assignGroup(i, par, grp);

  grp.resize(n);
  return grp;
}