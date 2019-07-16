#include "cstdlib"
#include "iostream"
#include "TFile.h"
#include "cstring"
#include "TLegend.h"
#include "TGraph.h"
#include "TH3.h"
#include "TH2.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TMath.h"
#include "TText.h"
#include "TPaveText.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TAttFill.h"
#include "TColor.h"
#include "string"
#include "fstream"

using namespace std;

void makeTxtFromCSV_Uni(char *csvin);
int countLines(char* filelist);
fstream& goToLine(fstream& file, unsigned int num);
void mpvCrossCheck(char *uniplast, char *gsu);
float findMPV(string tilename);
void makeTxtFromCSV_GSU(char *csvin);
int countLines(string filelist);

void makeTxtFromCSV_Uni(char *csvin) //Note this is specifically for Uniplast data
{
  fstream outputboi;
  outputboi.open("CSV_output_UNI.txt",ios::app);
  fstream inputbois;
  inputbois.open(csvin);
  int nFiles = countLines(csvin);
  
  for(int i = 0; i < nFiles; i++)
    {
      string inputline;
      inputbois >> inputline;
      fstream csvboi; csvboi.open(inputline.c_str());
      
      for(int j = 12; j < 22; j++)
	{
	  goToLine(csvboi,j);
	  string tilename;
	  float MPV;
	  float dumb;
	  string dummy;
	  csvboi >> dumb >> dumb >> dummy >> tilename >> MPV;
	  outputboi << tilename << '\t' << MPV  << endl;
	}
    }
  
  outputboi.close();
}

void makeTxtFromCSV_GSU(char *csvin)// And this is specifically for GSU data
{
  fstream outputboi;
  outputboi.open("CSV_output_GSU.txt",ios::app);
  fstream inputbois;
  inputbois.open(csvin);

  int nFiles = 12;
  for(int i = 0; i < 12; i++)
    {
      string name;
      inputbois >> name;
      int nLines = countLines(name); cout << "nLines: " << nLines << endl;
      fstream database; database.open(name.c_str());
      for(int j = 1; j < nLines; j++)
	{
	  goToLine(database,j);
	  string tilename, dummy;
	  float  mpv;
	  database >> dummy >> dummy >> tilename >> dummy >> dummy>> dummy >> dummy >> mpv;
	  outputboi << tilename << '\t' << mpv << endl;
	}
    }
  outputboi.close();
}
		 
  

void mpvCrossCheck(char *uniplast, char *gsu)
{
  fstream unidat; unidat.open(uniplast);
  fstream gsudat; gsudat.open(gsu);

  TH2F *crosscheck = new TH2F("uniplastvgsu","uniplastvgsu",20,300,1200,20,300,1000);

  int nGLines = countLines(gsu);
  int nULines = countLines(uniplast);
  int missingTiles = 0;
  for(int i = 0; i < nGLines; i++)
    {
      string gsutile;
      float gsuMPV;
      gsudat >> gsutile >> gsuMPV;
      int missCheck = 0;
      for(int j = 0; j < nULines; j++)
	{
	  string unitile; float uniMPV;
	  goToLine(unidat,j);
	  unidat >> unitile >> uniMPV;
	  if(!strcmp(unitile.c_str(),gsutile.c_str()))
	    {
	      crosscheck -> Fill(uniMPV,gsuMPV);
	      break;
	    }
	  else
	    {
	      missCheck++;
	    }
	  if(missCheck == nULines)
	    {
	      missingTiles++;
	      cout << "Missing Tile " << gsutile << endl;
	    }
	}
    }
  cout << "Number of tiles not found: " << missingTiles << endl;
  crosscheck -> SetTitle(";Uniplast MPV; GSU MPV");
  crosscheck -> Draw("colz");
  
}




  
int countLines(char *filelist) {
    int number_of_lines = 0;
    std::string line;
    std::ifstream myfile(filelist);

    while (std::getline(myfile, line))++number_of_lines;
    myfile.seekg (0, ios::beg);
    return number_of_lines;

}

int countLines(string filelist) {
    int number_of_lines = 0;
    std::string line;
    std::ifstream myfile(filelist);

    while (std::getline(myfile, line))++number_of_lines;
    myfile.seekg (0, ios::beg);
    return number_of_lines;

}

fstream& goToLine(fstream& file, unsigned int num)
{
  file.seekg(0);
  for(int i = 0; i < num; i++)
    {
      file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
  return file;
}

