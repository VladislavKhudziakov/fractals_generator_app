

#include "canvas_model.hpp"

#include <src/app/line.hpp>


App::canvas_model::canvas_model() = default;
App::canvas_model::~canvas_model() = default;


const std::vector<std::unique_ptr<App::line>> &App::canvas_model::get_lines() const
{
    return m_lines;
}


std::vector<std::unique_ptr<App::line>> &App::canvas_model::get_lines()
{
    return m_lines;
}


