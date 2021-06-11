#ifndef SEARCH_H
#define SEARCH_H
#include <iostream>
using namespace std;
#include "data_structs.h"
#include "database_interaction/database_interaction.h"
#include <list>
#include <QDebug>
#include "Jieba.hpp"
using namespace cppjieba;
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

class Search{
public:
    Search(database_interaction *d){
        db = d;
    }
    inline void search(QString str1, list<article_post*>&result){
        l.clear();
        db->getPostInfo(l,-1,"202200000000","000000000000",-1);
        Tit.clear();
        result.clear();
        string str;
        str = str1.toStdString();
        vector<string>res;
        q->Cut(str, res);
        int x = res.size();
        for (int i = 0; i < x; i++){
            QString str2 = QString::fromStdString(res[i]);
            Tit.push_back(str2);
        }
        int n = 0;
        string st;
        vector<string>res2;
        for(auto it=l.begin();it!=l.end();it++){
            res2.clear();
            st = (*it)->title.toStdString();
            q->Cut(st, res2);
            int x = res2.size();
            for (int i = 0; i < x; i++){
                n = 0;
                QString st1 = QString::fromStdString(res2[i]);
                for (int j = 0;j < Tit.size();j++){
                    if ((st1 == Tit[j]) && st1.size() > 1)
                        n++;
                }
                if (n!=0){
                    result.insert(result.end(),*it);
                    break;
                }
            }
        }
    }
    inline void search2(list<article_post*>&result, QString _account){
        l.clear();
        result.clear();
        db->getCollectedPost(l, _account);
        for(auto it=l.begin();it!=l.end();it++){
            result.push_back(*it);
        }
    }
private:
    const char* const DICT_PATH = "./dict/jieba.dict.utf8";
    const char* const HMM_PATH = "./dict/hmm_model.utf8";
    const char* const USER_DICT_PATH = "./dict/user.dict.utf8";
    const char* const IDF_PATH = "./dict/idf.utf8";
    const char* const STOP_WORD_PATH = "./dict/stop_words.utf8";
    Jieba *q = new Jieba(DICT_PATH,
            HMM_PATH,
            USER_DICT_PATH,
            IDF_PATH,
            STOP_WORD_PATH);

    list<article_post*>l;
    QVector<QString>Tit;
    database_interaction *db;
};

#endif
