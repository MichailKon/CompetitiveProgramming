#include <bits/stdc++.h>

template<class T, int N>
class sparseTable {
private:
    std::size_t size;
    int logs[N + 1];
    std::vector<std::array<T, N>> table;
    std::function<T(const T, const T)> function;

    constexpr inline void fillLogs() {
        logs[1] = 0;
        for (int i = 2; i <= size; i++) {
            logs[i] = logs[i >> 1] + 1;
        }
    }

    void inline fillTable() {
        for (int k = 1; k <= logs[size]; k++) {
            std::size_t nowSize = table[k - 1].size() - (1 << (k - 1));
            for (int i = 0; i < nowSize; i++) {
                table[k][i] = function(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

public:
    template<typename ForwardIterator>
    void build(ForwardIterator begin, ForwardIterator end) {
        // build logs
        size = std::distance(begin, end);
        fillLogs();
        // build table
        table.resize(logs[size] + 1);
        std::copy(begin, end, table[0].begin());
        fillTable();
    }

    explicit sparseTable(std::function<T(const T, const T)> function) : function(std::move(function)), size(0) {}

    sparseTable() : function([](const T &a, const T &b) { return std::min(a, b); }), size(0) {}

    size_t inline getSize() const {
        return size;
    }

    T inline get(const int &l, const int &r) const {
        int k = logs[r - l];
        return function(table[k][l], table[k][r - (1 << k) + 1]);
    }
};

int f(const int &a, const int &b) {
    return std::max(a, b);
}

int main() {
    // std::vector<int> a = { 1, 2, 3, 2, 5 };
    // int a[] = { 1, 2, 3, 2, 5 };
    std::forward_list<int> a;
    a.assign({1, 2, 3, 4, 5});

    sparseTable<int, 5> st1;
    sparseTable<int, 5> st2([](const int &a, const int &b) { return std::max(a, b); });
    sparseTable<int, 5> st3(f);

    // st1.build(a.begin(), a.end());
    // st1.build(a, a + 5);
    st1.build(a.begin(), a.end());

    std::cout << st1.get(0, 3) << '\n';
}
