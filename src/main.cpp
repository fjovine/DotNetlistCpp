#include <iostream>
#include <fstream>
#include <string>
#include "AbstractBitmapGenerator.h"
#include "DrillConnector.h"
#include "BitmapScanner.h"
#include "MonochromeBitmapAccessor.h"
#include "RealBitmapGenerator.h"
#include "meminfo.h"
#include <sys/stat.h>
#ifdef __MINGW32__
	#include <windows.h>
#endif

using namespace std;

/**
 * Creates a subfolder with the relative path.
 * @param path of the folder to be created.
 */
void makedir(string path) {
#ifdef __MINGW32__	
	CreateDirectory(path.c_str(), NULL );
#else
	mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
}

/**
 * Checks if the passed file exists.
 * @param filename of the file to be verified.
 * @return true if the passed file exists.
 */
bool file_exists(const string filename) {
	ifstream infile(filename);
	return infile.good();
}

/**
 * Loads the PNG bitmap contained by the file filename and returns it inside a \ref "BitmapScanner" class.
 * @param "filename" Filename of the PNG file.
 * @return A \ref "BitmapScanner" object containing the loaded bitmap.
 */
BitmapScanner * LoadAndScan (const string filename) {
	cout << "LoadAndScan (" << filename << ")" << endl;
	MonochromeBitmapAccessor layer(filename);
	BitmapScanner * result = new BitmapScanner(&layer);
	result->PrepareAll();
	return result;
}

/**
 * Gets the passed filename cutting of the file extension.
 * @returns the processed filename.
 */
string GetFilenameWithoutExtension(const string & filename) {
	size_t lastIndex = filename.find_last_of(".");
	return filename.substr(0, lastIndex);
}

/**
 * Generates the HTML file that permits showing each found net.
 * @param path The pathname of the PNG file to be scanned.
 * @param html list of lines composing the output HTML.
 * @param optionValues The options of the net list box.
 * @returns The list of HTML lines.
 */
void GenerateHtml(string path, vector<string> &html, vector<string> &optionValues) {
	html.push_back("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml/DTD/xhtml1 transitional.dtd\">");
	html.push_back("<html xmlns=\"http://www.w3.org/1999/xhtml\">");
	html.push_back("<head>");
	html.push_back("<title>DotNetlist</title>");
	html.push_back("</head>");
	html.push_back("<html>");
	html.push_back("<body>");
	html.push_back("<select id=\"dlist\" onChange=\"swapImage()\">");
	for (auto s : optionValues) {
		html.push_back(s);
	}
	html.push_back("</select>");
	html.push_back("<br/><br/>");
	html.push_back("<img id=\"imageToSwap\" src=\""+path+"/Net_1.png\" />");
	html.push_back("<script type=\"text/javascript\">");
	html.push_back("function swapImage(){");
	html.push_back("    var image = document.getElementById(\"imageToSwap\");");
	html.push_back("    var dropd = document.getElementById(\"dlist\");");
	html.push_back("    image.src = dropd.value;  ");
	html.push_back("};");
	html.push_back("</script>");
	html.push_back("</body>");
	html.push_back("</html>");
}

/**
 * Generates the links to the external bitmaps in the HTML file.
 * @param scanner The bitmap scanner to be used.
 * @param path The pathname of the PNG file to be scanned.
 * @param html A list of strings containing the HTML lines with the net lists.
 */
void GenerateNetLinks(BitmapScanner & scanner, string & path, vector<string> &html) {
	for (int netId : scanner.GetNetIds()) {
		string sline = to_string(netId);
		string s  = "<option value=\""+path+"/Net_"+sline+".png\">Net_"+sline+"</option>";
		html.push_back(s);
	}
}

/**
 * Processes a single PNG file representing a copper layer.
 * The nets, i.e. the areas in electrical contact are found, a bitmap with each net highlighted is generated as well
 * as a HTML file to show them properly.
 * @param "filename" Filename of the file containing the PNG image of the copper layer.
 */
void ProcessSingleLayer(const string & filename) {
	if (! file_exists(filename)) {
		cout << "File " << filename << " not found" << endl;
		return;
	}

	MonochromeBitmapAccessor topLayer(filename);
	BitmapScanner * scannerTopLayer = LoadAndScan(filename);
	auto path = string("./")+GetFilenameWithoutExtension(filename);
	makedir(path);
	for (int netId :scannerTopLayer->GetNetIds() ) {
		RealBitmapGenerator outBitmap(topLayer.GetBitmap(), topLayer.get_width(), topLayer.get_height());
		for (auto segment : scannerTopLayer ->GetSegmentsOfNet(netId)) {
			outBitmap.DrawSegment(segment, 100);
		}
		string outfile = path + "/Net_"+to_string(netId)+".png";
		cout << outfile << endl;
		outBitmap.SaveTo(outfile);
	}
	
	vector<string> netLinks;
	GenerateNetLinks(*scannerTopLayer, path, netLinks);

	vector<string> html;
	GenerateHtml(path, html, netLinks);
	fstream file;
	string htmlFile = path + ".html";
	file.open(htmlFile, ios::in | ios::out | ios::trunc);
	if (file.is_open()) {
		for (auto line : html) {
			file << line << endl;
		}
		file.close();
	} else {
		cout << "Unable to write :" << htmlFile << endl;
	}
}

/**
 * Loads and processes the PNG bitmaps containing the bitmaps representing the top, drill and bottom layers.
 * It generates bitmaps containing the copper layers with each available net highlighted and an HTML file to easily
 * show all the found nets.
 * @param topLayerFilename Filename of the PNG file containing the top copper layer.
 * @param drillLayerFilename Filename of the PNG file containing the drill layer.
 * @param bottomLayerFilename Filename of the PNG file containing the bottom copper layer.
 * @param path name of the project output. This is the name of the folder where bitmaps will be stored and the html will be path.HTML.
 * @param doHoles True if holes should be drawn on copper layers.
 * @param doMirror" True if the bottom layer should be mirrored in the output file produced.
 */
void ProcessDoubleLayerWithDrill(const string &topLayerFilename, const string &drillLayerFilename, const string &bottomLayerFilename, const string &path, bool doHoles, bool doMirror){
	if (! file_exists(topLayerFilename)) {
		cout << "The top layer file " << topLayerFilename << " was not found" << endl;
		return;
	}

	if (! file_exists(drillLayerFilename)) {
		cout << "The drill layer file " << topLayerFilename <<" was not found" << endl;
		return;
	}

	if (! file_exists(bottomLayerFilename)) {
		cout << "The bottom layer file " << topLayerFilename <<" was not found" << endl;
		return;
	}

	BitmapScanner * top = LoadAndScan(topLayerFilename);
	BitmapScanner * drill = LoadAndScan(drillLayerFilename);
	BitmapScanner * bottom = LoadAndScan(bottomLayerFilename);

	MonochromeBitmapAccessor topLayer(topLayerFilename);
	MonochromeBitmapAccessor bottomLayer(bottomLayerFilename);
	MonochromeBitmapAccessor drillLayer(drillLayerFilename);
	DrillScanner drillScanner(*drill);

	DrillConnector connector(*top, *bottom, drillScanner);
	connector.ComputeGlobalNet();

	makedir(path);

	if (doHoles)
	{
		MonochromeBitmapAccessor drillPlane(drillLayerFilename);
		vector<unsigned char> * bitmap = drillPlane.GetBitmap();
		for (int x = 0; x < drillPlane.get_width(); x++) {
			for (int y = 0; y < drillPlane.get_height(); y++) {
				if (drillPlane.pixel_at(x, y)) {
					topLayer.set_pixel(x, y, 0xFF000000); // the pixels of the holes are black
					bottomLayer.set_pixel(x, y, 0xFF000000);
				}
			}
		}
	}

	// Generates the bitmaps with the highlighted segments.
	// Bottom layer is mirrored
	auto nets = connector.GetNets();
	int netCount = nets.size();
	for (int key : nets)
	{
		RealBitmapGenerator topBitmap(topLayer.GetBitmap(), topLayer.get_width(), topLayer.get_height());
		RealBitmapGenerator bottomBitmap(bottomLayer.GetBitmap(), bottomLayer.get_width(), bottomLayer.get_height());
		for (auto layerNet : connector.GetLayerNetsOfNet(key))
		{
			if (layerNet.getLayerId() == TOPLAYER)
			{
				for (auto segment : top->GetSegmentsOfNet(layerNet.getNetId()))
				{
					topBitmap.DrawSegment(segment, 100);
				}
			}
			else
			{
				for (auto segment : bottom->GetSegmentsOfNet(layerNet.getNetId()))
				{
					bottomBitmap.DrawSegment(segment, 100);
				}
			}
		}

		int margin = 20;
		RealBitmapGenerator full(
			topBitmap.getWidth() + bottomBitmap.getWidth() + margin,
			topBitmap.getHeight());
		
		full.CopyBitmap(topBitmap.GetBitmap(), 0, 0, topBitmap.getWidth(), topBitmap.getHeight());
		full.CopyBitmap(bottomBitmap.GetBitmap(), topBitmap.getWidth() + margin, 0, bottomBitmap.getWidth(), bottomBitmap.getHeight(), doMirror);
		string outFile =  path+"/"+"Net_"+to_string(key)+".png";
		cout << "Save " << outFile << " / " << netCount << endl;
		full.SaveTo(outFile);
	}
	
	vector<string> netLinks;
	for (int netId : connector.GetNets()) {
		string sline = to_string(netId);
		string s  = "<option value=\""+path+"/Net_"+sline+".png\">Net_"+sline+"</option>";
		netLinks.push_back(s);
	}
	
	vector<string> html;
	GenerateHtml(path, html, netLinks);
	fstream file;
	string htmlFile = path + ".html";
	file.open(htmlFile, ios::in | ios::out | ios::trunc);
	if (file.is_open()) {
		for (auto line : html) {
			file << line << endl;
		}
		file.close();
	} else {
		cout << "Unable to write :" << htmlFile << endl;
	}
}

/**
 * Entry point of the application.
 * It is a console application accepting the names of the PNG bitmap to be
 * processed as parameters.
 * The first PNG is the top layer, the second one is the drill layer while the third is the bottom layer.
 * It generates a folder containing all the found networks found and an HTML file
 * that graphically shows them.
 * @param argc Count of the passed arguments
 * @param argv command line arguments.
 */
int main (int argc, char * argv[]) {
	if (argc == 2) {
		ProcessSingleLayer(argv[1]);
	} else {
		ProcessDoubleLayerWithDrill(argv[1], argv[2], argv[3], "blob", true, true);


//		cout << "Syntax DotNetlist <topLayer>" << endl;
	}
}