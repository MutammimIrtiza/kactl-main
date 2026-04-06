/**
 * Author: ...
 * Description: ...
 * Time: ...
 * Status: ...
 */
main:
// Sum of elements <= N implies that every element is <= N
vector<int> freq(N + 1, 0);
for (int i = 0; i < N; i++) {
    int x;  cin >> x;  freq[x]++;
}
vector<pair<int, int>> compressed;
for (int i = 1; i <= N; i++) {
    if (freq[i] > 0) compressed.emplace_back(i, freq[i]);
}
vector<int> dp(N + 1, 0);  dp[0] = 1;
for (const auto &[w, k] : compressed) {
    vector<int> ndp = dp;
    for (int p = 0; p < w; p++) {
        int sum = 0;
        for(int mult = p, cnt = 0; mult<=N; mult += w, cnt++){
            if (cnt > k) {
                sum -= dp[mult - w * cnt];  cnt--;
            }
            if (sum > 0) ndp[mult] = 1;  sum += dp[mult];
        }
    }
    swap(dp, ndp);
}
cout << "Possible subset sums are:\n";
for (int i = 0; i <= N; i++) {
    if (dp[i] > 0) cout << i << " ";
}