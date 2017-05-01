#include "sysinfo.h"
#include "qsettings.h"
#include "qdebug.h"
#include "qt_windows.h"

sysinfo::sysinfo()
{
    /*
     * 初始化参数
     * 调用搜索函数
     */
   this->name1="HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName";
   this->name2="HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\BIOS";
   this->name3="HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";
   this->name4="HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Windows";
   this->name5="HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\Wds\\rdpwd\\Tds\\tcp";
   this->name6="HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
   this->search();
}

void sysinfo::search()
{
    //获取计算机名称
    QSettings reg(this->name1,QSettings::NativeFormat);
    this->computername = reg.value("ComputerName").toString();

    //获取BIOS信息
    QSettings reg2(this->name2,QSettings::NativeFormat);
    this->bios[0] = reg2.value("BIOSVendor").toString();
    this->bios[1] = reg2.value("BIOSVersion").toString();
    this->bios[2] = reg2.value("BIOSReleaseDate").toString();

    //获取CPU信息
    QSettings reg3(this->name3,QSettings::NativeFormat);
    this->cpu = reg3.value("ProcessorNameString").toString();

    /*
     * 获取最后关机时间
     *读取注册表保存的16个16进制数字
     * 对每个16进制数字进行处理
     * 8个16进制数字转化成10进制数字再保存到FILETIME的高字节
     * 8个16进制数字转化成10进制数字再保存到FILETIME的低字节
     * FILETIME转换成SYSTEMTIME得到具体的时间
     */
    QSettings reg4(this->name4,QSettings::NativeFormat);
    QString c;
    QString s;
    QString s1="",s2="";
    DWORD num1=0,num2=0;
    int base = 16*16*16*16*16*16*16;
    c = reg4.value("ShutdownTime").toString();
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
    this->shutdowntime+=QString::number(st.wYear)+"年";
    this->shutdowntime+=QString::number(st.wMonth)+"月";
    if(flag==0)
        this->shutdowntime+=QString::number(st.wDay)+"日 ";
    else
        this->shutdowntime+=QString::number(st.wDay+1)+"日 ";
    if (QString::number(st.wHour).length()==1)
        this->shutdowntime+="0"+QString::number(st.wHour)+":";
    else
        this->shutdowntime+=QString::number(st.wHour)+":";
    if (QString::number(st.wMinute).length()==1)
        this->shutdowntime+="0"+QString::number(st.wMinute)+":";
    else
        this->shutdowntime+=QString::number(st.wMinute)+":";
    if (QString::number(st.wSecond).length()==1)
        this->shutdowntime+="0"+QString::number(st.wSecond);
    else
        this->shutdowntime+=QString::number(st.wSecond);

    //获取远程桌面连接的端口

    QSettings reg5(this->name5,QSettings::NativeFormat);
    this->port = QString::number(reg5.value("PortNumber").toInt());

    //获取操作系统版本
    QSettings reg6(this->name6,QSettings::NativeFormat);
    this->os = reg6.value("ProductName").toString();
    this->renew = reg6.value("ReleaseId").toString();
}

sysinfo::~sysinfo()
{

}

