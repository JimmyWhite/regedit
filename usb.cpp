#include "usb.h"
#include "qsettings.h"
#include "qdebug.h"
#include "qstring"
#include "qt_windows.h"

usb::usb()
{
    /*
     * 初始化参数
     * 调用搜索函数
     */
    this->name="HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Enum\\USBSTOR";
    this->number=0;
    this->search();
}

void usb::search()
{
    QString childgroups1[100]={""};
    QSettings reg(this->name,QSettings::NativeFormat);
    int num=0;

    //列出连接过的USB品牌
    for (int i=0;i<reg.childGroups().length();i++)
    {
        if (reg.childGroups().at(i).mid(0,4)=="Disk")
        {
           num++;
           childgroups1[num]=reg.childGroups().at(i);
        }
    }

    //处理并保存每个USB设备的ID、名称、首次使用时间
    for (int i=1;i<=num;i++)
    {
        QSettings subreg(this->name+"\\"+childgroups1[i],QSettings::NativeFormat);
        for (int j=0;j<subreg.childGroups().length();j++)
        {
            QSettings subreg2(this->name+"\\"+childgroups1[i]+"\\"+subreg.childGroups().at(j),QSettings::NativeFormat);

            //调用windows.h中的注册表API获取首次使用时间
            HKEY key;
            QString path="SYSTEM\\CurrentControlSet\\Enum\\USBSTOR\\" + childgroups1[i]+"\\"+subreg.childGroups().at(j)+"\\Device Parameters";
            RegOpenKeyEx(HKEY_LOCAL_MACHINE,reinterpret_cast<const wchar_t *>(path.utf16()),0,KEY_ALL_ACCESS||KEY_WOW64_64KEY,&key);
            //转换时间
            FILETIME *time = new FILETIME();
            SYSTEMTIME st;
            RegQueryInfoKey(key,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,time);
            FileTimeToSystemTime(time,&st);
            int flag=0;
            if (st.wHour>=16)
                flag=1;
            st.wHour = (st.wHour+8) % 24;
            //保存ID、名称、首次使用时间到类的实例
            this->number++;
            this->u_id[this->number] =subreg.childGroups().at(j);
            this->u_name[this->number] = subreg2.value("FriendlyName").toString();
            this->u_time[this->number]+=QString::number(st.wYear)+"年";
            this->u_time[this->number]+=QString::number(st.wMonth)+"月";
            if (flag==0)
                this->u_time[this->number]+=QString::number(st.wDay)+"日 ";
            else
                this->u_time[this->number]+=QString::number(st.wDay+1)+"日 ";
            if (QString::number(st.wHour).length()==1)
                this->u_time[this->number]+="0"+QString::number(st.wHour)+":";
            else
                this->u_time[this->number]+=QString::number(st.wHour)+":";
            if (QString::number(st.wMinute).length()==1)
                this->u_time[this->number]+="0"+QString::number(st.wMinute)+":";
            else
                this->u_time[this->number]+=QString::number(st.wMinute)+":";
            if (QString::number(st.wSecond).length()==1)
                this->u_time[this->number]+="0"+QString::number(st.wSecond);
            else
                this->u_time[this->number]+=QString::number(st.wSecond);

        }
    }
}
usb::~usb()
{

}

