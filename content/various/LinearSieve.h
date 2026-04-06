/**
 * Author: ...
 * Description: ...
 * Time: ...
 * Status: ...
 */
const int N = 1000000;
vector<int> primes;
int spf[N + 1];  int phi[N + 1];  int mu[N + 1];
bool is_composite[N + 1];
// int func[MAXN], cnt[MAXN]; // Extension

void linear_sieve(int n) {
    std::fill (is_composite, is_composite + n, false);
    phi[1] = 1;  mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!is_composite[i]) {
            primes.push_back(i);
            spf[i] = i;  phi[i] = i - 1;  mu[i] = -1;
        }
        for (int p : primes) {
            if (i * 1LL * p > n) break;
            is_composite[i * p] = true;
            spf[i * p] = p;

            if (i % p == 0) {  
                phi[i * p] = phi[i] * p;
                mu[i * p] = 0;
            // func[i*prime[j]] = func[i]/cnt[i] * (cnt[i]+1);
            // cnt[i * prime[j]] = cnt[i] + 1; 
                break;
            } else { 
                phi[i * p] = phi[i] * (p - 1);
                mu[i * p] = -mu[i];
            // func[i * prime[j]] = func[i] * func[prime[j]];
            // cnt[i * prime[j]] = 1;
            }
        }
    }
}
