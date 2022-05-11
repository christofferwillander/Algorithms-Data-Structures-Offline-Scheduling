/*
* Programmer: Christoffer Willander								Date completed: Jan 5th, 2019
* Instructor: Johanna Törnquist Krasemann, Marie Netz		    Class: DV1490
*
* Offline scheduling program (First fit decreasing, Best fit decreasing)
*
*
*/

#include <fstream>
#include <tuple>
#include "List.h"
#include "OperatingRoom.h"
#include "Job.h"

std::pair <Job*, int> readFromFile(std::string fileName); // Function reading data files, returns pointer to Job array and int variable with number of jobs
void firstFitAlgorithm(Job *&jobsArr, int nrOfJobs, int printIndex); // First fit bin packing algorithm
void bestFitAlgorithm(Job *&jobsArr, int nrOfJobs, int printIndex); // Best fit bin packing algorithm

int partitionJobs(int start, int end, Job*& jobList); // Partitioning function for QuickSort
void sortJobsByDuration(int start, int end, Job*& jobList); // Main function for QuickSort
void swapJobs(int index1, int index2, Job *&jobList); // Swap function for QuickSort

void clearConsole(); // Function that "clears" console after printing

int main()
{
	for (int i = 1; i < 4; i++)
	{
		std::string fileName = "Textfil_" + std::to_string(i) + ".txt"; // Concatenating file name

		Job* jobsArr = nullptr;
		int nrOfJobs;
		std::tie(jobsArr, nrOfJobs) = readFromFile(fileName);

		if (jobsArr) // If jobs were succesfully extracted from data file
		{
			sortJobsByDuration(0, (nrOfJobs - 1), jobsArr); // Sort jobs by duration (decreasing order) with QuickSort

			firstFitAlgorithm(jobsArr, nrOfJobs, i); // Running the sorted jobs array through the First fit algorithm

			bestFitAlgorithm(jobsArr, nrOfJobs, i); // Running the sorted jobs array through the Best fit algorithm

			delete[] jobsArr;
			jobsArr = nullptr;
		}
	}

	return 0;
}

std::pair <Job*, int> readFromFile(std::string fileName)
{
	Job tempJob;
	int pos, idPart, durationPart;
	std::string tempLine;
	std::ifstream inFile;
	Job* jobsArr = nullptr;
	List<Job> jobs;

	inFile.open(fileName);

	if (!inFile.fail()) // If data file was succesfully opened
	{
		while (std::getline(inFile, tempLine, '\r')) // While there are lines left to read
		{
			pos = tempLine.find(","); // Find "," in string
			idPart = std::stoi(tempLine.substr(0, pos)); // Extract id from string
			durationPart = std::stoi(tempLine.substr(pos + 1)); // Extract duration from string
			tempJob.setId(idPart); // Set id in temp job object
			tempJob.setDuration(durationPart); // Set duration in temp job object
			jobs.insertAt(0, tempJob); // Insert job in jobs list
		}

		jobsArr = new Job[jobs.length()]; // Create job array to accomodate all jobs in jobs list
		jobs.getAll(jobsArr, jobs.length()); // Retrieve all jobs from jobs list
	}

	inFile.close();
	return std::make_pair(jobsArr, jobs.length());
}

void firstFitAlgorithm(Job *&jobsArr, int nrOfJobs, int printIndex)
{
	List<int> unscheduled;
	OperatingRoom* rooms;
	rooms = new OperatingRoom[3];

	for (int i = 0; i < nrOfJobs; i++) // First fit decreasing
	{
		if (rooms[0].addOperation(jobsArr[i])) // Add job to first operation room if it fits
		{
		}
		else if (rooms[1].addOperation(jobsArr[i])) // Else add job to second operation room if it fits
		{
		}
		else if (rooms[2].addOperation(jobsArr[i])) // Else add job to third operation room if it fits
		{
		}
		else
		{
			unscheduled.insertAt(0, jobsArr[i].getId()); // Else add job to list of unscheduled jobs
		}
	}

	std::cout << "--------------------------------------------------------------\n" << "First fit decreasing (Textfil_" << printIndex << ".txt)" << "\n--------------------------------------------------------------";

	for (int i = 0; i < 3; i++)
	{
		std::cout << "\n\nOperating Room " << (i + 1) << "\n";
		rooms[i].printStats();
	}

	int* unscheduledTotal = new int[unscheduled.length()];
	unscheduled.getAll(unscheduledTotal, unscheduled.length());

	std::cout << "\n\n--------------------------------------------------------------\nUnscheduled operations (ID): ";

	if (unscheduled.length() > 0)
	{
		for (int i = 0; i < unscheduled.length(); i++)
		{
			if (i < unscheduled.length() - 1)
			{
				std::cout << unscheduledTotal[i] << ", ";
			}
			else
			{
				std::cout << unscheduledTotal[i] << "\n--------------------------------------------------------------";
			}
		}
	}
	else
	{
		std::cout << "None" << "\n--------------------------------------------------------------";
	}

	std::cout << "\n\nPress return to continue...";
	getchar();
	clearConsole();

	delete unscheduledTotal;
	delete[] rooms;
}

void bestFitAlgorithm(Job *&jobsArr, int nrOfJobs, int printIndex)
{
	List<int> unscheduled;
	int tightestSpot;
	OperatingRoom* rooms;
	rooms = new OperatingRoom[3];

	for (int i = 0; i < nrOfJobs; i++) // Best fit decreasing
	{
		tightestSpot = -1;

		for (int j = 0; j < 3; j++) // Finding the "tightest" bin that can accomodate the job
		{
			if ((tightestSpot == -1 && jobsArr[i].getDuration() <= rooms[j].timeLeft())) // If no bin has yet been found and current bin can fit the job
			{
				tightestSpot = j;
			}
			else if ((tightestSpot != -1 && jobsArr[i].getDuration() <= rooms[j].timeLeft() && rooms[tightestSpot].timeLeft() > rooms[j].timeLeft())) // If the current bin's schedule can fit the job and is tighter than the previous fit
			{
				tightestSpot = j;
			}
		}

		if (tightestSpot != -1) // If an arbitrary bin has been found
		{
			rooms[tightestSpot].addOperation(jobsArr[i]);
		}
		else // If no bin can accomodate the job
		{
			unscheduled.insertAt(0, jobsArr[i].getId());
		}
	}

	std::cout << "--------------------------------------------------------------\n" << "Best fit decreasing (Textfil_" << printIndex << ".txt)" << "\n--------------------------------------------------------------";
	for (int i = 0; i < 3; i++)
	{
		std::cout << "\n\nOperating Room " << (i + 1) << "\n";
		rooms[i].printStats();
	}

	int *unscheduledTotal = new int[unscheduled.length()];
	unscheduled.getAll(unscheduledTotal, unscheduled.length());

	std::cout << "\n\n--------------------------------------------------------------\nUnscheduled operations (ID): ";

	if (unscheduled.length() > 0)
	{
		for (int i = 0; i < unscheduled.length(); i++)
		{
			if (i < unscheduled.length() - 1)
			{
				std::cout << unscheduledTotal[i] << ", ";
			}
			else
			{
				std::cout << unscheduledTotal[i] << "\n--------------------------------------------------------------";
			}
		}
	}
	else
	{
		std::cout << "None" << "\n--------------------------------------------------------------";
	}
	std::cout << "\n\nPress return to continue...";
	getchar();
	clearConsole();

	delete unscheduledTotal;
	delete[] rooms;
}

void swapJobs(int index1, int index2, Job *&jobList)
{
	Job tempJob = jobList[index1];
	jobList[index1] = jobList[index2];
	jobList[index2] = tempJob;
}

void sortJobsByDuration(int start, int end, Job*& jobList)
{
	if (start < end)
	{
		int pivotValue = partitionJobs(start, end, jobList);
		sortJobsByDuration(start, pivotValue - 1, jobList);
		sortJobsByDuration(pivotValue + 1, end, jobList);
	}
}

int partitionJobs(int start, int end, Job*& jobList)
{
	int pivotValue = jobList[start].getDuration();
	int pivotPosition = start;

	for (int i = start + 1; i <= end; i++)
	{
		if (jobList[i].getDuration() > pivotValue)
		{
			swapJobs(i, pivotPosition + 1, jobList);
			swapJobs(pivotPosition, pivotPosition + 1, jobList);
			pivotPosition++;
		}
	}

	return pivotPosition;
}

void clearConsole() {
	std::cout << std::string(100, '\n');
}