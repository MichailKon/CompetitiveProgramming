#include <bits/stdc++.h>

template<class T>
class sparseTable {
private:
    unsigned int size;
    std::vector <std::vector<T>> table;
    std::vector<int> logs;
    std::function<T(const T, const T)> function;

    void fillLogs() {
        logs.assign(size + 1, 0);
        logs.shrink_to_fit();
        logs[1] = 0;
        for (int i = 2; i <= size; i++) {
            logs[i] = logs[i >> 1] + 1;
        }
    }

    void fillTable() {
        for (int k = 1; k <= logs[size]; k++) {
            unsigned int nowSize = table[k - 1].size() - (1 << (k - 1));
            table[k].resize(nowSize);
            table[k].shrink_to_fit();
            for (int i = 0; i < nowSize; i++) {
                table[k][i] = function(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

public:
    template<typename _RandomAccessIterator>
    void build(const _RandomAccessIterator begin, const _RandomAccessIterator end) {
        // build logs
        size = end - begin;
        fillLogs();
        // build table
        table.resize(logs[size] + 1);
        table[0].resize(size);
        table[0].shrink_to_fit();
        for (int i = 0; i < size; i++) table[0][i] = *(begin + i);
        fillTable();
    }

    sparseTable(const std::function<T(const T, const T)> &function) : function(function), size(0) {}

    sparseTable() : function([](const T &a, const T &b) { return std::min(a, b); }), size(0) {}

    unsigned int getSize() const {
        return size;
    }

    T get(const int &l, const int &r) const {
        int k = logs[r - l + 1];
        return function(table[k][l], table[k][r - (1 << k) + 1]);
    }
};

int f(const int &a, const int &b) {
	return std::max(a, b);
}

int main() {
	//	std::vector<int> a = { 1, 2, 3, 2, 5 };
    int a[] = {1, 2, 3, 2, 5};

    sparseTable<int> st1;
    sparseTable<int> st2([](const int &a, const int &b) { return std::max(a, b); });
    sparseTable<int> st3(f);

	//	st.build(a.begin(), a.end());
    st1.build(a, a + 5);

    std::cout << st1.get(0, 1) << '\n';
}
