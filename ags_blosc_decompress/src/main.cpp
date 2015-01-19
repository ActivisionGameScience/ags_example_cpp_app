#include <activision_game_science/blosc_wrapper.h>

#include <string>
#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>


using namespace std;


// for storing command-line options
struct ProgOpts
{
	bool help;
    std::string infile;
    std::string outfile;

	bool verifyOpts()
	{
		if(help)
			return true;

		if(!boost::filesystem::exists(infile) || !boost::filesystem::is_regular_file(infile))
		{
            std::cerr << "Input file does not exist" << std::endl;
			help = true;
			return false;
		}

		if(outfile == "")
		{
            std::cerr << "You must specify an output file" << std::endl;
			help = true;
			return false;
		}

		return true;
	}
};





// parses command-line options
ProgOpts getOpts(std::vector< std::string > & args)
{
	ProgOpts opts;
	// set defaults
	opts.help = false;

	// Set the options.
	int n_args = (int) args.size();
	int j = 1;
	int n = n_args;
	for(int i = 1; i < n; ++i) 
	{
		bool rm = false;

		if(args[j] == "-h" || args[j] == "-help") 
		{
			rm = true;
			opts.help = true; 
		}				
		if(args[j] == "-i")
		{
			args.erase(args.begin() + j);
			--n;
			opts.infile = boost::filesystem::path(args[j]).normalize().make_preferred().string();
			rm = true;
		}
		if(args[j] == "-o")
		{
			args.erase(args.begin() + j);
			--n;
			opts.outfile = boost::filesystem::path(args[j]).normalize().make_preferred().string();
			rm = true;
		}
		if(rm) 
			args.erase(args.begin() + j);
		else 
			++j;
	}

	return opts;
}





int main(int argc, char * argv[])
{
	//*********************
	// Command line parsing
	//*********************

	// Get executable options.
	bool good_opts;
	ProgOpts opts;
	if(argc > 1) // Parse from command line.
	{
		std::vector<std::string> args;
		for(int i = 0; i < argc; ++i)
			args.push_back(argv[i]);
		opts = getOpts(args);
		good_opts = opts.verifyOpts();
	}
	else // Hardcoded values if no command line specified.
	{
		std::cerr << "No options specified." << std::endl;
		opts.help = true;
		good_opts = false;
	}

	// Display the help.
	if(opts.help)
	{
		std::cout << "Usage: " << argv[0] << std::endl;
		std::cout << std::endl;		
		std::cout << "  -h              Displays this message" << std::endl;
		std::cout << "  -i              Input file" << std::endl;
		std::cout << "  -o              Output file" << std::endl;
		if(good_opts)
			return 0;
		else
			return -1;
	}


	//*****************
	// Work starts here
	//*****************

    // read file in
    size_t srcsize;
    std::vector<char> src;

    ifstream ifile(opts.infile.c_str(), ios::in|ios::binary|ios::ate);
    if (ifile.is_open()) {

        srcsize = ifile.tellg();  // this works because ios::ate starts at end of file
        ifile.seekg (0, ios::beg);

        src.resize(srcsize);
        ifile.read(&src[0], srcsize);  // should do better error handling here
        ifile.close();

    } else {
            
        std::cout << "Cannot read infile " << opts.infile << std::endl;
        return -1;
    }
    std::cout << "Read in " << srcsize << " bytes" << std::endl;

    
    // get BloscWrapper object
    activision_game_science::BloscWrapper b = activision_game_science::BloscWrapper();


    // allocate enough memory for decompressed buffer
    size_t dstsize = b.reserveNeededToDecompress(&src[0]);
    std::cout << "Reserving " << dstsize << " bytes" << std::endl;
    std::vector<char> dst = std::vector<char>(dstsize);


    // decompress and resize
    dstsize = b.decompress(&src[0], &dst[0], dstsize);
    dst.resize(dstsize);
    std::cout << "Decompressed to " << dstsize << " bytes" << std::endl;


    // write compressed stream out
    ofstream ofile(opts.outfile.c_str(), ios::out|ios::binary|ios::trunc);
    if (ofile.is_open()) {

        ofile.write(&dst[0], dstsize); // should do better error handling here
        ofile.close();
    } else {
            
        std::cout << "Cannot open file " << opts.infile << " for writing" << std::endl;
        return -1;
    }

    return 0;
}
