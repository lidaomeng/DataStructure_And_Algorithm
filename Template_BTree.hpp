//
// Created by LiDaoMeng on 2018/3/31.
//

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>


using namespace std;

template <class T = int>
struct BinaryTreeNode {
    BinaryTreeNode():m_pLeft(nullptr),m_pRight(nullptr){}
    BinaryTreeNode(const T& aoValue):m_nValue(aoValue),m_pLeft(nullptr),m_pRight(nullptr){}

    T m_nValue;
    struct BinaryTreeNode<T>* m_pLeft;
    struct BinaryTreeNode<T>* m_pRight;
};

template <class T = int>
class CBTree {
public:
    CBTree():m_pRoot(nullptr){}
    ~CBTree(){
        _DeleteNodeRecursive(m_pRoot);
    }

    void AddNode(const T& aoValue) {
        BinaryTreeNode<T>* pNode = new BinaryTreeNode<T>(aoValue);

        if(m_pRoot == nullptr) {
            m_pRoot = pNode;
        } else{
            _AddNode(m_pRoot, pNode);
        }
    }

    BinaryTreeNode<T>* GetBTRootNode() {
        return m_pRoot;
    }

    void PrintBTreeRecursively() {
        std::queue<BinaryTreeNode<T>*> loQueue;

        if(m_pRoot == nullptr)
            return;
        loQueue.push(m_pRoot);

        while( !loQueue.empty() ) {
            BinaryTreeNode<T>* pNode = loQueue.front();
            loQueue.pop();
            cout << pNode->m_nValue << " ";

            if(pNode->m_pLeft != nullptr) {
                loQueue.push(pNode->m_pLeft);
            }
            if(pNode->m_pRight != nullptr) {
                loQueue.push(pNode->m_pRight);
            }
        }

        cout << endl;
    }

private:
    void _AddNode(BinaryTreeNode<T>* apRoot, BinaryTreeNode<T>* apNode) {
         if(apNode->m_nValue >= apRoot->m_nValue) {
             if(apRoot->m_pRight == nullptr){
                 apRoot->m_pRight = apNode;
             } else {
                 _AddNode(apRoot->m_pRight, apNode);
             }
         } else{
             if(apRoot->m_pLeft == nullptr){
                 apRoot->m_pLeft = apNode;
             } else {
                 _AddNode(apRoot->m_pLeft, apNode);
             }
         }
    }

    void _DeleteNodeRecursive(BinaryTreeNode<T>* apRoot) {
        if(apRoot != nullptr) {
            _DeleteNodeRecursive(apRoot->m_pLeft);
            _DeleteNodeRecursive(apRoot->m_pRight);
            delete apRoot;
            apRoot = nullptr;
        }
    }

private:
    BinaryTreeNode<T>* m_pRoot;
};

// 全局函数
template <class T = int>
void PrintVector(const vector<T>& aoVec) {
    auto itr = aoVec.begin();
    for(; itr != aoVec.end(); ++itr) {
        cout << *itr << " ";
    }
    cout << endl;
}

template <class T = int>
int SumVector(const vector<T>& aoVec) {
    T lnSum = 0;
    auto itr = aoVec.begin();
    for(; itr != aoVec.end(); ++itr) {
        lnSum += *itr;
    }

    return lnSum;
}

// 递归打印
template <class T>
void PrintBTreePathCore(BinaryTreeNode<T>* pRoot, int value, std::vector<int>& aoVec) {
    aoVec.push_back( pRoot->m_nValue );
    if(pRoot->m_pLeft == nullptr && pRoot->m_pRight == nullptr) {
        //aoVec.push_back( pRoot->m_nValue );
        if(value == SumVector(aoVec)) {
            PrintVector(aoVec);
        }
        //aoVec.pop_back();
    } else {
        if(pRoot->m_pLeft != nullptr) {
            PrintBTreePathCore(pRoot->m_pLeft, value, aoVec);
        }
        if(pRoot->m_pRight != nullptr) {
            PrintBTreePathCore(pRoot->m_pRight, value, aoVec);
        }
    }
    aoVec.pop_back();
}

// 打印二叉树中节点之和为特定值的路径
template <class T>
void PrintBTreePath(BinaryTreeNode<T>* pRoot, T value){
    if(pRoot == nullptr)
        return ;

    std::vector<T> loVec;

    PrintBTreePathCore(pRoot, value, loVec);
}



int main() {
    CBTree<int> moBtree;

    moBtree.AddNode(10);
    moBtree.AddNode(5);
    moBtree.AddNode(12);
    moBtree.AddNode(4);
    moBtree.AddNode(7);
    moBtree.AddNode(3);

    moBtree.PrintBTreeRecursively();
    PrintBTreePath(moBtree.GetBTRootNode(), 22);
    return 0;
}
