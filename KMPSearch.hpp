//
// Created by LiDaoMeng on 2018/4/21.
// KMP算法 即字符串查找算法
// 描述：有一个文本串S和一个模式串P，要查找P在S中的位置该怎么做？

#include <iostream>
#include <set>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
using namespace std;

class CKmpSearch {
public:
    CKmpSearch();
    ~CKmpSearch();

public:
    // KMP算法
    // @在字符串中查找关键词，比如Jordan，并在关键词前后插入特殊字符，例如*Jordan*
    char* KmpSearchAndInsert(const char* S, const char* P, char ch);

    // 蛮力算法
    // @返回匹配下标
    int ViolentMatch(char* S, char* P);

private:
    // 计算next数组
    void GetNext(const char* P, int next[]);
private:
    int* m_nNext;
};

CKmpSearch::CKmpSearch() :m_nNext(nullptr){}
CKmpSearch::~CKmpSearch() {
    if(m_nNext){
        delete [] m_nNext;
        m_nNext = nullptr;
    }
}

void CKmpSearch::GetNext(const char *P, int *next) {
    if(P == nullptr || next == nullptr)
        return;

    int pLen = strlen(P);
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < pLen - 1) { // Note
        if(k == -1 || P[j] == P[k]){
            ++k;
            ++j;
            //next[j] = k;
            if( P[j] != P[k]){
                next[j] = k;
            }else {
                next[j] = next[k];
            }
        }else{
            k = next[k];
        }
    }
}

// 查找关键字，并在关键字前后插入特殊字符
char* CKmpSearch::KmpSearchAndInsert(const char* S, const char* P, char ch) {
    if(S == nullptr || P == nullptr)
        return nullptr;

    int i = 0;
    int j = 0;
    int sLen = strlen(S);
    int pLen = strlen(P);
    int beg = i;

    // 初始化next数组
    m_nNext = new int[pLen];
    GetNext(P, m_nNext);

    // 目标字符串
    char* pDest = new  char[sLen*3 + 1];
    memset(pDest, 0, sLen*3 + 1);
    char* pRet = pDest;

    while(i < sLen){
        j = 0;
        //beg = i;
        while(i < sLen && j < pLen) {
            if(j == -1 || S[i] == P[j]){
                ++i;
                ++j;
            }else {
                j = m_nNext[j];
            }
        }

        // 123abc456
        if(j == pLen) {
            //插入123
            while(beg < i-j)
                *pDest++ = S[beg++];

            // 插入*
            *pDest++ = ch;

            // 插入abc
            while(beg < i)
                *pDest++ = S[beg++];

            // 插入*
            *pDest++ = ch;
        } else {
            while(beg < i)
                *pDest++ = S[beg++];
        }
    }

    return pRet;
}

int CKmpSearch::ViolentMatch(char *S, char *P) {
    if(S == nullptr || P == nullptr)
        return -1;

    int sLen = strlen(S);
    int pLen = strlen(P);

    int i = 0;
    int j = 0;
    while( i < sLen && j < pLen){
        if(S[i] == P[j]){
            ++i;
            ++j;
        }else{
            i = i - j  + 1;
            j = 0;
        }
    }

    if(j == pLen)
        return i - j;
    else
        return -1;
}


// 单元测试
int main() {
    CKmpSearch kmp;

    const char* pS = "123abc456";
    //pS = "abcabcabc";
    const char* pP = "abc";
    char* pObj = kmp.KmpSearchAndInsert(pS, pP, '*');

    cout << pObj << endl;

    if(pObj)
        delete pObj;


    return 0;
}
