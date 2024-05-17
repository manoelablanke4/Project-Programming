
#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace svg
{
//     void readGroup(XMLElement* group_elem, GroupElement* group) {
//     XMLElement* child = group_elem->FirstChildElement();
//     while (child) {
//         printf("Found a child\n");
//         const char* elem_name = child->Name();
//         if (strcmp(elem_name, "g") == 0) {
//             printf("Found a nested group\n");
//             std::vector<SVGElement*> elements;
//             GroupElement* nested_group = new GroupElement(elements);
//             readGroup(child, nested_group);
//             group->addElement(nested_group);
//         } else {
//         if (strcmp(elem_name, "circle") == 0)
//         {
//             printf("Found a circle\n");
//             Color fill = parse_color(group_elem->Attribute("fill"));
//             double cx = child->DoubleAttribute("cx");
//             double cy = child->DoubleAttribute("cy");
//             double r = child->DoubleAttribute("r");
            
//             Point p;
//             p.x = cx;
//             p.y = cy;

            
    
//             group->addElement(new Circle(fill, p, r));
//     }
//             else if (strcmp(elem_name, "polyline") == 0){
//             Color fill = parse_color(group_elem->Attribute("stroke"));
//             vector<Point> points;
//             const char *points_str = group_elem->Attribute("points");
//             char *point_str = strtok((char *)points_str, " ");
//             while (point_str)
//             {
//                 Point p;
//                  double translate_x = 0.0, translate_y = 0.0;
//                  int degrees = 0;
//             const char* transform_attr = group_elem->Attribute("transform");
//             const char* transform_origin_attr = group_elem->Attribute("transform-origin");
    
//             if (transform_attr != nullptr) {
//             const char* translate_str = strstr(transform_attr, "translate");
//             const char* rotate_str = strstr(transform_attr, "rotate");
//             const char* scale_str = strstr(transform_attr, "scale");

//             if (translate_str != nullptr) {
//                 if (sscanf(translate_str, "translate(%lf %lf)", &translate_x, &translate_y) == 2) {
//                     sscanf(point_str, "%d,%d", &p.x, &p.y);
//                     point_str = strtok(NULL, " ");
//                     p.x += translate_x;
//                     p.y += translate_y;
//                     points.push_back(p);
//             }}
//             else if(rotate_str != nullptr){
//                 if(sscanf(rotate_str, "rotate(%d)", &degrees) == 1){
//                     if(transform_origin_attr != nullptr){
//                         sscanf(point_str, "%d,%d", &p.x, &p.y);
//                         point_str = strtok(NULL, " ");
//                         Point origin;
//                         sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
//                         p = p.rotate(origin, degrees);
//                         points.push_back(p);
//                     }
//                     else{
//                         sscanf(point_str, "%d,%d", &p.x, &p.y);
//                         point_str = strtok(NULL, " ");
//                         Point origin;
//                         origin.x = 0;
//                         origin.y = 0;
//                         p = p.rotate(origin, degrees);
//                         points.push_back(p);}
//                 }
//             }
//             else if(scale_str != nullptr){
//                 int scale = 0;
//                 if(sscanf(scale_str, "scale(%d)", &scale) == 1){
//                     if(transform_origin_attr != nullptr){
//                         sscanf(point_str, "%d,%d", &p.x, &p.y);
//                         point_str = strtok(NULL, " ");
//                         Point origin;
//                         sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
//                         p = p.scale(origin, scale);
//                         points.push_back(p);
//                     }
//                     else{
//                         sscanf(point_str, "%d,%d", &p.x, &p.y);
//                         point_str = strtok(NULL, " ");
//                         Point origin;
//                         origin.x = 0;
//                         origin.y = 0;
//                         p = p.scale(origin, scale);
//                         points.push_back(p);
//                         }}}
//             }
//             else{
//                 sscanf(point_str, "%d,%d", &p.x, &p.y);
//                 points.push_back(p);
//                 point_str = strtok(NULL, " ");}
//             }
           
//         group->addElement(new Polyline(fill, points));
//         }

//         }

//         child = child->NextSiblingElement();
//     }
// }

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
        
        //! Current SVG element read from the XML document 
        XMLElement *elem = xml_elem->FirstChildElement();
        //! Loop through all the elements in the XML document
        while (elem)
    {
        //! Name of the current element
        const char *elem_name = elem->Name();

        //! If the element is a circle
        if (strcmp(elem_name, "circle") == 0)
        {
            //! Get the color of the circle
            Color fill = parse_color(elem->Attribute("fill"));
            //! Get the X coordinate of the center of the circle
            double cx = elem->DoubleAttribute("cx");
            //! Get the Y coordinate of the center of the circle
            double cy = elem->DoubleAttribute("cy");
            //! Get the radius of the circle
            double r = elem->DoubleAttribute("r");
            //! Get the translation values
            double translate_x = 0.0, translate_y = 0.0;
            //! Get the rotation values
            double degrees = 0;
            //! Get the scale value
            int scale = 0;
            //! Get the transform attribute
            const char* transform_attr = elem->Attribute("transform");
            //! Get the transform-origin attribute
            const char* transform_origin_attr = elem->Attribute("transform-origin");

            //! A point for the center of the circle
            Point p;
            //! Set the X coordinate of the center of the circle
            p.x = cx;
            //! Set the Y coordinate of the center of the circle
            p.y = cy;

            //! Check if there is a transform attribute
            if (transform_attr != nullptr) {
                //! Get the transform attribute
                const char* translate_str = strstr(transform_attr, "translate");
                const char* rotate_str = strstr(transform_attr, "rotate");
                const char* scale_str = strstr(transform_attr, "scale");
                //! Check if there is a translate attribute
                if (translate_str != nullptr) {
                    if (sscanf(translate_str, "translate(%lf %lf)", &translate_x, &translate_y) == 2) {
                        //! Translate the X coordinate of the center of the circle
                        p.x += translate_x;
                        //! Translate the Y coordinate of the center of the circle
                        p.y += translate_y;
                }}

                //! Check if there is a rotate attribute                
                else if(rotate_str != nullptr){
                    if(sscanf(rotate_str, "rotate(%lf)", &degrees) == 1){
                        //! Check if there is a transform-origin attribute
                        if(transform_origin_attr != nullptr){
                            //! Get the origin of the rotation
                            Point origin;
                            sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                            //! Rotate the center of the circle
                            p = p.rotate(origin, degrees);
                        }
                        else {
                            //! Rotate the center of the circle
                            Point origin;
                            origin.x = 0;
                            origin.y = 0;
                            p = p.rotate(origin, degrees);
                        }
                    }
                }
                //! Check if there is a scale attribute
                else if(scale_str != nullptr){
                    if(sscanf(scale_str, "scale(%d)", &scale) == 1){
                        //! Check if there is a transform-origin attribute
                        if(transform_origin_attr != nullptr){
                            //! Get the origin of the scale
                            Point origin;
                            sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                            //! Scale the center of the circle
                            p = p.scale(origin, scale);
                            //! Scale the radius of the circle
                            r = r*scale;
                        }
                        else{
                            Point origin;
                            origin.x = 0;
                            origin.y = 0;
                            //! Scale the center of the circle
                            p = p.scale(origin, scale);
                            //! Scale the radius of the circle
                            r = r*scale;}

                    }
                }
            }

            //! Add the circle to the vector of SVG elements
            svg_elements.push_back(new Circle(fill, p, r));
    }
        //! If the element is an ellipse
        else if (strcmp(elem_name, "ellipse") == 0)
        {
            //! Get the X coordinate of the center of the ellipse
            double cx = elem->DoubleAttribute("cx");
            //! Get the Y coordinate of the center of the ellipse
            double cy = elem->DoubleAttribute("cy");
            //! Get the X radius of the ellipse
            double rx = elem->DoubleAttribute("rx");
            //! Get the Y radius of the ellipse
            double ry = elem->DoubleAttribute("ry");
            //! Get the color of the ellipse
            Color fill = parse_color(elem->Attribute("fill"));
            //! Get the translation values
            double translate_x = 0.0, translate_y = 0.0;
            //! Get the transform attribute
            const char* transform_attr = elem->Attribute("transform");
            const char* transform_origin_attr = elem->Attribute("transform-origin");

            //! A point for the center of the ellipse
            Point p;
            //! Set the X coordinate of the center of the ellipse
            p.x = cx;
            //! Set the Y coordinate of the center of the ellipse
            p.y = cy;

            //! A point for the radii of the ellipse
            Point r;
            //! Set the X radius of the ellipse
            r.x = rx;
            //! Set the Y radius of the ellipse
            r.y = ry;
    
            //! Check if there is a transform attribute
            if (transform_attr != nullptr) {
                //! Get the transform attribute
                const char* translate_str = strstr(transform_attr, "translate");
                const char* scale_str = strstr(transform_attr, "scale");
            
                //! Check if there is a translate attribute
                if (translate_str != nullptr) {
                    if (sscanf(translate_str, "translate(%lf %lf)", &translate_x, &translate_y) == 2) {
                        //! Translate the X coordinate of the center of the ellipse
                        p.x += translate_x;
                        //! Translate the Y coordinate of the center of the ellipse
                        p.y += translate_y;
                }}
                //! Check if there is a scale attribute                
                else if(scale_str != nullptr){
                    int scale = 0;
                    if(sscanf(scale_str, "scale(%d)", &scale) == 1){
                        //! Check if there is a transform-origin attribute
                        if(transform_origin_attr != nullptr){
                            Point origin;
                            sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                            //! Scale the center of the ellipse with the origin
                            p = p.scale(origin, scale);
                            //! Scale the X radius of the ellipse
                            r.x = r.x * scale;
                            //! Scale the Y radius of the ellipse
                            r.y = r.y * scale;
                        }
                        else{
                            Point origin;
                            origin.x = 0;
                            origin.y = 0;
                            //! Scale the center of the ellipse
                            p = p.scale(origin, scale);
                            //! Scale the X radius of the ellipse
                            r.x = r.x * scale;
                            //! Scale the Y radius of the ellipse
                            r.y = r.y * scale;}

                }
                }
            }

            //! Add the ellipse to the vector of SVG elements
            svg_elements.push_back(new Ellipse(fill, p, r));
        }

        //! If the element is a line
        else if (strcmp(elem_name, "line") == 0){
            //! Get the color of the line
            Color fill = parse_color(elem->Attribute("stroke"));
            //! Get the X coordinate of the start of the line
            double x1 = elem->DoubleAttribute("x1");
            //! Get the Y coordinate of the start of the line
            double y1 = elem->DoubleAttribute("y1");
            //! Get the X coordinate of the end of the line
            double x2 = elem->DoubleAttribute("x2");
            //! Get the Y coordinate of the end of the line
            double y2 = elem->DoubleAttribute("y2");
            //! Get the translation values
            double translate_x1 = 0.0, translate_y1 = 0.0;
            //! Get the rotation values
            int degrees = 0;

            //! Get the transform attribute
            const char* transform_attr = elem->Attribute("transform");
            const char* transform_origin_attr = elem->Attribute("transform-origin");
            
            //! A point for the start of the line
            Point p1;
            //! Set the X coordinate of the start of the line
            p1.x = x1;
            //! Set the Y coordinate of the start of the line
            p1.y = y1;

            //! A point for the end of the line
            Point p2;
            //! Set the X coordinate of the end of the line
            p2.x = x2;
            //! Set the Y coordinate of the end of the line
            p2.y = y2;
    
            //! Check if there is a transform attribute
            if (transform_attr != nullptr) {
                //! Get the transform attribute
                const char* translate_str = strstr(transform_attr, "translate");
                const char* rotate_str = strstr(transform_attr, "rotate");
                const char* scale_str = strstr(transform_attr, "scale");
                //! Check if there is a translate attribute
                if (translate_str != nullptr) {
                    if (sscanf(translate_str, "translate(%lf %lf)", &translate_x1, &translate_y1) == 2) {
                        //! Translate the X coordinate of the start of the line
                        p1.x += translate_x1;
                        //! Translate the Y coordinate of the start of the line
                        p1.y += translate_y1;
                        //! Translate the X coordinate of the end of the line
                        p2.x += translate_x1;
                        //! Translate the Y coordinate of the end of the line
                        p2.y += translate_y1;
                }}
                //! Check if there is a rotate attribute                
                else if(rotate_str != nullptr){
                    if(sscanf(rotate_str, "rotate(%d)", &degrees) == 1){
                        if(transform_origin_attr != nullptr){
                            Point origin;
                            sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                            //! Rotate the start of the line with the origin
                            p1 = p1.rotate(origin, degrees);
                            //! Rotate the end of the line with the origin
                            p2 = p2.rotate(origin, degrees);
                        }
                        else{
                            Point origin;
                            origin.x = 0;
                            origin.y = 0;
                            //! Rotate the start of the line
                            p1 = p1.rotate(origin, degrees);
                            //! Rotate the end of the line
                            p2 = p2.rotate(origin, degrees);}
                    }
                }
                //! Check if there is a scale attribute                
                else if(scale_str != nullptr){
                    int scale = 0;
                    if(sscanf(scale_str, "scale(%d)", &scale) == 1){
                        if(transform_origin_attr != nullptr){
                            Point origin;
                            sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                            //! Scale the start of the line with the origin
                            p1 = p1.scale(origin, scale);
                            //! Scale the end of the line with the origin
                            p2 = p2.scale(origin, scale);
                        }
                        else {
                            Point origin;
                            origin.x = 0;
                            origin.y = 0;
                            //! Scale the start of the line
                            p1 = p1.scale(origin, scale);
                            //! Scale the end of the line
                            p2 = p2.scale(origin, scale);
                        }
                    }
                }
            }
            //! If there is no transform attribute
            else {
                //! Set the X coordinate of the start of the line
                p1.x = x1;
                //! Set the Y coordinate of the start of the line
                p1.y = y1;
                //! Set the X coordinate of the end of the line
                p2.x = x2;
                //! Set the Y coordinate of the end of the line
                p2.y = y2;
            }
            
            //! Add the line to the vector of SVG elements
            svg_elements.push_back(new Line(fill, p1, p2));
        }

        //! If the element is a polyline
        else if (strcmp(elem_name, "polyline") == 0){
            //! Get the color of the polyline
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
           
            //! Add the polyline to the vector of SVG elements
            svg_elements.push_back(new Polyline(fill, points));
        }

        //! If the element is a polygon
        else if (strcmp(elem_name, "polygon") == 0){
            Color fill = parse_color(elem->Attribute("fill"));
            //! Vector of points for the polygon
            vector<Point> points;
            //! Get the points of the polygon
            const char *points_str = elem->Attribute("points");
            //! Tokenize the points string
            char *point_str = strtok((char *)points_str, " ");
            //! Loop through all the points
            while (point_str)
            {
                //! Point for the polygon
                Point p;
                //! Get the translation values
                double translate_x = 0.0, translate_y = 0.0;
                //! Get the rotation values
                int degrees = 0;
                //! Get the transform attribute
                const char* transform_attr = elem->Attribute("transform");
                const char* transform_origin_attr = elem->Attribute("transform-origin");
        
                //! Check if there is a transform attribute
                if (transform_attr != nullptr) {
                    //! Get the transform attribute
                    const char* translate_str = strstr(transform_attr, "translate");
                    const char* rotate_str = strstr(transform_attr, "rotate");
                    const char* scale_str = strstr(transform_attr, "scale");
                    //! Check if there is a translate attribute
                    if (translate_str != nullptr) {
                        if (sscanf(translate_str, "translate(%lf %lf)", &translate_x, &translate_y) == 2) {
                            sscanf(point_str, "%d,%d", &p.x, &p.y);
                            point_str = strtok(NULL, " ");
                            //! Translate the X coordinate of the point
                            p.x += translate_x;
                            //! Translate the Y coordinate of the point
                            p.y += translate_y;
                            //! Add the point to the vector of points
                            points.push_back(p);
                    }}

                    //! Check if there is a rotate attribute
                    else if(rotate_str != nullptr){
                        if(sscanf(rotate_str, "rotate(%d)", &degrees) == 1){
                            if(transform_origin_attr != nullptr){
                                sscanf(point_str, "%d,%d", &p.x, &p.y);
                                point_str = strtok(NULL, " ");
                                Point origin;
                                sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                                //! Rotate the point with the origin
                                p = p.rotate(origin, degrees);
                                //! Add the point to the vector of points
                                points.push_back(p);
                            }
                            else{
                                sscanf(point_str, "%d,%d", &p.x, &p.y);
                                point_str = strtok(NULL, " ");
                                Point origin;
                                origin.x = 0;
                                origin.y = 0;
                                //! Rotate the point
                                p = p.rotate(origin, degrees);
                                //! Add the point to the vector of points
                                points.push_back(p);}
                        }
                    }

                    //! Check if there is a scale attribute
                    else if(scale_str != nullptr){
                        int scale = 0;
                        if(sscanf(scale_str, "scale(%d)", &scale) == 1){
                            if(transform_origin_attr != nullptr){
                                sscanf(point_str, "%d,%d", &p.x, &p.y);
                                point_str = strtok(NULL, " ");
                                Point origin;
                                sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);
                                //! Scale the point with the origin
                                p = p.scale(origin, scale);
                                //! Add the point to the vector of points
                                points.push_back(p);
                            }
                            else{
                                sscanf(point_str, "%d,%d", &p.x, &p.y);
                                point_str = strtok(NULL, " ");
                                Point origin;
                                origin.x = 0;
                                origin.y = 0;
                                //! Scale the point
                                p = p.scale(origin, scale);
                                //! Add the point to the vector of points
                                points.push_back(p);
                                }}}
                    }

                //! If there is no transform attribute
                else {
                    sscanf(point_str, "%d,%d", &p.x, &p.y);
                    //! Add the point to the vector of points
                    points.push_back(p);
                    point_str = strtok(NULL, " ");
                }
            }

            //! Add the polygon to the vector of SVG elements
            svg_elements.push_back(new Polygon(fill, points));
        }

        //! If the element is a rectangle
        else if(strcmp(elem_name, "rect") == 0){
            //! Get the color of the rectangle
            Color fill = parse_color(elem->Attribute("fill"));
            //! Get the X coordinate of the top left corner of the rectangle
            double x = elem->DoubleAttribute("x");
            //! Get the Y coordinate of the top left corner of the rectangle
            double y = elem->DoubleAttribute("y");
            //! Get the width of the rectangle
            double width = elem->DoubleAttribute("width");
            //! Get the height of the rectangle
            double height = elem->DoubleAttribute("height");
            //! Get the translation values
            double translate_x = 0.0, translate_y = 0.0;
            //! Get the rotation values
            int degrees = 0;
            //! Get the transform attribute
            const char* transform_attr = elem->Attribute("transform");
            const char* transform_origin_attr = elem->Attribute("transform-origin");

            //! Define the top left corner of the rectangle
            Point t_l;
            t_l.x = x;
            t_l.y = y;

            //! Define the top right corner of the rectangle
            Point t_r;
            t_r.x = x + width-1;
            t_r.y = y;

            //! Define the bottom right corner of the rectangle
            Point b_r;
            b_r.x = x + width-1;
            b_r.y = y + height-1;

            //! Define the bottom left corner of the rectangle
            Point b_l;
            b_l.x = x;
            b_l.y = y + height-1;

            //! Check if there is a transform attribute
            if (transform_attr != nullptr) {
                //! Get the transform attribute
                const char* translate_str = strstr(transform_attr, "translate");
                const char* rotate_str = strstr(transform_attr, "rotate");
                const char* scale_str = strstr(transform_attr, "scale");
                //! Check if there is a translate attribute
                if (translate_str != nullptr) {
                    if (sscanf(translate_str, "translate(%lf %lf)", &translate_x, &translate_y) == 2) {
                        //! Translate the X coordinate of the top left corner of the rectangle
                        t_l.x += translate_x;
                        //! Translate the Y coordinate of the top left corner of the rectangle
                        t_l.y += translate_y;
                        //! Translate the X coordinate of the top right corner of the rectangle 
                        t_r.x += translate_x;
                        //! Translate the Y coordinate of the top right corner of the rectangle
                        t_r.y += translate_y;
                        //! Translate the X coordinate of the bottom right corner of the rectangle
                        b_r.x += translate_x;
                        //! Translate the Y coordinate of the bottom right corner of the rectangle
                        b_r.y += translate_y;
                        //! Translate the X coordinate of the bottom left corner of the rectangle
                        b_l.x += translate_x;
                        //! Translate the Y coordinate of the bottom left corner of the rectangle
                        b_l.y += translate_y;
                }

                //! Does the samething as the previous one, but it handles the case where the translate attribute is written with a comma instead of a space
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

                //! Check if there is a rotate attribute                
                else if(rotate_str != nullptr){
                    if(sscanf(rotate_str, "rotate(%d)", &degrees) == 1){
                        //! Check if there is a transform-origin attribute
                        if(transform_origin_attr != nullptr){
                            Point origin;
                            sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);

                            //! Rotate the top left corner of the rectangle with the origin
                            t_l = t_l.rotate(origin, degrees);
                            //! Rotate the top right corner of the rectangle with the origin
                            t_r = t_r.rotate(origin, degrees);
                            //! Rotate the bottom right corner of the rectangle with the origin
                            b_r = b_r.rotate(origin, degrees);
                            //! Rotate the bottom left corner of the rectangle with the origin
                            b_l = b_l.rotate(origin, degrees);
                        
                        }
                        else{
                            Point origin;
                            origin.x = 0;
                            origin.y = 0;
                            //! Rotate the top left corner of the rectangle
                            t_l = t_l.rotate(origin, degrees);
                            //! Rotate the top right corner of the rectangle
                            t_r = t_r.rotate(origin, degrees);
                            //! Rotate the bottom right corner of the rectangle
                            b_r = b_r.rotate(origin, degrees);
                            //! Rotate the bottom left corner of the rectangle
                            b_l = b_l.rotate(origin, degrees);
                            }}}

                //! Check if there is a scale attribute            
                else if(scale_str != nullptr){
                    int scale = 0;
                    if(sscanf(scale_str, "scale(%d)", &scale) == 1){
                        //! Check if there is a transform-origin attribute
                        if(transform_origin_attr != nullptr) {
                            Point origin;
                            sscanf(transform_origin_attr, "%d %d", &origin.x, &origin.y);

                            //! Scale the top left corner of the rectangle with the origin
                            t_l = t_l.scale(origin, scale);
                            //! Scale the top right corner of the rectangle with the origin
                            t_r = t_r.scale(origin, scale);
                            //! Scale the bottom right corner of the rectangle with the origin
                            b_r = b_r.scale(origin, scale);
                            //! Scale the bottom left corner of the rectangle with the origin
                            b_l = b_l.scale(origin, scale);
                        }

                        else{
                            Point origin;
                            origin.x = 0;
                            origin.y = 0;
                        
                            //! Scale the top left corner of the rectangle
                            t_l = t_l.scale(origin, scale);
                            //! Scale the top right corner of the rectangle
                            t_r = t_r.scale(origin, scale);
                            //! Scale the bottom right corner of the rectangle
                            b_r = b_r.scale(origin, scale);
                            //! Scale the bottom left corner of the rectangle
                            b_l = b_l.scale(origin, scale);
                            }}}
            }

            //! Add the rectangle to the vector of SVG elements
            svg_elements.push_back(new Rect(fill, t_l, t_r,b_r,b_l));
        }
        // else if(strcmp(elem_name, "g") == 0){
        //      std::vector<SVGElement *> elements;
        //      GroupElement* group = new GroupElement(elements);
        //      readGroup(elem, group);
        //      svg_elements.push_back(group);

            
        // }

        //! Move to the next element
        elem = elem->NextSiblingElement();
    }
}

}