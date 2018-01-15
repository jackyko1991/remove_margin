#ifndef REMOVE_MARGIN_H
#define REMOVE_MARGIN_H

#include "typedef.h"

#include <boost/thread.hpp>
#include <boost/bind.hpp>  
#include <boost/asio/io_service.hpp>
#include <boost/filesystem.hpp>

class RemoveMargin
{
public:
	RemoveMargin();
	~RemoveMargin();

	void SetInputDirectory(boost::filesystem::path inputDir);
	void SetOutputDirectory(boost::filesystem::path outputDir);


private:
	boost::filesystem::path m_inputDir;
	boost::filesystem::path m_outputDir;
	
	bool m_mask;
	

};

#endif