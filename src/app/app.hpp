


#pragma once

#include <memory>

namespace App
{
    class fractal_generator;
    class fractal_pattern_generator;

    class app
    {
    public:
        static void register_metaobjects();
        static void apply_theme();
        app();
    private:
        std::shared_ptr<fractal_generator> m_fractal_generator;
        std::shared_ptr<fractal_pattern_generator> m_fractal_pattern_generator;
    };
}

