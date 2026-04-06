/**
 * Author: chatgpt
 * Date: ...
 * Source: ...
 * Description: ...
 * Time: $O(\log N)$
 * Status: ...
 */
#pragma once

// Indexing is 0-based
struct Treap {
  struct Node {
    int val, sum, size, prior, lazy;
    Node *l = nullptr, *r = nullptr;
    Node(int v):val(v),sum(v),size(1), prior(rand()), lazy(0){}
  };
 
  Node* root = nullptr;
 
  int _sz(Node* t) { return t ? t->size : 0; }
  int sum(Node* t) { return t ? t->sum : 0; }
 
  void push(Node* t) {
    if (!t || t->lazy == 0) return;
    t->val += t->lazy;
    t->sum += t->lazy * _sz(t);
    if (t->l) t->l->lazy += t->lazy;
    if (t->r) t->r->lazy += t->lazy;
    t->lazy = 0;
  }
 
  void upd(Node* t) {
    if (!t) return;
    push(t->l); push(t->r);
    t->size = 1 + _sz(t->l) + _sz(t->r);
    t->sum = t->val + sum(t->l) + sum(t->r);
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

