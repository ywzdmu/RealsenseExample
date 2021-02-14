import pyrealsense2 as rs

pl = rs.pipeline()
pl.start()

try:
    while True:
        frame = pl.wait_for_frames()
        depthFrame = frame.get_depth_frame()

        width = depthFrame.get_width()
        height = depthFrame.get_height()

        centerDepth = depthFrame.get_distance(int(width / 2), int(height / 2))

        print("center",centerDepth)

finally:
    pl.stop()
