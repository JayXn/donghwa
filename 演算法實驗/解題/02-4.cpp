#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> DataType;  // {數值, 出現次數}

vector<DataType> merge(const vector<DataType>& left,
                       const vector<DataType>& right) {
  vector<DataType> merged;
  size_t i = 0, j = 0;

  while (i < left.size() && j < right.size()) {
    if (left[i].first < right[j].first) {
      merged.push_back(left[i++]);
    } else if (left[i].first > right[j].first) {
      merged.push_back(right[j++]);
    } else {
      // 相同數值，累積計數
      merged.push_back({left[i].first, left[i].second + right[j].second});
      i++;
      j++;
    }
  }
  while (i < left.size())
    merged.push_back(left[i++]);
  while (j < right.size())
    merged.push_back(right[j++]);

  return merged;
}

vector<DataType> mergeSortWithCount(const vector<int>& arr,
                                    int left,
                                    int right) {
  if (left == right)
    return {{arr[left], 1}};  // 單個元素，計數為 1

  int mid = (left + right) / 2;
  vector<DataType> leftPart = mergeSortWithCount(arr, left, mid);
  vector<DataType> rightPart = mergeSortWithCount(arr, mid + 1, right);

  return merge(leftPart, rightPart);
}

int main() {
  vector<int> input = {3, 2, 3, 5, 2, 3, 4, 5, 6, 22};
  vector<DataType> result = mergeSortWithCount(input, 0, input.size() - 1);

  for (const auto& p : result) {
    cout << "{" << p.first << ", " << p.second << "} ";
  }
  cout << endl;

  return 0;
}
