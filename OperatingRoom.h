/*
* Programmer: Christoffer Willander								Date completed: Jan 5th, 2019
* Instructor: Johanna Törnquist Krasemann, Marie Netz		    Class: DV1490
*
* Offline scheduling program (First fit decreasing, Best fit decreasing)
*
*
*/

#ifndef OPERATINGROOM_H
#define OPERATINGROOM_H
#include "Job.h"
#include <iostream>
#include <iomanip>
#include <string>

class OperatingRoom
{
private: // Private member variables
	int nrOf;
	int cap;
	int *operations;
	int totalOperationalTime;
	int totalScheduledTime;

private: // Private help functions
	void freeMemory();
	void expand();

public: // Constructors & destructor
	OperatingRoom(int operationalTime = 510);
	OperatingRoom(const OperatingRoom& other);
	OperatingRoom& operator = (const OperatingRoom& other);
	virtual ~OperatingRoom();

public: // Public member functions
	int timeLeft() const;
	void printStats() const;
	void setOperationalTime(int operationalTime);
	void clearSchedule();
	bool addOperation(const Job& job);
	bool canFit(const Job& job) const;

};

void OperatingRoom::freeMemory()
{
	delete[] this->operations;
}

void OperatingRoom::expand()
{
	this->cap += 10;

	int *tempArr = new int[this->cap];

	for (int i = 0; i < this->nrOf; i++)
	{
		tempArr[i] = this->operations[i];
	}
	this->freeMemory();
	this->operations = tempArr;
}

OperatingRoom::OperatingRoom(int operationalTime)
{
	this->nrOf = 0;
	this->cap = 10;
	this->totalOperationalTime = operationalTime;
	this->totalScheduledTime = 0;
	this->operations = new int[this->cap];
}

OperatingRoom::OperatingRoom(const OperatingRoom & other)
{
	this->nrOf = other.nrOf;
	this->cap = other.cap;
	this->totalOperationalTime = other.totalOperationalTime;
	this->totalScheduledTime = other.totalScheduledTime;
	this->operations = new int[this->cap];

	for (int i = 0; i < this->cap; i++)
	{
		this->operations[i] = other.operations[i];
	}
}

OperatingRoom & OperatingRoom::operator=(const OperatingRoom & other)
{
	if (this != &other)
	{
		this->freeMemory();

		this->nrOf = other.nrOf;
		this->cap = other.cap;
		this->totalOperationalTime = other.totalOperationalTime;
		this->totalScheduledTime = other.totalScheduledTime;
		this->operations = new int[this->cap];

		for (int i = 0; i < this->cap; i++)
		{
			this->operations[i] = other.operations[i];
		}
	}

	return *this;
}

OperatingRoom::~OperatingRoom()
{
	this->freeMemory();
}

int OperatingRoom::timeLeft() const
{
	return (this->totalOperationalTime - this->totalScheduledTime);
}

void OperatingRoom::printStats() const
{
	std::cout << "--------------------------------------------------------------\n";
	std::cout << "Scheduled operations: ";
	for (int i = 0; i < this->nrOf; i++)
	{
		if (i < this->nrOf - 1)
		{
			std::cout << this->operations[i] << ", ";
		}
		else
		{
			std::cout << this->operations[i] << "\n\n";
			std::cout << "Total number of operations scheduled: " << this->nrOf << "\n";
		}
	}
	std::cout << "Total time scheduled: " << this->totalScheduledTime << " minutes (" << std::setprecision(4) << ((static_cast<double>(this->totalScheduledTime) / static_cast<double>(this->totalOperationalTime)) * 100) << "%)\n";
	std::cout << "Idle time: " << (this->totalOperationalTime - this->totalScheduledTime) << " minutes (" << std::setprecision(4) << ((1 - (static_cast<double>(this->totalScheduledTime) / static_cast<double>(this->totalOperationalTime))) * 100) << "%)\n";
	std::cout << "--------------------------------------------------------------";
}

void OperatingRoom::setOperationalTime(int operationalTime)
{
	this->totalOperationalTime = operationalTime;
}

void OperatingRoom::clearSchedule()
{
	if (this->nrOf > 0)
	{
		this->freeMemory();
		this->nrOf = 0;
		this->cap = 10;
		this->totalScheduledTime = 0;
		this->operations = new int[this->cap];
	}
}

bool OperatingRoom::addOperation(const Job& job)
{
	bool successfullyAdded = false;
	if ((job.getDuration() + this->totalScheduledTime) <= this->totalOperationalTime)
	{
		if (this->nrOf == this->cap)
		{
			this->expand();
		}

		this->operations[this->nrOf++] = job.getId();
		this->totalScheduledTime += job.getDuration();
		successfullyAdded = true;
	}

	return successfullyAdded;
}

bool OperatingRoom::canFit(const Job& job) const
{
	return (job.getDuration() <= (this->totalOperationalTime - this->totalScheduledTime));
}

#endif