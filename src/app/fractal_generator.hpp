


#pragma once

#include <src/app/line.hpp>

#include <QTransform>

#include <mutex>
#include <stack>

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
        using lines_handler = std::function<void()>;
        fractal_generator();
        void make_fractal(uint32_t depth);
        void push_point(QPointF);

        void subscribe_lines_handler(const lines_handler&);

        template<typename CallbackType>
        void handle_lines(CallbackType&& cb) const
        {
            std::unique_lock g(m_lines_mutex, std::try_to_lock);
            cb(m_lines);
        }

        void set_points_pattern(const std::vector<QPointF>&);
    private:
        void make_fractals_generation();

        std::vector<fractal_line> m_lines;
        std::stack<QPointF> m_points;
        std::vector<QPointF> m_points_pattern;
        std::vector<lines_handler> m_lines_handlers;

        mutable std::mutex m_lines_mutex;
        mutable std::mutex m_lines_handlers_mutex;
        mutable std::mutex m_points_mutex;
        mutable std::mutex m_points_pattern_mutex;
    };
}
