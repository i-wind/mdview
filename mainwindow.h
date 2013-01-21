#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtWebKit/QWebView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &fileName = QString(), QWidget *parent = 0);

private:
    QPlainTextEdit* m_edit;
    QWebView* m_view;
    QString m_fileName;
};

#endif // MAINWINDOW_H
