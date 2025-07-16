#include <vector>
#include<memory>

class EntityManager{
    /*Class to create and manage entity tle data that has been fetched from 
    libcurl*/
    EntityManager(char* data_buffer);
    ~EntityManager();
    std::vector<std::shared_ptr<entity_t>> getEntityData();

};

typedef struct {
    // Line 1 fields
    char catalog_number[6];
    char classification;
    char intl_designator[9];
    double epoch;
    double first_derivative;
    double second_derivative;
    char bstar_drag[9];
    char ephemeris_type;
    char element_number[5];
    char checksum1;
    
    // Line 2 fields  
    char catalog_number2[6];
    double inclination;
    double right_ascension;
    double eccentricity;
    double arg_of_perigee;
    double mean_anomaly;
    double mean_motion;
    int revolution_number;
    char checksum2;
} entity_t;