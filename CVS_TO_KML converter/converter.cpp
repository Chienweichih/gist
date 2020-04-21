#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

void convert(char *filename) {

	ifstream file(filename);
	if(file.fail()) {
		cerr << "cannot open file: " << filename << endl;
		return;
	}

	string output("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<kml xmlns=\"http://earth.google.com/kml/2.2\">\n<Document>\n\t<name>youbike</name>\n");

	string line;

	getline( file, line, '\n'); //first line

	while(getline( file, line, '\n')) {

		istringstream ss(line);
		string token;
		vector<string> v;

		while(getline( ss, token, ','))
			v.push_back(token);

		output.append("\t<Placemark>\n\t\t<name>");
		output.append(v[1]);
		output.append("</name>\n\t\t<description><![CDATA[");
		output.append(v[7]);
		output.append("]]></description>\n\t\t<Point>\n\t\t\t<coordinates>");
		output.append(v[6] + "," + v[5]);
		output.append("</coordinates>\n\t\t</Point>\n\t</Placemark>\n");
	}

	output.append("</Document>\n</kml>");

	ofstream print("youbike.kml");
	print << output;
	print.close();
}

int main(int argc,char** argv) {
	if(argc != 1)
		convert( argv[1]);
}
