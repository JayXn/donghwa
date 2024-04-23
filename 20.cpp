#include <iostream>    
#include <utility>  
#include <cstring>
#include <stack>

using namespace std;

class MazeSolver {
private:
    char maze[1000][1000];
    stack<pair<int, int>> p; 

public:
    void createGrid(int M, int N) {
        for (int i = 0; i < (N * 2) + 1; ++i)  
            maze[0][i] = (i % 2 == 1 ? '_' : ' ');
        maze[0][N*2] = '\0';
        for (int j = 1; j < M + 1; ++j) { 
            for (int k = 0; k < (N * 2) + 1; ++k) 
                maze[j][k] = (k % 2 == 0 ? '|' : '_');
        }
    }

    void solve(int t) {
        while (t--) {
            int M, N, x, y;
            cin >> M >> N >> x >> y;
            createGrid(M, N);

            int checkX = (M+1) - x, checkY = y; // 將起始位置轉換成陣列中的座標
            int count = 2; // 初始化為2，因為起始位置和終點位置都已經有了
            p.push({checkX, checkY});
            char cmd;
            while (cin >> cmd && count < M * N) { 
                if (cmd == 'U') {
                    maze[--checkX][checkY] = ' ';
                    p.push({checkX, checkY});
                    ++count;
                }
                else if (cmd == 'D') {
                    maze[checkX][checkY] = ' ';
                    p.push({checkX, checkY});
                    ++checkX;
                    ++count;
                }
                else if (cmd == 'L') {
                    maze[checkX][--checkY] = ' ';
                    --checkY;
                    p.push({checkX, checkY});
                    ++count;
                }
                else if (cmd == 'R') {
                    maze[checkX][++checkY] = ' ';
                    ++checkY;
                    p.push({checkX, checkY});
                    ++count;
                } 
                else { 
                    int num;
                    cin >> num;
                    for (int i = 1; i <= num; ++i) p.pop();
                    checkX = p.top().first, checkY = p.top().second;
                }
            }
            if (cmd == 'U') maze[--checkX][checkY] = ' ';
            else if (cmd == 'D') maze[++checkX][checkY] = ' ';
            else if (cmd == 'L') maze[checkX][--checkY] = ' ';
            else if (cmd == 'R') maze[checkX][++checkY] = ' ';

            for (int i = 0; i < M + 1; ++i) {
                for (int j = 0; j < (N * 2) + 1; ++j) {
                    if (i == 0 && j == N * 2) continue;
                    else cout << maze[i][j];
                }
                cout << endl;
            }
            memset(maze, ' ', sizeof(maze));
            cout << endl;
        }
    }
};

int main() {
    int t;
    cin >> t;
    MazeSolver mazeSolver;
    mazeSolver.solve(t);
    return 0;
}
