

#include "init_app.hpp"

#include <src/app/fractals_renderer_view_model.hpp>
#include <src/app/line.hpp>
#include <src/app/view_models_factory.hpp>

#include <QQmlApplicationEngine>

#include <QQuickStyle>

void App::init_app()
{
    QQuickStyle::setStyle("Material");
    QQuickStyle::setFallbackStyle("Material");

    qmlRegisterAnonymousType<App::fractals_renderer_view_model>("App", 1);
    qmlRegisterAnonymousType<App::line>("App", 1);

    qmlRegisterSingletonInstance("App", 1, 0, "ViewModelsFactory", view_models_factory::get_instance());
}
