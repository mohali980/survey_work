int vcounter = 0; //this keeps track of the number of vertex points in the obj file

static TString ptColor = "red"; //collor of point
static float unitsConv = 1.0; //if a units conversion is needed, we can do it here (i.e. m to mm)
static float ptHW = 0.5*unitsConv; //this will make each plane have +/- ptHW in mm

void ptconv(vector<float> pts, TString *name, ofstream *st)
{
	//each cross will have 12 points, so out vertex tracker will need to be incremented by 12 each time
	//give some information here:
	*st << "# " << name << "  (" << pts[0] << ", " << pts[1] << ", " << pts[2] << ")" << endl;
	//first we loop through the points
	*st << "g " << name << endl;
	*st << "v " << pts[0] << " " << pts[1] + ptHW << " " << pts[2] + ptHW << endl;
	*st << "v " << pts[0] << " " << pts[1] + ptHW << " " << pts[2] - ptHW << endl;
	*st << "v " << pts[0] << " " << pts[1] - ptHW << " " << pts[2] - ptHW << endl;
	*st << "v " << pts[0] << " " << pts[1] - ptHW << " " << pts[2] + ptHW << endl;
	*st << "f -4 -3 -2 -1" << endl;
	
	*st << "v " << pts[0] + ptHW << " " << pts[1] << " " << pts[2] + ptHW << endl;
	*st << "v " << pts[0] + ptHW << " " << pts[1] << " " << pts[2] - ptHW << endl;
	*st << "v " << pts[0] - ptHW << " " << pts[1] << " " << pts[2] - ptHW << endl;
	*st << "v " << pts[0] - ptHW << " " << pts[1] << " " << pts[2] + ptHW << endl;
	*st << "f -4 -3 -2 -1" << endl;
	
	*st << "v " << pts[0] + ptHW << " " << pts[1] + ptHW << " " << pts[2] << endl;
	*st << "v " << pts[0] + ptHW << " " << pts[1] - ptHW << " " << pts[2] << endl;
	*st << "v " << pts[0] - ptHW << " " << pts[1] - ptHW << " " << pts[2] << endl;
	*st << "v " << pts[0] - ptHW << " " << pts[1] + ptHW << " " << pts[2] << endl;
	*st << "f -4 -3 -2 -1" << endl;
	*st << endl;
}

void MUSE_obj_converter(TString collection = "", TString rotTrans = "", vector<float> vrt = {})

{



//	define the input files... 
//	the first one is ole and its frame is the old/main PSI frame, there is no need to use it, it is not a direct MUSE survey.

	int nu_of_trees=0;

	TFile *in_root_file= new TFile("points.root","READ");
	


	TTree *in_PiM1_tree				=	(TTree*) in_root_file->	Get("PiM1");			nu_of_trees++;
	TTree *in_G_PlatForm_tree		=	(TTree*) in_root_file->	Get("G_PlatForm");		nu_of_trees++;
	TTree *in_H_SlidingTable_tree	=	(TTree*) in_root_file->	Get("H_SlidingTable");	nu_of_trees++;
	TTree *in_TA_SlidingTable_tree	=	(TTree*) in_root_file->	Get("TA_SlidingTable");	nu_of_trees++;
	TTree *in_BM_BigBars_tree		=	(TTree*) in_root_file->	Get("BM_BigBars");		nu_of_trees++;
	TTree *in_BM_Hodo_tree			=	(TTree*) in_root_file->	Get("BM_Hodo");			nu_of_trees++;
	TTree *in_STT_LV60_tree			=	(TTree*) in_root_file->	Get("STT_LV60");		nu_of_trees++;
	TTree *in_STT_LH60_tree			=	(TTree*) in_root_file->	Get("STT_LH60");		nu_of_trees++;
	TTree *in_STT_LV90_tree			=	(TTree*) in_root_file->	Get("STT_LV90");		nu_of_trees++;
	TTree *in_STT_LH90_tree			=	(TTree*) in_root_file->	Get("STT_LH90");		nu_of_trees++;
	TTree *in_SPS_LF_tree			=	(TTree*) in_root_file->	Get("SPS_LF");			nu_of_trees++;
	TTree *in_SPS_LR_tree			=	(TTree*) in_root_file->	Get("SPS_LR");			nu_of_trees++;
	TTree *in_STT_RV60_tree			=	(TTree*) in_root_file->	Get("STT_RV60");		nu_of_trees++;
	TTree *in_STT_RH60_tree			=	(TTree*) in_root_file->	Get("STT_RH60");		nu_of_trees++;
	TTree *in_STT_RV90_tree			=	(TTree*) in_root_file->	Get("STT_RV90");		nu_of_trees++;
	TTree *in_STT_RH90_tree			=	(TTree*) in_root_file->	Get("STT_RH90");		nu_of_trees++;
	TTree *in_SPS_RF_tree			=	(TTree*) in_root_file->	Get("SPS_RF");			nu_of_trees++;
	TTree *in_SPS_RR_tree			=	(TTree*) in_root_file->	Get("SPS_RR");			nu_of_trees++;
	TTree *in_M_STT_tree			=	(TTree*) in_root_file->	Get("M_STT");			nu_of_trees++;
	TTree *in_HP_tree				=	(TTree*) in_root_file->	Get("HP");				nu_of_trees++;
	TTree *in_PA6_tree				=	(TTree*) in_root_file->	Get("PA6");				nu_of_trees++;
	TTree *in_PA7_tree				=	(TTree*) in_root_file->	Get("PA7");				nu_of_trees++;
	TTree *in_Kreis_tree			=	(TTree*) in_root_file->	Get("Kreis");			nu_of_trees++;
	TTree *in_G_group_tree			=	(TTree*) in_root_file->	Get("G_group");			nu_of_trees++;
	TTree *in_TG_tree				=	(TTree*) in_root_file->	Get("TG");				nu_of_trees++;
	TTree *in_2E2_tree				=	(TTree*) in_root_file->	Get("2E2");				nu_of_trees++;
	TTree *in_2E1_tree				=	(TTree*) in_root_file->	Get("2E1");				nu_of_trees++;
	TTree *in_TC1_tree				=	(TTree*) in_root_file->	Get("TC1");				nu_of_trees++;
	TTree *in_TC2_tree				=	(TTree*) in_root_file->	Get("TC2");				nu_of_trees++;
	TTree *in_TC3_tree				=	(TTree*) in_root_file->	Get("TC3");				nu_of_trees++;

//	........................................................................................


	TString tmp_txt;
	TString		*in_file_name,*in_frame,*in_collection,*in_group,*in_point,*in_date_time;
	float 	in_x,in_y,in_z,in_offp,in_offr;
	int tree_size;

	for(int i=1;i<nu_of_trees+1;i++)
	{




	if(i==1)
	{
		tmp_txt="TC1";
		tree_size = in_TC1_tree->	GetEntries();
	in_TC1_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_TC1_tree				->	SetBranchAddress("frame",&in_frame);
	in_TC1_tree				->	SetBranchAddress("collection",&in_collection);
	in_TC1_tree				->	SetBranchAddress("group",&in_group);
	in_TC1_tree				->	SetBranchAddress("point",&in_point);
	in_TC1_tree				->	SetBranchAddress("x",&in_x);
	in_TC1_tree				->	SetBranchAddress("y",&in_y);
	in_TC1_tree				->	SetBranchAddress("z",&in_z);
	in_TC1_tree				->	SetBranchAddress("offp",&in_offp);
	in_TC1_tree				->	SetBranchAddress("offr",&in_offr);
	in_TC1_tree				->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==2)
	{
		tmp_txt="TC2";
		tree_size = in_TC2_tree->	GetEntries();
	in_TC2_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_TC2_tree				->	SetBranchAddress("frame",&in_frame);
	in_TC2_tree				->	SetBranchAddress("collection",&in_collection);
	in_TC2_tree				->	SetBranchAddress("group",&in_group);
	in_TC2_tree				->	SetBranchAddress("point",&in_point);
	in_TC2_tree				->	SetBranchAddress("x",&in_x);
	in_TC2_tree				->	SetBranchAddress("y",&in_y);
	in_TC2_tree				->	SetBranchAddress("z",&in_z);
	in_TC2_tree				->	SetBranchAddress("offp",&in_offp);
	in_TC2_tree				->	SetBranchAddress("offr",&in_offr);
	in_TC2_tree				->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==3)
	{
		tmp_txt="TC3";
		tree_size = in_TC3_tree->	GetEntries();
	in_TC3_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_TC3_tree				->	SetBranchAddress("frame",&in_frame);
	in_TC3_tree				->	SetBranchAddress("collection",&in_collection);
	in_TC3_tree				->	SetBranchAddress("group",&in_group);
	in_TC3_tree				->	SetBranchAddress("point",&in_point);
	in_TC3_tree				->	SetBranchAddress("x",&in_x);
	in_TC3_tree				->	SetBranchAddress("y",&in_y);
	in_TC3_tree				->	SetBranchAddress("z",&in_z);
	in_TC3_tree				->	SetBranchAddress("offp",&in_offp);
	in_TC3_tree				->	SetBranchAddress("offr",&in_offr);
	in_TC3_tree				->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==4)
	{
		tmp_txt="2E1";
		tree_size = in_2E1_tree->	GetEntries();
	in_2E1_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_2E1_tree				->	SetBranchAddress("frame",&in_frame);
	in_2E1_tree				->	SetBranchAddress("collection",&in_collection);
	in_2E1_tree				->	SetBranchAddress("group",&in_group);
	in_2E1_tree				->	SetBranchAddress("point",&in_point);
	in_2E1_tree				->	SetBranchAddress("x",&in_x);
	in_2E1_tree				->	SetBranchAddress("y",&in_y);
	in_2E1_tree				->	SetBranchAddress("z",&in_z);
	in_2E1_tree				->	SetBranchAddress("offp",&in_offp);
	in_2E1_tree				->	SetBranchAddress("offr",&in_offr);
	in_2E1_tree				->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==5)
	{
		tmp_txt="2E2";
		tree_size = in_2E2_tree->	GetEntries();
	in_2E2_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_2E2_tree				->	SetBranchAddress("frame",&in_frame);
	in_2E2_tree				->	SetBranchAddress("collection",&in_collection);
	in_2E2_tree				->	SetBranchAddress("group",&in_group);
	in_2E2_tree				->	SetBranchAddress("point",&in_point);
	in_2E2_tree				->	SetBranchAddress("x",&in_x);
	in_2E2_tree				->	SetBranchAddress("y",&in_y);
	in_2E2_tree				->	SetBranchAddress("z",&in_z);
	in_2E2_tree				->	SetBranchAddress("offp",&in_offp);
	in_2E2_tree				->	SetBranchAddress("offr",&in_offr);
	in_2E2_tree				->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==6)
	{
		tmp_txt="G_group";
		tree_size = in_G_group_tree->	GetEntries();
	in_G_group_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_G_group_tree				->	SetBranchAddress("frame",&in_frame);
	in_G_group_tree				->	SetBranchAddress("collection",&in_collection);
	in_G_group_tree				->	SetBranchAddress("group",&in_group);
	in_G_group_tree				->	SetBranchAddress("point",&in_point);
	in_G_group_tree				->	SetBranchAddress("x",&in_x);
	in_G_group_tree				->	SetBranchAddress("y",&in_y);
	in_G_group_tree				->	SetBranchAddress("z",&in_z);
	in_G_group_tree				->	SetBranchAddress("offp",&in_offp);
	in_G_group_tree				->	SetBranchAddress("offr",&in_offr);
	in_G_group_tree				->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==7)
	{
		tmp_txt="TG";
		tree_size = in_TG_tree->	GetEntries();
	in_TG_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_TG_tree				->	SetBranchAddress("frame",&in_frame);
	in_TG_tree				->	SetBranchAddress("collection",&in_collection);
	in_TG_tree				->	SetBranchAddress("group",&in_group);
	in_TG_tree				->	SetBranchAddress("point",&in_point);
	in_TG_tree				->	SetBranchAddress("x",&in_x);
	in_TG_tree				->	SetBranchAddress("y",&in_y);
	in_TG_tree				->	SetBranchAddress("z",&in_z);
	in_TG_tree				->	SetBranchAddress("offp",&in_offp);
	in_TG_tree				->	SetBranchAddress("offr",&in_offr);
	in_TG_tree				->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==8)
	{
		tmp_txt="PiM1";
		tree_size = in_PiM1_tree->	GetEntries();
	in_PiM1_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_PiM1_tree				->	SetBranchAddress("frame",&in_frame);
	in_PiM1_tree				->	SetBranchAddress("collection",&in_collection);
	in_PiM1_tree				->	SetBranchAddress("group",&in_group);
	in_PiM1_tree				->	SetBranchAddress("point",&in_point);
	in_PiM1_tree				->	SetBranchAddress("x",&in_x);
	in_PiM1_tree				->	SetBranchAddress("y",&in_y);
	in_PiM1_tree				->	SetBranchAddress("z",&in_z);
	in_PiM1_tree				->	SetBranchAddress("offp",&in_offp);
	in_PiM1_tree				->	SetBranchAddress("offr",&in_offr);
	in_PiM1_tree				->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==9)
	{
		tmp_txt="G_PlatForm";
		tree_size = in_G_PlatForm_tree->	GetEntries();
	in_G_PlatForm_tree			->	SetBranchAddress("file_name",&in_file_name);
	in_G_PlatForm_tree			->	SetBranchAddress("frame",&in_frame);
	in_G_PlatForm_tree			->	SetBranchAddress("collection",&in_collection);
	in_G_PlatForm_tree			->	SetBranchAddress("group",&in_group);
	in_G_PlatForm_tree			->	SetBranchAddress("point",&in_point);
	in_G_PlatForm_tree			->	SetBranchAddress("x",&in_x);
	in_G_PlatForm_tree			->	SetBranchAddress("y",&in_y);
	in_G_PlatForm_tree			->	SetBranchAddress("z",&in_z);
	in_G_PlatForm_tree			->	SetBranchAddress("offp",&in_offp);
	in_G_PlatForm_tree			->	SetBranchAddress("offr",&in_offr);
	in_G_PlatForm_tree			->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==10)
	{
		tmp_txt="H_SlidingTable";
		tree_size = in_H_SlidingTable_tree->	GetEntries();
	in_H_SlidingTable_tree		->	SetBranchAddress("file_name",&in_file_name);
	in_H_SlidingTable_tree		->	SetBranchAddress("frame",&in_frame);
	in_H_SlidingTable_tree		->	SetBranchAddress("collection",&in_collection);
	in_H_SlidingTable_tree		->	SetBranchAddress("group",&in_group);
	in_H_SlidingTable_tree		->	SetBranchAddress("point",&in_point);
	in_H_SlidingTable_tree		->	SetBranchAddress("x",&in_x);
	in_H_SlidingTable_tree		->	SetBranchAddress("y",&in_y);
	in_H_SlidingTable_tree		->	SetBranchAddress("z",&in_z);
	in_H_SlidingTable_tree		->	SetBranchAddress("offp",&in_offp);
	in_H_SlidingTable_tree		->	SetBranchAddress("offr",&in_offr);
	in_H_SlidingTable_tree		->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==11)
	{
		tmp_txt="H_SlidingTable";
		tree_size = in_TA_SlidingTable_tree->	GetEntries();
	in_TA_SlidingTable_tree	->	SetBranchAddress("file_name",&in_file_name);
	in_TA_SlidingTable_tree	->	SetBranchAddress("frame",&in_frame);
	in_TA_SlidingTable_tree	->	SetBranchAddress("collection",&in_collection);
	in_TA_SlidingTable_tree	->	SetBranchAddress("group",&in_group);
	in_TA_SlidingTable_tree	->	SetBranchAddress("point",&in_point);
	in_TA_SlidingTable_tree	->	SetBranchAddress("x",&in_x);
	in_TA_SlidingTable_tree	->	SetBranchAddress("y",&in_y);
	in_TA_SlidingTable_tree	->	SetBranchAddress("z",&in_z);
	in_TA_SlidingTable_tree	->	SetBranchAddress("offp",&in_offp);
	in_TA_SlidingTable_tree	->	SetBranchAddress("offr",&in_offr);
	in_TA_SlidingTable_tree	->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==12)
	{
		tmp_txt="BM_BigBars";
		tree_size = in_BM_BigBars_tree->	GetEntries();
	in_BM_BigBars_tree			->	SetBranchAddress("file_name",&in_file_name);
	in_BM_BigBars_tree			->	SetBranchAddress("frame",&in_frame);
	in_BM_BigBars_tree			->	SetBranchAddress("collection",&in_collection);
	in_BM_BigBars_tree			->	SetBranchAddress("group",&in_group);
	in_BM_BigBars_tree			->	SetBranchAddress("point",&in_point);
	in_BM_BigBars_tree			->	SetBranchAddress("x",&in_x);
	in_BM_BigBars_tree			->	SetBranchAddress("y",&in_y);
	in_BM_BigBars_tree			->	SetBranchAddress("z",&in_z);
	in_BM_BigBars_tree			->	SetBranchAddress("offp",&in_offp);
	in_BM_BigBars_tree			->	SetBranchAddress("offr",&in_offr);
	in_BM_BigBars_tree			->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==13)
	{
		tmp_txt="BM_Hodo";
		tree_size = in_BM_Hodo_tree->	GetEntries();
	in_BM_Hodo_tree			->	SetBranchAddress("file_name",&in_file_name);
	in_BM_Hodo_tree			->	SetBranchAddress("frame",&in_frame);
	in_BM_Hodo_tree			->	SetBranchAddress("collection",&in_collection);
	in_BM_Hodo_tree			->	SetBranchAddress("group",&in_group);
	in_BM_Hodo_tree			->	SetBranchAddress("point",&in_point);
	in_BM_Hodo_tree			->	SetBranchAddress("x",&in_x);
	in_BM_Hodo_tree			->	SetBranchAddress("y",&in_y);
	in_BM_Hodo_tree			->	SetBranchAddress("z",&in_z);
	in_BM_Hodo_tree			->	SetBranchAddress("offp",&in_offp);
	in_BM_Hodo_tree			->	SetBranchAddress("offr",&in_offr);
	in_BM_Hodo_tree			->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==14)
	{
		tmp_txt="STT_LV60";
		tree_size = in_STT_LV60_tree->	GetEntries();
	in_STT_LV60_tree			->	SetBranchAddress("file_name",&in_file_name);
	in_STT_LV60_tree			->	SetBranchAddress("frame",&in_frame);
	in_STT_LV60_tree			->	SetBranchAddress("collection",&in_collection);
	in_STT_LV60_tree			->	SetBranchAddress("group",&in_group);
	in_STT_LV60_tree			->	SetBranchAddress("point",&in_point);
	in_STT_LV60_tree			->	SetBranchAddress("x",&in_x);
	in_STT_LV60_tree			->	SetBranchAddress("y",&in_y);
	in_STT_LV60_tree			->	SetBranchAddress("z",&in_z);
	in_STT_LV60_tree			->	SetBranchAddress("offp",&in_offp);
	in_STT_LV60_tree			->	SetBranchAddress("offr",&in_offr);
	in_STT_LV60_tree			->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==15)
	{
		tmp_txt="STT_LH60";
		tree_size = in_STT_LH60_tree->	GetEntries();
	in_STT_LH60_tree			->	SetBranchAddress("file_name",&in_file_name);
	in_STT_LH60_tree			->	SetBranchAddress("frame",&in_frame);
	in_STT_LH60_tree			->	SetBranchAddress("collection",&in_collection);
	in_STT_LH60_tree			->	SetBranchAddress("group",&in_group);
	in_STT_LH60_tree			->	SetBranchAddress("point",&in_point);
	in_STT_LH60_tree			->	SetBranchAddress("x",&in_x);
	in_STT_LH60_tree			->	SetBranchAddress("y",&in_y);
	in_STT_LH60_tree			->	SetBranchAddress("z",&in_z);
	in_STT_LH60_tree			->	SetBranchAddress("offp",&in_offp);
	in_STT_LH60_tree			->	SetBranchAddress("offr",&in_offr);
	in_STT_LH60_tree			->	SetBranchAddress("date_time",&in_date_time);

	}
	if(i==16)
	{
		tmp_txt="STT_LV90";
		tree_size = in_STT_LV90_tree->	GetEntries();
	in_STT_LV90_tree			->	SetBranchAddress("file_name",&in_file_name);
	in_STT_LV90_tree			->	SetBranchAddress("frame",&in_frame);
	in_STT_LV90_tree			->	SetBranchAddress("collection",&in_collection);
	in_STT_LV90_tree			->	SetBranchAddress("group",&in_group);
	in_STT_LV90_tree			->	SetBranchAddress("point",&in_point);
	in_STT_LV90_tree			->	SetBranchAddress("x",&in_x);
	in_STT_LV90_tree			->	SetBranchAddress("y",&in_y);
	in_STT_LV90_tree			->	SetBranchAddress("z",&in_z);
	in_STT_LV90_tree			->	SetBranchAddress("offp",&in_offp);
	in_STT_LV90_tree			->	SetBranchAddress("offr",&in_offr);
	in_STT_LV90_tree			->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==17)
	{
		tmp_txt="STT_LH90";
		tree_size = in_STT_LH90_tree->	GetEntries();
	in_STT_LH90_tree			->	SetBranchAddress("file_name",&in_file_name);
	in_STT_LH90_tree			->	SetBranchAddress("frame",&in_frame);
	in_STT_LH90_tree			->	SetBranchAddress("collection",&in_collection);
	in_STT_LH90_tree			->	SetBranchAddress("group",&in_group);
	in_STT_LH90_tree			->	SetBranchAddress("point",&in_point);
	in_STT_LH90_tree			->	SetBranchAddress("x",&in_x);
	in_STT_LH90_tree			->	SetBranchAddress("y",&in_y);
	in_STT_LH90_tree			->	SetBranchAddress("z",&in_z);
	in_STT_LH90_tree			->	SetBranchAddress("offp",&in_offp);
	in_STT_LH90_tree			->	SetBranchAddress("offr",&in_offr);
	in_STT_LH90_tree			->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==18)
	{
		tmp_txt="SPS_LF";
		tree_size = in_SPS_LF_tree->	GetEntries();
	in_SPS_LF_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_SPS_LF_tree				->	SetBranchAddress("frame",&in_frame);
	in_SPS_LF_tree				->	SetBranchAddress("collection",&in_collection);
	in_SPS_LF_tree				->	SetBranchAddress("group",&in_group);
	in_SPS_LF_tree				->	SetBranchAddress("point",&in_point);
	in_SPS_LF_tree				->	SetBranchAddress("x",&in_x);
	in_SPS_LF_tree				->	SetBranchAddress("y",&in_y);
	in_SPS_LF_tree				->	SetBranchAddress("z",&in_z);
	in_SPS_LF_tree				->	SetBranchAddress("offp",&in_offp);
	in_SPS_LF_tree				->	SetBranchAddress("offr",&in_offr);
	in_SPS_LF_tree				->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==19)
	{
		tmp_txt="SPS_LR";
		tree_size = in_SPS_LR_tree->	GetEntries();
	in_SPS_LR_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_SPS_LR_tree				->	SetBranchAddress("frame",&in_frame);
	in_SPS_LR_tree				->	SetBranchAddress("collection",&in_collection);
	in_SPS_LR_tree				->	SetBranchAddress("group",&in_group);
	in_SPS_LR_tree				->	SetBranchAddress("point",&in_point);
	in_SPS_LR_tree				->	SetBranchAddress("x",&in_x);
	in_SPS_LR_tree				->	SetBranchAddress("y",&in_y);
	in_SPS_LR_tree				->	SetBranchAddress("z",&in_z);
	in_SPS_LR_tree				->	SetBranchAddress("offp",&in_offp);
	in_SPS_LR_tree				->	SetBranchAddress("offr",&in_offr);
	in_SPS_LR_tree				->	SetBranchAddress("date_time",&in_date_time);

	}
	if(i==20)
	{
		tmp_txt="STT_RV60";
		tree_size = in_STT_RV60_tree->	GetEntries();
	in_STT_RV60_tree			->	SetBranchAddress("file_name",&in_file_name);
	in_STT_RV60_tree			->	SetBranchAddress("frame",&in_frame);
	in_STT_RV60_tree			->	SetBranchAddress("collection",&in_collection);
	in_STT_RV60_tree			->	SetBranchAddress("group",&in_group);
	in_STT_RV60_tree			->	SetBranchAddress("point",&in_point);
	in_STT_RV60_tree			->	SetBranchAddress("x",&in_x);
	in_STT_RV60_tree			->	SetBranchAddress("y",&in_y);
	in_STT_RV60_tree			->	SetBranchAddress("z",&in_z);
	in_STT_RV60_tree			->	SetBranchAddress("offp",&in_offp);
	in_STT_RV60_tree			->	SetBranchAddress("offr",&in_offr);
	in_STT_RV60_tree			->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==21)
	{
		tmp_txt="STT_RH60";
		tree_size = in_STT_RH60_tree->	GetEntries();
	in_STT_RH60_tree			->	SetBranchAddress("file_name",&in_file_name);
	in_STT_RH60_tree			->	SetBranchAddress("frame",&in_frame);
	in_STT_RH60_tree			->	SetBranchAddress("collection",&in_collection);
	in_STT_RH60_tree			->	SetBranchAddress("group",&in_group);
	in_STT_RH60_tree			->	SetBranchAddress("point",&in_point);
	in_STT_RH60_tree			->	SetBranchAddress("x",&in_x);
	in_STT_RH60_tree			->	SetBranchAddress("y",&in_y);
	in_STT_RH60_tree			->	SetBranchAddress("z",&in_z);
	in_STT_RH60_tree			->	SetBranchAddress("offp",&in_offp);
	in_STT_RH60_tree			->	SetBranchAddress("offr",&in_offr);
	in_STT_RH60_tree			->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==22)
	{
		tmp_txt="STT_RV90";
		tree_size = in_STT_RV90_tree->	GetEntries();
	in_STT_RV90_tree			->	SetBranchAddress("file_name",&in_file_name);
	in_STT_RV90_tree			->	SetBranchAddress("frame",&in_frame);
	in_STT_RV90_tree			->	SetBranchAddress("collection",&in_collection);
	in_STT_RV90_tree			->	SetBranchAddress("group",&in_group);
	in_STT_RV90_tree			->	SetBranchAddress("point",&in_point);
	in_STT_RV90_tree			->	SetBranchAddress("x",&in_x);
	in_STT_RV90_tree			->	SetBranchAddress("y",&in_y);
	in_STT_RV90_tree			->	SetBranchAddress("z",&in_z);
	in_STT_RV90_tree			->	SetBranchAddress("offp",&in_offp);
	in_STT_RV90_tree			->	SetBranchAddress("offr",&in_offr);
	in_STT_RV90_tree			->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==23)
	{
		tmp_txt="STT_RH90";
		tree_size = in_STT_RH90_tree->	GetEntries();
	in_STT_RH90_tree			->	SetBranchAddress("file_name",&in_file_name);
	in_STT_RH90_tree			->	SetBranchAddress("frame",&in_frame);
	in_STT_RH90_tree			->	SetBranchAddress("collection",&in_collection);
	in_STT_RH90_tree			->	SetBranchAddress("group",&in_group);
	in_STT_RH90_tree			->	SetBranchAddress("point",&in_point);
	in_STT_RH90_tree			->	SetBranchAddress("x",&in_x);
	in_STT_RH90_tree			->	SetBranchAddress("y",&in_y);
	in_STT_RH90_tree			->	SetBranchAddress("z",&in_z);
	in_STT_RH90_tree			->	SetBranchAddress("offp",&in_offp);
	in_STT_RH90_tree			->	SetBranchAddress("offr",&in_offr);
	in_STT_RH90_tree			->	SetBranchAddress("date_time",&in_date_time);

	}
	if(i==24)
	{
		tmp_txt="SPS_RF";
		tree_size = in_SPS_RF_tree->	GetEntries();
	in_SPS_RF_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_SPS_RF_tree				->	SetBranchAddress("frame",&in_frame);
	in_SPS_RF_tree				->	SetBranchAddress("collection",&in_collection);
	in_SPS_RF_tree				->	SetBranchAddress("group",&in_group);
	in_SPS_RF_tree				->	SetBranchAddress("point",&in_point);
	in_SPS_RF_tree				->	SetBranchAddress("x",&in_x);
	in_SPS_RF_tree				->	SetBranchAddress("y",&in_y);
	in_SPS_RF_tree				->	SetBranchAddress("z",&in_z);
	in_SPS_RF_tree				->	SetBranchAddress("offp",&in_offp);
	in_SPS_RF_tree				->	SetBranchAddress("offr",&in_offr);
	in_SPS_RF_tree				->	SetBranchAddress("date_time",&in_date_time);

	}
	if(i==25)
	{
		tmp_txt="SPS_RR";
		tree_size = in_SPS_RR_tree->	GetEntries();
	in_SPS_RR_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_SPS_RR_tree				->	SetBranchAddress("frame",&in_frame);
	in_SPS_RR_tree				->	SetBranchAddress("collection",&in_collection);
	in_SPS_RR_tree				->	SetBranchAddress("group",&in_group);
	in_SPS_RR_tree				->	SetBranchAddress("point",&in_point);
	in_SPS_RR_tree				->	SetBranchAddress("x",&in_x);
	in_SPS_RR_tree				->	SetBranchAddress("y",&in_y);
	in_SPS_RR_tree				->	SetBranchAddress("z",&in_z);
	in_SPS_RR_tree				->	SetBranchAddress("offp",&in_offp);
	in_SPS_RR_tree				->	SetBranchAddress("offr",&in_offr);
	in_SPS_RR_tree				->	SetBranchAddress("date_time",&in_date_time);

	}
	if(i==26)
	{
		tmp_txt="M_STT";
		tree_size = in_M_STT_tree->	GetEntries();
	in_M_STT_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_M_STT_tree				->	SetBranchAddress("frame",&in_frame);
	in_M_STT_tree				->	SetBranchAddress("collection",&in_collection);
	in_M_STT_tree				->	SetBranchAddress("group",&in_group);
	in_M_STT_tree				->	SetBranchAddress("point",&in_point);
	in_M_STT_tree				->	SetBranchAddress("x",&in_x);
	in_M_STT_tree				->	SetBranchAddress("y",&in_y);
	in_M_STT_tree				->	SetBranchAddress("z",&in_z);
	in_M_STT_tree				->	SetBranchAddress("offp",&in_offp);
	in_M_STT_tree				->	SetBranchAddress("offr",&in_offr);
	in_M_STT_tree				->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==27)
	{
		tmp_txt="HP";
		tree_size = in_HP_tree->	GetEntries();
	in_HP_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_HP_tree				->	SetBranchAddress("frame",&in_frame);
	in_HP_tree				->	SetBranchAddress("collection",&in_collection);
	in_HP_tree				->	SetBranchAddress("group",&in_group);
	in_HP_tree				->	SetBranchAddress("point",&in_point);
	in_HP_tree				->	SetBranchAddress("x",&in_x);
	in_HP_tree				->	SetBranchAddress("y",&in_y);
	in_HP_tree				->	SetBranchAddress("z",&in_z);
	in_HP_tree				->	SetBranchAddress("offp",&in_offp);
	in_HP_tree				->	SetBranchAddress("offr",&in_offr);
	in_HP_tree				->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==28)
	{
		tmp_txt="PA6";
		tree_size = in_PA6_tree->	GetEntries();
	in_PA6_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_PA6_tree				->	SetBranchAddress("frame",&in_frame);
	in_PA6_tree				->	SetBranchAddress("collection",&in_collection);
	in_PA6_tree				->	SetBranchAddress("group",&in_group);
	in_PA6_tree				->	SetBranchAddress("point",&in_point);
	in_PA6_tree				->	SetBranchAddress("x",&in_x);
	in_PA6_tree				->	SetBranchAddress("y",&in_y);
	in_PA6_tree				->	SetBranchAddress("z",&in_z);
	in_PA6_tree				->	SetBranchAddress("offp",&in_offp);
	in_PA6_tree				->	SetBranchAddress("offr",&in_offr);
	in_PA6_tree				->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==29)
	{
		tmp_txt="PA7";
		tree_size = in_PA7_tree->	GetEntries();
	in_PA7_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_PA7_tree				->	SetBranchAddress("frame",&in_frame);
	in_PA7_tree				->	SetBranchAddress("collection",&in_collection);
	in_PA7_tree				->	SetBranchAddress("group",&in_group);
	in_PA7_tree				->	SetBranchAddress("point",&in_point);
	in_PA7_tree				->	SetBranchAddress("x",&in_x);
	in_PA7_tree				->	SetBranchAddress("y",&in_y);
	in_PA7_tree				->	SetBranchAddress("z",&in_z);
	in_PA7_tree				->	SetBranchAddress("offp",&in_offp);
	in_PA7_tree				->	SetBranchAddress("offr",&in_offr);
	in_PA7_tree				->	SetBranchAddress("date_time",&in_date_time);
	}
	if(i==30)
	{
		tmp_txt="Kreis";
		tree_size = in_Kreis_tree->	GetEntries();
	in_Kreis_tree				->	SetBranchAddress("file_name",&in_file_name);
	in_Kreis_tree				->	SetBranchAddress("frame",&in_frame);
	in_Kreis_tree				->	SetBranchAddress("collection",&in_collection);
	in_Kreis_tree				->	SetBranchAddress("group",&in_group);
	in_Kreis_tree				->	SetBranchAddress("point",&in_point);
	in_Kreis_tree				->	SetBranchAddress("x",&in_x);
	in_Kreis_tree				->	SetBranchAddress("y",&in_y);
	in_Kreis_tree				->	SetBranchAddress("z",&in_z);
	in_Kreis_tree				->	SetBranchAddress("offp",&in_offp);
	in_Kreis_tree				->	SetBranchAddress("offr",&in_offr);
	in_Kreis_tree				->	SetBranchAddress("date_time",&in_date_time);
	}
//	........................................................................................



	TString ofstName =  tmp_txt+ "_"+ ".obj";

	ofstream ofst;
	ofst.open(ofstName);
	

	for(int j=0;j<tree_size;j++)
	{

		if(i==1){in_TC1_tree	-> GetEntry(j);}
		if(i==2){in_TC2_tree	-> GetEntry(j);}
		if(i==3){in_TC3_tree	-> GetEntry(j);}
		if(i==4){in_2E1_tree	-> GetEntry(j);}
		if(i==5){in_2E2_tree	-> GetEntry(j);}
		if(i==6){in_G_group_tree	-> GetEntry(j);}
		if(i==7){in_TG_tree		-> GetEntry(j);}
		if(i==8){in_PiM1_tree	-> GetEntry(j);}
		if(i==9){in_G_PlatForm_tree	-> GetEntry(j);}
		if(i==10){in_H_SlidingTable_tree	-> GetEntry(j);}
		if(i==11){in_TA_SlidingTable_tree	-> GetEntry(j);}
		if(i==12){in_BM_BigBars_tree	-> GetEntry(j);}
		if(i==13){in_BM_Hodo_tree	-> GetEntry(j);}
		if(i==14){in_STT_LV60_tree	-> GetEntry(j);}
		if(i==15){in_STT_LH60_tree	-> GetEntry(j);}
		if(i==16){in_STT_LV90_tree	-> GetEntry(j);}
		if(i==17){in_STT_LH90_tree	-> GetEntry(j);}
		if(i==18){in_SPS_LF_tree	-> GetEntry(j);}
		if(i==19){in_SPS_LR_tree	-> GetEntry(j);}
		if(i==20){in_STT_RV60_tree	-> GetEntry(j);}
		if(i==21){in_STT_RH60_tree	-> GetEntry(j);}
		if(i==22){in_STT_RV90_tree	-> GetEntry(j);}
		if(i==23){in_STT_RH90_tree	-> GetEntry(j);}
		if(i==24){in_SPS_RF_tree	-> GetEntry(j);}
		if(i==25){in_SPS_RR_tree	-> GetEntry(j);}
		if(i==26){in_M_STT_tree	-> GetEntry(j);}
		if(i==27){in_HP_tree	-> GetEntry(j);}
		if(i==28){in_PA6_tree	-> GetEntry(j);}
		if(i==29){in_PA7_tree	-> GetEntry(j);}
		if(i==30){in_Kreis_tree	-> GetEntry(j);}

	
	

	

	bool rt = false;
	
		if((int)vrt.size())
			{
				if((int)vrt.size() == rotTrans.Length()){
					cout << "doing a rotations/translation" << endl;
					rt = true;
				}else{
					cout << "string " << rotTrans << " needs to have the same number of characters as the size of the supplied vector: " << vrt.size() << endl;
				}
			}		

	

	
		TString *name, *collname;
	
		float pt1, pt2, pt3;
		name =	in_point;

		collname = in_collection;


			pt1 = unitsConv*in_x;
			pt2 = unitsConv*in_y;
			pt3 = unitsConv*in_z;
			
			if(rt){
				TVector3 v(pt1, pt2, pt3);
				TVector3 varb;
				for(int i = 0; i < (int)vrt.size(); i++){
					if(rotTrans[i] == 'x'){
						v[0] += vrt[i];
					}
					if(rotTrans[i] == 'y'){
						v[1] += vrt[i];
					}
					if(rotTrans[i] == 'z'){
						v[2] += vrt[i];
					}
					if(rotTrans[i] == 'X'){
						v.RotateX(vrt[i]);
					}
					if(rotTrans[i] == 'Y'){
						v.RotateY(vrt[i]);
					}
					if(rotTrans[i] == 'Z'){
						v.RotateZ(vrt[i]);
					}
					if(rotTrans[i] == 'A'){
						varb.SetX(vrt[i]);
					}
					if(rotTrans[i] == 'R'){
						varb.SetY(vrt[i]);
					}
					if(rotTrans[i] == 'B'){
						varb.SetZ(vrt[i]);
						varb = varb.Unit();
					}
					if(rotTrans[i] == 'T'){
						v.Rotate(vrt[i],varb);
					}
					
				}
				pt1 = v[0];
				pt2 = v[1];
				pt3 = v[2];
			}
			
			vector<float> pts = {pt1, pt2, pt3};

				ptconv(pts, name, &ofst);
			

				
		



	}	//	for(j) over the tree elements

	ofst.close();

	}	//	if(i) over all the trees


	

	
}

