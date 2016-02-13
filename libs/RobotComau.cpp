//RobotComau Class
//Developed by Davide Valeriani
//www.davidevaleriani.it

#include "RobotComau.h"
#pragma warning(disable : 4996)

#define ENABLE_O TRUE //TRUE to show the warnings, FALSE to hide them

//Constructor: create the socket and connect to the server
//Use: RobotComau(server_ip, server_port)

RobotComau::RobotComau(char server_ip[], int server_port)
{
    connect_(server_ip, server_port, lhSocket);
	selsock = false;
}

//Constructor: create two sockets, one for the motion and one to control the position
RobotComau::RobotComau(char server_ip[], int server_port, int server_port_onlyREAD)
{
    connect_(server_ip, server_port, lhSocket);
    connect_(server_ip, server_port_onlyREAD, lhSocket_OnlyREAD);
	selsock = true;
}

//Connect to the socket
void RobotComau::connect_(const char server_ip[], int server_port, SOCKET& sock)
{
	int lConnect;
	SOCKADDR_IN lSockAddr;
    WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,0),&wsaData) != 0)
        {
#if ENABLE_O
			cout << "Socket initialization failed. Exit... :-( \n";
#endif
            return;
        }
    sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sock == INVALID_SOCKET)
        {
#if ENABLE_O
			cout << "Socket not valid "<<GetLastError()<<". Exit... :-( \n" << endl;
#endif
			return;
        }
    memset(&lSockAddr,0, sizeof(lSockAddr));
    lSockAddr.sin_family = AF_INET;
    lSockAddr.sin_port = htons(server_port);
    lSockAddr.sin_addr.s_addr = inet_addr(server_ip);
    lConnect = connect(sock,(SOCKADDR *)&lSockAddr,sizeof(SOCKADDR_IN));
    if(lConnect != 0)
		{
#if ENABLE_O
			cout << "Connection error. Exit... :-( \n";
#endif
           return;
        }
#if ENABLE_O
	cout << "Connected to the server " << server_ip << " on the port " << server_port << endl;
#endif
}

RobotComau::~RobotComau(void)
{
	closesocket(lhSocket);
    if (selsock) closesocket(lhSocket_OnlyREAD);
	WSACleanup();
}

// Move to the calibration point
void RobotComau::MoveCalibration (void) {
	char data[10];
	int iResult;
	SetFunction(1, lhSocket);
#if ENABLE_O
	cout << "In positioning..." << endl;
#endif
	iResult = ReceiveData(data, lhSocket);
#if ENABLE_O
	if (!strncmp(data,"OK", 2)) cout << "Robot positioned" << endl;
	else cout << "An error has occurred" << endl;
#endif
}

// Move linear to a point
void RobotComau::MoveLinearTo (char file[])
{
	vector<Point6d> p;
	p = ConvertFile(file);
	for (unsigned int i=0; i<p.size(); i++)
		MoveLinearTo(p[i]);
}

void RobotComau::MoveLinearTo(Point6d p)
{
	int iResult;
	char data[80];
	SetFunction(2, lhSocket);
	sprintf_s(data, "%.3f", p.getX());
	strcat_s(data,"\n");
	iResult = SendData(data, lhSocket);
	iResult = ReceiveData(data, lhSocket);
	sprintf_s(data, "%.3f", p.getY());
	strcat_s(data,"\n");
	iResult = SendData(data, lhSocket);
	iResult = ReceiveData(data, lhSocket);
	sprintf_s(data, "%.3f", p.getZ());
	strcat_s(data,"\n");
	iResult = SendData(data, lhSocket);
	iResult = ReceiveData(data, lhSocket);
	sprintf_s(data, "%.3f", p.getA());
	strcat_s(data,"\n");
	iResult = SendData(data, lhSocket);
	iResult = ReceiveData(data, lhSocket);
	sprintf_s(data, "%.3f", p.getB());
	strcat_s(data,"\n");
	iResult = SendData(data, lhSocket);
	iResult = ReceiveData(data, lhSocket);
	sprintf_s(data, "%.3f", p.getC());
	strcat_s(data,"\n");
	iResult = SendData(data, lhSocket);
	iResult = ReceiveData(data, lhSocket);
#if ENABLE_O
	cout << "In positioning..." << endl;
#endif
	iResult = ReceiveData(data, lhSocket);
#if ENABLE_O
	if (!strncmp(data,"OK", 2)) cout << "Robot positioned" << endl;
	else cout << "An error has occurred" << endl;
#endif
}

//Move through a trajectory
void RobotComau::MoveTrajectory (char file[])
{
	vector<Point6d> p;
	p = ConvertFile(file);
	MoveTrajectory(p);
}

void RobotComau::MoveTrajectory (vector<Point6d> p)
{
	int iResult;
	char data[80];
	char fb[3];
	SetFunction(3, lhSocket);
	_itoa_s(p.size(), data, 10);
	strcat_s(data,"\n");
	iResult = SendData(data, lhSocket);
#if ENABLE_O
	if (iResult==0) cerr << "An error has occurred";
#endif
	for (unsigned int i=0; i<p.size(); i++)
		{
			sprintf_s(data, "%.3f", p[i].getX());
			strcat_s(data, "\n");
			iResult = SendData(data, lhSocket);
			iResult = ReceiveData(fb, lhSocket);
			sprintf_s(data, "%.3f", p[i].getY());
			strcat_s(data, "\n");
			iResult = SendData(data, lhSocket);
			iResult = ReceiveData(fb, lhSocket);
			sprintf_s(data, "%.3f", p[i].getZ());
			strcat_s(data, "\n");
			iResult = SendData(data, lhSocket);
			iResult = ReceiveData(fb, lhSocket);
			sprintf_s(data, "%.3f", p[i].getA());
			strcat_s(data, "\n");
			iResult = SendData(data, lhSocket);
			iResult = ReceiveData(fb, lhSocket);
			sprintf_s(data, "%.3f", p[i].getB());
			strcat_s(data, "\n");
			iResult = SendData(data, lhSocket);
			iResult = ReceiveData(fb, lhSocket);
			sprintf_s(data, "%.3f", p[i].getC());
			strcat_s(data, "\n");
			iResult = SendData(data, lhSocket);
			iResult = ReceiveData(fb, lhSocket);
		}
	iResult = ReceiveData(data, lhSocket);
#if ENABLE_O
	if (!strncmp(data,"OK", 2)) cout << "Robot positioned" << endl;
	else cout << "An error has occurred" << endl;
#endif
}

//Move relative from the current position
void RobotComau::MoveRelative (double x, double y, double z)
{
	int iResult;
	char data[80];
	SetFunction(4, lhSocket);
	sprintf_s(data, "%.3f", x);
	strcat_s(data, "\n");
	iResult = SendData(data, lhSocket);
	iResult = ReceiveData(data, lhSocket);
	sprintf_s(data, "%.3f", y);
	strcat_s(data, "\n");
	iResult = SendData(data, lhSocket);
	iResult = ReceiveData(data, lhSocket);
	sprintf_s(data, "%.3f", z);
	strcat_s(data, "\n");
	iResult = SendData(data, lhSocket);
	iResult = ReceiveData(data, lhSocket);
#if ENABLE_O
	cout << "In positioning..." << endl;
#endif
	iResult = ReceiveData(data, lhSocket);
#if ENABLE_O
	if (!strncmp(data,"OK", 2)) cout << "Robot positioned" << endl;
	else cout << "An error has occurred" << endl;
#endif
}

//Move arm along his axis
void RobotComau::MoveAxis (double x)
{
	int iResult;
	char data[80];
	SetFunction(5, lhSocket);
	sprintf_s(data, "%.3f", x);
	strcat_s(data, "\n");
	iResult = SendData(data, lhSocket);
	iResult = ReceiveData(data, lhSocket);
#if ENABLE_O
	cout << "In positioning..." << endl;
#endif
	iResult = ReceiveData(data, lhSocket);
#if ENABLE_O
	if (!strncmp(data,"OK", 2)) cout << "Robot positioned" << endl;
	else cout << "An error has occurred" << endl;
#endif
}

//Move in the space of joint
void RobotComau::MoveJoint (char file[])
{
	vector<Point6d> p;
	p=ConvertFile(file);
	for (unsigned int i=0; i<p.size(); i++)
		MoveJoint(p[i]);
}

void RobotComau::MoveJoint (Point6d p)
{
	int iResult;
	char data[80];
	char fb[3];
	SetFunction(6, lhSocket);
	sprintf_s(data, "%.3f", p.getX());
	strcat_s(data, "\n");
	iResult = SendData(data, lhSocket);
	iResult = ReceiveData(fb, lhSocket);
	sprintf_s(data, "%.3f", p.getY());
	strcat_s(data, "\n");
	iResult = SendData(data, lhSocket);
	iResult = ReceiveData(fb, lhSocket);
	sprintf_s(data, "%.3f", p.getZ());
	strcat_s(data, "\n");
	iResult = SendData(data, lhSocket);
	iResult = ReceiveData(fb, lhSocket);
	sprintf_s(data, "%.3f", p.getA());
	strcat_s(data, "\n");
	iResult = SendData(data, lhSocket);
	iResult = ReceiveData(fb, lhSocket);
	sprintf_s(data, "%.3f", p.getB());
	strcat_s(data, "\n");
	iResult = SendData(data, lhSocket);
	iResult = ReceiveData(fb, lhSocket);
	sprintf_s(data, "%.3f", p.getC());
	strcat_s(data, "\n");
	iResult = SendData(data, lhSocket);
	iResult = ReceiveData(fb, lhSocket);
	iResult = ReceiveData(data, lhSocket);
#if ENABLE_O
	if (!strncmp(data,"OK", 2)) cout << "Robot positioned" << endl;
	else cout << "An error has occurred" << endl;
#endif
}

//Set linear speed
void RobotComau::SetSpeed (char x[10])
{
	char data[80];
	int iResult;
	SetFunction(7, lhSocket);
	int speed;
	speed = atoi(x);
    if (speed<0 || speed>100) {
#if ENABLE_O
        cout << "Value is not allowed" << endl;
#endif
    }
	else {
		strcpy_s(data, x);
		strcat_s(data, "\n");
		iResult = SendData(data, lhSocket);
		iResult = ReceiveData(data, lhSocket);
#if ENABLE_O
		if (!strncmp(data,"OK", 2)) cout << "Speed set" << endl;
		else cout << "An error has occurred" << endl;
#endif
	}
}

//Return the current position
Point6d RobotComau::GetCurrentPosition (void)
{
    char data[80]="";
    int iResult;
    Point6d p;
    SetFunction(8, lhSocket);
	iResult = ReceiveData(data, lhSocket);// Clear the socket
	iResult = SendData("OK\n", lhSocket);
	p.setX(atof(data));
	iResult = ReceiveData(data, lhSocket);
	iResult = SendData("OK\n", lhSocket);
	p.setY(atof(data));
	iResult = ReceiveData(data, lhSocket);
	iResult = SendData("OK\n", lhSocket);
	p.setZ(atof(data));
	iResult = ReceiveData(data, lhSocket);
	iResult = SendData("OK\n", lhSocket);
	p.setA(atof(data));
	iResult = ReceiveData(data, lhSocket);
	iResult = SendData("OK\n", lhSocket);
	p.setB(atof(data));
	iResult = ReceiveData(data, lhSocket);
	iResult = SendData("OK\n", lhSocket);
	p.setC(atof(data));
	return p;
}

//Return the current position on the second socket
Point6d RobotComau::GetCurrentPositionOR (void)
{
    char data[80] = "";
    int iResult;
    Point6d p;
    SetFunction(8, lhSocket_OnlyREAD);
    iResult = ReceiveData(data, lhSocket_OnlyREAD);// Clear the socket
    iResult = SendData("OK\n", lhSocket_OnlyREAD);
    p.setX(atof(data));
    iResult = ReceiveData(data, lhSocket_OnlyREAD);
    iResult = SendData("OK\n", lhSocket_OnlyREAD);
    p.setY(atof(data));
    iResult = ReceiveData(data, lhSocket_OnlyREAD);
    iResult = SendData("OK\n", lhSocket_OnlyREAD);
    p.setZ(atof(data));
    iResult = ReceiveData(data, lhSocket_OnlyREAD);
    iResult = SendData("OK\n", lhSocket_OnlyREAD);
    p.setA(atof(data));
    iResult = ReceiveData(data, lhSocket_OnlyREAD);
    iResult = SendData("OK\n", lhSocket_OnlyREAD);
    p.setB(atof(data));
    iResult = ReceiveData(data, lhSocket_OnlyREAD);
    iResult = SendData("OK\n", lhSocket_OnlyREAD);
    p.setC(atof(data));
    return p;
}

//Return the current joints position on the second socket
Point6d RobotComau::GetJointOR (void)
{
    char data[80] = "";
    int iResult;
    Point6d p;
    SetFunction(9, lhSocket_OnlyREAD);
    iResult = ReceiveData(data, lhSocket_OnlyREAD);// Clear the socket
    iResult = SendData("OK\n", lhSocket_OnlyREAD);
    p.setX(atof(data));
    iResult = ReceiveData(data, lhSocket_OnlyREAD);
    iResult = SendData("OK\n", lhSocket_OnlyREAD);
    p.setY(atof(data));
    iResult = ReceiveData(data, lhSocket_OnlyREAD);
    iResult = SendData("OK\n", lhSocket_OnlyREAD);
    p.setZ(atof(data));
    iResult = ReceiveData(data, lhSocket_OnlyREAD);
    iResult = SendData("OK\n", lhSocket_OnlyREAD);
    p.setA(atof(data));
    iResult = ReceiveData(data, lhSocket_OnlyREAD);
    iResult = SendData("OK\n", lhSocket_OnlyREAD);
    p.setB(atof(data));
    iResult = ReceiveData(data, lhSocket_OnlyREAD);
    iResult = SendData("OK\n", lhSocket_OnlyREAD);
    p.setC(atof(data));
    return p;
}

//Return the current joints position
Point6d RobotComau::GetJoint (void)
{
	char data[80] = "";
	int iResult;
	Point6d p;
	SetFunction(9, lhSocket);
	iResult = ReceiveData(data, lhSocket);// Clear the socket
	iResult = SendData("OK\n", lhSocket);
	p.setX(atof(data));
	iResult = ReceiveData(data, lhSocket);
	iResult = SendData("OK\n", lhSocket);
	p.setY(atof(data));
	iResult = ReceiveData(data, lhSocket);
	iResult = SendData("OK\n", lhSocket);
	p.setZ(atof(data));
	iResult = ReceiveData(data, lhSocket);
	iResult = SendData("OK\n", lhSocket);
	p.setA(atof(data));
	iResult = ReceiveData(data, lhSocket);
	iResult = SendData("OK\n", lhSocket);
	p.setB(atof(data));
	iResult = ReceiveData(data, lhSocket);
	iResult = SendData("OK\n", lhSocket);
	p.setC(atof(data));
	return p;
}

//Suspend the execution of the program
void RobotComau::Sleep (float delay) {
	time_t start;
	time_t current;
	time(&start);
	do {
		time(&current);
	}
	while(difftime(current,start) < delay);
}

//Send data through the socket
//Return the number of bytes sended
int RobotComau::SendData(char data[], SOCKET& sock)
{
	int iResult;
	iResult = send(sock, data, strlen(data), 0);
	if (iResult == SOCKET_ERROR)
		{
#if ENABLE_O
			printf("Send failed: %d\n", WSAGetLastError());
#endif
			return 0;
		}
	else
		return iResult;
}

//Receive data through the socket
//Return the number of bytes received
int RobotComau::ReceiveData(char data[], SOCKET& sock)
{
	int iResult;
	iResult = recv(sock, data, 80, 0);
	if (iResult > 0)
			return iResult;
	else
		{
#if ENABLE_O
			printf("Receive failed: %d\n", WSAGetLastError());
#endif
			return 0;
		}
}

//Print the menu of the functions of the server
void RobotComau::PrintMenu(void)
{
	cout << endl<<"-------------------------MENU----------------------------" << endl;
	cout << "1) Move to position $CAL_SYS" << endl;
	cout << "2) Linear motion to a point" << endl;
	cout << "3) Motion along a trajectory" << endl;
	cout << "4) Relative motion from current position" << endl;
	cout << "5) Motion from current position" << endl;
	cout << "6) Move all joints" << endl;
	cout << "7) Set the velocity" << endl;
	cout << "8) Read current position in the operative space" << endl;
	cout << "9) Read current position in the joints space" << endl;
	cout << "10) Close the connection" << endl;
	cout << endl;
	cout << "99) Exit the server" << endl;
	cout << "---------------------------------------------------------" << endl << endl;
}

//Set the desired function
void RobotComau::SetFunction(int f, SOCKET& sock)
{
	int iResult;
	char data[10];
	_itoa_s(f, data, 10);
	strcat_s(data, "\n");
	iResult = SendData(data, sock);
	iResult = ReceiveData(data, sock);
#if ENABLE_O
	if (strncmp(data,"OK", 2)) cout << "Sending error" << endl; // !=
#endif
}

//Convert the file into a vector of Point6d
vector<Point6d> RobotComau::ConvertFile(char file[])
{
    vector<Point6d> l;
	int num = 0;
	ifstream fin(file);
	if (!fin) {
#if ENABLE_O
		cout << "Error opening file" << endl;
#endif
		return l;
	}
	char t[80];
    while (fin.getline(t, 80)) {
		Point6d p;
		p.setX(atof(strtok(t," ")));
		cout << "X=" << p.getX() << endl;
		p.setY(atof(strtok(NULL," ")));
		cout << "Y=" << p.getY() << endl;
		p.setZ(atof(strtok(NULL," ")));
		cout << "Z=" << p.getZ() << endl;
		p.setA(atof(strtok(NULL," ")));
		cout << "A=" << p.getA() << endl;
		p.setB(atof(strtok(NULL," ")));
		cout << "B=" << p.getB() << endl;
		p.setC(atof(strtok(NULL," ")));
		cout << "C=" << p.getC() << endl;
		l.push_back(p);
		num++;
    }
    fin.close();
    return l;
}

//Close the active connection, but mantain active the server
void RobotComau::CloseConnection(void)
{
	close_(lhSocket);
    if (selsock) close_(lhSocket_OnlyREAD);
}

void RobotComau::close_(SOCKET& sock) {
    SetFunction(10, sock);
    int iResult;
    char data[80];
    iResult = ReceiveData(data, sock);
#if ENABLE_O
    if (!strncmp(data,"OK", 2)) cout << "Connection closed" << endl;
    else cout << "An error has occurred" << endl;
#endif
}

//Terminate the server
void RobotComau::StopServer(void)
{
    stop_(lhSocket);
    if (selsock) stop_(lhSocket_OnlyREAD);
}

void RobotComau::stop_ (SOCKET& sock) {
    SetFunction(99, sock);
    int iResult;
    char data[80];
    iResult = ReceiveData(data, sock);
#if ENABLE_O
    if (!strncmp(data,"END", 3)) cout << "Server terminated" << endl;
    else cout << "An error has occurred" << endl;
#endif
}