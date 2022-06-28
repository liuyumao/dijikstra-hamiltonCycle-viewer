/* 这个是矩阵输入模式，在主程序界面点击矩阵输入可得一个子窗口，通过点击子窗口上面的表格来进行
 * 路径连接，点击“输入完毕”即可，它会询问是否回头检查，如果不需要就直接离开，反之则回头补充勾选
 */
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
