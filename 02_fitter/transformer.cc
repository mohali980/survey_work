#include "G4RunManager.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UImanager.hh"
#include "cminpack.h"
#include "g4PSIAnalysisManager.hh"
#include "g4PSIDetectorConstruction.hh"
#include "g4PSIDetectorParts.hh"
#include "surveymarker.hpp"

G4RunManager *runManager;

// Format of the local point definitions
// type coordinate_system_name  point_name
// for now: type="proj" for this type. Then:  norm_x norm_y norm_y  dist
//                projp   norm_x norm_y norm_y  parameter_for_dist
//                dist  norm_x norm_y norm_y  distance
//                distp norm_x norm_y norm_y  parameter_for_distance

class pointdef {
  public:
    int type;
    std::string system;
    std::string name;
    std::vector<double> param;
    std::string paramname;
};
// Format of the survey information
// coordinate_system_name   point_name   coords_x coords_y coords_z

class measurement {
  public:
    std::string system;
    std::string name;
    HepGeom::Point3D<double> pos;
    measurement(std::string s, std::string n, HepGeom::Point3D<double> p) {
        system = s;
        name = n;
        pos = p;
    }
};

std::multimap<std::string, measurement> measurements;

template <typename It> struct range {
    It begin_, end_;
    It begin() const { return begin_; }
    It end() const { return end_; }
};
template <typename It> range<It> as_range(const std::pair<It, It> &p) {
    return {p.first, p.second};
}

void loadMeasurements(std::string filename) {
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        size_t start = line.find_first_not_of(" ");
        // skip comment lines
        if (start != std::string::npos && line.substr(start, 1) != "#") {
            size_t pos = line.find(" ");
            std::string system = line.substr(0, pos);
            line.erase(0, pos + 1);
            if (system == "end" || pos == std::string::npos)
                break;

            pos = line.find(" ");
            std::string name = line.substr(0, pos);
            line.erase(0, pos + 1);
            G4ThreeVector v =
                G4UIcmdWith3VectorAndUnit::GetNew3VectorValue(line.c_str());
            measurements.emplace(
                std::make_pair(name, measurement(system, name, v)));
        }
    }
    infile.close();
}

std::string commands;

void showMeasurements() {
    for (auto m : measurements) {
        printf("Point %s in system %s at point %g %g %g\n",
               m.second.name.c_str(), m.second.system.c_str(), m.second.pos[0],
               m.second.pos[1], m.second.pos[2]);
    }
}


void sendCommands(std::string cmd) {
    std::string buffer;
    std::stringstream cmds(cmd);
    while (cmds.good()) {
        std::getline(cmds, buffer);
        G4UImanager::GetUIpointer()->ApplyCommand(buffer);
    }
}

survey_points sp;

void dumpAllMeasurementsInSystem(std::string basename,std::string targetsystem) {
    std::ofstream ofile;
    ofile.open(basename);
    g4PSIDetectorParts *parts = g4PSIDetectorParts::getInstance();


    G4Transform3D tgttrans;
    if (targetsystem!="global"){
        bool found=false;
        tgttrans=parts->FindTrans(targetsystem,found).inverse();
        if (!found)
        {
            printf("Could not find target system %s",targetsystem.c_str());
            exit(-1);
        }

    }
    ofile<<"# points in system: "<<targetsystem<<std::endl;
    for (auto &m : measurements) {
        std::string m_system = m.second.system;
        G4Transform3D trans;
        G4Transform3D m_trans;
        if (m_system != "global") {
            survey_points::marker *sm = sp.get_survey_marker(m.second.system);
            if (sm) {
                m_system = sm->marker_system;
                m_trans = sm->trans;
            }
        }
        if (m_system != "global") {
            bool found = false;
            trans = parts->FindTrans(m_system, found);
            if (!found)
                continue;
        }
        trans = tgttrans*trans * m_trans;

        G4ThreeVector glo = trans * m.second.pos;
        ofile << m.first << std::setprecision(10) << "\t" << glo[0] << "\t"
              << glo[1] << "\t" << glo[2] << std::endl;
    }
    ofile.close();
}


void loadCommands(std::string filename, std::string &mac_commands)
    {

    std::ifstream file(filename);
    std::string str;
    while (std::getline(file, str)) {
        size_t start = str.find_first_not_of(" ");
        // skip comment lines
        if (start != std::string::npos && str.substr(start, 1) != "#") {
            mac_commands += str + "\n";            
            std::stringstream ss(str);
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 5) {
        printf("Need more arguments: <measurements> <mac "
               "file> <system> <output-name>\n");
        exit(-1);
    }

    
    loadMeasurements(argv[1]);
    //  showMeasurements();

    std::string commands_transforms;
    loadCommands(argv[2],commands);


    runManager = new G4RunManager;

    // set mandatory initialization classes
    runManager->SetUserInitialization(new g4PSIDetectorConstruction);
    sendCommands(commands);
    runManager->InitializeGeometry();

    dumpAllMeasurementsInSystem(argv[4],argv[3]);

    return 0;
}