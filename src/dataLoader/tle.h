#pragma once
#include <string>
#include <iostream>


struct TleData {
    std::string OBJECT_NAME;
    std::string OBJECT_ID;
    std::string EPOCH;

    double MEAN_MOTION;
    double ECCENTRICITY;
    double INCLINATION;
    double RA_OF_ASC_NODE;
    double ARG_OF_PERICENTER;
    double MEAN_ANOMALY;

    int EPHEMERIS_TYPE;
    std::string CLASSIFICATION_TYPE;
    int NORAD_CAT_ID;
    int ELEMENT_SET_NO;
    int REV_AT_EPOCH;

    double BSTAR;
    double MEAN_MOTION_DOT;
    double MEAN_MOTION_DDOT;
};


