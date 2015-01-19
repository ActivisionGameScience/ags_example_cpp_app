#include <activision_game_science/ags_blosc_wrapper.h>

#include <string>

#include <boost/filesystem.hpp>



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
		std::cout << "  -h              Displays this message" << std::endl << std::endl;
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

    std::cout << opts.infile << " " << opts.outfile << std::endl; 

    return 0;
}
