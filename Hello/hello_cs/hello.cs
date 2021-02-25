using System;
using Intel.RealSense;

namespace hello_cs
{
    class hello
    {
        static void Main(string[] args)
        {
            var pi = new Pipeline();
            try
            {
                pi.Start();

                while (true)
                {
                    using (var frame = pi.WaitForFrames())
                    using (var depthFrame = frame.DepthFrame)
                    {
                        var width = depthFrame.Width;
                        var height = depthFrame.Height;
                        var centerDepth = depthFrame.GetDistance(width / 2, height / 2);

                        Console.WriteLine($"屏幕中心点距离{centerDepth}米");
                    }
                }


            }
            catch (Exception ex)
            {
                Console.WriteLine($"error：{ex.Message}");
            }
            finally
            {
                pi.Stop();
            }
        }
    }
}
