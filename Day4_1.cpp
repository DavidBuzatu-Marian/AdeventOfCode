#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

void splitString(string &field, string &key, string &value) {
    size_t pos;
    while ((pos = field.find(":")) != string::npos) {
        key = field.substr(0, pos);
        field.erase(0, pos + 1);
    }
    value = field;
}

void getFields(string line, vector<string> &res) {
    size_t pos;
    while ((pos = line.find(" ")) != string::npos) {
        res.push_back(line.substr(0, pos));
        line.erase(0, pos + 1);
    }
    res.push_back(line);
}

int fieldIsValid(string field, string value) {
    if (field.compare("byr") == 0) {
        long year = stol(value);
        return year >= 1920 && year <= 2002;
    }
    if (field.compare("iyr") == 0) {
        long year = stol(value);
        return year >= 2010 && year <= 2020;
    }
    if (field.compare("eyr") == 0) {
        long year = stol(value);
        return year >= 2020 && year <= 2030;
    }
    if (field.compare("hgt") == 0) {
        long h = stol(value);
        long i;
        for (i = 0; i < value.size(); ++i) {
            if (value[i] < '0' || value[i] > '9') {
                break;
            }
        }
        value = value.substr(i);
        if (value.compare("cm") == 0) {
            return h >= 150 && h <= 193;
        }
        if (value.compare("in") == 0) {
            return h >= 59 && h <= 76;
        }
        return 0;  // invalid
    }
    if (field.compare("hcl") == 0) {
        long cnt = 0;
        for (char c : value) {
            if (cnt == 0 && c != '#') {
                return 0;
            } else {
                ++cnt;
                continue;
            }
            if ((c < '0' || c > '9') && (c < 'a' || c > 'f')) {
                return 0;
            }
            ++cnt;
        }

        return 1;
    }
    if (field.compare("ecl") == 0) {
        if (value.compare("amb") == 0) {
            return 1;
        }
        if (value.compare("blu") == 0) {
            return 1;
        }
        if (value.compare("brn") == 0) {
            return 1;
        }
        if (value.compare("gry") == 0) {
            return 1;
        }
        if (value.compare("grn") == 0) {
            return 1;
        }
        if (value.compare("hzl") == 0) {
            return 1;
        }
        if (value.compare("oth") == 0) {
            return 1;
        }
        return 0;
    }
    if (field.compare("pid") == 0) {
        if (value.size() > 9) {
            return 0;
        }
        long zeros = 0;
        for (long i = 0; i < value.size(); ++i) {
            if (value[i] == '0') {
                ++zeros;
            } else {
                break;
            }
        }
        try {
            long id = stol(value);
            long digits = 0;
            while (id > 0) {
                ++digits;
                id /= 10;
            }
            return digits + zeros == 9;
        } catch (std::invalid_argument ex) {
            return 0;
        }
    }
    if (field.compare("cid") == 0) {
        return 1;
    }
    return 0;
}

int allFields(unordered_map<string, string> &fields,
              const unordered_set<string> &correctFields) {
    int cnt = 0;
    for (auto it = fields.begin(); it != fields.end(); it++) {
        if (correctFields.find(it->first) != correctFields.end() &&
            fieldIsValid(it->first, it->second)) {
            cnt++;
        }
    }
    if (cnt == correctFields.size()) {
        return 1;
    }
    return 0;
}

void insertFields(unordered_set<string> &correctFields) {
    correctFields.insert("byr");
    correctFields.insert("iyr");
    correctFields.insert("eyr");
    correctFields.insert("hgt");
    correctFields.insert("hcl");
    correctFields.insert("ecl");
    correctFields.insert("pid");
    // correctFields.insert("cid");
}

int main() {
    ifstream f("day4_1.txt");
    int res = 0;
    unordered_map<string, string> fields;
    unordered_set<string> correctFields;
    insertFields(correctFields);
    string line;
    while (getline(f, line)) {
        if (line.compare("") == 0) {
            if (allFields(fields, correctFields)) {
                ++res;
            }
            fields.clear();
        } else {
            string key, value;
            vector<string> fieldsRead;
            getFields(line, fieldsRead);
            for (string field : fieldsRead) {
                splitString(field, key, value);
                fields.insert({key, value});
            }
        }
    }
    if (allFields(fields, correctFields)) {
        ++res;
    }
    cout << res << '\n';
}