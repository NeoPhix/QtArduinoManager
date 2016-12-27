#include <iostream>
#include "SerialClass.h"



#define COM_PORT "COM7"
#define BUF_SIZE 10

int main()
{
	Serial port(COM_PORT);
	// обнуляем буфер
	char buf[BUF_SIZE];
	while (1)
	{
		std::cin >> buf;
		port.WriteData(buf, BUF_SIZE - 1);

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
