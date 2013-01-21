#include <QtGui/QSplitter>
#include "mainwindow.h"

MainWindow::MainWindow(const QString &fileName, QWidget *parent)
    : QMainWindow(parent),
      m_fileName(fileName)
{
    createWidgets();
}

void MainWindow::createWidgets()
{
    QSplitter* splitter = new QSplitter();

    m_edit = new QPlainTextEdit(this);
    splitter->addWidget(m_edit);
    m_view = new QWebView(this);
    splitter->addWidget(m_view);

    setCentralWidget(splitter);
    setText();
    setWindowTitle("Markdown preview");
}

// Display markdown file in simple text view and convert it to html
void MainWindow::setText()
{
    if (m_fileName.isEmpty()) return;
    qDebug() << "setText: " << m_fileName;
}
