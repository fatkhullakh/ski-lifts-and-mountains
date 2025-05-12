#include <iostream>

#define INF 1000000000
#define MAX_W 100
#define MAX_H 100
#define MAX_LIFTS 100

using namespace std;

struct Node {
    int time;
    int row;
    int col;
};

struct Lift {
    int startCol, startRow;
    int endCol, endRow;
    int travelTime;
    int interval;
};

void readInput(int& width, int& height, int& startCol, int& startRow, int& endCol, int& endRow, int& numLifts, Lift lifts[MAX_LIFTS], int map[MAX_H][MAX_W]) {
    
    cin >> width >> height;
    cin >> startCol >> startRow;
    cin >> endCol >> endRow;
    cin >> numLifts;

    for (int i = 0; i < numLifts; ++i) {
        cin >> lifts[i].startCol >> lifts[i].startRow >> lifts[i].endCol >> lifts[i].endRow >> lifts[i].travelTime >> lifts[i].interval;
    }

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            cin >> map[row][col];
        }
    }
}

int computeCost(int from, int to) {
    if (to > from) {
        return (to - from) + 1;
    }
    else {
        return 1;
    }
}

Node pop(Node heap[], int& heapSize) {
    Node result = heap[0];

    heapSize--;
    heap[0] = heap[heapSize];

    int i = 0;

    while (true) {
        int left = i * 2 + 1;
        int right = i * 2 + 2;
        int smallest = i;


        if (left < heapSize && heap[left].time < heap[smallest].time) {
            smallest = left;
        }

        if (right < heapSize && heap[right].time < heap[smallest].time) {
            smallest = right;
        }

        if (smallest == i) {
            break;
        }

        Node temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;

        i = smallest;
    }

    return result;
}

void push(Node heap[], int& heapSize, Node n) {
    int i = heapSize;
    heap[i] = n;

    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[i].time < heap[parent].time) {
            Node temp = heap[i];
            heap[i] = heap[parent];
            heap[parent] = temp;

            i = parent;
        }
        else {
            break;
        }
    }
    heapSize++;
}

int dijkstra(int width, int height, int startRow, int startCol, int endRow, int endCol, Lift lifts[MAX_LIFTS], int numLifts, int map[MAX_H][MAX_W]) {
    Node heap[MAX_H * MAX_W];
    int heapSize = 0;

    int dist[MAX_H][MAX_W];
    bool visited[MAX_H][MAX_W];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            dist[i][j] = INF;
            visited[i][j] = false;
        }
    }

    dist[startRow][startCol] = 0;
    push(heap, heapSize, { 0, startRow, startCol });

    while (heapSize > 0) {
        Node current = pop(heap, heapSize);
        int r = current.row;
        int c = current.col;
        int time = current.time;

        if (visited[r][c]) continue;
        visited[r][c] = true;

        if (r == endRow && c == endCol) {
            return time;
        }

        int dr[4] = { -1, 1, 0 ,0 };
        int dc[4] = { 0, 0, -1, 1 };

        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr >= 0 && nr < height && nc >= 0 && nc < width) {
                int newTime = time + computeCost(map[r][c], map[nr][nc]);
                if (newTime < dist[nr][nc]) {
                    dist[nr][nc] = newTime;
                    push(heap, heapSize, { newTime, nr, nc });
                }
            }
        }

    }
    

    return -1;


}



int main() {
    int width, height;
    int startCol, startRow;
    int endCol, endRow;
    int numLifts;

    Lift lifts[MAX_LIFTS];
    int map[MAX_H][MAX_W];

    readInput(width, height, startCol, startRow, endCol, endRow, numLifts, lifts, map);

    int result = dijkstra(width, height, startRow, startCol, endRow, endCol, lifts, numLifts, map);
    cout << result << endl;


    return 0;
}