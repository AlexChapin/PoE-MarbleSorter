#pragma config(Sensor, in1,    Line,           sensorLineFollower)
#pragma config(Sensor, dgtl1,  InitQuad,       sensorQuadEncoder)
#pragma config(Motor,  port2,           InitMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           ColorGate,     tmotorServoStandard, openLoop)
#pragma config(Motor,  port4,           DirectionGate, tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Task Description: Sort 4 Different Types Of Marbles Into 4 Bins In Less Than 2 Mins, 15 Marbles Total.

void intake() //Function To Intake One Marble into The Sensor Area.
{
	while(SensorValue(InitQuad)<5){ //Run the motor up until we reach an encoder position of 5.
		startMotor(InitMotor, -30);
	}
	startMotor(InitMotor, 127); //Run the motor back down until the encoder reaches a position of 2. 
	while (SensorValue(InitQuad)>2){
		startMotor(InitMotor, 60); // Slow down the motor to create a nice deceleration curve to stop the marble.
	}
	stopMotor(InitMotor); // Stop the motor after.
}


void checkmarble() // Checks to see if there is a marble
{
	if(SensorValue(Line) > 2685) //Is Marble Transparent?
	{
		setServo(DirectionGate, 0);
		wait(.5);
		setServo(ColorGate, 30); //Send To Bin 1
		wait(3);
		setServo(ColorGate, -40);
	}
	if (SensorValue(Line) < 2350) //Is Marble Plastic?
	{
		setServo(DirectionGate, -50);
		wait(.5);
		setServo(ColorGate, 30); // Send To Bin 2
		wait(3);
		setServo(ColorGate, -40);
	}
	if(SensorValue(Line) < 2550) //Is Marble Wood?
	{
		setServo(DirectionGate, 100);
		wait(.5);
		setServo(ColorGate, 30); // Send To Bin 3
		wait(3);
		setServo(ColorGate, -40);
	}
	if(SensorValue(Line) < 2680) //Is Marble Metal?
	{
		setServo(DirectionGate, -120);
		wait(.5);
		setServo(ColorGate, 30); //Send To Bin 4
		wait(3);
		setServo(ColorGate, -40);
	}
SensorValue(InitQuad) = 0; //Finish Zeroring Encoder For Reliablilty 
stopMotor(InitMotor);
}




task main()
{
	startMotor(InitMotor, 20);
	wait(3);
	SensorValue(InitQuad) = 0;
	wait(.05); //Initialy Zero Encoder

	while(true){ //Repeat Forever
		setServo(ColorGate, -40); //Move Gate To Lower Conditition
		intake(); //Move A Marble Down The System To The Sorter
		startMotor(InitMotor, 20); //Move TThe Gate Motor Down To Zero Encoder
		wait(3);
		checkmarble(); //Determine what Color Marble Is In The Sorter And Sort It

	}
}
