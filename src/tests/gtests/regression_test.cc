// Copyright (c) 2015-2018 Songyu Yan, Daniel Keefe, TAs, & Regents
// of the University of Minnesota.

#include <iostream>
#include <string>
#include <cstring>
#include <deque>
#include "gtest/gtest.h"
#include "imagetools/image_editor.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/filter_motionblur.h"

class RegressionTest : public :: testing :: Test {
	void SetUp() override { 
		filesource = "resources/";
        buffer_ = new image_tools::PixelBuffer("resources/in.png");
		image_editor_  = new image_tools::ImageEditor(buffer_);
	}
	
	void TearDown() override {
		delete image_editor_;
		delete buffer_;
	}

 protected:
  image_tools::ImageEditor* image_editor_;
  image_tools::PixelBuffer* buffer_ ;
  std::string filesource;
  enum MBlurDir {
    MBLUR_DIR_N_S,
    MBLUR_DIR_E_W,
    MBLUR_DIR_NE_SW,
    MBLUR_DIR_NW_SE
  };
  MBlurDir mblur_dir_;
  static const std::map<MBlurDir, std::string> mblur_dir_names_;

};
  const std::map<RegressionTest::MBlurDir, std::string>
  RegressionTest::mblur_dir_names_ = {
    {MBLUR_DIR_N_S,   "North/South"},
    {MBLUR_DIR_E_W,   "East/West"},
    {MBLUR_DIR_NE_SW, "Northeast/Southwest"},
    {MBLUR_DIR_NW_SE, "Northwest/Southeast"}
};

TEST_F(RegressionTest, QuantizeTest) {
	image_tools::PixelBuffer de_correct_quan("resources/correct-quantize-5.png");
	image_editor_ -> ApplyQuantizeFilter(5);
	image_tools::PixelBuffer* current_quan = image_editor_->pixel_buffer();
    image_editor_ -> SaveToFile("resources/generated5quantize.png");
    image_editor_ -> LoadFromFile("resources/generated5quantize.png");
	EXPECT_TRUE(*current_quan == de_correct_quan)<<"quantize filter regression test failed";
}

TEST_F(RegressionTest, EdgeTest) {
	image_tools::PixelBuffer de_correct_edge("resources/correct-edge.png");
	image_editor_ -> ApplyEdgeDetectFilter();
	image_tools::PixelBuffer* current_edge = image_editor_->pixel_buffer();
    image_editor_ -> SaveToFile("resources/generatededge.png");
    image_editor_ -> LoadFromFile("resources/generatededge.png");
	EXPECT_TRUE(*current_edge == de_correct_edge)<<"Edgedetect filter regression test failed";
}

TEST_F(RegressionTest, SaturateTest) {
    image_tools::PixelBuffer de_correct_saturate("resources/correct-saturate-3.png");
	image_editor_ -> ApplySaturateFilter(3.0);
	image_tools::PixelBuffer* current_satu = image_editor_->pixel_buffer();
    image_editor_ -> SaveToFile("resources/generated3satu.png");
    image_editor_ -> LoadFromFile("resources/generated3satu.png");
	EXPECT_TRUE(*current_satu == de_correct_saturate)<<"Saturate filter regression test failed";
}

TEST_F(RegressionTest, BlurTest) {
    image_tools::PixelBuffer de_correct_blur("resources/correct-blur-3.png");
	image_editor_ -> ApplyBlurFilter(3.0);
	image_tools::PixelBuffer* current_blur = image_editor_->pixel_buffer();
    image_editor_ -> SaveToFile("resources/generated3blur.png");
    image_editor_ -> LoadFromFile("resources/generated3blur.png");
	EXPECT_TRUE(*current_blur == de_correct_blur)<<"Blur filter regression test failed";
}

TEST_F(RegressionTest, SharpenTest) {
    image_tools::PixelBuffer de_correct_sharpen("resources/correct-sharpen-3.png");
	image_editor_ -> ApplySharpenFilter(3.0);
	image_tools::PixelBuffer* current_sharpen = image_editor_->pixel_buffer();
    image_editor_ -> SaveToFile("resources/generated3sharpen.png");
    image_editor_ -> LoadFromFile("resources/generated3sharpen.png");
	EXPECT_TRUE(*current_sharpen == de_correct_sharpen)<<"Sharpen filter regression test failed";
}

TEST_F(RegressionTest, RedTest) {
    image_tools::PixelBuffer de_correct_red("resources/correct-red-3.png");
	image_editor_ -> ApplyChannelsFilter(3.0, 1.0, 1.0);
	image_tools::PixelBuffer* current_red = image_editor_->pixel_buffer();
    image_editor_ -> SaveToFile("resources/generated3red.png");
    image_editor_ -> LoadFromFile("resources/generated3red.png");
	EXPECT_TRUE(*current_red == de_correct_red)<<"Red filter regression test failed";
}	

TEST_F(RegressionTest, GreenTest) {
    image_tools::PixelBuffer de_correct_green("resources/correct-green-3.png");
	image_editor_ -> ApplyChannelsFilter(1.0, 3.0, 1.0);
	image_tools::PixelBuffer* current_green = image_editor_->pixel_buffer();
    image_editor_ -> SaveToFile("resources/generated3green.png");
    image_editor_ -> LoadFromFile("resources/generated3green.png");
	EXPECT_TRUE(*current_green == de_correct_green)<<"Red filter regression test failed";
}		

TEST_F(RegressionTest, BlueTest) {
    image_tools::PixelBuffer de_correct_blue("resources/correct-blue-3.png");
	image_editor_ -> ApplyChannelsFilter(1.0, 1.0, 3.0);
	image_tools::PixelBuffer* current_blue = image_editor_->pixel_buffer();
    image_editor_ -> SaveToFile("resources/generated3blue.png");
    image_editor_ -> LoadFromFile("resources/generated3blue.png");
	EXPECT_TRUE(*current_blue == de_correct_blue)<<"Blue filter regression test failed";
}	

TEST_F(RegressionTest, ThresholdTest) {
    image_tools::PixelBuffer de_correct_threshold("resources/correct-threshold-3.png");
	image_editor_ -> ApplyThresholdFilter(3.0);
	image_tools::PixelBuffer* current_threshold = image_editor_->pixel_buffer();
    image_editor_ -> SaveToFile("resources/generated3threshold.png");
    image_editor_ -> LoadFromFile("resources/generated3threshold.png");
	EXPECT_TRUE(*current_threshold == de_correct_threshold)<<"Threshold filter regression test failed";
}

TEST_F(RegressionTest, MotionBlurNSTest) {
    image_tools::PixelBuffer de_correct_mbns("resources/correct-mbns-3.png");
    image_editor_ -> ApplyMotionBlurFilter
    (3.0, static_cast<image_tools::FilterMotionblur::MBlurDir>(MBLUR_DIR_N_S));
	image_tools::PixelBuffer* current_mbns = image_editor_->pixel_buffer();
    image_editor_ -> SaveToFile("resources/generated3mbns.png");
    image_editor_ -> LoadFromFile("resources/generated3mbns.png");
	EXPECT_TRUE(*current_mbns == de_correct_mbns)<<"MotionBlurNS filter regression test failed";
}

TEST_F(RegressionTest, MotionBlurEWTest) {
    image_tools::PixelBuffer de_correct_mbew("resources/correct-mbew-3.png");
    image_editor_ -> ApplyMotionBlurFilter
    (3.0, static_cast<image_tools::FilterMotionblur::MBlurDir>(MBLUR_DIR_E_W));
	image_tools::PixelBuffer* current_mbew = image_editor_->pixel_buffer();
    image_editor_ -> SaveToFile("resources/generated3mbew.png");
    image_editor_ -> LoadFromFile("resources/generated3mbew.png");
	EXPECT_TRUE(*current_mbew == de_correct_mbew)<<"MotionBlurEW filter regression test failed";
}

TEST_F(RegressionTest, MotionBlurNESWTest) {
    image_tools::PixelBuffer de_correct_mbnesw("resources/correct-mbnesw-3.png");
    image_editor_ -> ApplyMotionBlurFilter
    (3.0, static_cast<image_tools::FilterMotionblur::MBlurDir>(MBLUR_DIR_NE_SW));
	image_tools::PixelBuffer* current_mbnesw = image_editor_->pixel_buffer();
    image_editor_ -> SaveToFile("resources/generated3mbnesw.png");
    image_editor_ -> LoadFromFile("resources/generated3mbnesw.png");
	EXPECT_TRUE(*current_mbnesw == de_correct_mbnesw)<<"MotionBlurNESW filter regression test failed";
}

TEST_F(RegressionTest, MotionBlurNWSETest) {
    image_tools::PixelBuffer de_correct_mbnwse("resources/correct-mbnwse-3.png");
    image_editor_ -> ApplyMotionBlurFilter
    (3.0, static_cast<image_tools::FilterMotionblur::MBlurDir>(MBLUR_DIR_NW_SE));
	image_tools::PixelBuffer* current_mbnwse = image_editor_->pixel_buffer();
    image_editor_ -> SaveToFile("resources/generated3mbnwse.png");
    image_editor_ -> LoadFromFile("resources/generated3mbnwse.png");
	EXPECT_TRUE(*current_mbnwse == de_correct_mbnwse)<<"MotionBlurNWSE filter regression test failed";
}

TEST_F(RegressionTest, ToolPenTest) {
    image_tools::PixelBuffer de_correct_pen("resources/correct-pen.png");
    image_tools::ColorData color(1.0, 0, 0);
    std::string name = "Pen";
    image_editor_ -> StartStroke(name, color, 5.0, 0, 0);
    image_editor_ -> AddToStroke(100, 100);
    image_editor_ -> EndStroke(100, 100);
    image_editor_ -> SaveToFile("resources/generatedpen.png");
    image_editor_ -> LoadFromFile("resources/generatedpen.png");
    image_tools::PixelBuffer* pen_buffer = image_editor_ -> pixel_buffer();
    EXPECT_TRUE(*pen_buffer == de_correct_pen) << "Tool pen regression test failed";
}

TEST_F(RegressionTest, ToolStampTest) {
    image_tools::PixelBuffer de_correct_stamp("resources/correct-stamp.png");
    image_tools::ColorData color(1.0, 0, 0);
    std::string name = "Stamp";
    image_editor_ -> StartStroke(name, color, 5.0, 0, 0);
    image_editor_ -> AddToStroke(100, 100);
    image_editor_ -> EndStroke(100, 100);
    image_editor_ -> SaveToFile("resources/generatedstamp.png");
    image_editor_ -> LoadFromFile("resources/generatedstamp.png");
    image_tools::PixelBuffer* stamp_buffer = image_editor_ -> pixel_buffer();
    EXPECT_TRUE(*stamp_buffer == de_correct_stamp) << "Tool stamp regression test failed";
}

TEST_F(RegressionTest, ToolSprayCanTest) {
    image_tools::PixelBuffer de_correct_spray("resources/correct-spraycan.png");
    image_tools::ColorData color(1.0, 0, 0);
    std::string name = "Spray Can";
    image_editor_ -> StartStroke(name, color, 5.0, 0, 0);
    image_editor_ -> AddToStroke(100, 100);
    image_editor_ -> EndStroke(100, 100);
    image_editor_ -> SaveToFile("resources/generatedspraycan.png");
    image_editor_ -> LoadFromFile("resources/generatedspraycan.png");
    image_tools::PixelBuffer* spray_buffer = image_editor_ -> pixel_buffer();
    EXPECT_TRUE(*spray_buffer == de_correct_spray) << "Tool spray can regression test failed";
}

TEST_F(RegressionTest, ToolHighlighterTest) {
    image_tools::PixelBuffer de_correct_highlighter("resources/correct-highlighter.png");
    image_tools::ColorData color(1.0, 0, 0);
    std::string name = "Highlighter";
    image_editor_ -> StartStroke(name, color, 5.0, 0, 0);
    image_editor_ -> AddToStroke(100, 100);
    image_editor_ -> EndStroke(100, 100);
    image_editor_ -> SaveToFile("resources/generatedhighlighter.png");
    image_editor_ -> LoadFromFile("resources/generatedhighlighter.png");
    image_tools::PixelBuffer* highlighter_buffer = image_editor_ -> pixel_buffer();
    EXPECT_TRUE(*highlighter_buffer == de_correct_highlighter) << "Tool highlighter regression test failed";
}

TEST_F(RegressionTest, ToolEraserTest) {
    image_tools::PixelBuffer de_correct_eraser("resources/correct-eraser.png");
    image_tools::PixelBuffer* test_buffer = new image_tools::PixelBuffer("resources/correct-highlighter.png");
    image_tools::ColorData color(1.0, 0, 0);
    std::string name = "Eraser";
    image_editor_ -> set_pixel_buffer(test_buffer);
    image_editor_ -> StartStroke(name, color, 5.0, 0, 0);
    image_editor_ -> AddToStroke(100, 100);
    image_editor_ -> EndStroke(100, 100);
    image_editor_ -> SaveToFile("resources/generatederaser.png");
    image_editor_ -> LoadFromFile("resources/generatederaser.png");
    image_tools::PixelBuffer* eraser_buffer = image_editor_ -> pixel_buffer();
    EXPECT_TRUE(*eraser_buffer == de_correct_eraser) << "Tool eraser regression test failed";
}

TEST_F(RegressionTest, ToolChalkTest) {
    image_tools::PixelBuffer de_correct_chalk("resources/correct-chalk.png");
    image_tools::ColorData color(1.0, 0, 0);
    std::string name = "Chalk";
    image_tools::ToolChalk chalk_;
    chalk_.set_seed(10);
    image_editor_ -> StartStroke(chalk_.name(), color, 5.0, 0, 0);
    image_editor_ -> AddToStroke(100, 100);
    image_editor_ -> EndStroke(100, 100);
    image_editor_ -> SaveToFile("resources/generatedchalk.png");
    image_editor_ -> LoadFromFile("resources/generatedchalk.png");
    image_tools::PixelBuffer* chalk_buffer = image_editor_ -> pixel_buffer();
    EXPECT_TRUE(*chalk_buffer == de_correct_chalk) << "Tool chalk regression test failed";
}

TEST_F(RegressionTest, ToolCaliPenTest) {
    image_tools::PixelBuffer de_correct_calipen("resources/correct-caligraphypen.png");
    image_tools::ColorData color(1.0, 0, 0);
    std::string name = "Caligraphy Pen";
    image_editor_ -> StartStroke(name, color, 5.0, 0, 0);
    image_editor_ -> AddToStroke(100, 100);
    image_editor_ -> EndStroke(100, 100);
    image_editor_ -> SaveToFile("resources/generatedcalipen.png");
    image_editor_ -> LoadFromFile("resources/generatedcalipen.png");
    image_tools::PixelBuffer* calipen_buffer = image_editor_ -> pixel_buffer();
    EXPECT_TRUE(*calipen_buffer == de_correct_calipen) << "Tool caligraphy pen regression test failed";
}

TEST_F(RegressionTest, ToolBlurTest) {
    image_tools::PixelBuffer de_correct_blur("resources/correct-blur.png");
    image_tools::ColorData color(1.0, 0, 0);
    std::string name = "Blur";
    image_editor_ -> StartStroke(name, color, 5.0, 0, 0);
    image_editor_ -> AddToStroke(100, 100);
    image_editor_ -> EndStroke(100, 100);
    image_editor_ -> SaveToFile("resources/generatedblur.png");
    image_editor_ -> LoadFromFile("resources/generatedblur.png");
    image_tools::PixelBuffer* blur_buffer = image_editor_ -> pixel_buffer();
    EXPECT_TRUE(*blur_buffer == de_correct_blur) << "Tool blur regression test failed";
}
