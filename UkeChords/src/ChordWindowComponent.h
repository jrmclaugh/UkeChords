/*
 * ChordWindowComponent.h
 *
 *  Created on: Jan 6, 2018
 *      Author: james
 */

#ifndef CHORDWINDOWCOMPONENT_H_
#define CHORDWINDOWCOMPONENT_H_

#include "../JuceLibraryCode/JuceHeader.h"
#include "FlexBoxItem.h"

namespace gndbnc {

class ChordWindowComponent : public Component {
public:
	ChordWindowComponent();
	ChordWindowComponent(Array<Image> &images);
	virtual ~ChordWindowComponent();

    void paint (Graphics& g) override;
    void resized() override;

    void setupChordWindow();
    void setChordList(Array<Image> &images);

    Rectangle<float> getFlexBoxBounds() const;

private:
    void addFlexItem(Image image);
    void setupFlexBox();


    Array<Image> chordImages;

	FlexBox flexBox;
	OwnedArray<FlexBoxItem> items;
};

} /* namespace gndbnc */

#endif /* CHORDWINDOWCOMPONENT_H_ */
