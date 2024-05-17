//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"

namespace svg
{
    class SVGElement
    {

    public:
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;
    
    };

    // Declaration of namespace functions
    // readSVG -> implement it in readSVG.cpp
    // convert -> already given (DO NOT CHANGE) in convert.cpp

    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    class Ellipse : public SVGElement
    {
    public:
        Ellipse(const Color &fill, const Point &center, const Point &radius);
        void draw(PNGImage &img) const override;

    private:
        Color fill;
        Point center;
        Point radius;
    };

    // new classes


/************************************************************
* Circle:
* (Write what does the class function Circle do?)
* @param fill (Description...)
* @param center (Description...)
* @param radius (Description...)
************************************************************/

    class Circle : public SVGElement
    {
    public:
        Circle(const Color &fill, const Point &center, const double &radius);
        void draw(PNGImage &img) const override;
        

    private:
        Color fill;
        Point center;
        double radius;
    };


/************************************************************
* Pylyline:
* (Write what does the class function Polyline do?)
* @param stroke (Description...)
* @param points (Description...)
************************************************************/

    class Polyline : public SVGElement
    {
    public:
        Polyline(const Color &stroke, const std::vector<Point> &points);
        void draw(PNGImage &img) const override;

    private:
        Color stroke;
        std::vector<Point> points;
    };


/************************************************************
* Line:
* (Write what does the class function Line do?)
* @param stroke (Description...)
* @param start (Description...)
* @param end (Description...)
************************************************************/
    class Line : public SVGElement
    {
    public:
        Line(const Color &stroke, const Point &start, const Point &end);
        void draw(PNGImage &img) const override;

    private:
        Color stroke;
        Point start;
        Point end;
    };

/************************************************************
* Polygon:
* (Write what does the class function Polygon do?)
* @param fill (Description...)
* @param center (Description...)
* @param radius (Description...)
************************************************************/

    class Polygon : public SVGElement
    {
    public:
        Polygon(const Color &fill, const std::vector<Point> &points);
        void draw(PNGImage &img) const override;

    private:
        Color fill;
        std::vector<Point> points;
    };

/************************************************************
* Rect:
* (Write what does the class function Rect do?)
* @param fill (Description...)
* @param top_left (Description...)
* @param top_right (Description...)
* @param bottom_right (Description...)
* @param bottom_left (Description...)
************************************************************/

     class Rect : public SVGElement
    {
    public:
        Rect(const Color &fill, const Point &top_left, const Point &top_right,const Point &bottom_right, const Point &bottom_left);
        void draw(PNGImage &img) const override;

    private:
        Color fill;
        Point top_left;
        Point top_right;
        Point bottom_right;
        Point bottom_left;

    };

/************************************************************
* GroupElement:
* (Write what does the class function GroupElement do?)
* @param elements (Description...)
************************************************************/

     class GroupElement : public SVGElement {
        public:
            GroupElement();
             ~GroupElement() {
    
            for (auto element : elements) {
                delete element;
            }
        }

            GroupElement(const std::vector<SVGElement *> &elements);
            void draw(PNGImage &img) const override;
             void addElement(SVGElement* element);

        private:
            std::vector<SVGElement *> elements;
    };




  
}

#endif

// Caso alguma coisa dê return especificar oquê!
// exemplo:

/************************************************************
* ClassFunctionName:
* (Write what does the class function do?)
* @param parameter_1 (Description...)
* @param parameter_2 (Description...)
* ...
* @param parameter_n (Description...)
* (Description of what it returns)
************************************************************/

