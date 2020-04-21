void readFromStream(std::istream &stream,std::string streamName)
{
	std::ostringstream ss;
	ss << stream.rdbuf();
	std::string const source = ss.str();
	
	//source.begin(),source.end()
}

void readFromFiles(char **filenames,int num)
{
	std::cout << "--- read form Files ---" << std::endl;
	for(int cnt = 0;cnt < num;++cnt)
	{
		std::ifstream file(filenames[cnt]);

		if(file.fail())
		{
			std::cerr << "cannot open file: " << filenames[cnt] << std::endl;
			continue;
		}

		std::cout << "-- read from file: " << filenames[cnt] << std::endl;
		readFromStream(file,filenames[cnt]);
	}
}

int main(int argc,char** argv)
{
	if(argc != 1)
		readFromFiles(argv+1,argc-1);
}