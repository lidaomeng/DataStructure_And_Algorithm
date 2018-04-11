//
// Created by LiDaoMeng on 2018/3/31.
//

#include "BTree.h"
#include <iostream>

CBinaryTree::CBinaryTree() : m_pRoot(nullptr){}

CBinaryTree::~CBinaryTree() {
    if(m_pRoot != nullptr) {
        DeleteNodeCursively_(m_pRoot);
        delete m_pRoot;
        m_pRoot = nullptr;
    }
}

void CBinaryTree::DeleteNodeCursively_(BinaryTreeNode *apRoot) {
    if(apRoot == nullptr) {
        return;
    }

    DeleteNodeCursively_(apRoot->m_pLeft);
    DeleteNodeCursively_(apRoot->m_pRight);

    if(apRoot->m_pLeft != nullptr) {
        delete apRoot->m_pLeft;
        apRoot->m_pLeft = nullptr;
    }
    if(apRoot->m_pRight != nullptr) {
        delete apRoot->m_pRight;
        apRoot->m_pRight = nullptr;
    }
}

void CBinaryTree::AddNodeCursively_(BinaryTreeNode *apNode, BinaryTreeNode *apRoot) {
    if(apNode == nullptr || apRoot == nullptr)
        return;

    if(apNode->m_nValue < apRoot->m_nValue) {
        if(apRoot->m_pLeft == nullptr) {
            apRoot->m_pLeft = apNode;
        } else {
            AddNodeCursively_(apNode, apRoot->m_pLeft);
        }
    } else {
        if(apRoot->m_pRight == nullptr) {
            apRoot->m_pRight = apNode;
        } else {
            AddNodeCursively_(apNode, apRoot->m_pRight);
        }
    }
}

void CBinaryTree::AddNode(int anValue) {
    if(m_pRoot == nullptr) {
        m_pRoot = new BinaryTreeNode(anValue);
    } else {
        BinaryTreeNode* pTemp = new BinaryTreeNode(anValue);
        AddNodeCursively_(pTemp, m_pRoot);
    }
}

// 中序遍历
void CBinaryTree::InorderTraverse(BinaryTreeNode *apRoot) {
    if(apRoot != nullptr) {
        if(apRoot->m_pLeft != nullptr) {
            InorderTraverse(apRoot->m_pLeft);
        }

        std::cout << apRoot->m_nValue << ",";

        if(apRoot->m_pRight != nullptr) {
            InorderTraverse(apRoot->m_pRight);
        }
    }
}

BinaryTreeNode* CBinaryTree::GetRootNode() {
    return m_pRoot;
}

void CBinaryTree::HierarchiTraverseCore_(BinaryTreeNode *apRoot) {
    if(apRoot != nullptr) {
        // 先输出左右子树，再遍历
        if(apRoot->m_pLeft != nullptr)
            std::cout << apRoot->m_pLeft->m_nValue << ",";
        if(apRoot->m_pRight != nullptr)
            std::cout << apRoot->m_pRight->m_nValue << ",";

        HierarchiTraverseCore_(apRoot->m_pLeft);
        HierarchiTraverseCore_(apRoot->m_pRight);
    }
}

void CBinaryTree::HierarchiTraverse(BinaryTreeNode *apRoot) {
    if(apRoot != nullptr) {
        std::cout << apRoot->m_nValue << ",";
        HierarchiTraverseCore_(apRoot);
    }
}

void CBinaryTree::GetKthNode(BinaryTreeNode *apRoot, unsigned &k) {
    if(apRoot == nullptr || k == 0)
        return;

    if(apRoot->m_pLeft)
        GetKthNode(apRoot->m_pLeft, k);

    if(k == 1) {
        std::cout << apRoot->m_nValue << std::endl;
        //return;
    }
    k--;

    if(apRoot->m_pRight != nullptr) {
        GetKthNode(apRoot->m_pRight, k);
    }
}


unsigned CBinaryTree::GetBTDepth(BinaryTreeNode *apRoot) {
    if(apRoot == nullptr)
        return 0;

    int nLeft = GetBTDepth(apRoot->m_pLeft);
    int nRight = GetBTDepth(apRoot->m_pRight);

    return nLeft > nRight ? (nLeft+1) : (nRight+1);
}

bool CBinaryTree::IsBalancedBTree(BinaryTreeNode *apRoot) {
    int depth = 0;
    return IsBalancedBTreeCore_(apRoot, depth);
}

bool CBinaryTree::IsBalancedBTreeCore_(BinaryTreeNode *apRoot, int &depth) {
    return true;
}


