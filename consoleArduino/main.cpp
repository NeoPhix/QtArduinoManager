#include <iostream>
#include "SerialClass.h"



#define COM_PORT "COM3"
#define BUF_SIZE 256

int main()
{
	Serial port(COM_PORT);
	// обнуляем буфер
	char buf[BUF_SIZE];
	for (int i = 0; i < BUF_SIZE; i++)
		buf[i] = '\0';

	while (1)
	{
		std::cin >> buf;

		int bufSize = 0;
		while (buf[bufSize++] != '\0')
			bufSize++;

		port.WriteData(buf, bufSize - 1);

		std::cout << "I said: " << buf << std::endl;
		Sleep(500);

		for (int i = 0; i < BUF_SIZE; i++)
			buf[i] = '\0';
		port.ReadData(buf, BUF_SIZE - 1, 1000);

		std::cout << "Arduino answered: " << buf << std::endl;
	}
	//for (int i = 0; i < BUF_SIZE; i++)
	//	buf[i] = '\0';
	//for (;;)
	//{
	//	for (int i = 0; i < BUF_SIZE; i++)
	//		buf[i] = '\0';
	//	port.ReadData(buf, BUF_SIZE - 1, 1000);
	//	std::cout << buf << std::endl;
	//	Sleep(1000);
	//}
	return 0;
}
