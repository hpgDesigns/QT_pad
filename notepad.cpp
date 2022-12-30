#include <QFile>
#include <QProcess>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextStream>
#include <QTextDocument>
#include <QMessageBox>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QPalette>
#include <QPainter>
#include <QtWidgets>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPdf/QtPdf>
#include <QtPrintSupport/QtPrintSupport>

#include "notepad.h"
#include "ui_notepad.h"

notepad::notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::notepad)
{
    ui->setupUi(this);

#if QT_CONFIG(clipboard)
    connect(ui->textEdit, &QTextEdit::copyAvailable, ui->actionCopy, &QAction::setEnabled);
    connect(ui->actionCopy, &QAction::triggered, ui->textEdit, &QTextEdit::copy);
    connect(ui->actionCut, &QAction::triggered, ui->textEdit, &QTextEdit::cut);
    connect(ui->actionPaste, &QAction::triggered, ui->textEdit, &QTextEdit::paste);
#endif
    connect(ui->textEdit, &QTextEdit::undoAvailable, ui->actionUndo, &QAction::setEnabled);
    connect(ui->actionUndo, &QAction::triggered, ui->textEdit, &QTextEdit::undo);
    connect(ui->textEdit, &QTextEdit::redoAvailable, ui->actionRedo, &QAction::setEnabled);
    connect(ui->actionRedo, &QAction::triggered, ui->textEdit, &QTextEdit::redo);

#if !QT_CONFIG(clipboard)
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);
#endif
}


    notepad::~notepad()
{
    delete ui;
}


void notepad::Create()
{
    currentfile.clear();
    ui->textEdit->setText(QString());
}


void notepad::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
        if (fileName.isEmpty())
            return;
        QFile file(fileName);
        currentfile = fileName;
        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
            return;
        }
        setWindowTitle(fileName);
        QTextStream in(&file);
        QString text = in.readAll();
        ui->textEdit->setText(text);
        file.close();
}


void notepad::on_actionSave_triggered()
{
    QString fileName;
       // If we don't have a filename from before, get one.
       if (currentfile.isEmpty()) {
           fileName = QFileDialog::getSaveFileName(this, "Save");
           if (fileName.isEmpty())
               return;
           currentfile = fileName;
       } else {
           fileName = currentfile;
       }
       QFile file(fileName);
       if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
           QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
           return;
       }
       setWindowTitle(fileName);
       QTextStream out(&file);
       QString text = ui->textEdit->toPlainText();
       out << text;
       file.close();
}
void notepad::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as", "/home/hughiep/Documents","HTML Document(*.html);; Text Files(*.txt)");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentfile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}
void notepad::selectFont()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}


void notepad::on_actionQuit_triggered()
{

}

void notepad::Cut()
{

}

void notepad::Copy()
{

}

void notepad::Paste()
{

}

void notepad::Redo()
{

}

void notepad::Undo()
{

}

void notepad::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About Notepad"),
                           tr("This custom <b>Notepad</b> text editor was created by Hugh Patrick Greene"
                              " using Qt6 QtWidgets"));
}



void notepad::on_actionSelect_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}

void notepad::on_actionBold_triggered(bool bold)
{
   // bold ? ui->textEdit->setFontWeight(QFont::Bold):
   //        ui->textEdit->setFontWeight(QFont::Normal);
    ui->textEdit->setFontWeight(QFont::Bold);
   // ui->textEdit->setFontWeight(QFont::Normal);
}


void notepad::on_actionItalic_triggered(bool italic)
{
    ui->textEdit->setFontItalic(1);
}


void notepad::on_actionNormal_triggered(bool normal)
{
    ui->textEdit->setFontWeight(QFont::Normal);
}


void notepad::on_actionUnderline_triggered(bool underline)
{
    ui->textEdit->setFontUnderline(1);
}


void notepad::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color.isValid())
    {
        ui->textEdit->setTextColor(color);

    }
}


void notepad::on_actionBackground_Text_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color.isValid())
    {
        ui->textEdit->setTextBackgroundColor(color);

    }
}


void notepad::on_actionChange_Area_Color_triggered()
{

}

void notepad::on_actionExport_HTML_triggered()
{
    //QString fileName = QFileDialog.getSaveFileName(self, "Export As", "/home/hughiep/Documents","PDF Document(*.pdf);; All Files(*.*)");
    {
    //QFile file(fileName);
    //QPrinter printer;
    //printer.setFullPage(true);
    //    QPrintDialog dialog(&printer, this);


    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export HTML", QString(), "*.html");
        if (QFileInfo(fileName).suffix().isEmpty())
        {
            fileName.append(".html");

        }
        QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
            return;
        }
        currentfile = fileName;
        setWindowTitle(fileName);
        QTextStream out(&file);
        QString text = ui->textEdit->toHtml();
        out << text;
        file.close();


 //       QPrinter printer = QPrinter();
       // printer.setFullPage(true);
   //     printer.setOutputFileName( fileName );
        // printer.setOutputFormat( QPrinter::PdfFormat );
        // printer.setOutputFileName("output.pdf");

    //enum
    //    QPrinter printer = QPrinter(QPrinter::PrinterMode(2));
       // QPrinter printer = QPrinter(QPrinter::HighResolution);
    //    printer.setOutputFormat(QPrinter::PdfFormat);
    //    printer.setPageSize(QPageSize::Letter);
    //    printer.setOutputFileName(fileName);

    /*
        QTextDocument doc;
        doc.setHtml("<h1>Hello, World!</h1>\n<p>Lorem ipsum dolor sit amet, consectitur adipisci elit.</p>");
        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
        doc.print(&printer);

    */
}





}






