#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 2    // 每個節點最多容納的資料數量
#define MAX_NAME_LEN 50  // 資料名稱最大長度

// 定義邊界框結構
typedef struct {
  double minX, minY;  // 邊界框的最小 X 和 Y 座標
  double maxX, maxY;  // 邊界框的最大 X 和 Y 座標
} BoundingBox;

// 定義資料項結構
typedef struct {
  double latitude, longitude;  // 緯度和經度
  char name[MAX_NAME_LEN];     // 資料名稱
} DataItem;

// 定義 R-Tree 節點結構
typedef struct RTreeNode {
  int isLeaf;                                   // 是否為葉節點
  int count;                                    // 目前節點的資料數量
  BoundingBox mbr;                              // 節點的最小邊界矩形 (MBR)
  struct RTreeNode* children[MAX_ENTRIES + 1];  // 子節點指標
  DataItem data[MAX_ENTRIES];                   // 存放資料的陣列
} RTreeNode;

// 搜尋結果結構
typedef struct {
  DataItem item;    // 資料項
  double distance;  // 距離
} SearchResult;

// 函數原型聲明
RTreeNode* createNode(int isLeaf);
BoundingBox calculateMBR(BoundingBox a, BoundingBox b);
double calculateDistance(double lat1, double lon1, double lat2, double lon2);
void adjustMBR(RTreeNode* node);
void splitNode(RTreeNode** root, RTreeNode* node, DataItem item);
void insert(RTreeNode** root, DataItem item);
void searchHelper(RTreeNode* node,
                  double latitude,
                  double longitude,
                  int n,
                  SearchResult* results);
SearchResult* search(RTreeNode* root, double latitude, double longitude, int n);
void printTree(RTreeNode* root, int depth);
int chooseSubtree(RTreeNode* node, DataItem item);

// 創建一個新的 RTreeNode 節點
RTreeNode* createNode(int isLeaf) {
  RTreeNode* node = (RTreeNode*)malloc(sizeof(RTreeNode));
  node->isLeaf = isLeaf;
  node->count = 0;
  node->mbr.minX = node->mbr.minY = DBL_MAX;   // 設置邊界框為最大值
  node->mbr.maxX = node->mbr.maxY = -DBL_MAX;  // 設置邊界框為最小值
  for (int i = 0; i <= MAX_ENTRIES; i++) {
    node->children[i] = NULL;
  }
  return node;
}

// 計算兩個邊界框的邊界矩形 (MBR)
BoundingBox calculateMBR(BoundingBox a, BoundingBox b) {
  BoundingBox result;
  result.minX = fmin(a.minX, b.minX);
  result.minY = fmin(a.minY, b.minY);
  result.maxX = fmax(a.maxX, b.maxX);
  result.maxY = fmax(a.maxY, b.maxY);
  return result;
}

// 計算兩個座標點之間的距離（簡單的歐氏距離）
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
  return sqrt(pow(lat1 - lat2, 2) + pow(lon1 - lon2, 2));
}

// 選擇最適合插入資料的子節點
int chooseSubtree(RTreeNode* node, DataItem item) {
  int bestIndex = -1;             // 最適合插入的子節點索引
  double minExpansion = DBL_MAX;  // 最小擴展面積
  double minArea = DBL_MAX;       // 最小面積

  for (int i = 0; i < node->count; i++) {
    // 計算加入該子節點後的 MBR
    BoundingBox mbr = calculateMBR(
        node->children[i]->mbr, (BoundingBox){item.latitude, item.longitude,
                                              item.latitude, item.longitude});
    // 計算子節點擴展面積
    double currentArea =
        (node->children[i]->mbr.maxX - node->children[i]->mbr.minX) *
        (node->children[i]->mbr.maxY - node->children[i]->mbr.minY);
    double expandedArea = (mbr.maxX - mbr.minX) * (mbr.maxY - mbr.minY);
    double expansion = expandedArea - currentArea;

    // 找到擴展最小的子節點
    if (expansion < minExpansion ||
        (expansion == minExpansion && currentArea < minArea)) {
      minExpansion = expansion;
      minArea = currentArea;
      bestIndex = i;
    }
  }
  return bestIndex;
}

// 插入資料後調整節點的 MBR
void adjustMBR(RTreeNode* node) {
  node->mbr.minX = node->mbr.minY = DBL_MAX;
  node->mbr.maxX = node->mbr.maxY = -DBL_MAX;
  for (int i = 0; i < node->count; i++) {
    if (node->isLeaf) {
      BoundingBox dataMBR = {node->data[i].latitude, node->data[i].longitude,
                             node->data[i].latitude, node->data[i].longitude};
      node->mbr = calculateMBR(node->mbr, dataMBR);
    } else {
      node->mbr = calculateMBR(node->mbr, node->children[i]->mbr);
    }
  }
}

// 分裂節點
void splitNode(RTreeNode** root, RTreeNode* node, DataItem item) {
  // 暫存所有資料，包括新插入的
  DataItem allData[MAX_ENTRIES + 1];
  for (int i = 0; i < node->count; i++) {
    allData[i] = node->data[i];
  }
  allData[node->count] = item;

  // 找到最遠的兩點，作為分裂的對角線
  int farthest1 = 0, farthest2 = 1;
  double maxDistance = 0;
  for (int i = 0; i < node->count + 1; i++) {
    for (int j = i + 1; j < node->count + 1; j++) {
      double distance =
          calculateDistance(allData[i].latitude, allData[i].longitude,
                            allData[j].latitude, allData[j].longitude);
      if (distance > maxDistance) {
        maxDistance = distance;
        farthest1 = i;
        farthest2 = j;
      }
    }
  }

  // 初始化兩個新節點
  RTreeNode* newNode1 = createNode(1);
  RTreeNode* newNode2 = createNode(1);

  // 分別將最遠的兩個點加入不同的組
  newNode1->data[newNode1->count++] = allData[farthest1];
  newNode2->data[newNode2->count++] = allData[farthest2];
  adjustMBR(newNode1);
  adjustMBR(newNode2);  // 更新 MBR

  // 將其餘的資料分配到兩個節點，根據 MBR 的擴展最小原則
  for (int i = 0; i < node->count + 1; i++) {
    if (i == farthest1 || i == farthest2)
      continue;

    BoundingBox mbr1 =
        calculateMBR(newNode1->mbr,
                     (BoundingBox){allData[i].latitude, allData[i].longitude,
                                   allData[i].latitude, allData[i].longitude});
    BoundingBox mbr2 =
        calculateMBR(newNode2->mbr,
                     (BoundingBox){allData[i].latitude, allData[i].longitude,
                                   allData[i].latitude, allData[i].longitude});

    // 比較 MBR 擴展面積，將資料加入擴展最小的節點
    double area1 = (mbr1.maxX - mbr1.minX) * (mbr1.maxY - mbr1.minY);
    double area2 = (mbr2.maxX - mbr2.minX) * (mbr2.maxY - mbr2.minY);
    if (area1 < area2) {
      newNode1->data[newNode1->count++] = allData[i];
      newNode1->mbr = mbr1;
    } else {
      newNode2->data[newNode2->count++] = allData[i];
      newNode2->mbr = mbr2;
    }
  }

  // 如果當前節點不是根節點（內部節點分裂）
  if (!(*root)->isLeaf) {
    // 將當前節點轉為內部節點
    node->isLeaf = 0;

    // 清空原本葉節點的資料
    node->count = 0;

    // 設置新增的兩個節點作為它的子節點
    node->children[node->count++] = newNode1;
    node->children[node->count++] = newNode2;

    adjustMBR(newNode1);
    adjustMBR(newNode2);

    // 調整當前節點的 MBR
    node->mbr = calculateMBR(newNode1->mbr, newNode2->mbr);
  }

  // 如果當前節點是根節點，創建新的根節點
  if (*root == node) {
    *root = createNode(0);
    (*root)->children[0] = newNode1;
    (*root)->children[1] = newNode2;
    (*root)->count = 2;
    adjustMBR(*root);
  }
}

// 插入資料到 R-Tree
void insert(RTreeNode** root, DataItem item) {
  RTreeNode* node = *root;

  if (node->isLeaf) {
    if (node->count < MAX_ENTRIES) {
      node->data[node->count++] = item;
      adjustMBR(node);
    } else {
      splitNode(root, node, item);
    }
  } else {
    int bestChild = chooseSubtree(node, item);
    insert(&(node->children[bestChild]), item);
    adjustMBR(node);
  }
}

// 搜尋輔助函數
void searchHelper(RTreeNode* node,
                  double latitude,
                  double longitude,
                  int n,
                  SearchResult* results) {
  if (node->isLeaf) {
    for (int i = 0; i < node->count; i++) {
      double distance = calculateDistance(
          latitude, longitude, node->data[i].latitude, node->data[i].longitude);
      for (int j = 0; j < n; j++) {
        if (results[j].distance > distance) {
          for (int k = n - 1; k > j; k--) {
            results[k] = results[k - 1];
          }
          results[j].item = node->data[i];
          results[j].distance = distance;
          break;
        }
      }
    }
  } else {
    for (int i = 0; i < node->count; i++) {
      searchHelper(node->children[i], latitude, longitude, n, results);
    }
  }
}

// 搜尋最近的 n 個資料項
SearchResult* search(RTreeNode* root,
                     double latitude,
                     double longitude,
                     int n) {
  SearchResult* results = (SearchResult*)malloc(sizeof(SearchResult) * n);
  for (int i = 0; i < n; i++) {
    results[i].distance = DBL_MAX;
  }
  searchHelper(root, latitude, longitude, n, results);
  return results;
}

// 印出 R-Tree 的結構
void printTree(RTreeNode* root, int depth) {
  for (int i = 0; i < depth; i++)
    printf("  ");
  printf("Node (count=%d, isLeaf=%d):\n", root->count, root->isLeaf);
  for (int i = 0; i < root->count; i++) {
    if (root->isLeaf) {
      for (int j = 0; j < depth + 1; j++)
        printf("  ");
      printf("Data: %s (%.2f, %.2f)\n", root->data[i].name,
             root->data[i].latitude, root->data[i].longitude);
    } else {
      printTree(root->children[i], depth + 1);
    }
  }
}

// 主函數，提供指令處理
int main() {
  RTreeNode* root = createNode(1);  // 創建根節點
  DataItem item;
  double latitude, longitude;
  SearchResult* results;

  char command[50];  // 儲存使用者輸入的命令

  while (1) {
    scanf("%s", command);  // 讀取指令
    if (strcmp("insert", command) == 0) {
      // 插入新資料
      scanf("%lf %lf %s", &item.latitude, &item.longitude, item.name);
      insert(&root, item);
    } else if (strcmp("print", command) == 0) {
      // 印出樹的結構
      printTree(root, 0);
    } else if (strcmp("exit", command) == 0) {
      // 結束程序
      break;
    } else if (strcmp("search", command) == 0) {
      // 搜尋最近的 2 個資料
      scanf("%lf %lf", &latitude, &longitude);
      results = search(root, latitude, longitude, 2);
      for (int i = 0; i < 2; i++) {
        printf("%s (%.2f, %.2f) - Distance: %.2f\n", results[i].item.name,
               results[i].item.latitude, results[i].item.longitude,
               results[i].distance);
      }
      free(results);
    } else {
      printf("Unknown command.\n");
    }
  }
  return 0;
}
