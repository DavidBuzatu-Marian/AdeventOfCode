#include <fstream>
#include <iostream>
#include <set>
#include <unordered_set>

using namespace std;

struct cube {
    long x, y, z;
};

inline bool operator==(const cube &c1, const cube &c2) {
    return tie(c1.x, c1.y, c1.z) == tie(c2.x, c2.y, c2.z);
}

inline bool operator!=(const cube &c1, const cube &c2) {
    return tie(c1.x, c1.y, c1.z) != tie(c2.x, c2.y, c2.z);
}

inline bool operator>(const cube &c1, const cube &c2) {
    return tie(c1.x, c1.y, c1.z) > tie(c2.x, c2.y, c2.z);
}

inline bool operator<(const cube &c1, const cube &c2) {
    return tie(c1.x, c1.y, c1.z) < tie(c2.x, c2.y, c2.z);
}

int countActive(struct cube &currCube, const set<cube> &cubes) {
    int cnt = 0;
    for (long x = currCube.x - 1; x <= currCube.x + 1 && cnt < 4; ++x) {
        for (long y = currCube.y - 1; y <= currCube.y + 1 && cnt < 4; ++y) {
            for (long z = currCube.z - 1; z <= currCube.z + 1 && cnt < 4; ++z) {
                struct cube neigh = (struct cube){x, y, z};
                if (neigh != currCube && cubes.count(neigh) > 0) {
                    ++cnt;
                }
            }
        }
    }
    return cnt;
}

void round_cube(set<cube> &cubes) {
    set<cube> next_round;
    set<cube> visited;
    for (const auto &cube : cubes) {
        for (long currX = cube.x - 1; currX <= cube.x + 1; ++currX) {
            for (long currY = cube.y - 1; currY <= cube.y + 1; ++currY) {
                for (long currZ = cube.z - 1; currZ <= cube.z + 1; ++currZ) {
                    struct cube currCube = (struct cube){currX, currY, currZ};
                    if (!visited.count(currCube)) {
                        visited.insert(currCube);
                        int cntActive = countActive(currCube, cubes);
                        if (cubes.count(currCube) &&
                            (cntActive == 2 || cntActive == 3)) {
                            next_round.insert(currCube);
                        } else if (!cubes.count(currCube) && cntActive == 3) {
                            next_round.insert(currCube);
                        }
                    }
                }
            }
        }
    }
    cubes = next_round;
}

int main() {
    ifstream f("day17_1.txt");
    set<cube> cubes;
    long x = 0, y = 0, z = 0;
    while (!f.eof()) {
        string line;
        getline(f, line);
        for (const char &c : line) {
            if (c == '#') {
                cubes.insert(cube{x, y, z});
            }
            ++x;
        }
        ++y;
        x = 0;
    }
    int round = 0;
    while (round < 6) {
        round_cube(cubes);
        ++round;
    }
    cout << cubes.size() << '\n';
}