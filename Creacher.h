/*
	Authors: Allen Higgins C00197373 and Robert Scully C00196960
	Date: 15 December 2017

*/
#pragma once
class Creacher
{
public:
	Creacher(char type,int age);
	~Creacher();

	//bool isAlive;
	int age;
	char type;
	void move();
};
