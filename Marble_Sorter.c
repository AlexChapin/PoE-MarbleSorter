#pragma config(Sensor, in1,    Line,           sensorLineFollower)
#pragma config(Sensor, dgtl1,  InitQuad,       sensorQuadEncoder)
#pragma config(Motor,  port2,           InitMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           ColorGate,     tmotorServoStandard, openLoop)
#pragma config(Motor,  port4,           DirectionGate, tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//



void intake()
{
	while(SensorValue(InitQuad)<5){
		startMotor(InitMotor, -30);
	}
	startMotor(InitMotor, 127);
	while (SensorValue(InitQuad)>2){
		startMotor(InitMotor, 60);
	}
	stopMotor(InitMotor);
}


void checkmarble()
{
	if(SensorValue(Line) > 2685)
	{
		setServo(DirectionGate, 0);
		wait(.5);
		setServo(ColorGate, 30);
		wait(3);
		setServo(ColorGate, -40);
	}
	if (SensorValue(Line) < 2350)
	{
		setServo(DirectionGate, -50);
		wait(.5);
		setServo(ColorGate, 30);
		wait(3);
		setServo(ColorGate, -40);
	}
	if(SensorValue(Line) < 2550)
	{
		setServo(DirectionGate, 100);
		wait(.5);
		setServo(ColorGate, 30);
		wait(3);
		setServo(ColorGate, -40);
	}
	if(SensorValue(Line) < 2680)
	{
		setServo(DirectionGate, -120);
		wait(.5);
		setServo(ColorGate, 30);
		wait(3);
		setServo(ColorGate, -40);
	}
SensorValue(InitQuad) = 0;
stopMotor(InitMotor);
}




task main()
{
	startMotor(InitMotor, 20);
	wait(3);
	SensorValue(InitQuad) = 0;
	wait(.05);

	while(true){
		setServo(ColorGate, -40);
		intake();
		startMotor(InitMotor, 20);
		wait(3);
		checkmarble();

	}
}
