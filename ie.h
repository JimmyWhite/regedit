#ifndef IE_H
#define IE_H
#include "qstring.h"

class ie
{
public:

    QString name1;  //IE浏览记录在注册表的位置
    QString name2;  // IE浏览时间在注册表的位置
    int number;     //IE浏览记录的数量
    QString name[10000];  //IE浏览记录的网址
    QString time[10000];   //IE浏览记录的时间

    void search();  //搜索注册表存储的IE浏览记录信息
    ie();
    ~ie();
};

#endif // IE_H
