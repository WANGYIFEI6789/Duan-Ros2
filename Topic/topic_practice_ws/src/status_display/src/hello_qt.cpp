#include <QApplication>
#include <QLabel>
#include <QString>

int main(int argc, char** argv){
    QApplication app(argc, argv);
    QLabel* label = new QLabel();
    QString message = QString::fromStdString("Hello Qt!");
    // 将文本放入label
    label->setText(message);
    // 此时label可以展示了 但是要通过app去调用
    label->show();
    // 执行应用  不断循环，阻塞代码
    app.exec();
    return 0;
}