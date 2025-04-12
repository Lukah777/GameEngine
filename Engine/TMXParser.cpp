#include "TMXParser.h"
#include "tinyxml2.h"
#include "Graphics.h"
#include "Image.h"
#include "System.h"
#include <sstream>

void Engine::TMXParser::RunParser(System*, std::string file)
{
    tinyxml2::XMLDocument doc;

#if NDEBUG
    doc.Parse(file.c_str(), file.size());
#else
    doc.LoadFile(file.c_str());
#endif

    std::stringstream ss;

    tinyxml2::XMLElement* elementTag = doc.FirstChildElement("map");
    ss << elementTag->Attribute("width") << " ";
    ss << elementTag->Attribute("height") << " ";
    ss << elementTag->Attribute("tilewidth") << " ";
    ss << elementTag->Attribute("tileheight") << " ";

    ss >> m_width >> m_height >> m_tileWidth >> m_tileHeight;

    tinyxml2::XMLElement* entryTag = elementTag->FirstChildElement("tileset");
    std::string imgFile = entryTag->Attribute("source");
    size_t sourcePos = imgFile.find("/");
    size_t tsxPos = imgFile.find(".tsx");
    std::string source = imgFile.substr(sourcePos + 1, tsxPos - (sourcePos + 1));
    source = source + ".png";

    entryTag = elementTag->FirstChildElement("layer");

    std::string data = entryTag->FirstChildElement("data")->GetText();

    size_t start = 0;
    size_t comma = data.find(",");
    m_backgroundVect.emplace_back(stoi(data.substr(start, (comma - start))));
    for (int i = 0; i < m_height; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            start = comma +1;
            comma = data.find(",", start);
            m_backgroundVect.emplace_back(stoi(data.substr(start, (comma - start))));
        }
    }
}
