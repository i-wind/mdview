#include <QDir>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(mdview);

    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("mdview");
    QCoreApplication::setApplicationVersion("0.1.2");

    QTextCodec* codec = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);

    QStringList args = app.arguments();

    QString fileName = QString();
    if (argc>1)
        fileName = mdview::pathAppend(QDir::currentPath(), args.value(1));

    app.setWindowIcon(QIcon(":/images/preview.png"));

    MainWindow w(fileName);
    w.showMaximized();

    return app.exec();
}
