#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QColorDialog>
#include <QColor>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_5_triggered();
    void showCursorPos();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_action_15_triggered();

    void on_action_6_triggered();

    void on_action_7_triggered();

    void on_action_8_triggered();

    void on_action_9_triggered();

    void on_action_10_triggered();

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_comboBox_activated(int index);

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_actionleftAligment_triggered();

    void on_actioncenterAligment_triggered();

    void on_actionrightAligment_triggered();

private:
    Ui::MainWindow *ui;

    QString currentFileName = "";
};
#endif // MAINWINDOW_H
