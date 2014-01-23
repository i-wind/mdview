#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtWebKit/QWebView>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QStatusBar>
#include <QTextCodec>
#include <QDebug>

const QByteArray css(
  "@charset 'utf-8';"
  "body {"
    "font-family: Helvetica, Arial, Freesans, clean, sans-serif;"
    "padding: 1em;"
    "margin: auto;"
    "max-width: 50em;"
    "background: #fefefe;"
  "}"
  "h1, h2, h3, h4, h5, h6 { font-weight: bold; }"
  "h1 { color: #000000; font-size: 28px; }"
  "h2 { border-bottom: 1px solid #CCCCCC; color: #000000; font-size: 24px; }"
  "h3 { font-size: 18px; }"
  "h4 { font-size: 16px; }"
  "h5 { font-size: 14px; }"
  "h6 { color: #777777; background-color: inherit; font-size: 14px; }"
  "hr { height: 0.2em; border: 0; color: #CCCCCC; background-color: #CCCCCC; }"
  "p, blockquote, ul, ol, dl, table, pre { margin-left: 15px 0; }"
  "code, pre { border-radius: 3px; background-color: #F8F8F8; color: inherit; }"
  "code { border: 1px solid #EAEAEA; margin: 0 2px; padding: 0 5px; }"
  "pre { border: 1px solid #CCCCCC; line-height: 1.25em; overflow: auto; padding: 6px 10px; }"
  "pre > code { border: 0; margin: 0; padding: 0; }"
  "a, a:visited { color: #4183C4; background-color: inherit; text-decoration: none; }"
);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &fileName = QString(), QWidget *parent = 0);

private slots:
    void newFile();

private:
    void createWidgets();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

    void setText();
    bool maybeSave();
    void setCurrentFile(const QString &fileName);

    QPlainTextEdit* m_edit;
    QWebView* m_view;
    QString m_fileName;

    QMenu *fileMenu;
    QToolBar *fileToolBar;
    QAction *newAct;
    QAction *exitAct;
};

#endif // MAINWINDOW_H
