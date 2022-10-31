#pragma once


class Reservoir
{
	double width;
	double length;
	double depth;
	string name;
public:

	Reservoir() :Reservoir{ 1, 1, 1, "reservoir" } {}

	Reservoir(double width, double length, double depth, string name) :width{ width }, length{ length }, depth{ depth }, name{ name } {}

	void Show(); 
};