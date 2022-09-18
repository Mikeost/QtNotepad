#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->showMessage(QString("Позиція курсору: Строка 1, Символ 1"));
    connect(ui->textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(showCursorPos()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_5_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Вийти", "Ви дійсно хочете вийти?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
            QApplication::quit();
    }
}

void MainWindow::showCursorPos()
{
    int line = ui->textEdit->textCursor().blockNumber() + 1;
    int pos = ui->textEdit->textCursor().columnNumber() + 1;
    ui->statusbar->showMessage(QString("Позиція курсору: Строка %1, Символ %2").arg(line).arg(pos));
}

void MainWindow::on_action_2_triggered()
{
    currentFileName.clear();
    ui->textEdit->setText(QString());

    QTextCharFormat format;
    QTextCursor cursor = ui->textEdit->textCursor();
    format.setFontItalic(false);
    format.setFontWeight(QFont::Normal);
    format.setFontUnderline(false);
    format.setFontStrikeOut(false);
    cursor.mergeCharFormat(format);
}


void MainWindow::on_action_3_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Відкрити файл"));
    QFile file(fileName);
    currentFileName = fileName;

    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Попередження", "Файл не відкрився: " + file.errorString());
    }

    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);

    file.close();
}


void MainWindow::on_action_4_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Зберегти файл"));
    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Попередження", "Файл не зберігся: " + file.errorString());
        return;
    }

    currentFileName = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;

    file.close();
}


void MainWindow::on_action_15_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Назва принтеру:");
    QPrintDialog pDialog(&printer, this);

    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Попередження", "Принтер недоступний");
        return;
    }

    ui->textEdit->print(&printer);
}


void MainWindow::on_action_6_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_action_7_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_action_8_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_action_9_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_action_10_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->textEdit->setFont(f);
}


void MainWindow::on_comboBox_activated(int index)
{
    QTextCharFormat format;
    QTextCursor cursor = ui->textEdit->textCursor();

    switch(index){
    case 1:
        format.setFontItalic(true);
        cursor.mergeCharFormat(format);
        break;
    case 2:
        format.setFontWeight(QFont::Bold);
        cursor.mergeCharFormat(format);
        break;
    case 3:
        format.setFontUnderline(true);
        cursor.mergeCharFormat(format);
        break;
    case 4:
        format.setFontStrikeOut(true);
        cursor.mergeCharFormat(format);
        break;
    case 0:
    default:
        format.setFontItalic(false);
        format.setFontWeight(QFont::Normal);
        format.setFontUnderline(false);
        format.setFontStrikeOut(false);
        cursor.mergeCharFormat(format);
    }
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    ui->textEdit->selectAll();
    ui->textEdit->setFontPointSize(arg1);
    ui->textEdit->setTextCursor( cursor );
}


void MainWindow::on_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Оберіть колір");
    if(color.isValid()){
        ui->textEdit->setTextColor(color);
        QString qss = QString("background-color: %1").arg(color.name());
        ui->pushButton->setStyleSheet(qss);
    }
}


void MainWindow::on_actionleftAligment_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignLeft);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->textEdit->setTextCursor(cursor);
}


void MainWindow::on_actioncenterAligment_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->textEdit->setTextCursor(cursor);
}


void MainWindow::on_actionrightAligment_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignRight);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->textEdit->setTextCursor(cursor);
}


void MainWindow::on_action_14_triggered()
{
    QString link = "http://www.mikeost.com";
    QDesktopServices::openUrl(QUrl(link));
}


void MainWindow::on_action_13_triggered()
{
    QString link = "https://github.com/Mikeost/QtNotepad";
    QDesktopServices::openUrl(QUrl(link));
}

