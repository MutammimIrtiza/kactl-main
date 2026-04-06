/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: ...
 * Time: log square n
 * Usage: one based grid, and all inclusive
 * Status: ...
 */

const int TREE_SIZE = 1 << 10;
int trees[TREE_SIZE * 2][TREE_SIZE * 2];
// Adds d to the position x in the segment tree `tree`.
void add(int *tree, int x, int d) {
    x += TREE_SIZE;
    while (x > 0) {  tree[x] += d;   x /= 2;  }
}
// Adds d to the position (i, j).
void add(int y, int x, int d) {
    y += TREE_SIZE;
    while (y > 0) {   add(trees[y], x, d);   y /= 2;   }
}
// Returns the sum of value in range [x1, x2] in `tree`.
int query(int *tree, int x1, int x2) {
    x1 += TREE_SIZE;   x2 += TREE_SIZE;   int sum = 0;
    while (x1 <= x2) {
        if (x1 % 2 == 1) sum += tree[x1++];
        if (x2 % 2 == 0) sum += tree[x2--];
        x1 /= 2;   x2 /= 2;
    } return sum;
}
// Returns the sum of value in the rectangle [y1, y2]x[x1, x2]
int query(int y1, int y2, int x1, int x2) {
    y1 += TREE_SIZE;   y2 += TREE_SIZE;   int sum = 0;
    while (y1 <= y2) {
        if (y1 % 2 == 1) sum += query(trees[y1++], x1, x2);
        if (y2 % 2 == 0) sum += query(trees[y2--], x1, x2);
        y1 /= 2;   y2 /= 2;
    } return sum;
}