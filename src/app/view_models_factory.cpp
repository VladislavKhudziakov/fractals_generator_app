

#include "view_models_factory.hpp"

#include <src/app/fractals_renderer_view_model.hpp>
#include <src/app/pattern_generator_view_model.hpp>

#include <src/app/fractal_generator.hpp>
#include <src/app/fractal_pattern_generator.hpp>



App::view_models_factory *App::view_models_factory::get_instance()
{
    static view_models_factory f;
    return &f;
}


App::view_models_factory::view_models_factory()
: QObject(nullptr)
{
}


App::view_models_factory::~view_models_factory() = default;



QObject* App::view_models_factory::make_fractals_renderer_vm(QObject *parent)
{
    return new fractals_renderer_view_model(parent, m_fractals_generator);
}


void App::view_models_factory::set_fractals_generator(const std::shared_ptr<fractal_generator>& fg)
{
    m_fractals_generator = fg;
}


QObject *App::view_models_factory::make_pattern_generator_vm(QObject *parent)
{
    return new pattern_generator_view_model(parent, m_fractal_pattern_generator);
}


void App::view_models_factory::set_pattern_generator(const std::shared_ptr<fractal_pattern_generator>& g)
{
    m_fractal_pattern_generator = g;
}
