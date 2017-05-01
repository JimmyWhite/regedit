#ifndef WORD_H
#define WORD_H
#include "qstring.h"

class word
{
public:
    QString name; //word文档打开记录在注册表中的位置
    int number;  //打开的文档数量
    QString w_name[10000];//打开的文档名称
    QString w_time[10000];//打开时间
    QString w_path[10000];//打开路径

    void search(); //搜索word打开文档记录
    word();
    ~word();
};

#endif // WORD_H
