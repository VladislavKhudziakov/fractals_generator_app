


#pragma once

#include <src/app/line.hpp>

#include <stack>

#include <QTransform>

namespace App
{
    class fractal_line
    {
    public:
        fractal_line(QPointF begin, QPointF end);
        void generate(const std::vector<QPointF>&);
        const std::vector<std::unique_ptr<line>>& get_lines() const;
    private:
        std::vector<std::unique_ptr<line>> m_lines;
        QTransform m_transformation;
    };


    class fractal_generator
    {
    public:
        fractal_generator();
        void make_fractal(uint32_t depth);
        void push_point(QPointF);
        std::vector<std::unique_ptr<line>> get_lines() const;
        void set_points_pattern(const std::vector<QPointF>&);
    private:
        void make_fractals_generation();
        std::vector<fractal_line> m_lines;
        std::stack<QPointF> m_points;
        std::vector<QPointF> m_points_pattern;
    };
}
