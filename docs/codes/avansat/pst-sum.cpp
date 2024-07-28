#include <iostream>
#include <vector>
#include <bits/stdc++.h>

typedef long long ll;

struct Node {
  ll sum;
  Node* l;
  Node* r;
  Node() {
    sum = 0;
    l = r = nullptr;
  }
  Node(ll _sum, Node* _l, Node* _r) {
    sum = _sum;
    l = _l;
    r = _r;
  }
};

Node* build(int tl, int tr, int* a) {
  if (tl == tr) {
    return new Node {
      a[tl - 1],
      NULL, NULL
    };
  } else {
    int mid = (tl + tr) / 2;
    Node* ret = new Node();
    ret -> l = build(tl, mid, a);
    ret -> r = build(mid + 1, tr, a);
    ret -> sum = ret -> l -> sum + ret -> r -> sum;
    return ret;
  }
}

Node* update(const Node* node, int tl, int tr, int p, int v) {
  if (tl == tr) {
    return new Node {
      v,
      NULL,
      NULL
    };
  } else {
    Node *ret = new Node();
    *ret = *node;
    int mid = (tl + tr) / 2;
    if (p <= mid) {
      ret -> l = update(node -> l, tl, mid, p, v);
    } else {
      ret -> r = update(node -> r, mid + 1, tr, p, v);
    }
    return ret;
  }
}

ll query(const Node* node, int tl, int tr, int ql, int qr) {
    if (ql <= tl && tr <= qr) {
      return node -> sum;
    } else {
      int mid = (tl + tr) / 2;
      ll ret = 0;
      if (ql <= mid) {
        ret += query(node -> l, tl, mid, ql, qr);
      }
      if (mid < qr) {
        ret += query(node -> r, mid + 1, tr, ql, qr);
      }
      return ret;
    }
}

int n;
std::vector<Node*> versions;

void init(int _n, int* a) {
  n = _n;
  versions.push_back(build(1, n, a));
}

void updateValue(int pos, int value) {
  versions.push_back(update(versions.back(), 1, n, pos, value)); // creem o versiune nouă, pornim inițial cu versiunea trecută
}

ll sequenceQuery(int l, int r, int t) {
  return query(versions[t], 1, n, l, r);
}

int main() {
    return 0;
}