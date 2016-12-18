
#ifndef Fido_Data_H
#define Fido_Data_H

/*********Verices*********/
/***********Fido***********/
const GLfloat pelvis[8][3]={{1.581921,4.807983,-.9096741},
{2.167017,7.698334,-.5317017},
{2.167017,7.138336,4.278168},
{1.581921,4.219983,3.900202},
{-1.581921,4.807983,-.9096741},
{-2.167017,7.698334,-.5317017},
{-2.167017,7.138336,4.278168},
{-1.581921,4.219983,3.900202}};

const GLfloat torso[8][3]={{1.845575,2.90799,-5.144598},
{2.528192,6.839654,-3.638147},
{2.528192,8.193506,.2441772},
{1.845575,4.146942,.2441772},
{-1.845575,2.90799,-5.144598},
{-1.845575,4.146942,.2441772},
{-2.528192,8.193506,.2441772},
{-2.528192,6.839654,-3.638147}};

const GLfloat ruparm[8][3]={{-2.394708,3.912378,-1.553571},
{-2.394708,6.118683,-2.749841},
{-2.394708,6.550775,-.762848},
{-2.394708,4.34447,.4334166},
{-4.881024,3.912378,-1.553571},
{-4.881024,4.34447,.4334166},
{-4.881024,6.550775,-.762848},
{-4.881024,6.118683,-2.749841}};

const GLfloat rloarm[8][3]={{-2.878888,.877759,-2.043537},
{-2.878888,4.471851,-2.043537},
{-2.878888,4.471851,.4008178},
{-2.878888,.877759,-.6046693},
{-4.449188,.877759,-2.043537},
{-4.449188,.877759,-.6046693},
{-4.449188,4.471851,.4008178},
{-4.449188,4.471851,-2.043537}};

const GLfloat rhand[6][3]={{-4.652588,1.205389,-.8437561},
{-2.450641,1.205389,-.8437561},
{-2.450641,1.114511E-02,-3.823443},
{-4.652588,1.114511E-02,-3.823443},
{-4.652588,2.356577E-02,-.3929993},
{-2.450641,2.356577E-02,-.3929993}};

const GLfloat luparm[8][3]={{4.881024,3.912378,-1.553571},
{4.881024,6.118683,-2.749841},
{4.881024,6.550776,-.762848},
{4.881024,4.344471,.4334166},
{2.394708,3.912378,-1.553571},
{2.394708,4.344471,.4334166},
{2.394708,6.550776,-.762848},
{2.394708,6.118683,-2.749841}};

const GLfloat lloarm[8][3]={{4.449188,.877759,-2.043537},
{4.449188,4.471851,-2.043537},
{4.449188,4.471851,.4008178},
{4.449188,.877759,-.6046693},
{2.878888,.877759,-2.043537},
{2.878888,.877759,-.6046693},
{2.878888,4.471851,.4008178},
{2.878888,4.471851,-2.043537}};

const GLfloat lhand[6][3]={{2.450641,1.205389,-.8437561},
{4.652588,1.205389,-.8437561},
{4.652588,1.114511E-02,-3.823443},
{2.450641,1.114511E-02,-3.823443},
{2.450641,2.356577E-02,-.3929993},
{4.652588,2.356577E-02,-.3929993}};

const GLfloat turret[6][3]={{-1.668604,7.339197,3.201221},
{-1.668604,10.24299,2.088879},
{-1.668604,7.364282,.6803894},
{1.668604,7.339197,3.201221},
{1.668604,7.364282,.6803894},
{1.668604,10.24299,2.088879}};

const GLfloat gauss[10][3]={{.8608215,10.17199,-4.515607},
{.8608215,9.177996,-4.515607},
{-.8608215,9.177996,-4.515607},
{-.8608215,10.17199,-4.515607},
{1.229755,9.177996,3.975989},
{1.229755,10.59799,3.975989},
{-1.229755,10.59799,3.975989},
{-1.229755,9.177996,3.975989},
{0,10.66899,-3.379602},
{0,11.30799,2.555982}};

const GLfloat lthing[8][3]={{4.599994,5.127973,1.092755},
{4.599994,7.67066,3.916693},
{4.599994,6.900653,5.653992},
{4.599994,4.361139,2.059558},
{2.599994,5.127973,1.092755},
{2.599994,4.361139,2.059558},
{2.599994,6.900653,5.653992},
{2.599994,7.67066,3.916693}};

const GLfloat rthing[8][3]={{-2.599994,5.127973,1.092755},
{-2.599994,7.67066,3.916693},
{-2.599994,6.900653,5.653992},
{-2.599994,4.361139,2.059558},
{-4.599994,5.127973,1.092755},
{-4.599994,4.361139,2.059558},
{-4.599994,6.900653,5.653992},
{-4.599994,7.67066,3.916693}};

const GLfloat lleg[8][3]={{4.259753,2.361517,3.043512},
{4.259753,5.071557,1.890344},
{4.259753,5.390771,3.262268},
{4.259753,2.445007,4.176971},
{2.891711,2.361517,3.043512},
{2.891711,2.445007,4.176971},
{2.891711,5.390771,3.262268},
{2.891711,5.071557,1.890344}};

const GLfloat rleg[8][3]={{-4.259753,2.361517,3.043512},
{-4.259753,5.071557,1.890344},
{-4.259753,5.390771,3.262268},
{-4.259753,2.445007,4.176971},
{-2.891711,2.361517,3.043512},
{-2.891711,2.445007,4.176971},
{-2.891711,5.390771,3.262268},
{-2.891711,5.071557,1.890344}};

const GLfloat lfoot[8][3]={{4.499994,8.690166E-02,1.693726E-02},
{4.499994,3.358716,3.411511},
{4.499994,2.770941,4.220514},
{4.499994,7.031822E-02,2.15661},
{2.599994,8.690166E-02,1.693726E-02},
{2.599994,7.031822E-02,2.15661},
{2.599994,2.770941,4.220514},
{2.599994,3.358716,3.411511}};

const GLfloat rfoot[8][3]={{-4.499994,8.690166E-02,1.693726E-02},
{-4.499994,3.358716,3.411511},
{-4.499994,2.770941,4.220514},
{-4.499994,7.031822E-02,2.15661},
{-2.599994,8.690166E-02,1.693726E-02},
{-2.599994,7.031822E-02,2.15661},
{-2.599994,2.770941,4.220514},
{-2.599994,3.358716,3.411511}};

/***********Favce Indeces************/
const GLubyte pelvis_vertex[6][4]={{0,1,2,3},
{1,5,6,2},
{7,6,5,4},
{0,4,7,3},
{2,6,7,3},
{1,0,4,5}};

const GLubyte torso_vertex[6][4]={{1,2,3,0},
{2,5,4,3},
{5,6,7,4},
{1,6,7,0},
{6,5,2,1},
{3,4,7,0}};

const GLubyte cube_vertex[6][4]={{5,6,7,4},
{7,6,2,1},
{2,3,0,1},
{3,5,4,0},
{7,1,0,4},
{6,5,3,2}};

const GLubyte hand_vertex[5][4]={{0,1,2,3},
{0,4,5,1},
{3,2,5,4},
{3,0,4,255},
{1,5,2,255}};

const GLubyte turret_vertex[5][4]={{1,5,4,2},
{0,3,5,1},
{0,2,4,3},
{5,3,4,255},
{0,1,2,255}};

const GLubyte gauss_vertex[9][4]={{0,5,4,1},
{0,8,9,5},
{8,3,6,9},
{2,7,6,3},
{1,4,7,2},
{4,5,6,7},
{0,1,2,3},
{3,8,0,255},
{5,9,6,255}};

/********Wind Generator********/
/*********Vertices*********/
const GLfloat base[48][3]={{2.119617,23.63284,6.444092E-02},
{1.137543,23.63284,-1.636548},
{-.8265808,23.63284,-1.636548},
{-1.808655,23.63284,6.444092E-02},
{-.8265808,23.63284,1.76543},
{1.137543,23.63284,1.76543},
{3.084998,10.19099,-.1454956},
{1.603748,10.19099,-2.711096},
{-1.358746,10.19099,-2.711096},
{-2.839996,10.19099,-.1454956},
{-1.358746,10.19099,2.420099},
{1.603748,10.19099,2.420099},
{5.503424,10.08435,8.088379E-02},
{3.154865,10.08435,4.787213},
{-2.57572,10.08435,4.618182},
{-5.346637,10.08435,-.181189},
{-2.669501,10.08435,-5.246387},
{2.618048,10.08435,-4.863538},
{-5.346637,9.084473E-02,-.181189},
{-2.57572,9.084473E-02,4.618182},
{-2.669501,9.084473E-02,-5.246387},
{2.618048,9.084473E-02,-4.863538},
{5.503424,9.084473E-02,7.957153E-02},
{3.154865,9.084473E-02,4.787213},
{2.898779,10.15412,6.73374},
{-2.456958,10.15412,6.54671},
{-1.068323,10.15412,7.797254},
{1.4263,10.15412,7.884369},
{-2.236456,7.267456E-02,10.64515},
{-.8478211,7.267456E-02,11.8957},
{.9204407,7.267456E-02,11.95744},
{2.39292,7.267456E-02,10.80682},
{-4.46424,10.15412,-5.992371},
{-6.980145,10.15412,-1.260645},
{-7.368823,10.15412,-3.088507},
{-6.19696,10.15412,-5.292468},
{-8.24455,7.267456E-02,-7.590827},
{-9.977277,7.267456E-02,-6.89093},
{-10.80793,7.267456E-02,-5.328687},
{-10.41925,7.267456E-02,-3.500824},
{4.423017,10.15412,-5.690826},
{7.102527,10.15412,-1.049786},
{7.427173,10.15412,-2.890106},
{6.179108,10.15412,-5.051831},
{8.145246,7.267456E-02,-7.420245},
{9.901337,7.267456E-02,-6.781238},
{10.78601,7.267456E-02,-5.248938},
{10.46135,7.267456E-02,-3.408624}};

const GLfloat post[48][3]={{-6.717749,26.95084,9.006141},
{-1.782434,26.95084,14.24779},
{2.882935,26.95084,14.24779},
{6.909741,26.95084,9.006153},
{2.882935,25.58809,14.24779},//4
{6.909741,25.58809,9.006153},
{-1.782434,25.58809,14.24779},
{-6.717749,25.58809,9.006141},
{-3.537994,26.95084,9.006153},
{-6.681408,26.95084,5.826397},
{-6.681408,25.58809,5.826397},//10
{-3.537994,25.58809,9.006153},
{6.891565,25.58809,5.826397},
{6.891565,26.95084,5.826397},
{3.729993,26.95084,9.006141},
{3.729993,25.58809,9.006141},
{1.004492,23.7711,-1.914008},
{1.004492,31.9476,-1.914008},
{1.005249,31.9476,-.6407959},
{1.004492,23.7711,1.719977},
{-.8125,23.7711,-1.914008},//20
{-.8125,23.7711,1.719977},
{-.8117431,31.9476,-.6407959},
{-.8125,31.9476,-1.914008},
{-.8125,26.95084,5.372143},
{-.8125,23.7711,5.372143},
{-.8125,25.58809,9.006153},
{-.8125,26.95084,9.006153},
{1.004492,26.95084,5.372143},
{1.004492,26.95084,9.006141},
{1.004492,25.58809,9.006141},//30
{1.004492,23.7711,5.372143},//31
{1.030988,23.7,2.461487},//32
{2.610992,23.7,.8814942},
{2.610992,26.46499,.8814942},//34
{1.030988,26.46499,2.461487},
{2.610992,26.46499,-.6984985},
{2.610992,23.7,-.6984985},
{1.030988,23.7,-1.883502},
{1.030988,26.46499,-1.883502},
{-.8650025,26.46499,2.461487},//40
{-.8650025,26.46499,-1.883502},//41
{-2.445001,26.46499,-.6984985},//42
{-2.445001,26.46499,.8814942},//43
{-.8650025,23.7,2.461487},//44
{-2.445001,23.7,.8814942},//45
{-2.445001,23.7,-.6984985},
{-.8650025,23.7,-1.883502}};

const GLfloat blades[28][3]={{-1.522559,31.57258,-4.755133},
{-.3625061,32.21561,-2.376209},
{-6.929071,44.06202,-2.376209},
{-9.334381,45.66546,-4.755133},
{-1.484802,29.26857,-2.178046},
{-.4725158,28.68412,-4.731848},
{-8.529095,14.72971,-4.731848},
{-8.257129,17.53856,-2.17804},
{17.98458,30.00416,-2.450507},
{15.39332,31.24684,-4.875488},
{1.850732,31.20579,-4.642694},
{1.873883,29.95532,-2.17356},
{2.374879E-02,32.38998,-4.766998},
{1.819666,31.40248,-4.766998},
{1.819666,29.42749,-4.766998},
{2.374879E-02,28.43999,-4.766998},
{-1.772162,29.42749,-4.766998},
{-1.772162,31.40248,-4.766998},//17
{2.374879E-02,32.38998,-2.239002},
{1.819666,31.40248,-2.239002},
{1.819666,29.42749,-2.239002},
{2.374879E-02,28.43999,-2.239002},
{-1.772162,29.42749,-2.239002},
{-1.772162,31.40248,-2.239002},
{.2353699,30.57118,-6.374646},
{-.7412598,31.94804,-4.830194},
{1.643549,30.57118,-4.830194},
{-.7412598,29.19432,-4.830194}};

/*************Face Indeces*********/
const GLubyte base_vertex[43][4]={{0,1,2,3},
{3,4,5,0},
{10,4,3,9},
{10,11,5,4},
{5,11,6,0},
{0,6,7,1},
{1,7,8,2},
{3,2,8,9},
{15,14,13,12},//8
{15,12,17,16},//+
{25,24,13,14},//10
{17,12,41,40},//+
{15,16,32,33},//+
{41,42,43,40},//+
{33,32,35,34},//+
{25,26,27,24},//+
{26,29,30,27},//+
{42,46,45,43},//+
{38,34,35,37},//+
{19,28,25,14},
{25,28,29,26},
{30,31,24,27},
{31,23,13,24},
{13,23,22,12},
{12,22,47,41},
{41,47,46,42},
{40,43,45,44},
{17,40,44,21},
{16,17,21,20},
{32,16,20,36},
{35,32,36,37},
{32,35,37,36},
{33,34,38,39},
{18,15,33,39},
{19,14,15,18},
{31,30,29,28},
{23,31,28,19},
{22,23,19,18},
{36,39,38,37},
{20,18,39,36},
{46,47,44,45},
{47,22,21,44},
{18,20,21,22}};

const GLubyte post_vertex[39][4]={{1,2,14,8},
{2,3,13,14},
{0,1,8,9},
{10,7,0,9},
{7,6,1,0},//4
{6,4,2,1},
{4,5,3,2},
{3,5,12,13},
{8,14,15,11},
{14,13,12,15},
{9,8,11,10},//10
{15,4,6,11},
{12,5,5,15},
{11,6,7,10},//p//13
{27,29,28,24},
{26,27,24,25},
{30,26,25,31},//16
{29,30,31,28},
{24,28,18,22},
{25,24,22,21},
{19,31,25,21},//20
{28,31,19,18},
{18,19,16,17},
{22,18,17,23},
{21,22,23,20},
{17,16,20,23},
{19,21,20,16},//b
{42,39,40,41},//27
{45,44,40,43},
{46,45,43,42},
{42,41,47,46},//30
{44,45,46,47},
{44,47,41,40},
{35,35,36,39},
{35,32,33,34},//34
{34,33,37,36},
{39,36,37,38},
{38,37,33,32},
{32,38,37,33}};

const GLubyte blades_vertex[16][4]={{0,1,2,3},//+
{4,5,6,7},//+
{10,9,8,11},//+
{12,13,16,17},//+
{13,14,15,16},//+
{12,18,19,13},//5
{13,19,20,14},
{14,20,21,15},
{16,15,21,22},
{23,17,16,22},
{23,18,12,17},
{19,18,23,22},
{20,19,22,21},
{24,25,26,255},//+
{24,26,27,255},//+
{25,24,27,255}};//+

/*************Centers of Objects********/
const GLfloat pelvis_center[3]={0.0,6.0,-1.2};
const GLfloat torso_center[3]={0.0,6.0,-1.2};
const GLfloat ruparm_center[3]={-2.250903,5.689374,-1.366034};
const GLfloat rloarm_center[3]={-3.858691,4.284986,.1164428};
const GLfloat rhand_center[3]={-3.858691,.9882874,-1.118951};
const GLfloat luparm_center[3]={2.250903,5.689374,-1.366034};
const GLfloat lloarm_center[3]={3.858691,4.284986,.1164428};
const GLfloat lhand_center[3]={3.858691,.9882874,-1.118951};
const GLfloat turret_center[3]={0.0,7.339221,1.955035};
const GLfloat gauss_center[3]={0.0,9.873913,2.092554};
const GLfloat rthing_center[3]={-2.499872,6.957208,3.890796};
const GLfloat rleg_center[3]={-3.458697,5.053106,2.717719};
const GLfloat rfoot_center[3]={-3.599994,2.8,3.599994};
const GLfloat lthing_center[3]={2.499872,6.957208,3.890796};
const GLfloat lleg_center[3]={3.458697,5.053106,2.717719};
const GLfloat lfoot_center[3]={3.599994,2.8,3.599994};
const GLfloat post_center[3]={.1619934,24.095,5.199585E-02};
const GLfloat blades_center[3]={5.199585E-02,30.57118,-2.0336};

/***************Floor vertices***********/
static GLfloat floorVertices[4][3] = 
{
  { -20.0, 0.0, 20.0 },
  { 20.0, 0.0, 20.0 },
  { 20.0, 0.0, -20.0 },
  { -20.0, 0.0, -20.0 },
};
/******************************************/
#define PI 3.14159265358979323846

float a=45.0,b=45.0,c=0.0; // point for light1_dir
GLfloat  r=0.0,g=0.0,bb=0.0;

/********* Lights definitions *************/
GLfloat light0_pos[]     = {-30.0, 0.0, -10.0, 1.0};
GLfloat light0_ambient[] = {0.5, 0.5, 0.5, 1.0};
GLfloat light0_diffuse[] = {0.5, 0.5, 0.5, 1.0};
GLfloat light0_spec[]    = {1.0, 1.0, 1.0, 1.0};

GLfloat light1_pos[]	 = {-45.0, -45.0, 0.0, 1.0};
GLfloat light1_dir[]	 = {45.0, 45.0, 0.0, 0.0};
GLfloat light1_ambient[] = {r, g, bb, 1.0};
GLfloat light1_diffuse[] = {r, g, bb, 1.0};
GLfloat light1_spec[]	 = {r, g, bb, 1.0};
GLfloat light1_cutoff	 = 60.0;
GLfloat light1_exp		 = 2.0;

GLfloat light2_pos[]	 = {30.0, 0.0, -10.0, 1.0};
GLfloat light2_ambient[] = {0.5, 0.5, 0.5, 1.0};
GLfloat light2_diffuse[] = {0.5, 0.5, 0.5, 1.0};
GLfloat light2_spec[]	 = {1.0, 1.0, 1.0, 1.0};

GLfloat global_amb[]	 = {0.01, 0.01, 0.01, 1.0};

/*********** Material definitions ***************/
GLfloat fido_amb[]		 = {0.5, 0.5, 0.5, 1.0};
GLfloat fido_diff[]		 = {1.0, 1.0, 1.0, 1.0};
GLfloat fido_spec[]		 = {1.0, 1.0, 1.0, 1.0};
GLfloat fido_shine		 = {128.0};

GLfloat floor_amb[]		 = {0.5, 0.5, 0.5, 1.0};
GLfloat floor_diff[]	 = {1.0, 1.0, 1.0, 1.0};
GLfloat floor_spec[]	 = {0.0, 0.0, 0.0, 1.0};
GLfloat floor_shine		 = {20.0};

#endif Fido_Data_H