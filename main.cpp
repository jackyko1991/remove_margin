#include "remove_margin.h"

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
	try
	{
		boost::program_options::options_description desc{ 
			"Crop image and label with margins according to mask. If mask is not set, label is considered as mask \nExample usage: MarginCrop.exe -i ./input -o ./output" };
		desc.add_options()
			("help,h", "Print help")
			("input,i", boost::program_options::value<boost::filesystem::path>()->default_value("./input"), "Input data directory")
			("output,o", boost::program_options::value<boost::filesystem::path>()->default_value("./output"), "Output data directory")
			("mask,m", boost::program_options::value<bool>()->default_value(false),"Use mask, will override auto computed mask")
			("image-name", boost::program_options::value<std::string>()->default_value("image.nii.gz"), "Name of image data")
			("label-name", boost::program_options::value<std::string>()->default_value("label.nii.gz"), "Name of label data")
			("mask-name", boost::program_options::value<std::string>()->default_value("mask.nii.gz"), "Name of mask data")
			("margin", boost::program_options::value<unsigned int>()->default_value(0), "Set cropping margin")
			;

		boost::program_options::variables_map variableMap;
		boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), variableMap);

		if (variableMap.count("help") || argc == 1)
			std::cout << desc << std::endl;
		else
		{
			RemoveMargin removeMargin;

			if (variableMap.count("input"))
			{
				if (boost::filesystem::is_directory(variableMap["input"].as<boost::filesystem::path>()))
				{
					removeMargin.SetInputDirectory(variableMap["input"].as<boost::filesystem::path>());

				}
				else
					return 1;
			}

			if (variableMap.count("output"))
			{
				removeMargin.SetOutputDirectory(variableMap["output"].as<boost::filesystem::path>());
			}
			else
				return 1;

			if (variableMap.count("mask"))
			{
				removeMargin.SetUseMask(variableMap["mask"].as<bool>());
			}

			if (variableMap.count("image-name"))
			{
				removeMargin.SetImageName(variableMap["image-name"].as<std::string>());
			}

			if (variableMap.count("label-name"))
			{
				removeMargin.SetLabelName(variableMap["label-name"].as<std::string>());
			}

			if (variableMap.count("mask-name"))
			{
				removeMargin.SetMaskName(variableMap["mask-name"].as<std::string>());
			}

			if (variableMap.count("margin"))
			{
				removeMargin.SetMargin(variableMap["margin"].as<unsigned int>());
			}

			removeMargin.Run();
		}
			

	}
	catch (const boost::program_options::error &ex)
	{
		std::cerr << ex.what() << std::endl;
		return 0;
	}



}