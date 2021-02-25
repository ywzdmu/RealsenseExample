#include <librealsense2\rs.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

int main(int argc, char* argv[])
{
    rs2::pipeline pl;
    pl.start();

    try
    {
        rs2::rates_printer printer;
        rs2::colorizer color;

        //rs2::frameset data = pl.wait_for_frames().apply_filter(printer).apply_filter(color);
        rs2::frameset data = pl.wait_for_frames().apply_filter(color);

        for (size_t i = 0; i < data.size(); i++)
        {
            rs2::video_frame vf = data[i].as<rs2::video_frame>();
            if (vf != NULL)
            {
                const int width = vf.get_width();
                const int height = vf.get_height();

                cv::Mat image(cv::Size(width, height), CV_8UC3, (void*)data[i].get_data(), cv::Mat::AUTO_STEP);

                cv::imshow(std::to_string(i), image);
            }
        }

        cv::waitKey(0);

        return EXIT_SUCCESS;
    }
    catch (const rs2::error& e)
    {
        std::cerr << "realsense error " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
        pl.stop();
        return EXIT_FAILURE;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        pl.stop();
        return EXIT_FAILURE;
    }
}