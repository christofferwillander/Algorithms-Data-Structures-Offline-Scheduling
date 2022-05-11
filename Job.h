/*
* Programmer: Christoffer Willander								Date completed: Jan 5th, 2019
* Instructor: Johanna Törnquist Krasemann, Marie Netz		    Class: DV1490
*
* Offline scheduling program (First fit decreasing, Best fit decreasing)
*
*
*/

#ifndef JOB_H
#define JOB_H

class Job
{
private: // Private member variables
	int id;
	int duration;

public: // Constructors & destructor
	Job(int id = 0, int duration = 0);
	Job(const Job& other);
	Job& operator = (const Job& other);
	virtual ~Job();

public: // Public member functions
	void setId(int id);
	void setDuration(int duration);
	int getId() const;
	int getDuration() const;
};

Job::Job(int id, int duration)
{
	this->id = id;
	this->duration = duration;
}

Job::Job(const Job & other)
{
	this->id = other.id;
	this->duration = other.duration;
}

Job & Job::operator=(const Job & other)
{
	if (this != &other)
	{
		this->id = other.id;
		this->duration = other.duration;
	}

	return *this;
}

Job::~Job()
{

}

void Job::setId(int id)
{
	this->id = id;
}

void Job::setDuration(int duration)
{
	this->duration = duration;
}

int Job::getId() const
{
	return this->id;
}

int Job::getDuration() const
{
	return this->duration;
}

#endif