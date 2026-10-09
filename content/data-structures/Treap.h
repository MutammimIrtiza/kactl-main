/**
 * Author:
 * Date: 
 * Description:
 */
#pragma once

// Indexing is 0-based
struct Treap {
  struct Node {
    int val, sum, mn, mx, size, prior, lazy, set;
    bool has_set = false, rev = false;
    Node *l = nullptr, *r = nullptr;
    Node(int v):val(v),sum(v),mn(v),mx(v),size(1), prior(rand()), lazy(0), set(0){}
  };
 
  Node* root = nullptr;
 
  int _sz(Node* t) { return t ? t->size : 0; }
  int sum(Node* t) { return t ? t->sum : 0; }
  int mn(Node* t) { return t ? t->mn : INT_MAX; }
  int mx(Node* t) { return t ? t->mx : INT_MIN; }
 
  void push(Node* t) {
    if (!t) return;
    if (t->has_set) {
      t->val = t->set;
      t->sum = t->set * _sz(t);
      t->mn = t->mx = t->set;
      if (t->l) t->l->set = t->set, t->l->has_set = 1, t->l->lazy = 0;
      if (t->r) t->r->set = t->set, t->r->has_set = 1, t->r->lazy = 0;
      t->has_set = 0;
    }
    if (t->lazy) {
      t->val += t->lazy;
      t->sum += t->lazy * _sz(t);
      t->mn += t->lazy; t->mx += t->lazy;
      if (t->l) t->l->lazy += t->lazy;
      if (t->r) t->r->lazy += t->lazy;
      t->lazy = 0;
    }
    if (t->rev) {
      swap(t->l, t->r);
      if (t->l) t->l->rev ^= 1;
      if (t->r) t->r->rev ^= 1;
      t->rev = 0;
    }
  }
 
  void upd(Node* t) {
    if (!t) return;
    push(t->l); push(t->r);
    t->size = 1 + _sz(t->l) + _sz(t->r);
    t->sum = t->val + sum(t->l) + sum(t->r);
    t->mn = min(t->val, min(mn(t->l), mn(t->r)));
    t->mx = max(t->val, max(mx(t->l), mx(t->r)));
  }
 
  void split(Node* t, int k, Node*& l, Node*& r) { 
		// l holds first k indices [0...k-1]       
		// r holds rem. indices [k...n-1]

    if (!t) { l = r = nullptr; return; }
    push(t);
    if (_sz(t->l) < k) {
      split(t->r, k - _sz(t->l) - 1, t->r, r);
      l = t;
    } else {
      split(t->l, k, l, t->l);
      r = t;
    }
    upd(t);
  }
 
  Node* merge(Node* l, Node* r) {
    push(l); push(r);
    if (!l || !r) return l ? l : r;
    if (l->prior > r->prior) { 
      l->r = merge(l->r, r); upd(l); return l;
    } else { 
      r->l = merge(l, r->l); upd(r); return r;
    }
  }

// inserts val at index pos [0 based], shifting the rest right
  void insert(int pos, int val) {
    Node *t1, *t2;
    split(root, pos, t1, t2);
    root = merge(merge(t1, new Node(val)), t2);
  }
 
  // Range add [l, r]
  void range_add(int l, int r, int v) {
    Node *t1, *t2, *t3; // [0...l-1], [l...r], [r+1...n-1] 
    split(root, r+1, t2, t3);
    split(t2, l, t1, t2);
    if (t2) t2->lazy += v;
    root = merge(merge(t1, t2), t3);
  }
 
  // Range sum [l, r]
  int range_sum(int l, int r) {
    Node *t1, *t2, *t3;
    split(root, r+1, t2, t3);
    split(t2, l, t1, t2);
    int ans = sum(t2);
    root = merge(merge(t1, t2), t3);
    return ans;
  }

  void range_set(int l, int r, int v) {
    Node *t1, *t2, *t3;
    split(root, r + 1, t2, t3); split(t2, l, t1, t2);
    if (t2) t2->set = v, t2->has_set = 1, t2->lazy = 0;
    root = merge(merge(t1, t2), t3);
  }

  int range_min(int l, int r) {
    Node *t1, *t2, *t3;
    split(root, r + 1, t2, t3); split(t2, l, t1, t2);
    int ans = mn(t2);
    root = merge(merge(t1, t2), t3);
    return ans;
  }

  int range_max(int l, int r) {
    Node *t1, *t2, *t3;
    split(root, r + 1, t2, t3); split(t2, l, t1, t2);
    int ans = mx(t2);
    root = merge(merge(t1, t2), t3);
    return ans;
  }

  int at(int pos) {
    Node* t = root;
    while (t) {
      push(t);
      if (_sz(t->l) == pos) return t->val;
      if (pos < _sz(t->l)) t = t->l;
      else pos -= _sz(t->l) + 1, t = t->r;
    }
    return 0;
  }

  int kth(int k) { return at(k); }

  void range_reverse(int l, int r) {
    Node *t1, *t2, *t3;
    split(root, r + 1, t2, t3); split(t2, l, t1, t2);
    if (t2) t2->rev ^= 1;
    root = merge(merge(t1, t2), t3);
  }
 
  void erase(int pos) {
	// [0...pos-1], [pos...pos], [pos+1...n-1]
    Node *t1, *t2, *t3; 
    split(root, pos + 1, t2, t3);
    split(t2, pos, t1, t2);
    delete t2;
    root = merge(t1, t3);
  }
 
  // add functions as needed :
 
  void f(ll a, ll b) {
    if(a >= b) return;
 
  // both cases can be generalized to ...|block|...|block|...
  // any of the ... can be null, no problem
 
    Node *t1, *t2, *t3, *t4, *t5;
    int blocksize = min(n-b, b-a);
    split(root, b+blocksize, t4, t5);
    split(t4, b, t3, t4);
    split(t3, a+blocksize, t2, t3);
    split(t2, a, t1, t2);
    Node *res = merge(t1, t4);
    res = merge(res, t3);
    res = merge(res, t2);
    res = merge(res, t5);
    root = res;
  }
 
  void print() {
    print(root); cout << nl;
  }
  void print(Node* root) { // simply in-order
    if(!root) return;
    print(root->l);
    cout << root->val << gp;
    print(root->r);
  }
};
