#include <fstream>
#include <iostream>
#include <set>
#include <unordered_set>

using namespace std;

struct cube {
    long x, y, z;
};

struct quadrub {
    long x, y, z, w;
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

inline bool operator==(const quadrub &c1, const quadrub &c2) {
    return tie(c1.x, c1.y, c1.z, c1.w) == tie(c2.x, c2.y, c2.z, c2.w);
}

inline bool operator!=(const quadrub &c1, const quadrub &c2) {
    return tie(c1.x, c1.y, c1.z, c1.w) != tie(c2.x, c2.y, c2.z, c2.w);
}

inline bool operator>(const quadrub &c1, const quadrub &c2) {
    return tie(c1.x, c1.y, c1.z, c1.w) > tie(c2.x, c2.y, c2.z, c2.w);
}

inline bool operator<(const quadrub &c1, const quadrub &c2) {
    return tie(c1.x, c1.y, c1.z, c1.w) < tie(c2.x, c2.y, c2.z, c2.w);
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

int countActive2(struct quadrub &currQuadrub, const set<quadrub> &quadrubs) {
    int cnt = 0;
    for (long x = currQuadrub.x - 1; x <= currQuadrub.x + 1 && cnt < 4; ++x) {
        for (long y = currQuadrub.y - 1; y <= currQuadrub.y + 1 && cnt < 4;
             ++y) {
            for (long z = currQuadrub.z - 1; z <= currQuadrub.z + 1 && cnt < 4;
                 ++z) {
                for (long w = currQuadrub.w - 1;
                     w <= currQuadrub.w + 1 && cnt < 4; ++w) {
                    struct quadrub neigh = (struct quadrub){x, y, z, w};
                    if (neigh != currQuadrub && quadrubs.count(neigh) > 0) {
                        ++cnt;
                    }
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

void round_quadrub(set<quadrub> &quadrubs) {
    set<quadrub> next_round;
    set<quadrub> visited;
    for (const auto &quadrub : quadrubs) {
        for (long currX = quadrub.x - 1; currX <= quadrub.x + 1; ++currX) {
            for (long currY = quadrub.y - 1; currY <= quadrub.y + 1; ++currY) {
                for (long currZ = quadrub.z - 1; currZ <= quadrub.z + 1;
                     ++currZ) {
                    for (long currW = quadrub.w - 1; currW <= quadrub.w + 1;
                         ++currW) {
                        struct quadrub currQuadrub =
                            (struct quadrub){currX, currY, currZ, currW};
                        if (!visited.count(currQuadrub)) {
                            visited.insert(currQuadrub);
                            int cntActive = countActive2(currQuadrub, quadrubs);
                            if (quadrubs.count(currQuadrub) &&
                                (cntActive == 2 || cntActive == 3)) {
                                next_round.insert(currQuadrub);
                            } else if (!quadrubs.count(currQuadrub) &&
                                       cntActive == 3) {
                                next_round.insert(currQuadrub);
                            }
                        }
                    }
                }
            }
        }
    }
    quadrubs = next_round;
}

int main() {
    ifstream f("day17_1.txt");
    set<quadrub> quadrubs;
    long x = 0, y = 0, z = 0, w = 0;
    while (!f.eof()) {
        string line;
        getline(f, line);
        for (const char &c : line) {
            if (c == '#') {
                quadrubs.insert(quadrub{x, y, z, w});
            }
            ++x;
        }
        ++y;
        x = 0;
    }
    int round = 0;
    while (round < 6) {
        round_quadrub(quadrubs);
        ++round;
    }
    cout << quadrubs.size() << '\n';
}