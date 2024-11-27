#include <iostream>
#include "queue.cpp"
#include <vector>
using namespace std;

//luu trang thai
struct State {
    int steps; 
    int x, y;  // toa do hien tai

    State(int s, int x, int y) : steps(s), x(x), y(y) {}
};

// ktra toa do hop le
bool is_valid(int x, int y, int n, int m) {
    return (0 <= x && x < n && 0 <= y && y < m);
}

int solve(int n, int m, int x1, int y1, int x2, int y2) {
    // Cac buoc di chuyen cua con ma
    int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

    //mang danh dau cac o da tham
    vector<vector<bool>> is_visited(n, vector<bool>(m, false));

    //BFS luu trang thai
    queue<State> q;
    q.push(State(0, x1, y1)); 
    is_visited[x1][y1] = true;

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        //ktra den dich
        if (current.x == x2 && current.y == y2) {
            return current.steps;
        }

        // Duyet cac buoc di chuyen
        for (int i = 0; i < 8; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            // Ktra o moi hop le, chua tham
            if (is_valid(nx, ny, n, m) && !is_visited[nx][ny]) {
                q.push(State(current.steps + 1, nx, ny));
                is_visited[nx][ny] = true;
            }
        }
    }
    return -1;
}

int main() {
    int n, m;
    cout<< "Nhap n va m: ";
    cin >> n >> m;
    int x1, y1, x2, y2;
    cout<<"Nhap toa do diem thu nhat: ";
    cin >> x1 >> y1;
    cout<<"Nhap toa do diem thu hai: ";
    cin>> x2>> y2;

    // chuyen doi chi so 1 thanh 0
    x1--; y1--; x2--; y2--;
    if(solve(n, m, x1, y1, x2, y2) != -1){
        cout <<"So nuoc di it nhat de con ma di tu ("<<x1+1<<", "<<y1+1<<") den ("<<x2+1<<", "<<y2+1<<") la: "<< 
                                                    solve(n, m, x1, y1, x2, y2) << endl;
    }
    else{
        cout <<solve(n, m, x1, y1, x2, y2) << endl;
    }
    
    return 0;
}