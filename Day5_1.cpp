#include <fstream>
#include <iostream>
#include <unordered_set>

using namespace std;

void updateQuestions(unordered_set<char> &questions, const string &line) {
    for (const char c : line) {
        questions.insert(c);
    }
}

int main() {
    fstream f("day5_1.txt");
    unordered_set<char> questions;
    int res = 0;
    while (!f.eof()) {
        string line;
        getline(f, line);
        if (line.compare("") == 0) {
            res += questions.size();
            questions.clear();
        } else {
            updateQuestions(questions, line);
        }
    }
    res += questions.size();
    cout << res << '\n';
}