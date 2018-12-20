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

    vector<string> lines = utils::read_lines(params.filename);
	vector<string> temp_line;
	total_rows_num = lines.size();
	temp_line = utils::split(lines[0],' ');//TODO: Corner case for 0 lines
	total_cols_num = temp_line.size();

	//Initializing the vectors with '0':
	curr = bool_mat(total_rows_num + 2);
	next = bool_mat(total_rows_num + 2);
	for(uint i = 0 ; i < total_rows_num + 2; i++) {
		for (uint j = 0; j < total_cols_num + 2; j++) {
			curr[i].push_back(false);
			next[i].push_back(false);
		}
	}

	//Parse the board input:
	for(uint i = 1 ; i < total_rows_num + 1 ; i++){
		temp_line = utils::split(lines[i-1],' ');
		for(uint j = 1; j < total_cols_num + 1 ; j++){
            curr[i][j] = (temp_line[j-1] == "1") ;
            next[i][j] = (temp_line[j-1] == "1") ;
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

	 m_threadpool = vector<Thread*>(1);
	 Worker* worker = new Worker(1,&curr,&next,
	 		{1,total_rows_num + 1,1,total_cols_num + 1}
	 		);
     worker->start();
     m_threadpool.push_back(worker);



}

void Game::_step(uint curr_gen) {
	// Push jobs to queue
	// Wait for the workers to finish calculating 
	// Swap pointers between current and next field

	vector<vector<bool>> temp = vector<vector<bool>>(curr);
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
            for(uint i = 1 ; i < total_rows_num + 1; i++) {
                cout << "|" ;
                for (uint j = 1; j < total_cols_num + 1; j++) {
                    cout << curr[i][j];
                }
                cout << "|" << endl;
            }
            cout << "======================" << endl;
		}
		
		// TODO: Print the board
		if(header == NULL){
            for(uint i = 1 ; i < total_rows_num + 1; i++) {
                cout << "|" ;
                for (uint j = 1; j < total_cols_num + 1; j++) {
                    cout << curr[i][j];
                }
                cout << "|" << endl;
            }
            cout << "======================" << endl;
		}

		// Display for GEN_SLEEP_USEC micro-seconds on screen 
		if(interactive_on)
			usleep(GEN_SLEEP_USEC);
	}

}


void Game::Worker::thread_workload(){
	//while(true) {
		int alives = 0;
		//Loop over the given cells:
		for (uint row = job.start_row; row < job.finish_row; row++) {
			for (uint col = job.start_col; col < job.finish_col; col++) {
				//Check neighbors:
				for (int i = -1; i < 2; i++) {
					for (int j = -1; j < 2; j++) {
						if((*(this->curr))[row + i][col + j])
							alives++ ;
					}
				}
				if((*(this->curr))[row][col]) alives--;

				//===========Rules:==========//
				(*(this->next))[row][col] = false; //KILL

				if ((*(this->curr))[row][col]) {
					if (alives == 3 || alives == 2)
						(*(this->next))[row][col] = true; //SURVIVE
				} else {
					if (alives == 3)
						(*(this->next))[row][col] = true; //BIRTH
				}
				//===========::::::===========//
				alives = 0;
			}

		//}
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

