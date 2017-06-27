#include "main_window.h"

MainWindow::MainWindow(Cef *cef, QWidget *parent) : QMainWindow(parent) {
  // Set CEF and start the timer
  // TODO: how to determine best interval
  // TODO: is the timer destructed for us?
  cef_ = cef;
  if (startTimer(10) == 0) {
    throw std::runtime_error("Unable to start CEF timer");
  }

  // Common settings
  setWindowTitle("QT CEF POC");
  setFocusPolicy(Qt::FocusPolicy::StrongFocus);
  resize(1024, 768);

  cef_widg_ = new CefWidget(cef);

  url_line_edit_ = new QLineEdit;
  connect(url_line_edit_, SIGNAL(returnPressed()), this, SLOT(UrlEntered()));

  auto layout = new QGridLayout;
  layout->addWidget(url_line_edit_, 0, 0);
  layout->addWidget(cef_widg_, 1, 0);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->setRowStretch(0, 0);
  layout->setRowStretch(1, 1);
  auto frame = new QFrame;
  frame->setLayout(layout);
  setCentralWidget(frame);
}

MainWindow::~MainWindow() {
}

void MainWindow::timerEvent(QTimerEvent*) {
  cef_->Tick();
}

void MainWindow::showEvent(QShowEvent* event) {
  cef_widg_->EmbedBrowser();
  QWidget::showEvent(event);
}

void MainWindow::UrlEntered() {
  qInfo() << "You entered " << url_line_edit_->text();
}