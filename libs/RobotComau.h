//RobotComau Class
//Developed by Davide Valeriani
//www.davidevaleriani.it

#pragma once
#include <iostream>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "Point6d.h"
#include <winsock2.h>

using namespace std;

class RobotComau
{
public:
	RobotComau(char[], int);
    RobotComau(char[], int, int);
	~RobotComau(void);
	void MoveCalibration(void);	// Move to the calibration point
	void MoveLinearTo(char []);	// Move linear to a point taken from a file (not blocking)
	void MoveLinearTo(Point6d); // Move linear to a point
	void MoveTrajectory(vector<Point6d>); // Move through a trajectory of points (not blocking)
	void MoveTrajectory(char []); // Move through a trajectory taken from a file
	void MoveRelative(double, double, double); // Move relative from the current position
	void MoveAxis(double); // Move arm along his axis
	void MoveJoint(char []); // Move to a point in the space of joint taken from a file
	void MoveJoint(Point6d); // Move to a point in the space of joint
	void SetSpeed(char[]); // Set program speed
	Point6d GetCurrentPosition(void); // Return the current position
    Point6d GetCurrentPositionOR(void); // Return the current position on the second socket
	Point6d GetJoint(void); // Return the current joints position
	Point6d GetJointOR (void); // Return the current joints position on the second socket
	void CloseConnection(void); // Close the active connection, but mantain active the server
	void StopServer(void); // Terminate the server
	void PrintMenu(void); // Print the menu of the functions of the server
	void Sleep(float); // Suspend the execution of the program
private:
	SOCKET lhSocket, lhSocket_OnlyREAD;
	void SetFunction(int, SOCKET&); // Take the function desired
	int SendData(char[], SOCKET&); // Send data through the socket
	int ReceiveData(char[], SOCKET&); // Receive data through the socket
	vector<Point6d> ConvertFile(char[]); // Convert the file into a vector of Point
    void stop_ (SOCKET&);
    void close_ (SOCKET&);
    void connect_ (const char[], int, SOCKET&);
	bool selsock;
};