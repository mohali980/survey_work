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

std::vector<pointdef> pointdefs;

std::map<std::string, int> nameToParam;
int paramcount = 0;

std::string commands;


//...........................................................................

void loadPointDefs(std::string filename) {
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        size_t start = line.find_first_not_of(" ");
        // skip comment lines
        if (start != std::string::npos && line.substr(start, 1) != "#") {
            std::stringstream ss(line);
            std::string type, system, name;
            ss >> type >> system >> name;

            if (type == "proj") 
            {
                double x, y, z;
                ss >> x >> y >> z;
                char buffer[1024];
                ss.getline(buffer, 1024);
                double dist =
                    G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(buffer);
                pointdefs.push_back(
                    {0, system, name, std::vector<double>{x, y, z, dist}, ""});
            }

            if (type == "projp") 
            {
                double x, y, z;
                std::string parmname;
                ss >> x >> y >> z >> parmname;
                if (nameToParam.count(parmname) == 0)
                    nameToParam[parmname] = paramcount++;
                pointdefs.push_back({1, system, name,
                                     std::vector<double>{x, y, z, 0},
                                     parmname});
            }

            if (type == "dist") 
            {
                double x, y, z;
                ss >> x >> y >> z;
                char buffer[1024];
                ss.getline(buffer, 1024);
                double dist =
                    G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(buffer);
                pointdefs.push_back(
                    {2, system, name, std::vector<double>{x, y, z, dist}, ""}); 
            }

            if (type == "distp") 
            {
                double x, y, z;
                std::string parmname;
                ss >> x >> y >> z >> parmname;
                if (nameToParam.count(parmname) == 0)
                    nameToParam[parmname] = paramcount++;
                pointdefs.push_back({3, system, name,
                                     std::vector<double>{x, y, z, 0},
                                     parmname});
            }

            if (type == "end") 
            {
                break;
            }
        }
    }
}

//...........................................................................


void showPointDefs() 
{
    for (auto m : pointdefs) 
    {
        printf("PD type %i is in system %s name %s using ", m.type,
               m.system.c_str(), m.name.c_str());
        for (auto v : m.param)
        
        printf("%g ", v);
        printf("\n");
    }
}


//...........................................................................
// Format of the survey information
// coordinate_system_name   point_name   coords_x coords_y coords_z

class measurement 
{
  public:
    std::string system;
    std::string name;
    HepGeom::Point3D<double> pos;

    measurement(std::string s, std::string n, HepGeom::Point3D<double> p) 
    {
        system = s;
        name = n;
        pos = p;
    }
}

std::multimap<std::string, measurement> measurements;

template <typename It> struct range 
{
    It begin_, end_;
    It begin() const { return begin_; }
    It end() const { return end_; }
}

template <typename It> range<It> as_range(const std::pair<It, It> &p) 
{
    return {p.first, p.second};
}



//...........................................................................

void loadMeasurements(std::string filename) 
{
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) 
    {
        size_t start = line.find_first_not_of(" ");
        // skip comment lines
        if (start != std::string::npos && line.substr(start, 1) != "#") 
        {
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

//...........................................................................

void showMeasurements() 
{
    for (auto m : measurements) 
    {
        printf("Point %s in system %s at point %g %g %g\n",
               m.second.name.c_str(), m.second.system.c_str(), m.second.pos[0],
               m.second.pos[1], m.second.pos[2]);
    }
}

//...........................................................................


void loadAndFindParams(std::string filename, std::string &mac_commands,
                       std::string &mac_commands_transform) 
{

    std::ifstream file(filename);
    std::string str;
    while (std::getline(file, str)) 
    {
        size_t start = str.find_first_not_of(" ");
        // skip comment lines
        if (start != std::string::npos && str.substr(start, 1) != "#") 
        {
            mac_commands += str + "\n";
            if (str.find("$") != std::string::npos) 
            {
                mac_commands_transform += str + "\n";
            }

            std::stringstream ss(str);
            while (ss.good()) {
                std::string word;
                ss >> word;
                if (word[0] == '$') 
                {
                    printf("Found param: %s\n", word.c_str());
                    if (nameToParam.count(word) == 0)
                        nameToParam[word] = paramcount++;
                }
            }
        }
    }
}

double *params;


//...........................................................................

std::string updateCommands(std::string mac_file, const double *par,
                           std::string format_string = "%.20g") 
{
    for (auto p : nameToParam) 
    {
        size_t pos;
        char buf[1024];
        sprintf(buf, format_string.c_str(), par[p.second]);
        while (mac_file.npos != (pos = mac_file.find(p.first)))
        
            mac_file.replace(pos, p.first.length(), buf);  
    }        
    return mac_file;
}

//...........................................................................
void showCommandsAndParams() {
    std::cout << commands << std::endl;
    for (auto p : nameToParam) {
        std::cout << p.first << " " << p.second << std::endl;
    }
}
//...........................................................................
void sendCommands(std::string cmd) 
{
    std::string buffer;
    std::stringstream cmds(cmd);
    while (cmds.good()) 
    {
        std::getline(cmds, buffer);
        G4UImanager::GetUIpointer()->ApplyCommand(buffer);
    }
}


//...........................................................................

survey_points sp;
int iter = 0;

inline double sqr(double x) { return x * x; }



int fitfunc(void *p, int m0, int n, const double *x, double *fvec, int iflag) 
{
    double chi2 = 0;
    // show parameters
    /*    printf("==========\n");
      for (int i = 0; i < n; i++) {
          printf(" %8.12g ", i, x[i]);
      }
      printf("\n");*/
    // make new geometry with current parameter set
    runManager->ReinitializeGeometry(true);
    g4PSIDetectorParts::getInstance()->dispose();    
    sendCommands(updateCommands(commands, x));

    runManager->InitializeGeometry();

    // go through the list of "rules" in pointdefs
    // transform measurements from measurement to local, determine error
    // save error in fvec

    int i = 0;

    std::map<std::string, G4Transform3D> rcache, mcache;



//...........................................................................




    for (auto &rule : pointdefs) 
    {

        // here, convert from m.system to rule.system
        // geant 4 call!

        std::string r_system = rule.system;

        G4Transform3D trans;
        G4Transform3D trans2;
        g4PSIDetectorParts *parts = g4PSIDetectorParts::getInstance();
        if (measurements.find(rule.name) == measurements.end()) 
        {
            assert(false);
            printf("Did not find measurement for %s.. bailing out\n",
                   rule.name.c_str());
            exit(-1);
        }

        if (rcache.find(rule.system) == rcache.end()) 
        {
            G4Transform3D r_trans;
            if (r_system != "global") 
            {
                survey_points::marker *sm1 = sp.get_survey_marker(rule.system);
                if (sm1) 
                {
                    r_system = sm1->marker_system;
                    r_trans = sm1->trans.inverse();
                }
            }
        
        if (r_system != "global") 
            {
                bool found = false;
                trans = parts->FindTrans(r_system, found).inverse();
                if (!found) {
                    printf("Did not find %s as rule.system.. bailing "
                           "out\n",
                           r_system.c_str());
                    assert(false);
                    exit(-1);
                }
            }
            trans = r_trans * trans;
            rcache[rule.system] = trans;
        }

        else    {   trans = rcache[rule.system];    }
      

        for (auto m : as_range(measurements.equal_range(rule.name))) 
        {
            if (mcache.find(m.second.system) == mcache.end()) 
            {
                std::string m_system = m.second.system;
                G4Transform3D m_trans;
                if (m_system != "global") 
                {
                    survey_points::marker *sm =
                        sp.get_survey_marker(m.second.system);
                    if (sm) 
                    {
                        m_system = sm->marker_system;
                        m_trans = sm->trans;
                    }
                }
                if (m_system != "global") 
                {
                    bool found = false;
                    trans2 = parts->FindTrans(m_system, found);
                    if (!found) 
                    {
                        printf("Did not find %s as m.system.. bailing "
                               "out\n",
                               m_system.c_str());
                        assert(false);
                        exit(-1);
                    }
                }

                trans2 = trans2 * m_trans;
                mcache[m.second.system] = trans2;
            } 
            else    {   trans2 = mcache[m.second.system];   }

        

            G4ThreeVector transformed_meas = trans * trans2 * m.second.pos;
            

            if (rule.type == 0 || rule.type == 1) 
            {
                if (rule.type == 1)
                    rule.param[3] = x[nameToParam[rule.paramname]];
                double err = transformed_meas[0] * rule.param[0] +
                             transformed_meas[1] * rule.param[1] +
                             transformed_meas[2] * rule.param[2] -
                             rule.param[3];
                fvec[i] = err;
                chi2 += err * err;
                if (iflag == 100 || isnan(err))
                    printf("%s %s %s %g %g %g  %g %g   %g\n", r_system.c_str(),
                           m.second.system.c_str(), m.first.c_str(),
                           rule.param[0], rule.param[1], rule.param[2],
                           rule.param[3],
                           transformed_meas[0] * rule.param[0] +
                               transformed_meas[1] * rule.param[1] +
                               transformed_meas[2] * rule.param[2],
                           err);
                i++;
            }

        if (rule.type == 2 || rule.type == 3) 
            {
                if (rule.type == 3)
                {
                    rule.param[3] = x[nameToParam[rule.paramname]];                    
                }

                double err = sqrt(sqr(transformed_meas[0] * rule.param[0]) +
                             sqr(transformed_meas[1] * rule.param[1]) +
                             sqr(transformed_meas[2] * rule.param[2])) -
                             rule.param[3];
                fvec[i] = err;
                chi2 += err * err;
                if (iflag == 100 || isnan(err))
                    printf("distance %s %s %s %g %g %g  %g %g   %g\n", r_system.c_str(),
                           m.second.system.c_str(), m.first.c_str(),
                           rule.param[0], rule.param[1], rule.param[2],
                           rule.param[3],
                           sqrt(sqr(transformed_meas[0] * rule.param[0]) +
                               sqr(transformed_meas[1] * rule.param[1]) +
                               sqr(transformed_meas[2] * rule.param[2])),
                           err);
                i++;
            }

        }
    }
    printf("Total Chi^2:%8.12g  Red Chi^2: %8.12g => Err: %8.12g mm Iter: "
           "%i\n",
           chi2, chi2 / (m0 - n), sqrt(chi2 / (m0 - n)), iter++);
    return 0;
}


//...........................................................................




void dumpAllMeasurementsInGlobal(std::string basename) 
{
    std::ofstream ofile;
    ofile.open(basename + ".measurements_in_global");
    g4PSIDetectorParts *parts = g4PSIDetectorParts::getInstance();

    for (auto &m : measurements) 
    {
        std::string m_system = m.second.system;
        G4Transform3D trans;
        G4Transform3D m_trans;
        if (m_system != "global") 
        {
            survey_points::marker *sm = sp.get_survey_marker(m.second.system);
            if (sm) 
            {
                m_system = sm->marker_system;
                m_trans = sm->trans;
            }
        }
        if (m_system != "global") 
        {
            bool found = false;
            trans = parts->FindTrans(m_system, found);
            if (!found)
                continue;
        }
        trans = trans * m_trans;
        G4ThreeVector glo = trans * m.second.pos;
        ofile << m.first << std::setprecision(10) << "\t" << glo[0] << "\t"
              << glo[1] << "\t" << glo[2] << std::endl;
    }
    ofile.close();
}



//...........................................................................

int calcNumberOfPoints() 
{
    int np = 0;
    for (auto pd : pointdefs) 
    {
        np += measurements.count(pd.name);
    }
    return np;
}

//...........................................................................

int main(int argc, char **argv) 
{
    if (argc < 4) 
    {
        printf("Need more arguments: <pointdefs> <measurements> <mac "
               "file> "
               "[output-base-name]\n");
        exit(-1);
    }

    loadPointDefs(argv[1]);
    showPointDefs();

    loadMeasurements(argv[2]);
    //  showMeasurements();

    std::string commands_transforms;
    loadAndFindParams(argv[3], commands, commands_transforms);
    showCommandsAndParams();

    params = new double[nameToParam.size()];
    for (size_t i = 0; i < nameToParam.size(); i++)
        params[i] = 0.1;

    int numberOfPoints = calcNumberOfPoints();
    int numberOfParameters = nameToParam.size();

    int *iwork = new int[numberOfPoints + numberOfParameters];
    double *dwork = new double[10000000];
    double *fvec = new double[numberOfPoints];

    runManager = new G4RunManager;

    // set mandatory initialization classes
    runManager->SetUserInitialization(new g4PSIDetectorConstruction);
    sendCommands(updateCommands(commands, params));
    runManager->InitializeGeometry();


    g4PSIDetectorParts::getInstance()->Dump();

    printf("Fitting %i to %i\n", numberOfParameters, numberOfPoints);
    int erg = lmdif1(fitfunc, NULL, numberOfPoints, numberOfParameters, params,
                     fvec, 1e-10, iwork, dwork, 10000000);
    printf("lmdif1 returned: erg = %d\n", erg);

    fitfunc(NULL, numberOfPoints, numberOfParameters, params, fvec, 100);

    // Print out best parameters;
    printf("Final parameters\n");
    for (auto p : nameToParam) 
    {
        printf("%s %8.12g\n", p.first.c_str(), params[p.second]);
    }
    runManager->ReinitializeGeometry(true);
    g4PSIDetectorParts::getInstance()->dispose();
    sendCommands(updateCommands(commands, params));
    runManager->InitializeGeometry();

    if (argc == 5) {
        std::string basename = argv[4];
        std::cout << updateCommands(commands_transforms, params, "%9.5f");
        std::ofstream ofile;
        ofile.open(basename + ".mac");
        ofile << updateCommands(commands_transforms, params, "%9.5f");
        ofile.close();

        dumpAllMeasurementsInGlobal(basename);
    }
    return 0;
}

