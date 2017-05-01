#include "ie.h"
#include "qsettings.h"
#include "qdebug.h"
#include "qstring.h"
#include "qt_windows.h"
#include "qbitarray.h"

ie::ie()
{
    /*
     * 初始化参数
     * 调用搜索函数
     */
    this->name1="HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Internet Explorer\\TypedURLs";
    this->name2="HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Internet Explorer\\TypedURLsTime";
    this->number=0;
    this->search();
}

void ie::search()
{
    /*
     * 读取注册表保存的IE浏览记录
     */
    QStringList keys;
    QSettings reg(this->name1,QSettings::NativeFormat);
    keys = reg.allKeys();
    for (int i=0;i<keys.length();i++)
    {
        this->number++;
        this->name[number] = reg.value(keys[i]).toString();
        }

    /*
     * 读取注册表保存的IE浏览时间,Windows7不支持。
     */
    QStringList keys2;
    QSettings reg2(this->name2,QSettings::NativeFormat);
    keys2 = reg2.allKeys();
    int count = 0;
    int base;

    /*
     *读取注册表保存的16个16进制数字
     * 对每个16进制数字进行处理
     * 8个16进制数字转化成10进制数字再保存到FILETIME的高字节
     * 8个16进制数字转化成10进制数字再保存到FILETIME的低字节
     * FILETIME转换成SYSTEMTIME得到具体的时间
     */
    QString c;
    QString s;
    QString s1,s2;
    DWORD num1,num2;
    for (int i=0;i<keys2.length();i++)
    {
        count++;
        s1 = "";
        s2 = "";
        num1 = 0;
        num2 = 0;
        base = 16*16*16*16*16*16*16;
        c = reg2.value(keys2[i]).toString();
        const ushort *p=c.utf16();
        QByteArray bytes = QByteArray::fromRawData((char*)p,c.length()*2);
        s=QString::fromLocal8Bit(bytes.toHex());
        for (int j=3;j>=0;j--)
        {
            s1 = s1 + s[j*2];
            s1 = s1 + s[j*2+1];

        }
        for (int j=7;j>=4;j--)
        {
            s2 = s2 + s[j*2];
            s2 = s2 + s[j*2+1];
        }
        for (int j=0;j<=7;j++)
        {
            if (s1[j].unicode()<60)
                num1 = num1 + (s1[j].unicode()-48) * base;
            else
                num1 = num1 + (s1[j].unicode()-87) * base;
            if (s2[j].unicode()<60)
                num2 = num2 + (s2[j].unicode()-48) * base;
            else
                num2 = num2 + (s2[j].unicode()-87) * base;
            base = base /16;
        }
        FILETIME *time = new FILETIME();
        time->dwLowDateTime = num1;
        time->dwHighDateTime = num2;
        SYSTEMTIME st;
        FileTimeToSystemTime(time,&st);
        int flag=0;
        if (st.wHour>=16)
            flag=1;
        st.wHour = (st.wHour+8) % 24;
        this->time[count]+=QString::number(st.wYear)+"年";
        this->time[count]+=QString::number(st.wMonth)+"月";
        if (flag==0)
            this->time[count]+=QString::number(st.wDay)+"日 ";
        else
            this->time[count]+=QString::number(st.wDay+1)+"日 ";
        if (QString::number(st.wHour).length()==1)
            this->time[count]+="0"+QString::number(st.wHour)+":";
        else
            this->time[count]+=QString::number(st.wHour)+":";
        if (QString::number(st.wMinute).length()==1)
            this->time[count]+="0"+QString::number(st.wMinute)+":";
        else
            this->time[count]+=QString::number(st.wMinute)+":";
        if (QString::number(st.wSecond).length()==1)
            this->time[count]+="0"+QString::number(st.wSecond);
        else
            this->time[count]+=QString::number(st.wSecond);
    }
    if (count==0)
    {
        for (int j=1;j<=this->number;j++)
        {
            this->time[j]="Windows7不记录访问时间";

        }
    }
    //根据时间进行冒泡排序
    QString temp;
    for (int i=1;i<=this->number;i++)
        for (int j=1;j<=i;j++)
            if (this->time[i]>this->time[j])
            {
                temp = this->name[i];
                this->name[i] = this->name[j];
                this->name[j] = temp;

                temp = this->time[i];
                this->time[i] = this->time[j];
                this->time[j] = temp;

            }


}
ie::~ie()
{

}

