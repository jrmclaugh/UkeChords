/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "UkeChordDownloader.h"
#include "ChordWindowComponent.h"
#include <iostream>

using std::cout;
using std::endl;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component,
							   public Button::Listener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;

    void setupChordSelectionPanel();
    void setupFlexBoxPanel();
    void addFlexItem(Colour colour);

private:

    void setupToggleButton (ToggleButton& tb, StringRef text, int x, int y);
    void buttonClicked (Button* b) override;

    gndbnc::ChordWindowComponent chordWindow;
    const int chordSelectionPanelWidth = 200;

	std::array<ToggleButton,12> rootButton;
	std::array<ToggleButton,18> typeButton;
    TextButton downloadButton;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
