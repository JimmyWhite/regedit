#ifndef AUTORUN_H
#define AUTORUN_H
#include <qstring.h>

class autorun
{
public:

    QString name1;  //开机启动项目在注册表中的项路径
    QString name2;  //开机启动项目在注册表中的项路径
    int number;  //注册表中开机启动项目个数
    QString name[100]; //开机启动项目名称
    QString path[100];  //开机启动项目位置

    void search(); //搜索注册表存储的开机启动项目信息
    void search2(); //搜索注册表存储的开机启动项目信息
    void search3(); //搜索注册表存储的开机启动项目信息
    autorun();
    ~autorun();
};

#endif // AUTORUN_H
