#include <fstream>  
#include <iostream>  
#include <string>  
#include <vector>
#include <sstream>
#include <algorithm>
#include <limits>
#include <cmath>
#include <ctime>

// Constant
float const lower_bound_word_size = 25;
float const upper_bound_word_size = 50;
int const src_word_max_len = 26;

// Global Variable
int **matrix;
std::vector< int > typo_word_min;
std::vector< std::string > typo_word_vec;
std::vector< std::vector<std::string> > src_word_vec;

// Function Prototype
void call_get_dist(int index, int start_range, int end_range);
void strip_str(std::string& input_str);

/* @param index the index of the vector which consist of typo strings
 * @param start_range the start index of the vector which consist of source strings
 * @param end_range the end index of the vector which consist of source strings
*/
void call_get_dist(int index, int start_range, int end_range) {
	int i, j, n, m, k;
	i = j =  n = m = k = 0;
	for (k = start_range; k <= end_range; k++) {
		std::vector<std::string>::iterator src_it = src_word_vec[k].begin();
		
		for (; src_it!= src_word_vec[k].end(); ++src_it)  {
			i =  j = 0;
			n = typo_word_vec[index].length();
			m = src_it->length();

			for (j = 0; j <= m; j++) matrix[0][j]=j;	
			for (i = 0; i <= n; i++) matrix[i][0]=i;

			for (i = 1; i <= n; i++)  {
				for (j = 1; j <= m; j++)  {
					int cost = 1;
					if (typo_word_vec[index][i-1] == (*src_it)[j-1])
						cost = 0;
		      		matrix[i][j]= std::min(matrix[i-1][j] + 1, std::min(matrix[i][j-1] + 1, matrix[i-1][j-1] + cost));
    			}
  			}

			int dist_res = matrix[n][m];

			if (dist_res < typo_word_min[index]) {
				typo_word_min[index] = dist_res;
				if (dist_res == 0) return;
			}
		}
	}
}

// @param input_str input string to be stripped
void strip_str(std::string& input_str) {
	if(input_str.empty()) return;
	int startIndex = input_str.find_first_not_of(" ");
 	int endIndex = input_str.find_last_not_of("\r\n");
	std::string temp_str = input_str;
	input_str.erase();
	input_str = temp_str.substr(startIndex, (endIndex-startIndex+ 1) );
}

int main(int argc, char *argv[]) {
    //clock_t t1, t2;
    //t1 = clock();
	int i = 0;
	std::string line;
	 
	//std::ifstream src_file("twl06.txt"); 
	
	
	std::ifstream src_file("/var/tmp/twl06.txt"); 
	std::ifstream input(argv[1]);  
	std::string typo_word;  
	
	/// Initialize matrices - we will re-use this again and again.
	matrix = new int*[src_word_max_len+1];
	for (int i = 0; i < src_word_max_len+1; ++i)
    		matrix[i] = new int[src_word_max_len+1];

	/// assume that the maximum size of source string would be 30.
	src_word_vec.reserve(30);

	for (i = 0; i < src_word_max_len; i++) {
		std::vector<std::string> each_src_word_vec;
		/// assume that the number of each source string would be 20000.
		each_src_word_vec.reserve(20000);
		src_word_vec.push_back(each_src_word_vec);
	}

	/// tokenize and transform that string into upper ones from argument file.
	while( input >> typo_word ) {
		std::transform(typo_word.begin(), typo_word.end(), typo_word.begin(), ::toupper);
		typo_word_vec.push_back(typo_word);
		typo_word_min.push_back(std::numeric_limits<int>::max());
	}
	
	/// read source file, strip them, and put it in the vector.
  	if (src_file.is_open()) {
    	while (! src_file.eof() ) {
      		getline (src_file,line);
			strip_str(line);
			src_word_vec[line.size()].push_back(line);
    	}
		src_file.close();
  	}

	/// calculate the range of comparing strings
	for (int i = 0; i < typo_word_vec.size(); i++) {
		float each_typo_word_len = (float)typo_word_vec[i].size();
		int start_range = (int)(each_typo_word_len - floor((each_typo_word_len / lower_bound_word_size) * each_typo_word_len) - 1);
		if (start_range < 1)
			start_range = 1;
		int end_range = (int)(each_typo_word_len + ceil((each_typo_word_len / upper_bound_word_size) * each_typo_word_len) + 1 );
		if (end_range > src_word_max_len)
			end_range = src_word_max_len - 1;

		call_get_dist(i, start_range, end_range);
	}	

	/// calculate the sum of minimum edit distance of each string.
	int dist_sum = 0;
	for (int i = 0; i < typo_word_min.size(); i++)
		dist_sum += typo_word_min[i];

	/// free or delete matrices we've used.
	for (int i = 0; i < src_word_max_len+1; ++i)
    		delete [] matrix[i];
  	delete [] matrix;

	/// print the result.
	std::cout << dist_sum << std::endl;
	//t2 = clock();
	//std::cout<<"\n\n"<<t2-t1;
	return 0;  
}
