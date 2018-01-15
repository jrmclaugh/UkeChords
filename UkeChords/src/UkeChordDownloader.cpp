/*
 * UkeChordDownloader.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: james
 */

#include "UkeChordDownloader.h"

namespace gndbnc {

static size_t write_text_data(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

static size_t write_file_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

std::string ExtractXMLValue(std::string buffer, std::string tag) {
	std::istringstream sa(buffer);
	std::string temp = "";

	bool valueFound = false;
	while(!valueFound && !sa.eof()) {
		getline(sa, temp, '>');
		if(temp.find(tag) != std::string::npos) {
			getline(sa, temp, '<');
			valueFound = true;
		}
	}

	return temp;
}

static bool grabXMLfile(URL url, std::string *buffer) {
	CURL *curl = curl_easy_init();
	if(curl) {
		CURLcode res;
		curl_easy_setopt(curl, CURLOPT_URL, url.toString(true).toRawUTF8());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_text_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);
		return true;
	}
	else {
		cout << "No init!" << endl;
		return false;
	}
}

static const char* grabFile(URL url) {
	// TODO: see if FILE can be replaced by juce::File (curl seems to require former)
	FILE *file;

	file = fopen("temp.png", "wb");

	CURL *curl = curl_easy_init();
	if(curl) {
	  CURLcode res;
	  cout << "Downloading: " << url.toString(true) << endl;
	  curl_easy_setopt(curl, CURLOPT_URL, url.toString(true).toRawUTF8());
	  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_file_data);

	  if(file) {
		  curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
		  res = curl_easy_perform(curl);
		  fclose(file);
	  }

	  curl_easy_cleanup(curl);
	}

	return "temp.png";
}

Image UkeChordDownloader::getChordImage(String note, String type) {
	// URL class get methods don't support ssl, always gets failure to connect
	// have to resort to buildling URL using class but using libcurl for actual download

	// steps for grabbing pic
	// 1. build URL based on note and type
	// 2. use CURL to grab XML
	// 3. parse XML to grab link of image
	// 4. download image itself
	// 5. draw image on screen (or pass to function that lays it out)
	std::string readBuffer;

	//1. build URL
	URL api (API_URL);
	api = api.withParameter("ak", API_KEY);
	api = api.withParameter("r", note);
	api = api.withParameter("typ", type);

	// 2. grab XML file
	grabXMLfile(api, &readBuffer);

	// 3. parse XML to grab link
	URL imageFile (ExtractXMLValue(readBuffer, CHORD_XML_TAG.toStdString()));

	// 4. download image (using link extracted)
	String localFile = grabFile(imageFile);

	// 5. print image to screen
	File file = File(localFile);
    Image img = ImageFileFormat::loadFrom(file);

    return img;
}

UkeChordDownloader::UkeChordDownloader() {
	// TODO Auto-generated constructor stub

}

UkeChordDownloader::~UkeChordDownloader() {
	// TODO Auto-generated destructor stub
}

} /* namespace gndbnc */
