#ifndef USB_H
#define USB_H
#include <qstring.h>

class usb
{
public:

    QString name;  //USB在注册表中的项路径
    int number;   //注册表中USB记录个数
    QString u_id[100];  //USB设备的ID
    QString u_name[100];  //USB设备的品牌名称
    QString u_time[100];   //USB设备的首次使用时间

    void search();  //搜索注册表存储的USB记录
     usb();
    ~usb();
};

#endif // USB_H
