#include <QtGui/QSplitter>
#include <QMessageBox>
#include "mainwindow.h"

#include "markdown.h"
#include "html.h"
#include "buffer.h"

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

    QFile file(m_fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(m_fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    m_edit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
}
