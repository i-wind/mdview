#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(mdview);

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/images/preview.png"));

    MainWindow w;
    w.showMaximized();

    return app.exec();
}
