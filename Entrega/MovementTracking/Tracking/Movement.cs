using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Kinect;

namespace MovementData
{
    public class Movement
    {
        public Dictionary<JointType, JointPosition> jointMovement = new Dictionary<JointType,JointPosition>();
    }
}
