using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Kinect;
using System.IO;
using System.Xml;

namespace MovementData
{
    public class Movement
    {
        public List<DataMovement> movementRecord = new List<DataMovement>();
        public DataMovement previousHandRight = null;

        public void addMovement(Skeleton skeleton)
        {
            if (skeleton != null){

                if (skeleton.TrackingState == SkeletonTrackingState.Tracked)
                {
                    Joint jointHand = skeleton.Joints[JointType.HandRight];
                    DataMovement data = new DataMovement();
                    data.xPosition = jointHand.Position.X;
                    data.yPosition = jointHand.Position.Y;
                    data.zPosition = jointHand.Position.Z;

                    if (previousHandRight == null)
                    {
                        data.speed = 0;
                        previousHandRight = new DataMovement();
                    }
                    else
                    {
                        float dX = (float)Math.Pow((data.xPosition - previousHandRight.xPosition) * 30,2);
                        float dY = (float)Math.Pow((data.yPosition - previousHandRight.yPosition) * 30, 2);
                        float dZ = (float)Math.Pow((data.zPosition - previousHandRight.zPosition) * 30, 2);

                        data.speed = (float)Math.Sqrt(dX + dY + dZ);
                    }

                    previousHandRight.xPosition = data.xPosition;
                    previousHandRight.yPosition = data.yPosition;
                    previousHandRight.zPosition = data.zPosition;
                    previousHandRight.speed = data.speed;

                    movementRecord.Add(data);
                }
            }
        }

        public void saveToTXT()
        {
            using (XmlWriter writer = XmlWriter.Create("movimientosXML.xml"))
            {

                writer.WriteStartDocument();
                writer.WriteStartElement("Movimientos");
                foreach (DataMovement dm in movementRecord)
                {
                    writer.WriteStartElement("HandRight");

                    writer.WriteElementString("X", dm.xPosition.ToString());
                    writer.WriteElementString("Y", dm.yPosition.ToString());
                    writer.WriteElementString("Z", dm.zPosition.ToString());
                    writer.WriteElementString("Speed", dm.speed.ToString());

                    writer.WriteEndElement();

                }

                writer.WriteEndElement();
	            writer.WriteEndDocument();
            }



        }
            
        }

}
