#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtWebKit/QWebView>
#include <QtWebKit/QWebHistory>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QStatusBar>
#include <QDockWidget>
#include <QTextCodec>
#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &fileName = QString(), QWidget *parent = 0);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void refresh();
    void display();
    void back();
    void forward();
    void about();
    void documentWasModified();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void createWidgets();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    void readSettings();
    void writeSettings();

    QString pathAppend(const QString &path1, const QString &path2);

private:
    QPlainTextEdit *m_edit;
    QDockWidget *m_dock;
    QWebView *m_view;
    QString m_fileName;

    QMenu *fileMenu;
    QMenu *webMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *webToolBar;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *refreshAct;
    QAction *displayAct;
    QAction *backAct;
    QAction *forwardAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};

#endif // MAINWINDOW_H
