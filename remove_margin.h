#ifndef REMOVE_MARGIN_H
#define REMOVE_MARGIN_H

#include "typedef.h"

#include <boost/thread.hpp>
#include <boost/bind.hpp>  
#include <boost/asio/io_service.hpp>
#include <boost/filesystem.hpp>
#include <string>

class RemoveMargin
{
	typedef std::string string;
public:
	RemoveMargin();
	~RemoveMargin();
	void SetInputDirectory(boost::filesystem::path inputDir);
	void SetOutputDirectory(boost::filesystem::path outputDir);
	void SetUseMask(bool useMask);
	void SetImageName(string imageName);
	void SetLabelName(string labelName);
	void SetMaskName(string maskName);
	void SetMargin(unsigned int margin);
	void Run();

private:
	boost::filesystem::path m_inputDir;
	boost::filesystem::path m_outputDir;
	string m_imageName = "image.nii.gz";
	string m_labelName = "label.nii.gz";
	string m_maskName = "mask.nii.gz";
	
	bool m_useMask = false;
	unsigned int m_margin = 0;
};

#endif