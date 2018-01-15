/*
 * ChordWindowComponent.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: james
 */

#include "ChordWindowComponent.h"

namespace gndbnc {

ChordWindowComponent::ChordWindowComponent() {
    flexBox.alignContent = FlexBox::AlignContent::flexStart;
    flexBox.flexDirection = FlexBox::Direction::row;
    flexBox.justifyContent = FlexBox::JustifyContent::flexStart;
    flexBox.alignItems = FlexBox::AlignItems::flexStart;
    flexBox.flexWrap = FlexBox::Wrap::wrap;
}

ChordWindowComponent::~ChordWindowComponent() {

}

void ChordWindowComponent::paint (Graphics& g) {
	g.fillAll (Colours::white);
}

void ChordWindowComponent::resized() {
	flexBox.performLayout(getFlexBoxBounds());
}

void ChordWindowComponent::addFlexItem(Image image) {
	flexBox.items.add(FlexItem(200, 250).withMargin(10));

    auto &flexItem = flexBox.items.getReference(flexBox.items.size() - 1);

    auto *item = new FlexBoxItem(image);
    items.add(item);
    flexItem.associatedComponent = item;
    addAndMakeVisible(item);
}

Rectangle<float> ChordWindowComponent::getFlexBoxBounds() const
{
	return getLocalBounds().toFloat();
}

void ChordWindowComponent::setupChordWindow()
{
	flexBox.items.clear();

	for(auto img : chordImages) {
		addFlexItem(img);
	}
}

void ChordWindowComponent::setChordList(Array<Image> &images)
{
	if(chordImages.isEmpty() == false)
	{
		chordImages.clear();
	}
	chordImages.addArray(images);
}

} /* namespace gndbnc */
