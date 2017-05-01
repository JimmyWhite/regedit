#include "word.h"
#include "qstring.h"
#include "qsettings.h"
#include "qdebug.h"
#include "qt_windows.h"
word::word()
{
    /*
     * 初始化参数
     * 调用搜索函数
     */
    this->name = "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Office";
    this->number = 0;
    this->search();

}

void word::search()
{
    //获取word在注册表的版本
    QSettings reg(this->name,QSettings::NativeFormat);
    QStringList version = reg.childGroups();

    /*
     * 对每个版本进行遍历，获取word文档信息
     * 读取Reading Location
     * 读取File MRU
     */
    for (int i=0; i<version.length();i++)
    {
        QSettings reg2(this->name+"\\"+version[i]+"\\"+"Word"+"\\"+"Reading Locations",QSettings::NativeFormat);
        QStringList document = reg2.childGroups();
       for (int j=0;j<document.length();j++)
        {
            QSettings reg3(this->name+"\\"+version[i]+"\\"+"Word"+"\\"+"Reading Locations"+"\\"+document[j],QSettings::NativeFormat);
            this->number ++;
            this->w_time[this->number] = reg3.value("Datetime").toString().replace(10,1," ");
            this->w_path[this->number] = reg3.value("File Path").toString();
            this->w_name[this->number] = this->w_path[this->number];

            //提取文档路径的文件名
            while (this->w_name[this->number].indexOf("\\")!=-1)
            {
                this->w_name[this->number] = this->w_name[this->number].mid(this->w_name[this->number].indexOf("\\")+1);
            }

        }
       QSettings reg4(this->name+"\\"+version[i]+"\\"+"Word"+"\\"+"File MRU",QSettings::NativeFormat);
       QStringList item = reg4.allKeys();
       for (int k=0;k<item.length();k++)
       {
           this->number++;
           QString s = reg4.value(item[k]).toString();
           this->w_path[this->number] = s.mid(s.indexOf("*")+1);
           this->w_name[this->number] = this->w_path[this->number];
           while (this->w_name[this->number].indexOf("\\")!=-1)
           {
               this->w_name[this->number] = this->w_name[this->number].mid(this->w_name[this->number].indexOf("\\")+1);
           }
           QString ss =s.mid(s.indexOf("T")+1,16);
           QString s1,s2;
           DWORD num1,num2;
           int base;
           {
               s1 = "";
               s2 = "";
               num1 = 0;
               num2 = 0;
               base = 16*16*16*16*16*16*16;
               const ushort *p=ss.utf16();
               QByteArray bytes = QByteArray::fromRawData((char*)p,ss.length()*2);
               s=QString::fromLocal8Bit(bytes.toHex());
               s2 = ss.mid(0,8);
               s1 = ss.mid(8,8);
               for (int j=0;j<=7;j++)
               {
                   if (s1[j].unicode()<60)
                       num1 = num1 + (s1[j].unicode()-48) * base;
                   else
                       num1 = num1 + (s1[j].unicode()-55) * base;
                   if (s2[j].unicode()<60)
                       num2 = num2 + (s2[j].unicode()-48) * base;
                   else
                       num2 = num2 + (s2[j].unicode()-55) * base;
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
               if (flag==1)
                   st.wDay =st.wDay +1;
               this->w_time[this->number]+=QString::number(st.wYear)+"-";
               if (QString::number(st.wMonth).length()==2)
                   this->w_time[this->number]+=QString::number(st.wMonth)+"-";
               else
                   this->w_time[this->number]+="0"+QString::number(st.wMonth)+"-";
               if (QString::number(st.wDay).length()==2)
                    this->w_time[this->number]+=QString::number(st.wDay)+" ";
               else
                   this->w_time[this->number]+="0"+QString::number(st.wDay)+" ";
               if (QString::number(st.wHour).length()==1)
                   this->w_time[this->number]+="0"+QString::number(st.wHour)+":";
               else
                   this->w_time[this->number]+=QString::number(st.wHour)+":";
               if (QString::number(st.wMinute).length()==1)
                   this->w_time[this->number]+="0"+QString::number(st.wMinute);
               else
                   this->w_time[this->number]+=QString::number(st.wMinute);
       }
    }
}

    //以时间进行冒泡排序
    QString temp;
    for (int i=1;i<=this->number;i++)
        for (int j=1;j<=i;j++)
            if (this->w_time[i]>this->w_time[j])
            {
                temp = this->w_time[i];
                this->w_time[i] = this->w_time[j];
                this->w_time[j] = temp;

                temp = this->w_name[i];
                this->w_name[i] = this->w_name[j];
                this->w_name[j] = temp;

                temp = this->w_path[i];
                this->w_path[i] = this->w_path[j];
                this->w_path[j] = temp;
            }

}
word::~word()
{

}

