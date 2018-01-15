#ifndef  TYPEDEF_H
#define TYPEDEF_H

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkLabelMap.h>
#include <itkLabelObject.h>
#include <itkOtsuThresholdImageFilter.h>
#include <itkImageFileWriter.h>
#include <itkLabelImageToLabelMapFilter.h>
#include <itkLabelMapToLabelImageFilter.h>
#include <itkAutoCropLabelMapFilter.h>
#include <itkExtractImageFilter.h>
#include <itkRegion.h>

typedef itk::Image<float, 3> FloatImageType;
typedef itk::Image<unsigned char, 3> LabelImageType;
typedef itk::LabelObject< unsigned char, 3 > LabelObjectType;
typedef itk::LabelMap< LabelObjectType > LabelMapType;

typedef itk::ImageFileReader<FloatImageType> ImageFileReaderType;
typedef itk::ImageFileReader<LabelImageType> LabelFileReaderType;

typedef itk::ImageFileWriter<FloatImageType> ImageFileWriterType;
typedef itk::ImageFileWriter<LabelImageType> LabelFileWriterType;

typedef itk::LabelImageToLabelMapFilter<LabelImageType, LabelMapType> LabelImageToLabelMapFilterType;
typedef itk::LabelMapToLabelImageFilter<LabelMapType, LabelImageType> LabelMapToLabelImageFilterType;

//typedef itk::OtsuThresholdImageFilter<FloatImageType, LabelImageType> OtsuFilterType;
typedef itk::AutoCropLabelMapFilter<LabelMapType> AutoCropLabelMapFilterType;


#endif // ! TYPEDEF_H
