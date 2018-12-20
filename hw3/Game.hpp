#ifndef __GAMERUN_H
#define __GAMERUN_H

#include "Headers.hpp"
#include "Thread.hpp"
#include "PCQueue.hpp"
#include "utils.hpp"
/*--------------------------------------------------------------------------------
								  Auxiliary Structures
--------------------------------------------------------------------------------*/
struct game_params {
	// All here are derived from ARGV, the program's input parameters. 
	uint n_gen;
	uint n_thread;
	string filename;
	bool interactive_on; 
	bool print_on; 
};

/* Every thread needs to know his job definition */
struct job_t {
	uint start_row;
	uint finish_row;
	uint start_col;
	uint finish_col;
};


/*--------------------------------------------------------------------------------
									Class Declaration
--------------------------------------------------------------------------------*/
class Game {
public:

	Game(game_params);
	~Game() = default;
	void run(); // Runs the game
	const vector<float> gen_hist() const; // Returns the generation timing histogram  
	const vector<float> tile_hist() const; // Returns the tile timing histogram
	uint thread_num() const; //Returns the effective number of running threads = min(thread_num, field_height)


protected: // All members here are protected, instead of private for testing purposes

	// See Game.cpp for details on these three functions
	void _init_game(); 
	void _step(uint curr_gen); 
	void _destroy_game();
    inline void print_board(const char* header);


	uint m_gen_num; 			 // The number of generations to run
	uint m_thread_num; 			 // Effective number of threads = min(thread_num, field_height)
	vector<float> m_tile_hist; 	 // Shared Timing history for tiles: First m_gen_num cells are the calculation durations for tiles in generation 1 and so on. 
							   	 // Note: In your implementation, all m_thread_num threads must write to this structure. 
	vector<float> m_gen_hist;  	 // Timing history for generations: x=m_gen_hist[t] iff generation t was calculated in x microseconds
	vector<Thread*> m_threadpool; // A storage container for your threads. This acts as the threadpool.

	bool interactive_on; // Controls interactive mode - that means, prints the board as an animation instead of a simple dump to STDOUT 
	bool print_on; // Allows the printing of the board. Turn this off when you are checking performance (Dry 3, last question)
	
	// TODO: Add in your variables and synchronization primitives

    uint total_rows_num;
    uint total_cols_num;

    bool_mat curr;
    bool_mat next;

	friend class Worker;
private:
	class Worker :  public Thread {

	private:
		//bool_mat* curr;
		//bool_mat* next;
		//job_t job;
		Game* game_ptr;

	public:
		Worker(uint thread_id, Game* game)://, job_t job):
				Thread::Thread(thread_id), game_ptr(game){};//, job(job){};
		//Worker(uint thread_id, bool_mat* curr_ptr, bool_mat* next_ptr, job_t job):
		//		Thread::Thread(thread_id), curr(curr_ptr), next(next_ptr), job(job){};

	protected:
		void thread_workload() override;

	};
	//vector<Worker*> workers;
	PCQueue<job_t> jobs_q;
	int jobs_num;
};
#endif
