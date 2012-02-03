/*
 * Basically, this problem is a kind of "weighted interval scheduling". 
 * I used bucket sort and binary search for this problem.
*/
#include <fstream>  
#include <iostream>  
#include <string>  
#include <vector>
#include <sstream>
#include <algorithm>
#include <limits>
#include <cmath>

/**
* @brief class for interval data.
* 
* begin is the beginning of interval in Gattaca input file. 
* end and score is as well.
*/
class Interval
{
public:
	int begin;
	int end;
	int score;

	Interval(int begin, int end, int score)
	{
		this->begin = begin;
		this->end = end;
		this->score = score;
	}
};

int main(int argc, char *argv[])
{
	int i = 0, j = 0, k = 0;
	int int_buf = 0;
	int count_number = 0;
	int itv_num = 0;
	int top = 0, p = 0, bottom = 0;
	std::string str_buf;
	std::ifstream  is;
	std::vector< std::vector<Interval*> > ref_cnt;
	std::vector<int> best;
	std::vector<Interval*> itv_vec;

	is.open (argv[1], std::ifstream::in);
	getline(is, str_buf);
	std::istringstream (str_buf) >> count_number;
	ref_cnt.resize(count_number);

	is.seekg (str_buf.size() + count_number + std::ceil(count_number / 80) + 1);
	getline(is, str_buf);
	
	if (str_buf.size() > 0)
		std::istringstream (str_buf) >> itv_num;
	else
	{
		getline(is, str_buf);
		std::istringstream (str_buf) >> itv_num;
	}

	best.resize(itv_num);
	itv_vec.resize(itv_num);
	
	/*
	std::cout << "itv_num: " << itv_num << " count_number: " << count_number << std::endl;
	*/

	/// prepare for the array for bucket sort of interval.
	for (i = 0; i < ref_cnt.size(); i++)
	{
		std::vector<Interval*> temp;
		ref_cnt[i] = temp;
	}

	/// reading input interval file.
	while(is.good())
	{
		i = 0;
		getline(is, str_buf);
	    	std::stringstream ss(str_buf);
    		std::vector<int> int_tokens(3, 0);

		/// tokenizing and convert it as integer values
		while (ss >> str_buf)
			std::istringstream (str_buf) >> int_tokens[i++];
	
		/// push each interval object in ref_cnt vector for bucket sort based on its "end" value.
		if (i > 0)
			ref_cnt[int_tokens[1]].push_back(new Interval(int_tokens[0], int_tokens[1], int_tokens[2]));
	}
	
	/// now do sorting here.
	for (i = 0, k = 0; i < ref_cnt.size(); i++)
		for (j = 0; j < ref_cnt[i].size(); j++)
			itv_vec[k++] = (ref_cnt[i][j]);
	/*
	for (i = 0; i < itv_num; i++)
		std::cout << itv_vec[i]->begin << ", " << itv_vec[i]->end << ", " << itv_vec[i]->score << std::endl;
	*/

	/// scan each items to calculate maximum interval sum
	for (k = 1; k < itv_num; k++)
	{
		top = itv_num - 1;
		p =  bottom = 0;

		/// do binary search to find largest end value based on current start value.
		while (top >= bottom)
		{
			p = std::floor((top + bottom) / 2);
		
			if (itv_vec[p]->end < itv_vec[k]->begin) 
				bottom = p + 1;
			else if (itv_vec[p]->end >= itv_vec[k]->begin) 
				top = p - 1;
			else 
				break;
		}

		/// in case of the top is zero, we need some kind of alignment here.
		if (top == 0)
			best[k] = std::max(best[k - 1], itv_vec[0]->score + itv_vec[k]->score);
		else
		{
			if (top < 0) top = 0;
			best[k] = std::max(best[k - 1], best[top] + itv_vec[k]->score);
		}
	}
	
	std::cout << best[itv_num  - 1] << std::endl;
	is.close();

	return 0;  
}
