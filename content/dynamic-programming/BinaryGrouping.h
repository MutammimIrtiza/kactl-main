/**
 * Author: 
 * Date :
 * License: CC0
 * Source: cp-algorithms.com
 * Description: Split bounded-multiplicity items into 0-1 bundles.
 * Each item is given as \{weight, value, count\}; the result contains
 * pairs of total weight and value suitable for 0-1 knapsack.
 * Time: Bundle generation $O(\sum_i \log k_i)$; using the bundles
 * in 0-1 knapsack takes $O(W \sum_i \log k_i)$.
 * Status: Tested
 */
vector<pair<int, int>> binaryGrouping(vector<array<int, 3>> items) {
	vector<pair<int, int>> res;
	for (auto [w, v, k] : items) {
		if (!k) continue;
		for (int c = 1; k > c; c *= 2) {
			k -= c;
			res.emplace_back(c * w, c * v);
		}
		res.emplace_back(k * w, k * v);
	}
	return res;
}
