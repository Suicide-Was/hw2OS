#include <iostream>                                                                                                     //Written by Zach Kofoed Q934C652
#include <vector>
#include <random>

// Class representing a process
class Process {
private:
    int id;         // Unique identifier for the process
    int tickets;    // Number of lottery tickets assigned to the process
public:
    // Constructor initializing process ID and tickets
    Process(int id, int tickets) : id(id), tickets(tickets) {}
    // Getter method to retrieve process ID
    int get_ID() const { return id; }
    // Getter method to retrieve number of tickets
    int get_tickets() const { return tickets; }
};

// Class representing the scheduler
class Scheduler {
private:
    std::vector<Process> processes;    // Vector to hold processes
    std::random_device rd;              // Random device for seed generation
    std::mt19937 gen;                   // Mersenne Twister random number generator
public:
    //Constructor initializing the random number generator
    Scheduler() : gen(rd()) {}

    //Method to add a process to the scheduler
    void add_process(const Process& process) {
        processes.push_back(process);
    }

    //Lottery tickets to processes
    void allocate_tickets() {
        //Loop through all processes
        for (auto& process : processes) {
            //Assign the process ID as the number of tickets
            process = Process(process.get_ID(), process.get_ID());
        }
    }

    //Select a winner process based on lottery tickets
    const Process& select_winner() {
        //Uniform distribution to generate random numbers         //Apparently a part of the random class took me forever to find
        std::uniform_int_distribution<> dis(0, get_total_tickets() - 1);     
        //Generate a random winning ticket
        int winningTicket = dis(gen);

        int ticketSum = 0;
        //Loop through all processes
        for (const auto& process : processes) {
            //Add the number of tickets of the current process to the total
            ticketSum += process.get_tickets();
            //If the tickets exceed the winning ticket, return the process
            if (ticketSum > winningTicket) {
                return process;
            }
        }

        //Just in case.
        throw std::runtime_error("Error selecting winner.");
    }

    //Method to calculate the total number of lottery tickets
    int get_total_tickets() const {
        int total_tickets = 0;
        //Loop through all processes
        for (const auto& process : processes) {
            //Add the number of tickets of the current process to the total
            total_tickets += process.get_tickets();
        }
        return total_tickets;
    }

    //Method to display the current state of the scheduler
    void display_state() const {
        std::cout << "Current state of the scheduler:" << std::endl;
        for (const auto& process : processes) {
            std::cout << "Process ID: " << process.get_ID() << ", Tickets: " << process.get_tickets() << std::endl;
        }
    }
};

//Main function
int main() {
    Scheduler sched;

    // Adding processes
    sched.add_process(Process(1, 5));
    sched.add_process(Process(2, 10));
    sched.add_process(Process(3, 3));
    sched.add_process(Process(4, 7));

    //Allocating tickets
    sched.allocate_tickets();

    //Displaying the current state of the scheduler
    sched.display_state();

    //Selecting winner
    const Process winner = sched.select_winner();
    //Output the winner process ID
    std::cout << "Process " << winner.get_ID() << " wins the lottery!" << std::endl;

    return 0;
}
