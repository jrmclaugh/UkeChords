/*
 * FlexBoxItem.h
 *
 *  Created on: Jan 13, 2018
 *      Author: james
 */

#ifndef FLEXBOXITEM_H_
#define FLEXBOXITEM_H_

#include "../JuceLibraryCode/JuceHeader.h"


class FlexBoxItem : public Component {
public:

	FlexBoxItem(Image &i) {
		image = i;
	}

	void paint(Graphics& g) override {
		g.drawImageAt(image, 0, 0);
	}

	void mouseDown(const MouseEvent&) override {
		DBG(colour.toString());
	}

	Image image;
};


#endif /* FLEXBOXITEM_H_ */
