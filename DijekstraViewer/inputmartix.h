#ifndef INPUTMARTIX_H
#define INPUTMARTIX_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class InputMartix;
}

class InputMartix : public QWidget
{
    Q_OBJECT

public:
    explicit InputMartix(QWidget *parent = nullptr);
    ~InputMartix();
    QStringList getStringList();
    void clearWidgetTable();

private slots:
    void on_btn_ok_clicked();
    void on_btn_submit_clicked();
    void on_spinBox_valueChanged(int);
    void on_btn_quit_clicked();
    void makeFullTable();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent *e)override;

signals:
    void sucess();
    void boxChecked();

private:
    Ui::InputMartix *ui;
    QStringList list;
    int vexNum, arcNum;
    QPoint point;
};

#endif // INPUTMARTIX_H
