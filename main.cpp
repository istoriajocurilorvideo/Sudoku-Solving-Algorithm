#include <iostream>
#include <fstream>

using namespace std;

int mat[10][10], comp[10][10];
ifstream in("grid.file");
bool exFull = false;

void show() {
    int i, j;
    for(i=1; i<=9; i++) {
        for(j=1; j<=9; j++)
           cout<<mat[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

bool full() {
    int i, j;
    for(i=1; i<=9; i++)
        for(j=1; j<=9; j++)
            if(mat[i][j] == 0)
                return false;
    return true;
}

bool isModif(int x, int y) {
    if(comp[x][y] != 0)
        return false;
    return true;
}

bool isHorizAndVert(int val, int x, int y) {
    int i;
    for(i=1; i<=9; i++)
        if(i != x || i != y) {
            if(mat[i][y] == val) return false;
            if(mat[x][i] == val) return false;
        }
    return true;
}

bool isBlock(int val, int x, int y){
    int i, j, r1, r2;
    r1 = ((x-1) - (x-1)%3)+1;
    r2 = ((y-1) - (y-1)%3)+1;
    for(i=r1; i<=r1+2; i++)
        for(j=r2; j<=r2+2; j++)
            if(i != x && j != y)
                if(mat[i][j] == val) return false;
    return true;
}

void solver(int x, int y) {
    if(!exFull) {
        if(!isModif(x, y)) {
            if(y==9) solver(x+1, 1);
            else solver(x, y+1);
        } else {
            int i;
            for(i=1; i<=9 && !exFull; i++) {
                if(isHorizAndVert(i, x, y) && isBlock(i, x, y)) {
                    mat[x][y] = i;
                    if(full()) {
                            exFull = true;
                        } else {
                            if(y==9) solver(x+1, 1);
                            else solver(x, y+1);
                        }
                } else
                    mat[x][y] = 0;
            }
        }
    }
}

int main() {
    int i, j;
    for(i=1; i<=9; i++)
        for(j=1; j<=9; j++) {
            in>>mat[i][j];
            comp[i][j] = mat[i][j];
        }
    solver(1, 1);
    show();
    return 0;
}
