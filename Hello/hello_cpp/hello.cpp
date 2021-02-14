#include <librealsense2\rs.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    rs2::pipeline pl;
    pl.start();

    try
    {
        while (true)
        {
            rs2::frameset frame = pl.wait_for_frames();
            rs2::depth_frame depthFrame = frame.get_depth_frame();

            float width = depthFrame.get_width();
            float height = depthFrame.get_height();

            float centerDepth = depthFrame.get_distance(width / 2, height / 2);

            std::cout << "屏幕中心点距离" << centerDepth << "米" << std::endl;
        }

        pl.stop();
        return EXIT_SUCCESS;
    }
    catch (const rs2::error &e)
    {
        std::cerr << "realsense error " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
        pl.stop();
        return EXIT_FAILURE;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        pl.stop();
        return EXIT_FAILURE;
    }
}