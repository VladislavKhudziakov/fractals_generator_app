

#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <src/app/app.hpp>
#include <QQuickWindow>
#include <QQuickView>
#include <QQuickStyle>


int main(int argc, char** argv)
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    App::app::register_metaobjects();
    App::app::apply_theme();
    App::app myapp {};

    QQuickWindow w {};
    QQuickView qqv{&w};
    qqv.setSource(QUrl("qrc:/main.qml"));
    qqv.show();

    return QGuiApplication::exec();
}
