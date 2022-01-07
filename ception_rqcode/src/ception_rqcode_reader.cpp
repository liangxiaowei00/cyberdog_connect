#include <memory>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <string.h>
#include <thread>
#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "ReadBarcode.h"
#include "TextUtfEncoding.h"
#include "GTIN.h"
#include "std_msgs/msg/string.hpp"
#include <sensor_msgs/msg/image.hpp>
#include "back_trace.h"
#define stoptimelong 1  //Sleep函数以毫秒为单位，Sleep(500);表示停半秒

using std::placeholders::_1;
using namespace ZXing;
using namespace ZXing::TextUtfEncoding;
/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */
namespace cyberdog
{
namespace ception 
{


class QrcodeRead : public rclcpp::Node
{
  public:
    QrcodeRead()
    : Node("qrcode_read")
    {
      subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
      "/camera/color/image_raw", 10, std::bind(&QrcodeRead::topic_callback, this, _1));
    }

  private:
    void topic_callback(const sensor_msgs::msg::Image::SharedPtr ptr_img) 
    {
      RCLCPP_INFO(this->get_logger(), "hello_world");

      //auto rgb_0=ptr_img->data;
      
      int num_pixels=ptr_img->step*ptr_img->height;
      uint8_t *img_buffer=new uint8_t[num_pixels];
      //std::cout<<"11111num_pixels:"<<num_pixels<<std::endl;

      //uint8_t img_buffer[2764800]={};
      int i;
      for (i=0;i<num_pixels;i++)
      {
        img_buffer[i]=(ptr_img->data)[i];
      }
      std::cout<<"size of data "<<(ptr_img->data).size()<<std::endl;
      std::cout<<"size of data_ptr "<<num_pixels<<std::endl;


      
      DecodeHints hints;
      std::string outPath;
      bool oneLine = false;
	    bool angleEscape = false;
      hints.setEanAddOnSymbol(EanAddOnSymbol::Read);
      std::cout<<"11111"<<std::endl;

      ImageView image{img_buffer, int(ptr_img->width), int(ptr_img->height), ImageFormat::RGB};
   		std::cout<<image.width()<<std::endl;

      std::cout<<"2222"<<std::endl;
		  auto results = ReadBarcodes(image, hints);
      std::cout<<"000000000"<<std::endl;
      // std::this_thread::sleep_for(std::chrono::seconds(2));
      std::cout<<"after sleep"<<std::endl;

      if (results.empty()){
        results.emplace_back(DecodeStatus::NotFound);
      }
        

      for (auto&& result : results) 
      {
        std::cout << "Text:     \"" << ToUtf8(result.text(), angleEscape) << "\"\n"
					  << "Format:   " << ToString(result.format()) << "\n"
					  //<< "Position: " << result.position() << "\n"
					  << "Rotation: " << result.orientation() << " deg\n"
					  << "Error:    " << ToString(result.status()) << "\n";
      
      } //for
      sleep(stoptimelong);

      //delete [] img_buffer;
    }//topic_callback

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

} //ception
} //cyberdog


int main(int argc, char * argv[])
{
  signal(SIGSEGV, signal_handler);
  signal(SIGABRT, signal_handler);

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<cyberdog::ception::QrcodeRead>());
  rclcpp::shutdown();
  return 0;
}
    