
// RMIT University Vietnam
// Course: EEET2482 Software Engineering Design
// Assignment: 1
// Created date: 07/11/2020 (DD/MM/YYYY)
// Last modified date: 15/11/2020 (DD/MM/YYYY)

// Author: Group 18, members including:
// Vu Viet Minh (s3790708)
// Nguyen Chu Son (s3742891)
// Quach Gia Vi (s3757317)


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void printGroupInfo()
{
	/* PRINT FORMAT
	** ASSIGNMENT 1 GROUP<TT>
	** sWWWWWWW, sWWWWWWW@rmit.edu.vn, FirstName, LastName
	** sXXXXXXX, sXXXXXXX@rmit.edu.vn, FirstName, LastName
	** sYYYYYYY, sYYYYYYY@rmit.edu.vn, FirstName, LastName
	** sZZZZZZZ, sZZZZZZZ@rmit.edu.vn, FirstName, LastName
	*/

	cout << "ASSIGNMENT 1 GROUP 18" << endl;
	cout << "s3790708, s3790708@rmit.edu.vn, Minh, Vu" << endl;
	cout << "s3742891, s3742891@rmit.edu.vn, Son, Nguyen" << endl;
	cout << "s3757317, s3757317@rmit.edu.vn, Vi, Quach" << endl;
	cout << "sWWWWWWW, sWWWWWWW@rmit.edu.vn, FirstName, LastName" << endl;
}


/////////////////////////////////////////////////////////
// ~~~~ START OF DESCRIPTIVE STATISTICS SECTION ~~~~ //

/*
** calculate the mean from a csv file that contains data for two variables
*/
void calculateMean(const char* file)
{
	// init some values
	double x, y;
	double mean_x = 0.00;
	double mean_y = 0.00;

	// total amount of values
	long val_count = 0;

	// string to skip
	char str;

	// read file
	ifstream infile(file);

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to get the sum and
	// count the total amount of values
	while (infile >> x >> str >> y)
	{
		// get sum for mean calculation
		mean_x += x;
		mean_y += y;
		// count up amount of values
		val_count++;
	}

	// calculate the mean values
	mean_x /= val_count;
	mean_y /= val_count;

	// close file
	infile.close();

	// print out mean values of both variable x and y
	printf("mean_x = %.2f - mean_y = %.2f\n", mean_x, mean_y);
}

/*
** compare function for qsort from programiz
** https://www.programiz.com/cpp-programming/library-function/cstdlib/qsort
** modified to work correctly with this program
*/
int compare(const void* a, const void* b)
{
	const double* x = (double*)a;
	const double* y = (double*)b;

	if (*x > *y)
		return 1;
	else if (*x < *y)
		return -1;
	return 0;
}

/*
** calculate the median from a csv file that contains data for two variables
*/
void calculateMedian(const char* file)
{
	// init some variables to easily keep track
	double x, y;

	// total amount of values
	long val_count = 0;

	// string to skip (skip comma when going through each line)
	char str;

	// median value position (position n)
	double median_n = 0.00;

	// variables to store median values
	double median_x = 0.00;
	double median_y = 0.00;

	// read file to count the total amount of values
	ifstream infile(file);

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to get the total amount of values
	// to init arrays with correct size with x and y values
	while (infile >> x >> str >> y)
		val_count++; // count up amount of values

	// create dynamically-allocate memory arrays
	// to add all x and y values then sort from 
	// smallest to largest to find median
	double* xList = new double[val_count];
	double* yList = new double[val_count];

	// reset infile object to read file again
	infile.clear();	// clear fail and eof bits
	infile.seekg(0, ios::beg); // go back to the start

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to assign x and y values
	// to their respective arrays
	int i = 0;
	while (infile >> x >> str >> y)
	{
		xList[i] = x;
		yList[i] = y;
		i++;
	}

	// sort x and y value arrays from smallest to largest
	qsort(xList, val_count, sizeof(double), compare);
	qsort(yList, val_count, sizeof(double), compare);

	// total amount of values is an odd number
	if (val_count % 2 == 1)
	{
		// calculate the n position of median
		median_n = (val_count + 1) / 2;

		// median is at n-th position in the array
		median_x = xList[int(median_n) - 1];
		median_y = yList[int(median_n) - 1];
	}
	// total amount of values is an even number
	else
	{
		// calculate the n position of median
		median_n = val_count / 2;

		// add value at n position and n+1 position
		median_x = xList[int(median_n) - 1];
		median_x += xList[int(median_n)];

		// divide the sum by 2 to find median
		median_x /= 2;

		// add value at n position and n+1 position
		median_y = yList[int(median_n) - 1];
		median_y += yList[int(median_n)];

		// divide the sum by 2 to find median
		median_y /= 2;
	}

	// close file
	infile.close();

	// delete arrays to free up memory
	delete[] xList;
	delete[] yList;

	// print out median values of both variable x and y
	printf("median_x = %.2f - median_y = %.2f\n", median_x, median_y);
}

/*
** calculate the mode from a csv file that contains data for two variables
*/
void calculateMode(const char* file)
{
	// init some variables to easily keep track
	double x, y;

	// total amount of values
	long val_count = 0;

	// string to skip (skip comma when going through each line)
	char str;

	// variables to store final mode values
	double mode_x;
	double mode_y;

	// store number to remember and count up occurrences
	double number;
	// total amount of number count
	int count = 1;
	// total amount of the mode number count
	int modeCount = 1;

	// read file to count the total amount of values
	ifstream infile(file);

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to get the total amount of values
	// to init arrays with correct size with x and y values
	while (infile >> x >> str >> y)
		val_count++; // count up amount of values

	// create dynamically-allocate memory arrays
	// to add and then sort from smallest to largest
	// to find the mode values
	double* xList = new double[val_count];
	double* yList = new double[val_count];

	// reset infile object to read file again
	infile.clear();	// clear fail and eof bits
	infile.seekg(0, ios::beg); // go back to the start

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to assign x and y values
	// to their respective arrays
	int i = 0;
	while (infile >> x >> str >> y)
	{
		xList[i] = x;
		yList[i] = y;
		i++;
	}

	// sort x and y value arrays from smallest to largest
	qsort(xList, val_count, sizeof(double), compare);
	qsort(yList, val_count, sizeof(double), compare);

	// set number and mode to first value in x value array
	number = xList[0];
	mode_x = number;

	// loop through x list array to count numbers and find the mode
	for (int i = 1; i < val_count; i++)
	{
		// same number
		if (xList[i] == number)
		{
			// add up the number occurrence count
			count++;
		}
		// different number
		else
		{
			if (count > modeCount)
			{
				// update mode occurrences
				modeCount = count;
				// number is the new mode
				mode_x = number;
			}
			// reset count for the new number
			count = 1;
			// keep track of new number by assigning to number var
			number = xList[i];
		}
	}

	// reset values to find y mode value
	count = 1;
	modeCount = 1;
	number = yList[0];
	mode_y = number;

	// loop through y list array to count numbers and find the mode
	for (int i = 1; i < val_count; i++)
	{
		// same number
		if (yList[i] == number)
		{
			// add up the number occurrence count
			count++;
		}
		// different number
		else
		{
			if (count > modeCount)
			{
				// update mode occurrences
				modeCount = count;
				// number is the new mode
				mode_y = number;
			}
			// reset count for the new number
			count = 1;
			// keep track of new number by assigning to number variable
			number = yList[i];
		}
	}

	// close file
	infile.close();

	// delete arrays to free up memory
	delete[] xList;
	delete[] yList;

	// print out mode values of both variable x and y
	printf("mode_x = %.2f - mode_y = %.2f\n", mode_x, mode_y);
}

/*
** calculate the variance and standard deviation from
** a csv file that contains data for two variables
*/
void calculateVarianceAndStandardDeviation(const char* file)
{
	// init some variables to easily keep track
	double x, y;

	// total amount of values
	long val_count = 0;

	// string to skip (skip comma when going through each line)
	char str;

	// variables to store mean, variance, and standard deviation values
	double mean_x = 0.00;
	double mean_y = 0.00;
	double var_x = 0.00;
	double var_y = 0.00;
	double stdev_x = 0.00;
	double stdev_y = 0.00;

	// read file to count the total amount of values
	ifstream infile(file);

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to set sum for mean calculation 
	// and get the total amount of values to init
	// arrays with correct size with x and y values
	while (infile >> x >> str >> y)
	{
		// get sum for mean calculation
		mean_x += x;
		mean_y += y;
		// count up amount of values
		val_count++;
	}

	// calculate the mean values
	mean_x /= val_count;
	mean_y /= val_count;

	// reset infile object to read file again
	infile.clear();	// clear fail and eof bits
	infile.seekg(0, ios::beg); // go back to the start

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through file again to add up 
	// all (value - mean)^2 to perform 
	// the next step of variance calculation
	while (infile >> x >> str >> y)
	{
		var_x += (x - mean_x)*(x - mean_x);
		var_y += (y - mean_y)*(y - mean_y);
	}

	// calculate the variance
	var_x /= val_count - 1;
	var_y /= val_count - 1;

	// calculate the standard deviation
	stdev_x = sqrt(var_x);
	stdev_y = sqrt(var_y);

	// close file
	infile.close();

	// print out variance and standard deviation values of both variable x and y
	printf("var_x = %.2f - var_y = %.2f\n", var_x, var_y);
	printf("stdev_x = %.2f - stdev_y = %.2f\n", stdev_x, stdev_y);
}

/*
** calculate the mean absolute deviations from
** a csv file that contains data for two variables
*/
void calculateMeanAbsoluteDeviations(const char* file)
{
	// init some variables to easily keep track
	double x, y;

	// total amount of values
	long val_count = 0;

	// string to skip (skip comma when going through each line)
	char str;

	// variables to store mean and Mean Absolute Deviations values
	double mean_x = 0.00;
	double mean_y = 0.00;
	double mad_x = 0.00;
	double mad_y = 0.00;

	// read file to count the total amount of values
	ifstream infile(file);

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to set sum for mean calculation 
	// and get the total amount of values to init
	// arrays with correct size with x and y values
	while (infile >> x >> str >> y)
	{
		// get sum for mean calculation
		mean_x += x;
		mean_y += y;
		// count up amount of values
		val_count++;
	}

	// calculate the mean values
	mean_x /= val_count;
	mean_y /= val_count;

	// reset infile object to read file again
	infile.clear();	// clear fail and eof bits
	infile.seekg(0, ios::beg); // go back to the start

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// add up all item minus mean squared to perform the
	// next step of Mean Absolute Deviations calculation
	while (infile >> x >> str >> y)
	{
		mad_x += abs(x - mean_x);
		mad_y += abs(y - mean_y);
	}

	// calculate the Mean Absolute Deviations values
	mad_x /= val_count;
	mad_y /= val_count;

	// close file
	infile.close();

	// print out Mean Absolute Deviations values of both variable x and y
	printf("mad_x = %.2f - mad_y = %.2f\n", mad_x, mad_y);
}

/*
** calculate the first quartile from a csv file that contains data for two variables
*/
void calculateQ1(const char* file)
{
	// init some variables to easily keep track
	double x, y;

	// total amount of values
	long val_count = 0;

	// string to skip (skip comma when going through each line)
	char str;

	// first quartile value position (position n)
	double q1_n = 0.00;

	// variables to store the final first quartile values
	double q1_x = 0.00;
	double q1_y = 0.00;

	// read file to count the total amount of values
	ifstream infile(file);

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to get the total amount of values
	// to init arrays with correct size with x and y values
	while (infile >> x >> str >> y)
		val_count++; // count up amount of values

	// create dynamically-allocate memory arrays
	// to add all x and y values then sort from 
	// smallest to largest to find first quartile values
	double* xList = new double[val_count];
	double* yList = new double[val_count];

	// reset infile object to read file again
	infile.clear();	// clear fail and eof bits
	infile.seekg(0, ios::beg); // go back to the start

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to assign x and y values
	// to their respective arrays
	int i = 0;
	while (infile >> x >> str >> y)
	{
		xList[i] = x;
		yList[i] = y;
		i++;
	}

	// sort x and y value arrays from smallest to largest
	qsort(xList, val_count, sizeof(double), compare);
	qsort(yList, val_count, sizeof(double), compare);

	// total amount of x and y values is an odd number
	if (val_count % 2 == 1)
	{
		// calculate the n of first quartile
		q1_n = (val_count + 1) / 4;

		// first quartile value is at q1_n-th position in the array
		q1_x = xList[int(q1_n) - 1];
		q1_y = yList[int(q1_n) - 1];
	}
	// total amount of x and y values is an even number
	else
	{
		// calculate the n of first quartile
		q1_n = val_count / 4;

		q1_x = xList[int(q1_n) - 1];
		q1_x += xList[int(q1_n)];
		q1_x /= 2;

		q1_y = yList[int(q1_n) - 1];
		q1_y += yList[int(q1_n)];
		q1_y /= 2;
	}

	// close file
	infile.close();

	// delete arrays to free up memory
	delete[] xList;
	delete[] yList;

	// print out first quartile values of both variable x and y
	printf("q1_x = %.2f - q1_y = %.2f\n", q1_x, q1_y);
}

/*
** calculate the third quartile from a csv file that contains data for two variables
*/
void calculateQ3(const char* file)
{
	// init some variables to easily keep track
	double x, y;

	// total amount of values
	long val_count = 0;

	// string to skip (skip comma when going through each line)
	char str;

	// third quartile value position (position n)
	double q3_n = 0.00;

	// variables to store final third quartile values
	double q3_x = 0.00;
	double q3_y = 0.00;

	// read file for the first time to
	// count the total amount of values
	ifstream infile(file);

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to get the total amount of values
	// to init arrays with correct size with x and y values
	while (infile >> x >> str >> y)
		val_count++; // count up amount of values

	// create dynamically-allocate memory arrays
	// to add all x and y values then sort from 
	// smallest to largest to find third quartile values
	double* xList = new double[val_count];
	double* yList = new double[val_count];

	// reset infile object to read file again
	infile.clear();	// clear fail and eof bits
	infile.seekg(0, ios::beg); // go back to the start

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to assign x and y values
	// to their respective arrays
	int i = 0;
	while (infile >> x >> str >> y)
	{
		xList[i] = x;
		yList[i] = y;
		i++;
	}

	// sort x and y value arrays from smallest to largest
	qsort(xList, val_count, sizeof(double), compare);
	qsort(yList, val_count, sizeof(double), compare);

	// total amount of values is an odd number
	if (val_count % 2 == 1)
	{
		// calculate the n of third quartile
		q3_n = (val_count + 1) * 3 / 4;

		// third quartile is at q3_n-th position in the array
		q3_x = xList[int(q3_n) - 1];
		q3_y = yList[int(q3_n) - 1];
	}
	// total amount of values is an even number
	else
	{
		// calculate the n of third quartile
		q3_n = val_count * 3 / 4;

		q3_x = xList[int(q3_n) - 1];
		q3_x += xList[int(q3_n)];
		q3_x /= 2;

		q3_y = yList[int(q3_n) - 1];
		q3_y += yList[int(q3_n)];
		q3_y /= 2;
	}

	// close file
	infile.close();

	delete[] xList;
	delete[] yList;

	// print out third quartile values of both variable x and y
	printf("q3_x = %.2f - q3_y = %.2f\n", q3_x, q3_y);
}

// ~~~~~ END OF DESCRIPTIVE STATISTICS SECTION ~~~~~ //
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
// ~~~~ START OF INFERENTIAL STATISTICS SECTION ~~~~ //

/*
** calculate the covariance from a csv file that contains data for two variables
*/
void calculateCovariance(const char* file)
{
	// init some variables to easily keep track
	double x, y;

	// total amount of values
	long val_count = 0;

	// string to skip (skip comma when going through each line)
	char str;

	// variables to store covariance value
	double cov_x_y = 0.00;

	// variables to store mean values
	double mean_x = 0.00;
	double mean_y = 0.00;

	// read file to count the total amount of values
	ifstream infile(file);

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to get the total amount of values
	// to init arrays with correct size with x and y values
	while (infile >> x >> str >> y)
	{
		// get sum for mean calculation
		mean_x += x;
		mean_y += y;
		// count up amount of values
		val_count++;
	}

	// calculate the mean values
	mean_x /= val_count;
	mean_y /= val_count;

	// reset infile object to read file again
	infile.clear();	// clear fail and eof bits
	infile.seekg(0, ios::beg); // go back to the start

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to get x and y values to
	// add up all (x values - mean x)*(y values - mean y) to perform 
	// the next step of covariance calculation
	while (infile >> x >> str >> y)
		cov_x_y += (x - mean_x)*(y - mean_y);

	// calculate the covariance
	cov_x_y /= val_count - 1;

	// close file
	infile.close();

	// print out covariance value
	printf("cov(x_y) = %.2f\n", cov_x_y);
}

/*
** calculate the correlation coefficient from a csv file that contains data for two variables
*/
void calculateCorrelationCoefficient(const char* file)
{
	// init some variables to easily keep track
	double x, y;

	// total amount of values
	long val_count = 0;

	// string to skip (skip comma when going through each line)
	char str;

	// variable to store mean, standard deviation, 
	// and correlation coefficient value
	double mean_x = 0.00;
	double mean_y = 0.00;
	double stdev_x = 0.00;
	double stdev_y = 0.00;
	double r_x_y = 0.00;

	// read file to count the total amount of values
	ifstream infile(file);

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to get the total amount of values
	// to init arrays with correct size with x and y values
	while (infile >> x >> str >> y)
	{
		// get sum for mean calculation
		mean_x += x;
		mean_y += y;
		// count up amount of values
		val_count++;
	}

	// calculate the mean values
	mean_x /= val_count;
	mean_y /= val_count;

	// reset infile object to read file again
	infile.clear();	// clear fail and eof bits
	infile.seekg(0, ios::beg); // go back to the start

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to get x and y values to
	// add up all (values - mean)^2 to perform 
	// the next step of standard deviation calculation
	while (infile >> x >> str >> y)
	{
		stdev_x += (x - mean_x)*(x - mean_x);
		stdev_y += (y - mean_y)*(y - mean_y);
	}

	// get the final standard deviation values
	stdev_x = sqrt(stdev_x / (val_count - 1));
	stdev_y = sqrt(stdev_y / (val_count - 1));

	// reset infile object to read file again
	infile.clear();	// clear fail and eof bits
	infile.seekg(0, ios::beg); // go back to the start

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to get x and y values to 
	// add up all ((x - mean_x)/stdev_x)*((y - mean_y)/stdev_y)
	// then divide the sum by (total value count - 1) to get the 
	// correlation coefficient value
	while (infile >> x >> str >> y)
		r_x_y += ((x - mean_x) / stdev_x)*((y - mean_y) / stdev_y);
	r_x_y /= val_count - 1;

	// close file
	infile.close();

	// print out correlation coefficient value of x and y
	printf("r(x_y) = %f\n", r_x_y);
}

/*
** calculate the Linear Regression from a csv file that contains data for two variables
*/
void calculateLinearRegression(const char* file)
{
	// init some variables to easily keep track
	double x, y;

	// total amount of values
	long val_count = 0;

	// string to skip (skip comma when going through each line)
	char str;

	// variables to store mean, standard deviation, and correlation coefficient values
	double mean_x = 0.00;
	double mean_y = 0.00;
	double stdev_x = 0.00;
	double stdev_y = 0.00;
	double r_x_y = 0.00;

	// variables to store slope (a) and intercept (b)
	double a, b;

	// read file to count the total amount of values
	ifstream infile(file);

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to get the total amount of values
	// to init arrays with correct size with x and y values
	while (infile >> x >> str >> y)
	{
		// get sum for mean calculation
		mean_x += x;
		mean_y += y;
		// count up amount of values
		val_count++;
	}

	// calculate the mean values
	mean_x /= val_count;
	mean_y /= val_count;

	// reset infile object to read file again
	infile.clear();	// clear fail and eof bits
	infile.seekg(0, ios::beg); // go back to the start

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to get x and y values to
	// add up all (values - mean)^2 to perform 
	// the next step of standard deviation calculation
	while (infile >> x >> str >> y)
	{
		stdev_x += (x - mean_x)*(x - mean_x);
		stdev_y += (y - mean_y)*(y - mean_y);
	}

	// get the final standard deviation values
	stdev_x = sqrt(stdev_x / (val_count - 1));
	stdev_y = sqrt(stdev_y / (val_count - 1));

	// reset infile object to read file again
	infile.clear();	// clear fail and eof bits
	infile.seekg(0, ios::beg); // go back to the start

	// skip first line
	infile >> str >> str >> str;	// read x, ',', and y

	// go through each line to get x and y values to 
	// add up all ((x - mean_x)/stdev_x)*((y - mean_y)/stdev_y)
	// then divide the sum by (total value count - 1) to get the 
	// correlation coefficient value
	while (infile >> x >> str >> y)
		r_x_y += ((x - mean_x) / stdev_x)*((y - mean_y) / stdev_y);
	r_x_y /= val_count - 1;

	// calculate the slope (a)
	a = r_x_y * stdev_x / stdev_y;

	// calculate the intercept (b)
	b = mean_y - a * mean_x;

	// close file
	infile.close();

	// print out correlation coefficient values of both variables x and y
	printf("y = %f * x + %f\n", a, b);
}

// ~~~~~ END OF INFERENTIAL STATISTICS SECTION ~~~~~ //
/////////////////////////////////////////////////////////

void runAllCalculations(const char* file)
{
	cout << "DESCRIPTIVE STATISTICS" << endl;
	cout << "Mean values" << endl;
	calculateMean(file);

	cout << endl;

	cout << "Median values" << endl;
	calculateMedian(file);

	cout << endl;

	cout << "Mode values" << endl;
	calculateMode(file);

	cout << endl;

	cout << "Variance and stand deviation values" << endl;
	calculateVarianceAndStandardDeviation(file);

	cout << endl;

	cout << "Mean Absolute Deviations values" << endl;
	calculateMeanAbsoluteDeviations(file);

	cout << endl;

	cout << "First quartile values" << endl;
	calculateQ1(file);

	cout << endl;

	cout << "Third quartile values" << endl;
	calculateQ3(file);

	cout << endl;

	cout << "INFERENTIAL STATISTICS" << endl;
	cout << "Covariance values" << endl;
	calculateCovariance(file);

	cout << endl;

	cout << "Correlation coefficient values" << endl;
	calculateCorrelationCoefficient(file);

	cout << endl;

	cout << "Linear Regression" << endl;
	calculateLinearRegression(file);
}

/*
** check if string is a number
** return true if string is a valid number
** and return false otherwise
*/
bool is_number(const char *val)
{
	int i = 0;
	int dot_counter = 0;
	if (val[0] == '+' || val[0] == '-')
		i++;
	while (val[i] != '\0')
	{
		if (val[i] == '.')
		{
			dot_counter++;
			if (dot_counter > 1)
				return false;
		}
		else if (val[i] < '0' || val[i] > '9')
			return false;
		i++;
	}
	return true;
}

int main(int argc, char * argv[])
{
	//////////////////////////////////////////////
	//     THIS SECTION IS FOR ERROR CHECKS     //
	//        BEFORE RUNNING THE PROGRAM        //
	//////////////////////////////////////////////
	// program requires 1 argument
	if (argc > 2) // has more than 1 argument, exit with error message
	{
		cerr << "Program only accepts 1 argument!" << endl;
		return 1;
	}
	else if (argc != 2) // not 1 argument, exit with error message
	{
		cerr << "Insert file name as argument to run program!" << endl;
		return 1;
	}

	// file is not .csv file, exit with error message
	if (argv[1][strlen(argv[1]) - 3] != 'c' && argv[1][strlen(argv[1]) - 2] != 's' && argv[1][strlen(argv[1]) - 1] != 'v')
	{
		cerr << "File needs to be a .csv file!" << endl;
		return 1;
	}

	// read file to check file validity
	ifstream infile(argv[1]);

	// check if file exists, if not, exit with error message
	if (!infile)
	{
		cerr << "File doesn't exist!" << endl;
		return 1;
	}

	// check if file is an empty file
	if (infile.peek() == ifstream::traits_type::eof())
	{
		cerr << "File is empty!" << endl;
		return 1;
	}

	// check if the data format is correct and exit the program 
	// with an error if the data isn't in the csv format
	// and also check if there's any data in the file or just 
	// empty lines
	string line;
	int commaCount = 0;
	bool is_not_empty = false;
	int lineCount = 0;

	// go through each line and get line as string until the end
	while (getline(infile, line))
	{
		// skip first line
		if (lineCount > 0)
		{
			// line is not empty
			if (!line.empty())
				is_not_empty = true;
		}

		// loop through each character in the string
		// to count the amount of commas
		for (int i = 0; i < line.length(); i++)
		{
			// comma found, increase increment
			if (line[i] == ',')
				commaCount++;
			// more than 1 comma, exit program with error
			if (commaCount > 1)
			{
				cerr << "Wrong data format, program exiting!" << endl;
				return 1;
			}
		}
		// reset count for next line
		commaCount = 0;
		lineCount++;
	}

	// no data in file, exit with error
	if (!is_not_empty)
	{
		cerr << "There's no data in file!" << endl;
		return 1;
	}

	// reset infile object to read file again
	infile.clear();	// clear fail and eof bits
	infile.seekg(0, ios::beg); // go back to the start

	line = "";
	// string 1 to represent data x
	string string_1;
	// string 2 to represent data y
	string string_2;
	// boolean to switch to write to 2nd string
	bool is_string_2 = false;
	// get delimiter's position in string
	long pos;

	infile >> line;	// read the first line to skip checking first line

	// go through each line to get the entire line as string
	// and split the string by the comma delimiter to 2 strings
	// and check if they're valid numbers
	while (infile >> line)	// read each line with data and take 
	{						// them as string and assign to line
		// get position of comma delimiter
		pos = line.find(',');

		// go through each character of the line string
		// to split into two strings representing x and y data
		for (int i = 0; i < line.length(); i++)
		{
			// comma delimiter position reached, 
			// switch to writing to string 2 (representing y data)
			if ((line[i] == ',' && i == pos))
			{
				is_string_2 = true;
				// jump to next loop
				continue;
			}
			// write value after comma delimiter 
			// to string 2 (representing y data)
			if (is_string_2)
				string_2 += line[i];
			// comma not reached, write to string 
			// 1 (representing x data)
			else
				string_1 += line[i];
		}

		// if x and y are not valid numbers, exit with error message
		if (!is_number(string_1.c_str()) || !is_number(string_2.c_str()))
		{
			cerr << "Invalid number found in file, program exiting!" << endl;
			return 1;
		}

		// check passed, reset values for next line
		string_1 = "";
		string_2 = "";
		is_string_2 = false;
	}

	infile.close();
	///////////////////////////////////////////
	//     END OF ERROR CHECKING SECTION     //
	///////////////////////////////////////////

	// run the program
	runAllCalculations(argv[1]);

	// make space for group info printing
	cout << endl;
	cout << endl;
	// print group info
	printGroupInfo();

	return 0;
}
