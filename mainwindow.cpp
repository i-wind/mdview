#include <QtGui/QSplitter>
#include <QMessageBox>
#include <QFileDialog>
#include "mainwindow.h"

#include "markdown.h"
#include "html.h"
#include "buffer.h"

#define READ_UNIT 1024
#define OUTPUT_UNIT 64

MainWindow::MainWindow(const QString &fileName, QWidget *parent)
    : QMainWindow(parent),
      m_fileName(fileName)
{
    createWidgets();
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    connect(m_edit->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));
}

void MainWindow::newFile()
{
    if (maybeSave()) {
        m_edit->clear();
        m_view->setHtml("");
        setCurrentFile("");
    }
}

void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::save()
{
    if (m_fileName.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(m_fileName);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

// Update the contents in the web viewer.
void MainWindow::refresh()
{
    QString text = m_edit->toPlainText();
    QByteArray data = text.toLocal8Bit();

    struct buf *ib, *ob;
    struct sd_callbacks callbacks;
    struct html_renderopt options;
    struct sd_markdown *markdown;

    /* reading everything */
    ib = bufnew(128);
    bufput(ib, (void*) data.data(), data.size());

    /* performing markdown parsing */
    ob = bufnew(OUTPUT_UNIT);

    sdhtml_renderer(&callbacks, &options, 0);
    markdown = sd_markdown_new(0, 16, &callbacks, &options);

    sd_markdown_render(ob, ib->data, ib->size, markdown);
    sd_markdown_free(markdown);

    /* writing the result to stdout */
    fwrite(ob->data, 1, ob->size, stdout);
    QString html = QString::fromUtf8((const char*) ob->data, ob->size).toUtf8();
    m_view->setHtml(html);

    /* cleanup */
    bufrelease(ib);
    bufrelease(ob);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Application"),
             tr("The <b>Markdown preview</b> application demonstrates how to "
                "write modern GUI applications using Qt, with a menu bar, "
                "toolbars, and a status bar."
                "<br><br>version 0.1.0"));
}

void MainWindow::documentWasModified()
{
    setWindowModified(m_edit->document()->isModified());
}

void MainWindow::createWidgets()
{
    QSplitter* splitter = new QSplitter();

    m_edit = new QPlainTextEdit(this);
    splitter->addWidget(m_edit);
    m_view = new QWebView(this);
    splitter->addWidget(m_view);

    setCentralWidget(splitter);
    //m_view->settings()->setUserStyleSheetUrl(QUrl("qrc:/markdown.css"));
    //m_view->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile("markdown.css"));
    m_view->settings()->setUserStyleSheetUrl(QUrl("data:text/css;charset=utf-8;base64," + css.toBase64()));
    if (!m_fileName.isEmpty())
        loadFile(m_fileName);
    setWindowTitle("Markdown preview [*]");
}

void MainWindow::createActions()
{
    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    refreshAct = new QAction(QIcon(":/images/refresh.png"), tr("&Refresh"), this);
    refreshAct->setShortcuts(QKeySequence::Refresh);
    refreshAct->setStatusTip(tr("Refresh html preview of the current markdown text"));
    connect(refreshAct, SIGNAL(triggered()), this, SLOT(refresh()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(refreshAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(refreshAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

// Display markdown file in simple text view and convert it to html
void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    m_edit->setPlainText(in.readAll());

    struct buf *ib, *ob;
    int ret;
    FILE *fin = NULL;

    struct sd_callbacks callbacks;
    struct html_renderopt options;
    struct sd_markdown *markdown;

    fin = fopen(fileName.toAscii().data(), "r");

    /* reading everything */
    ib = bufnew(READ_UNIT);
    bufgrow(ib, READ_UNIT);
    while ((ret = fread(ib->data + ib->size, 1, ib->asize - ib->size, fin)) > 0) {
        ib->size += ret;
        bufgrow(ib, ib->size + READ_UNIT);
    }

    if (fin != stdin)
        fclose(fin);

    /* performing markdown parsing */
    ob = bufnew(OUTPUT_UNIT);

    sdhtml_renderer(&callbacks, &options, 0);
    markdown = sd_markdown_new(0, 16, &callbacks, &options);

    sd_markdown_render(ob, ib->data, ib->size, markdown);
    sd_markdown_free(markdown);

    /* writing the result to stdout */
    ret = fwrite(ob->data, 1, ob->size, stdout);
    //QString html = QString(reinterpret_cast<const char*>(ob->data)).toUtf8();
    QString html = QString::fromUtf8((const char*) ob->data, ob->size).toUtf8();
    m_view->setHtml(html);

    /* cleanup */
    bufrelease(ib);
    bufrelease(ob);
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << m_edit->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

bool MainWindow::maybeSave()
{
    if (m_edit->document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Application"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            //return save();
            return true;
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    m_fileName = fileName;
    m_edit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = m_fileName;
    if (m_fileName.isEmpty())
        shownName = "untitled.md";
    setWindowFilePath(shownName);
}
