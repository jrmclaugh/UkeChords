/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize(1280, 800);

	setupChordSelectionPanel();

	chordWindow = new gndbnc::ChordWindowComponent();
	addAndMakeVisible(chordWindow);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::setupChordSelectionPanel()
{
    auto rootGroup = new GroupComponent ("roots", "Root");
    addAndMakeVisible(rootGroup);
    rootGroup->setBounds (getRight() - chordSelectionPanelWidth + 10, 15, 70, 290);

    int i = 0;
    int leftMargin = rootGroup->getX() + 5;
    int topMargin = rootGroup->getY() + 15;

    setupToggleButton (rootButton[0],    "A",     leftMargin, topMargin + i++ * 22);
    setupToggleButton (rootButton[1],    "Bb",    leftMargin, topMargin + i++ * 22);
    setupToggleButton (rootButton[2],    "B",     leftMargin, topMargin + i++ * 22);
    setupToggleButton (rootButton[3],    "C",     leftMargin, topMargin + i++ * 22);
    setupToggleButton (rootButton[4],    "Db",    leftMargin, topMargin + i++ * 22);
    setupToggleButton (rootButton[5],    "D",     leftMargin, topMargin + i++ * 22);
    setupToggleButton (rootButton[6],    "Eb",    leftMargin, topMargin + i++ * 22);
    setupToggleButton (rootButton[7],    "E",     leftMargin, topMargin + i++ * 22);
    setupToggleButton (rootButton[8],    "F",     leftMargin, topMargin + i++ * 22);
    setupToggleButton (rootButton[9],    "Gb",    leftMargin, topMargin + i++ * 22);
    setupToggleButton (rootButton[10],   "G",     leftMargin, topMargin + i++ * 22);
    setupToggleButton (rootButton[11],   "Ab",    leftMargin, topMargin + i++ * 22);

    auto typeGroup = new GroupComponent ("types", "Type");
    addAndMakeVisible(typeGroup);
    typeGroup->setBounds (rootGroup->getRight() + 10, 15, 80, 420);

    i = 0;
    leftMargin = typeGroup->getX() + 5;
    topMargin = typeGroup->getY() + 15;

    // "major, "minor", "aug, "dim", "7", "m7", "maj7", "m7b5", "sus2", "sus4", "7sus4", "6", "m6", "add9", "m9", "9", "11", "13"

    setupToggleButton (typeButton[0],    "major",     leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[1],    "minor",     leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[2],    "aug",       leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[3],    "dim",       leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[4],    "7",         leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[5],    "m7",        leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[6],    "maj7",      leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[7],    "m7b5",      leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[8],    "sus2",      leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[9],    "sus4",      leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[10],   "7sus4",     leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[11],   "6",         leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[12],   "m6",        leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[13],   "add9",      leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[14],   "m9",        leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[15],   "9",         leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[16],   "11",        leftMargin, topMargin + i++ * 22);
    setupToggleButton (typeButton[17],   "13",        leftMargin, topMargin + i++ * 22);


    int displayWidth = 120;
    int displayHeight = 40;
    int selectionWidth = typeGroup->getRight() - rootGroup->getX();
    int displayX = rootGroup->getX() + ((selectionWidth - displayWidth) / 2);
    int displayY = typeGroup->getBottom() + 50;
    displayButton.setButtonText("Display");
    displayButton.setBounds(displayX, displayY, displayWidth, displayHeight);
    displayButton.addListener(this);
    addAndMakeVisible(displayButton);

    int clearWidth = 120;
    int clearHeight = 20;
    int clearX = displayX;
    int clearY = displayY + 50;
    clearButton.setButtonText("Clear Selections");
    clearButton.setBounds(clearX, clearY, clearWidth, clearHeight);
    clearButton.addListener(this);
    addAndMakeVisible(clearButton);
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::grey);
}

void MainContentComponent::resized()
{
	if(chordWindow != nullptr) {
		chordWindow->setBounds(getLocalBounds()
				.withTrimmedRight (chordSelectionPanelWidth)
				.reduced (10));
		chordWindow->setupChordWindow();
		chordWindow->resized();
	}
}

void MainContentComponent::setupToggleButton (ToggleButton& tb, StringRef text, int x, int y)
{
    tb.setButtonText (text);
    tb.setToggleState (false, dontSendNotification);
    tb.setBounds (x, y, 60, 22);

    addAndMakeVisible (tb);
}

void MainContentComponent::buttonClicked (Button* b)
{
	if(b == &displayButton) {
		gndbnc::UkeChordDownloader downloader;
		Array<Image> images;

		for(auto& r : rootButton) {
			for(auto& t : typeButton) {
				if(r.getToggleState() == true && t.getToggleState() == true)
					images.add(downloader.getChordImage(r.getButtonText(), t.getButtonText()));
			}
		}

		if(chordWindow != nullptr) {
			delete chordWindow;
			chordWindow = new gndbnc::ChordWindowComponent(images);
			addAndMakeVisible(chordWindow);
		}
		resized();
	}

	if(b == &clearButton) {
		for(auto& r : rootButton) {
			r.setToggleState(false, NotificationType::dontSendNotification);
		}

		for(auto& t : typeButton) {
			t.setToggleState(false, NotificationType::dontSendNotification);
		}
	}

}
