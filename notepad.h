#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class notepad;
}
QT_END_NAMESPACE

class notepad : public QMainWindow
{
    Q_OBJECT

public:
    notepad(QWidget *parent = nullptr);
    ~notepad();

private slots:
    void Create();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionQuit_triggered();
    void selectFont();
    void Cut();
    void Copy();
    void Paste();
    void Redo();
    void Undo();
    void on_actionAbout_triggered();
    void on_actionSelect_triggered();
    void on_actionBold_triggered(bool bold);
    void on_actionItalic_triggered(bool italic);
    void on_actionNormal_triggered(bool normal);
    void on_actionUnderline_triggered(bool underline);

    void on_actionColor_triggered();
    void on_actionBackground_Text_Color_triggered();
    void on_actionChange_Area_Color_triggered();
    void on_actionExport_HTML_triggered();

private:
    Ui::notepad *ui;
    QString currentfile;
};
#endif // NOTEPAD_H
