//
//  surveymarker.cpp
//  fitter
//
//  Created by Steffen Strauch on 2/5/21.
//

#include "g4PSIGEMTelescope.hh"
#include "surveymarker.hpp"

survey_points::survey_points()
{
    // GEMSurvey point: survey marker at the top surface of the GEM mounting plate.
    // It is the middle of the upstream side.

    double gtX = 0.0;
    double gtY = -g4PSIGEMTelescope::plate_top_pos_y;
    double gtZ = -g4PSIGEMTelescope::base_plate_dz / 2;
    add("GEMSurvey", "GEMTelescope", G4Translate3D(gtX, gtY, gtZ)); 
}

void survey_points::add(std::string name, std::string system, G4Transform3D trans)
{
    survey_markers.push_back(new marker({ name, system, trans }));
}

survey_points::marker* survey_points::get_survey_marker(std::string name)
{
    for (auto m : survey_markers) {
        if (m->marker_name == name) {
            return m;
        }
    }
    return nullptr;
}
