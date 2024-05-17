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

    /************************************************************
    * @class Ellipse
    * 
    * @brief A class representing an ellipse in an SVG. This class inherits from SVGElements and provides funcionality to define and draw a draw an ellipse with determined fill color, center point and radius.
    ************************************************************/
    class Ellipse : public SVGElement
    {
    public:
        /************************************************************
        * @brief Constructor for Ellipse. Initializes the Ellipse object with the specified fill color, center point, and radii along the x and y axes.
        * 
        * @param fill is the color of the ellipse
        * @param center is the point where the ellipse is centered
        * @param radius is both the x and y radius of the ellipse
        ************************************************************/
        Ellipse(const Color &fill, const Point &center, const Point &radius);

        /************************************************************
        * @brief Draws the ellipse on a PNG image. This function overrides the draw method of the SVGElement class and draws the ellipse on the PNG image.
        * 
        * @param img is the PNG image where the ellipse will be drawn
        ************************************************************/
        void draw(PNGImage &img) const override;

    private:
        //! Color of the ellipse.
        Color fill;
        //! Center of the ellipse.
        Point center;
        //! Radii of the ellipse.
        Point radius;
    };

    // new classes

    /************************************************************
    * @class Circle
    * 
    * @brief A class that represents a circle in a SVG image. This class inherits from SVGElements and provides funcionality to define and draw a draw a circle with determined fill color, center point and radius.
    ************************************************************/
    class Circle : public SVGElement
    {
    public:
        /************************************************************
        * @brief Constructor for Circle. Initializes the Circle object with the specified fill color, center point, and radius.
        * 
        * @param fill is the color of the circle
        * @param center is the point where the circle is centered
        * @param radius is the radius of the circle
        ************************************************************/
        Circle(const Color &fill, const Point &center, const double &radius);

        /************************************************************
        * @brief Draws the circle on a PNG image. This function overrides the draw method of the SVGElement class and draws the circle on the PNG image.
        * 
        * @param img is the PNG image where the circle will be drawn
        ************************************************************/        
        void draw(PNGImage &img) const override;
        

    private:
        //! Color of the circle.
        Color fill;
        //! Center of the circle.
        Point center;
        //! Radius of the circle.
        double radius;
    };


    /************************************************************
    * @class Polyline
    * 
    * @brief A class that represents a polyline in a SVG image. This class inherits from SVGElements and provides funcionality to define and draw a polyline with determined stroke color and points.
    ************************************************************/
    class Polyline : public SVGElement
    {
    public:
        /************************************************************
        * @brief Constructor for Polyline. Initializes the Polyline object with the specified stroke color and points.
        * 
        * @param stroke is the color of the polyline
        * @param points is a vector of points that define the polyline
        ************************************************************/
        Polyline(const Color &stroke, const std::vector<Point> &points);

        /************************************************************
        * @brief Draws the polyline on a PNG image. This function overrides the draw method of the SVGElement class and draws the polyline on the PNG image.
        * 
        * @param img is the PNG image where the polyline will be drawn
        ************************************************************/
        void draw(PNGImage &img) const override;

    private:
        //! Color of the polyline.
        Color stroke;
        //! Points defining the polyline.
        std::vector<Point> points;
    };


    /************************************************************
    * @class Line:
    * 
    * @brief A class that represents a line in a SVG image. This class inherits from SVGElements and provides funcionality to define and draw a line with determined stroke color and points.
    ************************************************************/
    class Line : public SVGElement
    {
    public:
        /************************************************************
        * @brief Constructor for Line. Initializes the Line object with the specified stroke color and points.
        * 
        * @param stroke is the color of the line
        * @param start is the point where the line starts
        * @param end is the point where the line ends
        ************************************************************/
        Line(const Color &stroke, const Point &start, const Point &end);

        /************************************************************
        * @brief Draws the line on a PNG image. This function overrides the draw method of the SVGElement class and draws the line on the PNG image.
        * 
        * @param img is the PNG image where the line will be drawn
        ************************************************************/
        void draw(PNGImage &img) const override;

    private:
        //! Color of the line.
        Color stroke;
        //! Start point of the line.
        Point start;
        //! End point of the line.
        Point end;
    };

    /************************************************************
    * @class Polygon
    * 
    * @brief A class that represents a polygon in a SVG image. This class inherits from SVGElements and provides funcionality to define and draw a polygon with determined fill color and points.
    ************************************************************/
    class Polygon : public SVGElement
    {
    public:
        /************************************************************
        * @brief Constructor for Polygon. Initializes the Polygon object with the specified fill color and points.
        *  
        * @param fill is the color of the polygon
        * @param points is a vector of points that define the polygon
        ************************************************************/
        Polygon(const Color &fill, const std::vector<Point> &points);

        /************************************************************
        * @brief Draws the polygon on a PNG image. This function overrides the draw method of the SVGElement class and draws the polygon on the PNG image.
        *  
        * @param img is the PNG image where the polygon will be drawn
        ************************************************************/
        void draw(PNGImage &img) const override;

    private:
        //! Color of the polygon.
        Color fill;
        //! Points defining the polygon.
        std::vector<Point> points;
    };

    /************************************************************
    * @class Rect
    * 
    * @brief A class that represents a rectangle in a SVG image. This class inherits from SVGElements and provides funcionality to define and draw a rectangle with determined fill color and points.
    ************************************************************/
    class Rect : public SVGElement
    {
    public:
        /************************************************************
        * @brief Constructor for Rect. Initializes the Rect object with the specified fill color and points.
        *  
        * @param fill is the color of the rectangle
        * @param top_left is the point where the top left corner of the rectangle is
        * @param top_right is the point where the top right corner of the rectangle is
        * @param bottom_right is the point where the bottom right corner of the rectangle is
        * @param bottom_left is the point where the bottom left corner of the rectangle is
        ************************************************************/
        Rect(const Color &fill, const Point &top_left, const Point &top_right,const Point &bottom_right, const Point &bottom_left);

        /************************************************************
        * @brief Draws the rectangle on a PNG image. This function overrides the draw method of the SVGElement class and draws the rectangle on the PNG image.
        * 
        * @param img is the PNG image where the rectangle will be drawn
        ************************************************************/
        void draw(PNGImage &img) const override;

    private:
        //! Color of the rectangle.
        Color fill;
        //! Top left corner of the rectangle.
        Point top_left;
        //! Top right corner of the rectangle.
        Point top_right;
        //! Bottom right corner of the rectangle.
        Point bottom_right;
        //! Bottom left corner of the rectangle.
        Point bottom_left;

    };

    /************************************************************
    * @class GroupElement
    * 
    * @brief A class that represents a group of SVG elements in a SVG image. This class inherits from SVGElements and provides funcionality to define and draw a group of SVG elements.
    ************************************************************/
     class GroupElement : public SVGElement {
        public:
            /************************************************************
            * @brief Constructor for GroupElement. Initializes the GroupElement object with an empty vector of SVG elements.
            * 
            ************************************************************/
            GroupElement();

            /************************************************************
            * @brief Destructor for GroupElement. Deletes all the SVG elements in the group.
            *
            ************************************************************/
            ~GroupElement() {
                for (auto element : elements) {
                    delete element;
                }
            }

            /************************************************************
            * @brief Constructor for GroupElement. Initializes the GroupElement object with the specified vector of SVG elements.
            * 
            * @param elements is a vector of SVG elements that will be grouped together
            ************************************************************/
            GroupElement(const std::vector<SVGElement *> &elements);

            /************************************************************
            * @brief Draws the group of SVG elements on a PNG image. This function overrides the draw method of the SVGElement class and draws the group of SVG elements on the PNG image.
            * 
            * @param img is the PNG image where the group of SVG elements will be drawn
            ************************************************************/
            void draw(PNGImage &img) const override;

            /************************************************************
            * @brief Adds an SVG element to the group of SVG elements.
            * 
            * @param element is the SVG element that will be added to the group
            ************************************************************/
            void addElement(SVGElement* element);

        private:
            //! Vector of SVG elements that are grouped together.
            std::vector<SVGElement *> elements;
    };
  
}

#endif