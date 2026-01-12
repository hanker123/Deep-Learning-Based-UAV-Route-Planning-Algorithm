#ifndef FAN_MODEL_H_
#define FAN_MODEL_H_


#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <onnx/onnxruntime_cxx_api.h>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/Constants.hpp>
#include <libexif/exif-data.h>
#include <tinyxml2.h>


using namespace std;
using namespace cv;
using namespace GeographicLib;
using namespace tinyxml2;

// 定义常量：地球半径（单位：米）
const double R = 6371000.0;

#define M_PI 3.14159265358979323846

struct Convariance_Matrix
{
    vector<float> cov_xx;
    vector<float> cov_yy;
    vector<float> cov_xy;
};


struct Obb_Res
{
    vector<float> point;
    float label;
    float score;
};

//中心点坐标结构体
struct Center_Point
{
    float x;
    float y;
};

//叶片位置结构体
struct Fan_Info
{
    //判断风机叶片在哪个位置，right?left
    string h;
    // down ? up
    string v;

    //判断风机在哪个象限取值1,2,3,4
    int quadrant;

    // 风机是否进行后向航线标志位，1，2， 默认为1，2是不进行航线
    int f_line_flag;

    //叶片编号
    int n;

    //叶片的中心点坐标
    Center_Point center_point;

    //叶片和中心点锐角夹角
    float degree;

};

//叶片在x,y方向的投影
struct Fan_Projection
{
    vector<float> x;
    vector<float> y;
};


//航点结构体
struct Fan_Air_Point
{
    double lon; //航点经度
    double lat; //航点纬度
    double high; //航点高度
    double air_direction; //航点偏航角
    double camera_direction; //航点camera云台俯仰角度
    double camera_direction_h; //航点camera云台水平偏航角
    double zoom; //航点长焦镜头推焦值，
    int camera_flag; //camera_flag == 1需要拍照航点, camera_flag == 0 不需要拍照航点
};

// 风机基本参数结构体
struct Fan_Blade_Info
{
    float pillar_high; //风机柱子高度
    float fan_length; //叶片长度
    float fan_width; //叶片宽度
    float cabin_length; // 机舱长度
    float cabin_width; //机舱宽度
    float altitude; //风机地表海拔高度
    float lon;//风机地表经度
    float lat;//风机地表维度

};

//函数声明

Convariance_Matrix get_convariance_matrix(vector<vector<float>> boxes);

Obb_Res xywhr2xyxyxyxy(vector<float> obb);

vector<int> probiou(vector<vector<float>>obb1, vector<vector<float>>obb2, float eps);

vector<Obb_Res> model_predict(const string model_path, const string img_path, const string save_img_path, int targetWidth, int targetHeight, float* output_data, vector<int64_t>& outputDims, Mat& dest_image);

double parse_dms(ExifEntry* dms_entry, ExifEntry* ref_entry);

std::pair<double, double> get_gps_coordinates(const std::string& image_path);

double calculate_bearing(double lat_B, double lon_B, double lat_C, double lon_C, double distance_AB);

float cal_radians(Center_Point fan_bbox, Center_Point center_bbox_center);

Fan_Info juge_bbox_ori(Center_Point fan_bbox, Center_Point center_bbox_center, float thread, int n);

std::pair<double, double> calculate_new_coordinates(double lat, double lon, double bearing, double distance);

std::pair<std::pair<double, double>, std::pair<double, double>> cal_offset(
    double lonB, double latB, double lonC, double latC, double offset_f, double offset_b);


std::pair<double, double> calculate_new_coordinates_A(
    double lat_b, double lon_b, double lat_c, double lon_c, double distance_ab, const std::string& flag);

vector<float> fan_air_direction(Fan_Info fan_bbox_info, float b_degree);
double toDegrees(double radians);
vector<float> camera_direction_up_down(double fan_degress);
vector<float> cal_vertical_info(Fan_Info fan_bbox_info, float up_offset, float down_offset);
std::pair<std::pair<double, double>, std::pair<double, double>> cal_new_left_right_B(
    double lonB, double latB, double lonA, double latA, double lonC, double latC, double offset);

Center_Point cal_center_point(vector<float> center_bbox);

bool compareByN(const Fan_Info& a, const Fan_Info& b);

vector<Fan_Air_Point> cal_high_lon_lat(Fan_Info fan_bbox_info, Fan_Projection fan_x_y, Fan_Blade_Info fan_blade_info, double Lon_B, double Lat_B, double Lon_C, double Lat_C, double degree, double camera_direction);

vector<Fan_Air_Point> cal_high_lon_lat(Fan_Info fan_bbox_info, Fan_Projection fan_x_y, Fan_Blade_Info fan_blade_info, double Lon_B, double Lat_B, double Lon_C, double Lat_C, string h_flag, double h_offset, double degree, double camera_direction);

vector<Fan_Air_Point> cal_high_lon_lat_new(Fan_Info fan_bbox_info, Fan_Projection fan_x_y, Fan_Blade_Info fan_blade_info, double Lon_B, double Lat_B, double Lon_C, double Lat_C, string h_flag, double h_offset, double degree, double camera_direction);

vector<vector<Fan_Air_Point>> track_cal(vector<vector<float>> blade_bbox, 
    vector<float> center_bbox, 
    Fan_Blade_Info fan_blade_info, 
    vector<double> Lon_Lat_B,
    vector<double> Lon_Lat_C,
    int fan_add,
    int offset_b,
    int offset_f,
    int offset_f_h,
    float angle_thread,
    int fan_h_offset,
    int center_offset);

void add_waypoint_camera_kml(XMLElement* parent, 
                                        int index, 
                                        double lon, 
                                        double lat, 
                                        double height, 
                                        double air_dir, 
                                        double camera_dir, 
                                        double camera_dir_v,
                                        double zoom_value,
                                        int group_id, 
                                        int camera_group_id, 
                                        int camera_group_start_index, 
                                        int camera_group_end_index);

void add_waypoint_kml(XMLElement* parent, 
                        int index, 
                        double lon, 
                        double lat, 
                        double height, 
                        double air_dir,
                        double camera_dir,
                        double camera_dir_v,
                        double zoom_value, 
                        int group_id);

void add_waypoint_camera(XMLElement* parent, 
                            int index, 
                            double lon, 
                            double lat, 
                            double height, 
                            double air_dir, 
                            double camera_dir,
                            double camera_dir_v,
                            double zoom_value,
                            int group_id, 
                            int camera_group_id, 
                            int camera_group_start_index, 
                            int camera_group_end_index
                            );
void add_waypoint(XMLElement* parent, 
                            int index, 
                            double lon, 
                            double lat, 
                            double height, 
                            double air_dir, 
                            double camera_dir,
                            double camera_dir_v,
                            double zoom_value,
                            int group_id);

void create_dji_kml(const string& filename, const vector<Fan_Air_Point>& data, const string& B_lon_lat_height); 
void create_waylines_wpml(const string& filename, const vector<Fan_Air_Point>& data);

double cal_distance(Fan_Air_Point& point_A, Fan_Air_Point& point_B);

vector<double> run(string B_img_path, 
    string C_img_path,
    string save_img_path,
    string model_path,
    string kml_path,
    string wpml_path,
    float pillar_high,
    float fan_length,
    float fan_width,
    float cabin_length,
    float cabin_width,
    float altitude,
    float lon,
    float lat);

#endif