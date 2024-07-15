---
tags:
    - structuri de date
    - arbori de intervale
---

**Autor**: Luca Mureșan, Vlad Tutunaru

## Introducere

Arborele de intervale dinamic poate fi folosit in probleme in care avem nevoie sa facem operatii pe o structura de date cu dimensiuni foarte mari $(N \leq 10^{12})$. 

!!! info "Definiție" 
    Arborele de intervale dinamic este un arbore de intervale care reține doar nodurile necesare. Fiecare query vizitează doar $ \log_2 N$ noduri, deci numarul de noduri de care avem nevoie este $Q \log_2 N$.

Putem sa implementăm aceasta structura de date ca pe un arbore de intervale clasic insa in loc să folosim un array, pentru fiecare nod vom reține doi pointeri, unul pentru fiecare fiu. 

## Problema [Large Queries](https://kilonova.ro/problems/3165)

Problema aceasta poate fi rezolvată cu un arbore de intervale static dacă $1 \leq N \leq 2 \cdot 10^5$. Insă în cazul de față $1 \leq N \leq 10^9$ deci ar trebui $4 \cdot 10^9$ noduri, care este prea mult. 

Problema trebuie rezolvată **online**, deci trebuie sa folosim un arbore de intervale dinamic.

## Implementare
```cpp
#include <iostream>
#include <vector>

typedef long long ll;

struct Node {
  ll sum;
  Node *l, *r;
  Node() {
    sum = 0;
    l = r = nullptr;
  }
};

void update(Node *node, int tl, int tr, int p, int v) {
  if (tl == tr) {
    node -> sum = v;
  } else {
    int mid = (tl + tr) / 2;
    if (p <= mid) {
      if (node -> l == nullptr) {
        node -> l = new Node();
      }
      update(node -> l, tl, mid, p, v);
    } else if (mid < p) {
      if (node -> r == nullptr) {
        node -> r = new Node();
      }
      update(node -> r, mid + 1, tr, p, v);
    }
    node -> sum = 0;
    if (node -> l != nullptr) {
      node -> sum += node -> l -> sum;
    }
    if (node -> r != nullptr) {
      node -> sum += node -> r -> sum;
    }
  }
}

ll query(Node *node, int tl, int tr, int l, int r) {
  if (l <= tl && tr <= r) {
    return node -> sum;
  }
  int mid = (tl + tr) / 2;
  ll ret = 0;
  if (node -> l != nullptr && l <= mid) {
    ret += query(node -> l, tl, mid, l, r);
  }
  if (node -> r != nullptr && mid < r) {
    ret += query(node -> r, mid + 1, tr, l, r);
  }
  return ret;
}

int n;
Node *root;

void init(int N) {
  n = N;
  root = new Node();
}

void updateValue(int pos, int value) {
  update(root, 1, n, pos, value);
}
ll querySequence(int l, int r) {
  return query(root, 1, n, l, r);
}
```

## Avantaje si dezavantaje

Dacă intr-o problemă ai nevoie de un arbore de intervale de mărime $N$, dacă $N$ este mic ($1 \leq N \leq 2 * 10^5$) este mai bine să fie folosit unul static. Altfel trebuie folosit un arbore de intervale dinamic.

# Probleme suplimentare

* [Monkey and Apple-trees](https://oj.uz/problem/view/IZhO12_apple)
* [Happiness](https://oj.uz/problem/view/Balkan15_HAPPINESS)

## Lectură suplimentară 

* [Sparse Segment Tree - USACO Guide](https://usaco.guide/plat/sparse-segtree?lang=cpp)
* [Dynamic Segment Tree - Cp algorithms](https://cp-algorithms.com/data_structures/segment_tree.html#dynamic-segment-tree)
