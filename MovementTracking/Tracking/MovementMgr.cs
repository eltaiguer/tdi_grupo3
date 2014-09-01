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
    public class MovementMgr
    {
        private List<Movement> movementRecord = new List<Movement>();
        private Movement previousMovement = null;
        private List<JointType> trackedJoints = null;

        public void Initialize()
        {
            trackedJoints = new List<JointType>();
            trackedJoints.Add(JointType.HandRight);
            trackedJoints.Add(JointType.HandLeft);
            trackedJoints.Add(JointType.Head);
        }

        public void addMovement(Skeleton skeleton)
        {
            if (skeleton != null){

                if (skeleton.TrackingState != SkeletonTrackingState.NotTracked)
                {
                    Movement currentMovement = new Movement();

                    foreach (JointType jointType in trackedJoints)
                    {

                        Joint joint = skeleton.Joints[jointType];
                        JointPosition currentJointPosition = new JointPosition();
                        currentJointPosition.xPosition = joint.Position.X;
                        currentJointPosition.yPosition = joint.Position.Y;
                        currentJointPosition.zPosition = joint.Position.Z;

                        if (previousMovement == null)
                        {
                            currentJointPosition.xSpeed = 0;
                            currentJointPosition.ySpeed = 0;
                            currentJointPosition.zSpeed = 0;
                        }
                        else
                        {
                            JointPosition previousJointPosition;
                            previousMovement.jointMovement.TryGetValue(jointType, out previousJointPosition);

                            currentJointPosition.xSpeed = (float)Math.Pow((currentJointPosition.xPosition - previousJointPosition.xPosition) * 30, 2);
                            currentJointPosition.ySpeed = (float)Math.Pow((currentJointPosition.yPosition - previousJointPosition.yPosition) * 30, 2);
                            currentJointPosition.zSpeed = (float)Math.Pow((currentJointPosition.zPosition - previousJointPosition.zPosition) * 30, 2);
                        }

                        currentMovement.jointMovement.Add(jointType, currentJointPosition);
                    }

                    movementRecord.Add(currentMovement);
                    previousMovement = currentMovement;
                }
            }
        }

        public void saveToXml()
        {
            NumberFormatInfo nfi = new CultureInfo("en-US", true).NumberFormat;
            nfi.NumberDecimalDigits = 8;

            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Encoding = System.Text.Encoding.ASCII;
            using (XmlWriter writer = XmlWriter.Create("movements.xml",settings))
            {

                writer.WriteStartDocument();
                writer.WriteStartElement("Movement");
                foreach (Movement m in movementRecord)
                {
                    writer.WriteStartElement("Joint");

                   // Dictionary<JointType, JointPosition>.Enumerator iterator= m.jointMovement.GetEnumerator();

                    foreach(KeyValuePair<JointType, JointPosition> dicItem in m.jointMovement)
                    {
                        writer.WriteStartElement(dicItem.Key.ToString());
                        
                        writer.WriteStartElement("Position");
                        writer.WriteElementString("X", dicItem.Value.xPosition.ToString("F",nfi));
                        writer.WriteElementString("Y", dicItem.Value.yPosition.ToString("F", nfi));
                        writer.WriteElementString("Z", dicItem.Value.zPosition.ToString("F", nfi));
                        writer.WriteEndElement();

                        writer.WriteStartElement("Speed");
                        writer.WriteElementString("X", dicItem.Value.xSpeed.ToString("F", nfi));
                        writer.WriteElementString("Y", dicItem.Value.ySpeed.ToString("F", nfi));
                        writer.WriteElementString("Z", dicItem.Value.zSpeed.ToString("F", nfi));
                        writer.WriteEndElement();

                        writer.WriteEndElement();

                    }                    

                    writer.WriteEndElement();

                }

                writer.WriteEndElement();

	            writer.WriteEndDocument();
            }

        }
            
    }

}
