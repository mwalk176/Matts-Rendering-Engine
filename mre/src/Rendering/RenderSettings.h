#ifndef RENDERSETTINGS_H
#define RENDERSETTINGS_H


#include <mutex>


class RenderSettings {
public:
	static RenderSettings* getInstance();
	RenderSettings(RenderSettings& r) = delete;
	void operator = (const RenderSettings&) = delete;

	void setSettings();

	bool getUseMultithreading();
	bool getUseSupersampling();
	int getSubRows();
	int getSubColumns();
	int getMaxTraceDepth();
	int getMaxSamples();

protected: 
	RenderSettings();
	~RenderSettings();

	bool useMultithreading;
	bool useSupersampling;
	int subRows;
	int subColumns;
	int maxTraceDepth;
	int maxSamples;


private:
	static RenderSettings* instance;
	static std::mutex mutex;



};






#endif