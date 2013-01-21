#include <QtGui/QSplitter>
#include "mainwindow.h"

MainWindow::MainWindow(const QString &fileName, QWidget *parent)
    : QMainWindow(parent),
      m_fileName(fileName)
{
    //m_fileName = fileName;
    QSplitter* splitter = new QSplitter();

    m_edit = new QPlainTextEdit(this);
    splitter->addWidget(m_edit);
    m_view = new QWebView(this);
    splitter->addWidget(m_view);

    setCentralWidget(splitter);
    setWindowTitle("Markdown preview");
}
