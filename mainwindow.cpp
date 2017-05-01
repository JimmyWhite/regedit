#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usb.h"
#include "qdebug.h"
#include "autorun.h"
#include "ie.h"
#include "sysinfo.h"
#include "word.h"
#include "qscrollbar.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("Windows注册表分析取证工具");
    setWindowIcon(QIcon(":/new/prefix1/icon.ico"));
    setFixedSize(650,500);

    /*
     * 显示主机基本信息
     * 表格设置自适应
     * 实例化sysinfo类
     * 读取注册表存储的主机基本信息
     * 格式化显示
     */
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    sysinfo SYS;

    QTableWidgetItem  *pos1 = new QTableWidgetItem(SYS.computername);
    QTableWidgetItem  *pos2 = new QTableWidgetItem(SYS.os);
    QTableWidgetItem  *pos3 = new QTableWidgetItem(SYS.cpu);
    QTableWidgetItem  *pos4 = new QTableWidgetItem(SYS.bios[0]);
    QTableWidgetItem  *pos5 = new QTableWidgetItem(SYS.bios[1]);
    QTableWidgetItem  *pos6 = new QTableWidgetItem(SYS.port);
    QTableWidgetItem  *pos7 = new QTableWidgetItem(SYS.shutdowntime);

    pos1->setTextAlignment(Qt::AlignCenter);
    pos2->setTextAlignment(Qt::AlignCenter);
    pos3->setTextAlignment(Qt::AlignCenter);
    pos4->setTextAlignment(Qt::AlignCenter);
    pos5->setTextAlignment(Qt::AlignCenter);
    pos6->setTextAlignment(Qt::AlignCenter);
    pos7->setTextAlignment(Qt::AlignCenter);

    ui->tableWidget->setItem(0,0,pos1);
    ui->tableWidget->setItem(1,0,pos2);
    ui->tableWidget->setItem(2,0,pos3);
    ui->tableWidget->setItem(3,0,pos4);
    ui->tableWidget->setItem(4,0,pos5);
    ui->tableWidget->setItem(5,0,pos6);
    ui->tableWidget->setItem(6,0,pos7);

    ui->tableWidget->setRowCount(8);


    /*
     * 显示IE浏览记录信息
     * 表格设置自适应
     * 实例化word类
     * 读取注册表存储的IE浏览记录信息
     * 格式化显示
     */
     ie IE;
     ui->tableWidget_2->resizeRowsToContents();
     ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->tableWidget_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     for (int i=1;i<=IE.number;i++)
     {
         QTableWidgetItem *pos1 = new QTableWidgetItem(IE.name[i]);
         QTableWidgetItem *pos2 = new QTableWidgetItem(IE.time[i]);
         pos1->setTextAlignment(Qt::AlignCenter);
         pos2->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget_2->setItem(i-1,0,pos1);
         ui->tableWidget_2->setItem(i-1,1,pos2);
     }
     ui->tableWidget_2->setRowCount(IE.number);

    /*
     * 显示开机启动项目信息
     * 表格设置自适应
     * 实例化autorun类
     * 读取注册表存储的开机启动项目信息
     * 格式化显示
     */
    ui->tableWidget_3->resizeRowsToContents();
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    autorun RUN;
    for (int i=1;i<=RUN.number;i++)
    {
        QTableWidgetItem *pos1 = new QTableWidgetItem(RUN.name[i]);
        QTableWidgetItem *pos2 = new QTableWidgetItem(RUN.path[i]);
        pos1->setTextAlignment(Qt::AlignCenter);
        pos2->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_3->setItem(i-1,0,pos1);
        ui->tableWidget_3->setItem(i-1,1,pos2);
    }
    ui->tableWidget_3->setRowCount(RUN.number);

    /*
     * 显示浏览文档信息
     * 表格设置自适应
     * 实例化word类
     * 读取注册表存储的浏览文档信息
     * 格式化显示
     */
    ui->tableWidget_4->resizeRowsToContents();
    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_4->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    word WORD;
    for (int i=1;i<=WORD.number;i++)
    {
        QTableWidgetItem *pos1 = new QTableWidgetItem(WORD.w_name[i]);
        QTableWidgetItem *pos2 = new QTableWidgetItem(WORD.w_path[i]);
        QTableWidgetItem *pos3 = new QTableWidgetItem(WORD.w_time[i]);
        pos1->setTextAlignment(Qt::AlignCenter);
        pos2->setTextAlignment(Qt::AlignCenter);
        pos3->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_4->setItem(i-1,0,pos1);
        ui->tableWidget_4->setItem(i-1,1,pos2);
        ui->tableWidget_4->setItem(i-1,2,pos3);
    }
    ui->tableWidget_4->setRowCount(WORD.number);


    /*
     * 显示USB设备信息
     * 表格设置自适应
     * 实例化usb类
     * 读取注册表存储的USB设备信息
     * 格式化显示
     */

    ui->tableWidget_5->resizeRowsToContents();
    ui->tableWidget_5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_5->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    usb USB;
    for (int i=1;i<=USB.number;i++)
    {
        QTableWidgetItem *pos1 = new QTableWidgetItem(USB.u_id[i]);
        QTableWidgetItem *pos2 = new QTableWidgetItem(USB.u_name[i]);
        QTableWidgetItem *pos3 = new QTableWidgetItem(USB.u_time[i]);
        pos1->setTextAlignment(Qt::AlignCenter);
        pos2->setTextAlignment(Qt::AlignCenter);
        pos3->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_5->setItem(i-1,0,pos1);
        ui->tableWidget_5->setItem(i-1,1,pos2);
        ui->tableWidget_5->setItem(i-1,2,pos3);
    }
    ui->tableWidget_5->setRowCount(USB.number);

}

MainWindow::~MainWindow()
{
    delete ui;
}

