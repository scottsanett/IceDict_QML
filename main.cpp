#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "main.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    Dictionary dic;
    QObject * mainApp = engine.rootObjects().first(); //access the root item
    QObject * item1 = mainApp->findChild<QObject*>("item1"); //access a specific item
    dic.setRoot(mainApp, item1);
    QObject::connect(item1, SIGNAL(onlineDefSig(QString)),
                     &dic, SLOT(onlineDefinition(QString)));
    QObject::connect(item1, SIGNAL(onlineDefClickedSig(int)),
                     &dic, SLOT(onlineDefSelected(int)));
    QObject * item2 = mainApp->findChild<QObject*>("item2");
    QObject::connect(item2, SIGNAL(onlineTextSig(QString)),
                     &dic, SLOT(onlineText(QString)));
    QObject::connect(item2, SIGNAL(onlineTextClickedSig(int)),
                     &dic, SLOT(onlineTextSelected(int)));
    QObject * item3 = mainApp->findChild<QObject*>("item3");
    QObject::connect(item3, SIGNAL(findDefSig(QString)),
                     &dic, SLOT(findDefinition(QString)));
    QObject::connect(item3, SIGNAL(findDefClickedSig(int)),
                     &dic, SLOT(findDefSelected(int)));
    QObject::connect(item3, SIGNAL(textChangedSig(QString)),
                     &dic, SLOT(textChanged(QString)));
    QObject * item4 = mainApp->findChild<QObject*>("item4");
    QObject::connect(item4, SIGNAL(findTextSig(QString)),
                     &dic, SLOT(textualSearch(QString)));
    QObject::connect(item4, SIGNAL(findTextClickedSig(int)),
                     &dic, SLOT(textualSearchSelected(int)));
    QObject * item5 = mainApp->findChild<QObject*>("item5");
    QObject::connect(item5, SIGNAL(querySig(QString)),
                     &dic, SLOT(findInflection(QString)));
    QObject * item6 = mainApp->findChild<QObject*>("item6");
    QObject::connect(item6, SIGNAL(printAllSig(QString)),
                     &dic, SLOT(printAll(QString)));
    QObject::connect(item6, SIGNAL(printAllClickedSig(int)),
                     &dic, SLOT(printAllSelected(int)));
    return app.exec();
}
