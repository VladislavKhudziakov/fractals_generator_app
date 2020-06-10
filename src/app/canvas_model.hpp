

#pragma once

#include <vector>

namespace App
{
    class line;

    class canvas_model
    {
    public:
        canvas_model();
        ~canvas_model();

        const std::vector<std::unique_ptr<line>>& get_lines() const;
        std::vector<std::unique_ptr<line>>& get_lines();

    private:
        std::vector<std::unique_ptr<line>> m_lines;
    };
}

