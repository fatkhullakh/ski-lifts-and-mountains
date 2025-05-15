#include <iostream>
#define INF 1000000000
#define MAX_LIFTS 10001
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

void push(Node heap[], int& heapSize, const Node& n) {
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

int dijkstra(
    int width, int height,
    int startRow, int startCol,
    int endRow, int endCol,
    Lift lifts[], int numLifts,
    int** map, int** dist, bool** visited
) {

    Node* heap = new Node[width * height];
    if (startRow == endRow && startCol == endCol) {
        delete[] heap;
        return 0;
    }
    int heapSize = 0;

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
            delete[] heap;
            return time;
        }

        int dr[4] = { -1, 1, 0 ,0 };
        int dc[4] = { 0, 0, -1, 1 };

        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr >= 0 && nr < height && nc >= 0 && nc < width) {
                int newTime = time + computeCost(map[r][c], map[nr][nc]);
                if (!visited[nr][nc] && newTime < dist[nr][nc]) {
                    dist[nr][nc] = newTime;
                    push(heap, heapSize, { newTime, nr, nc });
                }
            }
        }

        for (int i = 0; i < numLifts; ++i) {
            Lift& lift = lifts[i];

            if (lift.startRow == r && lift.startCol == c) {
                int waitTime = 0;
                if (time % lift.interval != 0) {
                    waitTime = lift.interval - (time % lift.interval);
                }


                int arrivalTime = time + waitTime + lift.travelTime;

                int destR = lift.endRow;
                int destC = lift.endCol;

                if (arrivalTime < dist[destR][destC]) {
                    dist[destR][destC] = arrivalTime;
                    push(heap, heapSize, { arrivalTime, destR, destC });
                }
            }
        }
    }
    delete[] heap;
    return -1;
}

int main() {
    int width, height;
    int startCol, startRow;
    int endCol, endRow;
    int numLifts;

    Lift lifts[MAX_LIFTS];

    cin >> width >> height;

    int** map = new int* [height];
    int** dist = new int* [height];
    bool** visited = new bool* [height];

    for (int i = 0; i < height; ++i) {
        map[i] = new int[width];
        dist[i] = new int[width];
        visited[i] = new bool[width];
    }

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

    int result = dijkstra(width, height, startRow, startCol, endRow, endCol, lifts, numLifts, map, dist, visited);
    cout << result << endl;

    for (int i = 0; i < height; ++i) {
        delete[] map[i];
        delete[] dist[i];
        delete[] visited[i];
    }
    delete[] map;
    delete[] dist;
    delete[] visited;

    return 0;
}
