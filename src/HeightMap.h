/**
 * Basic header/include file for HeightMap.cpp.
 *
 * @author GabuEx, dawnmew
 * @since 1.0
 *
 * Licensed under the MIT License.
 *
 * Copyright (c) 2014 Equestrian Dreamers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "Line.h"
#include "Polygon.h"

class XmlReader;

class HeightMap
{
public:
    virtual ~HeightMap() {}

    bool IsPointInBoundingPolygon(Vector2 point) { return this->boundingPolygon.Contains(point); }
    void SetDirectionVector(Vector2 directionVector) { this->directionVector = directionVector.Normalize(); }
    void SetBoundingPolygon(GeometricPolygon boundingPolygon) { this->boundingPolygon = boundingPolygon; }

    virtual int GetHeightAtPoint(Vector2 point) = 0;
    Vector2 GetBasePointOffsetFromHeightenedPoint(Vector2 point);
    static HeightMap * LoadFromXml(XmlReader *pReader);

protected:
    virtual int GetHighestHeight() = 0;
    void LoadFromXmlCore(XmlReader *pReader);

    Vector2 directionVector;
    GeometricPolygon boundingPolygon;
};

class ParabolicHeightMap : public HeightMap
{
public:
    ParabolicHeightMap(XmlReader *pReader);

    virtual int GetHeightAtPoint(Vector2 point);

protected:
    virtual int GetHighestHeight();

    class HeightLine : public Line
    {
    public:
        HeightLine()
        {
            heightAtLine = 0;
        }

        HeightLine(XmlReader *pReader);

        int GetHeightAtLine() { return this->heightAtLine; }

    private:
        int heightAtLine;
    };

private:
    HeightLine heightLine1;
    HeightLine heightLine2;
    HeightLine heightLine3;
};

#endif
