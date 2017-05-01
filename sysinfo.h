#ifndef SYSINFO_H
#define SYSINFO_H
#include "qstring.h"

class sysinfo
{
public:
    QString name1;   //计算机名所在注册表位置
    QString name2;   //BIOS信息所在注册表位置
    QString name3;   //处理器信息所在注册表位置
    QString name4;   //最后关机时间所在注册表位置
    QString name5;   //远程桌面连接端口所在注册表的位置
    QString name6;   //操作系统版本所在注册表的位置

    QString computername; //计算机名
    QString bios[3];      //BIOS信息、包括发布时间、厂商、型号
    QString cpu;          //处理器信息
    QString shutdowntime; //最后关机时间
    QString port;         //远程桌面连接端口
    QString os;           //操作系统版本
    QString renew;        //更新版本号

    void search();   //获取主机相关信息
    sysinfo();
    ~sysinfo();
};

#endif // SYSINFO_H
