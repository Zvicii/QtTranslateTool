#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitAllControl();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitAllControl()
{
    //默认选中英文转中文
    OnEn2CnClicked();
}

void MainWindow::OnEn2CnClicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEn2Cn);
}

void MainWindow::OnCn2CnClicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageCn2Cn);
}
