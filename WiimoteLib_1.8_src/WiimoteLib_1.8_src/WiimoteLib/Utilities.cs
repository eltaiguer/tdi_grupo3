using System;
using System.Collections.Generic;
using System.Text;

namespace WiimoteLib
{
    public static class Utilities
    {
        public static double CalculateRoll(float x, float y, float z)
        {
            return (Math.Atan2(x, Math.Sqrt(Math.Pow(y, 2) + Math.Pow(z, 2))) * 180.0) / Math.PI;
        }

        public static double CalculatePitch(float y, float z)
        {
            return (Math.Atan2(-y, z) * 180.0) / Math.PI;
        }
    }
}
