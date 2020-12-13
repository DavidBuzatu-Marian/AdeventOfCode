#include <boost/multiprecision/cpp_int.hpp>
#include <fstream>
#include <iostream>
#include <vector>
using namespace boost::multiprecision;
using namespace std;

void parseIDLine(string &line, vector<int> &ids) {
    size_t pos = 0;
    while ((pos = line.find(',')) != std::string::npos) {
        string value = line.substr(0, pos);
        if (value.compare("x") != 0) {
            ids.push_back(stoi(value));
        } else {
            ids.push_back(-1);
        }
        line.erase(0, pos + 1);
    }
    if (line.compare("x") != 0) {
        ids.push_back(stoi(line));
    }
}

int sequential(const long long &res, const vector<int> &ids) {
    for (int i = 0; i < ids.size(); ++i) {
        if (ids[i] == -1) {
            continue;
        }
        if ((res + i) % ids[i] != 0) {
            return 0;
        }
    }
    return 1;
}

cpp_int findX(cpp_int mult, const int &modulo) {
    mult %= modulo;
    if (mult == 1) {
        return 1;
    } else {
        cpp_int m = mult;
        cpp_int cnt = 1;
        while (mult % modulo != 1) {
            mult += m;
            ++cnt;
        }
        return cnt;
    }
}

cpp_int chineseDivision(const vector<int> &ids) {
    vector<cpp_int> b, Ns, x;
    cpp_int res = 0, N = 1, sum = 0;
    for (int i = 0; i < ids.size(); ++i) {
        if (ids[i] != -1) {
            if (b.size() == 0) {
                b.push_back(0);
            } else {
                b.push_back(ids[i] - i);
            }
            N *= ids[i];
        }
    }
    for (int i = 0; i < ids.size(); ++i) {
        if (ids[i] != -1) {
            Ns.push_back(N / ids[i]);

            x.push_back(findX(N / ids[i], ids[i]));
        }
    }
    for (int i = 0; i < b.size(); ++i) {
        sum += (b[i] * Ns[i] * x[i]);
    }
    return sum % N;
}
int main() {
    ifstream f("day12_1.txt");
    int ID, minTime = INT_MAX, minID = 0, minMinutes = 0;
    string idLine;
    vector<int> ids;
    f >> ID;
    f >> idLine;
    parseIDLine(idLine, ids);
    // long long result = 0;
    // while (!sequential(result, ids)) {
    //     result += ids[0];
    // }
    // cout << result << '\n';
    cout << chineseDivision(ids) << '\n';
}