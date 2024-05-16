
#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace svg
{
    // auxiliary functions to make the code cleaner
    void circle(XMLElement *elem, vector<SVGElement *> &svg_elements, double translate_x = 0.0, double translate_y = 0.0, int degrees = 0, int scale = 0) {
        Color fill = parse_color(elem->Attribute("fill"));
        double cx = elem->DoubleAttribute("cx");
        double cy = elem->DoubleAttribute("cy");
        double r = elem->DoubleAttribute("r");

        const char* transform_attr = elem->Attribute("transform");
        const char* transform_origin_attr = elem->Attribute("transform-origin");

        Point p;
        p.x = cx;
        p.y = cy;

        if (transform_attr != nullptr) {
        const char* translate_str = strstr(transform_attr, "translate");
        const char* rotate_str = strstr(transform_attr, "rotate");
        const char* scale_str = strstr(transform_attr, "scale");
        if (translate_str != nullptr) {
            if (sscanf(translate_str, "translate(%lf %lf)", &translate_x, &translate_y) == 2) {
                p.x += translate_x;
                p.y += translate_y;
        }}
        else if(rotate_str != nullptr){
            if(sscanf(rotate_str, "rotate(%lf)", &degrees) == 1){
                if(transform_origin_attr != nullptr){
                    Point origin;
                    sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                    p = p.rotate(origin, degrees);
                }
                else{
                    Point origin;
                    origin.x = 0;
                    origin.y = 0;
                    p = p.rotate(origin, degrees);}
            }
        }
        else if(scale_str != nullptr) {
            if(sscanf(scale_str, "scale(%d)", &scale) == 1) {
                if(transform_origin_attr != nullptr) {
                    Point origin;
                    sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                    p = p.scale(origin, scale);
                    r = r*scale;
                }
                else {
                    Point origin;
                    origin.x = 0;
                    origin.y = 0;
                    p = p.scale(origin, scale);
                    r = r*scale;
                }
            }
        }
        }

        svg_elements.push_back(new Circle(fill, p, r));
    }
    void ellipse(XMLElement *elem, vector<SVGElement *> &svg_elements) {
        double cx = elem->DoubleAttribute("cx");
        double cy = elem->DoubleAttribute("cy");
        double rx = elem->DoubleAttribute("rx");
        double ry = elem->DoubleAttribute("ry");
        Color fill = parse_color(elem->Attribute("fill"));
        double translate_x = 0.0, translate_y = 0.0;
    
        const char* transform_attr = elem->Attribute("transform");
        const char* transform_origin_attr = elem->Attribute("transform-origin");
        Point p;
        p.x = cx;
        p.y = cy;
        Point r;
        r.x = rx;
        r.y = ry;

        if (transform_attr != nullptr) {
        const char* translate_str = strstr(transform_attr, "translate");
        const char* scale_str = strstr(transform_attr, "scale");
        
        if (translate_str != nullptr) {
            if (sscanf(translate_str, "translate(%lf %lf)", &translate_x, &translate_y) == 2) {
                p.x += translate_x;
                p.y += translate_y;
        }}
        else if(scale_str != nullptr){
            int scale = 0;
            if(sscanf(scale_str, "scale(%d)", &scale) == 1){
                if(transform_origin_attr != nullptr){
                    Point origin;
                    sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                    p = p.scale(origin, scale);
                    r.x = r.x * scale;
                    r.y = r.y * scale;
                }
                else{
                    Point origin;
                    origin.x = 0;
                    origin.y = 0;
                    p = p.scale(origin, scale);
                    r.x = r.x * scale;
                    r.y = r.y * scale;}

        }
        }}


        svg_elements.push_back(new Ellipse(fill, p, r));
    }
    void line(XMLElement *elem, vector<SVGElement *> &svg_elements) {
        Color fill = parse_color(elem->Attribute("stroke"));
        double x1 = elem->DoubleAttribute("x1");
        double y1 = elem->DoubleAttribute("y1");
        double x2 = elem->DoubleAttribute("x2");
        double y2 = elem->DoubleAttribute("y2");
        double translate_x1 = 0.0, translate_y1 = 0.0;
        int degrees = 0;
        const char* transform_attr = elem->Attribute("transform");
        const char* transform_origin_attr = elem->Attribute("transform-origin");
        Point p1;
        p1.x = x1;
        p1.y = y1;
        Point p2;
        p2.x = x2;
        p2.y = y2;

        if (transform_attr != nullptr) {
        const char* translate_str = strstr(transform_attr, "translate");
        const char* rotate_str = strstr(transform_attr, "rotate");
        const char* scale_str = strstr(transform_attr, "scale");
        if (translate_str != nullptr) {
            if (sscanf(translate_str, "translate(%lf %lf)", &translate_x1, &translate_y1) == 2) {
                p1.x += translate_x1;
                p1.y += translate_y1;
                p2.x += translate_x1;
                p2.y += translate_y1;
        }}
        else if(rotate_str != nullptr){
            if(sscanf(rotate_str, "rotate(%d)", &degrees) == 1){
                if(transform_origin_attr != nullptr){
                    Point origin;
                    sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                    p1 = p1.rotate(origin, degrees);
                    p2 = p2.rotate(origin, degrees);
                }
                else{
                    Point origin;
                    origin.x = 0;
                    origin.y = 0;
                    p1 = p1.rotate(origin, degrees);
                    p2 = p2.rotate(origin, degrees);}
            }
        }
        else if(scale_str != nullptr){
            int scale = 0;
            if(sscanf(scale_str, "scale(%d)", &scale) == 1){
                if(transform_origin_attr != nullptr){
                    Point origin;
                    sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                    p1 = p1.scale(origin, scale);
                    p2 = p2.scale(origin, scale);
                }
                else{
                    Point origin;
                    origin.x = 0;
                    origin.y = 0;
                    p1 = p1.scale(origin, scale);
                    p2 = p2.scale(origin, scale);}
            }
        }
        }
        else{
            p1.x = x1;
            p1.y = y1;
            p2.x = x2;
            p2.y = y2;
        }

        svg_elements.push_back(new Line(fill, p1, p2));
    }
    void polyline(XMLElement *elem, vector<SVGElement *> &svg_elements) {
        Color fill = parse_color(elem->Attribute("stroke"));
        vector<Point> points;
        const char *points_str = elem->Attribute("points");
        char *point_str = strtok((char *)points_str, " ");
        while (point_str)
        {
            Point p;
            double translate_x = 0.0, translate_y = 0.0;
            int degrees = 0;
            const char* transform_attr = elem->Attribute("transform");
            const char* transform_origin_attr = elem->Attribute("transform-origin");

            if (transform_attr != nullptr) {
            const char* translate_str = strstr(transform_attr, "translate");
            const char* rotate_str = strstr(transform_attr, "rotate");
            const char* scale_str = strstr(transform_attr, "scale");

            if (translate_str != nullptr) {
                if (sscanf(translate_str, "translate(%lf %lf)", &translate_x, &translate_y) == 2) {
                    sscanf(point_str, "%d,%d", &p.x, &p.y);
                    point_str = strtok(NULL, " ");
                    p.x += translate_x;
                    p.y += translate_y;
                    points.push_back(p);
            }}
            else if(rotate_str != nullptr){
                if(sscanf(rotate_str, "rotate(%d)", &degrees) == 1){
                    if(transform_origin_attr != nullptr){
                        sscanf(point_str, "%d,%d", &p.x, &p.y);
                        point_str = strtok(NULL, " ");
                        Point origin;
                        sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                        p = p.rotate(origin, degrees);
                        points.push_back(p);
                    }
                    else{
                        sscanf(point_str, "%d,%d", &p.x, &p.y);
                        point_str = strtok(NULL, " ");
                        Point origin;
                        origin.x = 0;
                        origin.y = 0;
                        p = p.rotate(origin, degrees);
                        points.push_back(p);}
                }
            }
            else if(scale_str != nullptr){
                int scale = 0;
                if(sscanf(scale_str, "scale(%d)", &scale) == 1){
                    if(transform_origin_attr != nullptr){
                        sscanf(point_str, "%d,%d", &p.x, &p.y);
                        point_str = strtok(NULL, " ");
                        Point origin;
                        sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                        p = p.scale(origin, scale);
                        points.push_back(p);
                    }
                    else{
                        sscanf(point_str, "%d,%d", &p.x, &p.y);
                        point_str = strtok(NULL, " ");
                        Point origin;
                        origin.x = 0;
                        origin.y = 0;
                        p = p.scale(origin, scale);
                        points.push_back(p);
                        }}}
            }
            else{
                sscanf(point_str, "%d,%d", &p.x, &p.y);
                points.push_back(p);
                point_str = strtok(NULL, " ");}
        }
        
        svg_elements.push_back(new Polyline(fill, points));
    }
    void polygon(XMLElement *elem, vector<SVGElement *> &svg_elements) {
        Color fill = parse_color(elem->Attribute("fill"));
        vector<Point> points;
        const char *points_str = elem->Attribute("points");
        char *point_str = strtok((char *)points_str, " ");
        while (point_str)
        {
            Point p;
            double translate_x = 0.0, translate_y = 0.0;
            int degrees = 0;
            const char* transform_attr = elem->Attribute("transform");
            const char* transform_origin_attr = elem->Attribute("transform-origin");
    
            if (transform_attr != nullptr) {
            const char* translate_str = strstr(transform_attr, "translate");
            const char* rotate_str = strstr(transform_attr, "rotate");
            const char* scale_str = strstr(transform_attr, "scale");
            if (translate_str != nullptr) {
                if (sscanf(translate_str, "translate(%lf %lf)", &translate_x, &translate_y) == 2) {
                    sscanf(point_str, "%d,%d", &p.x, &p.y);
                    point_str = strtok(NULL, " ");
                    p.x += translate_x;
                    p.y += translate_y;
                    points.push_back(p);
                
            }}
            else if(rotate_str != nullptr){
                if(sscanf(rotate_str, "rotate(%d)", &degrees) == 1){
                    if(transform_origin_attr != nullptr){
                        sscanf(point_str, "%d,%d", &p.x, &p.y);
                        point_str = strtok(NULL, " ");
                        Point origin;
                        sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                        p = p.rotate(origin, degrees);
                        points.push_back(p);
                    }
                    else{
                        sscanf(point_str, "%d,%d", &p.x, &p.y);
                        point_str = strtok(NULL, " ");
                        Point origin;
                        origin.x = 0;
                        origin.y = 0;
                        p = p.rotate(origin, degrees);
                        points.push_back(p);}
                }
            }
            else if(scale_str != nullptr){
                int scale = 0;
                if(sscanf(scale_str, "scale(%d)", &scale) == 1){
                    if(transform_origin_attr != nullptr){
                        sscanf(point_str, "%d,%d", &p.x, &p.y);
                        point_str = strtok(NULL, " ");
                        Point origin;
                        sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                        p = p.scale(origin, scale);
                        points.push_back(p);
                    }
                    else{
                        sscanf(point_str, "%d,%d", &p.x, &p.y);
                        point_str = strtok(NULL, " ");
                        Point origin;
                        origin.x = 0;
                        origin.y = 0;
                        p = p.scale(origin, scale);
                        points.push_back(p);
                        }}}
            }
            else{
                sscanf(point_str, "%d,%d", &p.x, &p.y);
                points.push_back(p);
                point_str = strtok(NULL, " ");}
        }
        svg_elements.push_back(new Polygon(fill, points));
    }
    void rect(XMLElement *elem, vector<SVGElement *> &svg_elements) {
        Color fill = parse_color(elem->Attribute("fill"));
        double x = elem->DoubleAttribute("x");
        double y = elem->DoubleAttribute("y");
        double width = elem->DoubleAttribute("width");
        double height = elem->DoubleAttribute("height");
        double translate_x = 0.0, translate_y = 0.0;
        int degrees = 0;
        const char* transform_attr = elem->Attribute("transform");
        const char* transform_origin_attr = elem->Attribute("transform-origin");
        Point t_l;
        t_l.x = x;
        t_l.y = y;
        Point t_r;
        t_r.x = x + width-1;
        t_r.y = y;
        Point b_r;
        b_r.x = x + width-1;
        b_r.y = y + height-1;
        Point b_l;
        b_l.x = x;
        b_l.y = y + height-1;

        if (transform_attr != nullptr) {
        const char* translate_str = strstr(transform_attr, "translate");
        const char* rotate_str = strstr(transform_attr, "rotate");
        const char* scale_str = strstr(transform_attr, "scale");
        if (translate_str != nullptr) {
            if (sscanf(translate_str, "translate(%lf %lf)", &translate_x, &translate_y) == 2) {
                t_l.x += translate_x;
                t_l.y += translate_y; 
                t_r.x += translate_x;
                t_r.y += translate_y;
                b_r.x += translate_x;
                b_r.y += translate_y;
                b_l.x += translate_x;
                b_l.y += translate_y;
        }
        else if (sscanf(translate_str, "translate(%lf,%lf)", &translate_x, &translate_y) == 2) {
                t_l.x += translate_x;
                t_l.y += translate_y; 
                t_r.x += translate_x;
                t_r.y += translate_y;
                b_r.x += translate_x;
                b_r.y += translate_y;
                b_l.x += translate_x;
                b_l.y += translate_y;
        }}
        else if(rotate_str != nullptr){
            if(sscanf(rotate_str, "rotate(%d)", &degrees) == 1){
                if(transform_origin_attr != nullptr){
                    Point origin;
                    sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                    
                    t_l = t_l.rotate(origin, degrees);
                    t_r = t_r.rotate(origin, degrees);
                    b_r = b_r.rotate(origin, degrees);
                    b_l = b_l.rotate(origin, degrees);
                    
                }
                else{
                    Point origin;
                    origin.x = 0;
                    origin.y = 0;
                    
                    t_l = t_l.rotate(origin, degrees);
                    t_r = t_r.rotate(origin, degrees);
                    b_r = b_r.rotate(origin, degrees);
                    b_l = b_l.rotate(origin, degrees);
                    }}}
        else if(scale_str != nullptr){
            int scale = 0;
            if(sscanf(scale_str, "scale(%d)", &scale) == 1){
                if(transform_origin_attr != nullptr){
                    Point origin;
                    sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                    
                    t_l = t_l.scale(origin, scale);
                    t_r = t_r.scale(origin, scale);
                    b_r = b_r.scale(origin, scale);
                    b_l = b_l.scale(origin, scale);
                    
                }
                else{
                    Point origin;
                    origin.x = 0;
                    origin.y = 0;
                    
                    t_l = t_l.scale(origin, scale);
                    t_r = t_r.scale(origin, scale);
                    b_r = b_r.scale(origin, scale);
                    b_l = b_l.scale(origin, scale);
                    }}}}

        svg_elements.push_back(new Rect(fill, t_l, t_r,b_r,b_l));
    }
            

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

        if (strcmp(elem_name, "g") == 0)
        {
            double translate_x = 0.0, translate_y = 0.0;
            double degrees = 0;
            int scale = 0;
            const char* transform_attr = elem->Attribute("transform");
            const char* transform_origin_attr = elem->Attribute("transform-origin");

            // ler os atributos do transform, guardar e dps aplicar em cada elemento

            elem = elem->NextSiblingElement();
        }

        if (strcmp(elem_name, "circle") == 0)
        {
            circle(elem, svg_elements);
        }
        
        else if (strcmp(elem_name, "ellipse") == 0)
        {
            ellipse(elem, svg_elements);
        }

        else if (strcmp(elem_name, "line") == 0)
        {
            line(elem, svg_elements);
        }

        else if (strcmp(elem_name, "polyline") == 0)
        {
            polyline(elem, svg_elements);
        }

        else if (strcmp(elem_name, "polygon") == 0)
        {
            polygon(elem, svg_elements);
        }

        else if(strcmp(elem_name, "rect") == 0)
        {
            rect(elem, svg_elements);
        }

        elem = elem->NextSiblingElement();
    }
    }
}