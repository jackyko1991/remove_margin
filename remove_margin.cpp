#include "remove_margin.h"

RemoveMargin::RemoveMargin()
{

}

RemoveMargin::~RemoveMargin()
{

}

void RemoveMargin::SetInputDirectory(boost::filesystem::path inputDir)
{
	m_inputDir = inputDir;
}

void RemoveMargin::SetOutputDirectory(boost::filesystem::path outputDir)
{
	m_outputDir = outputDir;
}

void RemoveMargin::SetUseMask(bool useMask)
{
	m_useMask = useMask;
}

void RemoveMargin::SetImageName(string imageName)
{
	m_imageName = imageName;
}

void RemoveMargin::SetLabelName(string labelName)
{
	m_labelName = labelName;
}

void RemoveMargin::SetMaskName(string maskName)
{
	m_maskName = maskName;
}

void RemoveMargin::SetMargin(unsigned int margin)
{
	m_margin = margin;
}

void RemoveMargin::Run()
{
	boost::filesystem::path imgPathIn = m_inputDir / boost::filesystem::path(m_imageName);
	boost::filesystem::path labelPathIn = m_inputDir / boost::filesystem::path(m_labelName);

	// read image and label image
	ImageFileReaderType::Pointer imageReader = ImageFileReaderType::New();
	if (boost::filesystem::exists(imgPathIn))
	{
		imageReader->SetFileName(imgPathIn.string());
		imageReader->Update();
	}
	else
	{
		std::cerr << "Image File: " << imgPathIn.string() << " not exist!!!" << std::endl;
		std::exit(1);
	}

	LabelFileReaderType::Pointer labelReader = LabelFileReaderType::New();
	if (boost::filesystem::exists(labelPathIn))
	{
		labelReader->SetFileName(labelPathIn.string());
		labelReader->Update();
	}
	else
	{
		std::cerr << "Label File: " << labelPathIn.string() << " not exist!!!" << std::endl;
		std::exit(1);
	}


	// handle the mask
	LabelImageType::Pointer mask = LabelImageType::New();
	if (m_useMask)
	{
		boost::filesystem::path maskPath = m_inputDir / boost::filesystem::path(m_maskName);

		if (boost::filesystem::exists(labelPathIn))
		{
			LabelFileReaderType::Pointer maskReader = LabelFileReaderType::New();
			maskReader->SetFileName(maskPath.string());
			maskReader->Update();
			mask->Graft(maskReader->GetOutput());
			mask->SetMetaDataDictionary(maskReader->GetOutput()->GetMetaDataDictionary());
		}
		else
		{
			std::cerr << "Mask File: " << maskPath.string() << " not exist!!!" << std::endl;
		}
	}
	else
	{
		mask->Graft(labelReader->GetOutput());
		mask->SetMetaDataDictionary(labelReader->GetOutput()->GetMetaDataDictionary());
	}


	// crop to fit brain
	LabelImageToLabelMapFilterType::Pointer labelImageToMapConverter = LabelImageToLabelMapFilterType::New();
	labelImageToMapConverter->SetInput(mask);
	labelImageToMapConverter->Update();
	
	itk::Size<3> cropBorderSize;
	cropBorderSize.Fill(m_margin);
	
	AutoCropLabelMapFilterType::Pointer autoCropFilter = AutoCropLabelMapFilterType::New();
	autoCropFilter->SetInput(labelImageToMapConverter->GetOutput());
	autoCropFilter->SetCropBorder(cropBorderSize);
	autoCropFilter->Update();
	
	LabelMapToLabelImageFilterType::Pointer labelMapToImageConverter = LabelMapToLabelImageFilterType::New();
	labelMapToImageConverter->SetInput(autoCropFilter->GetOutput());
	labelMapToImageConverter->Update();

	itk::ExtractImageFilter<FloatImageType, FloatImageType>::Pointer imgCropper = itk::ExtractImageFilter<FloatImageType, FloatImageType>::New();
	imgCropper->SetInput(imageReader->GetOutput());
	imgCropper->SetExtractionRegion(autoCropFilter->GetRegion());
	imgCropper->Update();

	itk::ExtractImageFilter<LabelImageType, LabelImageType>::Pointer labelCropper = itk::ExtractImageFilter<LabelImageType, LabelImageType>::New();
	labelCropper->SetInput(labelReader->GetOutput());
	labelCropper->SetExtractionRegion(autoCropFilter->GetRegion());
	labelCropper->Update();
	
	// output
	boost::filesystem::create_directory(m_outputDir);

	boost::filesystem::path imgFileOut("image.nii.gz");
	boost::filesystem::path imgPathOut = m_outputDir / imgFileOut;

	boost::filesystem::path labelFileOut("label.nii.gz");
	boost::filesystem::path labelPathOut = m_outputDir / labelFileOut;

	ImageFileWriterType::Pointer imageWriter = ImageFileWriterType::New();
	imageWriter->SetFileName(imgPathOut.string());
	imageWriter->SetInput(imgCropper->GetOutput());
	imageWriter->Write();
	
	LabelFileWriterType::Pointer labelWriter = LabelFileWriterType::New();
	labelWriter->SetFileName(labelPathOut.string());
	labelWriter->SetInput(labelCropper->GetOutput());
	labelWriter->Write();
	
	std::cout << "Finish cropping " << imgPathIn << std::endl;
}