/**
 * Author: idk
 * Description: idk
 * Time: idk
 * Status: idk
 */
template <typename T>
struct ordered_multiset {
    using Tpair = pair<T, int>;
    tree<Tpair, null_type, less<Tpair>, rb_tree_tag \
     tree_order_statistics_node_update> t;
    int _idx = 0;
    void insert(const T &x) { t.insert({x, _idx++}); }
    void erase(const T &x) {
        auto it = t.lower_bound({x, 0});
        if (it != t.end() && it->first == x) t.erase(it); 
    }
    int order_of_key(const T &x) const {
        return t.order_of_key({x, 0}); 
    }
    T find_by_order(int k) const {
        auto it = t.find_by_order(k);
        if (it == t.end()) return 1000000000;
        return it->first; 
    }
    int size() const { return t.size(); }
    bool empty() const { return t.empty(); }
};