

#include "app.hpp"

#include <src/app/fractals_renderer_view_model.hpp>
#include <src/app/pattern_generator_view_model.hpp>

#include <src/app/line.hpp>
#include <src/app/fractal_generator.hpp>
#include <src/app/fractal_pattern_generator.hpp>

#include <src/app/view_models_factory.hpp>

#include <QQmlApplicationEngine>
#include <QQuickStyle>


void App::app::register_metaobjects()
{
    qmlRegisterAnonymousType<App::fractals_renderer_view_model>("App", 1);
    qmlRegisterAnonymousType<App::pattern_generator_view_model>("App", 1);
    qmlRegisterAnonymousType<App::line>("App", 1);

    qmlRegisterSingletonInstance("App", 1, 0, "ViewModelsFactory", view_models_factory::get_instance());
}


void App::app::apply_theme()
{
    QQuickStyle::setStyle("Material");
    QQuickStyle::setFallbackStyle("Material");
}


App::app::app()
{
    m_fractal_generator = std::make_shared<fractal_generator>();
    m_fractal_pattern_generator = std::make_shared<fractal_pattern_generator>(m_fractal_generator);
    view_models_factory::get_instance()->set_fractals_generator(m_fractal_generator);
    view_models_factory::get_instance()->set_pattern_generator(m_fractal_pattern_generator);

}



