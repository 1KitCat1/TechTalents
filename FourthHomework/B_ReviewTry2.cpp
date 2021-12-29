#include <iostream>
#include <algorithm>
#include <vector>
/*Author: _KitCat_*/
/*Riabtsev Denis*/

int n, m;
int tree[2100][2100];
int a[1005][1005];
const int negativeInf = -2100000000;

void buildY(int vx, int lx, int rx, int vy, int ly, int ry) {
    if (ly == ry){
        if (lx == rx){
            tree[vx][vy] = a[lx][ly];
        } else {
            tree[vx][vy] = std::max(tree[vx*2][vy], tree[vx*2+1][vy]);
        }
    } else {
        int my = (ly + ry) / 2;
        buildY(vx, lx, rx, vy*2, ly, my);
        buildY(vx, lx, rx, vy*2+1, my+1, ry);
        tree[vx][vy] = std::max(tree[vx][vy*2], tree[vx][vy*2+1]);
    }
}

void buildX(int vertexX, int lx, int rx) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        buildX(vertexX*2, lx, mx);
        buildX(vertexX*2+1, mx+1, rx);
    }
    buildY(vertexX, lx, rx, 1, 0, m-1);
}

int maxY(int vertexX, int vy, int tly, int tRightY, int ly, int ry) {
    if (ly > ry) return negativeInf;
    if (ly == tly && tRightY == ry) return tree[vertexX][vy];

    int tmy = (tly + tRightY) / 2;
    return std::max(maxY(vertexX, vy*2, tly, tmy, ly, std::min(ry, tmy)),
         maxY(vertexX, vy*2+1, tmy+1, tRightY, std::max(ly, tmy+1), ry));
}

int maxX(int vertexX, int tlx, int trx, int lx, int rx, int ly, int ry) {
    if (lx > rx) return negativeInf;
    if (lx == tlx && trx == rx) return maxY(vertexX, 1, 0, m-1, ly, ry);

    int tmx = (tlx + trx) / 2;
    return std::max(maxX(vertexX*2, tlx, tmx, lx, std::min(rx, tmx), ly, ry),
         maxX(vertexX*2+1, tmx+1, trx, std::max(lx, tmx+1), rx, ly, ry));
}

void updateY(int vertexX, int lx, int rx, int vertexY, int ly, int ry,
 int x, int y, int value) {
    if (ly == ry) {
        if (lx == rx){
            tree[vertexX][vertexY] = value;
        } else{
            tree[vertexX][vertexY] = std::max(tree[vertexX*2][vertexY],
             tree[vertexX*2+1][vertexY]);
        }
    } else {
        int my = (ly + ry) / 2;
        if (y <= my) {
            updateY(vertexX, lx, rx, vertexY*2, ly, my, x, y, value);
        } else {
            updateY(vertexX, lx, rx, vertexY*2+1, my+1, ry, x, y, value);
        }
        tree[vertexX][vertexY] = std::max(tree[vertexX][vertexY*2],
         tree[vertexX][vertexY*2+1]);
    }
}

void updateX(int vertexX, int lx, int rx, int x, int y, int value) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        if (x <= mx) {
            updateX(vertexX*2, lx, mx, x, y, value);
        } else {
            updateX(vertexX*2+1, mx+1, rx, x, y, value);
        }
    }
    updateY(vertexX, lx, rx, 1, 0, m-1, x, y, value);
}

void solve(){
    // int n, m, q;
    int q;
    std::cin >> n >> m >> q;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            std::cin >> a[i][j];
        }
    }
    buildX(1, 0, n-1);
    for (int query = 0; query < q; query++){
        char r;
        std::cin >> r;
        if (r == '?'){
            int fromRow, toRow, fromCol, toCol;
            std::cin >> fromRow >> toRow >> fromCol >> toCol;
            fromRow--, toRow--, fromCol--, toCol--;
            cout << maxX(1, 0, n-1, fromRow, toRow, fromCol, toCol) << nl;
        } else {
            int row, col, val;
            cin >> row >> col >> val;
            row--, col--;
            updateX(1, 0, n-1, row, col, val);
        }
    }
}

signed main() {
    cin.tie(0);
    cout.tie(0);
    std::ios_base::sync_with_stdio(0);
    // iospeed;
    // TESTS
        solve();

    return 0;
}
