/**
 * Author: ...
 * Description: ...
 * Time: ...
 * Status: ...
 */
sz - 2 // no. of distinct palindromes
no. of unique palindromes is linear !!! may use with hashing

use cnt during construction. After extend(i):
last = node representing the longest palindrome ending at pos i
pt.t[pt.last].cnt; // no. of pals ending here, smaller included

use oc after calc. 
t[i].oc //no. of occurence of this exact pal[smaller excluded]
sum(t[i].oc) // total no. of palindromic substrings

struct PalindromicTree {
  struct node {
    int nxt[26]; // transitions (adding char to both ends)
    int len;     // length of palindrome
    int st, en;  // start and end index in original string
    int link;    // suffix link (largest palindromic suffix)
    ll cnt;      // no. of palindromic suffixes ending here
    ll oc;       // no. of occurrences of this palindrome
  };
  string s;
  vector<node> t;
  int sz, last;
  PalindromicTree() {}
  PalindromicTree(string _s) {
    s = _s;
    int n = s.size();
    t.clear();
    t.resize(n + 9);
    sz = 2, last = 2;
    t[1].len = -1, t[1].link = 1;
    t[2].len = 0, t[2].link = 1;
  }
 int extend(int pos){//returns 1 if it creates a new palindrome
    int cur = last, curlen = 0;
    int ch = s[pos] - 'a';
    while (1) {
      curlen = t[cur].len;
      if(pos-1-curlen >= 0 && s[pos-1-curlen] == s[pos]) break;
      cur = t[cur].link;
    }
    if (t[cur].nxt[ch]) {
      last = t[cur].nxt[ch];
      t[last].oc++;
      return 0;
    }
    sz++;
    last = sz;
    t[sz].oc = 1;
    t[sz].len = t[cur].len + 2;
    t[cur].nxt[ch] = sz;
    t[sz].en = pos;
    t[sz].st = pos - t[sz].len + 1;
    if (t[sz].len == 1) {
      t[sz].link = 2;
      t[sz].cnt = 1;
      return 1;
    }
    while (1) {
      cur = t[cur].link;
      curlen = t[cur].len;
      if (pos-1-curlen >= 0 && s[pos-1-curlen] == s[pos]) {
        t[sz].link = t[cur].nxt[ch];
        break;
      }
    }
    t[sz].cnt = 1 + t[t[sz].link].cnt;
    return 1;
  }
  void calc_occurrences() {
    for (int i = sz; i >= 3; i--) t[t[i].link].oc += t[i].oc;
  }
};