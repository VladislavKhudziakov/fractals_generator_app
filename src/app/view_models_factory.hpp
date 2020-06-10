


#pragma once

#include <QObject>

#include <memory>

namespace App
{
    class fractal_generator;
    class fractal_pattern_generator;

    class view_models_factory : public QObject
    {
    Q_OBJECT
    public:
        view_models_factory();
        ~view_models_factory();
        static view_models_factory* get_instance();
        Q_INVOKABLE QObject* make_fractals_renderer_vm(QObject* parent);
        Q_INVOKABLE QObject* make_pattern_generator_vm(QObject* parent);

        void set_fractals_generator(const std::shared_ptr<fractal_generator>& fg);
        void set_pattern_generator(const std::shared_ptr<fractal_pattern_generator>& g);
    private:
        std::shared_ptr<fractal_generator> m_fractals_generator;
        std::shared_ptr<fractal_pattern_generator> m_fractal_pattern_generator;
    };
}

