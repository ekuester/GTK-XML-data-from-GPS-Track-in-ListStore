/* 
 * File:   trackpoint.cpp
 * Author: Erich Küster, Krefeld/Germany
 *
 * Created on 19. Mai 2018, 10:19
 */

#include "trackpoint.h"

Trackpoint::Trackpoint() {
    point = 0;
    latitude = 0.0;
    longitude = 0.0;
    elevation = 0.0;
    timeReading = string();
    time = 0;
    speed = 0.0;
    distance = 0.0;
    std::map<string, string> photoItems;
}

Trackpoint::~Trackpoint() {
    
}

void Trackpoint::distanceByHaversine(Trackpoint* previous) {
    // Formula given by http://en.wikipedia.org/wiki/Great-circle_distance
    // distance = 2 arcsin( sqrt( (sin ((lat2-lat1)/2))^^2 + cos(lat1)cos(lat2)(sin((lon2-lon1)/2))^^2))
    // same given by http://mathforum.org/library/drmath/view/51879.html
    double dRad = 1.74532925199433E-02; // entspricht pi()/180;
    double r = 6371.0; // mittlerer Erdradius in km
    double dlat = (latitude - previous->latitude) * dRad;
    double dlon = (longitude - previous->longitude) * dRad;
    double lat1 = previous->latitude * dRad;
    double lat2 = latitude * dRad;
    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
    distance = (2.0 * asin(sqrt(a)) * r);
}
