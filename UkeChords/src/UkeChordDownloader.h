/*
 * UkeChordDownloader.h
 *
 *  Created on: Jan 6, 2018
 *      Author: james
 */

#ifndef UKECHORDDOWNLOADER_H_
#define UKECHORDDOWNLOADER_H_

#include "../JuceLibraryCode/JuceHeader.h"
#include <curl/curl.h>
#include <sstream>
#include <iostream>
using std::cout;
using std::endl;

namespace gndbnc {

class UkeChordDownloader {
public:
	UkeChordDownloader();
	virtual ~UkeChordDownloader();

	Image getChordImage(String note, String type);

private:
    const String API_KEY = "e459fddcf1bfa5a6545c86693868aedf";
    const String API_URL = "https://ukulele-chords.com/get";
    const String CHORD_XML_TAG = "chord_diag";
};

} /* namespace gndbnc */

#endif /* UKECHORDDOWNLOADER_H_ */
