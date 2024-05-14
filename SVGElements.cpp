#include "SVGElements.hpp"

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const Point &radius)
        : fill(fill), center(center), radius(radius)
    {
    }
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }
    // @todo provide the implementation of SVGElement derived classes
    // HERE -->

    Circle::Circle(const Color &fill,
                   const Point &center,
                   const double &radius)
        : fill(fill), center(center), radius(radius)
    {
    }
    void Circle::draw(PNGImage &img) const
    {
        Point r;
        r.x = radius;
        r.y = radius;
        img.draw_ellipse(center, r, fill);
    }

    Polyline::Polyline(const Color &stroke,
                       const std::vector<Point> &points)
        : stroke(stroke), points(points)
    {
    }

    void Polyline::draw(PNGImage &img) const
    {
        for (size_t i = 0; i < points.size() - 1; i++)
        {
            img.draw_line(points[i], points[i + 1], stroke);
        }
    }

    Line::Line(const Color &stroke,
               const Point &start,
               const Point &end)
        : stroke(stroke), start(start), end(end)
    {
    }

    void Line::draw(PNGImage &img) const
    {
        img.draw_line(start, end, stroke);
    }

    Polygon::Polygon(const Color &fill,
                     const std::vector<Point> &points)
        : fill(fill), points(points)
    {
    }

    void Polygon::draw(PNGImage &img) const
    {
        img.draw_polygon(points, fill);
    }

    Rect::Rect(const Color &fill,
               const Point &top_left,
               const Point &top_right,
               const Point &bottom_right,
               const Point &bottom_left)
        : fill(fill), top_left(top_left), top_right(top_right), bottom_right(bottom_right), bottom_left(bottom_left)
    {
    }

    void Rect::draw(PNGImage &img) const
    {
        std ::vector<Point> points;
        points.push_back(top_left);
        points.push_back(top_right);
        points.push_back(bottom_right);
        points.push_back(bottom_left);

        img.draw_polygon(points, fill);
    }

    GroupElement::GroupElement(const std::vector<SVGElement *> &elements)
        : elements(elements)
    {
    }


}

