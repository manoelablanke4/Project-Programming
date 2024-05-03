
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

         elem = elem->NextSiblingElement();
    }
}}