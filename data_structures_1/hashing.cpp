#include <iostream>
#include <vector>
#include <list>
#include <string>

const int kMod = 100003;
const int kP = 31;

class TStringSet {
public:
    TStringSet() : table_(kMod) {}

    void Add(const std::string& s) {
        int hash = Hash(s);
        auto& chain = table_[hash];
        for (const auto& str : chain) {
            if (str == s) {
                return;
            }
        }
        chain.push_back(s);
    }

    void Remove(const std::string& s) {
        int hash = Hash(s);
        auto& chain = table_[hash];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (*it == s) {
                chain.erase(it);
                return;
            }
        }
    }

    bool Contains(const std::string& s) const {
        int hash = Hash(s);
        const auto& chain = table_[hash];
        for (const auto& str : chain) {
            if (str == s) {
                return true;
            }
        }
        return false;
    }

private:
    std::vector<std::list<std::string>> table_;

    int Hash(const std::string& s) const {
        long long hash = 0;
        long long p_pow = 1;
        for (char c : s) {
            hash = (hash + (c - 'a' + 1) * p_pow) % kMod;
            p_pow = (p_pow * kP) % kMod;
        }
        return static_cast<int>(hash);
    }
};

int main() {
    TStringSet set;
    std::vector<std::pair<char, std::string>> operations;
    std::string operation, word;

    while (std::cin >> operation && operation != "#") {
        std::cin >> word;
        operations.emplace_back(operation[0], word);
    }

    std::vector<std::string> results;

    for (const auto& op : operations) {
        char type = op.first;
        const std::string& str = op.second;

        if (type == '+') {
            set.Add(str);
        } else if (type == '-') {
            set.Remove(str);
        } else if (type == '?') {
            results.push_back(set.Contains(str) ? "YES" : "NO");
        }
    }

    for (const auto& result : results) {
        std::cout << result << std::endl;
    }
    return 0;
}