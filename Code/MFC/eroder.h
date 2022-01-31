#if !defined ERODER
#define ERODER

#include "cv.h"

#define DEFAULT_NITERATIONS 3

class Eroder {

  private:

	  // private attributes
	  IplImage *output;
	  int nIterations;

  public:

	  // empty constructor
	  Eroder() : nIterations(DEFAULT_NITERATIONS), output(0) { 

		  // default parameter initialization here
	  }

	  // getters and setters
	  void setNumberOfIterations(int n) {

		  nIterations= n;
	  }

	  int getNumberOfIterations() {

		  return nIterations;
	  }

	  IplImage* getOutputImage() {

		  return output;
	  }

	  // to check if an initialization is required
	  bool isInitialized(IplImage *image) {

		  return output && (output->width == image->width) 
			            && (output->height == image->height);
	  }

	  // for all memory allocation
	  void initialize(IplImage *image) {

		  cvReleaseImage(&output);
		  output= cvCreateImage(cvSize(image->width,image->height),
										image->depth, image->nChannels);
	  }

	  // the processing of the image
	  void process(IplImage *image) {

		  cvErode(image, output, 0, nIterations);
	  }

	  // the method that checks for initilization
	  // and then process the image
	  inline void processImage(IplImage *image) {

		  if (!isInitialized(image)) {

			  initialize(image);
		  }

		  process(image);
	  }

	  // memory de-allocation
	  void release() {

		  cvReleaseImage(&output);
	  }

	  ~Eroder() {

		  release();
	  }
};

#endif
