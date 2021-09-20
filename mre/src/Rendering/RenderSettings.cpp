#include "RenderSettings.h"

RenderSettings* RenderSettings::instance;
std::mutex RenderSettings::mutex;

RenderSettings* RenderSettings::getInstance() {
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr) {
        instance = new RenderSettings();
    }
    return instance;
}

void RenderSettings::setSettings() {
}

bool RenderSettings::getUseMultithreading() {
    return useMultithreading;
}

bool RenderSettings::getUseSupersampling() {
    return useSupersampling;
}

int RenderSettings::getSubRows() {
    return subRows;
}

int RenderSettings::getSubColumns() {
    return subColumns;
}

int RenderSettings::getMaxTraceDepth() {
    return maxTraceDepth;
}

int RenderSettings::getMaxSamples() {
    return maxSamples;
}

RenderSettings::RenderSettings() {
    useMultithreading = false;
    useSupersampling = true;
    subRows = 2;
    subColumns = 2;
    maxTraceDepth = 10;
    maxSamples = 1;
}

RenderSettings::~RenderSettings() {
}
