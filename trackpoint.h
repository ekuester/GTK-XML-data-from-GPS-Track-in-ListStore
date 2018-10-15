/* 
 * File:   trackpoint.h
 * Author: Erich Küster, Krefeld/Germany
 *
 * Created on 19. Mai 2018, 10:19
 */

#ifndef TRACKPOINT_H
#define TRACKPOINT_H

#include <cmath>
#include <glibmm.h>
#include <iostream>

using namespace std;

class Trackpoint {
public:
    guint point;
    double latitude, longitude, elevation;
    Glib::ustring timeReading;
    time_t time;
    double speed, distance;

    Trackpoint();
    virtual ~Trackpoint();

    // distance on great circle
    void distanceByHaversine(Trackpoint* previous);
};

#endif /* TRACKPOINT_H */

