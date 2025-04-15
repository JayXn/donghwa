#include <algorithm>
#include <vector>
typedef double DataType;
std::vector<DataType> given;

struct DataSet {
  size_t begin, count;
};

// 修改返回類型，回傳一個包含前三大數字的向量
std::vector<DataType> solve(DataSet input) {
  // 基本情況：如果只有一個元素，回傳它作為前三大（不足 3 個則補 -∞）
  if (input.count == 1)
    return {given[input.begin], -1e9, -1e9};

  // 分割問題為兩個子問題
  std::vector<DataSet> subProblems(2);
  subProblems[0].begin = input.begin;
  subProblems[0].count = input.count / 2;
  subProblems[1].begin = input.begin + subProblems[0].count;
  subProblems[1].count = input.count - subProblems[0].count;

  // 遞迴解決子問題
  std::vector<DataType> leftTop3 = solve(subProblems[0]);
  std::vector<DataType> rightTop3 = solve(subProblems[1]);

  // 合併左右子問題的結果
  std::vector<DataType> merged = leftTop3;
  merged.insert(merged.end(), rightTop3.begin(), rightTop3.end());

  // 排序並選取前三大
  std::sort(merged.begin(), merged.end(), std::greater<DataType>());
  merged.resize(3);  // 只保留前三個元素

  return merged;
}

DataType findThirdLargest() {
  std::vector<DataType> top3 = solve({0, given.size()});
  return top3[2];  // 回傳第 3 大的元素
}
