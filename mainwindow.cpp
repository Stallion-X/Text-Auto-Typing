#include "mainwindow.h"
#include "ui_mainwindow.h"

//初始化全局变量
int MainWindow::choose = 2;
bool MainWindow::isTab = false;
bool MainWindow::isFucked = true;
int MainWindow::speed;
bool MainWindow::isTesting = false;
bool MainWindow::isAuto = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("文本自动输入器");
    cfg = new QSettings("Config.ini", QSettings::IniFormat);
    speed = cfg->value("Speed/Max").toInt();
    cfg->sync();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString s = ui->textEdit->toPlainText();
//去除tab选项
    if (isTab)
    {
        QRegExp re("\\t");
        s.replace(re,"");
    }
//多线程执行弹窗倒计时
    QtConcurrent::run(this,&MainWindow::newwindow);
    QElapsedTimer t;
    t.start();
    while(t.elapsed()<2000)
        QCoreApplication::processEvents();
//多线程执行输入操作
    QtConcurrent::run(this,&MainWindow::SendKeyString,s);
    //SendKeyString(s);
}
void MainWindow::SendKeyString(QString text)
{
//通过附加线程到前台窗口的方式 获得编辑框的句柄
    HWND wnd = NULL;
    wnd = GetForegroundWindow();
    DWORD SelfThreadId = GetCurrentThreadId();
    DWORD ForeThreadId = GetWindowThreadProcessId(wnd, NULL);
    AttachThreadInput(ForeThreadId, SelfThreadId, true);
    wnd = GetFocus();
    hEdit = wnd;
    AttachThreadInput(ForeThreadId, SelfThreadId, false);
//方式1只能使用char数组 只能识别ASCII字符简单模拟敲击键盘 即无法输入中文
    std::string s = text.toStdString();
    const char *str = s.c_str();
    switch(choose)
    {
        case 1:
//方式1的模拟键盘代码十分古老 原作者和出处已不可考 以下注释为本人猜测
            DWORD sc, shift;
            unsigned char vkey;
            long long i;
            for (i = 0; str[i] != '\0'; i++) {
//ASCII字符映射为OEM扫描码
            sc = OemKeyScan(str[i]);
//未知 看似是扫描码移位16位可以获得shift状态?
            shift = sc >> 16;
//将扫描码翻译成虚拟键码 以供keybd_event使用
            vkey = MapVirtualKey(sc & 0xffff, 1);
//如果该扫描码包含shift 则按下shift
            if (shift)
                keybd_event(VK_SHIFT, 0, 0, 0);
//按下再松开给定字符
            keybd_event(vkey, 0, 0, 0);
            keybd_event(vkey, 0, KEYEVENTF_KEYUP, 0);
//如果该扫描码包含shift 则松开shift
            if (shift)
                keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
//停顿 以避开作业系统对时间间隔的检查
            if (isFucked)
            {
                Sleep(speed/10);
            }
        }
            break;
        case 2:
            if (isFucked)
            {
//使用正则匹配 6个文字分为一组
                QRegExp regex;
                regex.setPatternSyntax(QRegExp::RegExp);
                regex.setPattern(".{1,6}");
                regex.exactMatch(text);
                int pos =0;
                QString sub;
                while (pos >=0&&pos<=text.length())
                {
                    pos = regex.indexIn(text,pos);
                    if(pos >=0)
                    {
                        sub = text.mid(pos,6);
                        //qDebug()<<sub;
                        int nLenth = SendMessage(hEdit,WM_GETTEXTLENGTH,0,0);
//光标强制置后 应对作业系统随机性调光标到最前端
                        SendMessage(wnd, EM_SETSEL, nLenth, nLenth);
                        SetFocus(wnd);
//分段拼接文本
                        SendMessage(wnd, EM_REPLACESEL, FALSE, (LPARAM)(LPCTSTR)reinterpret_cast<LPCWSTR>(sub.data()));
//下滑滚动条 后经测试会影响稳定性
                        //PostMessage(wnd,WM_VSCROLL, SB_BOTTOM,0);
//停顿 以避开作业系统对时间间隔的检查
                        Sleep(speed);
//此处貌似并无必要 和正则可二选一
                        pos+=6;
                    }
                }
            }
            else
            {
//早期版本曾经使用的一键灌入文本
                SendMessage(wnd, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)reinterpret_cast<LPCWSTR>(text.data()));
                Sleep(100);
            }
            break;
    }
    //qDebug()<<isSuc();
    if (!isSuc()&&isAuto)
    {
        //SendKeyString("");
        QString blank = QString("");
        SendMessage(wnd, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)reinterpret_cast<LPCWSTR>(blank.data()));
        if (!isTesting)
        {
            speed+=50;
        }
        else
        {
            speed++;
        }
        SendKeyString(text);
    }
//检测输入文本是否一致
    if (!isSuc()&&!isAuto)
    {
        //QMessageBox::information(NULL, "Error", "请注意，程序检测到自动输入结果和原文不一致，请自行核对");
//操作界面时需要切回主线程执行
        QMetaObject::invokeMethod(qApp, [=]
        {
            QMessageBox msgBox(QMessageBox::Critical,"Error", "请注意，程序检测到自动输入结果和原文不一致，请自行核对",QMessageBox::Ok,NULL);
            msgBox.setWindowFlag(Qt::WindowStaysOnTopHint);
            msgBox.setWindowIcon(QIcon(":/keyboard.png"));
            msgBox.exec();
        });
    }
//如果检测到输入文本一致 自动打一个a再删去 以应对作业系统删文件
    if (isSuc())
    {
        keybd_event(65,0,0,0);
        keybd_event(65,0,KEYEVENTF_KEYUP,0);
        Sleep(1000);
        keybd_event(8,0,0,0);
        keybd_event(8,0,KEYEVENTF_KEYUP,0);
    }
//自动调试
    if (isSuc()&&isTesting)
    {
        cfg->setValue("Use/First", 1);
        cfg->setValue("Speed/Max", speed);
        cfg->sync();
    }
}
bool MainWindow::isSuc()
{
//正确的获取文本长度方法 其它方法很多都无法正确获得
    int len = SendMessage(hEdit,WM_GETTEXTLENGTH,0,0);
    //qDebug()<<len;
    wchar_t* s1 = new wchar_t[len+1];
//获取编辑框内容
    SendMessage(hEdit,WM_GETTEXT,len+1,(LPARAM)s1);
//获取后进行转码 再通过正则把Windows API默认的\r\n换行方式替换成\n
    QString str = QString::fromWCharArray(s1);
    //qDebug()<<str;
    QString str2 = ui->textEdit->toPlainText();
    QRegExp reg;
    reg.setPatternSyntax(QRegExp::RegExp);
    reg.setPattern("\\r");
    reg.exactMatch(str);
    str.replace(reg,"");
//如果打开了去除tab选项 则把\t也删去
    if (isTab)
    {
        QRegExp re("\\t");
        str2.replace(re,"");
    }
    //qDebug()<<"str:"+str;
    //qDebug()<<"str2:"+str2;
    if (str==str2)
    {
        return true;
    }
    return false;
}
void MainWindow::newwindow()
{
    emit emitsignal();
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
    qApp->quit();
}

void MainWindow::on_actionAbout_triggered()
{
    emit emitabout();
}

void MainWindow::on_actionSettings_triggered()
{
    emit emitsettings();
}

void MainWindow::on_pushButton_2_clicked()
{
    emit emitspeed();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
}
