#include "autorun.h"
#include "qsettings.h"
#include "qdebug.h"
#include "qstring.h"
#include "qt_windows.h"

autorun::autorun()
{
    /*
     * 初始化参数
     * 调用搜索函数
     */
    this->name1="HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    this->name2="HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    this->number=0;
    this->search();
    this->search2();
    this->search3();
}

void autorun::search()
{
    /*
     * 调用windows.h中的注册表API获取HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run保存的开机启动项
     * 利用KEY_WOW64_64KEY禁止32位程序自动跳转
     */
    HKEY key;
    QString path="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    RegOpenKeyEx(HKEY_LOCAL_MACHINE,reinterpret_cast<const wchar_t *>(path.utf16()),0,KEY_ALL_ACCESS|KEY_WOW64_64KEY,&key);
    DWORD KeyCnt=0;
    RegQueryInfoKey(key, NULL, NULL, NULL, NULL, NULL, NULL, &KeyCnt, NULL, NULL, NULL, NULL);

    /*
     * 遍历键值
     * 得到的数据进行类型转换保存到类的实例
     */
    for (unsigned int i=0;i<KeyCnt;i++)
    {
        wchar_t *s1 = new wchar_t[1000];
        DWORD size=1000;
        DWORD size2=1000;
         char *s2 = new  char[1000];
        RegEnumValue(key,i,s1,&size,NULL,NULL,LPBYTE(s2),&size2);
        int temp=0;
        QString ss="";
        while (s2[temp]!=0)
        {
            ss+=s2[temp];
            temp+=2;
        }
        this->number +=1;
        this->name[number] = QString::fromWCharArray(s1);
        this->path[number] = ss;
        delete []s1;
        delete []s2;
    }
}

void autorun::search2()
{
    /*
     * 调用windows.h中的注册表API获取HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run保存的开机启动项
     * 自动跳转到WOW6432目录
     */
    HKEY key;
    QString path="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    RegOpenKeyEx(HKEY_LOCAL_MACHINE,reinterpret_cast<const wchar_t *>(path.utf16()),0,KEY_ALL_ACCESS,&key);
    DWORD KeyCnt=0;
    RegQueryInfoKey(key, NULL, NULL, NULL, NULL, NULL, NULL, &KeyCnt, NULL, NULL, NULL, NULL);

    /*
     * 遍历键值
     * 得到的数据进行类型转换保存到类的实例
     */
    for (unsigned int i=0;i<KeyCnt;i++)
    {
        wchar_t *s1 = new wchar_t[1000];
        DWORD size=1000;
        DWORD size2=1000;
         char *s2 = new  char[1000];
        RegEnumValue(key,i,s1,&size,NULL,NULL,LPBYTE(s2),&size2);
        int temp=0;
        QString ss="";
        while (s2[temp]!=0)
        {
            ss+=s2[temp];
            temp+=2;
        }
        this->number +=1;
        this->name[number] = QString::fromWCharArray(s1);
        this->path[number] = ss;
        delete []s1;
        delete []s2;
    }

}

void autorun::search3()
{
    /*
     * 调用windows.h中的注册表API获取HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run保存的开机启动项
     * 利用KEY_WOW64_64KEY禁止32位程序自动跳转
     */
    HKEY key;
    QString path="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    RegOpenKeyEx(HKEY_CURRENT_USER,reinterpret_cast<const wchar_t *>(path.utf16()),0,KEY_ALL_ACCESS,&key);
    DWORD KeyCnt=0;
    RegQueryInfoKey(key, NULL, NULL, NULL, NULL, NULL, NULL, &KeyCnt, NULL, NULL, NULL, NULL);

    /*
     * 遍历键值
     * 得到的数据进行类型转换保存到类的实例
     */
    for (unsigned int i=0;i<KeyCnt;i++)
    {
        wchar_t *s1 = new wchar_t[1000];
        DWORD size=1000;
        DWORD size2=1000;
         char *s2 = new  char[1000];
        RegEnumValue(key,i,s1,&size,NULL,NULL,LPBYTE(s2),&size2);
        int temp=0;
        QString ss="";
        while (s2[temp]!=0)
        {
            ss+=s2[temp];
            temp+=2;
        }
        this->number +=1;
        this->name[number] = QString::fromWCharArray(s1);
        this->path[number] = ss;
        delete []s1;
        delete []s2;
    }


}
autorun::~autorun()
{


}

