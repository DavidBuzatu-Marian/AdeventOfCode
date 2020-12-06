#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

void updateQuestions(unordered_map<char, int> &questions, const string &line) {
    for (const char c : line) {
        questions[c]++;
    }
}

int countAllYes(const unordered_map<char, int> &questions,
                const int &nrPeople) {
    int cnt = 0;
    for (auto it = questions.begin(); it != questions.end(); ++it) {
        if (it->second == nrPeople) {
            ++cnt;
        }
    }
    return cnt;
}

int main() {
    fstream f("day5_1.txt");
    unordered_map<char, int> questions;
    int res = 0;
    int nrPeople = 0;
    while (!f.eof()) {
        string line;
        getline(f, line);
        if (line.compare("") == 0) {
            res += countAllYes(questions, nrPeople);
            questions.clear();
            nrPeople = 0;
        } else {
            ++nrPeople;
            updateQuestions(questions, line);
        }
    }
    res += countAllYes(questions, nrPeople);
    cout << res << '\n';
}