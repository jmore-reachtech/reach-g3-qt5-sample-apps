#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModbusDataUnit>

QT_BEGIN_NAMESPACE

class QModbusClient;
class QModbusReply;

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class WriteRegisterModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    void initActions();
    QModbusDataUnit readRequest() const;
    QModbusDataUnit writeRequest() const;

private slots:
    void on_connectButton_clicked();
    void onStateChanged(int state);
    void onModConnected_Changed();
    void on_readButton_clicked();
    void readReady();
    void on_clearButton_clicked();
    void on_writeButton_clicked();
    void onConnTypeChanged();

private:
    Ui::MainWindow *ui;
    QModbusReply *lastRequest;
    QModbusClient *modbusDevice;

};

#endif // MAINWINDOW_H
