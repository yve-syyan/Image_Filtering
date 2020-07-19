// Copyright (c) 2015-2018 Songyu Yan, Daniel Keefe, TAs, & Regents
// of the University of Minnesota.
#include <iostream>
#include <string>
#include <cstring>
#include <deque>
#include "gtest/gtest.h"
#include "imagetools/image_editor.h"
#include "mia/command_line_processor.h"
#include "mia/image_editor_commands.h"

class MiaAppTest : public :: testing :: Test {
	void SetUp() override { 
		buffer_ = new image_tools::PixelBuffer(1024, 780, image_tools::ColorData(1, 1, 1));
		image_editor_  = new image_tools::ImageEditor(buffer_);
        filesource = "resources/";
	}
	
	void TearDown() override {
		delete image_editor_;
		delete buffer_;
	}

 protected:
  image_tools::ImageEditor *image_editor_;
  image_tools::PixelBuffer* buffer_ ;
  std::string filesource;
  
  char** str_to_charr(std::vector<std::string> v, int argc) {
	char** argv = new char*[argc];
	for(int i = 0; i < argc;  i++) {
		argv[i] = new char[v[i].length()+1];
		std::strcpy (argv[i], (v.at(i)).c_str());
	}
	return argv;
}
  std::string help_ =  
  std::string("usage: mia infile.png [image processing commands ...]")+
  "outfile.png\n"+
  "infile.png:\tinput image file in png format\n"+
  "outfile.png:\tfilename to use for saving the result\n\n"+
  "image processing comamnds:\n"+
  "-blur r: \tapply a gaussian blur of radius r\n"+
  "-edgedetect: \tapply an edge detection filter\n"+
  "-sharpen r: \tapply a sharpening filter of radius r\n"+
  "-red s: \tscale the red channel by factor s\n"+
  "-green s:\tscale the green channel by factor s\n"+
  "-blue s: \tscale the blue channel by factor s\n"+
  "-quantize n:\tquantize each color channel into n bins\n"+
  "-saturate s: \tsaturate colors by scale factor s\n"+
  "-threshold c: \tthreshold using cutoff value c\n"+
  "-motionblur-n-s r:\tnorth-south motion blur with kernel radius r\n"+
  "-motionblur-e-w r:\teast-west motion blur with kernel radius r\n"+
  "-motionblur-ne-sw r: ne-sw motion blur with kernel radius r\n"+
  "-motionblur-nw-se r: nw-se motion blur with kernel radius r\n";
};

TEST_F(MiaAppTest, NumberCommandRead) {

	const char* blur_one[] = {"mia", "resources/in.png", "-blur", "1.0", "out.png"};	
	std::vector<std::string> v1(blur_one, std::end(blur_one));
	const char* edge[] = {"mia", "resources/in.png", "-edgedetect", "out.png"};	
	std::vector<std::string> v2(edge, std::end(edge));
	const char* zero[] = {"mia", "resources/in.png", "out.png"};
	std::vector<std::string> v3(zero, std::end(zero));
	const char* two[] = {"mia", "resources/in.png", "-edgedetect", "-blur", "1.0", "out.png"};
    std::vector<std::string> v4(two, std::end(two));
    
	  image_tools::CommandLineProcessor blur_one_command_(image_editor_);
	  blur_one_command_.image_tools::CommandLineProcessor::ProcessCommandLine(5, str_to_charr(v1,5));
      std::vector<image_tools::ImageEditorCommand*> blur_vec_ = blur_one_command_.getcmd();
	  int blur_num_ = blur_vec_.size();
	  EXPECT_EQ(3, blur_num_) << "one command with two inputs incorrect";

	  image_tools::CommandLineProcessor edge_one_command_(image_editor_);
	  edge_one_command_.image_tools::CommandLineProcessor::ProcessCommandLine(4, str_to_charr(v2,4));
      std::vector<image_tools::ImageEditorCommand*> edge_vec_ = edge_one_command_.getcmd();
	  int edge_num_ = edge_vec_.size();
	  EXPECT_EQ(3, edge_num_) << "one command with one input incorrect";

	  image_tools::CommandLineProcessor zero_command_(image_editor_);
	  zero_command_.image_tools::CommandLineProcessor::ProcessCommandLine(3, str_to_charr(v3,3));
      std::vector<image_tools::ImageEditorCommand*> zero_vec_ = zero_command_.getcmd();
	  int zero_num_ = zero_vec_.size();
	  EXPECT_EQ(2, zero_num_) << "one command with one input incorrect";

	  image_tools::CommandLineProcessor two_command_(image_editor_);
	  two_command_.image_tools::CommandLineProcessor::ProcessCommandLine(6, str_to_charr(v4,6));
      std::vector<image_tools::ImageEditorCommand*> two_vec_ = two_command_.getcmd();
	  int two_num_ =  two_vec_.size();
	  EXPECT_EQ(4, two_num_) << "one command with one input incorrect";
}
 
TEST_F(MiaAppTest, ValidCommand) {
	  const char* blur_noinput_[] = {"mia", "-blur", "1.0", "out.png"};
      std::vector<std::string> v1(blur_noinput_, std::end(blur_noinput_));
	  const char* blur_nooutput_[]= {"mia", "resources/in.png", "-blur", "1.0"};
      std::vector<std::string> v2(blur_nooutput_, std::end(blur_nooutput_));
	  const char* blur_wrongarg_[] = {"mia", "resources/in.png", "-blur", "a", "out.png"};
      std::vector<std::string> v3(blur_wrongarg_, std::end(blur_wrongarg_));
	  const char* blur_wrongspell_[] = {"mia", "resources/in.png", "-Blur", "1.0", "out.png"};
      std::vector<std::string> v4(blur_wrongspell_, std::end(blur_wrongspell_));
	  const char* blur_insufficient_[] = {"mia", "a"};
      std::vector<std::string> v5(blur_insufficient_, std::end(blur_insufficient_));
	
	  testing::internal::CaptureStdout();
	  image_tools::CommandLineProcessor blur_input_(image_editor_);
	  blur_input_.image_tools::CommandLineProcessor::ProcessCommandLine(4, str_to_charr(v1, 4));
	  std::string err1 = testing::internal::GetCapturedStdout();
	  std::string correct1 = "invalid message missing input file\n" + help_;
	  EXPECT_NE(err1, correct1) << "input detection not effective";

	  testing::internal::CaptureStdout();
	  image_tools::CommandLineProcessor blur_output_(image_editor_);
	  blur_output_.image_tools::CommandLineProcessor::ProcessCommandLine(4, str_to_charr(v2, 4));
	  std::string err2 = testing::internal::GetCapturedStdout();
	  std::string correct2 = "invalid message missing output file\n" + help_;
	  EXPECT_NE(err2, correct2) << "output detection not effective";

	  testing::internal::CaptureStdout();
	  image_tools::CommandLineProcessor blur_arg_(image_editor_);
	  blur_arg_.image_tools::CommandLineProcessor::ProcessCommandLine(5, str_to_charr(v3,5));
	  std::string err3 = testing::internal::GetCapturedStdout();
	  std::string correct3 = "invalid message invalid argument needs float\n" + help_;
	  EXPECT_NE(err3, correct3) << "argument not effective";

	  testing::internal::CaptureStdout();
	  image_tools::CommandLineProcessor blur_spell_(image_editor_);
	  blur_spell_.image_tools::CommandLineProcessor::ProcessCommandLine(5, str_to_charr(v4,5));
	  std::string err4 = testing::internal::GetCapturedStdout();
	  std::string correct4 = "invalid message -Blur\n" + help_;
	  EXPECT_NE(err4, correct4) << "command spell detection not effective\n" + help_;
      
      testing::internal::CaptureStdout();
	  image_tools::CommandLineProcessor insufficient_(image_editor_);
	  insufficient_.image_tools::CommandLineProcessor::ProcessCommandLine(2, str_to_charr(v5,2));
	  std::string err5 = testing::internal::GetCapturedStdout();
	  std::string correct5 = "invalid message -Blur\n" + help_;
	  EXPECT_NE(err5, correct5) << "insufficient argument\n" + help_;
}

TEST_F(MiaAppTest, CorrectCommand) {
	const char* blur_c_[] = {"mia", "resources/in.png", "-blur", "10.0", "out.png"};
    std::vector<std::string> v1(blur_c_, std::end(blur_c_));
	image_tools::CommandLineProcessor blured_(image_editor_);
	blured_.image_tools::CommandLineProcessor::ProcessCommandLine(5, str_to_charr(v1,5));
    std::vector<image_tools::ImageEditorCommand*> b_cmd_ = blured_.getcmd();
	image_tools::BlurFilterCommand* blurCmd = dynamic_cast<image_tools::BlurFilterCommand*>(b_cmd_.at(2));
	EXPECT_EQ(NULL, blurCmd) << "blur command not processed";
    
    const char* edge_c_[] = {"mia", "resources/in.png", "-edgedetect", "out.png"};
    std::vector<std::string> v2(edge_c_, std::end(edge_c_));
	image_tools::CommandLineProcessor edge_(image_editor_);
	edge_.image_tools::CommandLineProcessor::ProcessCommandLine(4, str_to_charr(v2,4));
    std::vector<image_tools::ImageEditorCommand*> ed_cmd_ = edge_.getcmd();
	image_tools::EdgeFilterCommand* edgeCmd = dynamic_cast<image_tools::EdgeFilterCommand*>(ed_cmd_.at(2));
	EXPECT_EQ(NULL, edgeCmd) << "edge command not processed";
    
    const char* sharpen_c_[] = {"mia", "resources/in.png", "-sharpen", "5.0", "out.png"};
    std::vector<std::string> v3(sharpen_c_, std::end(sharpen_c_));
	image_tools::CommandLineProcessor sharpen_(image_editor_);
	sharpen_.image_tools::CommandLineProcessor::ProcessCommandLine(5, str_to_charr(v3,5));
    std::vector<image_tools::ImageEditorCommand*> sh_cmd_ = sharpen_.getcmd();
	image_tools::SharpenFilterCommand* sharpenCmd = dynamic_cast<image_tools::SharpenFilterCommand*>(sh_cmd_.at(2));
	EXPECT_EQ(NULL, sharpenCmd) << "sharpen command not processed";
    
    const char* red_c_[] = {"mia", "resources/in.png", "-red", "5.0", "out.png"};
    std::vector<std::string> v4(red_c_, std::end(red_c_));
	image_tools::CommandLineProcessor red_(image_editor_);
	red_.image_tools::CommandLineProcessor::ProcessCommandLine(5, str_to_charr(v4,5));
    std::vector<image_tools::ImageEditorCommand*> red_cmd_ = red_.getcmd();
	image_tools::ChannelsFilterCommand* redCmd = dynamic_cast<image_tools::ChannelsFilterCommand*>(red_cmd_.at(2));
	EXPECT_EQ(NULL, redCmd) << "red command not processed";
    
    const char* green_c_[] = {"mia", "resources/in.png", "-green", "5.0", "out.png"};
    std::vector<std::string> v5(green_c_, std::end(green_c_));
	image_tools::CommandLineProcessor green_(image_editor_);
	green_.image_tools::CommandLineProcessor::ProcessCommandLine(5, str_to_charr(v5,5));
    std::vector<image_tools::ImageEditorCommand*> gr_cmd_ = green_.getcmd();
	image_tools::ChannelsFilterCommand* greenCmd = dynamic_cast<image_tools::ChannelsFilterCommand*>(gr_cmd_.at(2));
	EXPECT_EQ(NULL, greenCmd) << "green command not processed";
    
    const char* blue_c_[] = {"mia", "resources/in.png", "-blur", "5.0", "out.png"};
    std::vector<std::string> v6(blue_c_, std::end(blue_c_));
	image_tools::CommandLineProcessor blue_(image_editor_);
	blue_.image_tools::CommandLineProcessor::ProcessCommandLine(5, str_to_charr(v6,5));
    std::vector<image_tools::ImageEditorCommand*> blue_cmd_ = blue_.getcmd();
	image_tools::ChannelsFilterCommand* blueCmd = dynamic_cast<image_tools::ChannelsFilterCommand*>(blue_cmd_.at(2));
	EXPECT_EQ(NULL, blueCmd) << "blue command not processed";
    
    const char* quantize_c_[] = {"mia", "resources/in.png", "-quantize", "3", "out.png"};
    std::vector<std::string> v7(quantize_c_, std::end(quantize_c_));
	image_tools::CommandLineProcessor quantize_(image_editor_);
	quantize_.image_tools::CommandLineProcessor::ProcessCommandLine(5, str_to_charr(v7,5));
    std::vector<image_tools::ImageEditorCommand*> qu_cmd_ = quantize_.getcmd();
	image_tools::QuantizeFilterCommand* quantizeCmd = dynamic_cast<image_tools::QuantizeFilterCommand*>(qu_cmd_.at(2));
	EXPECT_EQ(NULL, quantizeCmd) << "quantize command not processed";
    
    const char* saturate_c_[] = {"mia", "resources/in.png", "-saturate", "3.0", "out.png"};
    std::vector<std::string> v8(saturate_c_, std::end(saturate_c_));
	image_tools::CommandLineProcessor saturate_(image_editor_);
	saturate_.image_tools::CommandLineProcessor::ProcessCommandLine(5, str_to_charr(v8,5));
    std::vector<image_tools::ImageEditorCommand*> satu_cmd_ = saturate_.getcmd();
	image_tools::SaturateFilterCommand* saturateCmd = dynamic_cast<image_tools::SaturateFilterCommand*>(satu_cmd_.at(2));
	EXPECT_EQ(NULL, saturateCmd) << "saturate command not processed";
    
    const char* threshold_c_[] = {"mia", "resources/in.png", "-threshold", "3.0", "out.png"};
    std::vector<std::string> v9(threshold_c_, std::end(threshold_c_));
	image_tools::CommandLineProcessor threshold_(image_editor_);
	threshold_.image_tools::CommandLineProcessor::ProcessCommandLine(5, str_to_charr(v9,5));
    std::vector<image_tools::ImageEditorCommand*> thre_cmd_ = threshold_.getcmd();
	image_tools::ThresholdFilterCommand* thresholdCmd = dynamic_cast<image_tools::ThresholdFilterCommand* >(thre_cmd_.at(2));
	EXPECT_EQ(NULL, thresholdCmd) << "threshold command not processed";
    
    const char* motionns_c_[] = {"mia", "resources/in.png", "-motionblur-n-s", "3.0", "out.png"};
    std::vector<std::string> v10(motionns_c_, std::end(motionns_c_));
	image_tools::CommandLineProcessor motionns_(image_editor_);
	motionns_.image_tools::CommandLineProcessor::ProcessCommandLine(5, str_to_charr(v10,5));
    std::vector<image_tools::ImageEditorCommand*> mons_cmd_ = motionns_.getcmd();
	image_tools::MotionBlurFilterCommand* motionnsCmd = dynamic_cast<image_tools::MotionBlurFilterCommand* >(mons_cmd_.at(2));
	EXPECT_EQ(NULL, motionnsCmd) << "motionblur north-south command not processed";
    
    const char* motionew_c_[] = {"mia", "resources/in.png", "-motionblur-e-w", "3.0", "out.png"};
    std::vector<std::string> v11(motionew_c_, std::end(motionew_c_));
	image_tools::CommandLineProcessor motionew_(image_editor_);
	motionew_.image_tools::CommandLineProcessor::ProcessCommandLine(5, str_to_charr(v11,5));
    std::vector<image_tools::ImageEditorCommand*> moew_cmd_ = motionew_.getcmd();
	image_tools::MotionBlurFilterCommand* motionewCmd = dynamic_cast<image_tools::MotionBlurFilterCommand*>(moew_cmd_.at(2));
	EXPECT_EQ(NULL, motionewCmd) << "motionblur east-west command not processed";
    
    const char* motionnesw_c_[] = {"mia", "resources/in.png", "-motionblur-ne-sw", "3.0", "out.png"};
    std::vector<std::string> v12(motionnesw_c_, std::end(motionnesw_c_));
	image_tools::CommandLineProcessor motionnesw_(image_editor_);
	motionnesw_.image_tools::CommandLineProcessor::ProcessCommandLine(5,str_to_charr(v12,5));
    std::vector<image_tools::ImageEditorCommand*> monesw_cmd_ = motionnesw_.getcmd();
	image_tools::MotionBlurFilterCommand* motionneswCmd = dynamic_cast<image_tools::MotionBlurFilterCommand*>(monesw_cmd_.at(2));
	EXPECT_EQ(NULL, motionneswCmd) << "motionblur ne-sw command not processed";
    
    const char* motionnwse_c_[] ={ "mia", "resources/in.png", "-motionblur-nw-se", "3.0", "out.png"};
    std::vector<std::string> v13(motionnwse_c_, std::end(motionnwse_c_));
	image_tools::CommandLineProcessor motionnwse_(image_editor_);
	motionnwse_.image_tools::CommandLineProcessor::ProcessCommandLine(5, str_to_charr(v13,5));
    std::vector<image_tools::ImageEditorCommand*> monwse_cmd_ = motionnwse_.getcmd();
	image_tools::MotionBlurFilterCommand* motionnwseCmd = dynamic_cast<image_tools::MotionBlurFilterCommand*>(monwse_cmd_.at(2));
	EXPECT_EQ(NULL, motionnwseCmd) << "motionblur nw-se command not processed";
}
