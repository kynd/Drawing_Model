#include "PolyLineUtil.hpp"


ofPolyline PolyLineUtil::toFlatStroke(ofPolyline line, float width, int resolution) {
    resolution = max(4, resolution);
    vector<ofVec3f> centerPoints;
    vector<ofVec3f> points;
    ofPolyline newLine;
    for (int i = 0; i < resolution; i ++) {
        float t = 1.0 / (resolution - 1) * i;
        centerPoints.push_back(line.getPointAtPercent(t));
    }
    
    for (int i = 0; i < resolution; i ++) {
        int pIdx = max(0, i - 1);
        int nIdx = min(resolution - 1, i + 1);
        ofVec3f dir = (centerPoints[nIdx] - centerPoints[pIdx]).getRotatedRad(PI / 2, ofVec3f(0.0, 0.0, 1.0)).getNormalized();
        
        points.push_back(centerPoints[i] + dir * width);
    }
    
    for (int i = resolution - 1; i >= 0; i --) {
        int pIdx = min(resolution - 1, i + 1);
        int nIdx = max(0, i - 1);
        ofVec3f dir = (centerPoints[nIdx] - centerPoints[pIdx]).getRotatedRad(PI / 2, ofVec3f(0.0, 0.0, 1.0)).getNormalized();
        
        points.push_back(centerPoints[i] + dir * width);
    }
     
    newLine.addVertex(points[0]);
    for (int i = 0; i <= points.size(); i ++) {
        int idx = i % points.size();
        newLine.lineTo(points[idx]);
    }
    return newLine;
}


ofPolyline PolyLineUtil::toRoundedStroke(ofPolyline line, float width, int resolution) {
    vector<ofVec3f> centerPoints;
    vector<ofVec3f> points;
    ofPolyline newLine;
    for (int i = 0; i < resolution; i ++) {
        float t = 1.0 / (resolution - 1) * i;
        centerPoints.push_back(line.getPointAtPercent(t));
    }
    
    int capRes = max(8, resolution / 4);
    
    for (int i = 0; i <= capRes; i ++) {
        float ang = -PI / capRes * i - PI / 2;
        ofVec3f dir = (centerPoints[1] - centerPoints[0]).getRotatedRad(ang, ofVec3f(0.0, 0.0, 1.0)).getNormalized();
        points.push_back(centerPoints[0] + dir * width);
    }
     
    for (int i = 0; i < resolution; i ++) {
        int pIdx = max(0, i - 1);
        int nIdx = min(resolution - 1, i + 1);
        ofVec3f dir = (centerPoints[nIdx] - centerPoints[pIdx]).getRotatedRad(PI / 2, ofVec3f(0.0, 0.0, 1.0)).getNormalized();
        
        points.push_back(centerPoints[i] + dir * width);
    }
    
    for (int i = 0; i <= capRes; i ++) {
        float ang = -PI / capRes * i + PI / 2;
        ofVec3f dir = (centerPoints[resolution - 1] - centerPoints[resolution - 2]).getRotatedRad(ang, ofVec3f(0.0, 0.0, 1.0)).getNormalized();
        points.push_back(centerPoints[resolution - 1] + dir * width);
    }
    for (int i = resolution - 1; i >= 0; i --) {
        int pIdx = min(resolution - 1, i + 1);
        int nIdx = max(0, i - 1);
        ofVec3f dir = (centerPoints[nIdx] - centerPoints[pIdx]).getRotatedRad(PI / 2, ofVec3f(0.0, 0.0, 1.0)).getNormalized();
        
        points.push_back(centerPoints[i] + dir * width);
    }
     
    newLine.addVertex(points[0]);
    for (int i = 0; i <= points.size(); i ++) {
        int idx = i % points.size();
        newLine.lineTo(points[idx]);
    }
    return newLine;
}


vector<ofPolyline> PolyLineUtil::toDottedLine(ofPolyline line, float spanA, float spanB) {
    float len = 0, d = 1;
    while (len == 0 && d < 1000) {
        len = line.getLengthAtIndex(line.getVertices().size() - d);
        d += 1;
    }
    
    vector<ofPolyline> lines;
    float p = 0;
    while (p < len) {
        ofPolyline dotLine;
        int n = max(1.f, ceil(spanA / 2));
        for (int i = 0; i < n; i ++) {
            float t = float(i) / (n - 1);
            float ep = min(len, p + spanA);
            ofVec3f pt = line.getPointAtLength(ofLerp(p, ep, t));
            dotLine.addVertex(pt);
        }
        
        p += spanA + spanB;
        lines.push_back(dotLine);
    }
    return lines;
}





ofPolyline PolyLineUtil::noiseWarp(ofPolyline line, int octave, float scaleMult, float decay, ofVec2f scale, ofVec2f amount, ofVec2f seed) {
    
    ofPolyline polyline;
    
    int res = line.getLengthAtIndex(line.getIndexAtPercent(0.999)) / 4;
    for (int i = 0; i < res; i ++) {
        ofVec3f v = line.getPointAtPercent(float(i)/ (res-1));
        ofVec2f p = v;
        ofVec2f amt = amount;
        float mult = 1;
        for (int k = 0; k < octave; k ++) {
            ofVec2f ns = seed + v * scale * mult;
            p.x += ofSignedNoise(ns) * amt.x;
            p.y += ofSignedNoise(ns + ofVec2f(12345.6789)) * amt.y;
            
            amt *= decay;
            mult *= scaleMult;
            
        }
        polyline.addVertex(ofVec3f(p.x, p.y, 0.0));
    }
    return polyline;
}

ofPolyline PolyLineUtil::rectangle(float x, float y, float w, float h) {
    ofPolyline polyline;
    polyline.addVertex(ofVec3f(x, y, 0));
    polyline.lineTo(ofVec3f(x + w, y, 0));
    polyline.lineTo(ofVec3f(x + w, y + h, 0));
    polyline.lineTo(ofVec3f(x, y + h, 0));
    polyline.close();
    return polyline;
}

ofPolyline PolyLineUtil::oval(float x, float y, float w, float h, int resolution) {
    ofPolyline polyline;
    float cx = x + w * 0.5;
    float cy = y + h * 0.5;
    for (int i = 0; i < resolution + 2; i ++) {
        float ang = float(i % resolution) / resolution * TWO_PI;
        float px = cx + cos(ang) * w * 0.5;
        float py = cy + sin(ang) * h * 0.5;
        polyline.curveTo(ofVec3f(px, py, 0.0));
    }
    polyline.close();
    return polyline;
}



ofMesh PolyLineUtil::toStrokeMesh(ofPolyline line, float width, int resolution, ofPolyline taper) {
    vector<ofVec3f> centerPoints;
    vector<ofVec3f> points;
    vector<float> widths;
    ofMesh mesh;
    
    for (int i = 0; i < resolution; i ++) {
        float t = 1.0 / (resolution - 1) * i;
        centerPoints.push_back(line.getPointAtPercent(t));
        float wMult = taper.getVertices().size() == 0 ? 1 : taper.getPointAtPercent(t).x;
        widths.push_back(width * wMult);
        
        if (i % 100 == 0) {
            //cout << i << " " << t << " ** " << line.getPointAtPercent(t) << " ** " << width * wMult << &endl;
        }
    }
    
    for (int i = 0; i < resolution-1; i ++) {
        int pIdx = max(0, i - 1);
        int nIdx = min(resolution - 1, i + 1);
        int nnIdx = min(resolution - 1, i + 2);
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        ofVec3f dir = (centerPoints[nIdx] - centerPoints[pIdx]).getRotatedRad(PI / 2, ofVec3f(0.0, 0.0, 1.0)).getNormalized();
        mesh.addVertex(ofVec3f(centerPoints[i] + dir * widths[i]));
        mesh.addVertex(ofVec3f(centerPoints[i] - dir * widths[i]));
        mesh.addVertex(ofVec3f(centerPoints[i + 1] + dir * widths[i + 1]));
        mesh.addVertex(ofVec3f(centerPoints[i + 1] - dir * widths[i + 1]));
        float t0 = float(i) / (resolution - 1);
        float t1 = float(i + 1) / (resolution - 1);
        mesh.addTexCoord(ofVec2f(0, t0));
        mesh.addTexCoord(ofVec2f(1, t0));
        mesh.addTexCoord(ofVec2f(0, t1));
        mesh.addTexCoord(ofVec2f(1, t1));
    }
    return mesh;
}


ofMesh PolyLineUtil::toFlatPenStrokeMesh(ofPolyline line, float width, ofVec2f dir, int resolution, ofPolyline taper) {
    dir = dir.normalize();
    vector<ofVec3f> centerPoints;
    vector<ofVec3f> points;
    vector<float> widths;
    ofMesh mesh;
    for (int i = 0; i < resolution; i ++) {
        float t = 1.0 / (resolution - 1) * i;
        centerPoints.push_back(line.getPointAtPercent(t));
        float wMult = taper.getVertices().size() == 0 ? 1 : taper.getPointAtPercent(t).x;
        widths.push_back(width * wMult);
    }
    
    for (int i = 0; i < resolution-1; i ++) {
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        mesh.addVertex(ofVec3f(centerPoints[i] + dir * widths[i]));
        mesh.addVertex(ofVec3f(centerPoints[i] - dir * widths[i]));
        mesh.addVertex(ofVec3f(centerPoints[i + 1] + dir * widths[i + 1]));
        mesh.addVertex(ofVec3f(centerPoints[i + 1] - dir * widths[i + 1]));
        float t0 = float(i) / (resolution - 1);
        float t1 = float(i + 1) / (resolution - 1);
        mesh.addTexCoord(ofVec2f(0, t0));
        mesh.addTexCoord(ofVec2f(1, t0));
        mesh.addTexCoord(ofVec2f(0, t1));
        mesh.addTexCoord(ofVec2f(1, t1));
    }
    
    return mesh;
}

ofMesh PolyLineUtil::toRoundStrokeMesh(ofPolyline line, float width, int resolution, ofPolyline taper) {
    vector<ofVec3f> centerPoints;
    vector<ofVec3f> points;
    vector<float> widths;
    float length = line.getLengthAtIndex(line.getIndexAtPercent(0.999));
    float radius = min(width, length / 2);
    float midLength = length - width * 2;
    int rRes = width / 2;
    for (int i = 0; i < rRes; i ++) {
        float l = width / rRes * i;
        ofVec3f p = line.getPointAtLength(l);
        float w = sqrt(pow(width, 2.0) - pow(width - l, 2.0));
        centerPoints.push_back(p);
        
        float wMult = taper.getVertices().size() == 0 ? 1 : taper.getPointAtPercent(l / length).x;
        widths.push_back(w * wMult);
    }
    for (int i = 0; i < resolution; i ++) {
        float l = width + (length - width * 2.0) / (resolution - 1) * i;
        centerPoints.push_back(line.getPointAtLength(l));
        
        float wMult = taper.getVertices().size() == 0 ? 1 : taper.getPointAtPercent(l / length).x;
        widths.push_back(width * wMult);
    }
    for (int i = rRes - 1; i >= 0; i --) {
        float l = width / rRes * i;
        ofVec3f p = line.getPointAtLength(length - l);
        float w = sqrt(pow(width, 2.0) - pow(width - l, 2.0));
        centerPoints.push_back(p);
        
        float wMult = taper.getVertices().size() == 0 ? 1 : taper.getPointAtPercent((length - l) / length).x;
        widths.push_back(w * wMult);
    }
    
    ofMesh mesh;
    int res = centerPoints.size();
    for (int i = 0; i < res-1; i ++) {
        int pIdx = max(0, i - 1);
        int nIdx = min(res - 1, i + 1);
        int nnIdx = min(res - 1, i + 2);
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        ofVec3f dir = (centerPoints[nIdx] - centerPoints[pIdx]).getRotatedRad(PI / 2, ofVec3f(0.0, 0.0, 1.0)).getNormalized();
        mesh.addVertex(ofVec3f(centerPoints[i] + dir * widths[i]));
        mesh.addVertex(ofVec3f(centerPoints[i] - dir * widths[i]));
        mesh.addVertex(ofVec3f(centerPoints[i + 1] + dir * widths[i + 1]));
        mesh.addVertex(ofVec3f(centerPoints[i + 1] - dir * widths[i + 1]));
        float t0 = float(i) / (res - 1);
        float t1 = float(i + 1) / (res - 1);
        mesh.addTexCoord(ofVec2f(0, t0));
        mesh.addTexCoord(ofVec2f(1, t0));
        mesh.addTexCoord(ofVec2f(0, t1));
        mesh.addTexCoord(ofVec2f(1, t1));
    }
    return mesh;
}



ofPath PolyLineUtil::polylineToPath(ofPolyline line) {
    auto v = line.getVertices();
    ofPath path;
    if (v.size() > 0) {
        path.moveTo(v[0]);
        for (int i = 0; i <= v.size(); i ++) {
            path.lineTo(v[i % v.size()]);
        }
    }
    path.close();
    return path;
}



ofPolyline PolyLineUtil::createTaperNtoN(float n0, float n1) {
    ofPolyline line;
    line.addVertex(ofVec3f(n0, 0.0, 0.0));
    line.addVertex(ofVec3f(n1, 1.0, 0.0));
    return line;
}




ofPolyline PolyLineUtil::interpolatePath(ofPolyline line0, ofPolyline line1, float t, bool angleMap) {
    
    ofPolyline lines[2];
    lines[0] = line0;
    lines[1] = line1;
    float startPct0 = 0, startPct1 = 0;
    
    int maxVert = max(lines[0].getVertices().size(), lines[1].getVertices().size());
    
    if (angleMap) {
        int startIdx[2];
        for (int i = 0; i < 2; i ++) {
            auto vertices = lines[i].getVertices();
            ofVec2f c = lines[i].getCentroid2D();
            
            int idx = 0;
            float minAng = PI;
            for (int j = 0; j < vertices.size(); j ++) {
                float ang = atan2(vertices[j].x - c.x, vertices[j].y - c.y);
                if (abs(ang) < minAng) {
                    minAng = abs(ang);
                    idx = j;
                }
            }
            startIdx[i] = idx;
        }
        
        float len0 = lines[0].getLengthAtIndex(startIdx[0]);
        float len1 = lines[1].getLengthAtIndex(startIdx[1]);
        startPct0 = len0 / lines[0].getLengthAtIndex(lines[0].getVertices().size() - 1);
        startPct1 = len1 / lines[1].getLengthAtIndex(lines[1].getVertices().size() - 1);
    }
    
    ofPolyline line = ofPolyline();
    int n = max(192, maxVert);
    for (int i = 0; i < n; i ++) {
        int idx = i % n;
        float pct = float(idx) / n;
        float pct0 = fmod(startPct0 +  pct, 1.f);
        float pct1 = fmod(startPct1 +  pct, 1.f);
        ofVec3f p0 = lines[0].getPointAtPercent(pct0);
        ofVec3f p1 = lines[1].getPointAtPercent(pct1);
        line.addVertex(p0.getInterpolated(p1, t));
    }
    line.close();
    
    return line;
}
