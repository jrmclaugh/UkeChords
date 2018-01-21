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
using gndbnc::ChordWindowComponent;
using std::array;

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

private:

    void setupToggleButton (ToggleButton& tb, StringRef text, int x, int y);
    void buttonClicked (Button* b) override;

    ChordWindowComponent *chordWindow{nullptr};
    const int chordSelectionPanelWidth = 200;

	array<ToggleButton,12> rootButton;
	array<ToggleButton,18> typeButton;
    TextButton downloadButton;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
