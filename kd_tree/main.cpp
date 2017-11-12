//
//  main.cpp
//  kd_tree
//
//  Created by 村上候助 on 2017/11/12.
//  Copyright © 2017 村上候助. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define MAX 1000000
#define NIL -1

using namespace std;

class Point {
public:
    int x, y;
};

class Node{
public:
    int location, l, r;
};

bool lessX(Point one, Point two){
    return (one.x < two.x);
}

bool lessY(Point one, Point two){
    return (one.y < two.y);
}

//int input_num = 0;
int node_id = 0;
//int depth = 0;
Point points[MAX];
Node T[MAX];

int make2DTree(int l, int r, int depth){
    if(!(l < r)) return NIL;

    int mid, t;
    mid = (l + r)/2;
    t = node_id++;

    if (depth % 2 == 0){
        sort(points+l, points+r, lessX);
    }
    else {
        sort(points+l, points+r, lessY);
    }
    
    T[t].location = mid;
    T[t].l = make2DTree(l, mid, depth++);
    T[t].r = make2DTree(mid+1, r, depth++);
    
    return t;
}

void find(int v, int sx, int tx, int sy, int ty, int depth){
    int x = points[T[v].location].x;
    int y = points[T[v].location].y;
    
    if(sx <= x && x <= tx && sy <= y && y <= ty){
        cout << points[T[v].location].x << " "<< points[T[v].location].y<< endl;
    }
    
    if (depth % 2 == 0) {
        if (T[v].l != NIL && sx <= x){
            find(T[v].l, sx, tx, sy, ty, depth++);
        }
        if(T[v].r != NIL && x <= tx){
            find(T[v].r, sx, tx, sy, ty, depth++);
        }
    }
    else{
        if(T[v].l != NIL && sy <= y){
            find(T[v].l, sx, tx, sy, ty, depth++);
        }
        if(T[v].r != NIL && y <= tx){
            find(T[v].r, sx, tx, sy, ty, depth++);
        }
    }
}


int main(int argc, const char * argv[]) {
    int input_num;
    scanf("%d", &input_num);
//    Point points[input_num];
    
    for(int i = 0; i < input_num; i ++){
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    
//    for(int i = 0; i < input_num; i ++){
//        cout<<points[i].x<<" "<< points[i].y << endl;
//    }
    
    int root = make2DTree(0, input_num, 0);
    
    int q;
    scanf("%d", &q);
    int sx, tx, sy, ty;
    for (int i = 0; i < q ; i ++){
        scanf("%d %d %d %d",  &sx, &tx, &sy, &ty);
        find(root, sx, tx, sy, ty, 0);
    }
    
    std::cout << "Hello, World!\n";
    return 0;
}
