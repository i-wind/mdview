#include <QtGui/QSplitter>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QSplitter* splitter = new QSplitter();

    edit = new QPlainTextEdit(this);
    splitter->addWidget(edit);
    view = new QWebView(this);
    splitter->addWidget(view);

    setCentralWidget(splitter);
    setWindowTitle("Markdown preview");
}
