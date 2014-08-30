using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Kinect;
using System.IO;
using System.Xml;
using System.Globalization;

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
                        data.xSpeed = 0;
                        previousHandRight = new DataMovement();
                    }
                    else
                    {
                        float dX = (float)Math.Pow((data.xPosition - previousHandRight.xPosition) * 30,2);
                        float dY = (float)Math.Pow((data.yPosition - previousHandRight.yPosition) * 30, 2);
                        float dZ = (float)Math.Pow((data.zPosition - previousHandRight.zPosition) * 30, 2);

                        data.xSpeed = (float)Math.Sqrt(dX + dY + dZ);
                    }

                    previousHandRight.xPosition = data.xPosition;
                    previousHandRight.yPosition = data.yPosition;
                    previousHandRight.zPosition = data.zPosition;
                    previousHandRight.xSpeed = data.xSpeed;

                    movementRecord.Add(data);
                }
            }
        }

        public void saveToXml()
        {
            NumberFormatInfo nfi = new CultureInfo("en-US", true).NumberFormat;
            nfi.NumberDecimalDigits = 8;

            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Encoding = System.Text.Encoding.ASCII;
            using (XmlWriter writer = XmlWriter.Create("movimientosXML.xml",settings))
            {

                writer.WriteStartDocument();
                writer.WriteStartElement("Movement");
                foreach (DataMovement dm in movementRecord)
                {
                    writer.WriteStartElement("HandRight");

                    writer.WriteElementString("X", dm.xPosition.ToString("F",nfi));
                    writer.WriteElementString("Y", dm.yPosition.ToString("F", nfi));
                    writer.WriteElementString("Z", dm.zPosition.ToString("F", nfi));
                    writer.WriteElementString("Speed", dm.xSpeed.ToString("F", nfi));

                    writer.WriteEndElement();

                }

                writer.WriteEndElement();
	            writer.WriteEndDocument();
            }



        }
            
        }

}
