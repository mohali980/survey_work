//
//  surveymarker.hpp
//  fitter
//
//  Created by Steffen Strauch on 2/5/21.
//

#ifndef surveymarker_hpp
#define surveymarker_hpp

#include "G4Transform3D.hh"
#include <stdio.h>
#include <string>
#include <vector>

class survey_points {
public:
    struct marker {
        std::string marker_name;
        std::string marker_system;
        G4Transform3D trans;
    };

    survey_points();
    void add(std::string name, std::string system, G4Transform3D trans);
    marker* get_survey_marker(std::string name);

private:
    std::vector<marker*> survey_markers;
};

#endif /* surveymarker_hpp */
