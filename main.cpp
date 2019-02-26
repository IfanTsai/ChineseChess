// 2016年6月8日19:36:49
// 加了剪枝优化，走棋的优化
// 目前深度为4
// 2016年7月4日14:36:47 追加悔棋功能
// 2016年7月5日15:32:20 实现网络版和不完善的网络聊天功能
// 待解决：网络版聊天功能中文乱码，长度不能过长等问题还没解决
#include "openWidget.h"
#include <QApplication>
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    openWidget w;
    w.show();

    return a.exec();
}

