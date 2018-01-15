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

//boost::filesystem::path dataFolder("G:/Deep_Learning/lisa-brain/testing/ventricle_and_vessel/testing");
////boost::filesystem::path labelFolder("G:/Deep_Learning/lisa-brain/DL_TEST_margin_remove");
//boost::filesystem::path outputFolder("G:/Deep_Learning/lisa-brain/testing/cropped/testing");
//std::cout << "Files in " << dataFolder << std::endl;

//std::vector<boost::thread *> threads;

//// create asio::io_service and thread_group

//boost::asio::io_service ioService;
//boost::thread_group threadpool;

//// start ioService processing loop. Tasks assigned with ioService.post() will start executing
//boost::asio::io_service::work work(ioService);

//// create threads to the thread pool. It will be maximum of computer threads - 1
//std::cout << boost::thread::hardware_concurrency() << std::endl;

//for (int i = 0; i < boost::thread::hardware_concurrency() - 1; i++)
//{
//	threadpool.create_thread(boost::bind(&boost::asio::io_service::run, &ioService));
//}

//for (boost::filesystem::directory_iterator it = boost::filesystem::directory_iterator(dataFolder);
//	it != boost::filesystem::directory_iterator(); ++it)
//{
//	boost::filesystem::path px = it->path();

//	boost::filesystem::path py = it->path().filename();

//	boost::filesystem::path imgFileIn("FLAIR_brain_norm.nii.gz");
//	boost::filesystem::path imgPathIn = px / imgFileIn;

//	//boost::filesystem::path maskFile("FLAIR_DilatedVentricle.nii.gz");
//	//boost::filesystem::path maskPath = px / maskFile;

//	boost::filesystem::path labelFileIn("FLAIR_ventricle_D.nii.gz");
//	boost::filesystem::path labelPathIn = px / labelFileIn;

//	boost::filesystem::create_directory(outputFolder / py);

//	boost::filesystem::path imgFileOut("image.nii.gz");
//	boost::filesystem::path imgPathOut = outputFolder / py / imgFileOut;

//	boost::filesystem::path labelFileOut("label.nii.gz");
//	boost::filesystem::path labelPathOut = outputFolder / py / labelFileOut;

//	//std::cout << imgPathIn << "\n";

//	// asssign task to thread pool
//	ioService.post(boost::bind(run, imgPathIn.string(), labelPathIn.string(), imgPathOut.string(), labelPathOut.string()));
//	//ioService.post(boost::bind(run, imgPathIn.string(), labelPathIn.string(), imgPathOut.string(), labelPathOut.string(), maskPath.string()));
//}

//// stop ioService processing loop. No new task can add to thread pool after this point
//ioService.stop();

//// wait until all threads in the thread pool finish processing
//threadpool.join_all();
//std::cout << "Process finish" << std::endl;

//system("pause");

//return 0;

////void run(std::string imgPathIn, std::string labelPathIn, std::string imgPathOut, std::string labelPathOut, std::string maskPath)
//void run(std::string imgPathIn, std::string labelPathIn, std::string imgPathOut, std::string labelPathOut)
//{
//	std::cout << "Cropping " << imgPathIn << std::endl;
//
//	// read image and label image
//	ImageFileReaderType::Pointer imageReader = ImageFileReaderType::New();
//	imageReader->SetFileName(imgPathIn);
//	imageReader->Update();
//
//	LabelFileReaderType::Pointer labelReader = LabelFileReaderType::New();
//	labelReader->SetFileName(labelPathIn);
//	labelReader->Update();
//
//	//LabelFileReaderType::Pointer maskReader = LabelFileReaderType::New();
//	//maskReader->SetFileName(maskPath);
//	//maskReader->Update();
//
//	//// otsu threshold for obtaining brain mask
//	//OtsuFilterType::Pointer otsuFilter = OtsuFilterType::New();
//	//otsuFilter->SetInput(imageReader->GetOutput());
//	//otsuFilter->SetInsideValue(0);
//	//otsuFilter->SetOutsideValue(1);
//	//otsuFilter->Update();
//
//	// crop to fit brain
//	LabelImageToLabelMapFilterType::Pointer labelImageToMapConverter = LabelImageToLabelMapFilterType::New();
//	//labelImageToMapConverter->SetInput(otsuFilter->GetOutput());
//	labelImageToMapConverter->SetInput(labelReader->GetOutput());
//	labelImageToMapConverter->Update();
//
//	itk::Size<3> cropBorderSize;
//	cropBorderSize.Fill(25);
//
//	AutoCropLabelMapFilterType::Pointer autoCropFilter = AutoCropLabelMapFilterType::New();
//	autoCropFilter->SetInput(labelImageToMapConverter->GetOutput());
//	autoCropFilter->SetCropBorder(cropBorderSize);
//	autoCropFilter->Update();
//
//	LabelMapToLabelImageFilterType::Pointer labelMapToImageConverter = LabelMapToLabelImageFilterType::New();
//	labelMapToImageConverter->SetInput(autoCropFilter->GetOutput());
//	labelMapToImageConverter->Update();
//
//	itk::ExtractImageFilter<FloatImageType, FloatImageType>::Pointer imgCropper = itk::ExtractImageFilter<FloatImageType, FloatImageType>::New();
//	imgCropper->SetInput(imageReader->GetOutput());
//	imgCropper->SetExtractionRegion(autoCropFilter->GetRegion());
//	imgCropper->Update();
//
//	itk::ExtractImageFilter<LabelImageType, LabelImageType>::Pointer labelCropper = itk::ExtractImageFilter<LabelImageType, LabelImageType>::New();
//	labelCropper->SetInput(labelReader->GetOutput());
//	labelCropper->SetExtractionRegion(autoCropFilter->GetRegion());
//	labelCropper->Update();
//
//	// output
//	ImageFileWriterType::Pointer imageWriter = ImageFileWriterType::New();
//	imageWriter->SetFileName(imgPathOut);
//	imageWriter->SetInput(imgCropper->GetOutput());
//	imageWriter->Write();
//
//	LabelFileWriterType::Pointer labelWriter = LabelFileWriterType::New();
//	labelWriter->SetFileName(labelPathOut);
//	labelWriter->SetInput(labelCropper->GetOutput());
//	labelWriter->Write();
//
//	std::cout << "Finish cropping " << imgPathIn << std::endl;
//}