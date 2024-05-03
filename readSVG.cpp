
#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace svg
{
    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement *>& svg_elements)
    {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");
        
        // TODO complete code -->
        
        XMLElement *elem = xml_elem->FirstChildElement();
         while (elem)
    {
        const char *elem_name = elem->Name();
        if (strcmp(elem_name, "circle") == 0)
        {
            // Parse circle attributes and create a Circle object
            double cx = elem->DoubleAttribute("cx");
            double cy = elem->DoubleAttribute("cy");
            double r = elem->DoubleAttribute("r");
            
            Color fill = parse_color(elem->Attribute("fill"));
            Point p;
            p.x = cx;
            p.y = cy;
           
            svg_elements.push_back(new Circle(fill, p, r));
        }
        else if (strcmp(elem_name, "ellipse") == 0)
        {
            // Parse circle attributes and create a Circle object
            double cx = elem->DoubleAttribute("cx");
            double cy = elem->DoubleAttribute("cy");
            double rx = elem->DoubleAttribute("rx");
            double ry = elem->DoubleAttribute("ry");
            Color fill = parse_color(elem->Attribute("fill"));
            Point p;
            p.x = cx;
            p.y = cy;
            Point r;
            r.x = rx;
            r.y = ry;
            svg_elements.push_back(new Ellipse(fill, p, r));
        }

        else if (strcmp(elem_name, "line") == 0){
            Color fill = parse_color(elem->Attribute("stroke"));
            double x1 = elem->DoubleAttribute("x1");
            double y1 = elem->DoubleAttribute("y1");
            double x2 = elem->DoubleAttribute("x2");
            double y2 = elem->DoubleAttribute("y2");
            Point p1;
            p1.x = x1;
            p1.y = y1;
            Point p2;
            p2.x = x2;
            p2.y = y2;

            svg_elements.push_back(new Line(fill, p1, p2));
        }

        else if (strcmp(elem_name, "polyline") == 0){
            Color fill = parse_color(elem->Attribute("stroke"));
            vector<Point> points;
            const char *points_str = elem->Attribute("points");
            char *point_str = strtok((char *)points_str, " ");
            while (point_str)
            {
                Point p;
                sscanf(point_str, "%d,%d", &p.x, &p.y);
                points.push_back(p);
                point_str = strtok(NULL, " ");
            }
            svg_elements.push_back(new Polyline(fill, points));
        }
        else if (strcmp(elem_name, "polygon") == 0){
            Color fill = parse_color(elem->Attribute("fill"));
            vector<Point> points;
            const char *points_str = elem->Attribute("points");
            char *point_str = strtok((char *)points_str, " ");
            while (point_str)
            {
                Point p;
                sscanf(point_str, "%d,%d", &p.x, &p.y);
                points.push_back(p);
                point_str = strtok(NULL, " ");
            }
            svg_elements.push_back(new Polygon(fill, points));
        }
        else if(strcmp(elem_name, "rect") == 0){
            Color fill = parse_color(elem->Attribute("fill"));
            double x = elem->DoubleAttribute("x");
            double y = elem->DoubleAttribute("y");
            double width = elem->DoubleAttribute("width");
            double height = elem->DoubleAttribute("height");
            Point p;
            p.x = x;
            p.y = y;
            Point d;
            d.x = p.x + width-1;
            d.y = p.y + height-1;
            svg_elements.push_back(new Rect(fill, p, d));
        
        }
         elem = elem->NextSiblingElement();
    }
}}