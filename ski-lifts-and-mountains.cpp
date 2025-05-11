#include <iostream>

#define INF 1000000000
#define MAX_W 100
#define MAX_H 100
#define MAX_LIFTS 100

using namespace std;

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




int main() {
    int width, height;
    int startCol, startRow;
    int endCol, endRow;
    int numLifts;

    Lift lifts[MAX_LIFTS];
    int map[MAX_H][MAX_W];

    readInput(width, height, startCol, startRow, endCol, endRow, numLifts, lifts, map);

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            cout << map[row][col];
        }
        cout << endl;
    }
    

    return 0;
}