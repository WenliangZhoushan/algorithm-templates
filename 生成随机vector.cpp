#include <bits/stdc++.h>
using namespace std;


std::vector<int> generateRandomVector(int n, int minVal, int maxVal) {
  // 1. 使用高精度时间戳作为种子，确保每次运行结果不同
  unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
  std::mt19937 gen(seed);

  // 2. 定义均匀分布 [min, max]
  std::uniform_int_distribution<int> dist(minVal, maxVal);

  // 3. 构造 vector 并填充
  std::vector<int> res(n);
  for (int i = 0; i < n; ++i) {
      res[i] = dist(gen); // 允许重复值
  }

  return res;
}
