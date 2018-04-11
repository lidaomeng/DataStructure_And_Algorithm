#include "BTree.h"
#include <iostream>
#include <set>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
using namespace std;


int main() {
    CBinaryTree bt;

    bt.AddNode(5);
    bt.AddNode(3);
    bt.AddNode(7);
    bt.AddNode(2);
    bt.AddNode(4);
    bt.AddNode(6);
    bt.AddNode(8);
    //bt.AddNode(9);
    //bt.AddNode(10);

    bt.InorderTraverse(bt.GetRootNode());
    cout << endl;

    bt.HierarchiTraverse(bt.GetRootNode());
    cout << endl;

    unsigned k = 3;
    bt.GetKthNode(bt.GetRootNode(), k);

    unsigned depth = bt.GetBTDepth(bt.GetRootNode());
    cout << depth << endl;


    return 0;
}
