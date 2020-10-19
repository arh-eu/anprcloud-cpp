#ifndef VEHICLE_H
#define VEHICLE_H
#include <string>
#include <vector>
#include "json.hpp"

struct Coord
{
    int x;
    int y;
    Coord(){}
    Coord(nlohmann::json coord)
    {
        x = coord["x"];
        y = coord["y"];
    }

};

struct Color
{
    int r;
    int g;
    int b;
    Color(){}
    Color(nlohmann::json color)
    {
        r = color["r"];
        g = color["g"];
        b = color["b"];
    }
};

struct ROI
{
    Coord topLeft;
    Coord topRight;
    Coord bottomLeft;
    Coord bottomRight;
    ROI(){}
    ROI(nlohmann::json roi)
    {
        topLeft = Coord(roi["topLeft"]);
        topRight = Coord(roi["topRight"]);
        bottomLeft = Coord(roi["bottomLeft"]);
        bottomRight = Coord(roi["bottomRight"]);
    }
};

struct PlateChar
{
    Color bgColor;
    Color color;
    ROI charROI;
    int code;
    int confidence;
    PlateChar(){}
    PlateChar(nlohmann::json plateChar)
    {
        bgColor = Color(plateChar["bgColor"]);
        color = Color(plateChar["color"]);
        charROI = ROI(plateChar["charROI"]);
        code = plateChar["code"];
        confidence = plateChar["confidence"];
    }
};

struct Plate{
    std::string text;
    std::string country;
    std::string state;
    Color bgColor;
    Color color;
    ROI plateROI;
    int confidence;
    int plateType;
    int proctime;
    std::vector<PlateChar> plateChars;

    Plate(){}
    Plate(nlohmann::json plate)
    {
        text = plate["unicodeText"];
        state = plate["state"];
        country = plate["country"];
        proctime = plate["proctime"];
        confidence = plate["confidence"];
        plateType = plate["plateType"];
        bgColor = Color(plate["bgColor"]);
        color = Color(plate["color"]);
        plateROI = ROI(plate["plateROI"]);

        auto chars = plate["plateChars"];
        for(auto plateChar : chars)
        {
            PlateChar c(plateChar);
            plateChars.push_back(c);
        }
    }
};

struct Mmr{

    std::string category;
    int categoryConfidence;
    Color color;
    int colorConfidence;
    std::string make;
    std::string model;
    std::string subModel;
    int makeAndModelConfidence;
    Mmr(){}
    Mmr(nlohmann::json mmr)
    {
        make = mmr["make"];
        model = mmr["model"];
        category = mmr["category"];
        subModel = mmr["subModel"];
        colorConfidence = mmr["colorConfidence"];
        categoryConfidence = mmr["categoryConfidence"];
        makeAndModelConfidence = mmr["makeAndModelConfidence"];
        color = Color(mmr["color"]);
    }
};

class Vehicle
{
public:
    Vehicle(nlohmann::json vehicle)
    {
        m_hasPlate = false;
        m_hasMmr = false;
        if(vehicle.contains("plate"))
        {
            auto jsonplate = vehicle["plate"];
            if(jsonplate.contains("unicodeText"))
            {
                m_hasPlate = true;
                m_plate = Plate(jsonplate);
            }
        }
        if(vehicle.contains("mmr"))
        {
            m_hasMmr = true;
            m_mmr = Mmr(vehicle["mmr"]);
        }
    }
    bool hasPlate()
    {
        return m_hasPlate;
    }
    bool hasMmr()
    {
        return m_hasMmr;
    }

    Plate getPlate()
    {
        return m_plate;
    }
    Mmr getMmr()
    {
        return m_mmr;
    }

private:
    bool m_hasPlate;
    bool m_hasMmr;
    Plate m_plate;
    Mmr m_mmr;
};

#endif // VEHICLE_H
