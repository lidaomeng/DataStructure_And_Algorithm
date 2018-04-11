//
// Created by LiDaoMeng on 2018/3/31.
//

#ifndef TEST1_BTREE_H
#define TEST1_BTREE_H

struct BinaryTreeNode {
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;

    // 无参构造函数
    BinaryTreeNode():m_nValue(0), m_pLeft(nullptr), m_pRight(nullptr) {}

    // 带参构造函数
    BinaryTreeNode(int anValue):m_nValue(anValue), m_pLeft(nullptr), m_pRight(nullptr) {}
};

// 二叉搜索树
class CBinaryTree {
public:
    CBinaryTree();
    ~CBinaryTree();

    // 增加节点
    void AddNode(int anValue);

    // 获取根节点
    BinaryTreeNode* GetRootNode();

    // 中序遍历
    void InorderTraverse(BinaryTreeNode* apRoot);

    // 层次遍历
    void HierarchiTraverse(BinaryTreeNode* apRoot);

public:
    // 打印第k大节点
    void GetKthNode(BinaryTreeNode* apRoot, unsigned& k);

    // 获取二叉树深度
    unsigned GetBTDepth(BinaryTreeNode* apRoot);

    // 是否平衡二叉树
    bool IsBalancedBTree(BinaryTreeNode* apRoot);
private:
    // 递归删除树节点
    void DeleteNodeCursively_(BinaryTreeNode* apRoot);

    // 递归增加树节点
    void AddNodeCursively_(BinaryTreeNode* apNode, BinaryTreeNode *apRoot);

    // 层次遍历
    void HierarchiTraverseCore_(BinaryTreeNode* apRoot);

    bool IsBalancedBTreeCore_(BinaryTreeNode* apRoot, int& depth);

private:
    BinaryTreeNode* m_pRoot;
};

#endif //TEST1_BTREE_H
