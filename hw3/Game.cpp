#include "Headers.hpp"
#include "Game.hpp"
#include <bitset>

/*--------------------------------------------------------------------------------
								
--------------------------------------------------------------------------------*/
Game::Game(game_params params){
    m_gen_num = params.n_gen;
    m_thread_num = params.n_thread;
    interactive_on = params.interactive_on;
    print_on = params.print_on;
	jobs_num = 0;

    vector<string> lines = utils::read_lines(params.filename);
	vector<string> temp_line;
	total_rows_num = lines.size();
	temp_line = utils::split(lines[0],' ');//TODO: Corner case for 0 lines
	total_cols_num = temp_line.size();
	//effective threads number:
	m_thread_num = (m_thread_num > total_rows_num) ? total_rows_num : m_thread_num;

	//Initializing the vectors with '0':
	curr = new bool_mat(total_rows_num + 2);
	next = new bool_mat(total_rows_num + 2);
	for(uint i = 0 ; i < total_rows_num + 2; i++) {
		for (uint j = 0; j < total_cols_num + 2; j++) {
			(*curr)[i].push_back(false);
			(*next)[i].push_back(false);
		}
	}

	//Parse the board input:
	for(uint i = 1 ; i < total_rows_num + 1 ; i++){
		temp_line = utils::split(lines[i-1],' ');
		for(uint j = 1; j < total_cols_num + 1 ; j++){
			(*curr)[i][j] = (temp_line[j-1] == "1") ;
			(*next)[i][j] = (temp_line[j-1] == "1") ;
		}
	}

}

void Game::run() {

	_init_game(); // Starts the threads and all other variables you need
	print_board("Initial Board");
	for (uint i = 0; i < m_gen_num; ++i) {
		auto gen_start = std::chrono::system_clock::now();
		_step(i); // Iterates a single generation 
		auto gen_end = std::chrono::system_clock::now();
		m_gen_hist.push_back((float)std::chrono::duration_cast<std::chrono::microseconds>(gen_end - gen_start).count());
		print_board(NULL);
	} // generation loop
	print_board("Final Board");
	_destroy_game();
}

void Game::_init_game() {
	// Create threads
	// Create game fields
	// Start the threads
	// Testing of your implementation will presume all threads are started here

	//Creating & Starting the threads:
	m_threadpool = vector<Thread*>(m_thread_num);
	for(uint i = 0; i < m_thread_num; i++){
		m_threadpool[i] = new Worker(i,this);
		m_threadpool[i]->start();
	}

}

void Game::_step(uint curr_gen) {

	// Push jobs to queue:
	//N jobs would be created by the producer and inserted to the queue
	//N = (total_rows_num / thread_num )
	job_t* job;
	jobs_num = m_thread_num ;
	uint range = total_rows_num / jobs_num;
	uint reminder = total_rows_num % jobs_num;

	for(int i = 0; i < jobs_num - 1; i++){
		job = new job_t{1+(range * i),range*(i + 1),1,total_cols_num + 1};
		jobs_q.push(*job);
	}
	//Last one gets the reminder:
	job = new job_t{1 + range*(jobs_num - 1),1 + (range*jobs_num) + reminder ,1,total_cols_num + 1};
	jobs_q.push(*job);

	// Wait for the workers to finish calculating
	//while(!jobs_q.is_empty() && jobs_num > 0){}
	while(!jobs_q.is_empty()){}
	// Swap pointers between current and next field
	//vector<vector<bool>> temp = vector<vector<bool>>(curr);
    bool_mat* temp = curr;
	curr = next;
    next = temp;

}

void Game::_destroy_game(){
	// Destroys board and frees all threads and resources 
	// Not implemented in the Game's destructor for testing purposes. 
	// Testing of your implementation will presume all threads are joined here
}

/*--------------------------------------------------------------------------------
								
--------------------------------------------------------------------------------*/
inline void Game::print_board(const char* header) {

	if(print_on){ 

		// Clear the screen, to create a running animation 
		if(interactive_on)
			system("clear");

		// Print small header if needed
		if (header != NULL){
			cout << "<------------" << header << "------------>" << endl;
		}
		
		// TODO: Print the board
		if(header == NULL){
            for(uint i = 1 ; i < total_rows_num + 1; i++) {
                cout << "|" ;
                for (uint j = 1; j < total_cols_num + 1; j++) {
                    cout << (*curr)[i][j];
                }
                cout << "|" << endl;
            }
            cout << "======================" << endl;
		}

		// Display for GEN_SLEEP_USEC micro-seconds on screen 
		if(interactive_on)
			usleep(GEN_SLEEP_USEC);

		/*	cout << u8"╔" << string(u8"═") * total_cols_num << u8"╗" << endl;
			for (uint i = 1; i < total_rows_num + 1; ++i) {
				cout << u8"║";
				for (uint j = 1; j < total_cols_num + 1; ++j) {
					cout << (curr[i][j] ? u8"█" : u8"░");
				}
				cout << u8"║" << endl;
			}
			cout << u8"╚" << string(u8"═") * total_cols_num << u8"╝" << endl;*/
	}

}

/*
 * Thread's Workload Function
 * */
void Game::Worker::thread_workload(){
	while(true) {
		//Start polling the queue:
		job_t job = this->game_ptr->jobs_q.pop();
		//Job acquired. now start working you lazy worker!

		//=============:WORK:============//
		int alives = 0;
		//Loop over the given cells:
		for (uint row = job.start_row; row < job.finish_row; row++) {
			for (uint col = job.start_col; col < job.finish_col; col++) {
				//Check for alive neighbors:
				for (int i = -1; i < 2; i++) {
					for (int j = -1; j < 2; j++) {
						if((*this->game_ptr->curr)[row + i][col + j])
							alives++ ;
					}
				}
				if((*this->game_ptr->curr)[row][col]) alives--;

				//===========Rules:==========//
				(*this->game_ptr->next)[row][col] = false; //KILL

				if ((*this->game_ptr->curr)[row][col]) {
					if (alives == 3 || alives == 2)
						(*this->game_ptr->next)[row][col] = true; //SURVIVE
				} else {
					if (alives == 3)
						(*this->game_ptr->next)[row][col] = true; //BIRTH
				}
				//===========::::::===========//
				alives = 0;
			}
		}
		//==========:WORK's DONE:=========//
		//Now to the next job!
		this->game_ptr->jobs_num--;
	}
}


/* Function sketch to use for printing the board. You will need to decide its placement and how exactly 
	to bring in the field's parameters. 

		cout << u8"╔" << string(u8"═") * field_width << u8"╗" << endl;
		for (uint i = 0; i < field_height ++i) {
			cout << u8"║";
			for (uint j = 0; j < field_width; ++j) {
				cout << (field[i][j] ? u8"█" : u8"░");
			}
			cout << u8"║" << endl;
		}
		cout << u8"╚" << string(u8"═") * field_width << u8"╝" << endl;
*/

/* Getters */
const vector<float> Game::gen_hist() const {
	return m_gen_hist;
}

const vector<float> Game::tile_hist() const {
	return m_tile_hist;
}

uint Game::thread_num() const {
	return m_thread_num;
}

