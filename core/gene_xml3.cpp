#include "fan_model.h"

//index作为航点index
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
                                        int camera_group_end_index)
{
    XMLDocument* doc = parent->GetDocument();

    // 创建Placemark元素
    XMLElement* placemark = doc->NewElement("Placemark");
    parent->InsertEndChild(placemark);

    // Point坐标
    XMLElement* point = doc->NewElement("Point");
    placemark->InsertEndChild(point);
    
    XMLElement* coordinates = doc->NewElement("coordinates");
    coordinates->SetText(("\n" + to_string(lon) + ", " + to_string(lat) + "\n").c_str());
    point->InsertEndChild(coordinates);

    // 基本参数
    XMLElement* elem = doc->NewElement("wpml:index");
    elem->SetText(index);
    placemark->InsertEndChild(elem);

    elem = doc->NewElement("wpml:ellipsoidHeight");
    elem->SetText(height);
    placemark->InsertEndChild(elem);

    elem = doc->NewElement("wpml:height");
    elem->SetText(height);
    placemark->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointSpeed");
    elem->SetText("3");
    placemark->InsertEndChild(elem);

    // 航向参数
    XMLElement* heading_param = doc->NewElement("wpml:waypointHeadingParam");
    placemark->InsertEndChild(heading_param);

    elem = doc->NewElement("wpml:waypointHeadingMode");
    elem->SetText("smoothTransition");
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointHeadingAngle");
    elem->SetText(air_dir);
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointPoiPoint");
    elem->SetText("0.000000,0.000000,0.000000");
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointHeadingPathMode");
    elem->SetText("followBadArc");
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointHeadingPoiIndex");
    elem->SetText("0");
    heading_param->InsertEndChild(elem);

    // 转弯参数
    XMLElement* turn_param = doc->NewElement("wpml:waypointTurnParam");
    placemark->InsertEndChild(turn_param);

    elem = doc->NewElement("wpml:waypointTurnMode");
    elem->SetText("toPointAndStopWithDiscontinuityCurvature");
    turn_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointTurnDampingDist");
    elem->SetText("0.2");
    turn_param->InsertEndChild(elem);

    // 全局参数
    elem = doc->NewElement("wpml:useGlobalSpeed");
    elem->SetText("1");
    placemark->InsertEndChild(elem);

    elem = doc->NewElement("wpml:useGlobalTurnParam");
    elem->SetText("1");
    placemark->InsertEndChild(elem);

    elem = doc->NewElement("wpml:useStraightLine");
    elem->SetText("1");
    placemark->InsertEndChild(elem);

    // 动作组
    XMLElement* actionGroup = doc->NewElement("wpml:actionGroup");
    placemark->InsertEndChild(actionGroup);

    elem = doc->NewElement("wpml:actionGroupId");
    elem->SetText(group_id);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupStartIndex");
    elem->SetText(group_id);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupEndIndex");
    elem->SetText(group_id);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupMode");
    elem->SetText("sequence");
    actionGroup->InsertEndChild(elem);

    XMLElement* actionTrigger = doc->NewElement("wpml:actionTrigger");
    actionGroup->InsertEndChild(actionTrigger);

    elem = doc->NewElement("wpml:actionTriggerType");
    elem->SetText("reachPoint");
    actionTrigger->InsertEndChild(elem);


    //新增action zoom焦距缩放
    XMLElement* action = doc->NewElement("wpml:action");
    actionGroup->InsertEndChild(action);

    elem = doc->NewElement("wpml:actionId");
    elem->SetText("0");
    action->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionActuatorFunc");
    elem->SetText("zoom");
    action->InsertEndChild(elem);

    XMLElement* param = doc->NewElement("wpml:actionActuatorFuncParam");
    action->InsertEndChild(param);

    elem = doc->NewElement("wpml:focalLength");
    elem->SetText(zoom_value);
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:isUseFocalFactor");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    param->InsertEndChild(elem);

    // 动作2: gimbalRotate 垂直方向
    action = doc->NewElement("wpml:action");
    actionGroup->InsertEndChild(action);

    elem = doc->NewElement("wpml:actionId");
    elem->SetText("0");
    action->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionActuatorFunc");
    elem->SetText("gimbalRotate");
    action->InsertEndChild(elem);

    param = doc->NewElement("wpml:actionActuatorFuncParam");
    action->InsertEndChild(param);

    elem = doc->NewElement("wpml:gimbalRotateMode");
    elem->SetText("absoluteAngle");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalPitchRotateEnable");
    elem->SetText("1");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalPitchRotateAngle");
    elem->SetText(camera_dir);
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRollRotateEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRollRotateAngle");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalYawRotateEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalYawRotateAngle");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRotateTimeEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRotateTime");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    param->InsertEndChild(elem);


    // 动作3: gimbalRotate 水平方向
    action = doc->NewElement("wpml:action");
    actionGroup->InsertEndChild(action);

    elem = doc->NewElement("wpml:actionId");
    elem->SetText("0");
    action->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionActuatorFunc");
    elem->SetText("gimbalRotate");
    action->InsertEndChild(elem);

    param = doc->NewElement("wpml:actionActuatorFuncParam");
    action->InsertEndChild(param);

    elem = doc->NewElement("wpml:gimbalRotateMode");
    elem->SetText("absoluteAngle");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalPitchRotateEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalPitchRotateAngle");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRollRotateEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRollRotateAngle");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalYawRotateEnable");
    elem->SetText("1");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalYawRotateAngle");
    elem->SetText(camera_dir_v);
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRotateTimeEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRotateTime");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    param->InsertEndChild(elem);


    //等间隔拍照
    actionGroup = doc->NewElement("wpml:actionGroup");
    placemark->InsertEndChild(actionGroup);

    elem = doc->NewElement("wpml:actionGroupId");
    elem->SetText(camera_group_id);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupStartIndex");
    elem->SetText(camera_group_start_index);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupEndIndex");
    elem->SetText(camera_group_end_index);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupMode");
    elem->SetText("sequence");
    actionGroup->InsertEndChild(elem);

    actionTrigger = doc->NewElement("wpml:actionTrigger");
    actionGroup->InsertEndChild(actionTrigger);

    elem = doc->NewElement("wpml:actionTriggerType");
    elem->SetText("multipleTiming");
    actionTrigger->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionTriggerParam");
    elem->SetText("1");
    actionTrigger->InsertEndChild(elem);

    //拍照动作
    action = doc->NewElement("wpml:action");
    actionGroup->InsertEndChild(action);

    elem = doc->NewElement("wpml:actionId");
    elem->SetText("0");
    action->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionActuatorFunc");
    elem->SetText("takePhoto");
    action->InsertEndChild(elem);

    param = doc->NewElement("wpml:actionActuatorFuncParam");
    action->InsertEndChild(param);

    elem = doc->NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:useGlobalPayloadLensIndex");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:isRisky");
    elem->SetText("0");
    placemark->InsertEndChild(elem);
    return;

}


void add_waypoint_kml(XMLElement* parent, 
                        int index, 
                        double lon, 
                        double lat, 
                        double height, 
                        double air_dir, 
                        double camera_dir, 
                        double camera_dir_v,
                        double zoom_value, 
                        int group_id) {
    XMLDocument* doc = parent->GetDocument();

    // 创建Placemark元素
    XMLElement* placemark = doc->NewElement("Placemark");
    parent->InsertEndChild(placemark);

    // Point坐标
    XMLElement* point = doc->NewElement("Point");
    placemark->InsertEndChild(point);
    
    XMLElement* coordinates = doc->NewElement("coordinates");
    coordinates->SetText(("\n" + to_string(lon) + ", " + to_string(lat) + "\n").c_str());
    point->InsertEndChild(coordinates);

    // 基本参数
    XMLElement* elem = doc->NewElement("wpml:index");
    elem->SetText(index);
    placemark->InsertEndChild(elem);

    elem = doc->NewElement("wpml:ellipsoidHeight");
    elem->SetText(height);
    placemark->InsertEndChild(elem);

    elem = doc->NewElement("wpml:height");
    elem->SetText(height);
    placemark->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointSpeed");
    elem->SetText("3");
    placemark->InsertEndChild(elem);

    // 航向参数
    XMLElement* heading_param = doc->NewElement("wpml:waypointHeadingParam");
    placemark->InsertEndChild(heading_param);

    elem = doc->NewElement("wpml:waypointHeadingMode");
    elem->SetText("smoothTransition");
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointHeadingAngle");
    elem->SetText(air_dir);
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointPoiPoint");
    elem->SetText("0.000000,0.000000,0.000000");
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointHeadingPathMode");
    elem->SetText("followBadArc");
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointHeadingPoiIndex");
    elem->SetText("0");
    heading_param->InsertEndChild(elem);

    // 转弯参数
    XMLElement* turn_param = doc->NewElement("wpml:waypointTurnParam");
    placemark->InsertEndChild(turn_param);

    elem = doc->NewElement("wpml:waypointTurnMode");
    elem->SetText("toPointAndStopWithDiscontinuityCurvature");
    turn_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointTurnDampingDist");
    elem->SetText("0.2");
    turn_param->InsertEndChild(elem);

    // 全局参数
    elem = doc->NewElement("wpml:useGlobalSpeed");
    elem->SetText("1");
    placemark->InsertEndChild(elem);

    elem = doc->NewElement("wpml:useGlobalTurnParam");
    elem->SetText("1");
    placemark->InsertEndChild(elem);

    elem = doc->NewElement("wpml:useStraightLine");
    elem->SetText("1");
    placemark->InsertEndChild(elem);

    // 动作组
    XMLElement* actionGroup = doc->NewElement("wpml:actionGroup");
    placemark->InsertEndChild(actionGroup);

    elem = doc->NewElement("wpml:actionGroupId");
    elem->SetText(group_id);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupStartIndex");
    elem->SetText(group_id);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupEndIndex");
    elem->SetText(group_id);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupMode");
    elem->SetText("sequence");
    actionGroup->InsertEndChild(elem);

    XMLElement* actionTrigger = doc->NewElement("wpml:actionTrigger");
    actionGroup->InsertEndChild(actionTrigger);

    elem = doc->NewElement("wpml:actionTriggerType");
    elem->SetText("reachPoint");
    actionTrigger->InsertEndChild(elem);


    //新增action zoom焦距缩放
    XMLElement* action = doc->NewElement("wpml:action");
    actionGroup->InsertEndChild(action);

    elem = doc->NewElement("wpml:actionId");
    elem->SetText("0");
    action->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionActuatorFunc");
    elem->SetText("zoom");
    action->InsertEndChild(elem);

    XMLElement* param = doc->NewElement("wpml:actionActuatorFuncParam");
    action->InsertEndChild(param);

    elem = doc->NewElement("wpml:focalLength");
    elem->SetText(zoom_value);
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:isUseFocalFactor");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    param->InsertEndChild(elem);


    // 动作2: gimbalRotate
    action = doc->NewElement("wpml:action");
    actionGroup->InsertEndChild(action);

    elem = doc->NewElement("wpml:actionId");
    elem->SetText("0");
    action->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionActuatorFunc");
    elem->SetText("gimbalRotate");
    action->InsertEndChild(elem);

    param = doc->NewElement("wpml:actionActuatorFuncParam");
    action->InsertEndChild(param);

    elem = doc->NewElement("wpml:gimbalRotateMode");
    elem->SetText("absoluteAngle");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalPitchRotateEnable");
    elem->SetText("1");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalPitchRotateAngle");
    elem->SetText(camera_dir);
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRollRotateEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRollRotateAngle");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalYawRotateEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalYawRotateAngle");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRotateTimeEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRotateTime");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    param->InsertEndChild(elem);

    // 动作3: gimbalRotate 水平方向
    action = doc->NewElement("wpml:action");
    actionGroup->InsertEndChild(action);

    elem = doc->NewElement("wpml:actionId");
    elem->SetText("0");
    action->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionActuatorFunc");
    elem->SetText("gimbalRotate");
    action->InsertEndChild(elem);

    param = doc->NewElement("wpml:actionActuatorFuncParam");
    action->InsertEndChild(param);

    elem = doc->NewElement("wpml:gimbalRotateMode");
    elem->SetText("absoluteAngle");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalPitchRotateEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalPitchRotateAngle");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRollRotateEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRollRotateAngle");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalYawRotateEnable");
    elem->SetText("1");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalYawRotateAngle");
    elem->SetText(camera_dir_v);
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRotateTimeEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRotateTime");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:isRisky");
    elem->SetText("0");
    placemark->InsertEndChild(elem);
    return;
}

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
                            )
{

    XMLDocument* doc = parent->GetDocument();

    // 创建Placemark元素
    XMLElement* placemark = doc->NewElement("Placemark");
    parent->InsertEndChild(placemark);

    // 创建Point坐标
    XMLElement* point = doc->NewElement("Point");
    placemark->InsertEndChild(point);

    XMLElement* coordinates = doc->NewElement("coordinates");
    coordinates->SetText(("\n" + to_string(lon) + ", " + to_string(lat) + "\n").c_str());
    point->InsertEndChild(coordinates);

    // 基本参数
    XMLElement* elem = doc->NewElement("wpml:index");
    elem->SetText(index);
    placemark->InsertEndChild(elem);

    elem = doc->NewElement("wpml:executeHeight");
    elem->SetText(height);
    placemark->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointSpeed");
    elem->SetText("3");
    placemark->InsertEndChild(elem);

    // 航向参数
    XMLElement* heading_param = doc->NewElement("wpml:waypointHeadingParam");
    placemark->InsertEndChild(heading_param);

    elem = doc->NewElement("wpml:waypointHeadingMode");
    elem->SetText("smoothTransition");
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointHeadingAngle");
    elem->SetText(air_dir);
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointPoiPoint");
    elem->SetText("0.000000,0.000000,0.000000");
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointHeadingAngleEnable");
    elem->SetText(1);
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointHeadingPathMode");
    elem->SetText("followBadArc");
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointHeadingPoiIndex");
    elem->SetText("0");
    heading_param->InsertEndChild(elem);

    // 转弯参数
    XMLElement* turn_param = doc->NewElement("wpml:waypointTurnParam");
    placemark->InsertEndChild(turn_param);

    elem = doc->NewElement("wpml:waypointTurnMode");
    elem->SetText("toPointAndStopWithDiscontinuityCurvature");
    turn_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointTurnDampingDist");
    elem->SetText("0");
    turn_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:useStraightLine");
    elem->SetText("1");
    placemark->InsertEndChild(elem);

    // 动作组
    XMLElement* actionGroup = doc->NewElement("wpml:actionGroup");
    placemark->InsertEndChild(actionGroup);

    elem = doc->NewElement("wpml:actionGroupId");
    elem->SetText(group_id);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupStartIndex");
    elem->SetText(group_id);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupEndIndex");
    elem->SetText(group_id);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupMode");
    elem->SetText("sequence");
    actionGroup->InsertEndChild(elem);

    XMLElement* actionTrigger = doc->NewElement("wpml:actionTrigger");
    actionGroup->InsertEndChild(actionTrigger);

    elem = doc->NewElement("wpml:actionTriggerType");
    elem->SetText("reachPoint");
    actionTrigger->InsertEndChild(elem);


    //新增action zoom焦距缩放
    XMLElement* action = doc->NewElement("wpml:action");
    actionGroup->InsertEndChild(action);

    elem = doc->NewElement("wpml:actionId");
    elem->SetText("0");
    action->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionActuatorFunc");
    elem->SetText("zoom");
    action->InsertEndChild(elem);

    XMLElement* param = doc->NewElement("wpml:actionActuatorFuncParam");
    action->InsertEndChild(param);

    elem = doc->NewElement("wpml:focalLength");
    elem->SetText(zoom_value);
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:isUseFocalFactor");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    param->InsertEndChild(elem);


    // 动作2: gimbalRotate
    action = doc->NewElement("wpml:action");
    actionGroup->InsertEndChild(action);

    elem = doc->NewElement("wpml:actionId");
    elem->SetText("1");
    action->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionActuatorFunc");
    elem->SetText("gimbalRotate");
    action->InsertEndChild(elem);

    param = doc->NewElement("wpml:actionActuatorFuncParam");
    action->InsertEndChild(param);

    elem = doc->NewElement("wpml:gimbalRotateMode");
    elem->SetText("absoluteAngle");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalPitchRotateEnable");
    elem->SetText("1");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalPitchRotateAngle");
    elem->SetText(camera_dir);
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRollRotateEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRollRotateAngle");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalYawRotateEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalYawRotateAngle");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRotateTimeEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRotateTime");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    param->InsertEndChild(elem);

    // 动作3: gimbalRotate 水平方向
    action = doc->NewElement("wpml:action");
    actionGroup->InsertEndChild(action);

    elem = doc->NewElement("wpml:actionId");
    elem->SetText("2");
    action->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionActuatorFunc");
    elem->SetText("gimbalRotate");
    action->InsertEndChild(elem);

    param = doc->NewElement("wpml:actionActuatorFuncParam");
    action->InsertEndChild(param);

    elem = doc->NewElement("wpml:gimbalRotateMode");
    elem->SetText("absoluteAngle");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalPitchRotateEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalPitchRotateAngle");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRollRotateEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRollRotateAngle");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalYawRotateEnable");
    elem->SetText("1");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalYawRotateAngle");
    elem->SetText(camera_dir_v);
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRotateTimeEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRotateTime");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    param->InsertEndChild(elem);


    //等间隔拍照
    actionGroup = doc->NewElement("wpml:actionGroup");
    placemark->InsertEndChild(actionGroup);

    elem = doc->NewElement("wpml:actionGroupId");
    elem->SetText(camera_group_id);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupStartIndex");
    elem->SetText(camera_group_start_index);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupEndIndex");
    elem->SetText(camera_group_end_index);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupMode");
    elem->SetText("sequence");
    actionGroup->InsertEndChild(elem);

    actionTrigger = doc->NewElement("wpml:actionTrigger");
    actionGroup->InsertEndChild(actionTrigger);

    elem = doc->NewElement("wpml:actionTriggerType");
    elem->SetText("multipleTiming");
    actionTrigger->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionTriggerParam");
    elem->SetText("1");
    actionTrigger->InsertEndChild(elem);

    //拍照动作
    action = doc->NewElement("wpml:action");
    actionGroup->InsertEndChild(action);

    elem = doc->NewElement("wpml:actionId");
    elem->SetText("0");
    action->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionActuatorFunc");
    elem->SetText("takePhoto");
    action->InsertEndChild(elem);

    param = doc->NewElement("wpml:actionActuatorFuncParam");
    action->InsertEndChild(param);

    elem = doc->NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:useGlobalPayloadLensIndex");
    elem->SetText("0");
    param->InsertEndChild(elem);


    // 云台参数
    XMLElement* gimbal_param = doc->NewElement("wpml:waypointGimbalHeadingParam");
    placemark->InsertEndChild(gimbal_param);

    elem = doc->NewElement("wpml:waypointGimbalPitchAngle");
    elem->SetText("0");
    gimbal_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointGimbalYawAngle");
    elem->SetText("0");
    gimbal_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:isRisky");
    elem->SetText("0");
    placemark->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointWorkType");
    elem->SetText("0");
    placemark->InsertEndChild(elem);


    return;
}




//wpml文件生成
void add_waypoint(XMLElement* parent, 
                            int index, 
                            double lon, 
                            double lat, 
                            double height, 
                            double air_dir, 
                            double camera_dir,
                            double camera_dir_v,
                            double zoom_value,
                            int group_id) {
    XMLDocument* doc = parent->GetDocument();

    // 创建Placemark元素
    XMLElement* placemark = doc->NewElement("Placemark");
    parent->InsertEndChild(placemark);

    // 创建Point坐标
    XMLElement* point = doc->NewElement("Point");
    placemark->InsertEndChild(point);

    XMLElement* coordinates = doc->NewElement("coordinates");
    coordinates->SetText(("\n" + to_string(lon) + ", " + to_string(lat) + "\n").c_str());
    point->InsertEndChild(coordinates);

    // 基本参数
    XMLElement* elem = doc->NewElement("wpml:index");
    elem->SetText(index);
    placemark->InsertEndChild(elem);

    elem = doc->NewElement("wpml:executeHeight");
    elem->SetText(height);
    placemark->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointSpeed");
    elem->SetText("3");
    placemark->InsertEndChild(elem);

    // 航向参数
    XMLElement* heading_param = doc->NewElement("wpml:waypointHeadingParam");
    placemark->InsertEndChild(heading_param);

    elem = doc->NewElement("wpml:waypointHeadingMode");
    elem->SetText("smoothTransition");
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointHeadingAngle");
    elem->SetText(air_dir);
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointPoiPoint");
    elem->SetText("0.000000,0.000000,0.000000");
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointHeadingAngleEnable");
    elem->SetText(1);
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointHeadingPathMode");
    elem->SetText("followBadArc");
    heading_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointHeadingPoiIndex");
    elem->SetText("0");
    heading_param->InsertEndChild(elem);

    // 转弯参数
    XMLElement* turn_param = doc->NewElement("wpml:waypointTurnParam");
    placemark->InsertEndChild(turn_param);

    elem = doc->NewElement("wpml:waypointTurnMode");
    elem->SetText("toPointAndStopWithDiscontinuityCurvature");
    turn_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointTurnDampingDist");
    elem->SetText("0");
    turn_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:useStraightLine");
    elem->SetText("1");
    placemark->InsertEndChild(elem);

    // 动作组
    XMLElement* actionGroup = doc->NewElement("wpml:actionGroup");
    placemark->InsertEndChild(actionGroup);

    elem = doc->NewElement("wpml:actionGroupId");
    elem->SetText(group_id);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupStartIndex");
    elem->SetText(group_id);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupEndIndex");
    elem->SetText(group_id);
    actionGroup->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionGroupMode");
    elem->SetText("sequence");
    actionGroup->InsertEndChild(elem);

    XMLElement* actionTrigger = doc->NewElement("wpml:actionTrigger");
    actionGroup->InsertEndChild(actionTrigger);

    elem = doc->NewElement("wpml:actionTriggerType");
    elem->SetText("reachPoint");
    actionTrigger->InsertEndChild(elem);

    //新增action zoom焦距缩放
    XMLElement* action = doc->NewElement("wpml:action");
    actionGroup->InsertEndChild(action);

    elem = doc->NewElement("wpml:actionId");
    elem->SetText("0");
    action->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionActuatorFunc");
    elem->SetText("zoom");
    action->InsertEndChild(elem);

    XMLElement* param = doc->NewElement("wpml:actionActuatorFuncParam");
    action->InsertEndChild(param);

    elem = doc->NewElement("wpml:focalLength");
    elem->SetText(zoom_value);
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:isUseFocalFactor");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    param->InsertEndChild(elem);

    // 动作2: gimbalRotate
    action = doc->NewElement("wpml:action");
    actionGroup->InsertEndChild(action);

    elem = doc->NewElement("wpml:actionId");
    elem->SetText("1");
    action->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionActuatorFunc");
    elem->SetText("gimbalRotate");
    action->InsertEndChild(elem);

    param = doc->NewElement("wpml:actionActuatorFuncParam");
    action->InsertEndChild(param);

    elem = doc->NewElement("wpml:gimbalRotateMode");
    elem->SetText("absoluteAngle");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalPitchRotateEnable");
    elem->SetText("1");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalPitchRotateAngle");
    elem->SetText(camera_dir);
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRollRotateEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRollRotateAngle");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalYawRotateEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalYawRotateAngle");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRotateTimeEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRotateTime");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    param->InsertEndChild(elem);

    // 动作3: gimbalRotate 水平方向
    action = doc->NewElement("wpml:action");
    actionGroup->InsertEndChild(action);

    elem = doc->NewElement("wpml:actionId");
    elem->SetText("2");
    action->InsertEndChild(elem);

    elem = doc->NewElement("wpml:actionActuatorFunc");
    elem->SetText("gimbalRotate");
    action->InsertEndChild(elem);

    param = doc->NewElement("wpml:actionActuatorFuncParam");
    action->InsertEndChild(param);

    elem = doc->NewElement("wpml:gimbalRotateMode");
    elem->SetText("absoluteAngle");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalPitchRotateEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalPitchRotateAngle");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRollRotateEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRollRotateAngle");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalYawRotateEnable");
    elem->SetText("1");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalYawRotateAngle");
    elem->SetText(camera_dir_v);
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRotateTimeEnable");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:gimbalRotateTime");
    elem->SetText("0");
    param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    param->InsertEndChild(elem);

    // 云台参数
    XMLElement* gimbal_param = doc->NewElement("wpml:waypointGimbalHeadingParam");
    placemark->InsertEndChild(gimbal_param);

    elem = doc->NewElement("wpml:waypointGimbalPitchAngle");
    elem->SetText("0");
    gimbal_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointGimbalYawAngle");
    elem->SetText("0");
    gimbal_param->InsertEndChild(elem);

    elem = doc->NewElement("wpml:isRisky");
    elem->SetText("0");
    placemark->InsertEndChild(elem);

    elem = doc->NewElement("wpml:waypointWorkType");
    elem->SetText("0");
    placemark->InsertEndChild(elem);
    return;
}


void create_dji_kml(const string& filename, const vector<Fan_Air_Point>& data,
                   const string& B_lon_lat_height = "41.09455944444445,112.59469955555555,2028") {
    XMLDocument doc;
    doc.InsertEndChild(doc.NewDeclaration());

    // 创建根元素
    XMLElement* kml = doc.NewElement("kml");
    kml->SetAttribute("xmlns", "http://www.opengis.net/kml/2.2");
    kml->SetAttribute("xmlns:wpml", "http://www.dji.com/wpmz/1.0.6");
    doc.InsertEndChild(kml);

    // 创建Document元素
    XMLElement* document = doc.NewElement("Document");
    kml->InsertEndChild(document);

    // 添加作者和时间戳
    XMLElement* elem = doc.NewElement("wpml:author");
    elem->SetText("13081515316");
    document->InsertEndChild(elem);

    elem = doc.NewElement("wpml:createTime");
    elem->SetText("1742529933669");
    document->InsertEndChild(elem);

    elem = doc.NewElement("wpml:updateTime");
    elem->SetText("1742530187947");
    document->InsertEndChild(elem);

    // 创建missionConfig
    XMLElement* mission_config = doc.NewElement("wpml:missionConfig");
    document->InsertEndChild(mission_config);

    elem = doc.NewElement("wpml:flyToWaylineMode");
    elem->SetText("safely");
    mission_config->InsertEndChild(elem);

    elem = doc.NewElement("wpml:finishAction");
    elem->SetText("goHome");
    mission_config->InsertEndChild(elem);

    elem = doc.NewElement("wpml:exitOnRCLost");
    elem->SetText("goContinue");
    mission_config->InsertEndChild(elem);

    elem = doc.NewElement("wpml:executeRCLostAction");
    elem->SetText("goBack");
    mission_config->InsertEndChild(elem);

    elem = doc.NewElement("wpml:takeOffSecurityHeight");
    elem->SetText("20");
    mission_config->InsertEndChild(elem);

    elem = doc.NewElement("wpml:takeOffRefPoint");
    elem->SetText(B_lon_lat_height.c_str());
    mission_config->InsertEndChild(elem);

    // elem = doc.NewElement("wpml:takeOffRefPointAGLHeight");
    // elem->SetText("0");
    // mission_config->InsertEndChild(elem);

    elem = doc.NewElement("wpml:globalTransitionalSpeed");
    elem->SetText("15");
    mission_config->InsertEndChild(elem);

    // elem = doc.NewElement("wpml:globalRTHHeight");
    // elem->SetText("80");
    // mission_config->InsertEndChild(elem);

    // 添加droneInfo
    XMLElement* drone_info = doc.NewElement("wpml:droneInfo");
    mission_config->InsertEndChild(drone_info);

    elem = doc.NewElement("wpml:droneEnumValue");
    elem->SetText("89");
    drone_info->InsertEndChild(elem);

    elem = doc.NewElement("wpml:droneSubEnumValue");
    elem->SetText("0");
    drone_info->InsertEndChild(elem);

    // elem = doc.NewElement("wpml:waylineAvoidLimitAreaMode");
    // elem->SetText("0");
    // mission_config->InsertEndChild(elem);

    // 添加payloadInfo
    XMLElement* payload_info = doc.NewElement("wpml:payloadInfo");
    mission_config->InsertEndChild(payload_info);

    elem = doc.NewElement("wpml:payloadEnumValue");
    elem->SetText("82");
    payload_info->InsertEndChild(elem);

    elem = doc.NewElement("wpml:payloadSubEnumValue");
    elem->SetText("0");
    payload_info->InsertEndChild(elem);

    elem = doc.NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    payload_info->InsertEndChild(elem);

    // 创建Folder
    XMLElement* folder = doc.NewElement("Folder");
    document->InsertEndChild(folder);

    elem = doc.NewElement("wpml:templateType");
    elem->SetText("waypoint");
    folder->InsertEndChild(elem);

    elem = doc.NewElement("wpml:templateId");
    elem->SetText("0");
    folder->InsertEndChild(elem);

    // 坐标系参数
    XMLElement* coord_sys = doc.NewElement("wpml:waylineCoordinateSysParam");
    folder->InsertEndChild(coord_sys);

    elem = doc.NewElement("wpml:coordinateMode");
    elem->SetText("WGS84");
    coord_sys->InsertEndChild(elem);

    elem = doc.NewElement("wpml:heightMode");
    elem->SetText("relativeToStartPoint");
    coord_sys->InsertEndChild(elem);

    elem = doc.NewElement("wpml:positioningType");
    elem->SetText("GPS");
    coord_sys->InsertEndChild(elem);

    // 全局飞行参数
    elem = doc.NewElement("wpml:autoFlightSpeed");
    elem->SetText("3");
    folder->InsertEndChild(elem);

    elem = doc.NewElement("wpml:globalHeight");
    elem->SetText("100");
    folder->InsertEndChild(elem);

    elem = doc.NewElement("wpml:caliFlightEnable");
    elem->SetText("0");
    folder->InsertEndChild(elem);

    elem = doc.NewElement("wpml:gimbalPitchMode");
    elem->SetText("manual");
    folder->InsertEndChild(elem);

    // 全局航向参数
    XMLElement* global_heading = doc.NewElement("wpml:globalWaypointHeadingParam");
    folder->InsertEndChild(global_heading);

    elem = doc.NewElement("wpml:waypointHeadingMode");
    elem->SetText("followWayline");
    global_heading->InsertEndChild(elem);

    elem = doc.NewElement("wpml:waypointHeadingAngle");
    elem->SetText("0");
    global_heading->InsertEndChild(elem);

    elem = doc.NewElement("wpml:waypointPoiPoint");
    elem->SetText("0.000000,0.000000,0.000000");
    global_heading->InsertEndChild(elem);

    // elem = doc.NewElement("wpml:waypointHeadingPathMode");
    // elem->SetText("followBadArc");
    // global_heading->InsertEndChild(elem);

    elem = doc.NewElement("wpml:waypointHeadingPoiIndex");
    elem->SetText("0");
    global_heading->InsertEndChild(elem);

    elem = doc.NewElement("wpml:globalWaypointTurnMode");
    elem->SetText("toPointAndStopWithDiscontinuityCurvature");
    folder->InsertEndChild(elem);

    elem = doc.NewElement("wpml:globalUseStraightLine");
    elem->SetText("1");
    folder->InsertEndChild(elem);

   

    //添加第一个航点
    // add_waypoint_camera_kml(folder, 0, data[0].lon, data[0].lat, data[0].high, data[0].air_direction, data[0].camera_direction, data[0].camera_direction_h, data[0].zoom, 0, data.size(), 0, data.size()-1);
    
     // 添加剩余航点
    int base_camera_group_id = data.size();
    int camera_flag_index = 0;
    for(size_t i = 0; i < data.size() - 1; ++i) {
        
        if (data[i].camera_flag == 1 && data[i+1].camera_flag == 1)
        {
            camera_flag_index = camera_flag_index + 1;
            if ((i>=1) && (data[i-1].camera_flag == 1) && (data[i+2].camera_flag == 1))
            {
                add_waypoint_kml(folder, i, 
                    data[i].lon, data[i].lat,
                    data[i].high,
                    data[i].air_direction,
                    data[i].camera_direction,
                    data[i].camera_direction_h,
                    data[i].zoom,
                    i);
            }
            else
            {
                add_waypoint_camera_kml(folder, i,
                                    data[i].lon, data[i].lat,
                                    data[i].high,
                                    data[i].air_direction,
                                    data[i].camera_direction,
                                    data[i].camera_direction_h,
                                    data[i].zoom,
                                    i,
                                    base_camera_group_id + camera_flag_index,
                                    i,
                                    i+1);
            }
            
        }
        else{
             add_waypoint_kml(folder, i, 
                    data[i].lon, data[i].lat,
                    data[i].high,
                    data[i].air_direction,
                    data[i].camera_direction,
                    data[i].camera_direction_h,
                    data[i].zoom,
                    i);
        }

       
    }
    // 添加payloadParam
    XMLElement* payload_param = doc.NewElement("wpml:payloadParam");
    folder->InsertEndChild(payload_param);

    elem = doc.NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    payload_param->InsertEndChild(elem);

    elem = doc.NewElement("wpml:meteringMode");
    elem->SetText("average");
    payload_param->InsertEndChild(elem);

    elem = doc.NewElement("wpml:dewarpingEnable");
    elem->SetText("0");
    payload_param->InsertEndChild(elem);

    elem = doc.NewElement("wpml:returnMode");
    elem->SetText("singleReturnStrongest");
    payload_param->InsertEndChild(elem);

    elem = doc.NewElement("wpml:samplingRate");
    elem->SetText("240000");
    payload_param->InsertEndChild(elem);

    elem = doc.NewElement("wpml:scanningMode");
    elem->SetText("nonRepetitive");
    payload_param->InsertEndChild(elem);

    elem = doc.NewElement("wpml:modelColoringEnable");
    elem->SetText("0");
    payload_param->InsertEndChild(elem);

    XMLError eResult = doc.SaveFile(filename.c_str());
}

void create_waylines_wpml(const string& filename, const vector<Fan_Air_Point>& data) {
    XMLDocument doc;
    doc.InsertEndChild(doc.NewDeclaration());

    // 创建根元素
    XMLElement* kml = doc.NewElement("kml");
    kml->SetAttribute("xmlns", "http://www.opengis.net/kml/2.2");
    kml->SetAttribute("xmlns:wpml", "http://www.dji.com/wpmz/1.0.6");
    doc.InsertEndChild(kml);

    // 创建Document元素
    XMLElement* document = doc.NewElement("Document");
    kml->InsertEndChild(document);

    // 创建missionConfig
    XMLElement* mission_config = doc.NewElement("wpml:missionConfig");
    document->InsertEndChild(mission_config);

    XMLElement* elem = doc.NewElement("wpml:flyToWaylineMode");
    elem->SetText("safely");
    mission_config->InsertEndChild(elem);

    elem = doc.NewElement("wpml:finishAction");
    elem->SetText("goHome");
    mission_config->InsertEndChild(elem);

    elem = doc.NewElement("wpml:exitOnRCLost");
    elem->SetText("executeLostAction");
    mission_config->InsertEndChild(elem);

    elem = doc.NewElement("wpml:executeRCLostAction");
    elem->SetText("goBack");
    mission_config->InsertEndChild(elem);

    elem = doc.NewElement("wpml:takeOffSecurityHeight");
    elem->SetText("20");
    mission_config->InsertEndChild(elem);

    elem = doc.NewElement("wpml:globalTransitionalSpeed");
    elem->SetText("15");
    mission_config->InsertEndChild(elem);

    // 添加droneInfo
    XMLElement* drone_info = doc.NewElement("wpml:droneInfo");
    mission_config->InsertEndChild(drone_info);

    elem = doc.NewElement("wpml:droneEnumValue");
    elem->SetText("89");
    drone_info->InsertEndChild(elem);

    elem = doc.NewElement("wpml:droneSubEnumValue");
    elem->SetText("0");
    drone_info->InsertEndChild(elem);

    // elem = doc.NewElement("wpml:waylineAvoidLimitAreaMode");
    // elem->SetText("0");
    // mission_config->InsertEndChild(elem);

    // 添加payloadInfo
    XMLElement* payload_info = doc.NewElement("wpml:payloadInfo");
    mission_config->InsertEndChild(payload_info);

    elem = doc.NewElement("wpml:payloadEnumValue");
    elem->SetText("82");
    payload_info->InsertEndChild(elem);

    elem = doc.NewElement("wpml:payloadSubEnumValue");
    elem->SetText("0");
    payload_info->InsertEndChild(elem);

    elem = doc.NewElement("wpml:payloadPositionIndex");
    elem->SetText("0");
    payload_info->InsertEndChild(elem);

    // 创建Folder
    XMLElement* folder = doc.NewElement("Folder");
    document->InsertEndChild(folder);

    elem = doc.NewElement("wpml:templateId");
    elem->SetText("0");
    folder->InsertEndChild(elem);

    elem = doc.NewElement("wpml:executeHeightMode");
    elem->SetText("relativeToStartPoint");
    folder->InsertEndChild(elem);

    elem = doc.NewElement("wpml:waylineId");
    elem->SetText("0");
    folder->InsertEndChild(elem);

    elem = doc.NewElement("wpml:distance");
    elem->SetText("45.9589042663574");
    folder->InsertEndChild(elem);

    elem = doc.NewElement("wpml:duration");
    elem->SetText("14.9455051422119");
    folder->InsertEndChild(elem);

    elem = doc.NewElement("wpml:autoFlightSpeed");
    elem->SetText("3");
    folder->InsertEndChild(elem);

    //添加第一个航点
    // add_waypoint_camera(folder, 0, data[0].lon, data[0].lat, data[0].high, data[0].air_direction, data[0].camera_direction, data[0].camera_direction_h, data[0].zoom, 0, data.size(), 0, data.size()-1);

    // 添加剩余航点
    int base_camera_group_id = data.size();
    int camera_flag_index = 0;

    for (size_t i = 0; i < data.size() - 1; ++i) {
        if (data[i].camera_flag == 1 && data[i+1].camera_flag == 1)
        {
            camera_flag_index = camera_flag_index + 1;
            if ((i>=1) && data[i-1].camera_flag == 1 && data[i+2].camera_flag == 1)
            {
                add_waypoint(folder, i, 
                    data[i].lon, data[i].lat,
                    data[i].high,
                    data[i].air_direction,
                    data[i].camera_direction,
                    data[i].camera_direction_h,
                    data[i].zoom,
                    i);
            }
            else
            {
                add_waypoint_camera(folder, i,
                                    data[i].lon, data[i].lat,
                                    data[i].high,
                                    data[i].air_direction,
                                    data[i].camera_direction,
                                    data[i].camera_direction_h,
                                    data[i].zoom,
                                    i,
                                    base_camera_group_id + camera_flag_index,
                                    i,
                                    i+1);
            }
            
        }
        else{
             add_waypoint(folder, i, 
                    data[i].lon, data[i].lat,
                    data[i].high,
                    data[i].air_direction,
                    data[i].camera_direction,
                    data[i].camera_direction_h,
                    data[i].zoom,
                    i);
        }
    }

    // 保存文件
    XMLError eResult = doc.SaveFile(filename.c_str());
}

// int main() {
//     vector<WaypointData> data = {
//         {114.03435840421778, 25.433167605700405, 50.82815444611505, 0.0, -45.0},
//         {114.03435283801107, 25.43316783520919, 51.65630889223011, 180.0, 45.0}
//     };

//     create_dji_kml("output.kml", data);

// }