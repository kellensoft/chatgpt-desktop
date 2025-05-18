#include "mainwindow.h"

#include <QApplication>
#include <QWebEngineView>
#include <QMainWindow>
#include <QWebEngineProfile>
#include <QWebEnginePage>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QMenuBar>
#include <QAction>
#include <QIcon>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/icons/chatgpt.png"));

    QMainWindow window;
    window.setWindowTitle("ChatGPT");
    window.setWindowIcon(QIcon(":/icons/logo.png"));

    // Persistent profile
    QWebEngineProfile *profile = new QWebEngineProfile("chatgpt_profile", &window);

    // Web view with persistent profile
    QWebEngineView *view = new QWebEngineView(&window);
    QWebEnginePage *page = new QWebEnginePage(profile, view);
    view->setPage(page);
    view->load(QUrl("https://chat.openai.com/"));

    // Loading progress bar
    QProgressBar *progressBar = new QProgressBar();
    progressBar->setRange(0, 100);
    progressBar->setTextVisible(false);
    progressBar->setMaximumHeight(4);

    QObject::connect(view, &QWebEngineView::loadProgress, progressBar, &QProgressBar::setValue);
    QObject::connect(view, &QWebEngineView::loadFinished, progressBar, &QProgressBar::hide);
    QObject::connect(view, &QWebEngineView::loadStarted, progressBar, [=]() {
        progressBar->show();
        progressBar->setValue(0);
    });

    // Layout to include progress bar above web view
    QWidget *centralWidget = new QWidget(&window);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(progressBar);
    layout->addWidget(view);
    window.setCentralWidget(centralWidget);

    // Reload action in menu
    QMenuBar *menuBar = window.menuBar();
    QMenu *fileMenu = menuBar->addMenu("File");
    QAction *reloadAction = fileMenu->addAction("Reload");
    QObject::connect(reloadAction, &QAction::triggered, view, &QWebEngineView::reload);

    // Logout action in menu
    QAction *logoutAction = fileMenu->addAction("Logout");
    QObject::connect(logoutAction, &QAction::triggered, [&]() {
        QWebEngineCookieStore *store = profile->cookieStore();
        store->deleteAllCookies();
        view->reload();
    });

    window.resize(1200, 800);
    window.show();

    return app.exec();
}
