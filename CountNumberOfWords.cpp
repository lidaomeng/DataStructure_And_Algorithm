//
// Created by LiDaoMeng on 2018/4/23.
//
#include <pthread.h>
#include <stdio.h>
int g_WordsNum = 0;
pthread_mutex_t g_Mutex; //互斥锁

typedef struct TextInfo{
    char* mpText;
    int miBegin_offset;
    int miEnd_offset;

    TextInfo():mpText(nullptr), miBegin_offset(0), miEnd_offset(0){}
}TextInfo;

int worker(char* text, int begin_offset, int end_offset) {
    if(text == nullptr || end_offset >= begin_offset)
        return 0;
    int liNum_Word = 0;

    //若最后出现字母，则回跳，避免计算成两个单词
    while( (begin_offset < end_offset) &&
           ((*(text + end_offset) >= 'a' && *(text + end_offset) <= 'z') ||
            (*(text + end_offset) >= 'A' && *(text + end_offset) <= 'Z')) ){
        end_offset--;
    }
    if(begin_offset >= end_offset)
        return 0;

    while(begin_offset < end_offset){
        //1.若非a-z,A-Z,则跳过
        while( (begin_offset < end_offset) && ( !(*(text+begin_offset) >= 'a' && *(text+begin_offset) <= 'z')
                                                || (*(text+begin_offset) >= 'A' && *(text+begin_offset) <= 'Z') ) ){
            begin_offset++;
        }

        if(begin_offset >= end_offset)
            break;

        while((*(text+begin_offset) >= 'a' && *(text+begin_offset) <= 'z')
              || (*(text+begin_offset) >= 'A' && *(text+begin_offset) <= 'Z')){
            begin_offset++;
        }
        liNum_Word++;
    }
}

void* thread_worker(void* arg){
    TextInfo* pTextInfo = (TextInfo*)arg;
    int sum = worker(pTextInfo->mpText, pTextInfo->miBegin_offset, pTextInfo->miEnd_offset);

    pthread_mutex_lock(&g_Mutex); //上锁
    g_WordsNum += sum;
    pthread_mutex_unlock(&g_Mutex); //解锁

    return nullptr;
}

int master(char* text, int size, int n){
    if(text == nullptr || size <= 0 || n > size)
        return 0;

    int liOffset = size / n - 1;
    int liBeg = 0;
    int liRet = 0;
    pthread_t szPThread[n];
    pthread_mutex_init(&g_Mutex, nullptr); //初始化互斥锁

    TextInfo loTextInfo;
    loTextInfo.mpText = text;
    int i = 0;
    while(liBeg < size){
        loTextInfo.miBegin_offset = liBeg;
        loTextInfo.miEnd_offset = liBeg + liOffset;
        
        liRet = pthread_create(szPThread + i, nullptr, thread_worker, (void*)&loTextInfo);
        if(liRet != 0){
            printf("pthread_create Error [%d]\n", i);
            break;
        }
        ++i;
    }

    for(int j = 0; j < n; ++j)
        pthread_join(szPThread[j], nullptr);

    pthread_mutex_destroy(&g_Mutex); //销毁互斥锁
}
