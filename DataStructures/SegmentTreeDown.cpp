#include <bits/stdc++.h>

template<class T, int N>
class segmentTreeDown {
private:
    std::size_t size;
    T tree[2 * N]{};
    T neutralElement;
    std::function<T(const T, const T)> function;
public:
    segmentTreeDown() :
            size(N), function([](const T &a, const T &b) { return a + b; }), neutralElement(T()) {}

    explicit segmentTreeDown(std::function<T(const T, const T)> function, const T &neutral = T()) :
            size(N), function(std::move(function)), neutralElement(neutral) {}

    explicit segmentTreeDown(const T &neutral) :
            size(N), function([](const T &a, const T &b) { return a + b; }), neutralElement(neutral) {}

    template<typename ForwardIterator>
    void build(ForwardIterator begin, ForwardIterator end) {
        std::copy(begin, end, tree + N);
        for (int i = N - 1; i > 0; i--) tree[i] = function(tree[i << 1], tree[i << 1 | 1]);
    }

    T get(const int l1, const int r1) const {
        int l = l1, r = r1;
        l += N, r += N;

        T ans = neutralElement;
        while (l < r) {
            if (l & 1) ans = function(ans, tree[l]);
            if (!(r & 1)) ans = function(ans, tree[r]);
            l = (l + 1) / 2;
            r = (r - 1) / 2;
        }

        if (l == r) ans = function(ans, tree[l]);
        return ans;
    }

    T get(const int &ind) const {
        return get(ind, ind);
    }

    std::size_t inline getSize() const {
        return size;
    }

    T inline getNeutralElement() const {
        return neutralElement;
    }

    void inline setNeutralElement(const T &newVal) {
        neutralElement = newVal;
    }

    void upd(int ind, const T &newVal) {
        ind += N;
        tree[ind] = newVal;
        ind >>= 1;
        while (ind > 0) {
            tree[ind] = function(tree[ind << 1], tree[ind << 1 | 1]);
            ind >>= 1;
        }
    }
};

int f(const int &a, const int &b) {
    return std::max(a, b);
}

int main() {
    segmentTreeDown<int, 5> st; // sum
    segmentTreeDown<int, 5> st1(f); // max
    st1.setNeutralElement(INT_MIN);
    segmentTreeDown<int, 5> st2([](const int &a, const int &b) { return std::min(a, b); }, INT_MAX); // min

    int a[] = {1, 2, 5, 3, 10};
    st.build(a, a + 5);
    st1.build(a, a + 5);
    st2.build(a, a + 5);
    std::cout << st.get(0, 3) << ' ' << st1.get(1, 4) << ' ' << st2.get(2, 3) << '\n';
    st.upd(2, 100);
    std::cout << st.get(0, 3) << ' ' << st1.get(1, 4) << ' ' << st2.get(2, 3) << '\n';

    std::vector<int> b = {1, 2, 5, 3, 10};
    st.build(b.begin(), b.end());
    st1.build(b.begin(), b.end());
    st2.build(b.begin(), b.end());
    std::cout << st.get(0, 3) << ' ' << st1.get(1, 4) << ' ' << st2.get(2, 3) << '\n';
    st.upd(2, 100);
    std::cout << st.get(0, 3) << ' ' << st1.get(1, 4) << ' ' << st2.get(2, 3) << '\n';

    std::forward_list<int> c;
    c.assign({1, 2, 5, 3, 10});
    st.build(c.begin(), c.end());
    st1.build(c.begin(), c.end());
    st2.build(c.begin(), c.end());
    std::cout << st.get(0, 3) << ' ' << st1.get(1, 4) << ' ' << st2.get(2, 3) << '\n';
    st.upd(2, 100);
    std::cout << st.get(0, 3) << ' ' << st1.get(1, 4) << ' ' << st2.get(2, 3) << '\n';
}
