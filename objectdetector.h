#pragma once

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/core/core.hpp>

#include <string>
#include <utility>

//显示窗口标识
enum ShowImage {
	NotShow = 0,
	ShowSource = 1,
	ShowBinary = 2,
	ShowDrawing = 4,
	ShowAll = ShowSource | ShowBinary | ShowDrawing
};

//矩形过滤器选项
enum RectFilter {
	NotFilter = 0,
	Vertical = 1,
};

class ObjectDetector
{
public:
	//构造函数，参数为名称、显示窗口标识
	ObjectDetector(const std::string & obj_name, int imshow_flag = NotShow,
		bool mixed_hue = false, double scale = 1.0);
	//析构函数，会保存颜色的值为文件
	~ObjectDetector();

	//刷新视频画面，参数为刷新次数
	void refresh_capture(int times = 3);

	//视频宽度、高度
	const double cap_width;
	const double cap_height;

	//调整颜色，按ESC退出，会自动保存
	void adjust_color();
	//按颜色处理图像，参数为处理间隔时间（毫秒）
	int process_by_color(int wait_msec, int rect_filter = NotFilter);

	//返回物体的宽度、高度、位置、是否存在
	int width() const;
	int height() const;
	int postion() const;
	std::pair<int, int> anchor_point() const;
	bool empty() const;
	
	//获取显示窗口标识，同时也可以直接设置（obj.imshow_flag() = ShowBinary)
	int & imshow_flag();
	//返回物体名
	const std::string object_name() const;

private:
	void load();
	void save();

	int x_axis() const;
	int y_axis() const;

	cv::Scalar get_lower_color(bool second_hue = false);
	cv::Scalar get_upper_color(bool second_hue = false);
	cv::Scalar get_avg_color();

	static cv::VideoCapture capture;
	
	std::string obj_name;
	int show_flag;
	bool mixed_flag;
	double scale;

	cv::Vec4i lower_color, upper_color;
	cv::Rect rect;
	
};

