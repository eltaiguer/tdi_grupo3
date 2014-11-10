//////////////////////////////////////////////////////////////////////////////////
//	MultipleWiimoteForm.cs
//	Managed Wiimote Library Tester
//	Written by Brian Peek (http://www.brianpeek.com/)
//  for MSDN's Coding4Fun (http://msdn.microsoft.com/coding4fun/)
//	Visit http://blogs.msdn.com/coding4fun/archive/2007/03/14/1879033.aspx
//  and http://www.codeplex.com/WiimoteLib
//  for more information
//////////////////////////////////////////////////////////////////////////////////

using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;
using Ventuz.OSC;
using WiimoteLib;

namespace WiimoteTest
{
	public partial class WiimoteInfo : UserControl
    {
        #region WiiMusic

        private const string DEST_IP = /*"172.16.108.64"; */"127.0.0.1";
        public const int PORT = 12345;
        private bool hitDownWiimote = false;
        private bool hitDownChuk = false;
        private bool hitUpWiimote = false;
        private bool hitUpChuk = false;
        NetWriter nw = new UdpWriter(DEST_IP, PORT);
        NetWriter nw2 = new UdpWriter("127.0.0.1", 12345);
        OscMessage msg;
        string address = String.Empty;
        double roll=-1;
        double pitch=-1;
        #endregion

        #region wiimote lib
        private delegate void UpdateWiimoteStateDelegate(WiimoteChangedEventArgs args);
		private delegate void UpdateExtensionChangedDelegate(WiimoteExtensionChangedEventArgs args);

		private Bitmap b = new Bitmap(256, 192, PixelFormat.Format24bppRgb);
		private Graphics g;
		private Wiimote mWiimote;

		public WiimoteInfo()
		{
			InitializeComponent();
			g = Graphics.FromImage(b);
		}

		public WiimoteInfo(Wiimote wm) : this()
		{
			mWiimote = wm;
		}

		public void UpdateState(WiimoteChangedEventArgs args)
		{
			BeginInvoke(new UpdateWiimoteStateDelegate(UpdateWiimoteChanged), args);
		}

		public void UpdateExtension(WiimoteExtensionChangedEventArgs args)
		{
			BeginInvoke(new UpdateExtensionChangedDelegate(UpdateExtensionChanged), args);
		}

		private void chkLED_CheckedChanged(object sender, EventArgs e)
		{
			mWiimote.SetLEDs(chkLED1.Checked, chkLED2.Checked, chkLED3.Checked, chkLED4.Checked);
		}

		private void chkRumble_CheckedChanged(object sender, EventArgs e)
		{
			mWiimote.SetRumble(chkRumble.Checked);
		}

        #endregion
        private void UpdateWiimoteChanged(WiimoteChangedEventArgs args)
        {
            #region seteo de interfaz
            WiimoteState ws = args.WiimoteState;

			clbButtons.SetItemChecked(0, ws.ButtonState.A);
			clbButtons.SetItemChecked(1, ws.ButtonState.B);
            clbButtons.SetItemChecked(2, ws.ButtonState.Minus);
			clbButtons.SetItemChecked(3, ws.ButtonState.Home);
			clbButtons.SetItemChecked(4, ws.ButtonState.Plus);
			clbButtons.SetItemChecked(5, ws.ButtonState.One);
			clbButtons.SetItemChecked(6, ws.ButtonState.Two);
			clbButtons.SetItemChecked(7, ws.ButtonState.Up);
			clbButtons.SetItemChecked(8, ws.ButtonState.Down);
			clbButtons.SetItemChecked(9, ws.ButtonState.Left);
			clbButtons.SetItemChecked(10, ws.ButtonState.Right);

			//lblAccel.Text = ws.AccelState.Values.ToString();
            
			chkLED1.Checked = ws.LEDState.LED1;
			chkLED2.Checked = ws.LEDState.LED2;
			chkLED3.Checked = ws.LEDState.LED3;
			chkLED4.Checked = ws.LEDState.LED4;


            address = "/Brian/" + MultipleWiimoteForm.wiimoteIdMap[mWiimote.ID] + "/Wiimote/Buttons";
            msg = new OscElement(address, Convert.ToInt32(ws.ButtonState.Up), Convert.ToInt32(ws.ButtonState.Right), Convert.ToInt32(ws.ButtonState.Down),
                                                Convert.ToInt32(ws.ButtonState.Left), Convert.ToInt32(ws.ButtonState.A), Convert.ToInt32(ws.ButtonState.Minus),
                                                Convert.ToInt32(ws.ButtonState.Home), Convert.ToInt32(ws.ButtonState.Plus), Convert.ToInt32(ws.ButtonState.One),
                                                Convert.ToInt32(ws.ButtonState.Two), Convert.ToInt32(ws.ButtonState.B));
            nw.Send(msg);

            pitch = Utilities.CalculatePitch(ws.AccelState.Values.Y, ws.AccelState.Values.Z);
            roll = Utilities.CalculateRoll(ws.AccelState.Values.X, ws.AccelState.Values.Y, ws.AccelState.Values.Z);

           // address = "/Brian/" + MultipleWiimoteForm.wiimoteIdMap[mWiimote.ID] + "/Wiimote/Accel";
           // msg = new OscElement(address, (float)ws.AccelState.Values.X, (float)ws.AccelState.Values.Y,
           //                                             (float)ws.AccelState.Values.Z, (float)roll, (float)pitch);
          //  nw.Send(msg);

            lblAccel.Text = String.Format("{0:0.##}",ws.AccelState.Values.Z) + "\n Pitch: " + String.Format("{0:0.##}", pitch) + "\n" + "Roll: " + String.Format("{0:0.##}", roll);

            address = "/Brian/" + MultipleWiimoteForm.wiimoteIdMap[mWiimote.ID] + "/Wiimote/Gestures";
            

            if (!hitDownWiimote && ws.AccelState.Values.Z > - 1  && (pitch <= 20 && pitch >= -20) )//&& ws.AccelState.Values.Y > 0)
            {               
                hitDownWiimote = true;
                msg = new OscElement(address, 0, 0, 1, 0);
                nw.Send(msg);
            }
            else if (ws.AccelState.Values.Z < -1)
            {
                hitDownWiimote = false;               
            }

            if (!hitUpWiimote && ws.AccelState.Values.Z <-1)//&& ws.AccelState.Values.Y > 0)
            {
                hitUpWiimote = true;
                msg = new OscElement(address, 1,0,0,0);
                nw.Send(msg);
            }
            else if (ws.AccelState.Values.Z > -1)
            {
                hitUpWiimote = false;
            }           

			switch(ws.ExtensionType)
			{
				case ExtensionType.NunchukI:
					lblChuk.Text = ws.NunchukState.AccelState.Values.ToString();
					lblChukJoy.Text = ws.NunchukState.Joystick.ToString();
					chkC.Checked = ws.NunchukState.C;
					chkZ.Checked = ws.NunchukState.Z;


                    address = "/Brian/" + MultipleWiimoteForm.wiimoteIdMap[mWiimote.ID] + "/Nunchuk/Buttons";
                    msg = new OscElement(address, Convert.ToInt32(ws.NunchukState.C), Convert.ToInt32(ws.NunchukState.Z), 
                                                            (float)ws.NunchukState.Joystick.X, (float) ws.NunchukState.Joystick.Y);
                    nw.Send(msg);


                    roll = Utilities.CalculateRoll(ws.NunchukState.AccelState.Values.X, ws.NunchukState.AccelState.Values.Y,ws.NunchukState.AccelState.Values.Z);

                    pitch = Utilities.CalculatePitch(ws.NunchukState.AccelState.Values.Y, ws.NunchukState.AccelState.Values.Z);

                  //  address = "/Brian/" + MultipleWiimoteForm.wiimoteIdMap[mWiimote.ID] + "/Nunchuk/Accel";
                  //  msg = new OscElement(address, (float)ws.NunchukState.AccelState.Values.X, (float) ws.NunchukState.AccelState.Values.Y,
                  //                                              (float)ws.NunchukState.AccelState.Values.Z, (float)roll, (float)pitch);
                  //  nw.Send(msg);

                    address = "/Brian/" + MultipleWiimoteForm.wiimoteIdMap[mWiimote.ID] + "/Nunchuk/Gestures";
                    lblAccel.Text = String.Format("{0:0.##}", ws.NunchukState.AccelState.Values.Z) + "\n Pitch: " + String.Format("{0:0.##}", pitch) + "\n" + "Roll: " + String.Format("{0:0.##}", roll);
                    if (!hitDownChuk && ws.NunchukState.AccelState.Values.Z > -1 && (pitch <= 30 && pitch >= -180))// && ws.NunchukState.AccelState.Values.Y >= 0)//&& ws.AccelState.Values.Y > 0)
                    {
                        hitDownChuk = true;
                        msg = new OscElement(address, 0, 0, 1, 0);
                        nw.Send(msg);
                    }
                    else if (ws.NunchukState.AccelState.Values.Z < -1)
                    {
                        hitDownChuk = false;
                    }

                    if (!hitUpChuk && ws.NunchukState.AccelState.Values.Z < -1 && pitch >= 140)// && pitch <=60)// && pitch>=-20 && pitch>= 190)//&& ws.AccelState.Values.Y > 0)
                    {
                        hitUpChuk = true;
                        msg = new OscElement(address, 1,0,0,0);
                        nw.Send(msg);
                    }
                    else if (ws.AccelState.Values.Z > -1 && pitch<140)
                    {
                        hitUpChuk = false;
                    } 
					break;

                case ExtensionType.Nunchuk:
                    lblChuk.Text = ws.NunchukState.AccelState.Values.ToString();
                    lblChukJoy.Text = ws.NunchukState.Joystick.ToString();
                    chkC.Checked = ws.NunchukState.C;
                    chkZ.Checked = ws.NunchukState.Z;


                                        address = "/Brian/" + MultipleWiimoteForm.wiimoteIdMap[mWiimote.ID] + "/Nunchuk/Buttons";
                    msg = new OscElement(address, Convert.ToInt32(ws.NunchukState.C), Convert.ToInt32(ws.NunchukState.Z), 
                                                            (float)ws.NunchukState.Joystick.X, (float) ws.NunchukState.Joystick.Y);
                    nw.Send(msg);


                    roll = Utilities.CalculateRoll(ws.NunchukState.AccelState.Values.X, ws.NunchukState.AccelState.Values.Y,ws.NunchukState.AccelState.Values.Z);

                    pitch = Utilities.CalculatePitch(ws.NunchukState.AccelState.Values.Y, ws.NunchukState.AccelState.Values.Z);

                  //  address = "/Brian/" + MultipleWiimoteForm.wiimoteIdMap[mWiimote.ID] + "/Nunchuk/Accel";
                  //  msg = new OscElement(address, (float)ws.NunchukState.AccelState.Values.X, (float) ws.NunchukState.AccelState.Values.Y,
                  //                                              (float)ws.NunchukState.AccelState.Values.Z, (float)roll, (float)pitch);
                  //  nw.Send(msg);

                    address = "/Brian/" + MultipleWiimoteForm.wiimoteIdMap[mWiimote.ID] + "/Nunchuk/Gestures";
                    lblAccel.Text = String.Format("{0:0.##}", ws.NunchukState.AccelState.Values.Z) + "\n Pitch: " + String.Format("{0:0.##}", pitch) + "\n" + "Roll: " + String.Format("{0:0.##}", roll);
                    if (!hitDownChuk && ws.NunchukState.AccelState.Values.Z > -1 && (pitch <= 30 && pitch >= -180))// && ws.NunchukState.AccelState.Values.Y >= 0)//&& ws.AccelState.Values.Y > 0)
                    {
                        hitDownChuk = true;
                        msg = new OscElement(address, 0, 0, 1, 0);
                        nw.Send(msg);
                    }
                    else if (ws.NunchukState.AccelState.Values.Z < -1)
                    {
                        hitDownChuk = false;
                    }

                    if (!hitUpChuk && ws.NunchukState.AccelState.Values.Z < -1 && pitch >= 140)// && pitch <=60)// && pitch>=-20 && pitch>= 190)//&& ws.AccelState.Values.Y > 0)
                    {
                        hitUpChuk = true;
                        msg = new OscElement(address, 1,0,0,0, (float)pitch);
                        nw.Send(msg);
                    }
                    else if (ws.AccelState.Values.Z > -1 && pitch<140)
                    {
                        hitUpChuk = false;
                    } 
					break;

				case ExtensionType.ClassicController:
					clbCCButtons.SetItemChecked(0, ws.ClassicControllerState.ButtonState.A);
					clbCCButtons.SetItemChecked(1, ws.ClassicControllerState.ButtonState.B);
					clbCCButtons.SetItemChecked(2, ws.ClassicControllerState.ButtonState.X);
					clbCCButtons.SetItemChecked(3, ws.ClassicControllerState.ButtonState.Y);
					clbCCButtons.SetItemChecked(4, ws.ClassicControllerState.ButtonState.Minus);
					clbCCButtons.SetItemChecked(5, ws.ClassicControllerState.ButtonState.Home);
					clbCCButtons.SetItemChecked(6, ws.ClassicControllerState.ButtonState.Plus);
					clbCCButtons.SetItemChecked(7, ws.ClassicControllerState.ButtonState.Up);
					clbCCButtons.SetItemChecked(8, ws.ClassicControllerState.ButtonState.Down);
					clbCCButtons.SetItemChecked(9, ws.ClassicControllerState.ButtonState.Left);
					clbCCButtons.SetItemChecked(10, ws.ClassicControllerState.ButtonState.Right);
					clbCCButtons.SetItemChecked(11, ws.ClassicControllerState.ButtonState.ZL);
					clbCCButtons.SetItemChecked(12, ws.ClassicControllerState.ButtonState.ZR);
					clbCCButtons.SetItemChecked(13, ws.ClassicControllerState.ButtonState.TriggerL);
					clbCCButtons.SetItemChecked(14, ws.ClassicControllerState.ButtonState.TriggerR);

					lblCCJoy1.Text = ws.ClassicControllerState.JoystickL.ToString();
					lblCCJoy2.Text = ws.ClassicControllerState.JoystickR.ToString();

					lblTriggerL.Text = ws.ClassicControllerState.TriggerL.ToString();
					lblTriggerR.Text = ws.ClassicControllerState.TriggerR.ToString();
                                   
     

                    address = "/Brian/" + MultipleWiimoteForm.wiimoteIdMap[mWiimote.ID] + "/Controller/Buttons";
                    msg = new OscElement(address, Convert.ToInt32(ws.ClassicControllerState.ButtonState.Up), Convert.ToInt32(ws.ClassicControllerState.ButtonState.Right), Convert.ToInt32(ws.ClassicControllerState.ButtonState.Down),
                                                        Convert.ToInt32(ws.ClassicControllerState.ButtonState.Left), Convert.ToInt32(ws.ClassicControllerState.ButtonState.Minus), Convert.ToInt32(ws.ClassicControllerState.ButtonState.Home),
                                                        Convert.ToInt32(ws.ClassicControllerState.ButtonState.Plus), Convert.ToInt32(ws.ClassicControllerState.ButtonState.X), Convert.ToInt32(ws.ClassicControllerState.ButtonState.A),
                                                        Convert.ToInt32(ws.ClassicControllerState.ButtonState.B), Convert.ToInt32(ws.ClassicControllerState.ButtonState.Y), Convert.ToInt32(ws.ClassicControllerState.ButtonState.TriggerL),
                                                        Convert.ToInt32(ws.ClassicControllerState.ButtonState.ZL), Convert.ToInt32(ws.ClassicControllerState.ButtonState.TriggerR), Convert.ToInt32(ws.ClassicControllerState.ButtonState.ZR));
                    nw.Send(msg);

					break;

                case ExtensionType.ClassicControllerI:
                    clbCCButtons.SetItemChecked(0, ws.ClassicControllerState.ButtonState.A);
                    clbCCButtons.SetItemChecked(1, ws.ClassicControllerState.ButtonState.B);
                    clbCCButtons.SetItemChecked(2, ws.ClassicControllerState.ButtonState.X);
                    clbCCButtons.SetItemChecked(3, ws.ClassicControllerState.ButtonState.Y);
                    clbCCButtons.SetItemChecked(4, ws.ClassicControllerState.ButtonState.Minus);
                    clbCCButtons.SetItemChecked(5, ws.ClassicControllerState.ButtonState.Home);
                    clbCCButtons.SetItemChecked(6, ws.ClassicControllerState.ButtonState.Plus);
                    clbCCButtons.SetItemChecked(7, ws.ClassicControllerState.ButtonState.Up);
                    clbCCButtons.SetItemChecked(8, ws.ClassicControllerState.ButtonState.Down);
                    clbCCButtons.SetItemChecked(9, ws.ClassicControllerState.ButtonState.Left);
                    clbCCButtons.SetItemChecked(10, ws.ClassicControllerState.ButtonState.Right);
                    clbCCButtons.SetItemChecked(11, ws.ClassicControllerState.ButtonState.ZL);
                    clbCCButtons.SetItemChecked(12, ws.ClassicControllerState.ButtonState.ZR);
                    clbCCButtons.SetItemChecked(13, ws.ClassicControllerState.ButtonState.TriggerL);
                    clbCCButtons.SetItemChecked(14, ws.ClassicControllerState.ButtonState.TriggerR);

                    lblCCJoy1.Text = ws.ClassicControllerState.JoystickL.ToString();
                    lblCCJoy2.Text = ws.ClassicControllerState.JoystickR.ToString();

                    //lblCCJoy1.Text = ws.ClassicControllerState.RawJoystickL.ToString();
                    //lblCCJoy2.Text = ws.ClassicControllerState.RawJoystickR.ToString();

                    lblTriggerL.Text = ws.ClassicControllerState.TriggerL.ToString();
                    lblTriggerR.Text = ws.ClassicControllerState.TriggerR.ToString();

                    break;

				case ExtensionType.Guitar:
				    clbGuitarButtons.SetItemChecked(0, ws.GuitarState.FretButtonState.Green);
				    clbGuitarButtons.SetItemChecked(1, ws.GuitarState.FretButtonState.Red);
				    clbGuitarButtons.SetItemChecked(2, ws.GuitarState.FretButtonState.Yellow);
				    clbGuitarButtons.SetItemChecked(3, ws.GuitarState.FretButtonState.Blue);
				    clbGuitarButtons.SetItemChecked(4, ws.GuitarState.FretButtonState.Orange);
				    clbGuitarButtons.SetItemChecked(5, ws.GuitarState.ButtonState.Minus);
				    clbGuitarButtons.SetItemChecked(6, ws.GuitarState.ButtonState.Plus);
				    clbGuitarButtons.SetItemChecked(7, ws.GuitarState.ButtonState.StrumUp);
				    clbGuitarButtons.SetItemChecked(8, ws.GuitarState.ButtonState.StrumDown);

					clbTouchbar.SetItemChecked(0, ws.GuitarState.TouchbarState.Green);
					clbTouchbar.SetItemChecked(1, ws.GuitarState.TouchbarState.Red);
					clbTouchbar.SetItemChecked(2, ws.GuitarState.TouchbarState.Yellow);
					clbTouchbar.SetItemChecked(3, ws.GuitarState.TouchbarState.Blue);
					clbTouchbar.SetItemChecked(4, ws.GuitarState.TouchbarState.Orange);

					lblGuitarJoy.Text = ws.GuitarState.Joystick.ToString();
					lblGuitarWhammy.Text = ws.GuitarState.WhammyBar.ToString();
					lblGuitarType.Text = ws.GuitarState.GuitarType.ToString();
				    break;



				case ExtensionType.Drums:
					clbDrums.SetItemChecked(0, ws.DrumsState.Red);
					clbDrums.SetItemChecked(1, ws.DrumsState.Blue);
					clbDrums.SetItemChecked(2, ws.DrumsState.Green);
					clbDrums.SetItemChecked(3, ws.DrumsState.Yellow);
					clbDrums.SetItemChecked(4, ws.DrumsState.Orange);
					clbDrums.SetItemChecked(5, ws.DrumsState.Pedal);
					clbDrums.SetItemChecked(6, ws.DrumsState.Minus);
					clbDrums.SetItemChecked(7, ws.DrumsState.Plus);

					lbDrumVelocity.Items.Clear();
					lbDrumVelocity.Items.Add(ws.DrumsState.RedVelocity);
					lbDrumVelocity.Items.Add(ws.DrumsState.BlueVelocity);
					lbDrumVelocity.Items.Add(ws.DrumsState.GreenVelocity);
					lbDrumVelocity.Items.Add(ws.DrumsState.YellowVelocity);
					lbDrumVelocity.Items.Add(ws.DrumsState.OrangeVelocity);
					lbDrumVelocity.Items.Add(ws.DrumsState.PedalVelocity);

					lblDrumJoy.Text = ws.DrumsState.Joystick.ToString();
					break;

				case ExtensionType.BalanceBoard:
					if(chkLbs.Checked)
					{
						lblBBTL.Text = ws.BalanceBoardState.SensorValuesLb.TopLeft.ToString();
						lblBBTR.Text = ws.BalanceBoardState.SensorValuesLb.TopRight.ToString();
						lblBBBL.Text = ws.BalanceBoardState.SensorValuesLb.BottomLeft.ToString();
						lblBBBR.Text = ws.BalanceBoardState.SensorValuesLb.BottomRight.ToString();
						lblBBTotal.Text = ws.BalanceBoardState.WeightLb.ToString();
					}
					else
					{
						lblBBTL.Text = ws.BalanceBoardState.SensorValuesKg.TopLeft.ToString();
						lblBBTR.Text = ws.BalanceBoardState.SensorValuesKg.TopRight.ToString();
						lblBBBL.Text = ws.BalanceBoardState.SensorValuesKg.BottomLeft.ToString();
						lblBBBR.Text = ws.BalanceBoardState.SensorValuesKg.BottomRight.ToString();
						lblBBTotal.Text = ws.BalanceBoardState.WeightKg.ToString();
					}
					lblCOG.Text = ws.BalanceBoardState.CenterOfGravity.ToString();
					break;

				case ExtensionType.TaikoDrum:
					clbTaiko.SetItemChecked(0, ws.TaikoDrumState.OuterLeft);
					clbTaiko.SetItemChecked(1, ws.TaikoDrumState.InnerLeft);
					clbTaiko.SetItemChecked(2, ws.TaikoDrumState.InnerRight);
					clbTaiko.SetItemChecked(3, ws.TaikoDrumState.OuterRight);
					break;

				case ExtensionType.MotionPlusI:
					lblMotionPlus.Text = ws.MotionPlusState.RawValues.ToString();
					clbSpeed.SetItemChecked(0, ws.MotionPlusState.YawFast);
					clbSpeed.SetItemChecked(1, ws.MotionPlusState.PitchFast);
					clbSpeed.SetItemChecked(2, ws.MotionPlusState.RollFast);

					break;

                case ExtensionType.MotionPlus:
                    lblMotionPlus.Text = ws.MotionPlusState.RawValues.ToString();
                    clbSpeed.SetItemChecked(0, ws.MotionPlusState.YawFast);
                    clbSpeed.SetItemChecked(1, ws.MotionPlusState.PitchFast);
                    clbSpeed.SetItemChecked(2, ws.MotionPlusState.RollFast);

                    break;
			}

			g.Clear(Color.Black);

			UpdateIR(ws.IRState.IRSensors[0], lblIR1, lblIR1Raw, 0, Color.Red);
			UpdateIR(ws.IRState.IRSensors[1], lblIR2, lblIR2Raw, 1, Color.Blue);
			UpdateIR(ws.IRState.IRSensors[2], lblIR3, lblIR3Raw, 2, Color.Yellow);
			UpdateIR(ws.IRState.IRSensors[3], lblIR4, lblIR4Raw, 3, Color.Orange);

			if(ws.IRState.IRSensors[0].Found && ws.IRState.IRSensors[1].Found)
				g.DrawEllipse(new Pen(Color.Green), (int)(ws.IRState.RawMidpoint.X / 4), (int)(ws.IRState.RawMidpoint.Y / 4), 2, 2);

			pbIR.Image = b;

			pbBattery.Value = (ws.Battery > 0xc8 ? 0xc8 : (int)ws.Battery);
			lblBattery.Text = ws.Battery.ToString();
            lblDevicePath.Text = "Device Path: " + mWiimote.HIDDevicePath;
            #endregion

            //if (ws.ButtonState.A && !a)
            //{

            //    NetWriter nw = new UdpWriter("127.0.0.1", 12345);
            //    OscMessage msg = new OscElement("/test/Brian/wiimote", 5555, 234.567);
            //    nw.Send(msg);
            //    a = true;
            //}
            //else if (!ws.ButtonState.A)
            //{
            //    a = false;
            //}

            //if (!hit && ws.AccelState.Values.Z > -1 && ws.ButtonState.B)
            //{
            //    NetWriter nw = new UdpWriter("127.0.0.1", 12345);
            //    OscMessage msg = new OscElement("/test/Brian/wiimote");
            //    hit = true;
            //    nw.Send(msg);

            //}
            //else if (ws.AccelState.Values.Z < -1)
            //{
            //    hit = false;
            //}


            //if (!hitNunchuk && ws.NunchukState.AccelState.Values.Z > -1 && ws.NunchukState.Z)
            //{
            //    //NetWriter nw = new UdpWriter("127.0.0.1", 12345);
            //    NetWriter nw = new UdpWriter("127.0.0.1", 12345);
            //    OscMessage msg = new OscElement("/test/Brian/nunchuk", 5555, 234.567);
            //    hitNunchuk = true;
            //    nw.Send(msg);

            //}
            //else if (ws.NunchukState.AccelState.Values.Z < -1)
            //{
            //    hitNunchuk = false;
            //}
		}

		private void UpdateIR(IRSensor irSensor, Label lblNorm, Label lblRaw, int index, Color color)
		{
			clbIR.SetItemChecked(index, irSensor.Found);

			if(irSensor.Found)
			{
				lblNorm.Text = irSensor.Position.ToString() + ", " + irSensor.Size;
				lblRaw.Text = irSensor.RawPosition.ToString();
				g.DrawEllipse(new Pen(color), (int)(irSensor.RawPosition.X / 4), (int)(irSensor.RawPosition.Y / 4),
							 irSensor.Size+1, irSensor.Size+1);
			}
		}

		private void UpdateExtensionChanged(WiimoteExtensionChangedEventArgs args)
		{
			chkExtension.Text = args.ExtensionType.ToString();
			chkExtension.Checked = args.Inserted;
		}

		public Wiimote Wiimote
		{
			set { mWiimote = value; }
		}

		private void button1_Click(object sender, EventArgs e)
		{
			mWiimote.InitializeMotionPlus();
		}




        
    }
}
