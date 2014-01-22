#include <QDir>
#include "mainwindow.h"

QString appendPath(const QString& path1, const QString& path2)
{
    return QDir::cleanPath(path1 + QDir::separator() + path2);
}

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(mdview);

    QApplication app(argc, argv);
    QStringList args = app.arguments();

    QString fileName = QString();
    if (argc>1)
        fileName = appendPath(QDir::currentPath(), args.value(1));

    app.setWindowIcon(QIcon(":/images/preview.png"));

    MainWindow w(fileName);
    w.showMaximized();

    return app.exec();
}
