

#include "line.hpp"

App::line::line(QPointF b , QPointF e)
    : m_begin(b)
    , m_end(e)
{
}


std::unique_ptr<App::line> App::line::create(QPointF b, QPointF e)
{
    return std::make_unique<line>(b, e);
}


QPointF App::line::get_begin() const
{
    return m_begin;
}


QPointF App::line::get_end() const
{
    return m_end;
}
